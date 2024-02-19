%{
#include <stdlib.h>
#include <math.h>
#include "hexcalc.h"
#define BASE 10
char* endptr;

%}

%%

[a-z] { yylval.varindex = yytext[0] - 'a'; $
}
[0-9]+ { yylval.nvalue = atof(yytext);
return NUMBER;
}
[0-9]+"."[0-9]+?|"."[0-9]+? {yylval.nvalue = atof(yytext);

return NUMBER;
}

[ \t] ;
\n|. { return yytext[0];
}
%%

int yywrap() {
return 1;
}
