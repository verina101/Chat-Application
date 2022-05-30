#include "login.h"
#include "ui_login.h"
#include "Data.h"
#include "MyConstants.h"
#include "constantdata.h"
#include<QMessageBox>
#include <qdebug.h>
#include<QPixmap>
#include<QFileDialog>
login::login(QWidget *parent): QWidget(parent), ui(new Ui::login) {
    this->setWindowTitle("Login");
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

    ui->stackedWidget_2->setCurrentIndex(0);

    ui->comboBox_visibilty->addItem("For Contacts Only");//0
    ui->comboBox_visibilty->addItem("Everyone");//1

    QPixmap pic(":/images/assets/defultProfile.png");
    ui->label_pic->setPixmap(pic.scaled(100, 100, Qt::KeepAspectRatio));

}

login::~login() {
    delete ui;
}

void login::on_pushButton_login_clicked() {
    constantdata currUser;
    QString mobileno,password;

    mobileno=ui->lineEdit_mobileno->text();
    password=ui->lineEdit_password->text();
    string tablename="USER",columns="UserID, FirstName, LastName, PhoneNumber, Password";
    string condition="where PhoneNumber = " + db.convertToValue(mobileno) + " and Password = " + db.convertToValue(password);
    vector<vector<QString>> returndata=db.SelectData(tablename,columns,condition);
    if(returndata.empty()){
        QMessageBox::warning(this,"invalid login","wrong mobileno or password");
        //qDebug() << "wrong password or mobileno";
    }
    else{
        currUser.setphoneNumber(mobileno.toStdString());

        MyConstants::setMyId(returndata[0][0]);
        MyConstants::setMyName( returndata[0][1] + " " + returndata[0][2] );
        ui->stackedWidget_2->close();
        this->close();

        myChats = new Chats();
        myChats->show();

    }
    db.DisplayData(returndata);
}

void login::on_pushButton_signup_clicked() {
    this->setWindowTitle("Register");
    ui->stackedWidget_2->setCurrentIndex(1);

}

void login::on_pushButton_submit_clicked() {
    QString firstname,lastname,password,phoneno,description,visibility;
    firstname=ui->lineEdit_firstname->text();
    lastname=ui->lineEdit_lastname->text();
    password=ui->lineEdit_password_2->text();
    phoneno=ui->lineEdit_phoneno->text();
    description=ui->lineEdit_description->text();
    visibility=ui->comboBox_visibilty->currentText();

    visibility = visibility.contains("Everyone") ? "1" : "0";

    if(firstname.isEmpty() || lastname.isEmpty() || description.isEmpty() || password.isEmpty() || phoneno.isEmpty()) {
        QMessageBox::warning(this,"invalid registration "," missing value");
    }
    else {
        if(lastname.size()<3 || firstname.size()<3){
            QMessageBox::warning(this,"invalid registration "," enter valid first or last name");
        }
        else{
            bool x = true;
            if(phoneno.size() == 11 && phoneno.toStdString()[0] == '0'){
                for(int i = 1; i <= 10; i++){
                    if(phoneno.toStdString()[i] >= '0' && phoneno.toStdString()[i] <= '9'){
                        x = true;
                        continue;
                    }
                    else{
                        x = false;
                        break;
                    }
                }
                if(x == true) {
                    string columns = "PhoneNumber ";
                    string condition = "where PhoneNumber = " + db.convertToValue(phoneno);
                    vector<vector<QString>> returnData = db.SelectData("USER", columns, condition);
                    if(returnData.empty()) {
                        string tablename="USER";
                        string values = "(" + db.convertToValue(firstname) + "," + db.convertToValue(lastname) + "," + db.convertToValue(ProfilePicture) + "," + db.convertToValue(description) + "," + db.convertToValue(password) + "," + db.convertToValue(phoneno) + "," + db.convertToValue(visibility) + ")";
                        db.InsertData(tablename,values);
                        constantdata currUser;
                        currUser.setphoneNumber(phoneno.toStdString());
                        QMessageBox::information(this, "valid registration", "registration successfully");
                    }
                    else{
                        QMessageBox::warning(this, "invalid registration ", " duplicated phone number");
                    }
                }
                else{
                    QMessageBox::warning(this, "invalid registration ", " enter valid phone number integer only");
                }

            }
            else{
                QMessageBox::warning(this, "invalid registration ", " enter valid phone number start with 0 and size 11");
            }
        }
    }
}

void login::on_pushButton_change_pic_clicked() {
    QString filter="Jpeg File(*.jpeg);; Png File(*.png);; JPG File(*.jpg) ;; BMP File(*.bmp);; GIF file(*.gif)";
    QString filePath=QFileDialog::getOpenFileName(this,"open a file","D:/pic",filter);
    QMessageBox::information(this,"..",filePath);
    this->ProfilePicture = filePath;
    if(!filePath.isEmpty()){
        QPixmap pic(filePath);
        ui->label_pic->setPixmap(pic.scaled(100,100,Qt::IgnoreAspectRatio));
        QFileInfo fi(filePath);
        QString fileName= fi.fileName();
        QString desktopPath = "D:/myProjects/Chat-Application/Chat-Application/assets/source_images";
        QString destinationPath= desktopPath+QDir::separator()+fileName;
        QFile::copy(filePath, destinationPath);
    }
}


void login::on_pushButton_loginin_2_clicked()
{
    this->setWindowTitle("Login");
    ui->stackedWidget_2->setCurrentIndex(0);
}

