#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_openButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                tr("Text Files (*.txt)"));

    if (!fileName.isEmpty()) {
       ui->lineEdit->setText(fileName);
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("%1").arg("Текстовый редактор"),
                             tr("Не могу открыть файл %1\nПричина: %2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);

    ui->textEdit->setPlainText(in.readAll());




}

void MainWindow::on_replaceButton_clicked()
{
    QRegularExpression re(ui->lineEdit_2->text());
    QString str =ui->textEdit->toPlainText();
    str.replace(re, ui->lineEdit_3->text());
    ui->textEdit->setPlainText(str);
}

void MainWindow::on_saveButton_clicked()
{
    QFile file(fileName); //Свяжем файловую переменную с именем файла
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("%1").arg("myName"),
                             tr("Не могу сохранить файл %1\nПричина: %2.")
                             .arg(fileName)
                             .arg(file.errorString()));
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText(); //Само сохранение
}

void MainWindow::on_searchButton_clicked()
{
    QString findReg = ui->lineEdit_2->text();
    QRegularExpression re(findReg);
    QString endStr = re.match(ui->textEdit->toPlainText()).capturedTexts().join(' ');

    if(!endStr.isEmpty())
    {
        QMessageBox::warning(this, tr("%1").arg(""), "Текст по маске "+ findReg + " найден!" );
    }
    else
        QMessageBox::warning(this, tr("%1").arg(""), "Текст по маске "+ findReg + " не найден!" );

}
