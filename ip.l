%{
#include "ip.tab.h"
extern int yylval;
%}

%%
[a-zA-Z]+ { yylval = *yytext; return id; } // Match identifiers (variables)
[0-9]+    { yylval = atoi(yytext); return digit; } // Match integers
[\t]      ; // Ignore tabs
\n        { return 0; } // Return 0 for new lines
.         { return yytext[0]; } // Return any other character
%%

int yywrap() {
    return 1;
}
