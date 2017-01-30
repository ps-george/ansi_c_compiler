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
/* End the embedded code section. */
%}

letter [a-zA-Z_]
alphanum [a-zA-Z0-9]
filechar [a-zA-Z0-9_/-]
digit [0-9]
keyword auto|break|double|else|enum|extern|float|for|goto|if|case|char|const|continue|default|do|int|long|struct|switch|register|typedef|union|unsigned|void|volatile|while|return|short|signed|sizeof|static
operator "="|"<="|">="|"=="|"!="|">"|"<"|"||"|"&&"|"|"|"&"|"^"|";"|"+"|"-"|"*"|"/"|"("|")"|"{"|"}"|"["|"]"|","|"."|"->"|"<<"|">>"|"~"|"!"|"\\"
filename "[\"]{filechar}+[\.]{letter}+[\"]
%%
[ ] {yylcolno++;}
[\t] {yylcolno++;}
[\n] {yylineno += 1; yylcolno = 1; yylsourcelino +=1;}

%{/* KEYWORDS  */%}
{keyword}	{/*fprintf(stderr, "Keyword\n");*/ yylval.raw = std::string(yytext); yylval.num = atoi(yytext); return Keyword;}

%{/* CONSTANT */%}
{digit}+(\.)*{digit}* {/*fprintf(stderr, "Constant\n");*/ yylval.raw = std::string(yytext); return Constant;}

%{/* IDENTIFIER  */%}
{letter}({letter}|{digit})* {/*fprintf(stderr, "Identifier\n");*/ yylval.raw = std::string(yytext); return Identifier; }

%{/* STRING LITERAL */%}
\".*\" {/*fprintf(stderr, StringLiteral"\n");*/ yylval.raw = extract_quoted(std::string(yytext)); return StringLiteral; }

%{/* OPERATORS  */%}
{operator}  {/*fprintf(stderr, "Operator\n");*/ yylval.raw = std::string(yytext); return Operator; }

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


