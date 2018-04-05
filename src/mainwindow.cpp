#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/3d_to_2d.h"
#include "include/2d_to_3d.h"
#include "form.h"
#include<QFileDialog>
#include<QMessageBox>
#include<iostream>

std::string file_str,file_outstr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int a = three_d_to_two_d(file_str);
    if(a == 1)
    {
        ui->label->setText("Could not read file, please try again");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString outfile = ui->lineEdit->text();
    file_outstr = outfile.toUtf8().constData();
    int a = two_d_to_three_d(file_str, file_outstr);
    if(a == 1)
    {
        ui->label->setText("Could not read file, please try again");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/home",
                   "Text File(*);;All files (*.*)"
                );
    ui->label->setText(filename);
    file_str = filename.toUtf8().constData();
}
