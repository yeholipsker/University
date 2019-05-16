
%{
	#include <stdio.h>
	#include <iostream>
	#include <string>
	#include <string.h>
	#include <algorithm>
	#include <map>
	#include <cmath>
	#include <vector>
	using namespace std;
	int yylex();
	void yyerror(const char*);
	char buffer[1000];
	int pos1 = 0, pos2 = 0, exist = 0;
	map<string,int> vars;
	vector<pair<string,int> > mapvec;
%}

%token <str_val> T_OR
%token <str_val> T_AND
%token <str_val> T_EQ
%token <str_val> T_NE
%token <int_val> T_INT
%token <str_val> T_STRING
%token <str_val> T_SEARCH
%token <str_val> T_RANGE
%token <str_val> T_VARIABLE
%token <str_val> T_VAR
%type  <int_val> expr
%type  <str_val> str
%type  <str_val> map
%type  <str_val> keysVals

%left T_OR
%left T_AND
%nonassoc T_EQ
%nonassoc T_NE
%nonassoc T_SEARCH
%left '+' '-'
%nonassoc T_RANGE
%left '*' '/'
%nonassoc '['
%nonassoc ']'
%right '^'
%nonassoc '('
%nonassoc ')'
%left ','

%union{
	int		int_val;
	char*	str_val;
}

%%

lines:
			line		
		|	lines line
		;
line:
			expr '\n'						{printf("Expr = %d\n",$1);}
		|	str '\n'						{printf("Str = %s\n",$1);}
		|	assign '\n'						{}/*ignore*/
		|	map '\n'						{
												for(int i = 0; i < mapvec.size(); i++){
													cout << mapvec[i].first << " : " << mapvec[i].second << endl;
												}
												mapvec.clear();
											}
		;
		
assign:
			T_VAR T_VARIABLE '=' expr		{vars[string($2)] = $4;}
		;
expr:
			expr '-' expr					{$$ = $1 - $3;}
		|	expr '+' expr					{$$ = $1 + $3;}
		|	expr '^' expr					{$$ = pow($1, $3);}
		|	'-' expr						{$$ = - $2;}
		|	'+' expr						{$$ = + $2;}
		|	'(' expr ')'					{$$ = $2;}
		|	expr '*' expr					{$$ = $1 * $3;}
		|	expr '/' expr					{
												if($3 == 0){ 
													printf("Error - Zero Division\n");
													return 0;
												} else {
													$$ = $1 / $3;
												}
											}
		|	expr T_OR expr					{$$ = $1 || $3;}
		|	expr T_AND expr					{$$ = $1 && $3;}
		|	expr T_EQ expr					{$$ = $1 == $3;}
		|	expr T_NE expr					{$$ = $1 != $3;}
		|	map '[' str ']'					{
												for(int i = 0; i < mapvec.size(); i++){
													if(mapvec[i].first == string($3)){
														$$ = mapvec[i].second;
														exist = 1;
													}
												}
												if(!exist){
														printf("The key %s doesn't exist!\n",$3);
														return 0;
												}
											}
		|	str T_SEARCH str				{
												string str($1), str2($3);
												$$ = str.find(str2);
											}
		|	T_INT							{$$ = $1;}
		|	T_VARIABLE						{
												if(!vars.count(string($1))){
														printf("The variable %s doesn't exist!\n",$1);
														return 0;
													} else {
														$$ = vars[string($1)];
													}
											}
		;
str:
			T_STRING						{$$ = $1;}
		|	str '+' str 					{$$ = strcat($1,$3);}
		|	'(' str ')' 					{$$ = $2;}
		|	'<' expr '>' 					{	
												sprintf (buffer, "%d", $2);
												$$ = buffer;
											}
		|	'^' str 						{
												string str($2);
												reverse($2, $2 +strlen($2));
												$$ = $2;
											}
		|	str '[' expr ']'				{	
												if($3 < 0 || $3 >= strlen($1)){
													printf("Error – Index out of range!\n");
													return 0;
													} else {
														$1+=$3;
														$1[1] = 0;
														$$ = $1;
													}
											}
		|	str '[' expr T_RANGE expr ']' 	{	
												if($3 < 0 || $5 < 0 || $3 >= strlen($1) || $5 >= strlen($1)){
													printf("Error – Index out of range!\n");
													return 0;
													} else {
														string str($1 + $3, $5 - $3 + 1);
														$$ = strdup(str.c_str());
													}
											}
		;
map:
			'{' keysVals '}'				{}/*ignore*/
		|	'{' '}'							{}/*ignore*/
		;
keysVals: 
			T_VARIABLE ':' expr             {
												pair<string,int> pair1(string($1),$3);
												for(int i = 0; i < mapvec.size(); i++){
													if(mapvec[i].first == pair1.first){
														printf("The key %s already exist!\n",$1);
														return 0;
													}
												}
												mapvec.push_back(pair1);
											}
		|	keysVals ',' keysVals			{}/*ignore*/
		;

%%

void yyerror(const char* err){
	printf("Error: %s\n", err);
}

int main(){
	//yydebug = 1;
	yyparse();
}
