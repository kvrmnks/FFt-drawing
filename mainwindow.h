#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <algorithm>
#include <QTimeLine>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

class Complex{
private:
    qreal a,b;
public:
    Complex(qreal a=0,qreal b=0):a(a),b(b){}
    Complex operator * (qreal x)const;
    Complex operator * (const Complex &y)const;
    Complex operator + (const Complex &y)const;
    Complex operator - (const Complex &y)const;
    qreal length()const{
        return sqrt(a*a+b*b);
    }
    qreal real()const{return a;}
    qreal img()const{return b;}
};

class MyScene : public QGraphicsScene{
    Q_OBJECT
private:
    QVector<Complex> data;
    QVector<QGraphicsLineItem *> ellipse;
    Complex previous;
    int cur;
    void drawCircles(int x);
public:
    MyScene(qreal a,qreal b,qreal c,qreal d):QGraphicsScene(a,b,c,d){
        cur=0;
        previous=Complex(0,0);
    }
    void setSize(int x);
    void add(const Complex& x);
    void setInit(Complex x){previous = x;}
    void compile();
    public slots:
    void next();
};

class MyView : public QGraphicsView{
public:
    MyView(QGraphicsScene *p = Q_NULLPTR):QGraphicsView(p){};
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

class MyLine : public QGraphicsLineItem{
public:
    MyLine(qreal a,qreal b,qreal c,qreal d):QGraphicsLineItem(a,b,c,d){}
    void hoverEnterEvent(QGraphicsSceneHoverEvent *e) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *e) override;
};



Complex operator * (qreal x,Complex y);

void fft(QVector<Complex>&data,int n);
#endif // MAINWINDOW_H
