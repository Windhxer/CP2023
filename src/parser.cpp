
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 ".\\parser.y"

#include <stdio.h>
#include <fstream>
#include <string>
#include "tree.hpp"
#include "translator.hpp"
using namespace std;

extern char *yytext;
extern int column;
extern FILE * yyin;
extern FILE * yyout;
treeNode* root = NULL;
extern int yylineno;

int yylex(void);
void yyerror(const char*); 


/* Line 189 of yacc.c  */
#line 93 "parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     CONSTANT = 259,
     STRING_LITERAL = 260,
     SIZEOF = 261,
     CONSTANT_INT = 262,
     CONSTANT_DOUBLE = 263,
     CONSTANT_CHAR = 264,
     PTR_OP = 265,
     INC_OP = 266,
     DEC_OP = 267,
     LEFT_OP = 268,
     RIGHT_OP = 269,
     LE_OP = 270,
     GE_OP = 271,
     EQ_OP = 272,
     NE_OP = 273,
     AND_OP = 274,
     OR_OP = 275,
     MUL_ASSIGN = 276,
     DIV_ASSIGN = 277,
     MOD_ASSIGN = 278,
     ADD_ASSIGN = 279,
     SUB_ASSIGN = 280,
     LEFT_ASSIGN = 281,
     RIGHT_ASSIGN = 282,
     AND_ASSIGN = 283,
     XOR_ASSIGN = 284,
     OR_ASSIGN = 285,
     TYPE_NAME = 286,
     CHAR = 287,
     INT = 288,
     DOUBLE = 289,
     VOID = 290,
     BOOL = 291,
     CASE = 292,
     IF = 293,
     ELSE = 294,
     SWITCH = 295,
     WHILE = 296,
     DO = 297,
     FOR = 298,
     GOTO = 299,
     CONTINUE = 300,
     BREAK = 301,
     RETURN = 302,
     TRUE = 303,
     FALSE = 304,
     LOWER_THAN_ELSE = 305
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 20 ".\\parser.y"

	class treeNode* tN;



/* Line 214 of yacc.c  */
#line 185 "parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 197 "parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   662

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNRULES -- Number of states.  */
#define YYNSTATES  221

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,     2,     2,    64,    57,     2,
      72,    73,    62,    61,    51,    60,    56,    63,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    52,    50,
      65,    53,    66,    69,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    55,    67,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    70,    68,    71,    59,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    74
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    23,    25,    30,    34,    39,    42,    45,    47,    51,
      53,    56,    59,    62,    64,    66,    68,    70,    72,    74,
      76,    80,    84,    88,    90,    94,    98,   100,   104,   108,
     110,   114,   118,   122,   126,   128,   132,   136,   138,   142,
     144,   148,   150,   154,   156,   160,   162,   166,   168,   172,
     174,   176,   178,   180,   182,   184,   186,   188,   190,   192,
     194,   196,   200,   203,   207,   209,   213,   215,   219,   221,
     223,   225,   227,   229,   231,   236,   240,   245,   250,   254,
     256,   260,   263,   265,   267,   271,   273,   275,   277,   279,
     281,   283,   285,   289,   294,   297,   301,   303,   306,   308,
     310,   312,   315,   321,   329,   335,   341,   349,   356,   364,
     371,   379,   383,   386,   389,   392,   396,   398,   401,   403,
     405
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      76,     0,    -1,   113,    -1,     3,    -1,    48,    -1,    49,
      -1,     7,    -1,     8,    -1,     9,    -1,     5,    -1,    72,
      94,    73,    -1,    77,    -1,    78,    54,    94,    55,    -1,
      78,    72,    73,    -1,    78,    72,    79,    73,    -1,    78,
      11,    -1,    78,    12,    -1,    92,    -1,    79,    51,    92,
      -1,    78,    -1,    11,    80,    -1,    12,    80,    -1,    81,
      80,    -1,    61,    -1,    60,    -1,    59,    -1,    58,    -1,
      62,    -1,    57,    -1,    80,    -1,    82,    62,    80,    -1,
      82,    63,    80,    -1,    82,    64,    80,    -1,    82,    -1,
      83,    61,    82,    -1,    83,    60,    82,    -1,    83,    -1,
      84,    13,    83,    -1,    84,    14,    83,    -1,    84,    -1,
      85,    65,    84,    -1,    85,    66,    84,    -1,    85,    15,
      84,    -1,    85,    16,    84,    -1,    85,    -1,    86,    17,
      85,    -1,    86,    18,    85,    -1,    86,    -1,    87,    57,
      86,    -1,    87,    -1,    88,    67,    87,    -1,    88,    -1,
      89,    68,    88,    -1,    89,    -1,    90,    19,    89,    -1,
      90,    -1,    91,    20,    90,    -1,    91,    -1,    80,    93,
      92,    -1,    53,    -1,    21,    -1,    22,    -1,    23,    -1,
      24,    -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,
      29,    -1,    30,    -1,    92,    -1,    94,    51,    92,    -1,
      98,    50,    -1,    98,    96,    50,    -1,    97,    -1,    96,
      51,    97,    -1,    99,    -1,    99,    53,   103,    -1,    35,
      -1,    32,    -1,    33,    -1,    34,    -1,    36,    -1,     3,
      -1,    99,    54,    92,    55,    -1,    99,    54,    55,    -1,
      99,    72,   100,    73,    -1,    99,    72,   102,    73,    -1,
      99,    72,    73,    -1,   101,    -1,   100,    51,   101,    -1,
      98,    99,    -1,    98,    -1,     3,    -1,   102,    51,     3,
      -1,    92,    -1,   105,    -1,   106,    -1,   109,    -1,   110,
      -1,   111,    -1,   112,    -1,     3,    52,   104,    -1,    37,
      91,    52,   104,    -1,    70,    71,    -1,    70,   107,    71,
      -1,   108,    -1,   107,   108,    -1,    95,    -1,   104,    -1,
      50,    -1,    94,    50,    -1,    38,    72,    94,    73,   104,
      -1,    38,    72,    94,    73,   104,    39,   104,    -1,    40,
      72,    94,    73,   104,    -1,    41,    72,    94,    73,   104,
      -1,    42,   104,    41,    72,    94,    73,    50,    -1,    43,
      72,   109,   109,    73,   104,    -1,    43,    72,   109,   109,
      94,    73,   104,    -1,    43,    72,    95,   109,    73,   104,
      -1,    43,    72,    95,   109,    94,    73,   104,    -1,    44,
       3,    50,    -1,    45,    50,    -1,    46,    50,    -1,    47,
      50,    -1,    47,    94,    50,    -1,   114,    -1,   113,   114,
      -1,   115,    -1,    95,    -1,    98,    99,   106,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    59,    59,    66,    70,    74,    77,    81,    84,    87,
      90,    97,   100,   104,   108,   112,   116,   123,   126,   133,
     136,   140,   144,   151,   154,   157,   160,   163,   166,   173,
     176,   179,   182,   189,   192,   195,   202,   205,   209,   217,
     220,   223,   226,   230,   238,   241,   245,   252,   255,   262,
     265,   272,   275,   282,   285,   293,   296,   304,   308,   315,
     318,   322,   326,   330,   334,   338,   342,   346,   350,   354,
     362,   366,   374,   377,   384,   387,   393,   396,   404,   407,
     410,   413,   416,   424,   432,   441,   445,   449,   453,   462,
     465,   471,   477,   483,   486,   529,   583,   586,   589,   592,
     595,   598,   605,   608,   615,   618,   624,   627,   633,   636,
     642,   645,   652,   655,   658,   665,   668,   671,   674,   677,
     680,   687,   690,   693,   696,   699,   705,   708,   714,   718,
     728
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT",
  "STRING_LITERAL", "SIZEOF", "CONSTANT_INT", "CONSTANT_DOUBLE",
  "CONSTANT_CHAR", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP",
  "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN",
  "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "TYPE_NAME",
  "CHAR", "INT", "DOUBLE", "VOID", "BOOL", "CASE", "IF", "ELSE", "SWITCH",
  "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "TRUE",
  "FALSE", "';'", "','", "':'", "'='", "'['", "']'", "'.'", "'&'", "'!'",
  "'~'", "'-'", "'+'", "'*'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'",
  "'?'", "'{'", "'}'", "'('", "')'", "LOWER_THAN_ELSE", "$accept",
  "Program", "primary_expression", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "assignment_expression", "assignment_operator", "expression",
  "declaration", "init_declarator_list", "init_declarator",
  "type_specifier", "declarator", "parameter_list",
  "parameter_declaration", "identifier_list", "initializer", "statement",
  "labeled_statement", "compound_statement", "block_item_list",
  "block_item", "expression_statement", "selection_statement",
  "iteration_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
      59,    44,    58,    61,    91,    93,    46,    38,    33,   126,
      45,    43,    42,    47,    37,    60,    62,    94,   124,    63,
     123,   125,    40,    41,   305
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    77,    77,    77,    77,    77,    77,    77,
      77,    78,    78,    78,    78,    78,    78,    79,    79,    80,
      80,    80,    80,    81,    81,    81,    81,    81,    81,    82,
      82,    82,    82,    83,    83,    83,    84,    84,    84,    85,
      85,    85,    85,    85,    86,    86,    86,    87,    87,    88,
      88,    89,    89,    90,    90,    91,    91,    92,    92,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      94,    94,    95,    95,    96,    96,    97,    97,    98,    98,
      98,    98,    98,    99,    99,    99,    99,    99,    99,   100,
     100,   101,   101,   102,   102,   103,   104,   104,   104,   104,
     104,   104,   105,   105,   106,   106,   107,   107,   108,   108,
     109,   109,   110,   110,   110,   111,   111,   111,   111,   111,
     111,   112,   112,   112,   112,   112,   113,   113,   114,   114,
     115
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     4,     3,     4,     2,     2,     1,     3,     1,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     3,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     4,     3,     4,     4,     3,     1,
       3,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     4,     2,     3,     1,     2,     1,     1,
       1,     2,     5,     7,     5,     5,     7,     6,     7,     6,
       7,     3,     2,     2,     2,     3,     1,     2,     1,     1,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    79,    80,    81,    78,    82,     0,   129,     0,     2,
     126,   128,     1,    83,    72,     0,    74,    76,   127,    73,
       0,     0,     0,     0,     0,   130,    75,    76,     3,     9,
       6,     7,     8,     0,     0,     4,     5,    28,    26,    25,
      24,    23,    27,     0,    11,    19,    29,     0,    33,    36,
      39,    44,    47,    49,    51,    53,    55,    57,    95,    77,
      85,     0,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,   104,    70,     0,   108,     0,   109,
      96,    97,     0,   106,    98,    99,   100,   101,    93,    88,
      92,     0,    89,     0,    20,    21,     0,    15,    16,     0,
       0,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    59,     0,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    84,     0,    29,     0,     0,     0,     0,     0,
       0,     0,   122,   123,   124,     0,   111,     0,   105,   107,
      91,     0,    86,     0,    87,    10,     0,    13,     0,    17,
      58,    30,    31,    32,    35,    34,    37,    38,    42,    43,
      40,    41,    45,    46,    48,    50,    52,    54,    56,   102,
       0,     0,     0,     0,     0,     0,     0,   121,   125,    71,
      90,    94,    12,     0,    14,   103,     0,     0,     0,     0,
       0,     0,    18,   112,   114,   115,     0,     0,     0,     0,
       0,     0,     0,   119,     0,   117,     0,   113,   116,   120,
     118
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,    44,    45,   158,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    75,   112,    76,
       7,    15,    16,    78,    27,    91,    92,    93,    59,    79,
      80,    81,    82,    83,    84,    85,    86,    87,     9,    10,
      11
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -121
static const yytype_int16 yypact[] =
{
     104,  -121,  -121,  -121,  -121,  -121,    23,  -121,    12,   104,
    -121,  -121,  -121,  -121,  -121,   -34,  -121,    14,  -121,  -121,
      11,   590,   496,   275,     4,  -121,  -121,    18,  -121,  -121,
    -121,  -121,  -121,   590,   590,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,   590,  -121,    -3,   197,   590,    19,    -6,
      79,    -5,   124,   -28,    -8,   -35,    30,    53,  -121,  -121,
    -121,   -13,    26,   590,    13,    15,    17,   415,    46,    77,
      48,    70,   512,  -121,  -121,  -121,    99,  -121,    12,  -121,
    -121,  -121,   345,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
      11,   -30,  -121,   -29,  -121,  -121,   -27,  -121,  -121,   590,
     116,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,   590,  -121,   590,   590,   590,   590,   590,   590,
     590,   590,   590,   590,   590,   590,   590,   590,   590,   590,
     590,   590,  -121,   415,  -121,    -7,   590,   590,   590,   102,
     434,    95,  -121,  -121,  -121,   105,  -121,   590,  -121,  -121,
      22,   104,  -121,   144,  -121,  -121,   -25,  -121,   -26,  -121,
    -121,  -121,  -121,  -121,    19,    19,    -6,    -6,    79,    79,
      79,    79,    -5,    -5,   124,   -28,    -8,   -35,    30,  -121,
     415,   -23,   -17,   -16,    80,   528,   528,  -121,  -121,  -121,
    -121,  -121,  -121,   590,  -121,  -121,   415,   415,   415,   590,
     187,   204,  -121,   118,  -121,  -121,   -10,   415,     1,   415,
       2,   415,   113,  -121,   415,  -121,   415,  -121,  -121,  -121,
    -121
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -121,  -121,  -121,  -121,  -121,   -15,  -121,    44,    47,     8,
      43,    52,    42,    51,    41,    50,   119,   -21,  -121,   -41,
     -18,  -121,   163,     3,    -2,  -121,    33,  -121,  -121,   -63,
    -121,   168,  -121,   109,  -120,  -121,  -121,  -121,  -121,   177,
    -121
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      58,    61,    96,     8,   139,    77,    17,    88,    97,    98,
     121,   122,     8,   131,    13,    13,    19,    20,    94,    95,
     186,   151,   153,    12,   147,   193,   147,    90,   147,   127,
     192,   145,   113,   129,   147,   147,     1,     2,     3,     4,
       5,   147,   132,   152,   154,   180,   155,   194,   134,   130,
     196,    99,   147,   147,   117,   118,   197,   198,   156,   128,
     123,   124,    14,   212,    77,   200,   201,    21,    22,   100,
     179,    21,    22,   131,   214,   216,    22,    89,   133,   159,
     141,   114,   115,   116,    23,   136,    24,   137,   150,   138,
      24,   160,   119,   120,    24,   181,   182,   183,   142,   161,
     162,   163,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   195,   140,    28,
     143,    29,   185,    30,    31,    32,   189,    33,    34,   168,
     169,   170,   171,   203,   204,   205,     1,     2,     3,     4,
       5,   125,   126,   184,   213,   187,   215,   191,   217,   146,
     147,   219,   199,   220,    90,   188,   147,   211,   206,   208,
     210,   164,   165,   218,    35,    36,   166,   167,   172,   173,
     175,   177,   202,    37,    38,    39,    40,    41,    42,   174,
     176,   178,   135,    26,   190,    25,    18,     0,    43,   157,
      28,   149,    29,     0,    30,    31,    32,     0,    33,    34,
       0,     0,     0,     0,     0,     0,     0,    28,     0,    29,
       0,    30,    31,    32,     0,    33,    34,     0,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,     0,     0,
       0,     0,     0,     0,     0,    35,    36,     0,     0,     0,
       0,     0,     0,     0,    37,    38,    39,    40,    41,    42,
     111,     0,    35,    36,     0,     0,     0,     0,     0,    43,
     207,    37,    38,    39,    40,    41,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    43,   209,    62,     0,
      29,     0,    30,    31,    32,     0,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     2,     3,
       4,     5,    63,    64,     0,    65,    66,    67,    68,    69,
      70,    71,    72,    35,    36,    73,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,    41,    42,     0,     0,
       0,     0,     0,     0,     0,    23,    74,    43,    62,     0,
      29,     0,    30,    31,    32,     0,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     2,     3,
       4,     5,    63,    64,     0,    65,    66,    67,    68,    69,
      70,    71,    72,    35,    36,    73,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,    41,    42,     0,     0,
       0,     0,     0,     0,     0,    23,   148,    43,    62,     0,
      29,     0,    30,    31,    32,     0,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,     0,    29,
       0,    30,    31,    32,     0,    33,    34,     0,     0,     0,
       0,     0,    63,    64,     0,    65,    66,    67,    68,    69,
      70,    71,    72,    35,    36,    73,     1,     2,     3,     4,
       5,     0,    37,    38,    39,    40,    41,    42,     0,     0,
       0,     0,    35,    36,    73,    23,     0,    43,     0,     0,
       0,    37,    38,    39,    40,    41,    42,     0,     0,    28,
       0,    29,     0,    30,    31,    32,    43,    33,    34,     0,
       0,     0,     0,     0,     0,    28,     0,    29,     0,    30,
      31,    32,     0,    33,    34,     0,     0,     0,     0,     0,
       0,    28,     0,    29,     0,    30,    31,    32,     0,    33,
      34,     0,     0,     0,    35,    36,     0,     0,     0,     0,
       0,    60,     0,    37,    38,    39,    40,    41,    42,     0,
      35,    36,   144,     0,     0,     0,     0,     0,    43,    37,
      38,    39,    40,    41,    42,     0,    35,    36,    73,     0,
       0,     0,     0,     0,    43,    37,    38,    39,    40,    41,
      42,     0,     0,    28,     0,    29,     0,    30,    31,    32,
      43,    33,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,    36,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,    41,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    43
};

static const yytype_int16 yycheck[] =
{
      21,    22,    43,     0,    67,    23,     8,     3,    11,    12,
      15,    16,     9,    20,     3,     3,    50,    51,    33,    34,
     140,    51,    51,     0,    51,    51,    51,    24,    51,    57,
      55,    72,    47,    68,    51,    51,    32,    33,    34,    35,
      36,    51,    55,    73,    73,    52,    73,    73,    63,    19,
      73,    54,    51,    51,    60,    61,    73,    73,    99,    67,
      65,    66,    50,    73,    82,   185,   186,    53,    54,    72,
     133,    53,    54,    20,    73,    73,    54,    73,    52,   100,
       3,    62,    63,    64,    70,    72,    72,    72,    90,    72,
      72,   112,    13,    14,    72,   136,   137,   138,    50,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   180,    72,     3,
      50,     5,   140,     7,     8,     9,   147,    11,    12,   121,
     122,   123,   124,   196,   197,   198,    32,    33,    34,    35,
      36,    17,    18,    41,   207,    50,   209,     3,   211,    50,
      51,   214,    72,   216,   151,    50,    51,    39,   199,   200,
     201,   117,   118,    50,    48,    49,   119,   120,   125,   126,
     128,   130,   193,    57,    58,    59,    60,    61,    62,   127,
     129,   131,    63,    20,   151,    17,     9,    -1,    72,    73,
       3,    82,     5,    -1,     7,     8,     9,    -1,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,
      -1,     7,     8,     9,    -1,    11,    12,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,    62,
      53,    -1,    48,    49,    -1,    -1,    -1,    -1,    -1,    72,
      73,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,     3,    -1,
       5,    -1,     7,     8,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    -1,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,     3,    -1,
       5,    -1,     7,     8,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    -1,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,     3,    -1,
       5,    -1,     7,     8,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,
      -1,     7,     8,     9,    -1,    11,    12,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    32,    33,    34,    35,
      36,    -1,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    48,    49,    50,    70,    -1,    72,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    62,    -1,    -1,     3,
      -1,     5,    -1,     7,     8,     9,    72,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,     5,    -1,     7,
       8,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,     5,    -1,     7,     8,     9,    -1,    11,
      12,    -1,    -1,    -1,    48,    49,    -1,    -1,    -1,    -1,
      -1,    55,    -1,    57,    58,    59,    60,    61,    62,    -1,
      48,    49,    50,    -1,    -1,    -1,    -1,    -1,    72,    57,
      58,    59,    60,    61,    62,    -1,    48,    49,    50,    -1,
      -1,    -1,    -1,    -1,    72,    57,    58,    59,    60,    61,
      62,    -1,    -1,     3,    -1,     5,    -1,     7,     8,     9,
      72,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    32,    33,    34,    35,    36,    76,    95,    98,   113,
     114,   115,     0,     3,    50,    96,    97,    99,   114,    50,
      51,    53,    54,    70,    72,   106,    97,    99,     3,     5,
       7,     8,     9,    11,    12,    48,    49,    57,    58,    59,
      60,    61,    62,    72,    77,    78,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,   103,
      55,    92,     3,    37,    38,    40,    41,    42,    43,    44,
      45,    46,    47,    50,    71,    92,    94,    95,    98,   104,
     105,   106,   107,   108,   109,   110,   111,   112,     3,    73,
      98,   100,   101,   102,    80,    80,    94,    11,    12,    54,
      72,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    53,    93,    80,    62,    63,    64,    60,    61,    13,
      14,    15,    16,    65,    66,    17,    18,    57,    67,    68,
      19,    20,    55,    52,    80,    91,    72,    72,    72,   104,
      72,     3,    50,    50,    50,    94,    50,    51,    71,   108,
      99,    51,    73,    51,    73,    73,    94,    73,    79,    92,
      92,    80,    80,    80,    82,    82,    83,    83,    84,    84,
      84,    84,    85,    85,    86,    87,    88,    89,    90,   104,
      52,    94,    94,    94,    41,    95,   109,    50,    50,    92,
     101,     3,    55,    51,    73,   104,    73,    73,    73,    72,
     109,   109,    92,   104,   104,   104,    94,    73,    94,    73,
      94,    39,    73,   104,    73,   104,    73,   104,    50,   104,
     104
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 59 ".\\parser.y"
    {
		root = new treeNode("Program",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 66 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("primary_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 70 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("primary_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 74 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("primary_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 77 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("primary_expression",1,(yyvsp[(1) - (1)].tN));
		
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 81 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("primary_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 84 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("primary_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 87 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("primary_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 90 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("primary_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 97 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("postfix_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 100 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("postfix_expression",4,(yyvsp[(1) - (4)].tN),(yyvsp[(2) - (4)].tN),(yyvsp[(3) - (4)].tN),(yyvsp[(4) - (4)].tN));
		//数组调用
	;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 104 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("postfix_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
		//函数调用
	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 108 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("postfix_expression",4,(yyvsp[(1) - (4)].tN),(yyvsp[(2) - (4)].tN),(yyvsp[(3) - (4)].tN),(yyvsp[(4) - (4)].tN));
		//函数调用
	;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 112 ".\\parser.y"
    {
		//++
		(yyval.tN) = new treeNode("postfix_expression",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 116 ".\\parser.y"
    {
		//--
		(yyval.tN) = new treeNode("postfix_expression",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 123 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("argument_expression_list",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 126 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("argument_expression_list",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 133 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("unary_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 136 ".\\parser.y"
    {
		//++
		(yyval.tN) = new treeNode("unary_expression",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 140 ".\\parser.y"
    {
		//--
		(yyval.tN) = new treeNode("unary_expression",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 144 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("unary_expression",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 151 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("unary_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 154 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("unary_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 157 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("unary_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 160 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("unary_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 163 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("unaru_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 166 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("unaru_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 173 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("multiplicative_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 176 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("multiplicative_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 179 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("multiplicative_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 182 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("multiplicative_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 189 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("additive_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 192 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("additive_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 195 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("additive_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 202 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("shift_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 205 ".\\parser.y"
    {
		//<<
		(yyval.tN) = new treeNode("shift_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 209 ".\\parser.y"
    {
		//<<
		(yyval.tN) = new treeNode("shift_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 217 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("relational_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 220 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("relational_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 223 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("relational_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 226 ".\\parser.y"
    {
		// <= 
		(yyval.tN) = new treeNode("relational_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 230 ".\\parser.y"
    {
		// >=
		(yyval.tN) = new treeNode("relational_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 238 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("equality_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 241 ".\\parser.y"
    {
		// ==
		(yyval.tN) = new treeNode("equality_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 245 ".\\parser.y"
    {
		// !=
		(yyval.tN) = new treeNode("equality_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 252 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("and_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 255 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("and_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 262 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("exclusive_or_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 265 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("exclusive_or_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 272 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("inclusive_or_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 275 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("inclusive_or_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 282 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("logical_and_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 285 ".\\parser.y"
    {
		//&&
		(yyval.tN) = new treeNode("logical_and_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 293 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("logical_or_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 296 ".\\parser.y"
    {
		//||
		(yyval.tN) = new treeNode("logical_or_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 304 ".\\parser.y"
    {
		//条件表达式
		(yyval.tN) = new treeNode("assignment_expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 308 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("assignment_expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 315 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("assignment_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 318 ".\\parser.y"
    {
		//*=
		(yyval.tN) = new treeNode("assignment_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 322 ".\\parser.y"
    {
		// /=
		(yyval.tN) = new treeNode("assignment_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 326 ".\\parser.y"
    {
		// %=
		(yyval.tN) = new treeNode("assignment_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 330 ".\\parser.y"
    {
		// += 
		(yyval.tN) = new treeNode("assignment_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 334 ".\\parser.y"
    {
		// -=
		(yyval.tN) = new treeNode("assignment_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 338 ".\\parser.y"
    {
		// <<=
		(yyval.tN) = new treeNode("assignment_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 342 ".\\parser.y"
    {
		// >>=
		(yyval.tN) = new treeNode("assignment_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 346 ".\\parser.y"
    {
		// &=
		(yyval.tN) = new treeNode("assignment_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 350 ".\\parser.y"
    {
		// ^=
		(yyval.tN) = new treeNode("assignment_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 354 ".\\parser.y"
    {
		// |=
		(yyval.tN) = new treeNode("assignment_operator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 362 ".\\parser.y"
    {
		//赋值表达式
		(yyval.tN) = new treeNode("expression",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 366 ".\\parser.y"
    {
		//逗号表达式
		(yyval.tN) = new treeNode("expression",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 374 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("declaration",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN)); //?
	;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 377 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("declaration",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 384 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("init_declarator_list",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 387 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("init_declarator_list",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 393 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("init_declarator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 396 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("init_declarator",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 404 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("type_specifier",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 407 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("type_specifier",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 410 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("type_specifier",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 413 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("type_specifier",1,(yyvsp[(1) - (1)].tN));	
	;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 416 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("type_specifier",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 424 ".\\parser.y"
    {
		//变量
		(yyval.tN) = new treeNode("declarator",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 432 ".\\parser.y"
    {
		//数组
		//printf("assignment_expression");
		(yyval.tN) = new treeNode("declarator",4,(yyvsp[(1) - (4)].tN),(yyvsp[(2) - (4)].tN),(yyvsp[(3) - (4)].tN),(yyvsp[(4) - (4)].tN));
	;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 441 ".\\parser.y"
    {
		//数组
		(yyval.tN) = new treeNode("declarator",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 445 ".\\parser.y"
    {
		//函数
		(yyval.tN) = new treeNode("declarator",4,(yyvsp[(1) - (4)].tN),(yyvsp[(2) - (4)].tN),(yyvsp[(3) - (4)].tN),(yyvsp[(4) - (4)].tN));
	;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 449 ".\\parser.y"
    {
		//函数
		(yyval.tN) = new treeNode("declarator",4,(yyvsp[(1) - (4)].tN),(yyvsp[(2) - (4)].tN),(yyvsp[(3) - (4)].tN),(yyvsp[(4) - (4)].tN));
	;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 453 ".\\parser.y"
    {
		//函数
		(yyval.tN) = new treeNode("declarator",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 462 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("parameter_list",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 465 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("parameter_list",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 471 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("parameter_declaration",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 477 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("parameter_declaration",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 483 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("identifier_list",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 486 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("identifier_list",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 529 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("initializer",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 583 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("statement",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 586 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("statement",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 589 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("statement",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 592 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("statement",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 595 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("statement",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 598 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("statement",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 605 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("labeled_statement",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 608 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("labeled_statement",4,(yyvsp[(1) - (4)].tN),(yyvsp[(2) - (4)].tN),(yyvsp[(3) - (4)].tN),(yyvsp[(4) - (4)].tN));
	;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 615 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("compound_statement",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 618 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("compound_statement",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 624 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("block_item_list",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 627 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("block_item_list",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 633 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("block_item",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 636 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("block_item",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 642 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("expression_statement",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 645 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("expression_statement",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 652 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("selection_statement",5,(yyvsp[(1) - (5)].tN),(yyvsp[(2) - (5)].tN),(yyvsp[(3) - (5)].tN),(yyvsp[(4) - (5)].tN),(yyvsp[(5) - (5)].tN));
	;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 655 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("selection_statement",7,(yyvsp[(1) - (7)].tN),(yyvsp[(2) - (7)].tN),(yyvsp[(3) - (7)].tN),(yyvsp[(4) - (7)].tN),(yyvsp[(5) - (7)].tN),(yyvsp[(6) - (7)].tN),(yyvsp[(7) - (7)].tN));
	;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 658 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("selection_statement",5,(yyvsp[(1) - (5)].tN),(yyvsp[(2) - (5)].tN),(yyvsp[(3) - (5)].tN),(yyvsp[(4) - (5)].tN),(yyvsp[(5) - (5)].tN));
	;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 665 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("iteration_statement",5,(yyvsp[(1) - (5)].tN),(yyvsp[(2) - (5)].tN),(yyvsp[(3) - (5)].tN),(yyvsp[(4) - (5)].tN),(yyvsp[(5) - (5)].tN));
	;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 668 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("iteration_statement",7,(yyvsp[(1) - (7)].tN),(yyvsp[(2) - (7)].tN),(yyvsp[(3) - (7)].tN),(yyvsp[(4) - (7)].tN),(yyvsp[(5) - (7)].tN),(yyvsp[(6) - (7)].tN),(yyvsp[(7) - (7)].tN));
	;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 671 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("iteration_statement",6,(yyvsp[(1) - (6)].tN),(yyvsp[(2) - (6)].tN),(yyvsp[(3) - (6)].tN),(yyvsp[(4) - (6)].tN),(yyvsp[(5) - (6)].tN),(yyvsp[(6) - (6)].tN));
	;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 674 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("iteration_statement",7,(yyvsp[(1) - (7)].tN),(yyvsp[(2) - (7)].tN),(yyvsp[(3) - (7)].tN),(yyvsp[(4) - (7)].tN),(yyvsp[(5) - (7)].tN),(yyvsp[(6) - (7)].tN),(yyvsp[(7) - (7)].tN));
	;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 677 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("iteration_statement",6,(yyvsp[(1) - (6)].tN),(yyvsp[(2) - (6)].tN),(yyvsp[(3) - (6)].tN),(yyvsp[(4) - (6)].tN),(yyvsp[(5) - (6)].tN),(yyvsp[(6) - (6)].tN));
	;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 680 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("iteration_statement",7,(yyvsp[(1) - (7)].tN),(yyvsp[(2) - (7)].tN),(yyvsp[(3) - (7)].tN),(yyvsp[(4) - (7)].tN),(yyvsp[(5) - (7)].tN),(yyvsp[(6) - (7)].tN),(yyvsp[(7) - (7)].tN));
	;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 687 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("jump_statement",2,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN));
	;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 690 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("jump_statement",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 693 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("jump_statement",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 696 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("jump_statement",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 699 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("jump_statement",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 705 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("translation_unit",1,(yyvsp[(1) - (1)].tN));
	;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 708 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("translation_unit",2,(yyvsp[(1) - (2)].tN),(yyvsp[(2) - (2)].tN));
	;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 714 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("external_declaration",1,(yyvsp[(1) - (1)].tN));
		//函数定义
	;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 718 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("external_declaration",1,(yyvsp[(1) - (1)].tN));
		//变量声明
	;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 728 ".\\parser.y"
    {
		(yyval.tN) = new treeNode("function_definition",3,(yyvsp[(1) - (3)].tN),(yyvsp[(2) - (3)].tN),(yyvsp[(3) - (3)].tN));
	;}
    break;



/* Line 1455 of yacc.c  */
#line 2906 "parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 742 ".\\parser.y"


void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}

int main(int argc,char* argv[]) {
	yyin = fopen(argv[1],"r");
	
	yyparse();
	printf("\n");
	ofstream treeOs;
	treeOs.open("test/tree.txt");
	root->printTree(0, treeOs);

	translator *t = new translator(root);

	ofstream innerCodeOs;
	innerCodeOs.open("test/innerCode.txt");
	t->innerCode.printCode(innerCodeOs);

	/* freeGramTree(root); */

	fclose(yyin);
	return 0;
}
