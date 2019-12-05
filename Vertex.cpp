#include "Vertex.h"
#include <QDebug>

Vertex::Vertex(int k, QString color, bool isNull) : QGraphicsItem(), key(k), color(color), isNull(isNull){}
Vertex::~Vertex(){}

QRectF Vertex::boundingRect() const{
    return QRectF(0,0,50,50);
}

void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->translate(25,25);
    painter->scale(1,-1);
    QColor cl;
    if (color == "avl"){
        cl = QColor::fromRgb(50, 205, 50);
    } else if (color == "red"){
        cl = Qt::red;
    } else if (color == "black"){
        cl = Qt::black;
    } else {
        cl = QColor::fromRgb(106, 90, 205);
    }

    painter->setBrush(cl);
    if (isNull){
        painter->drawRect(-20,-25,40,5);
    } else {
        painter->drawEllipse(-25,-25,50,50);
        QPen pen;
        pen.setColor(Qt::white);
        QFont f;
        QString s = QString::number(key);
        int sz = s.length()-1;
        int x = -4-sz*4, y = 5;

        f.setFamily("Trebuchet MS");
        f.setPixelSize(15);
        if (sz > 5){
            f.setPixelSize(12);
            x = -3-sz*3;
        }
        if (sz >7){
            f.setPixelSize(10);
            x = -sz*2-6;
            y = 4;
        }
        if (sz > 8){
            f.setPixelSize(8);
            x = -sz*2-3;
            y = 3;
        }

        painter->setFont(f);
        painter->setPen(pen);
        painter->drawText(QPoint(x,y), QString::number(key));
    }
}
