#ifndef AVLTREE_H
#define AVLTREE_H

#include <bits/stdc++.h>
#include <QStack>

struct AVLNode {
    int key;
    int h;
    AVLNode * l;
    AVLNode * r;
    AVLNode(){
        key = 0;
        l = nullptr;
        r = nullptr;
        h = 0;
    }
};


class AVLTree{

private:

    AVLNode * root;

    void balance(AVLNode *&p, int troubleSide){
         if (troubleSide  == -1){
            int k = compareHeigth(p->l);
            if (k == -1){
                smallRightTurn(p);
            } else if (k == 1) {
                bigRightTurn(p);
            }
        } else {
            int k = compareHeigth(p->r);
            if (k == 1){
                smallLeftTurn(p);
            } else if (k == -1){
                bigLeftTurn(p);
            }
        }
    }

    int compareHeigth(AVLNode *& p){
        if (p == nullptr) throw -1;
        if (p->l == nullptr && p->r == nullptr){
            return -1;
        }
        if (p->l == nullptr && p->r != nullptr){
            return 1;
        }
        if (p->l != nullptr && p->r == nullptr){
            return -1;
        }
        return ((p->l->h)>=(p->r->h)?-1:1);
    }

    void bigRightTurn(AVLNode * &p){
        AVLNode * q = p->l;
        AVLNode * r = q->r;
        p->l = r->r;
        q->r = r->l;
        updateHeight(p);
        updateHeight(q);
        r->l = q;
        r->r = p;
        updateHeight(r);
        p = r;
    }

    void updateHeight(AVLNode * &p){
            if (p == nullptr) throw -1;
            if (p->l == nullptr && p->r == nullptr){
                p->h = 1;
                return;
            }
            p->h = qMax(p->l==nullptr?0:p->l->h, p->r==nullptr?0:p->r->h)+1;
    }


    void smallRightTurn(AVLNode * &p){
        AVLNode * q = p->l;
        p->l = q->r;
        q->r=p;
        updateHeight(p);
        updateHeight(q);
        p=q;
    }
    void smallLeftTurn(AVLNode *&p){
        AVLNode * q = p->r;
        p->r = q->l;
        q->l = p;
        updateHeight(p);
        updateHeight(q);
        p = q;
    }


    void bigLeftTurn(AVLNode *&p){
        AVLNode * q = p->r;
        AVLNode * r = q->l;
        p->r = r->l;
        q->l = r->r;
        updateHeight(p);
        updateHeight(q);
        r->r = q;
        r->l = p;
        updateHeight(r);
        p = r;
    }

    int needBalance(AVLNode * elem){
        if (elem == nullptr) throw -1;
        if (elem->l == nullptr && elem->r == nullptr){
            return 0;
        } else if (elem->l == nullptr && elem->r != nullptr){
            if (abs(0 - elem->r->h) > 1){
                return 1;
            } else {
                return 0;
            }
        } else if (elem->l != nullptr && elem->r == nullptr){
            if (abs(0 - elem->l->h) > 1){
                return -1;
            } else {
                return 0;
            }
        } else {
            if (abs(elem->l->h - elem->r->h) > 1){
                if (elem->l->h > elem->r->h) return -1;
                else return 1;
            } else {
                return 0;
            }
        }
    }

    void add(int key, AVLNode *& p){
        if (p == nullptr){
            p = new AVLNode;
            p->key = key;
            p->l=nullptr;
            p->r=nullptr;
            p->h = 1;
            return;
        }
        if (p->key == key) {
            return;
        }
        if (key < p->key){
            add(key, p->l);
        } else {
            add(key, p->r);
        }
        int nb = needBalance(p);
        if (nb){
            balance(p, nb);
        }
        updateHeight(p);

        return;
    }




    void drop(int key, AVLNode * &p){
        if (p == nullptr)return;
        if (p->key == key){
            if (p->l == nullptr && p->r == nullptr){
                delete(p);
                p = nullptr;
            } else if (p->l != nullptr && p->r == nullptr) {
                p->key = p->l->key;
                delete (p->l);
                p->l = nullptr;
            } else if (p->l == nullptr && p->r != nullptr){
                p->key = p->r->key;
                delete (p->r);
                p->r = nullptr;
            } else {
                if (p->r->l == nullptr){
                    AVLNode ** q = &p->r;
                    qSwap((*q)->key, p->key);
                    if ((*q)->r != nullptr){
                        (*q)->key = (*q)->r->key;
                        delete ((*q)->r);
                        (*q)->r = nullptr;
                        updateHeight(*q);
                    } else {
                        (*q) = nullptr;
                    }
                    int nb = needBalance(p);
                    if (nb) balance(p, nb);

                } else {
                QStack <AVLNode*> s;
                AVLNode * q = p->r;
                AVLNode ** z;
                    while (q->l != nullptr) {
                        if (q->l->l == nullptr){
                            z = &q->l;
                            break;
                        } else {
                            s.push(q);
                            q = q->l;
                        }
                    }
                qSwap((*z)->key, p->key);
                if ((*z)->r != nullptr){
                    (*z)->key = (*z)->r->key;
                    (*z)->r = nullptr;
                } else {
                    (*z) = nullptr;
                }
                int nb;
                while(!s.empty()){
                   AVLNode * u = s.pop();
                   nb = needBalance(u);
                   if (nb){
                        balance(u,nb);
                   }
                }
                }
            }
            return;
        }
        if (key < p->key){
            drop(key, p->l);
        } else {
            drop(key, p->r);
        }
        updateHeight(p);
        int nb = needBalance(p);
        if (nb){
            balance(p, nb);
        }
    }



    void clear(AVLNode * p){
        if (p){
            clear(p->l);
            clear(p->r);
            delete p;
        }
    }

public:
    void add(int key){
        add(key, this->root);
    }
    void drop(int key){
        drop(key, this->root);
    }
    AVLTree(){
        root = nullptr;
    }
    AVLNode * getRoot(){
        return root;
    }
    void clear(){
        clear(root);
        root = nullptr;
    }

};
















#endif // AVLTREE_H
