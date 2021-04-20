#ifndef TREE_H
#define TREE_H

#include "node.h"

enum {
    //TT - Tree Type
    TTAVL = 1,
    TTRB = 2,
    TTSPLAY = 3
};

class Tree {
public:
    Tree();
    virtual ~Tree();
    virtual Node *getRoot();
    virtual void add(int);
    virtual void drop(int);
    virtual void clear();

private:
    Node *root;
};

#endif // TREE_H
