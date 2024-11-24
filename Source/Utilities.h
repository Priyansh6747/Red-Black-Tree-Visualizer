#ifndef RED_BLACK_TREE_VISUALIZER_UTILITIES_H
#define RED_BLACK_TREE_VISUALIZER_UTILITIES_H

#include <string>
#include <cctype>
#include <stdexcept>
#include <fstream>
#include "SaveManager.h"
#include "SaveHeap.h"

using namespace std;

int StringToInt(const std::string& str) {
    // Trim leading and trailing whitespace
    std::string trimmed = str;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r\f\v")); // Trim leading spaces
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r\f\v") + 1); // Trim trailing spaces

    // Check if the string is empty after trimming
    if (trimmed.empty()) {
        throw std::invalid_argument("Input string is empty or only contains whitespace.");
    }

    // Check if the string starts with a valid character ('-' or digit)
    if (trimmed[0] != '-' && !std::isdigit(trimmed[0])) {
        throw std::invalid_argument("Input string does not start with a valid numeric character.");
    }

    // Check the rest of the string for non-digit characters
    for (size_t i = 1; i < trimmed.size(); ++i) {
        if (!std::isdigit(trimmed[i])) {
            throw std::invalid_argument("Input string contains non-numeric characters.");
        }
    }

    // Convert the string to an integer using std::stoi with proper error handling
    try {
        return std::stoi(trimmed);
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument("Input string could not be converted to an integer.");
    } catch (const std::out_of_range&) {
        throw std::out_of_range("Input string represents a number out of range for int.");
    }
}


void OverWriteSaveManager(const SaveManager &obj, const string &IncludePath) {
    ofstream fp(IncludePath, ios::out | ios::binary);
    if (!fp) {
        cerr << "Failed to open file for writing: " << IncludePath << endl;
        return;
    }
    obj.serialize(fp);
    fp.close();
    if (fp.fail()) {
        cerr << "Error occurred while writing to file: " << IncludePath << endl;
    } else {
        cout << "Save successful to file: " << IncludePath << endl;
    }
}

void loadSaveManager(SaveManager& SM, const string& IncludePath) {
    ifstream fp(IncludePath, ios::in | ios::binary);
    if (!fp) {
        cerr << "Failed to open file for reading: " << IncludePath << endl;
        return;
    }
    SM.deserialize(fp);
    fp.close();
    if (fp.fail()) {
        cerr << "Error occurred while reading from file: " << IncludePath << endl;
    } else {
        cout << "Load successful from file: " << IncludePath << endl;
    }
}

void Save(TreeData& Tree,SaveManager& SM){
    SM.insert(Tree);
    Tree.clear();
}
#endif // RED_BLACK_TREE_VISUALIZER_UTILITIES_H
