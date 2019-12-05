#ifndef SPLAYTREE_H
#define SPLAYTREE_H
#include <QString>
#include <QDebug>

struct SNode{
    int key;
    SNode * l;
    SNode * r;
};





class SplayTree{
private:
    SNode * root;
    SNode * RRTurn(SNode * q){
        SNode * p = q->l;
        q->l = p->r;
        p->r = q;
        return p;
    }
    SNode * LLTurn(SNode * q){
        SNode * p = q->r;
        q->r = p->l;
        p->l = q;
        return p;
    }

    SNode * Splay(int k, SNode * p){
        if (!p) return nullptr;
        SNode q;
        q.l = q.r = nullptr;
        SNode * LTMax = &q;
        SNode * RTMin = &q;
        while (1){
            if (k < p->key){
                if (!p->l) break;
                if (k < p->l->key){
                    p = RRTurn(p);
                    if (!p->l) break;
                }
                RTMin->l = p;
                RTMin = RTMin->l;
                p = p->l;
                RTMin->l = nullptr;
            } else if (k > p->key){
                if (!p->r) break;
                if (k > p->r->key){
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


    SNode * NN(int k){
        SNode * p = new SNode;
        p->key = k;
        p->l = p->r = nullptr;
        return p;
    }
    SNode * add(int k, SNode * p){
        static SNode * q = nullptr;
        if (!q){
            q = NN(k);
        } else {
            q->key = k;
        }
        if (!p){
            p = q;
            q = nullptr;
            return p;
        }
        p = Splay(k, p);
        if (k < p->key){
            q->l = p->l;
            q->r = p;
            p->l = nullptr;
            p = q;
        } else if (k > p->key){
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

    SNode * drop(int k, SNode * p){
        SNode * q;
        if (!p){
            return nullptr;
        }
        p = Splay(k,p);
        if (k != p->key){
            return p;
        } else {
            if (!p->l){
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

    void print(SNode * p){
        if (p){
            QString s = "";
            print(p->l);
            if (p->l){
                s+= QString::number(p->l->key) + "<-";
            }
            s+= QString::number(p->key);
            if (p->r){
                s+="->"+ QString::number(p->r->key);
            }
            qDebug() << s;
        }
    }
    void clear(SNode * p){
        if (p){
            clear(p->l);
            clear(p->r);
            delete p;
        }
    }


public:
    SplayTree(){}
    void add(int k){
        root = add(k, root);
    }
    void drop(int k){
        root = drop(k, root);
    }
     SNode * getRoot(){
        return root;
    }
     void print(){
         print(root);
     }
     void clear(){
         clear(root);
         root = nullptr;
     }

};
#endif // SPLAYTREE_H
