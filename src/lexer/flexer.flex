%option noyywrap

%{
/* Bring in our declarations for token types and
   the col_inc(); yylval variable. */
#include "tokens.hpp"
#include "c_parser.tab.h"
#include <regex>
#include <string.h>

int extract_lineno(char * yytext){
  std::cmatch cm;
  std::regex_search(yytext, cm, std::regex("\\b[0-9]+\\b"), std::regex_constants::match_default);
  // return the first match, this is the linenumber
  return atoi(std::string(cm[0]).c_str());
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
  yylcolno += yylval.raw.length();
}

void store(char * t){
  yylval.raw = std::string(t);
}

%}

letter [a-zA-Z_]
alphanum [a-zA-Z0-9]
digit [0-9]
num [1-9]
decimal {digit}+(\.){digit}+
hex 0[xX][a-fA-F0-9]+
oct 0[1-7]+
float (({decimal})([eE][+-]?{digit}+)?)|{num}+[eE][+-]?{digit}+
constsuffix u|l|U|L|ul|uL|Ul|UL

operator "="|"<="|">="|"=="|"!="|">"|"<"|"||"|"&&"|"|"|"&"|"^"|";"|"+"|"-"|"*"|"/"|"("|")"|"{"|"}"|"["|"]"|","|"."|"->"|"<<"|">>"|"~"|"!"|"\\"
filename "[\"]{filechar}+[\.]{letter}+[\"]
%%
[ ] {yylcolno++;}
[\t] {yylcolno++;}
[\n] {yylineno += 1; yylcolno = 1; yylsourcelino +=1;}

%{/* KEYWORDS  */%}
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

%{/* CONSTANTS */%}
{float}{constsuffix}? { col_inc(); store(yytext); return FLOATC; }
0|{num}+|{hex}|{oct}{constsuffix}? { col_inc(); store(yytext); return INTC; }

%{/* IDENTIFIERS  */%}
{letter}{alphanum}* {/*fprintf(stderr, "Identifier\n");*/ col_inc(); store(yytext); return ID; }

%{/* STRING LITERAL - need to correctly find end of string i.e. not \" */%}
L?\"(\\.|[^\\"])*\" { col_inc(); yylval.raw = extract_quoted(std::string(yytext)); return STRING; }

%{/* OPERATORS  */%}
"="   { col_inc(); store(yytext); return ASGN; }
"<="  { col_inc(); store(yytext); return LE; }
">="  { col_inc(); store(yytext); return GE; }
"=="  { col_inc(); store(yytext); return EQ; }
"!="  { col_inc(); store(yytext); return NE; }
">"   { col_inc(); store(yytext); return GT; }
"<"   { col_inc(); store(yytext); return LT; }
"||"  { col_inc(); store(yytext); return LOR; }
"&&"  { col_inc(); store(yytext); return LAND; }
"|"   { col_inc(); store(yytext); return BOR; }
"&"   { col_inc(); store(yytext); return BAND; }
"^"   { col_inc(); store(yytext); return BXOR; }
"+"   { col_inc(); store(yytext); return PLUS; }
"-"   { col_inc(); store(yytext); return SUB; }
"*"   { col_inc(); store(yytext); return TIMES; }
"/"   { col_inc(); store(yytext); return DIV; }
"("   { col_inc(); store(yytext); return PLEFT; }
")"   { col_inc(); store(yytext); return PRIGHT; }
"{"   { col_inc(); store(yytext); return CPLEFT; }
"}"   { col_inc(); store(yytext); return CPRIGHT; }
"["   { col_inc(); store(yytext); return SPLEFT; }
"]"   { col_inc(); store(yytext); return SPRIGHT; }
";"   { col_inc(); store(yytext); return SEMI; }
","   { col_inc(); store(yytext); return COMMA; }
"."   { col_inc(); store(yytext); return DOT; }
"->"  { col_inc(); store(yytext); return ARROW; }
"<<"  { col_inc(); store(yytext); return LL; }
">>"  { col_inc(); store(yytext); return RR; }
"~"   { col_inc(); store(yytext); return BNOT; }
"!"   { col_inc(); store(yytext); return NOT; }
"\\"  { col_inc(); store(yytext); return BSLASH; }
"..." { col_inc();store(yytext);  return ELLIP; }
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

%{/* COMMENTS - Ignore them  */%}
\/\/.* { col_inc(); store(yytext); }
\/\*(.*\n)*.*\*\/ { col_inc(); store(yytext); }

^#include" ".+ { col_inc(); store(yytext); }

%{/* PREPROCESSOR  */%}
%{// Consume the whole line, and then update the referenced values %}
^#" "{digit}+" "\".*\"([ ]{digit})*\n {yylsourcelino = extract_lineno(yytext); yylfile = extract_quoted(std::string(yytext));}

%{// Anything else, return invalid/error %}
. {col_inc(); store(yytext); return Invalid;}

%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
    /*fprintf (stderr, "Flex Error: %s\n", s);*/ /* s is the text that wasn't matched */
    exit(1);
}
