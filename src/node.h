#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
    public:
        string operation;
        float result;
        vector<Node *> parents;
        vector<Node *> children;
};