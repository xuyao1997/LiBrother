#include "usermain.h"
#include "ui_usermain.h"
#include "mainwindow.h"
#include "userborrow.h"
#include "bookdata.h"
#include "client_interfaces.h"
#include "QMessageBox"
#include "changepassword.h"
#include "managermain.h"
#include "useredit.h"

usermain::usermain(QWidget *parent) ://开场直接显示所有用户已借的书本
    QDialog(parent),
    ui(new Ui::usermain)
{
    ui->setupUi(this);

    ui->listWidget->clear();
    getClassFactory(&factory1);

    IAuthManager *iUser;//构建iauth为了之后使用getcurrentuser
    factory1->getAuthManager(&iUser);
    IUser *iUser1;
    bool uPd = iUser->getCurrentUser(&iUser1);//获取当前登陆的用户
    if(uPd)
    {
        TUserBasicInfo basic1;
        if(iUser1->getBasicInfo(basic1))//获取当前用户信息
        {
            QString uName1 = QString::fromStdString(basic1.name);
            ui->label_2->setText(uName1);//两个显示
            ui->label_5->setText(QString::number(basic1.id));
            std::vector<TBorrowInfo> basic2;//已经借了的书目
            if(iUser1->getBorrowedBooks(basic2))
            {
                int i;

                ILibrary *library2;
                factory1->getLibrary(&library2);

                for(i=0;i<basic2.size();i++)//在widget依次显示已借的书本
                {
                    IBook *iBook1;
                    int bID1 = basic2[i].bookID;
                    if(library2->queryById(bID1,&iBook1))
                    {
                        TBookBasicInfo basic3;
                        if(iBook1->getBasicInfo(basic3))
                        {
                            QString bName2 = QString::fromStdString(basic3.name);

                            QListWidgetItem *item = new QListWidgetItem;
                            item->setText(bName2);
                            item->setData(Qt::UserRole,basic3.id);//随带保存书本ID便于之后归还
                            ui->listWidget->addItem(item);
                        }
                        else{QMessageBox::information(this,"Warning",u8"获取已借书本信息失败");}
                    }
                    else{QMessageBox::information(this,"Warning",u8"无法查询到用户所借的该本书");}
                }
            }
            else{QMessageBox::information(this,"Warning",u8"无法获取用户已借的书目信息");}

        }
        else{QMessageBox::information(this,"Warning",u8"当前用户信息错误");}
    }
    else{QMessageBox::information(this,"Warning",u8"请先登录");}


}

usermain::~usermain()
{
    delete ui;
}





void usermain::on_pushButton_2_clicked()//继续借书模块，直接进入书目搜索。（todo：增加对用户已借书目数量的检测）
{
    userborrow userborrow1;
    userborrow1.exec();
}

void usermain::on_pushButton_3_clicked()//还书操作
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    int bId = item->data(Qt::UserRole).toInt();

    ILibrary *library3;
    factory1->getLibrary(&library3);
    IBook *iBook1;
    if(library3->queryById(bId,&iBook1)){}//通过预先保存的书本ID号确定所要归还的ibook
    else{QMessageBox::information(this,"Warning",u8"无法找寻到该书本");return;}


    IAuthManager *iUser;
    factory1->getAuthManager(&iUser);
    IUser *iUser1;
    if(iUser->getCurrentUser(&iUser1))//确定当前要还书的用户
    {
        if(iUser1->returnBook(iBook1)){}//正式还书
        else{QMessageBox::information(this,"Warning",u8"归还失败");}
    }
    else{QMessageBox::information(this,"Warning",u8"用户信息错误");}


    ui->listWidget->takeItem(ui->listWidget->currentRow());//删除已还的书

    library3->Release();
    iBook1->Release();
    iUser->Release();
    iUser1->Release();
}



void usermain::on_pushButton_5_clicked()
{
    ChangePassword changePassword1;//进入修改密码界面
    changePassword1.exec();
}

void usermain::on_pushButton_4_clicked()//进入初等管理员（AuthLevel＝1）操作选择菜单
{
    IClassFactoryClient *factory3;
    getClassFactory(&factory3);
    IAuthManager *iUser;
    factory3->getAuthManager(&iUser);
    if(iUser->getAuthLevel() >= 1)
    {
        managermain managermain1;
        managermain1.exec();
    }
    else{QMessageBox::information(this,"Warning",u8"对不起，您没有权限");}

    factory3->Release();
    iUser->Release();
}

void usermain::on_pushButton_6_clicked()//只有authLevel＝2的高级管理员才能进入用户信息修改界面
{
    IClassFactoryClient *factory3;
    getClassFactory(&factory3);
    IAuthManager *iUser;
    factory3->getAuthManager(&iUser);
    if(iUser->getAuthLevel() >= 2)
    {
        useredit useredit1;
        useredit1.exec();
    }
    else{QMessageBox::information(this,"Warning",u8"对不起，您没有权限");}

    factory3->Release();
    iUser->Release();
}

void usermain::on_pushButton_7_clicked()//刷新操作，对当前用户的所借的书本做一个重新显示
{
    ui->listWidget->clear();
    getClassFactory(&factory1);

    IAuthManager *iUser;//构建iauth为了之后使用getcurrentuser
    factory1->getAuthManager(&iUser);
    IUser *iUser1;
    bool uPd = iUser->getCurrentUser(&iUser1);//获取当前登陆的用户
    if(uPd)
    {
        TUserBasicInfo basic1;
        if(iUser1->getBasicInfo(basic1))//获取当前用户信息
           {
            QString uName1 = QString::fromStdString(basic1.name);
            ui->label_2->setText(uName1);//两个显示
            ui->label_5->setText(QString::number(basic1.id));
            std::vector<TBorrowInfo> basic2;//已经借了的书目
            if(iUser1->getBorrowedBooks(basic2))
            {
                ILibrary *library2;
                factory1->getLibrary(&library2);
                int i;
                for(i=0;i<basic2.size();i++)//在widget依次显示已借的书本
                {
                    IBook *iBook1;
                    int bID1 = basic2[i].bookID;
                    if(library2->queryById(bID1,&iBook1))
                    {
                        TBookBasicInfo basic3;
                        if(iBook1->getBasicInfo(basic3))
                        {
                            QString bName2 = QString::fromStdString(basic3.name);

                            QListWidgetItem *item = new QListWidgetItem;
                            item->setText(bName2);
                            item->setData(Qt::UserRole,basic3.id);//随带保存书本ID便于之后归还
                            ui->listWidget->addItem(item);
                        }
                        else{QMessageBox::information(this,"Warning",u8"获取已借书本信息失败");}
                    }
                    else{QMessageBox::information(this,"Warning",u8"无法查询到用户所借的该本书");}
                }
            }
            else{QMessageBox::information(this,"Warning",u8"无法获取用户已借的书目信息");}

        }
        else{QMessageBox::information(this,"Warning",u8"当前用户信息错误");}
    }
    else{QMessageBox::information(this,"Warning",u8"请先登录");}

}
