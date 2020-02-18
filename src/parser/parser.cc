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

#line 37 "frontend/src/parser/parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hh"

// User implementation prologue.

#line 51 "frontend/src/parser/parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 40 "frontend/src/parser/parser.y" // lalr1.cc:413

    #include "../PCL_Driver.hpp"
    using namespace AST;

    namespace yy {
    	PCL_Parser::token_type yylex(PCL_Parser::semantic_type* yylval, PCL_Parser::location_type* yylloc, PCL_Driver* driver);
    }

#line 62 "frontend/src/parser/parser.cc" // lalr1.cc:413


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
#line 148 "frontend/src/parser/parser.cc" // lalr1.cc:479

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

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 401 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 4: // TID

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 408 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 5: // TWHILE

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 415 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 6: // TIF

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 422 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 7: // TOR

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 429 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 8: // TAND

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 436 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 9: // TLESS

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 443 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 10: // TGR

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 450 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 11: // TLESS_EQ

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 457 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 12: // TGR_EQ

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 464 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 13: // TEQUAL

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 471 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 14: // TNEQUAL

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 478 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 15: // TADD

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 485 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 16: // TSUB

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 492 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 17: // TMUL

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 499 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 18: // TDIV

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 506 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 19: // TINPUT

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 513 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 20: // TOUTPUT

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 520 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 21: // TASSIGN

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 527 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 22: // TEXCLAM

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 534 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 23: // TPERCENT

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 541 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 24: // TELSE

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 548 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 25: // TERR

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 555 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 26: // '{'

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 562 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 27: // '}'

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 569 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 28: // ';'

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 576 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 29: // '('

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 583 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 30: // ')'

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 590 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 32: // translation_unit

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 597 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 33: // block

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 604 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 35: // statement_list

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 611 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 36: // statement

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 618 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 37: // matched_statement

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 625 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 38: // open_statement

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 632 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 39: // iteration_statement

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 639 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 40: // expression

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 646 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 41: // assignment_expression

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 653 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 42: // logical_or_expression

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 660 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 43: // logical_and_expression

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 667 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 44: // equality_expression

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 674 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 45: // relational_expression

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 681 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 46: // additive_expression

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 688 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 47: // multiplicative_expression

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 695 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 48: // unary_expression

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 702 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 49: // primary_expression

#line 75 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 709 "frontend/src/parser/parser.cc" // lalr1.cc:614
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
#line 90 "frontend/src/parser/parser.y" // lalr1.cc:859
    { driver -> root_ = nullptr; (yylhs.value) = nullptr; }
#line 948 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 3:
#line 91 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
			(yylhs.value) = nullptr;
			driver -> root_ = (yystack_[0].value);
                  }
#line 957 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 98 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; }
#line 963 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 5:
#line 101 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
		SAVED = TOP;
		TOP = new SymTbl::Table(TOP, ID++);
		driver -> symtbl_.add_tbl(TOP -> id_, TOP);
	}
#line 973 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 107 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                            if((yystack_[1].value)) {
                                (yystack_[1].value) -> SetType(TokenName::T_SCOPE);
                                /// setting table id to find it in interpretation phase
                                static_cast<ListNode*>((yystack_[1].value)) -> SetTable_id(TOP -> id_);
                            }
                            (yylhs.value) = (yystack_[1].value);
                            TOP = SAVED;
			}
#line 987 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 119 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                                (yylhs.value) = new ListNode(TokenName::T_STMLST);
                                static_cast<ListNode*>((yylhs.value)) -> push_kid((yystack_[0].value));
                              }
#line 996 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 124 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                                static_cast<ListNode*>((yystack_[1].value)) -> push_kid((yystack_[0].value));
                                (yylhs.value) = (yystack_[1].value);
                              }
#line 1005 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 131 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1011 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 132 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1017 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 136 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[1].value); }
#line 1023 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 137 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[1].value); }
#line 1029 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 138 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; }
#line 1035 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 141 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                                          	(yylhs.value) = new IfNode(TokenName::T_IF, (yystack_[4].value), (yystack_[2].value), (yystack_[0].value));
                                    	}
#line 1043 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 145 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1049 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 146 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1055 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 147 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_OUTPUT, nullptr, (yystack_[1].value)); }
#line 1061 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 148 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_OUTPUT, nullptr, (yystack_[1].value)); }
#line 1067 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 152 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                                        	(yylhs.value) = new IfNode(TokenName::T_IF, (yystack_[2].value), (yystack_[0].value));
                                  	}
#line 1075 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 157 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
						(yylhs.value) = new IfNode(TokenName::T_IF, (yystack_[4].value), (yystack_[2].value), (yystack_[0].value));
					}
#line 1083 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 163 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                                                    (yylhs.value) = new TwoKidsNode(TokenName::T_WHILE, (yystack_[2].value), (yystack_[0].value));
                                        	}
#line 1091 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 167 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
				 		    (yylhs.value) = nullptr;
				 		    delete (yystack_[2].value);
				 		    delete (yystack_[0].value);
                                       		}
#line 1101 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 173 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
  				 		    (yylhs.value) = nullptr;
						    delete (yystack_[2].value);
						    delete (yystack_[0].value);
  				 		}
#line 1111 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 181 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1117 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 185 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1123 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 188 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                                        (yylhs.value) = new TwoKidsNode(TokenName::T_ASSIGN, (yystack_[2].value), (yystack_[0].value));
                                        // if there is no same identifier add it to symtbl
                                        try {
                                        	TOP -> find(static_cast<IdNode*>((yystack_[2].value)) -> get_id());
                                        }
                                        catch(const std::out_of_range&) {
                                            TOP -> insert(static_cast<IdNode*>((yystack_[2].value)) -> get_id(), {(yystack_[0].value), yystack_[2].location, 0});
                                        }
                                    }
#line 1138 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 201 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1144 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 202 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_OR, (yystack_[2].value), (yystack_[0].value)); }
#line 1150 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 206 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1156 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 207 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_AND, (yystack_[2].value), (yystack_[0].value)); }
#line 1162 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 211 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1168 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 212 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_EQUAL, (yystack_[2].value), (yystack_[0].value)); }
#line 1174 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 213 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_NEQUAL, (yystack_[2].value), (yystack_[0].value)); }
#line 1180 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 217 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1186 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 218 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_LESS, (yystack_[2].value), (yystack_[0].value)); }
#line 1192 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 219 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_GR, (yystack_[2].value), (yystack_[0].value)); }
#line 1198 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 220 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_LESS_EQ, (yystack_[2].value), (yystack_[0].value)); }
#line 1204 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 221 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_GR_EQ, (yystack_[2].value), (yystack_[0].value)); }
#line 1210 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 225 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1216 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 226 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_ADD, (yystack_[2].value), (yystack_[0].value)); }
#line 1222 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 227 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_SUB, (yystack_[2].value), (yystack_[0].value)); }
#line 1228 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 231 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1234 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 232 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_MUL, (yystack_[2].value), (yystack_[0].value)); }
#line 1240 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 233 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_DIV, (yystack_[2].value), (yystack_[0].value)); }
#line 1246 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 234 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_PERCENT, (yystack_[2].value), (yystack_[0].value)); }
#line 1252 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 238 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1258 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 239 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_ADD, nullptr, (yystack_[0].value)); }
#line 1264 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 240 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_SUB, nullptr, (yystack_[0].value)); }
#line 1270 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 241 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new TwoKidsNode(TokenName::T_EXCLAM, nullptr, (yystack_[0].value)); }
#line 1276 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 245 "frontend/src/parser/parser.y" // lalr1.cc:859
    { // identifier at the right hand of assignment
	    try{
	    	TOP -> find(static_cast<IdNode*>((yystack_[0].value)) -> get_id());
	    } catch(const std::out_of_range&) {
	   	error(yystack_[0].location, "undeclarated variable " + static_cast<IdNode*>((yystack_[0].value)) -> get_id());
	    }
            (yylhs.value) = (yystack_[0].value);
        }
#line 1289 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 253 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 1295 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 254 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new INode(TokenName::T_INPUT); }
#line 1301 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 255 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[1].value); }
#line 1307 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;


#line 1311 "frontend/src/parser/parser.cc" // lalr1.cc:859
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


  const signed char PCL_Parser::yypact_ninf_ = -57;

  const signed char PCL_Parser::yytable_ninf_ = -4;

  const signed char
  PCL_Parser::yypact_[] =
  {
       3,    -4,   -57,    13,    12,     7,    90,    90,   -57,   110,
      90,    15,   110,    38,   -57,    11,   -57,   -57,   -57,   -57,
      19,   -57,    43,    47,    32,    53,    57,    26,   -57,   -57,
     -57,    90,   110,   110,   110,   -57,   -57,   -57,    20,   -57,
     -57,    82,    27,   -57,   -57,   -57,   -57,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      43,    46,     9,    50,   -57,   -57,    55,   -57,    47,    32,
      53,    53,    57,    57,    57,    57,    26,    26,   -57,   -57,
     -57,    82,    82,    82,    82,   -57,   -57,   -57,   -57,   -57,
      67,    82,   -57,   -57
  };

  const unsigned char
  PCL_Parser::yydefact_[] =
  {
       0,     0,    51,    50,     0,     0,     0,     0,    52,     0,
       0,     5,     0,     0,    16,     0,     7,     9,    10,    15,
       0,    24,    25,    27,    29,    31,    34,    39,    42,    46,
      13,     0,     0,     0,     0,    50,    47,    48,     0,    49,
       4,     0,     0,     1,     8,    12,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,     0,     0,     0,    18,    17,     0,    53,    28,    30,
      32,    33,    35,    36,    37,    38,    40,    41,    43,    44,
      45,     0,     0,     0,     0,     6,    23,    22,    21,    19,
       9,     0,    14,    20
  };

  const signed char
  PCL_Parser::yypgoto_[] =
  {
     -57,   -57,   -57,   -57,    58,   -15,   -56,     5,   -57,    83,
     -57,    72,    60,    52,    29,    69,    34,    -5,   -57
  };

  const signed char
  PCL_Parser::yydefgoto_[] =
  {
      -1,    13,    14,    41,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29
  };

  const signed char
  PCL_Parser::yytable_[] =
  {
      44,    36,    37,    -2,     1,    39,     2,     3,     4,     5,
      82,    -3,     1,    32,     2,     3,     4,     5,     6,     7,
      45,    64,     8,     9,    30,    10,     6,     7,    90,    11,
       8,     9,    12,    10,    31,    92,    34,    11,    43,    83,
      12,    33,    40,    57,    58,    49,    50,    46,    65,    59,
      47,    44,    78,    79,    80,    48,     1,    67,     2,     3,
       4,     5,    51,    52,    53,    54,    86,    87,    88,    89,
       6,     7,    55,    56,     8,     9,    81,    10,    70,    71,
      84,    11,    85,     1,    12,     2,     3,     4,     5,    76,
      77,    91,    38,     2,    35,    42,    93,     6,     7,    66,
      69,     8,     9,    60,    10,     6,     7,    68,    11,     8,
       0,    12,    10,     2,     3,    61,    62,    63,     0,    12,
      72,    73,    74,    75,     0,     6,     7,     0,     0,     8,
       0,     0,    10,     0,     0,     0,     0,     0,     0,    12
  };

  const signed char
  PCL_Parser::yycheck_[] =
  {
      15,     6,     7,     0,     1,    10,     3,     4,     5,     6,
       1,     0,     1,     1,     3,     4,     5,     6,    15,    16,
       1,     1,    19,    20,    28,    22,    15,    16,    84,    26,
      19,    20,    29,    22,    21,    91,    29,    26,     0,    30,
      29,    29,    27,    17,    18,    13,    14,    28,    28,    23,
       7,    66,    57,    58,    59,     8,     1,    30,     3,     4,
       5,     6,     9,    10,    11,    12,    81,    82,    83,    84,
      15,    16,    15,    16,    19,    20,    30,    22,    49,    50,
      30,    26,    27,     1,    29,     3,     4,     5,     6,    55,
      56,    24,     9,     3,     4,    12,    91,    15,    16,    41,
      48,    19,    20,    31,    22,    15,    16,    47,    26,    19,
      -1,    29,    22,     3,     4,    32,    33,    34,    -1,    29,
      51,    52,    53,    54,    -1,    15,    16,    -1,    -1,    19,
      -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29
  };

  const unsigned char
  PCL_Parser::yystos_[] =
  {
       0,     1,     3,     4,     5,     6,    15,    16,    19,    20,
      22,    26,    29,    32,    33,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      28,    21,     1,    29,    29,     4,    48,    48,    40,    48,
      27,    34,    40,     0,    36,     1,    28,     7,     8,    13,
      14,     9,    10,    11,    12,    15,    16,    17,    18,    23,
      42,    40,    40,    40,     1,    28,    35,    30,    43,    44,
      45,    45,    46,    46,    46,    46,    47,    47,    48,    48,
      48,    30,     1,    30,    30,    27,    36,    36,    36,    36,
      37,    24,    37,    38
  };

  const unsigned char
  PCL_Parser::yyr1_[] =
  {
       0,    31,    32,    32,    33,    34,    33,    35,    35,    36,
      36,    37,    37,    37,    37,    37,    37,    37,    37,    38,
      38,    39,    39,    39,    40,    41,    41,    42,    42,    43,
      43,    44,    44,    44,    45,    45,    45,    45,    45,    46,
      46,    46,    47,    47,    47,    47,    48,    48,    48,    48,
      49,    49,    49,    49
  };

  const unsigned char
  PCL_Parser::yyr2_[] =
  {
       0,     2,     0,     1,     2,     0,     4,     1,     2,     1,
       1,     2,     2,     2,     7,     1,     1,     3,     3,     5,
       7,     5,     5,     5,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     2,
       1,     1,     1,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const PCL_Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "TNUM", "TID", "TWHILE", "TIF", "TOR",
  "TAND", "TLESS", "TGR", "TLESS_EQ", "TGR_EQ", "TEQUAL", "TNEQUAL",
  "TADD", "TSUB", "TMUL", "TDIV", "TINPUT", "TOUTPUT", "TASSIGN",
  "TEXCLAM", "TPERCENT", "TELSE", "TERR", "'{'", "'}'", "';'", "'('",
  "')'", "$accept", "translation_unit", "block", "$@1", "statement_list",
  "statement", "matched_statement", "open_statement",
  "iteration_statement", "expression", "assignment_expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "primary_expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  PCL_Parser::yyrline_[] =
  {
       0,    90,    90,    91,    98,   101,   100,   119,   124,   131,
     132,   136,   137,   138,   140,   145,   146,   147,   148,   152,
     156,   163,   167,   173,   181,   185,   188,   201,   202,   206,
     207,   211,   212,   213,   217,   218,   219,   220,   221,   225,
     226,   227,   231,   232,   233,   234,   238,   239,   240,   241,
     245,   253,   254,   255
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
      29,    30,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    28,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,    27,     2,     2,     2,     2,
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
      25
    };
    const unsigned int user_token_number_max_ = 280;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1801 "frontend/src/parser/parser.cc" // lalr1.cc:1167
#line 258 "frontend/src/parser/parser.y" // lalr1.cc:1168

namespace yy {

PCL_Parser::token_type yylex(PCL_Parser::semantic_type* yylval, PCL_Parser::location_type* yylloc, PCL_Driver* driver)
{
  return driver -> yylex(yylval, yylloc);
}

void yy::PCL_Parser::error(const location_type& loc, const std::string& s) {
	++driver -> err_counter_;
	std::cerr << "	error at line: " << loc << " : " << s << std::endl;
}

}
