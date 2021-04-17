%{ 
    /* defintions */
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include "y.tab.h"
%}

%option noyywrap

%%

"ADD" {return ADD;}
"SUBTRACT" {return SUBTRACT;}
"DIVIDE" {return DIVIDE;}
"MULTIPLY" {return MULTIPLY;}
"LEFT" {return LEFT;}
"RIGHT" {return RIGHT;}
"UP" {return UP;}
"DOWN" {return DOWN;}
"ASSIGN" {return ASSIGN;}
"TO" {return TO;}
"VAR" {return VAR;}
"IS" {return IS;}
"VALUE" {return VALUE;}
"IN" {return IN;}

[-][0-9]+|[0-9]+ {yylval.num=atoi(yytext); return NUMBER;}

[A-Za-z][0-9A-Za-z]* { yylval.name=yytext; return VARNAME;}


","     {return COMMA;}
"."     {return EOL;}

[\n]    {return NEWLINE;}

[ \t] {;}



%%

// int yywrap() {return 1;}