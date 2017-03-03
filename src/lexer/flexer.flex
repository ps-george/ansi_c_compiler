%option noyywrap
%option nounput

%{
/* Bring in our declarations for token types and
   the col_inc(); yylval variable. */
#include "tokens.hpp"
#include "c_parser.tab.h"

#include <string.h>

int extract_lineno(char * yytext);
std::string extract_quoted(std::string s);
void col_inc();
void store(char * yytext);

%}

letter [a-zA-Z_]
alphanum [a-zA-Z0-9_]
digit [0-9]
num [1-9]
decimal {digit}*(\.){digit}+
hex 0[xX][a-fA-F0-9]+
oct 0[1-7]+
float (({decimal})([eE][+-]?{digit}+)?)|{num}+[eE][+-]?{digit}+
constsuffix u|l|U|L|ul|uL|Ul|UL

operator "="|"<="|">="|"=="|"!="|">"|"<"|"||"|"&&"|"|"|"&"|"^"|";"|"+"|"-"|"*"|"/"|"("|")"|"{"|"}"|"["|"]"|","|"."|"->"|"<<"|">>"|"~"|"!"|"\\"
filename "[\"]{filechar}+[\.]{letter}+[\"]
%%


auto      { col_inc(); store(yytext); return AUTO; }
break     { col_inc(); store(yytext); return BREAK; }
double    { col_inc(); store(yytext); return DOUBLE; }
else      { col_inc(); store(yytext); return ELSE; }
enum      { col_inc(); store(yytext); return ENUM; }
extern    { col_inc(); store(yytext); return EXTERN; }
float     { col_inc(); store(yytext); return FLOAT; }
for       { col_inc(); store(yytext); return FOR; }
goto      { col_inc(); store(yytext); return GOTO; }
if        { col_inc(); store(yytext); return IF; }
case      { col_inc(); store(yytext); return CASE; }
char      { col_inc(); store(yytext); return CHAR; }
const     { col_inc(); store(yytext); return CONST; }
continue  { col_inc(); store(yytext); return CONTINUE; }
default   { col_inc(); store(yytext); return DEFAULT; }
do        { col_inc(); store(yytext); return DO; }
int       { col_inc(); store(yytext); return INT; }
long      { col_inc(); store(yytext); return LONG; }
struct    { col_inc(); store(yytext); return STRUCT; }
switch    { col_inc(); store(yytext); return SWITCH; }
register  { col_inc(); store(yytext); return REGISTER; }
typedef   { col_inc(); store(yytext); return TYPEDEF; }
union     { col_inc(); store(yytext); return UNION; }
unsigned  { col_inc(); store(yytext); return UNSIGNED; }
void      { col_inc(); store(yytext); return VOID; }
volatile  { col_inc(); store(yytext); return VOLATILE; }
while     { col_inc(); store(yytext); return WHILE; }
return    { col_inc(); store(yytext); return RETURN; }
short     { col_inc(); store(yytext); return SHORT; }
signed    { col_inc(); store(yytext); return SIGNED; }
sizeof    { col_inc(); store(yytext); return SIZEOF; }
static    { col_inc(); store(yytext); return STATIC; }

{float}{constsuffix}? { col_inc(); store(yytext); return F_CONSTANT; }
({num}{digit}*|{hex}|{oct}|0){constsuffix}? { col_inc(); store(yytext); return I_CONSTANT; }
L?'(\\.|[^\\'])+' { col_inc(); store(yytext); return C_CONSTANT; }

{letter}{alphanum}* {/*fprintf(stderr, "Identifier\n");*/ col_inc(); store(yytext); return ID; }

L?\"([^\\\"]|\\.)*\" { col_inc(); store(&extract_quoted(std::string(yytext))[0]); return STRING; }

"="   { col_inc(); store(yytext); return '='; }
"<="  { col_inc(); store(yytext); return LE; }
">="  { col_inc(); store(yytext); return GE; }
"=="  { col_inc(); store(yytext); return EQ; }
"!="  { col_inc(); store(yytext); return NE; }
">"   { col_inc(); store(yytext); return GT; }
"<"   { col_inc(); store(yytext); return LT; }
"||"  { col_inc(); store(yytext); return LOR; }
"&&"  { col_inc(); store(yytext); return LAND; }
"?"   { col_inc(); store(yytext); return '?'; }
"!"   { col_inc(); store(yytext); return '!'; }
"~"   { col_inc(); store(yytext); return '~'; }
"|"   { col_inc(); store(yytext); return '|'; }
"&"   { col_inc(); store(yytext); return '&'; }
"^"   { col_inc(); store(yytext); return '^'; }
"+"   { col_inc(); store(yytext); return '+'; }
"-"   { col_inc(); store(yytext); return '-'; }
"*"   { col_inc(); store(yytext); return '*'; }
"/"   { col_inc(); store(yytext); return '/'; }
"%"   { col_inc(); store(yytext); return '%'; }
"("   { col_inc(); store(yytext); return '('; }
")"   { col_inc(); store(yytext); return ')'; }
"{"   { col_inc(); store(yytext); return '{'; }
"}"   { col_inc(); store(yytext); return '}'; }
"["   { col_inc(); store(yytext); return '['; }
"]"   { col_inc(); store(yytext); return ']'; }
";"   { col_inc(); store(yytext); return ';'; }
":"   { col_inc(); store(yytext); return ':'; }
","   { col_inc(); store(yytext); return ','; }
"."   { col_inc(); store(yytext); return '.'; }
"->"  { col_inc(); store(yytext); return ARROW; }
"<<"  { col_inc(); store(yytext); return LL; }
">>"  { col_inc(); store(yytext); return RR; }
"..." { col_inc(); store(yytext); return ELLIP; }
"++"  { col_inc(); store(yytext); return INCR; }
"--"  { col_inc(); store(yytext); return DECR; }
">>=" { col_inc(); store(yytext); return RRASS; }
"<<=" { col_inc(); store(yytext); return LLASS; }
"+="  { col_inc(); store(yytext); return ADDASS; }
"-="  { col_inc(); store(yytext); return SUBASS; }
"*="  { col_inc(); store(yytext); return MULASS; }
"/="  { col_inc(); store(yytext); return DIVASS; }
"%="  { col_inc(); store(yytext); return MODASS; }
"&="  { col_inc(); store(yytext); return ANDASS; }
"^="  { col_inc(); store(yytext); return XORASS; }
"|="  { col_inc(); store(yytext); return ORASS; }

\/\/.* { col_inc(); store(yytext); }
\/\*(.*\n)*.*\*\/ { col_inc(); store(yytext); }

^#include" ".+ { col_inc(); store(yytext); }

^#[^(\n)]* {yylsourcelino = extract_lineno(yytext)-1; yylfile = extract_quoted(std::string(yytext));}

[" "\t\v\f] {yylcolno++;}

[\n\r] {len = 0; yylineno += 1; yylcolno = 1; yylsourcelino +=1;}

. {col_inc(); store(yytext); return Invalid;}

%%

int extract_lineno(char * yytext){
  std::string s(yytext);
  std::size_t first = s.find(" ");
  std::size_t second = s.find(" ", first+1);
  // extract whats inbetween
  return stoi(s.substr(first, second-first),0);
}

std::string extract_quoted(std::string s){
  unsigned first;
  unsigned last;
  first = s.find("\""); first++;
  last = s.find_last_of("\"");
  s = s.substr(first, last - first);
  return s;
}
void col_inc(){
  yylcolno += len;
}

void store(char * yytext){
  yylval.raw = new std::string(yytext);
  len = yyleng;
}

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
    fprintf (stderr, "Error: %s\n Line no: %d Column: %d\n", s, yylsourcelino, yylcolno); /* s is the text that wasn't matched */
    exit(1);
}
