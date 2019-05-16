	/*Name: Yehoshua Lipsker
	ID: 204038533
	Group: 89310-04
	Username: lipskey*/
%{
	char arr[2048] = {0};
	char *ptr = arr;
%}

PLUS	[+]+
MINUS	[-]+
RIGHT	[>]
LEFT	[<]
GETNUM	[,][0-9]+
GETCHAR [,].
PRINT 	[.]
SPACE   [ ]
ENTER	[\n]
	
%%

{PLUS}		{(*ptr)+=strlen(yytext);}
{MINUS}		{
				int temp = (*ptr)-strlen(yytext);
				if(temp < 0){
					printf("‫‪Invalid‬‬ ‫–‬ ‫‪command‬‬");
					return -1;
				}
				(*ptr)-=strlen(yytext);
			}
{RIGHT}		{
				if(ptr+1 > arr+2048){
					printf("‫‪Index‬‬ ‫‪Out‬‬ ‫‪Of‬‬ ‫‪Range‬‬");
					return -1;
				}
				++ptr;
			}
{LEFT}		{
				if(ptr < arr){
					printf("‫‪Index‬‬ ‫‪Out‬‬ ‫‪Of‬‬ ‫‪Range‬‬");
					return -1;
				}
				--ptr;
			}
{GETNUM}	{(*ptr) = atoi(yytext+1);}
{GETCHAR}	{(*ptr) = *(yytext+1);}
{PRINT}		{printf("%c",*ptr);}
{SPACE}		{}
{ENTER}		{}
.			{
				printf("‫‪Unknown‬‬ ‫‪command‬‬");
				return -1;
			}

%%

int yywrap(){
return 1;
}

int main(){
	yylex();
}