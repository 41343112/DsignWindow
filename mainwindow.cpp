#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
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
    // If no file path is set, call Save As
    if (currentFilePath.isEmpty()) {
        on_actionASave_triggered();
        return;
    }

    // Save to the current file
    saveToFile(currentFilePath);
}

void MainWindow::on_actionASave_triggered()
{
    // Open Save As dialog
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "另存新檔",
        currentFilePath.isEmpty() ? QDir::homePath() : currentFilePath,
        "文字檔案 (*.txt);;所有檔案 (*.*)"
    );

    // If user cancelled, return
    if (filePath.isEmpty()) {
        return;
    }

    // Update current file path and save
    currentFilePath = filePath;
    saveToFile(currentFilePath);
}

bool MainWindow::saveToFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "儲存錯誤", "無法寫入檔案：" + filePath);
        return false;
    }

    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();

    statusbar->showMessage("檔案已儲存：" + filePath, 3000);
    return true;
}
