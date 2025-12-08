// 防止標頭檔重複引入的保護機制開始
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// 引入Qt主視窗基礎類別
#include <QMainWindow>
// 引入Qt Designer自動產生的UI標頭檔
#include<ui_mainwindow.h>

// MainWindow類別：繼承自QMainWindow和Ui_MainWindow
// 使用多重繼承方式整合UI設計
class MainWindow : public QMainWindow,
                   public Ui_MainWindow
{
    Q_OBJECT  // Qt的元物件系統巨集，啟用訊號槽機制

public:
    // 建構子：parent為父視窗指標，預設為nullptr
    MainWindow(QWidget *parent = nullptr);
    // 解構子：負責清理資源
    ~MainWindow();

private slots:
    // 私有槽函數區段：這些函數會回應UI的訊號
    
    // 深色模式切換槽函數（原有功能）
    // checked: true表示啟用深色模式，false表示停用
    void on_actionDarkMode_toggled(bool checked);
    
    // 【新增】儲存檔案槽函數
    // 功能：將文字編輯器內容儲存到檔案
    // 首次儲存會呼叫另存新檔功能選擇路徑
    // 後續儲存直接覆寫原檔案
    void on_actionSave_triggered();
    
    // 【新增】另存新檔槽函數
    // 功能：開啟檔案對話框讓使用者選擇儲存位置
    // 選擇完成後呼叫儲存函數執行實際寫入
    void on_actionASave_triggered();

private:
    // 私有成員變數區段
    
    // 【新增】當前檔案路徑
    // 用途：記住目前開啟/儲存的檔案位置
    // 空字串表示尚未儲存過，需要使用另存新檔
    QString currentFilePath;
};

// 防止標頭檔重複引入的保護機制結束
#endif // MAINWINDOW_H
