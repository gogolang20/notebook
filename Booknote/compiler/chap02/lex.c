%{
/* C Declanations */
#include "tokens.h"
#include "errormsg.h"

union
{
   int ival;
   string sval;
   double fval
} yylval;

int charPost = 1;

#define ADJ (EM_tokPos=charPos, charPost+=yyleng)
%}
/* Lex Definitions: */
digits [0-9]+
%%
if              {ADJ;   return IF;}
[z-z][a-z0-9]*  {ADJ; yylval.sval=String(yytext);
                        return ID;};
{digits}        {ADJ; yylval.ival=atoi(yytext);
                        return NUM;}
({digits}"."[0-9]*)|([0-9]*"."{digits}) {ADJ;
                yylval.fval=atof(yytext);
                return REAL;}
("--"[a-z]*"\n")|(" "|"\n"|"\t")+       {ADJ;}
                {ADJ; EM_error("illegal character");}
