%{
#include "token.h"
extern int yylval;
%}
DIGIT [0-9]
%%
[ \t\n]       /* skip whitespace */
{DIGIT}+      { yylval = atoi(yytext); return TOKEN_INT; }
"+"           { return TOKEN_PLUS; }
"-"           { return TOKEN_MINUS; }
"*"           { return TOKEN_MUL; }
"/"           { return TOKEN_DIV; }
"("           { return TOKEN_LPAREN; }
")"           { return TOKEN_RPAREN; }
";"           { return TOKEN_SEMI; }
.             { return TOKEN_ERROR; }
<<EOF>>       { return TOKEN_EOF; }
%%
int yywrap() { return 1; }
