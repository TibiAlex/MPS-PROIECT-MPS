#include <iostream>
#include <string>

using namespace std;

class Node {
    public:
        string operation;
        float result;

        Node(string operation, float result);
        Node();
};

typedef struct {
    int op;
    int index1;
    int index2;
} operation;