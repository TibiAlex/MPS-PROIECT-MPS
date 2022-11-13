#include "node.h"
#include <vector>

class Graph {
    public:
        vector<Node> level;
        vector<Node> old_level;
        vector<Node> initial_level;
};