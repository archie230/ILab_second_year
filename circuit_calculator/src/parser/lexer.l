%option c++
%option noyywrap
%option nodefault

%{
	#include "parser.hh"
	using token_t = yy::GraphParser::token_type;
%}

SKIP            [ \t\n\v\r]+
VERTEXNUM       [1-9][0-9]*
DOUBLE          [-+]?([0-9]*\.?[0-9]+|[0-9]+\.)

%%

{SKIP}
(","|";")               {return static_cast<token_t>(yytext[0]);}
{VERTEXNUM}             {return token_t::TVERTEX;               }
{DOUBLE}                {return token_t::TRESISTANCE;           }
"--"                    {return token_t::TEDGE;                 }
{DOUBLE}V               {return token_t::TVOLTAGE;              }
.                       {return token_t::TERR;                  }

%%
