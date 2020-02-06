#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyScene *scene = new MyScene(0,0,1024,768);
    MyView *view = new MyView(scene);
    QPushButton *but = new QPushButton("next");
    //scene->addWidget(but);

 //   scene->setSize(4);
 //   scene->add(Complex(0,0));
 //   scene->add(Complex(100,10));
 //   scene->add(Complex(400,20));
  //  scene->add(Complex(900,30));
    Complex mid(1024.0/2,768.0/2);
    qreal pi = acos(-1);
    scene->setInit(mid);
    for(int i=0;i<1024;i++){
        qreal theta = 2*pi/100*i;
        scene->add(mid+Complex(25*cos(6*theta)*cos(theta)*theta,25*theta*cos(6*theta)*sin(theta)));
    }
    scene->compile();
    view->show();
    QTimeLine *time = new QTimeLine(40000);
    time->setFrameRange(0,1024);
    QObject::connect(time,SIGNAL(frameChanged(int)),scene,SLOT(next()));
    time->start();
    QObject::connect(but,SIGNAL(clicked()),scene,SLOT(next()));
    return a.exec();
}
