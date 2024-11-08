// File: HallmanAsg7Q2P1.cpp
// Author: Jackson Hallman
// Student Num: 00102945
// Email: jhallma5@my.athens.edu

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

enum TokenType {
    LS, CD, CAT, PRINT, EXEC, SET, ECHO,
    VARIABLE, VALUE, FILENAME, FOLDERNAME,
    ROOT, SEPARATOR, UNKNOWN, EQUAL, END
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string &val) : type(t), value(val) {}
};

bool isFilename(const std::string &str) {
    return std::regex_match(str, std::regex("^[a-zA-Z0-9]{1,8}\\.[a-zA-Z0-9]{3}$"));
}

bool isFolderName(const std::string &str) {
    return std::regex_match(str, std::regex("^[a-zA-Z0-9]{1,8}$"));
}

bool isVariable(const std::string &str) {
    return std::regex_match(str, std::regex("^\\$[a-zA-Z0-9]+$"));
}

std::vector<Token> tokenize(const std::string &command) {
    std::vector<Token> tokens;
    std::istringstream stream(command);
    std::string word;

    while (stream >> word) {
        if (word == "ls") {
            tokens.emplace_back(LS, word);
        } else if (word == "cd") {
            tokens.emplace_back(CD, word);
        } else if (word == "cat") {
            tokens.emplace_back(CAT, word);
        } else if (word == "print") {
            tokens.emplace_back(PRINT, word);
        } else if (word == "exec") {
            tokens.emplace_back(EXEC, word);
        } else if (word == "set") {
            tokens.emplace_back(SET, word);
        } else if (word == "echo") {
            tokens.emplace_back(ECHO, word);
        } else if (word == "=") {
            tokens.emplace_back(EQUAL, word);
        } else if (isVariable(word)) {
            tokens.emplace_back(VARIABLE, word);
        } else if (std::regex_match(word, std::regex("^\"[^\"]*\"$"))) { // String value
            tokens.emplace_back(VALUE, word);
        } else if (isFilename(word)) {
            tokens.emplace_back(FILENAME, word);
        } else if (isFolderName(word)) {
            tokens.emplace_back(FOLDERNAME, word);
        } else if (word == "\\") {
            tokens.emplace_back(ROOT, word);
        } else {
            tokens.emplace_back(UNKNOWN, word);
        }
    }

    return tokens;
}

void printTokens(const std::vector<Token> &tokens) {
    for (const auto &token : tokens) {
        std::cout << "Token(Type: " << token.type << ", Value: \"" << token.value << "\")\n";
    }
}

int main() {
    std::string command = "set $myVar = \"Hello\"";
    
    std::vector<Token> tokens = tokenize(command);
    printTokens(tokens);

    return 0;
}