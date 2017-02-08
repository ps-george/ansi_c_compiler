#include "tokens.hpp"
#include "c_parser.tab.h"

#include <iomanip>
#include <string.h>
// Define the instance of the variable that is declared in the header
YYSTYPE yylval;
std::string yylfile;
std::string t;
int yylcolno = 1;
int yylsourcelino = 1;

std::string quote(int i){
  std::string s = std::to_string(i);
  return "\"" + s + "\"";
}

std::string quote(std::string s){
  return "\"" + s + "\"";
}

std::string escape_chars(const std::string &before){
    std::string after;
    after.reserve(before.length() + 4);
    for (std::string::size_type i = 0; i < before.length(); ++i) {
        switch (before[i]) {
            // Replace tab character with \t
            case '\t':
              after += '\\';
              after += 't';
              break;
            // Replace newline character with \n - not sure if I need this for ANSI C
            case '\n':
              after += '\\';
              after += 'n';
              break;
            case '\r':
              after += '\\';
              after += 'r';
              break;
            case '\v':
              after += '\\';
              after += 'v';
              break;
            case '\f':
              after += '\\';
              after += 'f';
              break;
            case '\\': // If the next character is an n or t
              if (i+1 < before.length() && (before[i+1]=='n' || before[i+1]=='t' || before[i+1]=='r' || before[i+1]=='v' || before[i+1]=='f')){
                after += before[i];
                break;
              }
            case '\"':
                after += '\\';
                // Fall through.
            default:
                after += before[i];
        }
    }
    return after;
}

std::string classname(yytokentype t){
  switch((int)t){
  /* KEYWORDS */
    case AUTO:
    case BREAK:
    case DOUBLE:
    case ELSE:
    case ENUM:
    case EXTERN:
    case FLOAT:
    case FOR:
    case GOTO:
    case IF:
    case CASE:
    case CHAR:
    case CONST:
    case CONTINUE:
    case DEFAULT:
    case DO:
    case INT:
    case LONG:
    case STRUCT:
    case SWITCH:
    case REGISTER:
    case TYPEDEF:
    case UNION:
    case UNSIGNED:
    case VOID:
    case VOLATILE:
    case WHILE:
    case RETURN:
    case SHORT:
    case SIGNED:
    case SIZEOF:
    case STATIC: return "Keyword";
    /* Identifiers */
    case ID: return "Identifier";
     /* Operators */
    case '=':
    case '?':
    case '!':
    case '~':
    case '|':
    case '&':
    case '^':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case LE:
    case GE:
    case EQ:
    case NE:
    case GT:
    case LT:
    case LOR:
    case LAND:
    case SEMI:
    case COLON:
    case ',':
    case '.':
    case ARROW:
    case LL:
    case RR:
    case ELLIP:
    case INCR:
    case DECR:
    case RRASS:
    case LLASS:
    case ADDASS:
    case SUBASS:
    case MULASS:
    case DIVASS:
    case MODASS:
    case ANDASS:
    case XORASS:
    case ORASS:
    case '[':
    case ']':
    case '(':
    case ')':
    case '{':
    case '}': return "Operator";
    /* Constants */
    case CONSTANT: return "Constant";
    /* StringLiterals */
    case STRING: return "StringLiteral";
    //  Unncessary
    // case NEWLINE: return "Newline";
    case Invalid: return "Invalid";
    default: fprintf(stderr, "Invalid: %s, StreamLine: %s, ColNum: %s\n", yylval.raw.c_str(), quote(yylineno).c_str(), quote(yylcolno).c_str() ); return "Invalid";
  }
}
int main() {
  fprintf(stdout, "[\n");
  std::string Class;
  int tokens = 0;
  while (1) {
    yytokentype type = (yytokentype)yylex();
    if (!type) {
      break;
    }
    tokens++;
    Class = classname(type);
    // Replace 
    fprintf(stdout, "\t{\n\t\t\"Text\": %s,\n\t\t\"Class\": %s,\n\t\t\"StreamLine\": %s,\n\t\t\"SourceFile\": %s,\n\t\t\"SourceLine\": %s,\n\t\t\"SourceCol\": %s\n\t},\n",
            quote(escape_chars(yylval.raw)).c_str(),
            quote(Class).c_str(),
            std::to_string(yylineno).c_str(),
            quote(yylfile).c_str(),
            std::to_string(yylsourcelino).c_str(),
            std::to_string(yylcolno).c_str());
  }
  fprintf(stdout, "\t{}\n]\n");
  fprintf(stderr, "Number of tokens: %d", tokens);
  return 0;
}
