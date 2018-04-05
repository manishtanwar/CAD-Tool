#undef scroll
#undef timeout
#include "include/form.h"
#undef timeout
#undef scroll
#undef border
#include "ui_form.h"
#include <QtCore>
#include <QtGui>
#include <QApplication>
#include <QLabel>
#include<QFileDialog>
#include<QMessageBox>
#include <QHBoxLayout>
#include <QDesktopWidget>

#include<bits/stdc++.h>

#define F first
#define S second
#define pb push_back

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}
Form::Form(std::vector<std::pair<float,float>> T,std::vector<std::pair<float,float>> Fv, std::vector<std::pair<float,float>> S, std::vector<std::pair<float,float>> O,
           std::vector<std::pair<int,int>> Te, std::vector<std::pair<int,int>> Fe, std::vector<std::pair<int,int>> Se, std::vector<std::pair<int,int>> Oe, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    QDesktopWidget dw;
    this->setFixedSize(dw.width(), dw.height());

    QLabel *label = new QLabel(this);
    label->setText("Random String");

    QPicture pi,pi1;
    QPainter p(&pi);
    QPainter p11(&pi1);

    QMatrix m;

//     m.scale( 1, -1 );
     p.setMatrix( m );

    std::set< std::pair<int,int> > Ts,Fs,Ss,Os;
    for(auto z : Te) Ts.insert(z);
    for(auto z : Fe) Fs.insert(z);
    for(auto z : Se) Ss.insert(z);
    for(auto z : Oe) Os.insert(z);
    Te.clear();Fe.clear();Se.clear();Oe.clear();
     for(auto z : Ts) Te.pb(z);
     for(auto z : Fs) Fe.pb(z);
     for(auto z : Ss) Se.pb(z);
     for(auto z : Os) Oe.pb(z);

    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));

    float xScale,yScale,zScale;
    float xTrans,yTrans,zTrans;
    float x,y,z,X,Y,Z;
    x = y = z = 1e9;
    X = Y = Z = -(1e9);
    for(int i=0;i<((int)T.size());i++){
     x = std::min(x,T[i].F);	y = std::min(y,T[i].S);
     X = std::max(X,T[i].F);	Y = std::max(Y,T[i].S);
    }

    for(int i=0;i<(int)Fv.size();i++){
     x = std::min(x,Fv[i].F);	z = std::min(z,Fv[i].S);
     X = std::max(X,Fv[i].F);	Z = std::max(Z,Fv[i].S);
    }

    for(int i=0;i<(int)S.size();i++){
     y = std::min(y,S[i].F);	z = std::min(z,S[i].S);
     Y = std::max(Y,S[i].F);	Z = std::max(Z,S[i].S);
    }

    xTrans = -x;
    yTrans = -y;
    zTrans = -z;

    for(int i=0;i<(int)T.size();i++){
     T[i].F += xTrans;
     T[i].S += yTrans;
    }

    for(int i=0;i<(int)Fv.size();i++){
     Fv[i].F += xTrans;
     Fv[i].S += zTrans;
    }

    for(int i=0;i<(int)S.size();i++){
     S[i].F += yTrans;
     S[i].S += zTrans;
    }

    X-=x; Y-=y; Z-=z;
    xScale = 250/X;
    yScale = 250/Y;
    zScale = 250/Z;
    float scale = std::min(xScale, std::min(yScale,zScale));

     for(int i=0;i<(int)T.size();i++){
         T[i].F *= scale;
         T[i].S *= scale;
        }

        for(int i=0;i<(int)Fv.size();i++){
         Fv[i].F *= scale;
         Fv[i].S *= scale;
        }

        for(int i=0;i<(int)S.size();i++){
         S[i].F *= scale;
         S[i].S *= scale;
        }
    p.translate(width()/2, height()/2);
    p.drawLine(width()/2,0,-width()/2,0);
    p.drawLine(0,height()/2,0,-height()/2);

    float p1,p2,p3,p4;
    p1 = p2 =p3 = p4=0.0;
    std::map<std::pair<float,float>, std::set<int>> mp;
    for(auto z : Te){
       p1=T[z.F].F-300.0;
       p2=T[z.F].S+50.0;
       p3=T[z.S].F-300.0;
       p4=T[z.S].S+50.0;
       p.drawLine(p1,-p2,p3,-p4);
       std::pair<float,float> paira;
       paira = {p1,-p2};
       mp[paira].insert(z.F);
       paira = {p3,-p4};
       mp[paira].insert(z.S);
    }
    for(auto z : mp){
        p1 = z.F.F;
        p2 = z.F.S;
        float margin = 5;
        int i=0;
        for(auto zz : z.S){ i++;
           std::string s = std::to_string(zz);
           if(i != (int)z.S.size())
           s.pb(',');
           QString qstr = QString::fromStdString(s);
           p.drawText(p1+margin,p2-5,qstr);
           margin += 15;
        }

    }
    mp.clear();

    for(auto z : Fe){
       p1 = Fv[z.F].F - 300.0;
       p2 = Fv[z.F].S-300.0;
       p3 = Fv[z.S].F - 300.0;
       p4 = Fv[z.S].S-300.0;
       p.drawLine(p1, -p2, p3,-p4 );
       std::pair<float,float> paira;
       paira = {p1,-p2};
       mp[paira].insert(z.F);
       paira = {p3,-p4};
       mp[paira].insert(z.S);
    }
    for(auto z : mp){
        p1 = z.F.F;
        p2 = z.F.S;
        float margin = 5;
        int i=0;
        for(auto zz : z.S){ i++;
           std::string s = std::to_string(zz);
           if(i != (int)z.S.size())
           s.pb(',');
           QString qstr = QString::fromStdString(s);
           p.drawText(p1+margin,p2-5,qstr);
           margin += 15;
        }

    }
    mp.clear();
    for(auto z : Se){
        p1 = S[z.F].F+50.0;
        p2 = -S[z.F].S+300.0;
        p3 = S[z.S].F+50.0;
        p4 = -S[z.S].S+300.0;
       p.drawLine(p1, p2, p3, p4);
       std::pair<float,float> paira;
       paira = {p1,p2};
       mp[paira].insert(z.F);
       paira = {p3,p4};
       mp[paira].insert(z.S);
    }

    for(auto z : mp){
        p1 = z.F.F;
        p2 = z.F.S;
        float margin = 5;
        int i=0;
        for(auto zz : z.S){ i++;
           std::string s = std::to_string(zz);
           if(i != (int)z.S.size())
           s.pb(',');
           QString qstr = QString::fromStdString(s);
           p.drawText(p1+margin,p2-5,qstr);
           margin += 15;
        }

    }
    mp.clear();

    x = y = z = 1e9;
    X = Y = Z = -(1e9);
    for(int i=0;i<((int)O.size());i++){
     x = std::min(x,O[i].F);	y = std::min(y,O[i].S);
     X = std::max(X,O[i].F);	Y = std::max(Y,O[i].S);
    }
    X-=x; Y-=y;
    xScale = 250/X;
    yScale = 250/Y;
    for(int i=0;i<(int)O.size();i++){
     O[i].F -=x; O[i].F *= xScale;
     O[i].S -=y; O[i].S *= yScale;
    }

    for(auto z : Oe){
        p1 = O[z.F].F+50.0;
        p2 = -O[z.F].S-50.0;
        p3 = O[z.S].F+50.0;
        p4 = -O[z.S].S-50.0;
     p.drawLine(p1, p2, p3, p4);
     std::pair<float,float> paira;
     paira = {p1,p2};
     mp[paira].insert(z.F);
     paira = {p3,p4};
     mp[paira].insert(z.S);
    }

    for(auto z : mp){
        p1 = z.F.F;
        p2 = z.F.S;
        float margin = 2.5;
        int i=0;
        for(auto zz : z.S){ i++;
           std::string s = std::to_string(zz);
           if(i != (int)z.S.size())
           s.pb(',');
           QString qstr = QString::fromStdString(s);
           p.drawText(p1+margin,p2-2.5,qstr);
           margin += 15;
        }

    }
    mp.clear();

    p.drawText(25,-15,"Isometric view");
    p.drawText(25,25,"Right Side view");
    p.drawText(-100,-15,"Top view");
    p.drawText(-100,25,"Front view");

//    p11.drawText(25,25,"Isometric view");
    p.end(); // Don't forget this line!
    p11.end(); // Don't forget this line!

    label->setPicture(pi);
//    label->setPicture(pi1);
    label->show();

}

Form::~Form()
{
    delete ui;
}
