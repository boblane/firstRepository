#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include "./Tree/avltree.h"
#include "./common/mydrawlabel.h"

#define vlayoutnum 2
#define glayoutnum 2
#define hlayoutnum 2
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private slots:
    void insertBnt_clicked();
    void deleteBnt_clicked();
private:
    myDrawLabel*    canvas;
    QLabel*         enterText;
    QLineEdit*      enterEdit;
    QPushButton*    _insert;
    QPushButton*    _delete;

    QVBoxLayout*    Vlayout;
    QGridLayout*    Glayout;
    QHBoxLayout*    Hlayout;

    avltree<int>*   tree;
    map<int,QPoint> points;
    QVector<QLine> lines;

};

#endif // DIALOG_H
