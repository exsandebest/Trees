#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include "AVLTree.h"
#include "RedBlackTree.h"
#include "SplayTree.h"
#include "Vertex.h"

int curTree = TTAVL;
int RightEnd = 0;
const int R = 25;
const int TestSize = 100;
const int TestDelay = 50; //ms
QGraphicsScene * Scene;

AVLTree AVLT;
RedBlackTree RBT;
SplayTree ST;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Scene = new QGraphicsScene;
    ui->treeView->setScene(Scene);
    ui->treeView->setRenderHint(QPainter::Antialiasing);
    ui->treeView->translate(400,400);
    ui->treeView->scale(1,-1);
    ui->treeView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->treeView->setAlignment(Qt::AlignCenter);
    ui->treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->rbtn_AVL->setChecked(true);
    Scene->setStickyFocus(true);
    this->showMaximized();
    qsrand(0);
    ui->progressBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


template<class T> void MainWindow::presketch(T* p){
    Scene->clear();
    delete Scene;
    Scene = new QGraphicsScene;
    ui->treeView->setScene(Scene);
    RightEnd = sketch(p, 0, -RightEnd).first;
    ui->treeView->setFocusPolicy(Qt::FocusPolicy::WheelFocus);
}


QPair <int, int> MainWindow::sketch(RBNode *p, int h, int y){
    if ((p == p->l && p == p->r) || p == nullptr) {
        QGraphicsItem * item = new Vertex(0, "black",true);
        Scene->addItem(item);
        item->setPos(v(y), v(h));
        return {y,y};
    }

    QPair <int, int> lnr = sketch(p->l, h-3*R, y);
    Scene->addLine(lnr.first+2*R, h-R, lnr.second, h-2*R);
    QPair<int ,int> nr = sketch(p->r, h-3*R, lnr.first+4*R);
    Scene->addLine(lnr.first+2*R, h-R, nr.second, h-2*R);
    QGraphicsItem * item = new Vertex(p->key, (p->b?"black":"red"));
    Scene->addItem(item);
    item->setPos(v(lnr.first+2*R), v(h));
    return {nr.first, lnr.first+2*R};
}

QPair<int,int> MainWindow::sketch(AVLNode * p, int h, int y){
    if (p == nullptr) return {y,y};
    QPair <int, int> lnr = sketch(p->l, h-3*R, y);
    if (p->l){
        Scene->addLine(lnr.first+2*R, h-R, lnr.second, h-2*R);
    }
    QPair<int ,int> nr = sketch(p->r, h-3*R, lnr.first+2*R);
    if (p->r){
        Scene->addLine(lnr.first+2*R, h-R, nr.second, h-2*R);
    }
    QGraphicsItem * item = new Vertex(p->key, "avl");
    Scene->addItem(item);
    item->setPos(v(lnr.first+2*R), v(h));
    return {nr.first, lnr.first+2*R};
}

QPair<int, int> MainWindow::sketch(SNode * p, int h, int y){
    if (p == nullptr) return {y,y};
    QPair <int, int> lnr = sketch(p->l, h-3*R, y);
    if (p->l){
        Scene->addLine(lnr.first+2*R, h-R, lnr.second, h-2*R);
    }
    QPair<int ,int> nr = sketch(p->r, h-3*R, lnr.first+2*R);
    if (p->r){
        Scene->addLine(lnr.first+2*R, h-R, nr.second, h-2*R);
    }
    QGraphicsItem * item = new Vertex(p->key, "splay");
    Scene->addItem(item);
    item->setPos(lnr.first+R, h-R);
    return {nr.first, lnr.first+2*R};
}

int MainWindow::v(int x){
    return x-R;
}


template<class T, class D> void MainWindow::fromOneToAnother(T * p, D &tree){
    if (p == nullptr) return;
    if (p == p->l && p == p->r) return;
    fromOneToAnother(p->l, tree);
    fromOneToAnother(p->r, tree);
    tree.add(p->key);
}


void MainWindow::on_btn_add_clicked(){
    QString str = ui->line_input->text();
    if (curTree == TTAVL){
        if (str[0] == ' ' || str == ""){
            AVLT.add(qrand()%10000);
            presketch(AVLT.getRoot());
            return;
        }
        QStringList lis = str.split(" ");
        for (int i = 0; i < lis.size(); ++i){
            AVLT.add(lis[i].toInt());
        }
        ui->line_input->clear();
        presketch(AVLT.getRoot());
    } else if (curTree == TTRB){
        if (str[0] == ' ' || str == ""){
            RBT.add(qrand()%10000);
            presketch(RBT.getRoot());
            return;
        }
        QStringList lis = str.split(" ");
        for (int i = 0; i < lis.size(); ++i){
            RBT.add(lis[i].toInt());
        }
        ui->line_input->clear();
        presketch(RBT.getRoot());
    } else {
        if (str[0] == ' ' || str == ""){
            ST.add(qrand()%10000);
            presketch(ST.getRoot());
            return;
        }
        QStringList lis = str.split(" ");
        for (int i = 0; i < lis.size(); ++i){
            ST.add(lis[i].toInt());
        }
        ui->line_input->clear();
        presketch(ST.getRoot());
    }

}

void MainWindow::on_btn_del_clicked(){
    QString str = ui->line_input->text();
    if (str[0] == ' ' || str == ""){
        return;
    } else {
        if (curTree == TTAVL){
            QStringList lis = str.split(" ");
            for (int i = 0; i < lis.size(); ++i){
                AVLT.drop(lis[i].toInt());
            }
            ui->line_input->clear();
            presketch(AVLT.getRoot());
        } else if (curTree == TTRB){
            QStringList lis = str.split(" ");
            for (int i = 0; i < lis.size(); ++i){
                RBT.drop(lis[i].toInt());
            }
            ui->line_input->clear();
            presketch(RBT.getRoot());
        } else {
            QStringList lis = str.split(" ");
            for (int i = 0; i < lis.size(); ++i){
                ST.drop(lis[i].toInt());
            }
            ui->line_input->clear();
            presketch(ST.getRoot());
        }
    }
}

void MainWindow::on_btn_z_plus_clicked()
{
    ui->treeView->scale(1.1, 1.1);
}

void MainWindow::on_btn_z_minus_clicked()
{
    ui->treeView->scale(1/1.1, 1/1.1);
}


void MainWindow::on_rbtn_AVL_clicked()
{
    if (curTree == TTRB){
        fromOneToAnother(RBT.getRoot(), AVLT);
        presketch(AVLT.getRoot());
        curTree = TTAVL;
        RBT.clear();
    } else if (curTree == TTSPLAY) {
        fromOneToAnother(ST.getRoot(), AVLT);
        presketch(AVLT.getRoot());
        curTree = TTAVL;
        ST.clear();
    }
}

void MainWindow::on_rbtn_RB_clicked()
{
    if (curTree == TTAVL){
        fromOneToAnother(AVLT.getRoot(), RBT);
        presketch(RBT.getRoot());
        curTree = TTRB;
        AVLT.clear();
    } else if (curTree == TTSPLAY) {
        fromOneToAnother(ST.getRoot(), RBT);
        presketch(RBT.getRoot());
        curTree = TTRB;
        ST.clear();
    }
}

void MainWindow::on_rbtn_S_clicked()
{
    if (curTree == TTRB){
        fromOneToAnother(RBT.getRoot(), ST);
        presketch(ST.getRoot());
        curTree = TTSPLAY;
        RBT.clear();
    } else if (curTree == TTAVL){
        fromOneToAnother(AVLT.getRoot(), ST);
        presketch(ST.getRoot());
        curTree = TTSPLAY;
        AVLT.clear();
    }
}

void MainWindow::on_btnClear_clicked()
{
    if (curTree == TTAVL){
        AVLT.clear();
    } else if (curTree == TTRB) {
        RBT.clear();
    } else {
        ST.clear();
    }
    Scene->clear();
    delete Scene;
    Scene = new QGraphicsScene;
    ui->treeView->setScene(Scene);
}

void MainWindow::on_btnTest_clicked()
{
    ui->progressBar->show();
    if (curTree == TTAVL){
        for (int i = 0; i < TestSize; ++i){
            AVLT.add(qrand()*qrand());
            presketch(AVLT.getRoot());
            QThread::msleep(TestDelay);
            ui->progressBar->setValue(i);
            QCoreApplication::processEvents();
        }
    } else if (curTree == TTRB){
        for (int i = 0; i < TestSize; ++i){
            RBT.add(qrand()*qrand());
            presketch(RBT.getRoot());
            QThread::msleep(TestDelay);
            ui->progressBar->setValue(i);
            QCoreApplication::processEvents();
        }
    } else {
        for (int i = 0; i < TestSize; ++i){
            ST.add(qrand()*qrand());
            presketch(ST.getRoot());
            QThread::msleep(TestDelay);
            ui->progressBar->setValue(i);
            QCoreApplication::processEvents();
        }
    }
    ui->progressBar->hide();
}
