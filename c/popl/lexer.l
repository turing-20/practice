%{ 
    /* defintions */
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    // #include "popl_bison.h"
    #include "y.tab.h"
%}

%%

"ADD" {printf("lexer add\n"); yylval.key = yytext; return ADD;}
SUBTRACT {yylval.key = yytext; return SUBTRACT;}
MULTIPLY {yylval.key = yytext; return MULTIPLY;}
DIVIDE {yylval.key = yytext; return DIVIDE;}
"LEFT" {printf("lexer left\n"); yylval.key = yytext; return LEFT;}
RIGHT {yylval.key = yytext; return RIGHT;}
UP {yylval.key = yytext; return UP;}
DOWN {yylval.key = yytext; return DOWN;}
ASSIGN {yylval.key = yytext; return ASSIGN;}
TO {yylval.key = yytext; return TO;}
VAR {yylval.key = yytext; return VAR;}
IS {yylval.key = yytext; return IS;}
VALUE {yylval.key = yytext; return VALUE;}
IN {yylval.key = yytext; return IN;}
, {yylval.key = yytext ;return COMMA;}
[.](1) {yylval.key = yytext ;return EOL;}

[0-9]+ {yylval.num = atoi(yytext); printf("%d\n", yylval.num); return NUMBER;}

[A-Za-z][0-9A-Za-z]* {yylval.varname = yytext; return VARNAME;}

[ \t\n] {printf("lexer whitespace\n");}
.+ {printf("random\n");}
%%

int yywrap() {return 1;}