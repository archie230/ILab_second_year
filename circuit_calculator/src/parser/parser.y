%language "c++"

%defines
%define api.value.type {double}
%define parser_class_name {GraphParser}

%skeleton "lalr1.cc"

%param {Circuit::Parser& driver}

%code requires {
    namespace Circuit {
        class Parser;
    }
}

%code {
    #include "CircuitParser.hpp"

    namespace yy {
    	GraphParser::token_type
    	yylex(GraphParser::semantic_type* yylval, Circuit::Parser& driver);
    }
}

%token TVERTEX
%token TVOLTAGE
%token TRESISTANCE
%token TEDGE
%token TERR

%start input

%%
input :
	edge
| edge input
;

edge :
	TVERTEX[lhs] TEDGE TVERTEX[rhs] ',' TRESISTANCE ';'
{
	driver.add_edge($lhs, $rhs, $TRESISTANCE);
}
| TVERTEX[lhs] TEDGE TVERTEX[rhs] ',' TRESISTANCE ';' TVOLTAGE
{
	driver.add_edge($lhs, $rhs, $TRESISTANCE, $TVOLTAGE);
}
;

%%
namespace yy {
				GraphParser::token_type
				yylex(GraphParser::semantic_type* yylval, Circuit::Parser& driver)
				{
				  return driver.yylex(yylval);
				}

				void yy::GraphParser::error(const std::string& msg) {}
}