#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RedBlackTree.h"
#include "SplayTree.h"
#include "AVLTree.h"
#include "Vertex.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, int newParameter = 1);
    ~MainWindow();

   template<class T> void presketch(T *p);
   void copyTree(Node *p, Tree *targetTree);
   void toAnother(Tree *targetTree);

   QPair<int, int> sketch(AVLNode *p, int h, int y);
   QPair<int, int> sketch(RBNode *p, int h, int y);
   QPair<int, int> sketch(SNode *p, int h, int y);

   int v(int x);

private slots:
    void on_btn_add_clicked();
    void on_btn_del_clicked();
    void on_btn_z_plus_clicked();
    void on_btn_z_minus_clicked();
    void on_rbtn_AVL_clicked();
    void on_rbtn_RB_clicked();
    void on_rbtn_S_clicked();
    void on_btnClear_clicked();
    void on_btnTest_clicked();

private:
    //constants
    const int R = 25;
    const int TestSize = 100;
    const int TestDelay = 25; //ms

    int RightEnd = 0;

    Ui::MainWindow *ui;
    QGraphicsScene *Scene;
    Tree *tree;
};
#endif // MAINWINDOW_H
