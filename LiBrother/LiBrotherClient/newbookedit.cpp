#include "newbookedit.h"
#include "ui_newbookedit.h"
#include "client_interfaces.h"
#include "QMessageBox"

newbookedit::newbookedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newbookedit)
{
    ui->setupUi(this);
}

newbookedit::~newbookedit()
{
    delete ui;
}

void newbookedit::on_pushButton_3_clicked()
{
    IClassFactoryClient *factory2;
    getClassFactory(&factory2);
    ILibrary *library2;
    factory2->getLibrary(&library2);


    std::string bDescription;
    TBookBasicInfo basic2;
    IBook *iBook2;



        QString nbName1 = ui->lineEdit_6->text();//增加新书操作，一次读入所有新书信息，并insertbook

        QString nCount = ui->lineEdit_7->text();
        int nbCount = nCount.toInt();

        QString nbAuthor1 = ui->lineEdit_8->text();

        QString nbIsbn1 = ui->lineEdit_10->text();

        QString nbPublisher1 = ui->lineEdit_9->text();

        QString nbDescription1 = ui->textEdit_2->toPlainText();

        basic2.count = nbCount;
        basic2.name = nbName1.toStdString();
        basic2.author = nbAuthor1.toStdString();
        basic2.isbn = nbIsbn1.toStdString();
        basic2.publisher = nbPublisher1.toStdString();
        std::string nbDescription01 = nbDescription1.toStdString();

        if(iBook2->setBasicInfo(basic2)){}else{QMessageBox::information(this,"Warning","基础信息录入失败，请检查输入格式");}
        if(iBook2->setDescription(nbDescription01.c_str())){}else{QMessageBox::information(this,"Warning","简洁录入失败");}
        if(library2->insertBook(iBook2)){}else{QMessageBox::information(this,"Warning","无法写入");}

          factory2->Release();
          iBook2->Release();
          library2->Release();

}