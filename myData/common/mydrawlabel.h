#ifndef MYDRAWLABEL_H
#define MYDRAWLABEL_H

#include <QPainter>
#include <QLabel>
#include <memory>
#include <map>
using namespace std;
class myDrawLabel:public QLabel
{
    Q_OBJECT
public:
    explicit myDrawLabel(QWidget *parent = 0);
    virtual ~myDrawLabel();
    void setRadius(int _r);
    void setTreeNodes(map<int,QPoint> &_treeNodes);
    void setTreeLines(QVector<QLine>  &_treeLines);
private:
    void paintEvent(QPaintEvent *);
    map<int,QPoint> treeNodes;
    QVector<QLine>  treeLines;
    int             radius;


};

#endif // MYDRAWLABEL_H
