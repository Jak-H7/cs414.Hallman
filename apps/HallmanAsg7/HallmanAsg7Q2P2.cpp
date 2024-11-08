// File: HallmanAsg7Q2P2.cpp
// Author: Jackson Hallman
// Student Num: 00102945
// Email: jhallma5@my.athens.edu

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>


enum TokenType {
    LS, CD, CAT, PRINT, EXEC, SET, ECHO,
    VARIABLE, VALUE, FILENAME, FOLDERNAME,
    ROOT, SEPARATOR, EQUAL, UNKNOWN, END
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
    std::unordered_map<std::string, std::string> symbolTable;

public:
    Parser(const std::vector<Token> &tokens) : tokens(tokens), current(0) {}

    ASTNode* parse() {
        if (tokens.empty()) {
            throw std::runtime_error("No tokens to parse");
        }
        auto node = command();
        printSymbolTable();
        return node;
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
        } else if (currentToken().type == SET) {
            return setCommand();
        } else if (currentToken().type == ECHO) {
            return echoCommand();
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

    ASTNode* setCommand() {
        consume(SET);
        auto node = new ASTNode(SET);
        consume(VARIABLE);
        std::string varName = currentToken().value;
        consume(EQUAL);
        consume(VALUE);
        std::string varValue = currentToken().value;
        symbolTable[varName] = varValue;
        node->arguments.push_back(varName);
        node->arguments.push_back(varValue);
        return node;
    }

    ASTNode* echoCommand() {
        consume(ECHO);
        auto node = new ASTNode(ECHO);
        consume(VARIABLE);
        node->arguments.push_back(currentToken().value);
        return node;
    }

    void printSymbolTable() const {
        std::cout << "Symbol Table:\n";
        for (const auto& entry : symbolTable) {
            std::cout << entry.first << " = " << entry.second << "\n";
        }
    }
};

void printAST(const ASTNode* node) {
    std::cout << "Command: ";
    switch (node->command) {
        case LS: std::cout << "ls"; break;
        case CD: std::cout << "cd"; break;
        case CAT: std::cout << "cat"; break;
        case PRINT: std::cout << "print"; break;
        case EXEC: std::cout << "exec"; break;
        case SET: std::cout << "set"; break;
        case ECHO: std::cout << "echo"; break;
        default: std::cout << "unknown"; break;
    }
    std::cout << "\n";

    for (const auto& arg : node->arguments) {
        std::cout << "  Argument: " << arg << "\n";
    }
}

int main() {
    std::string command = "set $myVar = \"Hello\"";
    std::vector<Token> tokens = {
        Token(SET, "set"),
        Token(VARIABLE, "$