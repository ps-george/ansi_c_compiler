%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
#include "tokens.hpp"
#include  <regex>
#include <string.h>


int extract_lineno(char * yytext){
  std::cmatch cm;
  std::regex_search(yytext, cm, std::regex("\\b[0-9]+\\b"),
                        std::regex_constants::match_default);
  // return the first match, this is the linenumber
  return atoi(std::string(cm[0]).c_str());
}

std::string extract_quoted(std::string s){
  unsigned first;
  unsigned last;
  first = s.find("\""); first++;
  last = s.find_last_of("\"");
  s = s.substr(first, last - first);
  //fprintf(stderr,"%s\n", s.c_str());
  return s;
}
/*
TokenType get_token(std::string s){
  if (s == "auto"){
    return AUTO;
  }
}
*/


/* End the embedded code section. */
%}

letter [a-zA-Z_]
alphanum [a-zA-Z0-9]
filechar [a-zA-Z0-9_/-]
digit [0-9]
num [1-9]
decimal {digit}+(\.){digit}+
hex 0[xX][a-fA-F0-9]+
oct 0[1-7]+
float (({decimal})([eE][+-]?{digit}+)?)|{num}+[eE][+-]?{digit}+
constsuffix u|l|U|L|ul|uL|Ul|UL
keyword auto|break|double|else|enum|extern|float|for|goto|if|case|char|const|continue|default|do|int|long|struct|switch|register|typedef|union|unsigned|void|volatile|while|return|short|signed|sizeof|static
operator "="|"<="|">="|"=="|"!="|">"|"<"|"||"|"&&"|"|"|"&"|"^"|";"|"+"|"-"|"*"|"/"|"("|")"|"{"|"}"|"["|"]"|","|"."|"->"|"<<"|">>"|"~"|"!"|"\\"
filename "[\"]{filechar}+[\.]{letter}+[\"]
%%
[ ] {yylcolno++;}
[\t] {yylcolno++;}
[\n] {yylineno += 1; yylcolno = 1; yylsourcelino +=1;}

%{/* KEYWORDS  */%}
auto yylval.raw = std::string(yytext); return Keyword;
break yylval.raw = std::string(yytext); return Keyword;
double yylval.raw = std::string(yytext); return Keyword;
else yylval.raw = std::string(yytext); return Keyword;
enum yylval.raw = std::string(yytext); return Keyword;
extern yylval.raw = std::string(yytext); return Keyword;
float yylval.raw = std::string(yytext); return Keyword;
for yylval.raw = std::string(yytext); return Keyword;
goto yylval.raw = std::string(yytext); return Keyword;
if yylval.raw = std::string(yytext); return Keyword;
case yylval.raw = std::string(yytext); return Keyword;
char yylval.raw = std::string(yytext); return Keyword;
const yylval.raw = std::string(yytext); return Keyword;
continue yylval.raw = std::string(yytext); return Keyword;
default yylval.raw = std::string(yytext); return Keyword;
do yylval.raw = std::string(yytext); return Keyword;
int yylval.raw = std::string(yytext); return Keyword;
long yylval.raw = std::string(yytext); return Keyword;
struct yylval.raw = std::string(yytext); return Keyword;
switch yylval.raw = std::string(yytext); return Keyword;
register yylval.raw = std::string(yytext); return Keyword;
typedef yylval.raw = std::string(yytext); return Keyword;
union yylval.raw = std::string(yytext); return Keyword;
unsigned yylval.raw = std::string(yytext); return Keyword;
void yylval.raw = std::string(yytext); return Keyword;
volatile yylval.raw = std::string(yytext); return Keyword;
while yylval.raw = std::string(yytext); return Keyword;
return yylval.raw = std::string(yytext); return Keyword;
short yylval.raw = std::string(yytext); return Keyword;
signed yylval.raw = std::string(yytext); return Keyword;
sizeof yylval.raw = std::string(yytext); return Keyword;
static yylval.raw = std::string(yytext); return Keyword;

%{/* CONSTANTS */%}
{float}{constsuffix}? {fprintf(stderr, "Float\n"); yylval.raw = std::string(yytext); return FLOAT;}

{num}+|{hex}|{oct} {fprintf(stderr, "Integer\n"); yylval.raw = std::string(yytext); /*return Integer*/ return INTEGER;}

%{/* IDENTIFIERS  */%}
{letter}({letter}|{digit})* {/*fprintf(stderr, "Identifier\n");*/ yylval.raw = std::string(yytext); return Identifier; }

%{/* STRING LITERAL - need to correctly find end of string i.e. not \" */%}
\".*[^\\]\"|\".*\\\\\" {/*fprintf(stderr, StringLiteral"\n");*/ yylval.raw = extract_quoted(std::string(yytext)); return StringLiteral; }

%{/* OPERATORS  */%}
"=" yylval.raw = std::string(yytext); return ASGN;
"<=" yylval.raw = std::string(yytext); return LE;
">=" yylval.raw = std::string(yytext); return GE;
"==" yylval.raw = std::string(yytext); return EQ;
"!=" yylval.raw = std::string(yytext); return NE;
">" yylval.raw = std::string(yytext); return GT;
"<" yylval.raw = std::string(yytext); return LT;
"||" yylval.raw = std::string(yytext); return LOR;
"&&" yylval.raw = std::string(yytext); return LAND;
"|" yylval.raw = std::string(yytext); return BOR;
"&" yylval.raw = std::string(yytext); return BAND;
"^" yylval.raw = std::string(yytext); return BXOR;
"+" yylval.raw = std::string(yytext); return PLUS;
"-" yylval.raw = std::string(yytext); return MINUS;
"*" yylval.raw = std::string(yytext); return TIMES;
"/" yylval.raw = std::string(yytext); return DIV;
"(" yylval.raw = std::string(yytext); return PLEFT;
")" yylval.raw = std::string(yytext); return PRIGHT;
"{" yylval.raw = std::string(yytext); return CPLEFT;
"}" yylval.raw = std::string(yytext); return CPRIGHT;
"[" yylval.raw = std::string(yytext); return SPLEFT;
"]" yylval.raw = std::string(yytext); return SPRIGHT;
";" yylval.raw = std::string(yytext); return SEMI;
"," yylval.raw = std::string(yytext); return COMMA;
"." yylval.raw = std::string(yytext); return DOT;
"->" yylval.raw = std::string(yytext); return ARROW;
"<<" yylval.raw = std::string(yytext); return LL;
">>" yylval.raw = std::string(yytext); return RR;
"~" yylval.raw = std::string(yytext); return BNOT;
"!" yylval.raw = std::string(yytext); return  NOT;
"\\" yylval.raw = std::string(yytext); return BSLASH;

%{/* COMMENTS  */%}
\/\/.* {/* Ignore comments*/;}
\/\*(.*\n)*.*\*\/ {/* Ignore block comments*/;}

^#include" ".+ {/* Ignore includes */;}

%{/* PREPROCESSOR  */%}
%{// Consume the whole line, and then update the referenced values %}
^#" "{digit}+" "\".*\"([ ]{digit})*\n {yylsourcelino = extract_lineno(yytext); yylfile = extract_quoted(std::string(yytext));}

%{// Anything else, return invalid/error %}
. {fprintf(stderr, "Invalid: %s\n", yytext); yylval.raw = std::string(yytext); return Invalid;}

%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
    fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
    exit(1);
}


