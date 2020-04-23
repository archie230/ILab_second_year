// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "src/parser/parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hh"

// User implementation prologue.

#line 51 "src/parser/parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 47 "src/parser/parser.y" // lalr1.cc:413

    #include "../PCL_Driver.hpp"
    using namespace AST;

    namespace yy {
    	PCL_Parser::token_type yylex(PCL_Parser::semantic_type* yylval, PCL_Parser::location_type* yylloc, PCL_Driver* driver);
    }

#line 62 "src/parser/parser.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 148 "src/parser/parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  PCL_Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  PCL_Parser::PCL_Parser (yy::PCL_Driver* driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  PCL_Parser::~PCL_Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  PCL_Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  PCL_Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  PCL_Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  PCL_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  PCL_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  PCL_Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  PCL_Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  PCL_Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  PCL_Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  PCL_Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  PCL_Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  PCL_Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  PCL_Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  PCL_Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  PCL_Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  PCL_Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  PCL_Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  PCL_Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  PCL_Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  PCL_Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  PCL_Parser::symbol_number_type
  PCL_Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  PCL_Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  PCL_Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  PCL_Parser::stack_symbol_type&
  PCL_Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  PCL_Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 3: // TNUM

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 401 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 4: // TID

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 408 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 5: // TWHILE

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 415 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 6: // TIF

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 422 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 7: // TOR

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 429 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 8: // TAND

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 436 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 9: // TLESS

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 443 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 10: // TGR

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 450 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 11: // TLESS_EQ

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 457 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 12: // TGR_EQ

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 464 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 13: // TEQUAL

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 471 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 14: // TNEQUAL

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 478 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 15: // TADD

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 485 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 16: // TSUB

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 492 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 17: // TMUL

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 499 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 18: // TDIV

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 506 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 19: // TINPUT

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 513 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 20: // TOUTPUT

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 520 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 21: // TASSIGN

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 527 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 22: // TEXCLAM

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 534 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 23: // TPERCENT

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 541 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 24: // TELSE

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 548 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 25: // TRETURN

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 555 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 26: // TFUNC

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 562 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 27: // TERR

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 569 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 28: // '{'

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 576 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 29: // '}'

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 583 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 30: // ';'

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 590 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 31: // '('

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 597 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 32: // ')'

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 604 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 33: // ','

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 611 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 34: // ':'

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 618 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 36: // translation_unit

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 625 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 37: // block

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 632 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 39: // statement_list

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 639 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 40: // statement

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 646 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 41: // matched_statement

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 653 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 42: // open_statement

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 660 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 43: // function_declaration

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 667 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 45: // func_body

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 674 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 46: // arguments

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 681 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 47: // arguments_list

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 688 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 48: // name_form

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 695 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 49: // iteration_statement

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 702 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 50: // expression

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 709 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 51: // assignment_expression

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 716 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 52: // logical_or_expression

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 723 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 53: // logical_and_expression

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 730 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 54: // equality_expression

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 737 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 55: // relational_expression

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 744 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 56: // additive_expression

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 751 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 57: // multiplicative_expression

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 758 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 58: // unary_expression

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 765 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 59: // primary_expression

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 772 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 60: // function_call

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 779 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 61: // call_arguments

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 786 "src/parser/parser.cc" // lalr1.cc:614
        break;

      case 62: // expression_list

#line 84 "src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 793 "src/parser/parser.cc" // lalr1.cc:614
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  PCL_Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  PCL_Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  PCL_Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  PCL_Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  PCL_Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  PCL_Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  PCL_Parser::debug_level_type
  PCL_Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  PCL_Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline PCL_Parser::state_type
  PCL_Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  PCL_Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  PCL_Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  PCL_Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 97 "src/parser/parser.y" // lalr1.cc:859
    { driver -> root_ = nullptr; (yylhs.value) = nullptr; }
#line 1032 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 3:
#line 98 "src/parser/parser.y" // lalr1.cc:859
    {
													(yylhs.value) = nullptr;
													driver -> root_ = (yystack_[0].value);
                        }
#line 1041 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 105 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; }
#line 1047 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 5:
#line 108 "src/parser/parser.y" // lalr1.cc:859
    {
		ENV.push_front(new SymTbl::Table(ENV.front(), CUR_ID++));
		driver -> symtbl_.add_tbl(ENV.front() -> id_, ENV.front());
	}
#line 1056 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 113 "src/parser/parser.y" // lalr1.cc:859
    {
                            if((yystack_[1].value)) {
                                auto donor = static_cast<ListNode*>((yystack_[1].value));
                                (yylhs.value) = new ListNode(TokenName::T_SCOPE, std::move(*donor), ENV.front() -> id_);
																delete (yystack_[1].value);
                            } else
                                (yylhs.value) = nullptr;

                            ENV.pop_front();
											}
#line 1071 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 126 "src/parser/parser.y" // lalr1.cc:859
    {
                                (yylhs.value) = new ListNode(TokenName::T_STMLST);
                                static_cast<ListNode*>((yylhs.value)) -> push_kid((yystack_[0].value));
                              }
#line 1080 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 131 "src/parser/parser.y" // lalr1.cc:859
    {
                                static_cast<ListNode*>((yystack_[1].value)) -> push_kid((yystack_[0].value));
                                (yylhs.value) = (yystack_[1].value);
                              }
#line 1089 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 138 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1095 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 139 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1101 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 143 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[1].value); }
#line 1107 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 144 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; }
#line 1113 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 146 "src/parser/parser.y" // lalr1.cc:859
    {
 (yylhs.value) = (yystack_[0].value);
 if ((yystack_[0].value) && (yystack_[0].value) -> GetType() != T_SCOPE)
		error(yystack_[0].location, "forgot semicolon");
}
#line 1123 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 152 "src/parser/parser.y" // lalr1.cc:859
    {
	(yylhs.value) = new IfNode(TokenName::T_IF, (yystack_[4].value), (yystack_[2].value), (yystack_[0].value));
}
#line 1131 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 156 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1137 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 157 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_OUTPUT, nullptr, (yystack_[1].value)); }
#line 1143 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 158 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_OUTPUT, nullptr, (yystack_[1].value)); }
#line 1149 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 159 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1155 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 160 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[1].value); }
#line 1161 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 161 "src/parser/parser.y" // lalr1.cc:859
    {
																if (ENV.size() == 1)
																	error(yystack_[2].location, "return is not inside function");
																(yylhs.value) = new TwoKidsNode(TokenName::T_RETURN, nullptr, (yystack_[1].value));
                              }
#line 1171 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 170 "src/parser/parser.y" // lalr1.cc:859
    {
	(yylhs.value) = new IfNode(TokenName::T_IF, (yystack_[2].value), (yystack_[0].value));
}
#line 1179 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 175 "src/parser/parser.y" // lalr1.cc:859
    {
	(yylhs.value) = new IfNode(TokenName::T_IF, (yystack_[4].value), (yystack_[2].value), (yystack_[0].value));
}
#line 1187 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 182 "src/parser/parser.y" // lalr1.cc:859
    {
	/* at interpretation phase there will be copy of this Table to locate var values*/
	ENV.push_front( new SymTbl::Table(ENV.front(), CUR_ID++) );
	driver -> symtbl_.add_tbl(ENV.front() -> id_, ENV.front());

	if (! (ENV[1] -> find(GetName((yystack_[7].value)))) ) {
    ENV[1] -> insert(GetName((yystack_[7].value)),
      new FuncDec_t {FUNC, yystack_[7].location, ENV.front() -> id_});
	} else
			error(yystack_[7].location, "variable " + GetName((yystack_[7].value)) + " already exists");

	if ((yystack_[1].value)) { /* in case func(x) : name {...}*/
		if (! (ENV[1] -> find(GetName((yystack_[1].value)))) ) {
			ENV.back() -> insert(GetName((yystack_[1].value)),
				new FuncDec_t {FUNC, yystack_[1].location, ENV.front() -> id_});
		} else
				error(yystack_[1].location, "variable " + GetName((yystack_[1].value)) + " already exists");
	}



	if ((yystack_[3].value)) { /* adding function arguments to it's scope*/
		IDec_t* decl = nullptr;

		auto local_decl  = static_cast<FuncDec_t*>(ENV[1] -> find(GetName((yystack_[7].value))));
		auto global_decl = (yystack_[1].value) ? static_cast<FuncDec_t*>(ENV[1] -> find(GetName((yystack_[1].value)))) : nullptr;

		for(int i = 0; i < static_cast<ListNode*>((yystack_[3].value)) -> size(); i++)
		    try {

					decl = new VarDec_t {VAR, yystack_[3].location, 0};
					ENV.front() -> insert(GetName((*static_cast<ListNode*>((yystack_[3].value)))[i]), decl);

					(local_decl -> arg_names_).push_back(GetName((*static_cast<ListNode*>((yystack_[3].value)))[i]));
					if(global_decl)
						(global_decl -> arg_names_).push_back(GetName((*static_cast<ListNode*>((yystack_[3].value)))[i]));

		    } catch(...) {
					delete decl;
					error(yystack_[7].location, "variable " + GetName((*static_cast<ListNode*>((yystack_[3].value)))[i]) + " already exists");
		    }
	}

}
#line 1236 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 227 "src/parser/parser.y" // lalr1.cc:859
    {

	if ((yystack_[1].value)) {
		auto donor = static_cast<ListNode*>((yystack_[1].value));
		auto tmp = new ListNode(TokenName::T_FUNCTION_SCOPE, std::move(*donor), ENV.front() -> id_);
		delete (yystack_[1].value);
		(yystack_[1].value) = tmp;
	}

	static_cast<FuncDec_t*>(ENV[1] -> find(GetName((yystack_[10].value)))) -> function_body_ = (yystack_[1].value);

	if ((yystack_[4].value)) {
		static_cast<FuncDec_t*>(ENV[1] -> find(GetName((yystack_[4].value)))) -> function_body_ = (yystack_[1].value);
		delete (yystack_[4].value);
	}

	ENV.pop_front();

	 /*there is no point in saving that, because we added all variables in symtable
	 and saved their names*/
	delete (yystack_[6].value);

	(yylhs.value) = new TwoKidsNode(TokenName::T_FUNCDEC, (yystack_[10].value), (yystack_[1].value));
}
#line 1265 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 254 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1271 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 255 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; }
#line 1277 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 258 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; }
#line 1283 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 259 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1289 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 263 "src/parser/parser.y" // lalr1.cc:859
    {
  				      (yylhs.value) = new ListNode(TokenName::T_ARGLIST);
  				      static_cast<ListNode*>((yylhs.value)) -> push_kid((yystack_[0].value));
						}
#line 1298 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 268 "src/parser/parser.y" // lalr1.cc:859
    {
													  static_cast<ListNode*>((yystack_[2].value)) -> push_kid((yystack_[0].value));
													  (yylhs.value) = (yystack_[2].value);
											    }
#line 1307 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 275 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; }
#line 1313 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 276 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1319 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 280 "src/parser/parser.y" // lalr1.cc:859
    {
                                                    (yylhs.value) = new TwoKidsNode(TokenName::T_WHILE, (yystack_[2].value), (yystack_[0].value));
                                        	}
#line 1327 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 284 "src/parser/parser.y" // lalr1.cc:859
    {
						                                        (yylhs.value) = new TwoKidsNode(TokenName::T_WHILE, (yystack_[2].value), (yystack_[0].value));
                                       		}
#line 1335 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 288 "src/parser/parser.y" // lalr1.cc:859
    {
						                                        (yylhs.value) = new TwoKidsNode(TokenName::T_WHILE, (yystack_[2].value), (yystack_[0].value));
																					}
#line 1343 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 295 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1349 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 299 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1355 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 302 "src/parser/parser.y" // lalr1.cc:859
    {
                                        (yylhs.value) = new TwoKidsNode(TokenName::T_ASSIGN, (yystack_[2].value), (yystack_[0].value));
                                        IDec_t* decl = nullptr;
                                        /* if there is no same identifier add it to symtbl*/
                                        if ( !(decl = (ENV.front() -> find(GetName((yystack_[2].value))))) ) {
						                              VarDec_t* elem = new VarDec_t {VAR, yystack_[2].location, 0};
																					ENV.front() -> insert(GetName((yystack_[2].value)), elem);
                                        } else
                                          if (ENV.front() -> find(GetName((yystack_[2].value))) -> type_ == FUNC)
                                              error(yystack_[2].location, "can't assign smth to function name to " + GetName((yystack_[2].value)));
                                    }
#line 1371 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 316 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1377 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 317 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_OR, (yystack_[2].value), (yystack_[0].value)); }
#line 1383 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 321 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1389 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 322 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_AND, (yystack_[2].value), (yystack_[0].value)); }
#line 1395 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 326 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1401 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 327 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_EQUAL, (yystack_[2].value), (yystack_[0].value)); }
#line 1407 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 328 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_NEQUAL, (yystack_[2].value), (yystack_[0].value)); }
#line 1413 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 332 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1419 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 333 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_LESS, (yystack_[2].value), (yystack_[0].value)); }
#line 1425 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 334 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_GR, (yystack_[2].value), (yystack_[0].value)); }
#line 1431 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 335 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_LESS_EQ, (yystack_[2].value), (yystack_[0].value)); }
#line 1437 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 336 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_GR_EQ, (yystack_[2].value), (yystack_[0].value)); }
#line 1443 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 340 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1449 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 341 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_ADD, (yystack_[2].value), (yystack_[0].value)); }
#line 1455 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 342 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_SUB, (yystack_[2].value), (yystack_[0].value)); }
#line 1461 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 346 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1467 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 347 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_MUL, (yystack_[2].value), (yystack_[0].value)); }
#line 1473 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 348 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_DIV, (yystack_[2].value), (yystack_[0].value)); }
#line 1479 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 349 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_PERCENT, (yystack_[2].value), (yystack_[0].value)); }
#line 1485 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 353 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1491 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 354 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_ADD, nullptr, (yystack_[0].value)); }
#line 1497 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 355 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_SUB, nullptr, (yystack_[0].value)); }
#line 1503 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 356 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_EXCLAM, nullptr, (yystack_[0].value)); }
#line 1509 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 361 "src/parser/parser.y" // lalr1.cc:859
    {
				IDec_t* decl = nullptr;

				if(!(decl = ENV.front() -> find(GetName((yystack_[0].value))))) {
					error(yystack_[0].location, "undeclarated variable " + GetName((yystack_[0].value)));
				} else {
					if(decl -> type_ == FUNC)
						error (yystack_[0].location, GetName((yystack_[0].value)) + " isn't a name of variable ");
				}

		    (yylhs.value) = (yystack_[0].value);
}
#line 1526 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 373 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value);}
#line 1532 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 374 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1538 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 375 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new INode(TokenName::T_INPUT); }
#line 1544 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 376 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[1].value); }
#line 1550 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 377 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1556 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 381 "src/parser/parser.y" // lalr1.cc:859
    {
					IDec_t* decl = nullptr;

					if ( !(decl = ENV.front() -> find(GetName((yystack_[3].value)))) )
						error(yystack_[3].location, "undeclarated function " + GetName((yystack_[3].value)));
					else {
						if (decl && decl -> type_ == VAR)
						    error(yystack_[3].location, GetName((yystack_[3].value)) + " isn't a function name");

					  int arg_num = (yystack_[1].value) ? static_cast<ListNode*>((yystack_[1].value)) -> size() : 0;

            if (arg_num != (static_cast<FuncDec_t*>(decl) -> arg_names_).size())
		            error(yystack_[3].location, "in function call " + GetName((yystack_[3].value)) +
			             "(..) arguments number doesn't match with declaration");
					}

/*//					lhs of FUNCCALL node is list of exprs, like arg_name = expression
					if ($call_arguments && driver -> err_counter_ == 0) {
						ListNode& call_args = *static_cast<ListNode*>($call_arguments);
						for(int i = 0; i < call_args.size(); i++)
							call_args[i] = new TwoKidsNode(TokenName::T_ASSIGN,
							 new IdNode(T_ID, static_cast<FuncDec_t*>(decl) -> arg_names_[i]), call_args[i]);
					}*/

					(yylhs.value) = new TwoKidsNode(TokenName::T_FUNCCALL, (yystack_[3].value), (yystack_[1].value));
}
#line 1587 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 410 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; }
#line 1593 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 411 "src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value);}
#line 1599 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 415 "src/parser/parser.y" // lalr1.cc:859
    {
                                	(yylhs.value) = new ListNode(TokenName::T_EXPRLIST);
                                	static_cast<ListNode*>((yylhs.value)) -> push_kid((yystack_[0].value));
                              	}
#line 1608 "src/parser/parser.cc" // lalr1.cc:859
    break;

  case 72:
#line 421 "src/parser/parser.y" // lalr1.cc:859
    {
                                	static_cast<ListNode*>((yystack_[2].value)) -> push_kid((yystack_[0].value));
                                	(yylhs.value) = (yystack_[2].value);
                              	}
#line 1617 "src/parser/parser.cc" // lalr1.cc:859
    break;


#line 1621 "src/parser/parser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  PCL_Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  PCL_Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char PCL_Parser::yypact_ninf_ = -89;

  const signed char PCL_Parser::yytable_ninf_ = -27;

  const short int
  PCL_Parser::yypact_[] =
  {
      17,     1,   -89,    -6,     7,    12,   221,   221,   -89,   226,
     221,   226,    24,   226,    66,   -89,    73,   -89,   -89,   -89,
      37,   -89,    38,   -89,    62,    63,    21,    40,    31,    -4,
     -89,   -89,   -89,   -89,   200,   226,   226,   226,   226,    39,
     -89,   -89,    -5,    11,   -89,    42,   -89,   192,    52,   -89,
     -89,   -89,   -89,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,    54,    62,   -89,    58,
      53,    59,     8,    64,   221,   -89,   -89,   -89,   105,   -89,
      63,    21,    40,    40,    31,    31,    31,    31,    -4,    -4,
     -89,   -89,   -89,    90,   -89,   226,   192,   192,   192,   192,
     -89,   -89,    65,    67,   -89,   -89,   -89,   -89,   -89,    75,
      68,    99,   192,   103,    84,   -89,   -89,   -89,   -89,   -89,
     134,   163,    85,   -89
  };

  const unsigned char
  PCL_Parser::yydefact_[] =
  {
       0,     0,    64,    62,     0,     0,     0,     0,    65,     0,
       0,     0,     5,     0,     0,    67,     0,     7,     9,    10,
      18,    15,    13,    36,    37,    39,    41,    43,    46,    51,
      54,    58,    63,    12,     0,    69,     0,     0,     0,    62,
      59,    60,    62,     0,    61,     0,     4,     0,     0,     1,
       8,    19,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    38,    71,     0,
      70,     0,     0,     0,     0,    17,    16,    20,     0,    66,
      40,    42,    44,    45,    47,    48,    49,    50,    52,    53,
      55,    56,    57,    27,    68,     0,     0,     0,     0,     0,
       6,    29,     0,    28,    72,    35,    34,    33,    21,     9,
      31,     0,     0,     0,     0,    30,    14,    22,    32,    23,
       0,     0,     0,    24
  };

  const signed char
  PCL_Parser::yypgoto_[] =
  {
     -89,   -89,   -89,   -89,   -45,   -16,   -88,     4,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,    -8,   -89,   -30,    60,    61,
       3,    -3,    -1,     0,   -89,   -89,   -89,   -89
  };

  const signed char
  PCL_Parser::yydefgoto_[] =
  {
      -1,    14,    15,    47,    16,    17,    18,    19,    20,   120,
     122,   102,   103,   114,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    69,    70
  };

  const signed char
  PCL_Parser::yytable_[] =
  {
      50,    43,    78,    45,    67,    48,    40,    41,    36,    97,
      44,   109,    75,    63,    64,    34,    74,    -2,     1,    65,
       2,     3,     4,     5,   116,    35,    35,    68,    71,    72,
      73,    33,     6,     7,    55,    56,     8,     9,    37,    10,
      98,    76,    11,    38,    67,    12,    61,    62,    13,    57,
      58,    59,    60,    46,    84,    85,    86,    87,    82,    83,
      88,    89,    50,    90,    91,    92,    49,    51,    52,    53,
      35,    54,    77,    -3,     1,   121,     2,     3,     4,     5,
     105,   106,   107,   108,    79,    93,    95,   104,     6,     7,
      94,    96,     8,     9,   101,    10,    99,   110,    11,   112,
     111,    12,   113,   115,    13,    50,     1,   118,     2,     3,
       4,     5,   119,    80,   123,    81,   117,     0,     0,     0,
       6,     7,     0,     0,     8,     9,     0,    10,     0,     0,
      11,     0,     0,    12,   100,     1,    13,     2,     3,     4,
       5,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       7,     0,     0,     8,     9,     0,    10,     0,     0,    11,
       0,     0,    12,   -26,     1,    13,     2,     3,     4,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     6,     7,
       0,     0,     8,     9,     0,    10,     0,     0,    11,     0,
       0,    12,   -25,     1,    13,     2,     3,     4,     5,     0,
       0,     0,     0,     2,    39,     0,     0,     6,     7,     0,
       0,     8,     9,     0,    10,     6,     7,    11,     0,     8,
      12,     0,    10,    13,     2,    39,    66,     0,    12,     2,
      42,    13,     0,     0,     0,     0,     6,     7,     0,     0,
       8,     6,     7,    10,     0,     8,     0,     0,    10,    12,
       0,     0,    13,     0,    12,     0,     0,    13
  };

  const signed char
  PCL_Parser::yycheck_[] =
  {
      16,     9,    47,    11,    34,    13,     6,     7,     1,     1,
      10,    99,     1,    17,    18,    21,    21,     0,     1,    23,
       3,     4,     5,     6,   112,    31,    31,    35,    36,    37,
      38,    30,    15,    16,    13,    14,    19,    20,    31,    22,
      32,    30,    25,    31,    74,    28,    15,    16,    31,     9,
      10,    11,    12,    29,    57,    58,    59,    60,    55,    56,
      61,    62,    78,    63,    64,    65,     0,    30,    30,     7,
      31,     8,    30,     0,     1,   120,     3,     4,     5,     6,
      96,    97,    98,    99,    32,    31,    33,    95,    15,    16,
      32,    32,    19,    20,     4,    22,    32,    32,    25,    24,
      33,    28,    34,     4,    31,   121,     1,     4,     3,     4,
       5,     6,    28,    53,    29,    54,   112,    -1,    -1,    -1,
      15,    16,    -1,    -1,    19,    20,    -1,    22,    -1,    -1,
      25,    -1,    -1,    28,    29,     1,    31,     3,     4,     5,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    -1,    -1,    19,    20,    -1,    22,    -1,    -1,    25,
      -1,    -1,    28,    29,     1,    31,     3,     4,     5,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,
      -1,    -1,    19,    20,    -1,    22,    -1,    -1,    25,    -1,
      -1,    28,    29,     1,    31,     3,     4,     5,     6,    -1,
      -1,    -1,    -1,     3,     4,    -1,    -1,    15,    16,    -1,
      -1,    19,    20,    -1,    22,    15,    16,    25,    -1,    19,
      28,    -1,    22,    31,     3,     4,    26,    -1,    28,     3,
       4,    31,    -1,    -1,    -1,    -1,    15,    16,    -1,    -1,
      19,    15,    16,    22,    -1,    19,    -1,    -1,    22,    28,
      -1,    -1,    31,    -1,    28,    -1,    -1,    31
  };

  const unsigned char
  PCL_Parser::yystos_[] =
  {
       0,     1,     3,     4,     5,     6,    15,    16,    19,    20,
      22,    25,    28,    31,    36,    37,    39,    40,    41,    42,
      43,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    30,    21,    31,     1,    31,    31,     4,
      58,    58,     4,    50,    58,    50,    29,    38,    50,     0,
      40,    30,    30,     7,     8,    13,    14,     9,    10,    11,
      12,    15,    16,    17,    18,    23,    26,    52,    50,    61,
      62,    50,    50,    50,    21,     1,    30,    30,    39,    32,
      53,    54,    55,    55,    56,    56,    56,    56,    57,    57,
      58,    58,    58,    31,    32,    33,    32,     1,    32,    32,
      29,     4,    46,    47,    50,    40,    40,    40,    40,    41,
      32,    33,    24,    34,    48,     4,    41,    42,     4,    28,
      44,    39,    45,    29
  };

  const unsigned char
  PCL_Parser::yyr1_[] =
  {
       0,    35,    36,    36,    37,    38,    37,    39,    39,    40,
      40,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    42,    42,    44,    43,    45,    45,    46,    46,    47,
      47,    48,    48,    49,    49,    49,    50,    51,    51,    52,
      52,    53,    53,    54,    54,    54,    55,    55,    55,    55,
      55,    56,    56,    56,    57,    57,    57,    57,    58,    58,
      58,    58,    59,    59,    59,    59,    59,    59,    60,    61,
      61,    62,    62
  };

  const unsigned char
  PCL_Parser::yyr2_[] =
  {
       0,     2,     0,     1,     2,     0,     4,     1,     2,     1,
       1,     2,     2,     1,     7,     1,     3,     3,     1,     2,
       3,     5,     7,     0,    11,     1,     0,     0,     1,     1,
       3,     0,     2,     5,     5,     5,     1,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     2,     1,     1,     1,     1,     3,     1,     4,     0,
       1,     1,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const PCL_Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "TNUM", "TID", "TWHILE", "TIF", "TOR",
  "TAND", "TLESS", "TGR", "TLESS_EQ", "TGR_EQ", "TEQUAL", "TNEQUAL",
  "TADD", "TSUB", "TMUL", "TDIV", "TINPUT", "TOUTPUT", "TASSIGN",
  "TEXCLAM", "TPERCENT", "TELSE", "TRETURN", "TFUNC", "TERR", "'{'", "'}'",
  "';'", "'('", "')'", "','", "':'", "$accept", "translation_unit",
  "block", "$@1", "statement_list", "statement", "matched_statement",
  "open_statement", "function_declaration", "$@2", "func_body",
  "arguments", "arguments_list", "name_form", "iteration_statement",
  "expression", "assignment_expression", "logical_or_expression",
  "logical_and_expression", "equality_expression", "relational_expression",
  "additive_expression", "multiplicative_expression", "unary_expression",
  "primary_expression", "function_call", "call_arguments",
  "expression_list", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  PCL_Parser::yyrline_[] =
  {
       0,    97,    97,    98,   105,   108,   107,   126,   131,   138,
     139,   143,   144,   145,   151,   156,   157,   158,   159,   160,
     161,   169,   174,   182,   181,   254,   255,   258,   259,   263,
     268,   275,   276,   280,   284,   288,   295,   299,   302,   316,
     317,   321,   322,   326,   327,   328,   332,   333,   334,   335,
     336,   340,   341,   342,   346,   347,   348,   349,   353,   354,
     355,   356,   360,   373,   374,   375,   376,   377,   381,   410,
     411,   415,   420
  };

  // Print the state stack on the debug stream.
  void
  PCL_Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  PCL_Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  PCL_Parser::token_number_type
  PCL_Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      31,    32,     2,     2,    33,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    34,    30,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    28,     2,    29,     2,     2,     2,     2,
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
      25,    26,    27
    };
    const unsigned int user_token_number_max_ = 282;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 2155 "src/parser/parser.cc" // lalr1.cc:1167
#line 427 "src/parser/parser.y" // lalr1.cc:1168

namespace yy {
PCL_Parser::token_type yylex(PCL_Parser::semantic_type* yylval, PCL_Parser::location_type* yylloc, PCL_Driver* driver)
{
  return driver -> yylex(yylval, yylloc);
}
void yy::PCL_Parser::error(const location_type& loc, const std::string& s) {
	++driver -> err_counter_;
	std::cerr << "\terror at line: " << loc << " : " << s << std::endl;
}
}
