#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <tree.h>

class SNode : public Node {
 public:
    int key;
    SNode *l;
    SNode *r;

    SNode(){};
    ~SNode(){};

    SNode *getL() override { return this->l; }
    SNode *getR() override { return this->r; }
    int getKey() override { return this->key; }
    int getType() override { return TTSPLAY; }
};

class SplayTree : public Tree {
public:
   SNode *getRoot() override { return root; }
   void add(int k) override { root = add(k, root); }
   void drop(int k) override { root = drop(k, root); }
   void clear() override {
       clear(root);
       root = nullptr;
   }

private:
    SNode *root = nullptr;

    SNode *RRTurn(SNode *q) {
        SNode *p = q->l;
        q->l = p->r;
        p->r = q;
        return p;
    }

    SNode *LLTurn(SNode *q) {
        SNode *p = q->r;
        q->r = p->l;
        p->l = q;
        return p;
    }

    SNode *Splay(int k, SNode *p) {
        if (!p) return nullptr;
        SNode q;
        q.l = q.r = nullptr;
        SNode *LTMax = &q;
        SNode *RTMin = &q;
        while (true) {
            if (k < p->key) {
                if (!p->l) break;
                if (k < p->l->key) {
                    p = RRTurn(p);
                    if (!p->l) break;
                }
                RTMin->l = p;
                RTMin = RTMin->l;
                p = p->l;
                RTMin->l = nullptr;
            } else if (k > p->key) {
                if (!p->r) break;
                if (k > p->r->key) {
                    p = LLTurn(p);
                    if (!p->r) break;
                }
                LTMax->r = p;
                LTMax = LTMax->r;
                p = p->r;
                LTMax->r = nullptr;
            } else {
                break;
            }
        }
        LTMax->r = p->l;
        RTMin->l = p->r;
        p->l = q.r;
        p->r = q.l;
        return p;
    }

    SNode *NN(int k) {
        SNode *p = new SNode();
        p->key = k;
        p->l = p->r = nullptr;
        return p;
    }

    SNode *add(int k, SNode *p) {
        static SNode *q = nullptr;
        if (!q) {
            q = NN(k);
        } else {
            q->key = k;
        }
        if (!p) {
            p = q;
            q = nullptr;
            return p;
        }
        p = Splay(k, p);
        if (k < p->key) {
            q->l = p->l;
            q->r = p;
            p->l = nullptr;
            p = q;
        } else if (k > p->key) {
            q->r = p->r;
            q->l = p;
            p->r = nullptr;
            p = q;
        } else {
            return p;
        }
        q = nullptr;
        return p;
    }

    SNode *drop(int k, SNode *p) {
        if (!p) return nullptr;
        SNode *q;
        p = Splay(k, p);
        if (k != p->key) {
            return p;
        } else {
            if (!p->l) {
                q = p;
                p = p->r;
            } else {
                q = p;
                p = Splay(k, p->l);
                p->r = q->r;
            }
            delete q;
            return p;
        }
    }

    void clear(SNode *p) {
        if (p == nullptr) return;
        clear(p->l);
        clear(p->r);
        delete p;
    }
};
#endif // SPLAYTREE_H
