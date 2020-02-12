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
// Bison bad_outputs files to be licensed under the GNU General Public
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

#line 72 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 401 "frontend/src/parser/parser.cc" // lalr1.cc:614
        break;

      case 4: // TID

#line 73 "frontend/src/parser/parser.y" // lalr1.cc:614
        { delete (yysym.value); }
#line 408 "frontend/src/parser/parser.cc" // lalr1.cc:614
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
#line 85 "frontend/src/parser/parser.y" // lalr1.cc:859
    { driver -> root_ = nullptr; }
#line 647 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 3:
#line 86 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                    driver -> root_ = (yystack_[0].value);
                  }
#line 655 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 92 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; }
#line 661 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 5:
#line 95 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
		SAVED = TOP;
		TOP = new SymTbl::Table(TOP, ID++);
		driver -> symtbl_.add_tbl(TOP -> id_, TOP);
	}
#line 671 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 101 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                            if((yystack_[1].value)) {
                                (yystack_[1].value) -> SetType(TokenName::T_SCOPE);
                                /// setting table id to find it in interpretation phase
                                static_cast<ListNode*>((yystack_[1].value)) -> SetTable_id(TOP -> id_);
                            }
                            (yylhs.value) = (yystack_[1].value);
                            TOP = SAVED;
			}
#line 685 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 113 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                                (yylhs.value) = new ListNode(TokenName::T_STMLST);
                                static_cast<ListNode*>((yylhs.value)) -> push_kid((yystack_[0].value));
                              }
#line 694 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 118 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                                static_cast<ListNode*>((yystack_[1].value)) -> push_kid((yystack_[0].value));
                                (yylhs.value) = (yystack_[1].value);
                              }
#line 703 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 125 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[1].value); }
#line 709 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 126 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[1].value); }
#line 715 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 127 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; }
#line 721 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 128 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 727 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 129 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 733 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 130 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 739 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 131 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_OUTPUT, nullptr, (yystack_[1].value)); }
#line 745 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 132 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_OUTPUT, nullptr, (yystack_[1].value)); }
#line 751 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 136 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                                        	(yylhs.value) = new _2kidsNode(TokenName::T_IF, (yystack_[2].value), (yystack_[0].value));
                                  	}
#line 759 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 140 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
						(yylhs.value) = nullptr;
                                        	delete (yystack_[2].value);
                                        	delete (yystack_[0].value);
                                  	}
#line 769 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 146 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
						(yylhs.value) = nullptr;
						delete (yystack_[2].value);
						delete (yystack_[0].value);
					}
#line 779 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 154 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                                                    (yylhs.value) = new _2kidsNode(TokenName::T_WHILE, (yystack_[2].value), (yystack_[0].value));
                                        	}
#line 787 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 158 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
				 		    (yylhs.value) = nullptr;
				 		    delete (yystack_[2].value);
				 		    delete (yystack_[0].value);
                                       		}
#line 797 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 164 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
  				 		    (yylhs.value) = nullptr;
						    delete (yystack_[2].value);
						    delete (yystack_[0].value);
  				 		}
#line 807 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 172 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 813 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 176 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 819 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 178 "frontend/src/parser/parser.y" // lalr1.cc:859
    {
                                        (yylhs.value) = new _2kidsNode(TokenName::T_ASSIGN, (yystack_[2].value), (yystack_[0].value));
                                        // if there is no same identifier add it to symtbl
                                        auto p = TOP -> find(*(static_cast<IdNode*>((yystack_[2].value)) -> get_id()));
                                        if(!p)
                                            TOP -> insert(*(static_cast<IdNode*>((yystack_[2].value)) -> get_id()), {(yystack_[0].value), yystack_[2].location, 0});
                                    }
#line 831 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 188 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 837 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 189 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_OR, (yystack_[2].value), (yystack_[0].value)); }
#line 843 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 193 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 849 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 194 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_AND, (yystack_[2].value), (yystack_[0].value)); }
#line 855 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 198 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 861 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 199 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_EQUAL, (yystack_[2].value), (yystack_[0].value)); }
#line 867 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 200 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_NEQUAL, (yystack_[2].value), (yystack_[0].value)); }
#line 873 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 204 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 879 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 205 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_LESS, (yystack_[2].value), (yystack_[0].value)); }
#line 885 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 206 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_GR, (yystack_[2].value), (yystack_[0].value)); }
#line 891 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 207 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_LESS_EQ, (yystack_[2].value), (yystack_[0].value)); }
#line 897 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 208 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_GR_EQ, (yystack_[2].value), (yystack_[0].value)); }
#line 903 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 212 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 909 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 213 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_ADD, (yystack_[2].value), (yystack_[0].value)); }
#line 915 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 214 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_SUB, (yystack_[2].value), (yystack_[0].value)); }
#line 921 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 218 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 927 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 219 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_MUL, (yystack_[2].value), (yystack_[0].value)); }
#line 933 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 220 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_DIV, (yystack_[2].value), (yystack_[0].value)); }
#line 939 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 224 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 945 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 225 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_ADD, nullptr, (yystack_[0].value)); }
#line 951 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 226 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new _2kidsNode(TokenName::T_SUB, nullptr, (yystack_[0].value)); }
#line 957 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 230 "frontend/src/parser/parser.y" // lalr1.cc:859
    { // identifier at the right hand of assignment
	    auto p = TOP -> find(*(static_cast<IdNode*>((yystack_[0].value)) -> get_id()));
            if(!p)
            	error(yystack_[0].location, "undeclarated variable " + *(static_cast<IdNode*>((yystack_[0].value)) -> get_id()));
            (yylhs.value) = (yystack_[0].value);
        }
#line 968 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 236 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 974 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 237 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = new INode(TokenName::T_INPUT); }
#line 980 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 238 "frontend/src/parser/parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[1].value); }
#line 986 "frontend/src/parser/parser.cc" // lalr1.cc:859
    break;


#line 990 "frontend/src/parser/parser.cc" // lalr1.cc:859
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

        // Return failure if at end of correct_data.
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


  const signed char PCL_Parser::yypact_ninf_ = -15;

  const signed char PCL_Parser::yytable_ninf_ = -4;

  const signed char
  PCL_Parser::yypact_[] =
  {
       4,    20,   -15,    36,     0,    12,   109,   109,   -15,   117,
       1,   117,    31,   -15,    55,   -15,   -15,   -15,    14,   -15,
      65,    68,     8,    32,     2,    11,   -15,   -15,   -15,   109,
     117,   117,   117,   117,   -15,   -15,   -15,    15,   -15,   103,
      46,   -15,   -15,   -15,   -15,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,    65,    50,     5,
      52,    10,   -15,   -15,    79,   -15,    68,     8,    32,    32,
       2,     2,     2,     2,    11,    11,   -15,   -15,   103,   103,
     103,   103,   103,   103,   -15,   -15,   -15,   -15,   -15,   -15,
     -15
  };

  const unsigned char
  PCL_Parser::yydefact_[] =
  {
       0,     0,    48,    47,     0,     0,     0,     0,    49,     0,
       5,     0,     0,    14,     0,     7,    12,    13,     0,    23,
      24,    26,    28,    30,    33,    38,    41,    44,    11,     0,
       0,     0,     0,     0,    47,    45,    46,     0,     4,     0,
       0,     1,     8,    10,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,     0,    16,    15,     0,    50,    27,    29,    31,    32,
      34,    35,    36,    37,    39,    40,    42,    43,     0,     0,
       0,     0,     0,     0,     6,    22,    21,    20,    18,    19,
      17
  };

  const signed char
  PCL_Parser::yypgoto_[] =
  {
     -15,   -15,   -15,   -15,    47,   -14,   -15,   -15,     3,   -15,
      58,    43,    44,     6,    -3,     9,    -4,   -15
  };

  const signed char
  PCL_Parser::yydefgoto_[] =
  {
      -1,    12,    13,    39,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27
  };

  const signed char
  PCL_Parser::yytable_[] =
  {
      42,    30,    35,    36,    -2,     1,    79,     2,     3,     4,
       5,    82,    37,    32,    40,    43,    62,    53,    54,     6,
       7,    47,    48,     8,     9,    38,    31,    10,    55,    56,
      11,    41,    80,    58,    59,    60,    61,    83,    33,    44,
      63,    49,    50,    51,    52,    28,    70,    71,    72,    73,
      42,    76,    77,    68,    69,    -3,     1,    29,     2,     3,
       4,     5,    74,    75,    85,    86,    87,    88,    89,    90,
       6,     7,    45,    65,     8,     9,    46,    78,    10,    81,
       1,    11,     2,     3,     4,     5,    64,    57,    66,     0,
      67,     0,     0,     0,     6,     7,     0,     0,     8,     9,
       0,     0,    10,    84,     1,    11,     2,     3,     4,     5,
       0,     0,     2,    34,     0,     0,     0,     0,     6,     7,
       2,     3,     8,     9,     6,     7,    10,     0,     8,    11,
       0,     0,     6,     7,     0,    11,     8,     0,     0,     0,
       0,     0,     0,    11
  };

  const signed char
  PCL_Parser::yycheck_[] =
  {
      14,     1,     6,     7,     0,     1,     1,     3,     4,     5,
       6,     1,     9,     1,    11,     1,     1,    15,    16,    15,
      16,    13,    14,    19,    20,    24,    26,    23,    17,    18,
      26,     0,    27,    30,    31,    32,    33,    27,    26,    25,
      25,     9,    10,    11,    12,    25,    49,    50,    51,    52,
      64,    55,    56,    47,    48,     0,     1,    21,     3,     4,
       5,     6,    53,    54,    78,    79,    80,    81,    82,    83,
      15,    16,     7,    27,    19,    20,     8,    27,    23,    27,
       1,    26,     3,     4,     5,     6,    39,    29,    45,    -1,
      46,    -1,    -1,    -1,    15,    16,    -1,    -1,    19,    20,
      -1,    -1,    23,    24,     1,    26,     3,     4,     5,     6,
      -1,    -1,     3,     4,    -1,    -1,    -1,    -1,    15,    16,
       3,     4,    19,    20,    15,    16,    23,    -1,    19,    26,
      -1,    -1,    15,    16,    -1,    26,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    26
  };

  const unsigned char
  PCL_Parser::yystos_[] =
  {
       0,     1,     3,     4,     5,     6,    15,    16,    19,    20,
      23,    26,    29,    30,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    25,    21,
       1,    26,     1,    26,     4,    44,    44,    36,    24,    31,
      36,     0,    33,     1,    25,     7,     8,    13,    14,     9,
      10,    11,    12,    15,    16,    17,    18,    38,    36,    36,
      36,    36,     1,    25,    32,    27,    39,    40,    41,    41,
      42,    42,    42,    42,    43,    43,    44,    44,    27,     1,
      27,    27,     1,    27,    24,    33,    33,    33,    33,    33,
      33
  };

  const unsigned char
  PCL_Parser::yyr1_[] =
  {
       0,    28,    29,    29,    30,    31,    30,    32,    32,    33,
      33,    33,    33,    33,    33,    33,    33,    34,    34,    34,
      35,    35,    35,    36,    37,    37,    38,    38,    39,    39,
      40,    40,    40,    41,    41,    41,    41,    41,    42,    42,
      42,    43,    43,    43,    44,    44,    44,    45,    45,    45,
      45
  };

  const unsigned char
  PCL_Parser::yyr2_[] =
  {
       0,     2,     0,     1,     2,     0,     4,     1,     2,     2,
       2,     2,     1,     1,     1,     3,     3,     5,     5,     5,
       5,     5,     5,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     2,     2,     1,     1,     1,
       3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const PCL_Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "TNUM", "TID", "TWHILE", "TIF", "TOR",
  "TAND", "TLESS", "TGR", "TLESS_EQ", "TGR_EQ", "TEQUAL", "TNEQUAL",
  "TADD", "TSUB", "TMUL", "TDIV", "TINPUT", "TOUTPUT", "TASSIGN", "TERR",
  "'{'", "'}'", "';'", "'('", "')'", "$accept", "translation_unit",
  "block", "$@1", "statement_list", "statement", "selection_statement",
  "iteration_statement", "expression", "assignment_expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "primary_expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  PCL_Parser::yyrline_[] =
  {
       0,    85,    85,    86,    92,    95,    94,   113,   118,   125,
     126,   127,   128,   129,   130,   131,   132,   136,   140,   146,
     154,   158,   164,   172,   176,   178,   188,   189,   193,   194,
     198,   199,   200,   204,   205,   206,   207,   208,   212,   213,
     214,   218,   219,   220,   224,   225,   226,   230,   236,   237,
     238
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
      26,    27,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,     2,    24,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22
    };
    const unsigned int user_token_number_max_ = 277;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1480 "frontend/src/parser/parser.cc" // lalr1.cc:1167
#line 241 "frontend/src/parser/parser.y" // lalr1.cc:1168

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
