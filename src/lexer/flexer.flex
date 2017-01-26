%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
#include "tokens.hpp"

/* End the embedded code section. */
%}

letter [a-zA-Z]
alphanum [a-zA-Z0-9\-_/]
digit [0-9]
keyword int|unsigned|case|break|void|while|switch|default|if|else|float
operator "="|"<="|">="|"=="|"!="|">"|"<"|"||"|"&&"|"|"|"&"|"^"|";"

%%
[ ] {yylcolno++;}
[\t] {yylcolno++;}
[\n] {yylineno += 1; yylcolno = 1; yylsourcelino += 1; return Newline;}

%{/* FILENAME  */%}
^#" "{digit}+" "[\"]{alphanum}+[\.]{letter}+[\"] {yylsourcelino = 0;std::string s(yytext); yylfile = s.substr(s.find("\"")+1, s.size()-2); yylval.Text = yylfile; yylval.Class = "PreprocessorFile";return PreprocessorFile;}

%{/* KEYWORDS  */%}
{keyword}	{/*fprintf(stderr, "Keyword\n");*/ yylval.Class = "Keyword"; yylval.Text = std::string(yytext); return Keyword; }

%{/* CONSTANT */%}
{digit}+(\.)*{digit}* {/*fprintf(stderr, "Constant\n");*/ yylval.Class = "Constant"; yylval.Text = std::string(yytext); return Constant; }

%{/* IDENTIFIER  */%}
{letter}({letter}|{digit})* {/*fprintf(stderr, "Identifier\n");*/ yylval.Class = "Identifier"; yylval.Text = std::string(yytext); return Identifier; }

%{/* STRING LITERAL */%}
\".*\" {/*fprintf(stderr, StringLiteral"\n");*/ yylval.Class = "StringLiteral"; yylval.Text = std::string(yytext); return StringLiteral; }

%{/* OPERATORS  */%}
{operator}  {/*fprintf(stderr, "Operator\n");*/ yylval.Class = "Operator"; yylval.Text = std::string(yytext); return Operator; }

%{/* COMMENTS  */%}
\/\/.* {/* Ignore comments*/;}
\/\*(.*\n)*.*\*\/ {/* Ignore block comments*/;}

^"#include ".+ {/* Assume includes are correct */;}

^# {yylval.Class = "Preprocessor"; yylval.Text = std::string(yytext);return Preprocessor;}

. {fprintf(stderr, "Invalid\n"); yylval.Class = "Invalid"; yylval.Text = std::string(yytext); return Invalid;}

%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}
