#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<ui_mainwindow.h>
class MainWindow : public QMainWindow,
                   public Ui_MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
