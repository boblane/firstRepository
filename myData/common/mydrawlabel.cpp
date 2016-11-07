#include "mydrawlabel.h"

myDrawLabel::myDrawLabel(QWidget *parent):QLabel(parent)
{
    radius = 10;
}

myDrawLabel::~myDrawLabel()
{

}
void myDrawLabel::setRadius(int _r)
{
    radius = _r;
}
void myDrawLabel::setTreeNodes(map<int,QPoint> &_treeNodes)
{
    treeNodes = _treeNodes;
}
void myDrawLabel::setTreeLines(QVector<QLine> &_treeLines)
{
    treeLines = _treeLines;
}

void myDrawLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);//先调用父类的paintEvent为了显示'背景'!!!
    QPainter painter(this);
    for(auto it = treeNodes.cbegin();it!=treeNodes.cend();++it)
    {
        QString a = QString::number(it->first);
        painter.setPen(QPen(Qt::red,2));
        painter.drawText(it->second,a);
        painter.setPen(QPen(Qt::black,1));
        painter.drawEllipse(it->second,radius,radius);
    }
    painter.setPen(QPen(Qt::black,1));
    painter.drawLines(treeLines);
}

