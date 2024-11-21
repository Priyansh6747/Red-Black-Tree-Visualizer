#ifndef RED_BLACK_TREE_VISUALIZER_UTILITIES_H
#define RED_BLACK_TREE_VISUALIZER_UTILITIES_H
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;
#include <string>
#include <stdexcept>
#include <cctype>
#include <iostream>

int StringToInt(const std::string& str) {
    if (str.empty()) {
        throw std::invalid_argument("Input string is empty");
    }

    std::string s = (str[0] == '-') ? str.substr(1) : str;

    // Check if the string contains only numeric characters
    for (char c : s) {
        if (!isdigit(c)) {
            throw std::invalid_argument("Input string contains non-numeric characters");
        }
    }

    try {
        int result = std::stoi(s);
        return (str[0] == '-') ? -result : result;  // Convert string to integer
    } catch (const std::out_of_range&) {
        throw std::out_of_range("Input string represents a number out of range for int");
    }
}


#endif //RED_BLACK_TREE_VISUALIZER_UTILITIES_H
