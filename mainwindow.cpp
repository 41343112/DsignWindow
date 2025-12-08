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
    // Open file dialog to select save location
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("另存新檔"),
                                                    currentFilePath.isEmpty() ? QDir::homePath() : currentFilePath,
                                                    tr("文字檔 (*.txt);;所有檔案 (*)"));
    
    // If user cancelled the dialog, return
    if (fileName.isEmpty()) {
        return;
    }
    
    // Create/open the file for writing
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("另存新檔"), 
                           tr("無法儲存檔案:\n%1").arg(file.errorString()));
        return;
    }
    
    // Write the content from textEdit to the file
    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();
    
    // Update the current file path
    currentFilePath = fileName;
    
    // Update window title to show the saved file name
    setWindowTitle(QFileInfo(fileName).fileName() + " - MainWindow");
    
    // Show success message in status bar
    statusbar->showMessage(tr("檔案已儲存至: %1").arg(fileName), 3000);
}
