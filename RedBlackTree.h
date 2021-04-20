#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <tree.h>

class RBNode : public Node {
public:
    int key = 0;
    int h = 0;
    bool b = true;
    RBNode *l = nullptr;
    RBNode *r = nullptr;
    RBNode *p = nullptr;

    RBNode(){};
    RBNode(int key, int h, bool b, RBNode *l, RBNode *r, RBNode *p)
            : key(key), h(h), b(b), l(l), r(r), p(p) {}
    ~RBNode(){};

    RBNode *getL() override { return this->l; }
    RBNode *getR() override { return this->r; }
    int getKey() override { return this->key; }
    int getType() override { return TTRB; }
};

class RedBlackTree : public Tree {
#define NIL &sentinel

public:
    void add(int data) override {
        RBNode *current, *parent, *x;
        current = root;
        parent = nullptr;
        while (current != NIL) {
            if (data == current->key) return;
            parent = current;
            current = data < current->key ? current->l : current->r;
        }
        x = new RBNode();
        x->key = data;
        x->p = parent;
        x->l = NIL;
        x->r = NIL;
        x->b = 0;
        if (parent) {
            if (data < parent->key) {
                parent->l = x;
            } else {
                parent->r = x;
            }
        } else {
            root = x;
        }
        afterAdd(x);
    }

    void drop(int k) override {
        RBNode *tmp = findNode(k);
        if (tmp != nullptr) {
            dropNode(tmp);
        }
    }

    void clear() override {
        clear(root);
        root = NIL;
    }

    RBNode *getRoot() override { return root; }

private:
    RBNode sentinel = {0, 0, true, NIL, NIL, NIL};
    RBNode *root = NIL;

    void afterAdd(RBNode *x) {
        while (x != root && x->p->b == 0) {
            if (x->p == x->p->p->l) {
                RBNode *y = x->p->p->r;
                if (y->b == 0) {
                    x->p->b = 1;
                    y->b = 1;
                    x->p->p->b = 0;
                    x = x->p->p;
                } else {
                    if (x == x->p->r) {
                        x = x->p;
                        leftTurn(x);
                    }
                    x->p->b = 1;
                    x->p->p->b = 0;
                    rightTurn(x->p->p);
                }
            } else {
                RBNode *y = x->p->p->l;
                if (y->b == 0) {
                    x->p->b = 1;
                    y->b = 1;
                    x->p->p->b = 0;
                    x = x->p->p;
                } else {
                    if (x == x->p->l) {
                        x = x->p;
                        rightTurn(x);
                    }
                    x->p->b = 1;
                    x->p->p->b = 0;
                    leftTurn(x->p->p);
                }
            }
        }
        root->b = 1;
    }

    void clear(RBNode *p) {
        if (p == nullptr) return;
        if (p == p->l && p == p->r) return;
        clear(p->r);
        clear(p->l);
        delete p;
    }

    RBNode *findNode(int data) {
        RBNode *current = root;
        while (current != NIL) {
            if (data == current->key) {
                return current;
            } else {
                current = data < current->key ? current->l : current->r;
            }
        }
        return nullptr;
    }

    void dropNode(RBNode *z) {
        RBNode *x, *y;
        if (!z || z == NIL) return;
        if (z->l == NIL || z->r == NIL) {
            y = z;
        } else {
            y = z->r;
            while (y->l != NIL) y = y->l;
        }
        if (y->l != NIL) {
            x = y->l;
        } else {
            x = y->r;
        }
        x->p = y->p;
        if (y->p) {
            if (y == y->p->l) {
                y->p->l = x;
            } else {
                y->p->r = x;
            }
        } else {
            root = x;
        }
        if (y != z) z->key = y->key;
        if (y->b == 1) afterDrop(x);
        delete y;
    }

    void afterDrop(RBNode *x) {
        while (x != root && x->b == 1) {
            if (x == x->p->l) {
                RBNode *w = x->p->r;
                if (w->b == 0) {
                    w->b = 1;
                    x->p->b = 0;
                    leftTurn(x->p);
                    w = x->p->r;
                }
                if (w->l->b == 1 && w->r->b == 1) {
                    w->b = 0;
                    x = x->p;
                } else {
                    if (w->r->b == 1) {
                        w->l->b = 1;
                        w->b = 0;
                        rightTurn(w);
                        w = x->p->r;
                    }
                    w->b = x->p->b;
                    x->p->b = 1;
                    w->r->b = 1;
                    leftTurn(x->p);
                    x = root;
                }
            } else {
                RBNode *w = x->p->l;
                if (w->b == 0) {
                    w->b = 1;
                    x->p->b = 0;
                    rightTurn(x->p);
                    w = x->p->l;
                }
                if (w->r->b == 1 && w->l->b == 1) {
                    w->b = 0;
                    x = x->p;
                } else {
                    if (w->l->b == 1) {
                        w->r->b = 1;
                        w->b = 0;
                        leftTurn(w);
                        w = x->p->l;
                    }
                    w->b = x->p->b;
                    x->p->b = 1;
                    w->l->b = 1;
                    rightTurn(x->p);
                    x = root;
                }
            }
        }
        x->b = 1;
    }

    void leftTurn(RBNode *x) {
        RBNode *y = x->r;
        x->r = y->l;
        if (y->l != NIL) y->l->p = x;
        if (y != NIL) y->p = x->p;
        if (x->p) {
            if (x == x->p->l) {
                x->p->l = y;
            } else {
                x->p->r = y;
            }
        } else {
            root = y;
        }
        y->l = x;
        if (x != NIL) x->p = y;
    }

    void rightTurn(RBNode *x) {
        RBNode *y = x->l;
        x->l = y->r;
        if (y->r != NIL) y->r->p = x;
        if (y != NIL) y->p = x->p;
        if (x->p) {
            if (x == x->p->r) {
                x->p->r = y;
            } else {
                x->p->l = y;
            }
        } else {
            root = y;
        }
        y->r = x;
        if (x != NIL) x->p = y;
    }
};

#endif // REDBLACKTREE_H
