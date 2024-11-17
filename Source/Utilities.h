#ifndef RED_BLACK_TREE_VISUALIZER_UTILITIES_H
#define RED_BLACK_TREE_VISUALIZER_UTILITIES_H
#include <string>
#include <cctype>
#include <stdexcept>


int StringToInt(const std::string& str) {
    if (str.empty()) {
        throw std::invalid_argument("Input string is empty");
    }

    // Check if the string contains only numeric characters
    for (char c : str) {
        if (!isdigit(c)) {
            throw std::invalid_argument("Input string contains non-numeric characters");
        }
    }

    try {
        return std::stoi(str);  // Convert string to integer
    } catch (const std::out_of_range&) {
        throw std::out_of_range("Input string represents a number out of range for int");
    }
}

#endif //RED_BLACK_TREE_VISUALIZER_UTILITIES_H
