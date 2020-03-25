#pragma once

enum TokenName {
    T_NUM      ,
    T_ID       ,
    T_WHILE    ,
    T_IF       ,
    T_OR       ,
    T_AND      ,
    T_LESS     ,
    T_GR       ,
    T_LESS_EQ  ,
    T_GR_EQ    ,
    T_EQUAL    ,
    T_NEQUAL   ,
    T_ADD      ,
    T_SUB      ,
    T_MUL      ,
    T_DIV      ,
    T_INPUT    ,
    T_OUTPUT   ,
    T_ASSIGN   ,
    T_STMLST   ,
    T_SCOPE    ,
    T_PERCENT  ,
    T_RETURN   ,
    T_FUNCDEC  ,
    T_FUNCCALL ,
    T_ARGLIST  ,
    T_EXPRLIST ,
    T_EXCLAM   ,
    T_FUNCTION_SCOPE,

    // tokens below used in interpretation phase
    T_SCOPEEND , // end of scope marker
    T_FUNCEND  , // end of function scope marker
    T_FUNCNAME ,
    T_RETURNPOINT,

    T_WHILE_CALC_EXPR,
    T_IF_CALC_EXPR,
    T_OUTPUT_CALC_EXPR,
    T_RETURN_CALC_EXPR,
    T_ASSIGN_CALC_EXPR
};