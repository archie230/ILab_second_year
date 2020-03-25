%language "c++"

%defines
%define api.location.type {uint32_t}
%define api.value.type {AST::INode*}
%define parser_class_name {PCL_Parser}

%define parse.error verbose

%skeleton "lalr1.cc"
%param {yy::PCL_Driver* driver}

%code requires {
    #include "../AST.hpp"
    #include "../SymTbl.hpp"
    #include "../TokenNames.hpp"

    #define ENV         driver -> env_
    #define CUR_ID      driver -> cur_id_

    #define FUNC		SymTbl::Table::DECL_TYPE::FUNC
    #define VAR			SymTbl::Table::DECL_TYPE::VAR

    #define GET_ID(node_ptr)	static_cast<AST::IdNode*>(node_ptr) -> get_id()

    using IDec_t 	  = SymTbl::Table::IDec;
    using VarDec_t	= SymTbl::Table::VarDec;
    using FuncDec_t	= SymTbl::Table::FuncDec;


    /* forward declaration for parser */
    namespace yy {
        struct PCL_Driver;
    }

    #  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
        do                                                                  \
          if (N)                                                            \
            {                                                               \
              (Current)	       = YYRHSLOC (Rhs, 1);                         \
              (Current)        = YYRHSLOC (Rhs, N);                         \
            }                                                               \
          else                                                              \
            {                                                               \
              (Current)        = YYRHSLOC (Rhs, 0);                         \
            }                                                               \
        while (false)
}

%code {
    #include "../PCL_Driver.hpp"
    using namespace AST;

    namespace yy {
    	PCL_Parser::token_type yylex(PCL_Parser::semantic_type* yylval, PCL_Parser::location_type* yylloc, PCL_Driver* driver);
    }
}

%token
  TNUM
  TID
  TWHILE
  TIF
  TOR
  TAND
  TLESS
  TGR
  TLESS_EQ
  TGR_EQ
  TEQUAL
  TNEQUAL
  TADD
  TSUB
  TMUL
  TDIV
  TINPUT
  TOUTPUT
  TASSIGN
  TEXCLAM
  TPERCENT
  TELSE
  TRETURN
  TFUNC
  TERR
;

%destructor { delete $$; } <>


/* making grammar unambiguous */
%left TADD TSUB
%left TMUL TDIV
%left TOR  TAND


%start translation_unit
%%

translation_unit :
	%empty                { driver -> root_ = nullptr; $$ = nullptr; }
| statement_list        {
													$$ = nullptr;
													driver -> root_ = $1;
                        }
;

block :
  '{'  '}'  			{ $$ = nullptr; }

| '{'
	{
		ENV.push_front(new SymTbl::Table(ENV.front(), CUR_ID++));
		driver -> symtbl_.add_tbl(ENV.front() -> id_, ENV.front());
	}

 statement_list '}' 	{
                            if($statement_list) {
                                $statement_list -> SetType(TokenName::T_SCOPE);
                                /* setting table id to find it in interpretation phase*/
                                static_cast<ListNode*>($statement_list) -> SetTable_id(ENV.front() -> id_);
                            }

                            $$ = $statement_list;
                            ENV.pop_front();
											}
;

statement_list :
  statement                   {
                                $$ = new ListNode(TokenName::T_STMLST);
                                static_cast<ListNode*>($$) -> push_kid($1);
                              }

| statement_list statement    {
                                static_cast<ListNode*>($1) -> push_kid($2);
                                $$ = $1;
                              }
;

statement :
  matched_statement { $$ = $1; }
| open_statement    { $$ = $1; }
;

matched_statement :
  expression ';'                { $$ = $1; }
| error ';'                     { $$ = nullptr; }
| expression
{
 $$ = $1;
 if ($1 && $1 -> GetType() != T_SCOPE)
		error(@1, "forgot semicolon");
}
| TIF '(' expression ')' matched_statement[body] TELSE matched_statement[else]
{
	$$ = new IfNode(TokenName::T_IF, $expression, $body, $else);
}

| iteration_statement         { $$ = $1; }
| TOUTPUT expression ';'      { $$ = new TwoKidsNode(TokenName::T_OUTPUT, nullptr, $2); }
| TOUTPUT expression error    { $$ = new TwoKidsNode(TokenName::T_OUTPUT, nullptr, $2); }
| function_declaration 	      { $$ = $1; }
| function_declaration ';'    { $$ = $1; }
| TRETURN expression ';'      {
																if (ENV.size() == 1)
																	error(@1, "return is not inside function");
																$$ = new TwoKidsNode(TokenName::T_RETURN, nullptr, $2);
                              }
;

open_statement :        
  TIF '(' expression ')' statement
{
	$$ = new IfNode(TokenName::T_IF, $expression, $statement);
}

| TIF '(' expression ')' matched_statement[body] TELSE open_statement[else]
{
	$$ = new IfNode(TokenName::T_IF, $expression, $body, $else);
}
;

function_declaration :
  TID TASSIGN TFUNC '(' arguments ')' name_form '{'
{
	/* at interpretation phase there will be copy of this Table to locate var values*/
	ENV.push_front( new SymTbl::Table(ENV.front(), CUR_ID++) );
	driver -> symtbl_.add_tbl(ENV.front() -> id_, ENV.front());

	if (! (ENV[1] -> find(GET_ID($TID))) ) {
    ENV[1] -> insert(GET_ID($TID),
      new FuncDec_t {FUNC, @TID, ENV.front() -> id_});
	} else
			error(@1, "variable " + GET_ID($TID) + " already exists");

	if ($name_form) { /* in case func(x) : name {...}*/
		if (! (ENV[1] -> find(GET_ID($name_form))) ) {
			ENV.back() -> insert(GET_ID($name_form),
				new FuncDec_t {FUNC, @name_form, ENV.front() -> id_});
		} else
				error(@name_form, "variable " + GET_ID($name_form) + " already exists");
	}



	if ($arguments) { /* adding function arguments to it's scope*/
		IDec_t* decl = nullptr;

		auto local_decl  = static_cast<FuncDec_t*>(ENV[1] -> find(GET_ID($TID)));
		auto global_decl = $name_form ? static_cast<FuncDec_t*>(ENV[1] -> find(GET_ID($name_form))) : nullptr;

		for(int i = 0; i < static_cast<ListNode*>($arguments) -> size(); i++)
		    try {

					decl = new VarDec_t {VAR, @arguments, 0};
					ENV.front() -> insert(GET_ID((*static_cast<ListNode*>($arguments))[i]), decl);

					(local_decl -> arg_names_).push_back(GET_ID((*static_cast<ListNode*>($arguments))[i]));
					if(global_decl)
						(global_decl -> arg_names_).push_back(GET_ID((*static_cast<ListNode*>($arguments))[i]));

		    } catch(...) {
					delete decl;
					error(@1, "variable " + GET_ID((*static_cast<ListNode*>($arguments))[i]) + " already exists");
		    }
	}

}
    func_body '}'
{

	if ($func_body) {
	   $func_body -> SetType(TokenName::T_FUNCTION_SCOPE);
	   static_cast<ListNode*>($func_body) -> SetTable_id(ENV.front() -> id_);
	}

	static_cast<FuncDec_t*>(ENV[1] -> find(GET_ID($TID))) -> function_body_ = $func_body;

	if ($name_form) {
		static_cast<FuncDec_t*>(ENV[1] -> find(GET_ID($name_form))) -> function_body_ = $func_body;
		delete $name_form;
	}

	ENV.pop_front();

	 /*there is no point in saving that, because we added all variables in symtable
	 and saved their names*/
	delete $arguments;

	$$ = new TwoKidsNode(TokenName::T_FUNCDEC, $TID, $func_body);
}
;

func_body :
	statement_list        { $$ = $1; }
| %empty                { $$ = nullptr; }

arguments:
  %empty 		{ $$ = nullptr; }
| arguments_list 	{ $$ = $1; }
;

arguments_list :
  TID				{
  				      $$ = new ListNode(TokenName::T_ARGLIST);
  				      static_cast<ListNode*>($$) -> push_kid($TID);
						}

| arguments_list ',' TID 	{
													  static_cast<ListNode*>($1) -> push_kid($TID);
													  $$ = $1;
											    }
;

name_form :
  %empty	{ $$ = nullptr; }
| ':' TID	{ $$ = $TID; }
;

iteration_statement :
  TWHILE '(' expression ')' statement   	{
                                                    $$ = new TwoKidsNode(TokenName::T_WHILE, $expression, $statement);
                                        	}

| TWHILE '(' expression error statement 	{
						                                        $$ = new TwoKidsNode(TokenName::T_WHILE, $expression, $statement);
                                       		}

| TWHILE error expression ')' statement 	{
						                                        $$ = new TwoKidsNode(TokenName::T_WHILE, $expression, $statement);
																					}

;

expression :
  assignment_expression { $$ = $1; }
;

assignment_expression :
  logical_or_expression             { $$ = $1; }

/* chains like a = b = c aren't allowed*/
| TID TASSIGN logical_or_expression {
                                        $$ = new TwoKidsNode(TokenName::T_ASSIGN, $1, $3);
                                        IDec_t* decl = nullptr;
                                        /* if there is no same identifier add it to symtbl*/
                                        if ( !(decl = (ENV.front() -> find(GET_ID($TID)))) ) {
						                              VarDec_t* elem = new VarDec_t {VAR, @1, 0};
																					ENV.front() -> insert(GET_ID($TID), elem);
                                        } else
                                          if (ENV.front() -> find(GET_ID($TID)) -> type_ == FUNC)
                                              error(@1, "can't assign smth to function name to " + GET_ID($TID));
                                    }
;

logical_or_expression :
  logical_and_expression    { $$ = $1; }
| logical_or_expression TOR logical_and_expression  { $$ = new TwoKidsNode(TokenName::T_OR, $1, $3); }
;

logical_and_expression :
  equality_expression   { $$ = $1; }
| logical_and_expression TAND equality_expression   { $$ = new TwoKidsNode(TokenName::T_AND, $1, $3); }
;

equality_expression	:
  relational_expression { $$ = $1; }
| equality_expression TEQUAL relational_expression  { $$ = new TwoKidsNode(TokenName::T_EQUAL, $1, $3); }
| equality_expression TNEQUAL relational_expression { $$ = new TwoKidsNode(TokenName::T_NEQUAL, $1, $3); }
;

relational_expression :
  additive_expression   { $$ = $1; }
| relational_expression TLESS additive_expression       { $$ = new TwoKidsNode(TokenName::T_LESS, $1, $3); }
| relational_expression TGR additive_expression         { $$ = new TwoKidsNode(TokenName::T_GR, $1, $3); }
| relational_expression TLESS_EQ additive_expression    { $$ = new TwoKidsNode(TokenName::T_LESS_EQ, $1, $3); }
| relational_expression TGR_EQ additive_expression      { $$ = new TwoKidsNode(TokenName::T_GR_EQ, $1, $3); }
;

additive_expression :
  multiplicative_expression { $$ = $1; }
| additive_expression TADD multiplicative_expression    { $$ = new TwoKidsNode(TokenName::T_ADD, $1, $3); }
| additive_expression TSUB multiplicative_expression    { $$ = new TwoKidsNode(TokenName::T_SUB, $1, $3); }
;

multiplicative_expression :
  unary_expression  					                          { $$ = $1; }
| multiplicative_expression TMUL unary_expression     	{ $$ = new TwoKidsNode(TokenName::T_MUL, $1, $3); }
| multiplicative_expression TDIV unary_expression     	{ $$ = new TwoKidsNode(TokenName::T_DIV, $1, $3); }
| multiplicative_expression TPERCENT unary_expression 	{ $$ = new TwoKidsNode(TokenName::T_PERCENT, $1, $3); }
;

unary_expression :
  primary_expression        { $$ = $1; }
| TADD unary_expression     { $$ = new TwoKidsNode(TokenName::T_ADD, nullptr, $2); }
| TSUB unary_expression     { $$ = new TwoKidsNode(TokenName::T_SUB, nullptr, $2); }
| TEXCLAM unary_expression  { $$ = new TwoKidsNode(TokenName::T_EXCLAM, nullptr, $2); }
;

primary_expression :
  TID
{
				IDec_t* decl = nullptr;

				if(!(decl = ENV.front() -> find(GET_ID($TID)))) {
					error(@1, "undeclarated variable " + GET_ID($TID));
				} else {
					if(decl -> type_ == FUNC)
						error (@1, GET_ID($TID) + " isn't a name of variable ");
				}

		    $$ = $TID;
}
| function_call 	{ $$ = $1;}
| TNUM                  { $$ = $1; }
| TINPUT                { $$ = new INode(TokenName::T_INPUT); }
| '(' expression ')'    { $$ = $2; }
| block                 { $$ = $1; }
;

function_call :
  TID '(' call_arguments ')' 	{
					IDec_t* decl = nullptr;

					if ( !(decl = ENV.front() -> find(GET_ID($TID))) )
						error(@1, "undeclarated function " + GET_ID($TID));
					else {
						if (decl && decl -> type_ == VAR)
						    error(@1, GET_ID($TID) + " isn't a function name");

					  int arg_num = $call_arguments ? static_cast<ListNode*>($3) -> size() : 0;

            if (arg_num != (static_cast<FuncDec_t*>(decl) -> arg_names_).size())
		            error(@1, "in function call " + GET_ID($TID) +
			             "(..) arguments number doesn't match with declaration");
					}

/*//					lhs of FUNCCALL node is list of exprs, like arg_name = expression
					if ($call_arguments && driver -> err_counter_ == 0) {
						ListNode& call_args = *static_cast<ListNode*>($call_arguments);
						for(int i = 0; i < call_args.size(); i++)
							call_args[i] = new TwoKidsNode(TokenName::T_ASSIGN,
							 new IdNode(T_ID, static_cast<FuncDec_t*>(decl) -> arg_names_[i]), call_args[i]);
					}*/

					$$ = new TwoKidsNode(TokenName::T_FUNCCALL, $TID, $call_arguments);
}
;

call_arguments :
  %empty		{ $$ = nullptr; }
| expression_list	{ $$ = $1;}
;

expression_list :
  expression                   	{
                                	$$ = new ListNode(TokenName::T_EXPRLIST);
                                	static_cast<ListNode*>($$) -> push_kid($1);
                              	}

| expression_list ',' expression
																{
                                	static_cast<ListNode*>($1) -> push_kid($3);
                                	$$ = $1;
                              	}
;

%%
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