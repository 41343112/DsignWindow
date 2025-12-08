#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
}

MainWindow::~MainWindow() {}

void MainWindow::on_actionDarkMode_toggled(bool checked)
{
    if (checked) {
        // Dark theme stylesheet
        QString darkStyle = R"(
            QMainWindow {
                background-color: #2b2b2b;
            }
            QMenuBar {
                background-color: #3c3c3c;
                color: #ffffff;
            }
            QMenuBar::item:selected {
                background-color: #505050;
            }
            QMenu {
                background-color: #3c3c3c;
                color: #ffffff;
            }
            QMenu::item:selected {
                background-color: #505050;
            }
            QToolBar {
                background-color: #3c3c3c;
                border: none;
            }
            QTextEdit {
                background-color: #1e1e1e;
                color: #d4d4d4;
                border: 1px solid #3c3c3c;
            }
            QStatusBar {
                background-color: #3c3c3c;
                color: #ffffff;
            }
        )";
        qApp->setStyleSheet(darkStyle);
    } else {
        // Reset to default light theme
        qApp->setStyleSheet("");
    }
}

void MainWindow::on_actionASave_triggered()
{

    QString defaultPath = currentFilePath.isEmpty() ? QDir::homePath() : QFileInfo(currentFilePath).absolutePath();
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("另存新檔"),
                                                    defaultPath,
                                                    tr("文字檔 (*.txt);;所有檔案 (*)"));
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("另存新檔"),
                           tr("無法儲存檔案:\n%1").arg(file.errorString()));
        return;
    }    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();
    


    

}
