#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RedBlackTree.h"
#include "SplayTree.h"
#include "AVLTree.h"

enum {
    //TT - Tree Type
    TTAVL = 1,
    TTRB = 2,
    TTSPLAY = 3
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   template<class T> void presketch(T* p);
   int v(int x);
   QPair<int, int> sketch(SNode * p, int h, int y);
   QPair<int, int> sketch(AVLNode * p, int h, int y);
   QPair<int, int> sketch(RBNode * p, int h, int y);
   template<class T, class D> void fromOneToAnother(T * p, D &tree);

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
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
