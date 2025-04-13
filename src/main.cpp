#include "token.h"
#include <cstdio>

extern FILE* yyin;
extern int yylex();
extern char* yytext;
extern int yyparse();
extern int yyerror();
extern int parser_result;
// extern int yydebug;

int main(void)
{
    const char* filename = "program.zz";
    yyin = fopen(filename, "r");
    if (!yyin) {
        printf("Could not open %s!\n", filename);
        return 1;
    }
    // yydebug = 1;

    // while (1) {
    //     // token_t t = yylex();
    //     int t = yylex();
    //     if (t == TOKEN_EOF)
    //         break;
    //     printf("token: %d   text: %s\n", t, yytext);
    // }
    // int token;
    // while ((token = yylex()) != TOKEN_EOF) {
    //     printf("Token: %d, Text: %s\n", token, yytext);
    // }
    // printf("Reached EOF\n");

    int ret = yyparse();
    if (ret == 0) {
        printf("Parse successful!\n");
    } else if (ret == 1) {
        printf("Parse error.\n");
    } else if (ret == 2) {
        printf("yyparse: Internal error.\n");
    }
    printf("Result: %d\n", parser_result);

    return 0;
}
