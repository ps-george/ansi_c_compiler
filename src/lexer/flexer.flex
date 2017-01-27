%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
#include "tokens.hpp"

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
[\n] {yylineno += 1; yylcolno = 1; return Newline;}

%{/* KEYWORDS  */%}
{keyword}	{/*fprintf(stderr, "Keyword\n");*/ yylval.Class = "Keyword"; yylval.Text = std::string(yytext); return Keyword; }

%{/* CONSTANT */%}
{digit}+(\.)*{digit}* {/*fprintf(stderr, "Constant\n");*/ yylval.Class = "Constant"; yylval.Text = std::string(yytext); return Constant; }

%{/* IDENTIFIER  */%}
{letter}({letter}|{digit})* {/*fprintf(stderr, "Identifier\n");*/ yylval.Class = "Identifier"; yylval.Text = std::string(yytext); return Identifier; }

%{/* STRING LITERAL */%}
\".*\" {/*fprintf(stderr, StringLiteral"\n");*/ yylval.Class = "StringLiteral"; yylval.Text = extract_quoted(std::string(yytext)); return StringLiteral; }

%{/* OPERATORS  */%}
{operator}  {/*fprintf(stderr, "Operator\n");*/ yylval.Class = "Operator"; yylval.Text = std::string(yytext); return Operator; }

%{/* COMMENTS  */%}
\/\/.* {/* Ignore comments*/;}
\/\*(.*\n)*.*\*\/ {/* Ignore block comments*/;}

^#include" ".+ {/* Assume includes are correct */;}

%{/* PREPROCESSOR  */%}

^#" "{digit}+" "[\"]{filechar}+[\.]{letter}+[\"](" "{digit})* {std::string s(yytext); yylfile = extract_quoted(s); yylval.Text = s; yylval.Class = "PreprocFile";return PreprocessorFile;}
^#.+ {yylval.Class = "Preprocessor"; yylval.Text = std::string(yytext);return Preprocessor;}

. {fprintf(stderr, "Invalid: %s\n", yytext); yylval.Class = "Invalid"; yylval.Text = std::string(yytext); return Invalid;}

%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
    fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
    exit(1);
}
