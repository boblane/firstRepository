#include "dialog.h"
#include "ui_dialog.h"
#include <QtDebug>

#define screenWidth     800
#define screenHeight    600

#define btnMaxWidth     100
#define btnMaxHeight    25

Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    this->resize(screenWidth,screenHeight);

    canvas = new myDrawLabel(this);
    canvas->resize(640,480);
    canvas->setRadius(10);
    canvas->setMaximumSize(640,480);
    canvas->setMinimumSize(320,240);
    canvas->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    canvas->setStyleSheet("QPushButton { background-color: white }");

    enterText = new QLabel("Enter a key:",this);
    enterText->resize(btnMaxWidth,btnMaxHeight);
    enterText->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    enterEdit = new QLineEdit(this);
    enterEdit->resize(btnMaxWidth,btnMaxHeight);
    enterEdit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    _insert = new QPushButton("insert",this);
    _insert->resize(btnMaxWidth,btnMaxHeight);
    _insert->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(_insert,SIGNAL(clicked()),this,SLOT(insertBnt_clicked()));

    _delete = new QPushButton("delete",this);
    _delete->resize(btnMaxWidth,btnMaxHeight);
    _delete->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(_delete,SIGNAL(clicked()),this,SLOT(deleteBnt_clicked()));

    //功能框主要垂直布局
    Vlayout = new QVBoxLayout[vlayoutnum];
    //功能框主要网格布局
    Glayout = new QGridLayout[glayoutnum];
    //功能框主要水平布局
    Hlayout = new QHBoxLayout[hlayoutnum];

    Hlayout->addStretch();
    Hlayout->addWidget(enterText);
    Hlayout->addWidget(enterEdit);
    Hlayout->addWidget(_insert);
    Hlayout->addWidget(_delete);
    Hlayout->addStretch();

    Vlayout->addWidget(canvas);
    Vlayout->addLayout(Hlayout);

    tree = new avltree<int>();
    this->setLayout(Vlayout);

}

Dialog::~Dialog()
{
    delete canvas;
    delete enterText;
    delete enterEdit;
    delete _insert;
    delete _delete;
}

void Dialog::insertBnt_clicked()
{
    points.clear();
    lines.clear();
    QString a = enterEdit->text();
    if(!a.isEmpty())
    {
        tree->insert(a.toInt());
    }
    tree->getPointsAndLines(tree,points,lines);
    canvas->setTreeNodes(points);
    canvas->setTreeLines(lines);
    this->update();
    qDebug()<<"insert";
}

void Dialog::deleteBnt_clicked()
{
    points.clear();
    lines.clear();
    QString a = enterEdit->text();
    if(!a.isEmpty())
    {
        tree->remove(a.toInt());
    }
    tree->getPointsAndLines(tree,points,lines);
    canvas->setTreeNodes(points);
    canvas->setTreeLines(lines);
    this->update();
    qDebug()<<"delete";
}
