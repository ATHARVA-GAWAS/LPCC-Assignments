%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // often required

// A simple error message to move things along
void yyerror(const char *msg)
{
printf("ERROR(PARSER): %s\n", msg);
}

// Storage for variables: yes Virginia, only 26 variables possible in this langu$
long variables[26];
%}

%union {
float nvalue;
int ivalue;
int varindex;
}

%token <nvalue> NUMBER
%token <ivalue> INT
%token <varindex> NAME
%type <nvalue> expr
%type <nvalue> term
%type <nvalue> varOrNum
%%
statementList : statement '\n'
| statement '\n' statementList
;

statement : NAME '=' expr { variables[$1] = $3; }
| expr { printf("RESULT: %f\n", $1); }
;

expr: expr '+' term { $$ = $1 + $3; }
| expr '-' term { $$ = $1 - $3; }
| '-' term { $$ = 0 - $2; }

| "abs(" expr ')' { $$ = $2; }
| "sqrt(" expr ')' { $$ = sqrt($2); }
| expr '/' term { $$ = $1 / $3; }

| term { $$ = $1; }
;

term : term '*' varOrNum { $$ = $1 * $3; }

| varOrNum { $$ = $1; }
;

varOrNum : NUMBER { $$ = $1; }
| NAME { $$ = variables[$1]; }
;

%%

main() {
int i;
for (i=0; i<26; i++) variables[i] = 0;
yyparse();
}
