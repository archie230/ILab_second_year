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

    #define ID driver -> cur_id_
    #define TOP driver -> top_
    #define SAVED driver -> saved_

    // forward declaration for parser
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
  TERR
;

%destructor { delete $$; } <>
//%destructor { delete $$; } TID
//%destructor { delete $$; } TOUTPUT


// making grammar unambiguous
%left TADD TSUB
%left TMUL TDIV
%left TOR  TAND


%start translation_unit
%%

translation_unit :
    %empty { driver -> root_ = nullptr; $$ = nullptr; }
|  statement_list {
			$$ = nullptr;
			driver -> root_ = $1;
                  }
;

block :
  '{'  '}'  			{ $$ = nullptr; } // empty block optimization

| '{'
	{
		SAVED = TOP;
		TOP = new SymTbl::Table(TOP, ID++);
		driver -> symtbl_.add_tbl(TOP -> id_, TOP);
	}

 statement_list '}' 	{
                            if($statement_list) {
                                $statement_list -> SetType(TokenName::T_SCOPE);
                                /// setting table id to find it in interpretation phase
                                static_cast<ListNode*>($statement_list) -> SetTable_id(TOP -> id_);
                            }
                            $$ = $statement_list;
                            TOP = SAVED;
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
  expression ';'              { $$ = $1; }
| expression error	      { $$ = $1; }
| error ';'                   { $$ = nullptr; }

|   TIF '(' expression ')' matched_statement[body] TELSE matched_statement[else]
    					{
                                          	$$ = new IfNode(TokenName::T_IF, $expression, $body, $else);
                                    	}

| iteration_statement         { $$ = $1; }
| block                       { $$ = $1; }
| TOUTPUT expression ';'      { $$ = new TwoKidsNode(TokenName::T_OUTPUT, nullptr, $2); }
| TOUTPUT expression error    { $$ = new TwoKidsNode(TokenName::T_OUTPUT, nullptr, $2); }
;

open_statement :
  TIF '(' expression ')' statement  	{
                                        	$$ = new IfNode(TokenName::T_IF, $expression, $statement);
                                  	}

| TIF '(' expression ')' matched_statement[body] TELSE open_statement[else]
					{
						$$ = new IfNode(TokenName::T_IF, $expression, $body, $else);
					}
;

iteration_statement :
  TWHILE '(' expression ')' statement   	{
                                                    $$ = new TwoKidsNode(TokenName::T_WHILE, $expression, $statement);
                                        	}

| TWHILE '(' expression error statement 	{
				 		    $$ = nullptr;
				 		    delete $expression;
				 		    delete $statement;
                                       		}

| TWHILE error expression ')' statement 	{
  				 		    $$ = nullptr;
						    delete $expression;
						    delete $statement;
  				 		}
;

expression :
  assignment_expression { $$ = $1; }
;

assignment_expression :
  logical_or_expression             { $$ = $1; }

// chains like a = b = c aren't allowed
| TID TASSIGN logical_or_expression {
                                        $$ = new TwoKidsNode(TokenName::T_ASSIGN, $1, $3);
                                        // if there is no same identifier add it to symtbl
                                        try {
                                        	TOP -> find(static_cast<IdNode*>($TID) -> get_id());
                                        }
                                        catch(const std::out_of_range&) {
                                            TOP -> insert(static_cast<IdNode*>($TID) -> get_id(), {$3, @1, 0});
                                        }
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
  unary_expression  { $$ = $1; }
| multiplicative_expression TMUL unary_expression     { $$ = new TwoKidsNode(TokenName::T_MUL, $1, $3); }
| multiplicative_expression TDIV unary_expression     { $$ = new TwoKidsNode(TokenName::T_DIV, $1, $3); }
| multiplicative_expression TPERCENT unary_expression { $$ = new TwoKidsNode(TokenName::T_PERCENT, $1, $3); }
;

unary_expression :
  primary_expression        { $$ = $1; }
| TADD unary_expression     { $$ = new TwoKidsNode(TokenName::T_ADD, nullptr, $2); }
| TSUB unary_expression     { $$ = new TwoKidsNode(TokenName::T_SUB, nullptr, $2); }
| TEXCLAM unary_expression  { $$ = new TwoKidsNode(TokenName::T_EXCLAM, nullptr, $2); }
;

primary_expression :
  TID   { // identifier at the right hand of assignment
	    try{
	    	TOP -> find(static_cast<IdNode*>($TID) -> get_id());
	    } catch(const std::out_of_range&) {
	   	error(@1, "undeclarated variable " + static_cast<IdNode*>($TID) -> get_id());
	    }
            $$ = $TID;
        }
| TNUM                  { $$ = $1; }
| TINPUT                { $$ = new INode(TokenName::T_INPUT); }
| '(' expression ')'    { $$ = $2; }
;

%%
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