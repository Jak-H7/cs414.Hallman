//File: HallmanAsg6Q3.cpp
//Author: Jackson Hallman
//Student Num: 00102945
//Email: jhallma5@my.athens.edu

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

enum TokenType {
    LS, CD, CAT, PRINT, EXEC,
    FILENAME, FOLDERNAME, ROOT,
    SEPARATOR, UNKNOWN, END
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string &val) : type(t), value(val) {}
};

struct ASTNode {
    TokenType command;
    std::vector<std::string> arguments;

    ASTNode(TokenType cmd) : command(cmd) {}
};

class Parser {
private:
    std::vector<Token> tokens;
    size_t current;

public:
    Parser(const std::vector<Token> &tokens) : tokens(tokens), current(0) {}

    ASTNode* parse() {
        if (tokens.empty()) {
            throw std::runtime_error("No tokens to parse");
        }
        return command();
    }

private:
    Token& currentToken() {
        return tokens[current];
    }

    void consume(TokenType expected) {
        if (currentToken().type == expected) {
            current++;
        } else {
            throw std::runtime_error("Unexpected token: " + currentToken().value);
        }
    }

    ASTNode* command() {
        if (currentToken().type == LS) {
            return lsCommand();
        } else if (currentToken().type == CD) {
            return cdCommand();
        } else if (currentToken().type == CAT) {
            return catCommand();
        } else if (currentToken().type == PRINT) {
            return printCommand();
        } else if (currentToken().type == EXEC) {
            return execCommand();
        }
        throw std::runtime_error("Invalid command: " + currentToken().value);
    }

    ASTNode* lsCommand() {
        consume(LS);
        auto node = new ASTNode(LS);
        return node;
    }

    ASTNode* cdCommand() {
        consume(CD);
        auto node = new ASTNode(CD);
        if (currentToken().type == ROOT || currentToken().type == FOLDERNAME) {
            node->arguments.push_back(currentToken().value);
            consume(currentToken().type);
        }
        return node;
    }

    ASTNode* catCommand() {
        consume(CAT);
        auto node = new ASTNode(CAT);
        consume(FILENAME);
        node->arguments.push_back(currentToken().value);
        return node;
    }

    ASTNode* printCommand() {
        consume(PRINT);
        auto node = new ASTNode(PRINT);
        consume(FILENAME);
        node->arguments.push_back(currentToken().value);
        return node;
    }

    ASTNode* execCommand() {
        consume(EXEC);
        auto node = new ASTNode(EXEC);
        consume(FILENAME);
        node->arguments.push_back(currentToken().value);
        return node;
    }
};

void printAST(const ASTNode* node, int indent = 0) {
    std::string indentStr(indent, ' ');
    std::cout << indentStr << "Command: ";
    switch (node->command) {
        case LS: std::cout << "ls"; break;
        case CD: std::cout << "cd"; break;
        case CAT: std::cout << "cat"; break;
        case PRINT: std::cout << "print"; break;
        case EXEC: std::cout << "exec"; break;
        default: std::cout << "unknown"; break;
    }
    std::cout << "\n";

    for (const auto& arg : node->arguments) {
        std::cout << indentStr << "  Argument: " << arg << "\n";
    }
}

int main() {
    std::string command = "cd \\folder1";
    std::vector<Token> tokens = {
        Token(CD, "cd"),
        Token(ROOT, "\\"),
        Token(FOLDERNAME, "folder1"),
        Token(END, "") 
    };

    try {
        Parser parser(tokens);
        ASTNode* ast = parser.parse();
        printAST(ast);
        delete ast; 
    } catch (const std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}