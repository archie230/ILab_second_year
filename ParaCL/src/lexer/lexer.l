%option c++
%option noyywrap
%option nodefault
%option yylineno

%{
#include "../parser/parser.hh"
using token_t = yy::PCL_Parser::token_type;
%}

START   \/\*
END     \*\/
SKIP    [ \t\n\v\r]+
NAME    [_[:alpha:]][_[:alnum:]]*
NUM     [-+]?([0])|([1-9][0-9]*)

%%

{SKIP}
\/\/(.*) ;

[(){};:,]               {return static_cast<token_t>(yytext[0]); }
"="                     {return token_t::TASSIGN;                }
"=="                    {return token_t::TEQUAL;                 }
"!="                    {return token_t::TNEQUAL;                }
"<"                     {return token_t::TLESS;                  }
"<="                    {return token_t::TLESS_EQ;               }
">"                     {return token_t::TGR;                    }
">="                    {return token_t::TGR_EQ;                 }
"||"                    {return token_t::TOR;                    }
"&&"                    {return token_t::TAND;                   }
"+"                     {return token_t::TADD;                   }
"-"                     {return token_t::TSUB;                   }
"*"                     {return token_t::TMUL;                   }
"/"                     {return token_t::TDIV;                   }
"?"                     {return token_t::TINPUT;                 }
"!"                     {return token_t::TEXCLAM;                }
"%"                     {return token_t::TPERCENT;               }
print                   {return token_t::TOUTPUT;                }
while                   {return token_t::TWHILE;                 }
if                      {return token_t::TIF;                    }
else                    {return token_t::TELSE;                  }
return                  {return token_t::TRETURN;                }
func                    {return token_t::TFUNC;                  }
{NAME}                  {return token_t::TID;                    }
{NUM}                   {return token_t::TNUM;                   }
.                       {return token_t::TERR;                   }

%%