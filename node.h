#ifndef NODE_H
#define NODE_H

class Node {
public:
    Node();
    virtual ~Node();

    virtual int getType();
    virtual Node *getL();
    virtual Node *getR();
    virtual int getKey();

private:
    Node *l;
    Node *r;
    int key;
};

#endif // NODE_H
