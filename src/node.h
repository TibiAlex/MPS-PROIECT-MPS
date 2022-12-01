#include <iostream>
#include <string>

using namespace std;

typedef struct {
    string label;
    int op;
    int index1;
    int index2;
} Operation;

class Node {
    public:
        Operation operation;
        float result;

        Node(Operation operation, float result);
        Node();
};