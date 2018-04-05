#undef timeout
#ifndef FORM_H
#define FORM_H
#undef timeout
#include <QWidget>
#include <bits/stdc++.h>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    Form(std::vector<std::pair<float,float>> T,std::vector<std::pair<float,float>> Fv, std::vector<std::pair<float,float>> S, std::vector<std::pair<float,float>> O,
         std::vector<std::pair<int,int>> Te, std::vector<std::pair<int,int>> Fe, std::vector<std::pair<int,int>> Se, std::vector<std::pair<int,int>> Oe, QWidget *parent = 0);
    ~Form();

private:
    Ui::Form *ui;
};

#endif // FORM_H
