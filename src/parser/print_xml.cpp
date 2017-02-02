#include "ast.hpp"

int main()
{
    const Expression *ast=parseAST();

    ast->print_xml();
    std::cout<<std::endl;

    return 0;
}
