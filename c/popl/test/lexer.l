%{ 
    /* defintions */
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include "y.tab.h"
%}

%%

ADD {yylval.key = 1; return ADD;}
SUBTRACT {yylval.key = 2; return SUBTRACT;}
MULTIPLY {yylval.key = 3; return MULTIPLY;}
DIVIDE {yylval.key = 4; return DIVIDE;}
LEFT {yylval.key = 1; return LEFT;}
RIGHT {yylval.key = 2; return RIGHT;}
UP {yylval.key = 3; return UP;}
DOWN {yylval.key = 4; return DOWN;}
ASSIGN {yylval.key = 5; return ASSIGN;}
TO {yylval.key = 6; return TO;}
VAR {yylval.key = 7; return VAR;}
IS {yylval.key = 8; printf("lexer IS %s\n", yytext); return IS;}
VALUE {yylval.key = 9; return VALUE;}
IN {yylval.key = 10; return IN;}
, {yylval.key = 11; return COMMA;}
"." {yylval.key = 12; return EOL;}

[0-9]+ {yylval.num = atoi(yytext); return NUMBER;}

[A-Za-z][0-9A-Za-z]* { yylval.varname = yytext; printf("lexer varname %s\n", yylval.varname); return VARNAME;}
[ \t\n]+ {}


%%

int yywrap() {return 1;}


ADD LEFT.