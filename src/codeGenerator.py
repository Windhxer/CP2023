import re
import sys
regs = ["t0", "t1", "t2", "t3", "t4", "t5", "t6", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11"]
regsAllocation = {} # {temp, ref} 查看temp分配了哪个寄存器
regsAvailable = {} # {reg, bool}查看寄存器是否被分配
temps = [] # 所有会出现的temp
lines = []
result = []
funcStarts = []
funcEnds = []
innerCodePath = ""
asmPath = ""
stringMap = {} # 字符串储存在只读数据段中
strings = []
regNeedToBeDeleted = []

def init():
    result.append("\t.option nopic")
    result.append('\t.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"')
    result.append("\t.attribute unaligned_access, 0")
    result.append("\t.attribute stack_align, 16")

    global temps
    global strings
    for line in open(innerCodePath, "r", encoding="utf-8"):
        line = line.replace("\r", "").replace("\n", "")
        strings += [string.replace('"', "") for string in re.findall("(\".*\")", line)]
        temps += re.findall("(\d+temp\d+)", line)
        if line != "":
            tokenList = re.split(r'\s(?=(?:[^"]*"[^"]*")*[^"]*$)', line)
            lines.append(tokenList)
    for reg in regs:
        regsAvailable[reg] = True
    for i in range(len(lines)):
        line = " ".join(lines[i])
        if line.startswith("FUNCTION"):
            funcStarts.append(i)
        if line.startswith("END"):
            funcEnds.append(i)
    if len(strings) != 0:
        result.append("\t.text")
        result.append("\t.section .rodata")
        num = 0
        for string in strings:
            if string not in stringMap:
                stringMap[string] = ".STRING%d"%num
                num += 1
        for key, value in stringMap.items():
            result.append("\t.align 3")
            result.append("%s:"%value)
            result.append('\t.string "%s"'%key)
    result.append("\t.text")

def addLoadOrStoreInst(inst, reg1, offset, reg2):
    if offset < -2048 or offset > 2047:
        reg = getReg("")
        result.append("\tli %s, %d"%(reg, offset))
        result.append("\tadd %s, %s, %s"%(reg, reg, reg2))
        result.append("\t%s %s, 0(%s)"%(inst, reg1, reg))
        deleteReg(reg)
    else:
        result.append("\t%s %s, %d(%s)"%(inst, reg1, offset, reg2))

def addImmInst(inst, rd, rs, imm):
    if imm < -2048 or imm > 2047:
        reg = getReg("")
        result.append("\tli %s, %d"%(reg, imm))
        result.append("\t%s %s, %s, %s"%(inst[:-1], rd, rs, reg))
        deleteReg(reg)
    else:
        result.append("\t%s %s, %s, %d"%(inst, rd, rs, imm))

def getLoadOrStoreScope(var):
    size = int(re.search("(\d+).*", var).group(1))
    if size == 1:
        return "b"
    elif size == 2:
        return "h"
    elif size == 4:
        return "w"
    elif size == 8:
        return "d"

def getArithmeticScope(var):
    size = int(re.search("(\d+).*", var).group(1))
    if size == 1:
        return "b"
    elif size == 2:
        return "h"
    elif size == 4:
        return "w"
    elif size == 8:
        return ""


# name = temp%d or var%d
def getReg(name):
    if name == "":
        for key, value in regsAvailable.items():
            if value == True:
                regsAvailable[key] = False
                return key
    else:
        try:
            temps.remove(name)
        except:
            pass
        if name in regsAllocation:
            return regsAllocation[name]
        else:
            keys = []
            for key in regsAllocation:
                keys.append(key)
            for key in keys:
                if key not in temps:
                    regsAvailable[regsAllocation[key]] = True
                    del regsAllocation[key]
            for reg in regs:
                if regsAvailable[reg] == True:
                    regsAllocation[name] = reg
                    regsAvailable[reg] = False
                    return reg

def deleteReg(name):
    regsAvailable[name] = True

def loadValueInReg(name, varMap):
    global result
    global regNeedToBeDeleted
    match1 = re.search("(\d+)\*(.*\d+)", name)
    match2 = re.search("(\d+)&(.*\d+)", name)
    # 从一个temp上取指针得来的，加载temp所在的寄存器所对应的地址的内容
    if match1:
        rs = getReg("")
        result.append("l%s %s, 0(%s)"%(getLoadOrStoreScope(name), rs, getReg(match1.group(2))))
        regNeedToBeDeleted.append(rs)
        return rs
    elif match2:
        rs = getReg("")
        var = match2.group(2)
        addImmInst("addi", rs, "s0", varMap[var])
        regNeedToBeDeleted.append(rs)
        return rs
    elif "var" in name:
        rs = getReg("")
        addLoadOrStoreInst("l%s"%getLoadOrStoreScope(name), rs, varMap[name], "s0")
        regNeedToBeDeleted.append(rs)
        return rs
    elif "temp" in name:
        return getReg(name)

# arrayMap对应的是数组的起始地址的相对值（相对s0），varMap对应变量的相对地址（相对s0）
def generateFunctionNode(start, end, varMap, funcName):
    global result
    global regNeedToBeDeleted
    argNum = 0
    paraNum = 0
    for i in range(start, end):
        line = lines[i]
        # LABEL 语句
        if line[0] == "LABEL":
            result.append(".%s:"%line[1])
        # RETURN
        elif line[0] == "RETURN":
            if len(line) == 2:
                match = re.search("(\d+)\*(.*)", line[-1])
                match2 = re.search("(\d+)&(.*)", line[-1])
                # 一定是 *temp
                if match:
                    result.append("\tl%s a0, 0(%s)"%(getLoadOrStoreScope(line[-1]), getReg(match.group(2))))
                # 一定是 &var
                elif match2:
                    addr = match2.group(2)
                    addImmInst("addi", "a0", "s0", varMap[addr])
                elif "var" in line[-1]:
                    addLoadOrStoreInst("l%s"%getLoadOrStoreScope(line[-1]), "a0", varMap[line[-1]], "s0")
                elif "temp" in line[-1]:
                    result.append("\tmv a0, %s"%(getReg(line[-1])))
            result.append("\tj .%sReturn"%(funcName))
        # 赋值语句
        elif line[1] == ":=":
            # var/temp := var/temp/I
            if len(line) == 3:
				# temp := "str"
                if line[-1][0] == '"':
                    rd = getReg(line[0])
                    result.append("\tlui %s, %%hi(%s)"%(rd, stringMap[line[-1].replace('"', "")]))
                    result.append("\taddi %s, %s, %%lo(%s)"%(rd, rd, stringMap[line[-1].replace('"', "")]))
                # temp := 'c'
                elif line[-1][0] == "'":
                    ascii = ord(line[-1][1])
                    result.append("\tli %s, %d"%(getReg(line[0]), ascii))
				# temp := I
                elif line[-1][0] == "I":
                    result.append("\tli %s, %s"%(getReg(line[0]), line[-1].replace("I", "")))
                else:
                    rs = loadValueInReg(line[-1], varMap)
					# &仅存在与 temp := &var, 赋值左侧没有&
                    match = re.search("(\d+)\*(.*)", line[0])
                    if match:
                        result.append("\ts%s %s, 0(%s)"%(getLoadOrStoreScope(line[0]), rs, getReg(match.group(2))))
                    elif "var" in line[0]:
                        addLoadOrStoreInst("s%s"%getLoadOrStoreScope(line[0]), rs, varMap[line[0]], "s0")
                    elif "temp" in line[0]:
                        result.append("\tmv %s, %s"%(getReg(line[0]), rs))
                    for reg in regNeedToBeDeleted:
                        deleteReg(reg)
                    regNeedToBeDeleted.clear()
            # var/temp/*temp := var/temp/*temp +/-/*/<</>>// var/temp/*temp
            elif len(line) == 5:
                inst = ""
                if line[3] == "+":
                    inst = "add"
                elif line[3] == "-":
                    inst = "sub"
                elif line[3] == "*":
                    inst = "mul"
                elif line[3] == "/":
                    inst = "div"
                elif line[3] == "RIGHT_OP":
                    inst = "sra"
                elif line[3] == "LEFT_OP":
                    inst = "sll"
                if inst != "":
                    rs1 = loadValueInReg(line[2], varMap)
                    rs2 = loadValueInReg(line[-1], varMap)
                    match = re.search("(\d+)\*(.*)", line[0])
                    if match:
                        temp = getReg("")
                        result.append("\t%s %s, %s, %s"%(inst, temp, rs1, rs2))
                        result.append("\ts%s %s, 0(%s)"%(getLoadOrStoreScope(line[0]), temp, getReg(match.group(2))))
                        deleteReg(temp)
                    elif "var" in line[0]:
                        temp = getReg("")
                        result.append("\t%s %s, %s, %s"%(inst, temp, rs1, rs2))
                        addLoadOrStoreInst("s%s"%getLoadOrStoreScope(line[0]), temp, varMap[line[0]], "s0")
                        deleteReg(temp)
                    elif "temp" in line[0]:
                        result.append("\t%s %s, %s, %s"%(inst, getReg(line[0]), rs1, rs2))
                    for reg in regNeedToBeDeleted:
                        deleteReg(reg)
                    regNeedToBeDeleted.clear()
            # temp := CALL FUN
            elif line[2] == "CALL":
                result.append("\tcall %s"%(line[-1]))
                match = re.search("(\d+)\*(.*)", line[0])
                if match:
                    result.append("\ts%s a0, 0(%s)"%(getLoadOrStoreScope(line[0]), match.group(2)))
                elif "var" in line[0]:
                    addLoadOrStoreInst("s%s"%getLoadOrStoreScope(line[0]), "a0", varMap[line[0]], "s0")
                elif "temp" in line[0]:
                    result.append("\tmv %s, a0"%(getReg(line[0])))
                argNum = 0
        elif line[0] == "GOTO":
            result.append("\tj .%s"%(line[1]))

        # IF temp/var/*temp < temp/var/*temp GOTO lable
        elif line[0] == "IF":
            reg1 = loadValueInReg(line[1], varMap)
            reg2 = loadValueInReg(line[3], varMap)
            if line[2] == "EQ_OP":
                result.append("\tbeq %s, %s, .%s"%(reg1, reg2, line[-1]))
            elif line[2] == "NE_OP":
                result.append("\tbne %s, %s, .%s"%(reg1, reg2, line[-1]))
            elif line[2] == ">":
                result.append("\tbgt %s, %s, .%s"%(reg1, reg2, line[-1]))
            elif line[2] == "<":
                result.append("\tblt %s, %s, .%s"%(reg1, reg2, line[-1]))
            elif line[2] == ">=":
                result.append("\tbge %s, %s, .%s"%(reg1, reg2, line[-1]))
            elif line[2] == "<=":
                result.append("\tble %s, %s, .%s"%(reg1, reg2, line[-1]))
        elif line[0] == "ARG":
            match = re.search("(\d+)\*(.*)", line[1])
            if match:
                result.append("\tl%s a%d, 0(%s)"%(getLoadOrStoreScope(line[1]), argNum, getReg(match.group(2))))
                argNum += 1
            elif "var" in line[1]:
                addLoadOrStoreInst("l%s"%getLoadOrStoreScope(line[1]), "a%d"%argNum, varMap[line[1]], "s0")
                argNum += 1
            elif "temp" in line[1]:
                result.append("\tmv a%d, %s"%(argNum, getReg(line[1])))
                argNum += 1
        elif line[0] == "PARAM":
            addLoadOrStoreInst("s%s"%getLoadOrStoreScope(line[1]), "a%d"%paraNum, varMap[line[1]], "s0")
            paraNum += 1
        elif line[0] == "CALL":
            result.append("\tcall %s"%(line[1]))
            argNum = 0

def findArraySize(lineIndex, sizeExpression):
    if "temp" not in sizeExpression:
        return sizeExpression
    else:
        for i in range(lineIndex, -1, -1):
            if lines[i][0] == sizeExpression and lines[i][1] == ":=":
                if lines[i][-1][0] == "I":
                    return lines[i][-1].replace("I", "")
                else:
                    if len(lines[i]) == 3:
                        pass
                    elif len(lines[i]) == 5:
                        temp1 = lines[i][2]
                        temp2 = lines[i][-1]
                        temp1 = findArraySize(i, temp1)
                        temp2 = findArraySize(i, temp2)
                        return "(%s%s%s)"%(temp1, lines[i][3], temp2)

def generateCode():
    init()
    global result

    # 有全局变量


    for i in range(len(funcStarts)):
        start = funcStarts[i]
        end = funcEnds[i]
        varMap = {}
        arrayMap = {}
        frameSize = 0
        funcName = lines[start][1]
        location = 0

        for j in range(start, end):
            # ARRAY 8var0 4temp0 * 4temp1
            if lines[j][0] == "ARRAY":
                arrayMap[lines[j][1]] = location
                step = findArraySize(j, lines[j][2])
                size = findArraySize(j, lines[j][-1])
                totalSize = eval("%s * %s"%(step, size))
                location += totalSize
                
                
        for j in range(start, end):
            for var in re.findall("(\d+)(var\d+)", " ".join(lines[j])):
                if var[0] + var[1] not in varMap:
                    varMap[var[0] + var[1]] = location
                    location += int(var[0])
        frameSize = location + 24
        while frameSize % 16 != 0:
            frameSize += 1

        for key, value in varMap.items():
            varMap[key] = value - frameSize

        for key, value in arrayMap.items():
            arrayMap[key] = value - frameSize

        result.append("\t.align 1")
        result.append("\t.globl %s"%funcName)
        result.append("\t.type %s, @function"%funcName)
        result.append("%s:"%funcName)

        addImmInst("addi", "sp", "sp", -frameSize)
        addLoadOrStoreInst("sd", "ra", frameSize - 8, "sp")
        addLoadOrStoreInst("sd", "s0", frameSize - 16, "sp")
        addImmInst("addi", "s0", "sp", frameSize)

        for key, value in arrayMap.items():
            reg = getReg("")
            addImmInst("addi", reg, "s0", value)
            addLoadOrStoreInst("sd", reg, varMap[key], "s0")
            deleteReg(reg)
        print(varMap)
        generateFunctionNode(start, end, varMap, funcName)

        result.append(".%sReturn:"%(funcName))
        addLoadOrStoreInst("ld", "ra", frameSize - 8, "sp")
        addLoadOrStoreInst("ld", "s0", frameSize - 16, "sp")
        addImmInst("addi", "sp", "sp", frameSize)
        result.append("\tjr ra")
        result.append("\t.size\t%s, .-%s"%(funcName, funcName))

    result.append('\t.ident	"GCC: (SiFive GCC 10.1.0-2020.08.2) 10.1.0"')
    with open(asmPath, "w") as file:
        for line in result:
            file.write(line)
            file.write("\n")

arg1 = sys.argv[1]
arg2 = sys.argv[2]
innerCodePath = arg1
asmPath = arg2
generateCode()

'''
char a = '1';
char *b = &a;
*b = '3'


1temp0 := '1'
1var0 := 1temp0
8temp1 := 8&1var0
8var1 := 8temp1
8temp2 := 8var1

import re
def remove_number_parentheses(text):
    pattern = '\((\d+)\)'  # 匹配包裹纯数字的括号，其中\d+表示匹配一个或多个数字
    result = re.sub(pattern, '\\1', text)  # 将匹配到的内容替换为括号内的数字
    return result

re.sub("\d")

text = '这是一个示例(123)文本，(456)包裹着纯数字的括号将被去掉。'
result = remove_number_parentheses(text)
print(result)
'''