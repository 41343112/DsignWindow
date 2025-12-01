#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    connect(actionDarkMode, &QAction::toggled, this, &MainWindow::on_actionDarkMode_toggled);
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
