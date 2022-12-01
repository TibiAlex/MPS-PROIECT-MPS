#include "node.h"

// constructor with parameters
Node::Node(Operation operation, float result) {
    this->operation = operation;
    this->result = result;
}

// constructor
Node::Node() {
}
