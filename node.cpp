#include <node.h>

Node::Node() {}
Node::~Node() {}
int Node::getType() { return -1; }
Node *Node::getL() { return this->l; }
Node *Node::getR() { return this->r; }
int Node::getKey() { return this->key; }
