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

private slots:
    void on_actionDarkMode_toggled(bool checked);
    void on_actionSave_triggered();
    void on_actionASave_triggered();

private:
    QString currentFilePath;
};
#endif // MAINWINDOW_H
