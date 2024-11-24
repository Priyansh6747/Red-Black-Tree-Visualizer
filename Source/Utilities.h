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
    if (str.empty()) {
        throw std::invalid_argument("Input string is empty");
    }

    std::string s = (str[0] == '-') ? str.substr(1) : str;

    for (char c : s) {
        if (!isdigit(c)) {
            throw std::invalid_argument("Input string contains non-numeric characters");
        }
    }

    try {
        int result = std::stoi(s);
        return (str[0] == '-') ? -result : result;
    } catch (const std::out_of_range&) {
        throw std::out_of_range("Input string represents a number out of range for int");
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
