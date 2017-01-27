#include "tokens.hpp"

#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <string.h>
// Define the instance of the variable that is declared in the header
TokenValue yylval;
std::string yylfile;
std::string t;
std::cmatch cm;
int yylcolno = 1;
int yylsourcelino = 0;

int main() {
    std::map<std::string, int> sourceline;
    fprintf(stdout, "[\n");

    while (1) {
        TokenType type = (TokenType)yylex();
        if (type == Newline) {
            if (!((yylval.Class == "Preprocessor") |
            (yylval.Class == "PreprocFile"))) {
                yylsourcelino += 1;
            }
            continue;
        }
        if (type == Preprocessor) {
            // continue;
        }
        if (type == PreprocessorFile) {
            std::regex_search(yylval.Text.c_str(), cm, std::regex("\\b[0-9]+\\b"),
            std::regex_constants::match_default);
            sourceline[yylfile] = atoi(((std::string)cm[0]).c_str());
            yylsourcelino = sourceline[yylfile];
        }
        if (type == Invalid) {
            int y;
            std::cin >> y;
        }
        if (type == None) {
            fprintf(stdout, "{}\n");
            break;
        }
        fprintf(stdout, "{ \"Class\" : %-14s, Text : %-20s, \"StreamLine\" : %2d, "
        "\"SourceFile\" : %-15s, \"SourceLine\" : %d,  "
        "\"SourceCol\" : %d },\n",
        yylval.print_class().c_str(), yylval.print_text().c_str(), yylineno,
        yylfile.c_str(), yylsourcelino, yylcolno);
        yylcolno += yylval.Text.length();
    }
    fprintf(stdout, "]\n");
    return 0;
}
