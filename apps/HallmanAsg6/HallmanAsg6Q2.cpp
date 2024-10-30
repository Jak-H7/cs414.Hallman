//File: HallmanAsg6Q2.cpp
//Author: Jackson Hallman
//Student Num: 00102945
//Email: jhallma5@my.athens.edu

#include <iostream>
#include <string>
#include <vector>
#include <regex>

enum TokenType {
    LS, CD, CAT, PRINT, EXEC,
    FILENAME, FOLDERNAME, ROOT,
    SEPARATOR, UNKNOWN
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
        } else if (word == "\\") {
            tokens.emplace_back(ROOT, word);
        } else if (isFilename(word)) {
            tokens.emplace_back(FILENAME, word);
        } else if (isFolderName(word)) {
            tokens.emplace_back(FOLDERNAME, word);
        } else if (word == "\\") {
            tokens.emplace_back(SEPARATOR, word);
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
    std::string command = "cd \\folder1 cat file.txt exec program.exe";
    
    std::vector<Token> tokens = tokenize(command);
    printTokens(tokens);

    return 0;
}