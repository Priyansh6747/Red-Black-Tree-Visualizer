#ifndef RED_BLACK_TREE_VISUALIZER_SAVEHEAP_H
#define RED_BLACK_TREE_VISUALIZER_SAVEHEAP_H
#include <iostream>
#include "bits/stdc++.h"
#include <string>
// For formatting timestamps
using namespace std;

class TreeData {
private:
    vector<pair<int,bool>> inputArray; // A string ex "0T 2T 2T 3T 2F"
    string name;
    int Top;
public:
    void clear(){
        inputArray.clear();
        name.clear();
    }
    void SetInfo(const vector<pair<int, bool>>& InputArray, const string& Name,int top){
        clear();
        Top=top;
        name=Name;
        inputArray = InputArray;
    }

    // Comparator for sorting by lastModifiedDate (most recent first)
    bool operator<(const TreeData& other) const {
        return Top < other.Top;
    }
    bool operator>(const TreeData& other) const {
        return Top > other.Top;
    }

    string GetName(){
        return name;
    }

    int GetTop(){
        return Top;
    }

    vector<pair<int,bool>> GetInput(){
        return inputArray;
    }

    void serialize(ofstream &os){
        auto lenIA = inputArray.size();
        auto lenN = name.size();

        os.write(reinterpret_cast<const char *>(&lenIA), sizeof(lenIA));

        os.write(reinterpret_cast<const char *>(&lenN), sizeof(lenN));
        os.write(name.c_str(),lenN);
    }

    static TreeData deserialize(ifstream &is){
        size_t lenIA,lenN;
        is.read(reinterpret_cast<char *>(&lenIA), sizeof(lenIA));
        string IA(lenIA, ' ');
        is.read(&IA[0], lenIA);


        is.read(reinterpret_cast<char *>(&lenN), lenN);
        string N(lenN,' ');
        is.read(&N[0],lenN);

        TreeData obj;
        obj.name = N;

        return obj;
    }
};

#endif //RED_BLACK_TREE_VISUALIZER_SAVEHEAP_H
