#ifndef RED_BLACK_TREE_VISUALIZER_SAVEMANAGER_H
#define RED_BLACK_TREE_VISUALIZER_SAVEMANAGER_H
#include "bits/stdc++.h"

class SaveManager {
private:
    priority_queue<TreeData,vector<TreeData>,greater<>> pq;
public:
    void insert(TreeData &T){
        pq.push(T);
    }
    TreeData GetTop(){
        TreeData t = pq.top();
        pq.pop();
        return t;
    }
    bool Empty(){return pq.empty();}

    void serialize(ofstream &os) const{
        size_t size = pq.size();
        os.write(reinterpret_cast<const char*>(&size), sizeof(size));

        vector<TreeData> temp;
        priority_queue<TreeData,vector<TreeData>,greater<>> pqcpy;
        while (!pqcpy.empty()){
            temp.push_back(pqcpy.top());
            pqcpy.pop();
        }

        for(TreeData& obj : temp)
            obj.serialize(os);
    }

    void deserialize(ifstream &is){
        size_t size;
        is.read(reinterpret_cast<char*>(&size), sizeof(size));

        vector<TreeData> temp;
        for (size_t i = 0; i < size; ++i) {
            TreeData a = TreeData::deserialize(is);
            temp.push_back(a);
        }

        for (const TreeData& obj : temp) {
            pq.push(obj);
        }
    }
};


#endif //RED_BLACK_TREE_VISUALIZER_SAVEMANAGER_H
