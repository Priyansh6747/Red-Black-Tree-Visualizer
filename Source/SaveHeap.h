#ifndef RED_BLACK_TREE_VISUALIZER_SAVEHEAP_H
#define RED_BLACK_TREE_VISUALIZER_SAVEHEAP_H
#include <iostream>
#include "bits/stdc++.h"
#include <string>
// For formatting timestamps

using namespace std;

class TreeData {
private:
    string inputArray; // A string ex "0T 2T 2T 3T 2F"
    string name;
public:
    void SetInfo(const vector<pair<int, bool>>& InputArray, const string& Name){
        name=Name;
        for(auto it : InputArray){
            inputArray += to_string(it.first);
            inputArray += (it.second)?"+":"-";
            inputArray +=",";
        }
    }

    // Comparator for sorting by lastModifiedDate (most recent first)
    bool operator<(const TreeData& other) const {
        return name < other.name;
    }
    bool operator>(const TreeData& other) const {
        return name > other.name;
    }

    vector<pair<int,bool>> GetInput(){
        vector<pair<int,bool>> arr;
        pair<int,bool> p;
        for(int i =0 ;i<inputArray.size();i += 3){
            p.first = std::stoi(&inputArray[i]);
            p.second = (inputArray[i+1] == '+');
            arr.push_back(p);
        }
        return arr;
    }

    void serialize(ofstream &os){
        auto lenIA = inputArray.size();
        auto lenN = name.size();

        os.write(reinterpret_cast<const char *>(&lenIA), sizeof(lenIA));
        os.write(inputArray.c_str(),lenIA);

        os.write(reinterpret_cast<const char *>(&lenN), sizeof(lenN));
        os.write(name.c_str(),lenN);
    }

    static TreeData deserialize(ifstream &is){
        size_t lenIA,lenN;

        is.read(reinterpret_cast<char *>(&lenIA), lenIA);
        string IA(lenIA,' ');
        is.read(&IA[0],lenIA);

        is.read(reinterpret_cast<char *>(&lenN), lenN);
        string N(lenN,' ');
        is.read(&N[0],lenN);
    }
};

#endif //RED_BLACK_TREE_VISUALIZER_SAVEHEAP_H
