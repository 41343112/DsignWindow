#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
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

void MainWindow::on_actionSave_triggered()
{
    // 如果尚未設定檔案路徑，則呼叫另存新檔功能
    if (currentFilePath.isEmpty()) {
        on_actionASave_triggered();
        return;
    }
    
    // 開啟檔案進行寫入
    QFile file(currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "儲存失敗", "無法寫入檔案：" + currentFilePath);
        return;
    }
    
    // 將文字編輯器的內容寫入檔案
    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();
    
    // 顯示儲存成功訊息
    statusbar->showMessage("檔案已儲存：" + currentFilePath, 3000);
}

void MainWindow::on_actionASave_triggered()
{
    // 開啟另存新檔對話框
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "另存新檔",
        "",
        "文字檔案 (*.txt);;所有檔案 (*.*)"
    );
    
    // 如果使用者取消選擇，則返回
    if (fileName.isEmpty()) {
        return;
    }
    
    // 更新當前檔案路徑
    currentFilePath = fileName;
    
    // 呼叫儲存功能
    on_actionSave_triggered();
}
