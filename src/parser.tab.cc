/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 3 "parser.yy"

	#include <iostream>
	#include <fstream>
	#include <filesystem>
	#include <string>
	#include "../src/astNodes.h"

	extern int yylex();
	extern void yyrestart(FILE*);
	void yyerror(const char* s);
	extern int yylineno;

	#define YYFPRINTF(f, fmt, ...)  printf(fmt, ##__VA_ARGS__)
	#if YYDEBUG == 1
	#define PARSER_TRACE_DEBUG
	#define SYMBOL_TABLE_DEBUG
	#define AST_DEBUG
	#endif

#line 88 "parser.tab.cc"




# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hh"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONST = 3,                      /* CONST  */
  YYSYMBOL_VAR = 4,                        /* VAR  */
  YYSYMBOL_BOOL = 5,                       /* BOOL  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_STRING = 8,                     /* STRING  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_POINT = 10,                     /* POINT  */
  YYSYMBOL_PATH = 11,                      /* PATH  */
  YYSYMBOL_IMAGE = 12,                     /* IMAGE  */
  YYSYMBOL_RECTANGLE = 13,                 /* RECTANGLE  */
  YYSYMBOL_CIRCLE = 14,                    /* CIRCLE  */
  YYSYMBOL_ELLIPSE = 15,                   /* ELLIPSE  */
  YYSYMBOL_POLYGON = 16,                   /* POLYGON  */
  YYSYMBOL_CURVE = 17,                     /* CURVE  */
  YYSYMBOL_PI = 18,                        /* PI  */
  YYSYMBOL_COLOUR = 19,                    /* COLOUR  */
  YYSYMBOL_INTEGER_LITERAL = 20,           /* INTEGER_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 21,             /* FLOAT_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 22,              /* BOOL_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 23,            /* STRING_LITERAL  */
  YYSYMBOL_IF = 24,                        /* IF  */
  YYSYMBOL_ELSE = 25,                      /* ELSE  */
  YYSYMBOL_SWITCH = 26,                    /* SWITCH  */
  YYSYMBOL_CASE = 27,                      /* CASE  */
  YYSYMBOL_DEFAULT = 28,                   /* DEFAULT  */
  YYSYMBOL_WHILE = 29,                     /* WHILE  */
  YYSYMBOL_FOR = 30,                       /* FOR  */
  YYSYMBOL_BREAK = 31,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 32,                  /* CONTINUE  */
  YYSYMBOL_SEND = 33,                      /* SEND  */
  YYSYMBOL_FAMILY = 34,                    /* FAMILY  */
  YYSYMBOL_INHERITS = 35,                  /* INHERITS  */
  YYSYMBOL_PUBLIC = 36,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 37,                   /* PRIVATE  */
  YYSYMBOL_DRIVER = 38,                    /* DRIVER  */
  YYSYMBOL_IDENTIFIER = 39,                /* IDENTIFIER  */
  YYSYMBOL_ASSIGN = 40,                    /* ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 41,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 42,                /* SUB_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 43,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 44,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 45,                /* MOD_ASSIGN  */
  YYSYMBOL_LOGICAL_OR = 46,                /* LOGICAL_OR  */
  YYSYMBOL_LOGICAL_AND = 47,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_NOT = 48,               /* LOGICAL_NOT  */
  YYSYMBOL_EQ = 49,                        /* EQ  */
  YYSYMBOL_NOT_EQ = 50,                    /* NOT_EQ  */
  YYSYMBOL_LS_THAN = 51,                   /* LS_THAN  */
  YYSYMBOL_LS_THAN_EQ = 52,                /* LS_THAN_EQ  */
  YYSYMBOL_GR_THAN = 53,                   /* GR_THAN  */
  YYSYMBOL_GR_THAN_EQ = 54,                /* GR_THAN_EQ  */
  YYSYMBOL_INC = 55,                       /* INC  */
  YYSYMBOL_DEC = 56,                       /* DEC  */
  YYSYMBOL_INC_POST = 57,                  /* INC_POST  */
  YYSYMBOL_DEC_POST = 58,                  /* DEC_POST  */
  YYSYMBOL_SCOPE_ACCESS = 59,              /* SCOPE_ACCESS  */
  YYSYMBOL_60_ = 60,                       /* ','  */
  YYSYMBOL_61_ = 61,                       /* '?'  */
  YYSYMBOL_62_ = 62,                       /* ':'  */
  YYSYMBOL_63_ = 63,                       /* '+'  */
  YYSYMBOL_64_ = 64,                       /* '-'  */
  YYSYMBOL_65_ = 65,                       /* '*'  */
  YYSYMBOL_66_ = 66,                       /* '/'  */
  YYSYMBOL_67_ = 67,                       /* '%'  */
  YYSYMBOL_UPLUS = 68,                     /* UPLUS  */
  YYSYMBOL_UMINUS = 69,                    /* UMINUS  */
  YYSYMBOL_70_ = 70,                       /* '('  */
  YYSYMBOL_71_ = 71,                       /* ')'  */
  YYSYMBOL_72_ = 72,                       /* '['  */
  YYSYMBOL_73_ = 73,                       /* ']'  */
  YYSYMBOL_74_ = 74,                       /* ';'  */
  YYSYMBOL_75_ = 75,                       /* '{'  */
  YYSYMBOL_76_ = 76,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 77,                  /* $accept  */
  YYSYMBOL_program = 78,                   /* program  */
  YYSYMBOL_translation_unit = 79,          /* translation_unit  */
  YYSYMBOL_external_declaration = 80,      /* external_declaration  */
  YYSYMBOL_driver_definition = 81,         /* driver_definition  */
  YYSYMBOL_82_1 = 82,                      /* $@1  */
  YYSYMBOL_type = 83,                      /* type  */
  YYSYMBOL_literal = 84,                   /* literal  */
  YYSYMBOL_variable_declaration = 85,      /* variable_declaration  */
  YYSYMBOL_86_2 = 86,                      /* $@2  */
  YYSYMBOL_87_3 = 87,                      /* $@3  */
  YYSYMBOL_new_variable_list = 88,         /* new_variable_list  */
  YYSYMBOL_new_variable = 89,              /* new_variable  */
  YYSYMBOL_function_declaration = 90,      /* function_declaration  */
  YYSYMBOL_91_4 = 91,                      /* $@4  */
  YYSYMBOL_92_5 = 92,                      /* $@5  */
  YYSYMBOL_93_6 = 93,                      /* $@6  */
  YYSYMBOL_args_list = 94,                 /* args_list  */
  YYSYMBOL_arg = 95,                       /* arg  */
  YYSYMBOL_family_declaration = 96,        /* family_declaration  */
  YYSYMBOL_97_7 = 97,                      /* $@7  */
  YYSYMBOL_98_8 = 98,                      /* $@8  */
  YYSYMBOL_access_specifier = 99,          /* access_specifier  */
  YYSYMBOL_class_members = 100,            /* class_members  */
  YYSYMBOL_class_member = 101,             /* class_member  */
  YYSYMBOL_constructor_declaration = 102,  /* constructor_declaration  */
  YYSYMBOL_103_9 = 103,                    /* $@9  */
  YYSYMBOL_104_10 = 104,                   /* $@10  */
  YYSYMBOL_primary_expression = 105,       /* primary_expression  */
  YYSYMBOL_variable = 106,                 /* variable  */
  YYSYMBOL_expression = 107,               /* expression  */
  YYSYMBOL_expression_list = 108,          /* expression_list  */
  YYSYMBOL_statement = 109,                /* statement  */
  YYSYMBOL_compound_statement = 110,       /* compound_statement  */
  YYSYMBOL_111_11 = 111,                   /* $@11  */
  YYSYMBOL_statement_list = 112,           /* statement_list  */
  YYSYMBOL_expression_statement = 113,     /* expression_statement  */
  YYSYMBOL_selection_statement = 114,      /* selection_statement  */
  YYSYMBOL_labeled_statement = 115,        /* labeled_statement  */
  YYSYMBOL_iteration_statement = 116,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 117            /* jump_statement  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 41 "parser.yy"

	#include "../src/symbolTable.h"

	SymbolTable global_symbol_table(NULL, "global");
	SymbolTable* cur_symbol_table = &global_symbol_table;
	Program* root;

#line 251 "parser.tab.cc"

#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  33
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   810

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  135
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  254

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   316


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    67,     2,     2,
      70,    71,    65,    63,    60,    64,     2,    66,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,    74,
       2,     2,     2,    61,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,     2,    73,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,     2,    76,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    68,    69
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   140,   140,   141,   145,   146,   150,   151,   152,   153,
     157,   157,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   185,   186,
     187,   188,   192,   192,   194,   194,   199,   200,   204,   209,
     215,   221,   231,   230,   241,   245,   240,   259,   260,   264,
     269,   274,   285,   291,   290,   299,   306,   305,   318,   319,
     323,   324,   328,   329,   330,   335,   339,   334,   355,   356,
     357,   358,   359,   363,   364,   365,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   400,   401,   408,   409,   410,   411,
     412,   413,   414,   415,   419,   420,   420,   426,   427,   431,
     432,   436,   437,   438,   442,   443,   444,   448,   449,   450,
     451,   452,   453,   457,   458,   459
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CONST", "VAR", "BOOL",
  "FLOAT", "INT", "STRING", "VOID", "POINT", "PATH", "IMAGE", "RECTANGLE",
  "CIRCLE", "ELLIPSE", "POLYGON", "CURVE", "PI", "COLOUR",
  "INTEGER_LITERAL", "FLOAT_LITERAL", "BOOL_LITERAL", "STRING_LITERAL",
  "IF", "ELSE", "SWITCH", "CASE", "DEFAULT", "WHILE", "FOR", "BREAK",
  "CONTINUE", "SEND", "FAMILY", "INHERITS", "PUBLIC", "PRIVATE", "DRIVER",
  "IDENTIFIER", "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "LOGICAL_OR", "LOGICAL_AND", "LOGICAL_NOT",
  "EQ", "NOT_EQ", "LS_THAN", "LS_THAN_EQ", "GR_THAN", "GR_THAN_EQ", "INC",
  "DEC", "INC_POST", "DEC_POST", "SCOPE_ACCESS", "','", "'?'", "':'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "UPLUS", "UMINUS", "'('", "')'",
  "'['", "']'", "';'", "'{'", "'}'", "$accept", "program",
  "translation_unit", "external_declaration", "driver_definition", "$@1",
  "type", "literal", "variable_declaration", "$@2", "$@3",
  "new_variable_list", "new_variable", "function_declaration", "$@4",
  "$@5", "$@6", "args_list", "arg", "family_declaration", "$@7", "$@8",
  "access_specifier", "class_members", "class_member",
  "constructor_declaration", "$@9", "$@10", "primary_expression",
  "variable", "expression", "expression_list", "statement",
  "compound_statement", "$@11", "statement_list", "expression_statement",
  "selection_statement", "labeled_statement", "iteration_statement",
  "jump_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-134)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-43)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     421,   493,   493,  -134,  -134,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,   -31,  -134,
    -134,    27,   421,  -134,  -134,    10,  -134,  -134,  -134,  -134,
    -134,   -29,   -19,  -134,  -134,   -15,    34,    34,    -5,    20,
      28,    30,   -27,   -53,  -134,   -45,  -134,  -134,    64,    43,
      21,    51,    47,   458,   353,   255,    34,  -134,  -134,    60,
    -134,    66,   475,   -20,  -134,  -134,    61,  -134,    51,   493,
     493,   100,   -46,  -134,  -134,  -134,  -134,  -134,  -134,   353,
     102,   102,   353,   353,   353,  -134,  -134,   478,   699,  -134,
     699,   -24,  -134,    68,  -134,  -134,  -134,    72,  -134,  -134,
     198,  -134,   103,   106,  -134,   458,  -134,  -134,   -33,   -33,
    -134,  -134,   517,   353,   353,   353,   353,   353,   353,  -134,
    -134,   109,   265,   353,   353,   353,   353,   353,   353,   353,
     353,   353,   353,   353,   353,   353,   353,   353,   353,  -134,
      76,    21,   458,  -134,    79,    84,    88,   353,    97,    90,
      91,    89,    92,   -11,   107,  -134,  -134,   -36,  -134,  -134,
     101,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,    51,
    -134,   699,   699,   699,   699,   699,   699,  -134,  -134,   -10,
     492,   720,   726,   743,   743,    49,    49,    49,    49,   655,
     -25,   -25,  -134,  -134,  -134,   699,  -134,    71,    40,  -134,
     353,   353,   677,   198,   294,   235,  -134,  -134,  -134,   198,
    -134,  -134,  -134,  -134,  -134,  -134,   353,    94,  -134,   540,
     563,   198,  -134,    51,   586,   -11,   -11,  -134,   699,  -134,
      51,    51,   198,  -134,  -134,    51,   323,   333,  -134,   137,
    -134,  -134,    51,   609,    51,   632,    51,  -134,    51,  -134,
      51,  -134,  -134,  -134
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,    15,    13,    12,    14,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,     0,    10,
      27,     0,     3,     4,     6,     0,     7,     8,     9,    34,
      32,     0,     0,     1,     5,     0,     0,     0,     0,    53,
       0,    44,    38,     0,    36,     0,    58,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    33,     0,
      52,     0,     0,     0,    60,    64,   115,    11,     0,     0,
       0,     0,     0,    47,    28,    29,    31,    30,    73,     0,
       0,     0,     0,     0,     0,    68,    76,    69,    39,    40,
     104,     0,    37,    56,    65,    62,    63,     0,    61,   114,
       0,    43,     0,     0,    49,     0,    45,    92,    93,    94,
      77,    78,     0,     0,     0,     0,     0,     0,     0,    95,
      96,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    41,
       0,     0,     0,    54,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    73,   119,   108,     0,   117,   107,
       0,   109,   110,   106,   111,   112,    51,    50,    48,     0,
      72,    97,   101,   102,    98,    99,   100,    74,    70,     0,
       0,    91,    90,    84,    85,    86,    87,    88,    89,     0,
      82,    83,    79,    80,    81,   105,    55,     0,     0,   113,
       0,     0,     0,     0,     0,     0,   134,   133,   135,     0,
     120,   116,   118,    46,    71,    75,     0,     0,    66,     0,
       0,     0,   126,     0,     0,     0,     0,   124,   103,    57,
       0,     0,     0,   125,   127,     0,     0,     0,    67,   121,
     123,   128,     0,     0,     0,     0,     0,   131,     0,   129,
       0,   122,   132,   130
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -134,  -134,  -134,   148,  -134,  -134,     1,  -134,     0,  -134,
    -134,   135,   118,   116,  -134,  -134,  -134,    37,    77,  -134,
    -134,  -134,   145,    45,   -59,  -134,  -134,  -134,  -134,    14,
     -49,   -32,  -112,   -50,  -134,  -134,  -133,  -134,  -134,  -134,
    -134
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    21,    22,    23,    24,    32,    25,    85,   156,    37,
      36,    43,    44,    27,    52,    53,   169,    72,    73,    28,
      50,   141,    62,    63,    64,    65,   142,   230,    86,    87,
      90,   157,   158,   159,   100,   160,   161,   162,   163,   164,
     165
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,    67,    29,    30,    98,    88,    38,    56,    31,    74,
      75,    76,    77,    54,   105,    56,    46,    47,   101,    61,
     208,    57,    26,    91,   138,   106,   121,    33,    78,    58,
     107,    46,    47,   110,   111,   112,   138,    79,   210,   123,
     135,   136,   137,    55,    80,    81,    39,   139,   212,    35,
     138,    40,    82,    83,    71,    41,    97,    46,    47,    84,
      61,   214,    95,   155,   171,   172,   173,   174,   175,   176,
     102,   103,   226,    42,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     179,   222,   236,   237,   108,   109,    49,   227,   202,    51,
     105,   -42,   144,    59,     1,     2,    71,    46,    47,   233,
      61,   218,   133,   134,   135,   136,   137,    60,    68,   213,
     240,    74,    75,    76,    77,   145,    66,   146,   147,   148,
     149,   150,   151,   152,   153,    93,    94,    99,    98,   104,
     154,    78,   166,    71,   140,   167,   143,   217,   177,    79,
     196,   219,   220,   199,   200,   224,    80,    81,   201,   203,
     204,   205,   246,   206,    82,    83,   207,   228,   229,   209,
      34,    84,    45,   234,    92,   155,    66,   211,    96,   198,
     238,   239,   168,    48,     0,   241,   197,   243,   245,     0,
       0,     0,   247,     0,   249,     0,   251,     0,   252,   144,
     253,     1,     2,     0,     0,   225,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    74,    75,
      76,    77,   145,     0,   146,   147,   148,   149,   150,   151,
     152,   153,     0,     0,     0,     0,     0,   154,     1,     2,
       0,     0,     0,     0,     0,     0,    79,     0,     0,     0,
       0,     0,     0,    80,    81,    74,    75,    76,    77,     0,
       0,    82,    83,     0,     0,     0,     0,     0,    84,     0,
       0,     0,   155,    66,    78,    74,    75,    76,    77,     0,
       0,     0,     0,    79,     0,    74,    75,    76,    77,     0,
      80,    81,     0,     0,    78,     0,     0,     0,    82,    83,
       0,     0,     0,    79,    78,    84,     0,     0,     0,   155,
      80,    81,     0,    79,    74,    75,    76,    77,    82,    83,
      80,    81,     0,     0,     0,    84,    89,     0,    82,    83,
       0,     0,     0,    78,     0,    84,   178,     0,     0,     0,
       0,     0,    79,    74,    75,    76,    77,     0,     0,    80,
      81,     0,     0,    74,    75,    76,    77,    82,    83,     0,
       0,     0,    78,     0,    84,   223,     0,     0,     0,     0,
       0,    79,    78,    74,    75,    76,    77,     0,    80,    81,
       0,    79,     0,     0,     0,     0,    82,    83,    80,    81,
       0,     0,    78,    84,   242,     0,    82,    83,     0,     0,
       0,    79,     0,    84,   244,     0,     0,     0,    80,    81,
       0,     0,     0,     0,     0,     0,    82,    83,     0,     0,
       0,     0,     0,    84,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,     0,     0,     0,    19,
      20,    69,    70,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,     0,     0,    20,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,     0,    20,     0,     0,     0,   113,   114,
     115,   116,   117,   118,     0,     0,     0,     0,     0,     0,
       0,     0,    20,   119,   120,     0,     0,   121,   124,   125,
       0,   126,   127,   128,   129,   130,   131,     0,   122,     0,
     123,     0,     0,   132,     0,   133,   134,   135,   136,   137,
       0,     0,     0,   124,   125,   215,   126,   127,   128,   129,
     130,   131,     0,     0,     0,     0,     0,     0,   132,     0,
     133,   134,   135,   136,   137,     0,   124,   125,   170,   126,
     127,   128,   129,   130,   131,     0,     0,     0,     0,     0,
       0,   132,     0,   133,   134,   135,   136,   137,     0,   124,
     125,   231,   126,   127,   128,   129,   130,   131,     0,     0,
       0,     0,     0,     0,   132,     0,   133,   134,   135,   136,
     137,     0,   124,   125,   232,   126,   127,   128,   129,   130,
     131,     0,     0,     0,     0,     0,     0,   132,     0,   133,
     134,   135,   136,   137,     0,   124,   125,   235,   126,   127,
     128,   129,   130,   131,     0,     0,     0,     0,     0,     0,
     132,     0,   133,   134,   135,   136,   137,     0,   124,   125,
     248,   126,   127,   128,   129,   130,   131,     0,     0,     0,
       0,     0,     0,   132,     0,   133,   134,   135,   136,   137,
       0,   124,   125,   250,   126,   127,   128,   129,   130,   131,
       0,     0,     0,     0,     0,     0,   132,   216,   133,   134,
     135,   136,   137,   124,   125,     0,   126,   127,   128,   129,
     130,   131,     0,     0,     0,     0,     0,     0,   132,   221,
     133,   134,   135,   136,   137,   124,   125,     0,   126,   127,
     128,   129,   130,   131,     0,     0,     0,     0,     0,     0,
     132,     0,   133,   134,   135,   136,   137,   125,     0,   126,
     127,   128,   129,   130,   131,   126,   127,   128,   129,   130,
     131,     0,     0,   133,   134,   135,   136,   137,     0,   133,
     134,   135,   136,   137,   128,   129,   130,   131,     0,     0,
       0,     0,     0,     0,     0,     0,   133,   134,   135,   136,
     137
};

static const yytype_int16 yycheck[] =
{
       0,    51,     1,     2,    63,    54,    35,    60,    39,    20,
      21,    22,    23,    40,    60,    60,    36,    37,    68,    39,
     153,    74,    22,    55,    60,    71,    59,     0,    39,    74,
      79,    36,    37,    82,    83,    84,    60,    48,    74,    72,
      65,    66,    67,    70,    55,    56,    75,    71,   160,    39,
      60,    70,    63,    64,    53,    70,    76,    36,    37,    70,
      39,    71,    62,    74,   113,   114,   115,   116,   117,   118,
      69,    70,   205,    39,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     122,   203,   225,   226,    80,    81,    76,   209,   147,    71,
      60,    71,     1,    39,     3,     4,   105,    36,    37,   221,
      39,    71,    63,    64,    65,    66,    67,    74,    71,   169,
     232,    20,    21,    22,    23,    24,    75,    26,    27,    28,
      29,    30,    31,    32,    33,    75,    70,    76,   197,    39,
      39,    39,    39,   142,    76,    39,    74,    76,    39,    48,
      74,   200,   201,    74,    70,   204,    55,    56,    70,    62,
      70,    70,    25,    74,    63,    64,    74,   216,    74,    62,
      22,    70,    37,   223,    56,    74,    75,    76,    62,   142,
     230,   231,   105,    38,    -1,   235,   141,   236,   237,    -1,
      -1,    -1,   242,    -1,   244,    -1,   246,    -1,   248,     1,
     250,     3,     4,    -1,    -1,   205,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    39,     3,     4,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    20,    21,    22,    23,    -1,
      -1,    63,    64,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      -1,    -1,    74,    75,    39,    20,    21,    22,    23,    -1,
      -1,    -1,    -1,    48,    -1,    20,    21,    22,    23,    -1,
      55,    56,    -1,    -1,    39,    -1,    -1,    -1,    63,    64,
      -1,    -1,    -1,    48,    39,    70,    -1,    -1,    -1,    74,
      55,    56,    -1,    48,    20,    21,    22,    23,    63,    64,
      55,    56,    -1,    -1,    -1,    70,    71,    -1,    63,    64,
      -1,    -1,    -1,    39,    -1,    70,    71,    -1,    -1,    -1,
      -1,    -1,    48,    20,    21,    22,    23,    -1,    -1,    55,
      56,    -1,    -1,    20,    21,    22,    23,    63,    64,    -1,
      -1,    -1,    39,    -1,    70,    71,    -1,    -1,    -1,    -1,
      -1,    48,    39,    20,    21,    22,    23,    -1,    55,    56,
      -1,    48,    -1,    -1,    -1,    -1,    63,    64,    55,    56,
      -1,    -1,    39,    70,    71,    -1,    63,    64,    -1,    -1,
      -1,    48,    -1,    70,    71,    -1,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    -1,    -1,
      -1,    -1,    -1,    70,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    38,
      39,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    39,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    39,    -1,    -1,    -1,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    55,    56,    -1,    -1,    59,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    -1,    70,    -1,
      72,    -1,    -1,    61,    -1,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    46,    47,    73,    49,    50,    51,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,
      63,    64,    65,    66,    67,    -1,    46,    47,    71,    49,
      50,    51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    63,    64,    65,    66,    67,    -1,    46,
      47,    71,    49,    50,    51,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    63,    64,    65,    66,
      67,    -1,    46,    47,    71,    49,    50,    51,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    63,
      64,    65,    66,    67,    -1,    46,    47,    71,    49,    50,
      51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    -1,    63,    64,    65,    66,    67,    -1,    46,    47,
      71,    49,    50,    51,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    -1,    63,    64,    65,    66,    67,
      -1,    46,    47,    71,    49,    50,    51,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,
      65,    66,    67,    46,    47,    -1,    49,    50,    51,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      63,    64,    65,    66,    67,    46,    47,    -1,    49,    50,
      51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    -1,    63,    64,    65,    66,    67,    47,    -1,    49,
      50,    51,    52,    53,    54,    49,    50,    51,    52,    53,
      54,    -1,    -1,    63,    64,    65,    66,    67,    -1,    63,
      64,    65,    66,    67,    51,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,
      67
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    34,    38,
      39,    78,    79,    80,    81,    83,    85,    90,    96,    83,
      83,    39,    82,     0,    80,    39,    87,    86,    35,    75,
      70,    70,    39,    88,    89,    88,    36,    37,    99,    76,
      97,    71,    91,    92,    40,    70,    60,    74,    74,    39,
      74,    39,    99,   100,   101,   102,    75,   110,    71,     3,
       4,    83,    94,    95,    20,    21,    22,    23,    39,    48,
      55,    56,    63,    64,    70,    84,   105,   106,   107,    71,
     107,   108,    89,    75,    70,    85,    90,    76,   101,    76,
     111,   110,    83,    83,    39,    60,    71,   107,   106,   106,
     107,   107,   107,    40,    41,    42,    43,    44,    45,    55,
      56,    59,    70,    72,    46,    47,    49,    50,    51,    52,
      53,    54,    61,    63,    64,    65,    66,    67,    60,    71,
      76,    98,   103,    74,     1,    24,    26,    27,    28,    29,
      30,    31,    32,    33,    39,    74,    85,   108,   109,   110,
     112,   113,   114,   115,   116,   117,    39,    39,    95,    93,
      71,   107,   107,   107,   107,   107,   107,    39,    71,   108,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,    74,   100,    94,    74,
      70,    70,   107,    62,    70,    70,    74,    74,   113,    62,
      74,    76,   109,   110,    71,    73,    62,    76,    71,   107,
     107,    62,   109,    71,   107,    85,   113,   109,   107,    74,
     104,    71,    71,   109,   110,    71,   113,   113,   110,   110,
     109,   110,    71,   107,    71,   107,    25,   110,    71,   110,
      71,   110,   110,   110
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    77,    78,    78,    79,    79,    80,    80,    80,    80,
      82,    81,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    84,    84,
      84,    84,    86,    85,    87,    85,    88,    88,    89,    89,
      89,    89,    91,    90,    92,    93,    90,    94,    94,    95,
      95,    95,    96,    97,    96,    96,    98,    96,    99,    99,
     100,   100,   101,   101,   101,   103,   104,   102,   105,   105,
     105,   105,   105,   106,   106,   106,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   108,   108,   109,   109,   109,   109,
     109,   109,   109,   109,   110,   111,   110,   112,   112,   113,
     113,   114,   114,   114,   115,   115,   115,   116,   116,   116,
     116,   116,   116,   117,   117,   117
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     1,     1,     1,
       0,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     5,     0,     5,     1,     3,     1,     3,
       3,     4,     0,     6,     0,     0,     8,     1,     3,     2,
       3,     3,     5,     0,     7,     8,     0,    10,     1,     1,
       1,     2,     2,     2,     1,     0,     0,     7,     1,     1,
       3,     4,     3,     1,     3,     4,     1,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     5,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     0,     4,     1,     2,     1,
       2,     5,     7,     5,     3,     4,     3,     4,     5,     6,
       7,     6,     7,     2,     2,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: %empty  */
#line 140 "parser.yy"
                                                {(yyval.pgm) = new Program(); root = (yyval.pgm);}
#line 1617 "parser.tab.cc"
    break;

  case 3: /* program: translation_unit  */
#line 141 "parser.yy"
                                        {(yyval.pgm) = new Program((yyvsp[0].stmt_list)); root = (yyval.pgm);}
#line 1623 "parser.tab.cc"
    break;

  case 4: /* translation_unit: external_declaration  */
#line 145 "parser.yy"
                                                                {(yyval.stmt_list) = new list <Statement*>(); (yyval.stmt_list)->push_back((yyvsp[0].stmt));}
#line 1629 "parser.tab.cc"
    break;

  case 5: /* translation_unit: translation_unit external_declaration  */
#line 146 "parser.yy"
                                                {(yyval.stmt_list) = (yyvsp[-1].stmt_list); (yyval.stmt_list)->push_back((yyvsp[0].stmt));}
#line 1635 "parser.tab.cc"
    break;

  case 6: /* external_declaration: driver_definition  */
#line 150 "parser.yy"
                                        {(yyval.stmt) = (yyvsp[0].stmt);}
#line 1641 "parser.tab.cc"
    break;

  case 7: /* external_declaration: variable_declaration  */
#line 151 "parser.yy"
                                {(yyval.stmt) = (yyvsp[0].stmt);}
#line 1647 "parser.tab.cc"
    break;

  case 8: /* external_declaration: function_declaration  */
#line 152 "parser.yy"
                                {(yyval.stmt) = (yyvsp[0].stmt);}
#line 1653 "parser.tab.cc"
    break;

  case 9: /* external_declaration: family_declaration  */
#line 153 "parser.yy"
                                {(yyval.stmt) = (yyvsp[0].stmt);}
#line 1659 "parser.tab.cc"
    break;

  case 10: /* $@1: %empty  */
#line 157 "parser.yy"
                                                                        {cur_symbol_table = cur_symbol_table->addSymbol("driver", "void->()", &(yylsp[0]), KIND::FUNCTION);}
#line 1665 "parser.tab.cc"
    break;

  case 11: /* driver_definition: DRIVER $@1 '(' ')' compound_statement  */
#line 158 "parser.yy"
                                                        {(yyval.stmt) = new DriverDefinition((yyvsp[0].stmt)); cur_symbol_table = cur_symbol_table->returnFromFunction();}
#line 1671 "parser.tab.cc"
    break;

  case 12: /* type: INT  */
#line 166 "parser.yy"
                                {(yyval.t) = new Identifier("int");}
#line 1677 "parser.tab.cc"
    break;

  case 13: /* type: FLOAT  */
#line 167 "parser.yy"
                                {(yyval.t) = new Identifier("float");}
#line 1683 "parser.tab.cc"
    break;

  case 14: /* type: STRING  */
#line 168 "parser.yy"
                                {(yyval.t) = new Identifier("string");}
#line 1689 "parser.tab.cc"
    break;

  case 15: /* type: BOOL  */
#line 169 "parser.yy"
                                {(yyval.t) = new Identifier("bool");}
#line 1695 "parser.tab.cc"
    break;

  case 16: /* type: VOID  */
#line 170 "parser.yy"
                                {(yyval.t) = new Identifier("void");}
#line 1701 "parser.tab.cc"
    break;

  case 17: /* type: POINT  */
#line 171 "parser.yy"
                                {(yyval.t) = new Identifier("Point");}
#line 1707 "parser.tab.cc"
    break;

  case 18: /* type: PATH  */
#line 172 "parser.yy"
                                {(yyval.t) = new Identifier("Path");}
#line 1713 "parser.tab.cc"
    break;

  case 19: /* type: IMAGE  */
#line 173 "parser.yy"
                                {(yyval.t) = new Identifier("Image");}
#line 1719 "parser.tab.cc"
    break;

  case 20: /* type: RECTANGLE  */
#line 174 "parser.yy"
                        {(yyval.t) = new Identifier("Rectangle");}
#line 1725 "parser.tab.cc"
    break;

  case 21: /* type: CIRCLE  */
#line 175 "parser.yy"
                                {(yyval.t) = new Identifier("Circle");}
#line 1731 "parser.tab.cc"
    break;

  case 22: /* type: ELLIPSE  */
#line 176 "parser.yy"
                                {(yyval.t) = new Identifier("Ellipse");}
#line 1737 "parser.tab.cc"
    break;

  case 23: /* type: POLYGON  */
#line 177 "parser.yy"
                                {(yyval.t) = new Identifier("Polygon");}
#line 1743 "parser.tab.cc"
    break;

  case 24: /* type: CURVE  */
#line 178 "parser.yy"
                                {(yyval.t) = new Identifier("Curve");}
#line 1749 "parser.tab.cc"
    break;

  case 25: /* type: PI  */
#line 179 "parser.yy"
                                {(yyval.t) = new Identifier("Pi");}
#line 1755 "parser.tab.cc"
    break;

  case 26: /* type: COLOUR  */
#line 180 "parser.yy"
                                {(yyval.t) = new Identifier("Colour");}
#line 1761 "parser.tab.cc"
    break;

  case 27: /* type: IDENTIFIER  */
#line 181 "parser.yy"
                        {(yyval.t) = new Identifier(*((yyvsp[0].id)));}
#line 1767 "parser.tab.cc"
    break;

  case 28: /* literal: INTEGER_LITERAL  */
#line 185 "parser.yy"
                                {(yyval.exp) = new IntegerLiteral((yyvsp[0].valuei));}
#line 1773 "parser.tab.cc"
    break;

  case 29: /* literal: FLOAT_LITERAL  */
#line 186 "parser.yy"
                                {(yyval.exp) = new FloatLiteral((yyvsp[0].valuef));}
#line 1779 "parser.tab.cc"
    break;

  case 30: /* literal: STRING_LITERAL  */
#line 187 "parser.yy"
                                {(yyval.exp) = new StringLiteral(*((yyvsp[0].values)));}
#line 1785 "parser.tab.cc"
    break;

  case 31: /* literal: BOOL_LITERAL  */
#line 188 "parser.yy"
                                {(yyval.exp) = new BooleanLiteral((yyvsp[0].valueb));}
#line 1791 "parser.tab.cc"
    break;

  case 32: /* $@2: %empty  */
#line 192 "parser.yy"
                   { SymbolTable::currentVariableType = (yyvsp[0].t)->ret_id(); }
#line 1797 "parser.tab.cc"
    break;

  case 33: /* variable_declaration: VAR type $@2 new_variable_list ';'  */
#line 193 "parser.yy"
                                              { (yyval.stmt) = new VariableDeclaration(*((yyvsp[-3].t)), *((yyvsp[-1].exp_list))); }
#line 1803 "parser.tab.cc"
    break;

  case 34: /* $@3: %empty  */
#line 194 "parser.yy"
                     { SymbolTable::currentVariableType = (yyvsp[0].t)->ret_id(); }
#line 1809 "parser.tab.cc"
    break;

  case 35: /* variable_declaration: CONST type $@3 new_variable_list ';'  */
#line 195 "parser.yy"
                                              { (yyval.stmt) = new VariableDeclaration(*((yyvsp[-3].t)), *((yyvsp[-1].exp_list))); }
#line 1815 "parser.tab.cc"
    break;

  case 36: /* new_variable_list: new_variable  */
#line 199 "parser.yy"
                                                                 {(yyval.exp_list) = new list <Expression*>(); (yyval.exp_list)->push_back((yyvsp[0].exp));}
#line 1821 "parser.tab.cc"
    break;

  case 37: /* new_variable_list: new_variable_list ',' new_variable  */
#line 200 "parser.yy"
                                             {(yyval.exp_list) = (yyvsp[-2].exp_list); (yyval.exp_list)->push_back((yyvsp[0].exp));}
#line 1827 "parser.tab.cc"
    break;

  case 38: /* new_variable: IDENTIFIER  */
#line 205 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[0].id), SymbolTable::currentVariableType, &(yylsp[0])); 
				(yyval.exp) = new Identifier(*((yyvsp[0].id)));
			}
#line 1836 "parser.tab.cc"
    break;

  case 39: /* new_variable: IDENTIFIER ASSIGN expression  */
#line 210 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[-2].id), SymbolTable::currentVariableType, &(yylsp[-2])); 
				Variable* temp = new Identifier(*((yyvsp[-2].id))); 
				(yyval.exp) = new AssignmentExp(temp, (yyvsp[0].exp));
			}
#line 1846 "parser.tab.cc"
    break;

  case 40: /* new_variable: IDENTIFIER '(' ')'  */
#line 216 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[-2].id), SymbolTable::currentVariableType, &(yylsp[-2])); 
				Variable* temp = new Identifier(*((yyvsp[-2].id))); 
				(yyval.exp) = new FunctionCall(temp);
			}
#line 1856 "parser.tab.cc"
    break;

  case 41: /* new_variable: IDENTIFIER '(' expression_list ')'  */
#line 222 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[-3].id), SymbolTable::currentVariableType, &(yylsp[-3])); 
				Variable* temp = new Identifier(*((yyvsp[-3].id))); 
				(yyval.exp) = new FunctionCall(temp, *((yyvsp[-1].exp_list)));
			}
#line 1866 "parser.tab.cc"
    break;

  case 42: /* $@4: %empty  */
#line 231 "parser.yy"
                        { 
				cur_symbol_table = cur_symbol_table->addSymbol(*(yyvsp[-1].id), (yyvsp[-2].t)->ret_id()+"->()", &(yylsp[-2]), KIND::FUNCTION); 
			}
#line 1874 "parser.tab.cc"
    break;

  case 43: /* function_declaration: type IDENTIFIER '(' $@4 ')' compound_statement  */
#line 235 "parser.yy"
                        { 
				cur_symbol_table = cur_symbol_table->returnFromFunction(); 
				auto temp = new Identifier(*((yyvsp[-4].id))); 
				(yyval.stmt) = new FunctionDeclaration(temp, *((yyvsp[-5].t)), (yyvsp[0].stmt)); 
			}
#line 1884 "parser.tab.cc"
    break;

  case 44: /* $@5: %empty  */
#line 241 "parser.yy"
                        {
				cur_symbol_table = cur_symbol_table->addSymbol(*(yyvsp[-1].id), (yyvsp[-2].t)->ret_id()+"->", &(yylsp[-2]), KIND::FUNCTION);
			}
#line 1892 "parser.tab.cc"
    break;

  case 45: /* $@6: %empty  */
#line 245 "parser.yy"
                        {
				std::string arg_types = "";
				for(auto arg: *((yyvsp[-1].arg_list))) arg_types += arg->getType() + ",";
				cur_symbol_table->lookUp(*(yyvsp[-4].id))->addArgTypeNames(arg_types.substr(0, arg_types.size()-1));
			}
#line 1902 "parser.tab.cc"
    break;

  case 46: /* function_declaration: type IDENTIFIER '(' $@5 args_list ')' $@6 compound_statement  */
#line 251 "parser.yy"
                        {
				cur_symbol_table = cur_symbol_table->returnFromFunction();
				auto temp = new Identifier(*((yyvsp[-6].id))); 
				(yyval.stmt) = new FunctionDeclaration(temp, *((yyvsp[-7].t)), (yyvsp[0].stmt), *((yyvsp[-3].arg_list)));
			}
#line 1912 "parser.tab.cc"
    break;

  case 47: /* args_list: arg  */
#line 259 "parser.yy"
                                        {(yyval.arg_list) = new list <Arg*>(); (yyval.arg_list)->push_back((yyvsp[0].argument));}
#line 1918 "parser.tab.cc"
    break;

  case 48: /* args_list: args_list ',' arg  */
#line 260 "parser.yy"
                                {(yyval.arg_list) = (yyvsp[-2].arg_list); (yyval.arg_list)->push_back((yyvsp[0].argument));}
#line 1924 "parser.tab.cc"
    break;

  case 49: /* arg: type IDENTIFIER  */
#line 265 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[0].id), (yyvsp[-1].t)->ret_id(), &(yylsp[-1])); 
				(yyval.argument) = new Arg(*((yyvsp[-1].t)), Identifier(*((yyvsp[0].id))));
			}
#line 1933 "parser.tab.cc"
    break;

  case 50: /* arg: VAR type IDENTIFIER  */
#line 270 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[0].id), (yyvsp[-1].t)->ret_id(), &(yylsp[-2])); 
				(yyval.argument) = new Arg(*((yyvsp[-1].t)), Identifier(*((yyvsp[0].id))));
			}
#line 1942 "parser.tab.cc"
    break;

  case 51: /* arg: CONST type IDENTIFIER  */
#line 275 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[0].id), (yyvsp[-1].t)->ret_id(), &(yylsp[-2])); 
				(yyval.argument) = new Arg(*((yyvsp[-1].t)), Identifier(*((yyvsp[0].id))));
			}
#line 1951 "parser.tab.cc"
    break;

  case 52: /* family_declaration: FAMILY IDENTIFIER '{' '}' ';'  */
#line 286 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[-3].id), "Family", &(yylsp[-4]), KIND::FAMILY);
				(yyval.stmt) = new FamilyDecl(Identifier(*(yyvsp[-3].id)));
			}
#line 1960 "parser.tab.cc"
    break;

  case 53: /* $@7: %empty  */
#line 291 "parser.yy"
                        { 
				cur_symbol_table = cur_symbol_table->addSymbol(*(yyvsp[-1].id), "Family", &(yylsp[-2]), KIND::FAMILY); 
			}
#line 1968 "parser.tab.cc"
    break;

  case 54: /* family_declaration: FAMILY IDENTIFIER '{' $@7 class_members '}' ';'  */
#line 295 "parser.yy"
                        {
				(yyval.stmt) = new FamilyDecl(Identifier(*(yyvsp[-5].id)), *((yyvsp[-2].class_members))); 
				cur_symbol_table = cur_symbol_table->endScope();
			}
#line 1977 "parser.tab.cc"
    break;

  case 55: /* family_declaration: FAMILY IDENTIFIER INHERITS access_specifier IDENTIFIER '{' '}' ';'  */
#line 300 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[-6].id), "Family", &(yylsp[-7]), KIND::FAMILY);
				// TODO: Copy public members from parent class
				(yyval.stmt) = new FamilyDecl(Identifier(*((yyvsp[-6].id))),optional<pair<Identifier, ACCESS_SPEC>>(make_pair(Identifier(*(yyvsp[-3].id)), *((yyvsp[-4].access_spec)))));
			}
#line 1987 "parser.tab.cc"
    break;

  case 56: /* $@8: %empty  */
#line 306 "parser.yy"
                        {
				cur_symbol_table = cur_symbol_table->addSymbol(*(yyvsp[-4].id), "Family", &(yylsp[-5]), KIND::FAMILY);
				// TODO: Copy public members from parent class
			}
#line 1996 "parser.tab.cc"
    break;

  case 57: /* family_declaration: FAMILY IDENTIFIER INHERITS access_specifier IDENTIFIER '{' $@8 class_members '}' ';'  */
#line 311 "parser.yy"
                        {
				(yyval.stmt) = new FamilyDecl(Identifier(*((yyvsp[-8].id))),*((yyvsp[-2].class_members)), optional<pair<Identifier, ACCESS_SPEC>>(make_pair(Identifier(*(yyvsp[-5].id)), *((yyvsp[-6].access_spec)))));
				cur_symbol_table = cur_symbol_table->endScope();
			}
#line 2005 "parser.tab.cc"
    break;

  case 58: /* access_specifier: PUBLIC  */
#line 318 "parser.yy"
                        {(yyval.access_spec) = new ACCESS_SPEC(ACCESS_SPEC::PUBLIC);}
#line 2011 "parser.tab.cc"
    break;

  case 59: /* access_specifier: PRIVATE  */
#line 319 "parser.yy"
                        {(yyval.access_spec) = new ACCESS_SPEC(ACCESS_SPEC::PRIVATE);}
#line 2017 "parser.tab.cc"
    break;

  case 60: /* class_members: class_member  */
#line 323 "parser.yy"
                                                        {(yyval.class_members) = new list<FamilyMembers*>(); (yyval.class_members)->push_back((yyvsp[0].class_member));}
#line 2023 "parser.tab.cc"
    break;

  case 61: /* class_members: class_members class_member  */
#line 324 "parser.yy"
                                        {(yyval.class_members) =(yyvsp[-1].class_members); (yyval.class_members)->push_back((yyvsp[0].class_member));}
#line 2029 "parser.tab.cc"
    break;

  case 62: /* class_member: access_specifier variable_declaration  */
#line 328 "parser.yy"
                                                {(yyval.class_member) = new FamilyMembers(*((yyvsp[-1].access_spec)), (yyvsp[0].stmt));}
#line 2035 "parser.tab.cc"
    break;

  case 63: /* class_member: access_specifier function_declaration  */
#line 329 "parser.yy"
                                                {(yyval.class_member) = new FamilyMembers(*((yyvsp[-1].access_spec)), (yyvsp[0].stmt));}
#line 2041 "parser.tab.cc"
    break;

  case 64: /* class_member: constructor_declaration  */
#line 330 "parser.yy"
                                                                {(yyval.class_member) = new FamilyMembers(ACCESS_SPEC::PUBLIC, (yyvsp[0].stmt));}
#line 2047 "parser.tab.cc"
    break;

  case 65: /* $@9: %empty  */
#line 335 "parser.yy"
                        {
				cur_symbol_table = cur_symbol_table->addSymbol(*(yyvsp[-1].id), "void->", &(yylsp[-1]), KIND::FUNCTION);
			}
#line 2055 "parser.tab.cc"
    break;

  case 66: /* $@10: %empty  */
#line 339 "parser.yy"
                        {
				std::string arg_types = "";
				for(auto arg: *((yyvsp[-1].arg_list))) arg_types += arg->getType() + ",";
				cur_symbol_table->lookUp(*(yyvsp[-4].id))->addArgTypeNames(arg_types.substr(0, arg_types.size()-1));
			}
#line 2065 "parser.tab.cc"
    break;

  case 67: /* constructor_declaration: IDENTIFIER '(' $@9 args_list ')' $@10 compound_statement  */
#line 345 "parser.yy"
                        {
				cur_symbol_table = cur_symbol_table->returnFromFunction();
				(yyval.stmt) = new ConstructorDeclaration(Identifier(*((yyvsp[-6].id))), (yyvsp[0].stmt), *((yyvsp[-3].arg_list)));
			}
#line 2074 "parser.tab.cc"
    break;

  case 68: /* primary_expression: literal  */
#line 355 "parser.yy"
                                                                        {(yyval.exp) = (Expression*)(yyvsp[0].exp);}
#line 2080 "parser.tab.cc"
    break;

  case 69: /* primary_expression: variable  */
#line 356 "parser.yy"
                                                                        {(yyval.exp) = (Expression*)(yyvsp[0].exp);}
#line 2086 "parser.tab.cc"
    break;

  case 70: /* primary_expression: variable '(' ')'  */
#line 357 "parser.yy"
                                                                {(yyval.exp) = new FunctionCall((yyvsp[-2].exp));}
#line 2092 "parser.tab.cc"
    break;

  case 71: /* primary_expression: variable '(' expression_list ')'  */
#line 358 "parser.yy"
                                                {(yyval.exp) = new FunctionCall((yyvsp[-3].exp), *((yyvsp[-1].exp_list)));}
#line 2098 "parser.tab.cc"
    break;

  case 72: /* primary_expression: '(' expression ')'  */
#line 359 "parser.yy"
                                                        {(yyval.exp) = (yyvsp[-1].exp);}
#line 2104 "parser.tab.cc"
    break;

  case 73: /* variable: IDENTIFIER  */
#line 363 "parser.yy"
                                                                {(yyval.exp) = new Identifier(*((yyvsp[0].id)));}
#line 2110 "parser.tab.cc"
    break;

  case 74: /* variable: variable SCOPE_ACCESS IDENTIFIER  */
#line 364 "parser.yy"
                                                {(yyval.exp) = new MemberAccess((Variable*)(yyvsp[-2].exp), *((yyvsp[0].id)));}
#line 2116 "parser.tab.cc"
    break;

  case 75: /* variable: variable '[' expression ']'  */
#line 365 "parser.yy"
                                                {(yyval.exp) = new ArrayAccess((yyvsp[-3].exp), (yyvsp[-1].exp));}
#line 2122 "parser.tab.cc"
    break;

  case 77: /* expression: '+' expression  */
#line 370 "parser.yy"
                                                                {(yyval.exp) = new UnaryPlus((yyvsp[0].exp));}
#line 2128 "parser.tab.cc"
    break;

  case 78: /* expression: '-' expression  */
#line 371 "parser.yy"
                                                                {(yyval.exp) = new UnaryMinus((yyvsp[0].exp));}
#line 2134 "parser.tab.cc"
    break;

  case 79: /* expression: expression '*' expression  */
#line 372 "parser.yy"
                                                                        {(yyval.exp) = new Multiplication((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2140 "parser.tab.cc"
    break;

  case 80: /* expression: expression '/' expression  */
#line 373 "parser.yy"
                                                                        {(yyval.exp) = new Division((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2146 "parser.tab.cc"
    break;

  case 81: /* expression: expression '%' expression  */
#line 374 "parser.yy"
                                                                        {(yyval.exp) = new ModularDiv((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2152 "parser.tab.cc"
    break;

  case 82: /* expression: expression '+' expression  */
#line 375 "parser.yy"
                                                                        {(yyval.exp) = new Addition((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2158 "parser.tab.cc"
    break;

  case 83: /* expression: expression '-' expression  */
#line 376 "parser.yy"
                                                                        {(yyval.exp) = new Subtraction((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2164 "parser.tab.cc"
    break;

  case 84: /* expression: expression EQ expression  */
#line 377 "parser.yy"
                                                                        {(yyval.exp) = new CompEQ((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2170 "parser.tab.cc"
    break;

  case 85: /* expression: expression NOT_EQ expression  */
#line 378 "parser.yy"
                                                                {(yyval.exp) = new CompNEQ((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2176 "parser.tab.cc"
    break;

  case 86: /* expression: expression LS_THAN expression  */
#line 379 "parser.yy"
                                                                {(yyval.exp) = new CompLT((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2182 "parser.tab.cc"
    break;

  case 87: /* expression: expression LS_THAN_EQ expression  */
#line 380 "parser.yy"
                                                                {(yyval.exp) = new CompLE((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2188 "parser.tab.cc"
    break;

  case 88: /* expression: expression GR_THAN expression  */
#line 381 "parser.yy"
                                                                {(yyval.exp) = new CompGT((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2194 "parser.tab.cc"
    break;

  case 89: /* expression: expression GR_THAN_EQ expression  */
#line 382 "parser.yy"
                                                                {(yyval.exp) = new CompGE((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2200 "parser.tab.cc"
    break;

  case 90: /* expression: expression LOGICAL_AND expression  */
#line 383 "parser.yy"
                                                                {(yyval.exp) = new LogicalAND((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2206 "parser.tab.cc"
    break;

  case 91: /* expression: expression LOGICAL_OR expression  */
#line 384 "parser.yy"
                                                                {(yyval.exp) = new LogicalOR((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2212 "parser.tab.cc"
    break;

  case 92: /* expression: LOGICAL_NOT expression  */
#line 385 "parser.yy"
                                                                        {(yyval.exp) = new LogicalNOT((yyvsp[0].exp));}
#line 2218 "parser.tab.cc"
    break;

  case 93: /* expression: INC variable  */
#line 386 "parser.yy"
                                                                                {(yyval.exp) = new PrefixInc((Variable*)(yyvsp[0].exp));}
#line 2224 "parser.tab.cc"
    break;

  case 94: /* expression: DEC variable  */
#line 387 "parser.yy"
                                                                                {(yyval.exp) = new PostfixDec((Variable*)(yyvsp[0].exp));}
#line 2230 "parser.tab.cc"
    break;

  case 95: /* expression: variable INC  */
#line 388 "parser.yy"
                                                                {(yyval.exp) = new PostfixInc((Variable*)(yyvsp[-1].exp));}
#line 2236 "parser.tab.cc"
    break;

  case 96: /* expression: variable DEC  */
#line 389 "parser.yy"
                                                                {(yyval.exp) = new PostfixDec((Variable*)(yyvsp[-1].exp));}
#line 2242 "parser.tab.cc"
    break;

  case 97: /* expression: variable ASSIGN expression  */
#line 390 "parser.yy"
                                                                {(yyval.exp) = new AssignmentExp((Variable*)(yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2248 "parser.tab.cc"
    break;

  case 98: /* expression: variable MUL_ASSIGN expression  */
#line 391 "parser.yy"
                                                                {(yyval.exp) = new MulAssign((Variable*)(yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2254 "parser.tab.cc"
    break;

  case 99: /* expression: variable DIV_ASSIGN expression  */
#line 392 "parser.yy"
                                                                {(yyval.exp) = new DivAssign((Variable*)(yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2260 "parser.tab.cc"
    break;

  case 100: /* expression: variable MOD_ASSIGN expression  */
#line 393 "parser.yy"
                                                                {(yyval.exp) = new ModAssign((Variable*)(yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2266 "parser.tab.cc"
    break;

  case 101: /* expression: variable ADD_ASSIGN expression  */
#line 394 "parser.yy"
                                                                {(yyval.exp) = new AddAssign((Variable*)(yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2272 "parser.tab.cc"
    break;

  case 102: /* expression: variable SUB_ASSIGN expression  */
#line 395 "parser.yy"
                                                                {(yyval.exp) = new SubAssign((Variable*)(yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2278 "parser.tab.cc"
    break;

  case 103: /* expression: expression '?' expression ':' expression  */
#line 396 "parser.yy"
                                                        {(yyval.exp) = new TernaryOperator((yyvsp[-4].exp), (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2284 "parser.tab.cc"
    break;

  case 104: /* expression_list: expression  */
#line 400 "parser.yy"
                                                                {(yyval.exp_list) = new list <Expression*>(); ((yyval.exp_list))->push_back((yyvsp[0].exp));}
#line 2290 "parser.tab.cc"
    break;

  case 105: /* expression_list: expression_list ',' expression  */
#line 401 "parser.yy"
                                                {(yyval.exp_list) = (yyvsp[-2].exp_list); ((yyval.exp_list))->push_back((yyvsp[0].exp));}
#line 2296 "parser.tab.cc"
    break;

  case 114: /* compound_statement: '{' '}'  */
#line 419 "parser.yy"
                                                        {(yyval.stmt) = new CompoundStatement(list<Statement*>());}
#line 2302 "parser.tab.cc"
    break;

  case 115: /* $@11: %empty  */
#line 420 "parser.yy"
              {cur_symbol_table = cur_symbol_table->startNewScope();}
#line 2308 "parser.tab.cc"
    break;

  case 116: /* compound_statement: '{' $@11 statement_list '}'  */
#line 422 "parser.yy"
              {cur_symbol_table = cur_symbol_table->endScope(); (yyval.stmt) = new CompoundStatement(*((yyvsp[-1].stmt_list)));}
#line 2314 "parser.tab.cc"
    break;

  case 117: /* statement_list: statement  */
#line 426 "parser.yy"
                                                        {(yyval.stmt_list) = new list <Statement*>(); ((yyval.stmt_list))->push_back((yyvsp[0].stmt));}
#line 2320 "parser.tab.cc"
    break;

  case 118: /* statement_list: statement_list statement  */
#line 427 "parser.yy"
                                        {(yyval.stmt_list) = (yyvsp[-1].stmt_list); ((yyval.stmt_list))->push_back((yyvsp[0].stmt));}
#line 2326 "parser.tab.cc"
    break;

  case 119: /* expression_statement: ';'  */
#line 431 "parser.yy"
                                          {(yyval.stmt) = new ExpressionStatement();}
#line 2332 "parser.tab.cc"
    break;

  case 120: /* expression_statement: expression_list ';'  */
#line 432 "parser.yy"
                              {(yyval.stmt) = new ExpressionStatement((yyvsp[-1].exp_list));}
#line 2338 "parser.tab.cc"
    break;

  case 121: /* selection_statement: IF '(' expression ')' compound_statement  */
#line 436 "parser.yy"
                                                                                                        {(yyval.stmt) = new IfStatement((yyvsp[-2].exp), (CompoundStatement*)(yyvsp[0].stmt));}
#line 2344 "parser.tab.cc"
    break;

  case 122: /* selection_statement: IF '(' expression ')' compound_statement ELSE compound_statement  */
#line 437 "parser.yy"
                                                                                {(yyval.stmt) = new IfElseStatement((yyvsp[-4].exp), (CompoundStatement*)(yyvsp[-2].stmt), (CompoundStatement*)(yyvsp[0].stmt));}
#line 2350 "parser.tab.cc"
    break;

  case 123: /* selection_statement: SWITCH '(' expression ')' statement  */
#line 438 "parser.yy"
                                                                                                        {(yyval.stmt) = new SwitchStatement((yyvsp[-2].exp), (CompoundStatement*)(yyvsp[0].stmt));}
#line 2356 "parser.tab.cc"
    break;

  case 124: /* labeled_statement: IDENTIFIER ':' statement  */
#line 442 "parser.yy"
                                                {Expression* temp = new Identifier(*((yyvsp[-2].id)));(yyval.stmt) = new LabeledStatement(temp, (yyvsp[0].stmt));}
#line 2362 "parser.tab.cc"
    break;

  case 125: /* labeled_statement: CASE expression ':' statement  */
#line 443 "parser.yy"
                                        {(yyval.stmt) = new CaseLabel((yyvsp[-2].exp), (yyvsp[0].stmt));}
#line 2368 "parser.tab.cc"
    break;

  case 126: /* labeled_statement: DEFAULT ':' statement  */
#line 444 "parser.yy"
                                                {(yyval.stmt) = new DefaultLabel((yyvsp[0].stmt));}
#line 2374 "parser.tab.cc"
    break;

  case 127: /* iteration_statement: WHILE '(' ')' compound_statement  */
#line 448 "parser.yy"
                                                                                                                                                        {(yyval.stmt) = new WhileLoop((CompoundStatement*)(yyvsp[0].stmt));}
#line 2380 "parser.tab.cc"
    break;

  case 128: /* iteration_statement: WHILE '(' expression ')' compound_statement  */
#line 449 "parser.yy"
                                                                                                                                        {(yyval.stmt) = new WhileLoop((CompoundStatement*)(yyvsp[0].stmt), (yyvsp[-2].exp));}
#line 2386 "parser.tab.cc"
    break;

  case 129: /* iteration_statement: FOR '(' expression_statement expression_statement ')' compound_statement  */
#line 450 "parser.yy"
                                                                                                                {(yyval.stmt) = new ForLoop((CompoundStatement*)(yyvsp[0].stmt), (ExpressionStatement*)(yyvsp[-3].stmt), (ExpressionStatement*)(yyvsp[-2].stmt), NULL);}
#line 2392 "parser.tab.cc"
    break;

  case 130: /* iteration_statement: FOR '(' expression_statement expression_statement expression ')' compound_statement  */
#line 451 "parser.yy"
                                                                                                {(yyval.stmt) = new ForLoop((CompoundStatement*)(yyvsp[0].stmt), (ExpressionStatement*)(yyvsp[-4].stmt), (ExpressionStatement*)(yyvsp[-3].stmt), (yyvsp[-2].exp));}
#line 2398 "parser.tab.cc"
    break;

  case 131: /* iteration_statement: FOR '(' variable_declaration expression_statement ')' compound_statement  */
#line 452 "parser.yy"
                                                                                                                {(yyval.stmt) = new ForLoop((CompoundStatement*)(yyvsp[0].stmt), (ExpressionStatement*)(yyvsp[-3].stmt), (ExpressionStatement*)(yyvsp[-2].stmt), NULL);}
#line 2404 "parser.tab.cc"
    break;

  case 132: /* iteration_statement: FOR '(' variable_declaration expression_statement expression ')' compound_statement  */
#line 453 "parser.yy"
                                                                                                {(yyval.stmt) = new ForLoop((CompoundStatement*)(yyvsp[0].stmt), (ExpressionStatement*)(yyvsp[-4].stmt), (ExpressionStatement*)(yyvsp[-3].stmt), (yyvsp[-2].exp));}
#line 2410 "parser.tab.cc"
    break;

  case 133: /* jump_statement: CONTINUE ';'  */
#line 457 "parser.yy"
                                                {(yyval.stmt) = new ContinueStatement();}
#line 2416 "parser.tab.cc"
    break;

  case 134: /* jump_statement: BREAK ';'  */
#line 458 "parser.yy"
                                                        {(yyval.stmt) = new BreakStatement();}
#line 2422 "parser.tab.cc"
    break;

  case 135: /* jump_statement: SEND expression_statement  */
#line 459 "parser.yy"
                                        {(yyval.stmt) = new ReturnStatement((((ExpressionStatement*)(yyvsp[0].stmt))->getValue()).back());}
#line 2428 "parser.tab.cc"
    break;


#line 2432 "parser.tab.cc"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 462 "parser.yy"


void init_yylloc(const char* filename){
	yylloc.first_line = yylloc.last_line = yylineno = 1;
	yylloc.first_column = yylloc.last_column = 0;
	yylloc.filename = filename;
}

int main(int argc, char **argv){
	// The parser trace is generated only if yydebug is set to 1
	#ifdef PARSER_TRACE_DEBUG
		yydebug = 1;
	#endif
	
	if(argc < 2){
		init_yylloc("(stdin)");
		yyparse();
		#ifdef SYMBOL_TABLE_DEBUG
			global_symbol_table.printSymbolTable(std::cout);
		#endif
	}
    else{
        for(int i = 1; i < argc; i++){
            init_yylloc(argv[i]);
            FILE *file = fopen(argv[i], "r");
            if(file == NULL){ perror(argv[i]); return -1; }
            yyrestart(file);

			yyparse();

			#ifdef SYMBOL_TABLE_DEBUG
			int file_dir_path_size = (string(argv[i]).find_last_of('/') == string::npos) ? 0 : string(argv[i]).find_last_of('/') + 1;
			string dirname = string(argv[i]).substr(0, file_dir_path_size);
			string filename = string(argv[i]).substr(file_dir_path_size, string(argv[i]).size() - file_dir_path_size - 5);
			filesystem::create_directory(dirname + "output/");
			string symbol_table_filename = dirname + "output/" + filename + ".sym";
			ofstream symbol_table_output_file(symbol_table_filename);
			global_symbol_table.printSymbolTable(symbol_table_output_file);
			#endif

            fclose(file);
        }
    }
}

void yyerror(const char*s){
	fprintf(stdout, "%s: Line %d-(%d..%d):\n\t%s\n", yylloc.filename.c_str(), yylloc.first_line, yylloc.first_column, yylloc.last_column, s);
	fprintf(stderr, "%s: Line %d-(%d..%d):\n\t%s\n", yylloc.filename.c_str(), yylloc.first_line, yylloc.first_column, yylloc.last_column, s);
}
