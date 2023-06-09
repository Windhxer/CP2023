int check(char *course, char **coursesPass, int passCourseNum)
{
    for (int i = 0; i < passCourseNum; i = i + 1)
    {
        if (strcmp(coursesPass[i], course) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void process(int num, char **names, int *credits, char **preCourses, char *grades)
{
    int creditAll = 0, creditTry = 0, creditGet = 0, gradeMulCredet = 0;
    char *coursesPass[10000];
    int passCourseNum = 0;
    for (int i = 0; i < num; i = i + 1)
    {
        creditAll = creditAll + credits[i];
        
        if (grades[i] != '\0')
        {
            creditTry = creditTry + credits[i];
            if (grades[i] != 'F')
            {
                creditGet = creditGet + credits[i];
                coursesPass[passCourseNum] = strdup(names[i]);
                passCourseNum = passCourseNum + 1;
                gradeMulCredet = gradeMulCredet + ('E' - grades[i]) * credits[i];
            }
        }
    }
    int flag = 0;
    char *courseCanTake[10000];
    int canTakeIndex = 0;
    for (int i = 0; i < num; i = i + 1)
    {
        flag = 0;
        if (grades[i] == '\0')
        {
            flag = 1;
        }
        if (grades[i] == 'F')
        {
            flag = 1;
        }
        if (flag == 1)
        {
            int j = 0;
            char *this = preCourses[i];
            char remember[10000];
            int k = 0;
            int canBreak = 0;
            for (j = 0; 1 == 1; j = j + 1)
            {
                if (canBreak == 1)
                {
                    canBreak = 0;
                    break;
                }
                if (this[j] == '\0')
                {
                    remember[k] = '\0';
                    int get;
                    if (k == 0)
                    {
                        get = 1;
                    }
                    else
                    {
                        get = check(remember, coursesPass, passCourseNum);
                    }
                    if (get == 1)
                    {
                        courseCanTake[canTakeIndex] = strdup(names[i]);
                        canTakeIndex = canTakeIndex + 1;
                    }
                    k = 0;
                    break;
                }
                if (this[j] == ';')
                {
                    remember[k] = '\0';
                    int get;
                    if (k == 0)
                    {
                        get = 1;
                    }
                    else
                    {
                        get = check(remember, coursesPass, passCourseNum);
                    }
                    k = 0;
                    if (get == 1)
                    {
                        courseCanTake[canTakeIndex] = strdup(names[i]);
                        canTakeIndex = canTakeIndex + 1;
                        break;
                    }
                }
                else if (this[j] == ',')
                {
                    remember[k] = '\0';
                    k = 0;
                    int get = check(remember, coursesPass, passCourseNum);
                    if (get == 0)
                    {
                        for (j = j + 1; 1 == 1; j = j + 1)
                        {
                            if (this[j] == ';')
                            {
                                break;
                            }
                            if (this[j] == '\0')
                            {
                                canBreak = 1;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    remember[k] = this[j];
                    k = k + 1;
                }
            }
        }
    }
    if (creditTry == 0)
    {
        printf("GPA: 0.0\n");
    }
    else
    {
        int integer = gradeMulCredet / creditTry;
        int remainder1 = gradeMulCredet % creditTry;
        int digit1 = remainder1 * 10 / creditTry;
        int remainder2 = remainder1 * 10 % creditTry;
        int digit2 = remainder2 * 10 / creditTry;
        if (digit2 >= 5)
        {
            digit1 = digit1 + 1;
        }
        if (digit1 >= 10)
        {
            digit1 = 0;
            integer = integer + 1;
        }
        printf("GPA: %d.%d\n", integer, digit1);
    }
    printf("Hours Attempted: %d\n", creditTry);
    printf("Hours Completed: %d\n", creditGet);
    printf("Credits Remaining: %d\n", creditAll - creditGet);
    printf("\nPossible Courses to Take Next\n");
    if (canTakeIndex == 0)
    {
        if (creditAll == creditGet)
        {
            printf("  None - Congratulations!\n");
        }
    }
    else
    {
        for (int i = 0; i < canTakeIndex; i = i + 1)
        {
            printf("  %s\n", courseCanTake[i]);
        }
    }
}

int main() {
    // 获取输入
    char temp[5000];
	char *names[10000];
	int credits[10000];
	char *preCourses[10000];
	char grades[10000];
	int i = 0, j = 0;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
	int flag = 0;
    int index = 0;
    while (1 == 1) {
		char c;
		scanf("%c", &c);
		if (c == '\n')
		{
			temp[i] = '\0';
            i = 0;
            if (flag == 1)
			{
				break;
			}
			else
			{
				grades[i4] = temp[0];
                i4 = i4 + 1;
                index = 0;
                flag = 1;
			}
		}
		else
		{
			flag = 0;
            if (c == '|')
            {
                temp[i] = '\0';
                i = 0;
                if (index == 0)
                {
                    names[i1] = strdup(temp);
                    i1 = i1 + 1;
                    index = 1;
                }
                else if (index == 1)
                {
                    sscanf(temp, "%d", &credits[i2]);
                    i2 = i2 + 1;
                    index = 2;
                }
                else if (index == 2)
                {
                    preCourses[i3] = strdup(temp);
                    i3 = i3 + 1;
                    index = 3;
                }
            }
            else
            {
                temp[i] = c;
                i = i + 1;
            }
		}
    }

    if (i1 == i4)
    {
        process(i1, names, credits, preCourses, grades);
    }
    else
    {
        process(0, names, credits, preCourses, grades);
    }

    return 0;
}
