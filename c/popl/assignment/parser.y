%{
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "game.h"

int yylex();


void yyerror(char *s) {
    printf("syntax error\n");
    fprintf(stderr, "-1\n");
}

State *state;


char* var_names[4][4][100] ;

int idx[4][4];


%}


%union {
  int num;
  char *name;
};

%start prog


%type <num> val x opertion direction statement all error_stat



%token <name> VARNAME
%token <num> NUMBER
%token <num> ADD SUBTRACT MULTIPLY DIVIDE LEFT RIGHT UP DOWN ASSIGN TO VAR IS VALUE IN EOL COMMA NEWLINE

%%

prog : statement  prog
|   /* NULL */
;


statement: opertion direction EOL NEWLINE{ make_move($1,$2); printf("2048> Thanks, move done, random tile added.\n2048> The current state is :\n"); print_stderr(0), print_board(); YYACCEPT;}
|          VAR VARNAME IS x COMMA x EOL NEWLINE { add_var_name($2,$4-1,$6-1); YYACCEPT;}
|          ASSIGN val TO x COMMA x EOL NEWLINE {assign_value($2, $4-1, $6-1); YYACCEPT;}
|          VALUE IN x COMMA x EOL NEWLINE {int a = get_value($3-1,$5-1); if(a !=-1){printf("2048> The value is %d\n",a);}; YYACCEPT;}
|           error_stat {YYACCEPT;}
;

opertion: ADD { $$ = 1;}
|         SUBTRACT {$$ = 2;}
|         MULTIPLY {$$ = 3;}
|         DIVIDE {$$ = 4;}
;

direction: LEFT { $$ = 1;}
|          RIGHT { $$ = 2;}
|          UP { $$ = 3;}
|          DOWN { $$ = 4;}
;

val: NUMBER 
|    VALUE IN x COMMA x {$$ = get_value_val($3-1,$5-1);}
;


x: NUMBER ;

error_stat: all error_stat
|           all {print_stderr(1); printf("syntax error\n");}
;

all:    ADD | SUBTRACT | MULTIPLY | DIVIDE | LEFT | RIGHT | UP | DOWN | ASSIGN | TO | VAR | IS | VALUE | IN | EOL | NUMBER | COMMA | VARNAME { $$ = 0; };

%%

void print_stderr(int code)
{
    if(code==0)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(i==3 &&j==3)
                {
                    fprintf(stderr,"%d",state->board[i][j]);
                }
                else
                {
                    fprintf(stderr,"%d ",state->board[i][j]);
                }
            }
        }
        int count=0;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(idx[i][j]>0)
                {
                    if(count==0)
                    {
                        fprintf(stderr," ");
                        count+=1;
                    }
                    fprintf(stderr,"%d,%d",i+1,j+1);
                    for(int k=0;k<idx[i][j];k++)
                    {
                        if(k==(idx[i][j]-1))
                        {
                            fprintf(stderr,"%s",var_names[i][j][k]);
                        }
                        else
                        {
                            fprintf(stderr,"%s,",var_names[i][j][k]);
                        }
                    }
                    fprintf(stderr," ");
                }
            }
        }
        fprintf(stderr,"\n");
    }
    else
    {
        fprintf(stderr,"-1\n");
    }
}

void print_var_names()
{
    for(int i=0;i<4;i++)
    {
        for( int j=0;j<4;j++)
        {
            if(idx[i][j]>0)
            {
                printf("%d,%d ",i+1,j+1);
                for(int k=0;k<idx[i][j];k++)
                {
                    printf("%s, ",var_names[i][j][k]);
                }
                printf("\n");
            }
            
        }
    }
}


void add_var_name(char *name, int x, int y)
{
    
    if(state->board[x][y]==0)
    {
        printf("Cannot Add Variable at empty tile\n");
        print_stderr(1);
    }
    else{
        char *tok=strtok(name," ");
        name=tok;
    
        var_names[x][y][idx[x][y]]= (char *)malloc(strlen(name) * sizeof(char));
    
        sscanf(name,"%s",var_names[x][y][idx[x][y]++]);
        print_stderr(0);
        printf("2048> Thanks, naming done.\n");
    }
    
}

void transpose()
{
    //  printf("///////////////////////1/////////////////////\n");
    int new_board[4][4];
    char* new_var_names[4][4][100] ;
    int new_indx[4][4];

    for(int i = 0; i<4;i++)
    {
        for(int j=0; j<4; j++)
        {
            new_board[j][i] = state -> board[i][j];
            new_indx[j][i]=idx[i][j];
            for(int k=0;k<idx[i][j];k++)
            {
                new_var_names[j][i][k]=(char * )malloc(strlen(var_names[i][j][k])*sizeof(char));
                strcpy(new_var_names[j][i][k],var_names[i][j][k]);
            }
        }
    }
    // print_var_names();
    
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<idx[i][j];k++)
            {
                free(var_names[i][j][k]);
            }
            idx[i][j]=0;
        }
    }

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            state -> board[i][j] = new_board[i][j];

            for(int k=0;k<new_indx[i][j];k++)
            {
                var_names[i][j][k]=(char *)malloc(strlen(new_var_names[i][j][k])*sizeof(char));
                strcpy(var_names[i][j][k],new_var_names[i][j][k]);
            }
            idx[i][j]=new_indx[i][j];
        }
    }

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<new_indx[i][j];k++)
            {
                free(new_var_names[i][j][k]);
            }
            // idx[i][j]=0;
        }
    }
}

void reverse()
{
    int temp;
    for(int i=0;i<4;i++)
    {
        int temp;
        int start=0;
        int end=3;
        while(start<end)
        {
            temp= state->board[i][start];
            state->board[i][start] = state->board[i][end];
            state->board[i][end] = temp;

            char* temp[100];
            int tempindx=idx[i][start];

            for(int k=0;k<idx[i][start];k++)
            {
                temp[k] =(char *)malloc(strlen(var_names[i][start][k])*sizeof(char));
                strcpy(temp[k],var_names[i][start][k]);
            }
            
            for(int k=0;k<idx[i][start];k++)
            {
                free(var_names[i][start][k]);
            }
            idx[i][start]=0;

            for(int k=0; k<idx[i][end];k++)
            {
                var_names[i][start][k]=(char *)malloc(strlen(var_names[i][end][k])*sizeof(char));
                strcpy(var_names[i][start][k],var_names[i][end][k]);
            }
            idx[i][start]=idx[i][end];

            for(int k=0;k<idx[i][end];k++)
            {
                free(var_names[i][end][k]);
            }

            for(int k=0;k<tempindx;k++)
            {
                var_names[i][end][k]=(char * )malloc(strlen(temp[k])*sizeof(char));
                strcpy(var_names[i][end][k],temp[k]);
            }
            idx[i][end]=tempindx;

            for(int k=0;k<tempindx;k++)
            {
                free(temp[k]);
            }
            start++;end--;
        }
    }
}   

void left_merge(int operation)
{
    // print_board();
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<3;j++)
        {
            if((state->board[i][j]==state->board[i][j+1]) && state->board[i][j]!=0)
            {
                int n=0;
                switch(operation)
                {
                    case 1: n=state->board[i][j]*2;
                                            break;
                    case 2: n=0;
                                            break;                    
                    case 3: n=state->board[i][j]*state->board[i][j];
                                            break;                    
                    case 4: n=1;
                                            break;
                }
                state->board[i][j]=n;
                state->board[i][j+1]=0;
                int b=idx[i][j+1];
                for( int k=0;k<b;k++)
                {
                    var_names[i][j][idx[i][j]]= (char *)malloc(strlen(var_names[i][j+1][k]) * sizeof(char));
                    strcpy(var_names[i][j][idx[i][j]++],var_names[i][j+1][k]);
                }
                idx[i][j+1]=0;
                if(state->board[i][j]==0)
                {
                    for(int k=0;k<idx[i][j];k++)
                    {
                        free(var_names[i][j][k]);
                    }
                    idx[i][j]=0;
                }
            }
        }
    }
}

void left_compress()
{
    
    int new_board[4][4];
    char* new_var_names[4][4][100] ;
    int new_indx[4][4];

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            new_indx[i][j]=0;
            new_board[i][j]=0;
        }

    }
    

    for(int i=0;i<4;i++)
    {
        int count = 0;
        for(int j=0;j<4;j++)
        {
            if(state->board[i][j])
            {
                new_board[i][count]=state->board[i][j];


                for(int k=0;k<idx[i][j];k++)
                {
                    new_var_names[i][count][k]=(char *)malloc(strlen(var_names[i][j][k]) * sizeof(char));
                    strcpy(new_var_names[i][count][k],var_names[i][j][k]);
                }
                // idx[i][j]=0;
                new_indx[i][count]=idx[i][j];
                count++;
            }

        }
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<idx[i][j];k++)
            {
                free(var_names[i][j][k]);
            }
            idx[i][j]=0;
        }
    }

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            state->board[i][j]=new_board[i][j];

            for(int k=0;k<new_indx[i][j];k++)
            {
                var_names[i][j][k]=(char *)malloc(strlen(new_var_names[i][j][k]) * sizeof(char));
                strcpy(var_names[i][j][k],new_var_names[i][j][k]);
            }
            // var_names[i][j]=new_var_names[i][j];
            idx[i][j] =new_indx[i][j];
        }

    }
    
}


void left_move(int operation)
{
    left_compress();
    left_merge(operation);
    left_compress();
}

void right_move(int operation)
{
    reverse();
    left_compress();
    left_merge(operation);
    left_compress();
    reverse();
}

void up_move(int operation)
{
    transpose();
    left_compress();
    left_merge(operation);
    left_compress();
    transpose();
}

void down_move(int operation)
{
    
    transpose();
    reverse();
    left_compress();
    left_merge(operation);
    left_compress();
    reverse();
    transpose();
    
}



void make_move(int operation, int direction)
{
    switch(direction)
    {
        case 1: left_move(operation);
                                      break;
        case 2: right_move(operation);
                                      break;
        case 3: up_move(operation);
                                      break;
        case 4: down_move(operation);
                                      break;                                                                            
    }

    add_random();

}

void assign_value(int value, int x, int y)
{
    if(x>3 | y>3 | x<0 | y<0)
    {
        printf("Index out of range");
        print_stderr(1);
    }
    else{
        if(value<0)
        {
            printf("Value not Valid\n");
            print_stderr(1);
        }
        else
        {
            state->board[x][y]=value;
            printf("2048> Thanks, assignment done.\n");
            if(value==0)
            {
                for(int k=0;k<idx[x][y];k++)
                {
                    free(var_names[x][y][k]);
                }
                idx[x][y]=0;
            }
            print_stderr(0);
            print_board(); print_var_names(); 
        }

    }
    
}

int get_value( int x, int y)
{
    if(x>3 | y>3 | x<0 | y<0)
    {
        printf("Index out of range\n");
        print_stderr(1);
        return -1;
    }
    else{
        // print_stderr(0);
        return state->board[x][y];
    }
}

int get_value_val( int x, int y)
{
    if(x>3 | y>3 | x<0 | y<0)
    {
        printf("Index out of range\n");
        // print_stderr(1);
        return -1;
    }
    else{
        // print_stderr(0);
        return state->board[x][y];
    }
}

void add_random()
{
    int x,y;
    int list[16][2];
    int len=0;

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(state->board[i][j]==0)
            {
                list[len][0]=i;
                list[len][1]=j;
                len++;
            }
        }
    }

    if(len>0){
        int r = rand()%len;
        x=list[r][0];
        y=list[r][1];
        int n= (rand() % 10) ? 2 : 4;
        state->board[x][y]=n;
    }
}

void initialize()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            state->board[i][j]=0;
        }
    }

    add_random();

}


void print_board()
{
    printf("_________________\n");
    for(int i=0;i<4;i++)
    {
        printf("|");
        for(int j=0;j<4;j++)
        {
            if(state->board[i][j])
            {
                printf(" %d |",state->board[i][j]);
            }
            else
            {
                printf("   |");
            }
        }
        printf("\n");
        printf("_________________\n");
    }
}

int main()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            idx[i][j]=0;
        }
    }
    state = (State * )(malloc(sizeof(State)));
    initialize(state);
    printf("2048> Hi, I am the 2048-game Engine.\n2048> The start state is:\n");
    print_board(state);

    while(1)
    {
        printf("2048> Please type a command.\n----> ");
        yyparse();
    }

  return 0;
}