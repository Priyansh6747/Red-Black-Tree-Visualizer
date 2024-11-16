#ifndef RED_BLACK_TREE_VISUALIZER_RBTREE_H
#define RED_BLACK_TREE_VISUALIZER_RBTREE_H
using namespace std;
struct Node{
    int data;
    Node* Left;
    Node* Right;
    bool color;//true for red , false for black;
    Node(int val):data(val),Left(nullptr),Right(nullptr),color(true){};
};
class RBTree{
private:
    Node* Root;
public:
    //Rotations
    //Insert function
    //Delete Functions
};
#endif //RED_BLACK_TREE_VISUALIZER_RBTREE_H
