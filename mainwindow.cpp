#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWheelEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MyView::wheelEvent(QWheelEvent *event){
    if(event->delta()>0){
        this->scale(1.1,1.1);
    }else{
        this->scale(0.9,0.9);
    }
}

void MyView::keyPressEvent(QKeyEvent *event){
}

void MyLine::hoverEnterEvent(QGraphicsSceneHoverEvent *e){
    this->setPen(QPen(Qt::green));
}

void MyLine::hoverLeaveEvent(QGraphicsSceneHoverEvent *e){
    this->setPen(QPen(Qt::black));
}

Complex Complex::operator*(qreal x) const{
    return Complex(this->a*x,this->b*x);
}

Complex Complex::operator*(const Complex &y) const{
    Complex ret(this->a*y.a-this->b*y.b,this->a*y.b+this->b*y.a);
    return ret;
}

Complex Complex::operator+(const Complex &y) const{
    return Complex(this->a+y.a,this->b+y.b);
}

Complex Complex::operator-(const Complex &y) const{
    return Complex(this->a-y.a,this->b-y.b);
}

Complex operator * (qreal x,Complex y){
    return y*x;
}

void fft(QVector<Complex>&data,int n){
    QVector<int> rev(n);
    int R = 0;
    while((1<<(R+1))<=n)R++;
    for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(R-1));
    for(int i=0;i<n;i++){
        if(i<rev[i])
            std::swap(data[i],data[rev[i]]);
    }
    qreal pi = acos(-1);
    for(int i=1;i<n;i<<=1){
        Complex w(cos(pi/i),sin(pi/i));
        for(int j=0;j<n;j+=(i<<1)){
            Complex wn(1,0);
            for(int k=0;k<i;k++){
                Complex x=data[j+k],y=wn*data[j+i+k];
                data[j+k]=x+y;
                data[i+j+k]=x-y;
                wn=wn*w;
            }
        }
    }
}

void MyScene::setSize(int x){
    int R = 1;
    while((R<<1)<x)R<<=1;
    data = QVector<Complex>(R);
    ellipse = QVector<QGraphicsLineItem *>();
    for(int i=0;i<R;i++){
        ellipse.push_back(new QGraphicsLineItem(0,0,1,1));
        qDebug("233");
    }
}

void MyScene::add(const Complex &x){
    data.push_back(x);
    ellipse.push_back(new QGraphicsLineItem(0,0,1,1));
    QPen pen = QPen(Qt::green);
    pen.setWidth(5);
    ellipse.last()->setPen(pen);
    this->addItem(ellipse.last());

}

void MyScene::compile(){
    fft(this->data,this->data.length());
   drawCircles(0);
}

void MyScene::drawCircles(int x){

    qreal pi = acos(-1);
    int n = data.length();
    Complex init(0,0);
    Complex w0(cos(-2*pi*x/n),sin(-2*pi*x/n));
    Complex w(1,0),current(0,0);
    for(int k=0;k<data.length();k++){
        current = data[k]*w * (1.0/n);
        Complex tmp = init+current;
        //qDebug("%lf %lf %lf %lf\n",w0.real(),w0.img(),tmp.real(),tmp.img());
        ellipse[k]->setLine(init.real(),init.img(),tmp.real(),tmp.img());
        init = init+current;
        w=w*w0;
    }
    qDebug("draw %lf %lf %lf %lf",init.real(),init.img(),previous.real(),previous.img());
    QGraphicsLineItem *line = new QGraphicsLineItem(previous.real(),previous.img(),init.real(),init.img());
    QPen pen = QPen(Qt::black);
    pen.setWidth(5);

    line->setPen(pen);
    this->addItem(line);
    previous = init;
}

void MyScene::next(){
    drawCircles(++cur);
}
