#include <iostream>

#include "astnode.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "calcexception.hpp"

int main() {
    // Lexer intialization:
    Lexer lexer(std::cin);

    // Parser initialization:
    Parser parser(lexer);

    try{
        // Create AST:
        ASTNode *ast = parser.parse();
        parser.checkbraces();
        if (ast) {
            std::cout << "Abstract syntax tree:" << std::endl;
            ast->print(std::cout);
        }
        if (parser.calcmode()){
            std::cout << "Result: ";
            std::cout << ast->value() << std::endl;
        }
        delete ast;
    }
    catch (const calcexception &exc){
        std::cout << "Calc error: " << exc.what() << std::endl;
        return -2;
    }
    catch (const std::exception &exc){
        std::cout << "General error: " << exc.what() << std::endl;
        return -1;
    }
    catch (...){
        std::cout << "Unknown error" << std:: endl;
        return -3;
    }
    return 0;
}
