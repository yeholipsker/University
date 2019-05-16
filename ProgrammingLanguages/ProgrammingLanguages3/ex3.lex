
%{
	#include "ex3.tab.h"
%}
INT	[1-9][0-9]*|0
VARIABLE [a-zA-Z_][a-zA-Z0-9_]*
WS  [ \t]*
AND	"&&"
OR	"||"
EQ	"=="
NE	"!="
STRING 	\"[^"]*\"
SEARCH 	"=~"
RANGE	".."
VAR 	"var"
%%

{VAR}		{	
				return T_VAR;
			}
{VARIABLE}	{
				yylval.str_val = strdup(yytext);
				return T_VARIABLE;
			}
{INT}		{
				yylval.int_val = atoi(yytext);
				return T_INT;
			}
{OR}		{
				return T_OR;
			}
{AND}		{
				return T_AND;
			}
{EQ}		{
				return T_EQ;
			}
{NE}		{
				return T_NE;
			}
{STRING}	{
				yylval.str_val = strdup(yytext);
				yylval.str_val++;
				yylval.str_val[strlen(yylval.str_val)-1] = 0;
				return T_STRING;
			}
{SEARCH}	{
				return T_SEARCH;
			}
{RANGE}		{
				return T_RANGE;
			}

{WS}		/* ignore */
.			return yytext[0];
\n			return yytext[0];

%%

int yywrap(){
	return 1;
}
