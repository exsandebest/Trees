#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->showMaximized();

    Scene = new QGraphicsScene();
    Scene->setStickyFocus(true);

    ui->treeView->setScene(Scene);
    ui->treeView->setRenderHint(QPainter::Antialiasing);
    ui->treeView->scale(1, -1);
    ui->treeView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->treeView->setAlignment(Qt::AlignCenter);
    ui->treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->treeView->setFocusPolicy(Qt::FocusPolicy::WheelFocus);

    ui->rbtn_AVL->setChecked(true);
    ui->progressBar->hide();

    tree = new AVLTree();
}

MainWindow::~MainWindow() {
    delete ui;
}

template<class T> void MainWindow::presketch(T *p) {
    Scene->clear();
    delete Scene;
    Scene = new QGraphicsScene();
    ui->treeView->setScene(Scene);
    if (p == nullptr) return;
    if (p->getType() == TTAVL) {
        AVLNode *q = dynamic_cast<AVLNode *> (p);
        RightEnd = sketch(q, 0, -RightEnd).first;
    } else if (p->getType() == TTRB) {
        RBNode *q = dynamic_cast<RBNode *> (p);
        RightEnd = sketch(q, 0, -RightEnd).first;
    } else if (p->getType() == TTSPLAY) {
        SNode *q = dynamic_cast<SNode *> (p);
        RightEnd = sketch(q, 0, -RightEnd).first;
    }
}

QPair<int, int> MainWindow::sketch(RBNode *p, int h, int y) {
    if ((p == p->l && p == p->r) || p == nullptr) {
        QGraphicsItem *item = new Vertex(0, "black", true);
        Scene->addItem(item);
        item->setPos(v(y), v(h));
        return {y, y};
    }

    QPair <int, int> lnr = sketch(p->l, h-3*R, y);
    Scene->addLine(lnr.first+2*R, v(h), lnr.second, h-2*R);
    QPair<int ,int> nr = sketch(p->r, h-3*R, lnr.first+4*R);
    Scene->addLine(lnr.first+2*R, v(h), nr.second, h-2*R);
    QGraphicsItem *item = new Vertex(p->key, (p->b ? "black" : "red"));
    Scene->addItem(item);
    item->setPos(v(lnr.first+2*R), v(h));
    return {nr.first, lnr.first+2*R};
}

QPair<int, int> MainWindow::sketch(AVLNode *p, int h, int y) {
    if (p == nullptr) return {y, y};
    QPair <int, int> lnr = sketch(p->l, h-3*R, y);
    if (p->l) {
        Scene->addLine(lnr.first+2*R, v(h), lnr.second, h-2*R);
    }
    QPair<int, int> nr = sketch(p->r, h-3*R, lnr.first+2*R);
    if (p->r) {
        Scene->addLine(lnr.first+2*R, v(h), nr.second, h-2*R);
    }
    QGraphicsItem *item = new Vertex(p->key, "avl");
    Scene->addItem(item);
    item->setPos(v(lnr.first+2*R), v(h));
    return {nr.first, lnr.first+2*R};
}

QPair<int, int> MainWindow::sketch(SNode *p, int h, int y) {
    if (p == nullptr) return {y, y};
    QPair <int, int> lnr = sketch(p->l, h-3*R, y);
    if (p->l) {
        Scene->addLine(lnr.first+2*R, v(h), lnr.second, h-2*R);
    }
    QPair<int ,int> nr = sketch(p->r, h-3*R, lnr.first+2*R);
    if (p->r) {
        Scene->addLine(lnr.first+2*R, v(h), nr.second, h-2*R);
    }
    QGraphicsItem *item = new Vertex(p->key, "splay");
    Scene->addItem(item);
    item->setPos(lnr.first+R, v(h));
    return {nr.first, lnr.first+2*R};
}

int MainWindow::v(int x) {
    return x - R;
}

void MainWindow::toAnother(Tree *targetTree) {
    copyTree(tree->getRoot(), targetTree);
    tree->clear();
    tree = targetTree;
    presketch(tree->getRoot());
}

void MainWindow::copyTree(Node *p, Tree *targetTree) {
    if (p == nullptr || (p == p->getL() && p == p->getR())) return;
    copyTree(p->getL(), targetTree);
    copyTree(p->getR(), targetTree);
    targetTree->add(p->getKey());
}

void MainWindow::on_btn_add_clicked() {
    QString str = ui->line_input->text();
    ui->line_input->clear();
    if (str.isEmpty()) {
        tree->add(QRandomGenerator::global()->generate() % 10000);
        presketch(tree->getRoot());
        return;
    }
    QStringList list = str.split(" ");
    for (int i = 0; i < list.size(); ++i) {
        tree->add(list[i].toInt());
    }
    presketch(tree->getRoot());
}

void MainWindow::on_btn_del_clicked() {
    QString str = ui->line_input->text();
    if (str.isEmpty()) return;
    ui->line_input->clear();
    QStringList list = str.split(" ");
    for (int i = 0; i < list.size(); ++i) {
        tree->drop(list[i].toInt());
    }
    presketch(tree->getRoot());
}

void MainWindow::on_btn_z_plus_clicked() {
    ui->treeView->scale(1.1, 1.1);
}

void MainWindow::on_btn_z_minus_clicked() {
    ui->treeView->scale(1/1.1, 1/1.1);
}

void MainWindow::on_rbtn_AVL_clicked() {
    AVLTree *newTree = new AVLTree();
    toAnother(newTree);
}

void MainWindow::on_rbtn_RB_clicked() {
    RedBlackTree *newTree = new RedBlackTree();
    toAnother(newTree);
}

void MainWindow::on_rbtn_S_clicked() {
    SplayTree *newTree = new SplayTree();
    toAnother(newTree);
}

void MainWindow::on_btnClear_clicked() {
    tree->clear();
    Scene->clear();
    delete Scene;
    Scene = new QGraphicsScene();
    ui->treeView->setScene(Scene);
}

void MainWindow::on_btnTest_clicked() {
    ui->progressBar->show();
    for (int i = 0; i < TestSize; ++i) {
        tree->add(QRandomGenerator::global()->generate() * QRandomGenerator::global()->generate());
        presketch(tree->getRoot());
        QThread::msleep(TestDelay);
        ui->progressBar->setValue(i);
        QCoreApplication::processEvents();
    }
    ui->progressBar->hide();
}
