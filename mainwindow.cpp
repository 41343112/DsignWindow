// 引入主視窗類別定義（原有）
#include "mainwindow.h"
// 引入Qt Designer產生的UI類別定義（原有）
#include "ui_mainwindow.h"
// 【新增】引入Qt檔案對話框類別：用於顯示儲存/開啟檔案對話框
#include <QFileDialog>
// 【新增】引入Qt文字串流類別：提供方便的文字讀寫介面
#include <QTextStream>
// 【新增】引入Qt訊息對話框類別：用於顯示警告、錯誤等訊息
#include <QMessageBox>
// 【新增】引入Qt檔案類別：提供檔案的基本操作（開啟、關閉、讀寫）
#include <QFile>

// MainWindow建構子實作
// parent：父視窗指標，用於建立視窗階層關係
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)  // 呼叫基礎類別QMainWindow的建構子
{
    setupUi(this);  // 初始化UI元件（由Qt Designer產生的函數）
}

// MainWindow解構子實作（空實作，使用預設行為）
MainWindow::~MainWindow() {}

// 深色模式切換函數實作（原有功能，未修改）
// checked：true表示啟用深色模式，false表示停用
void MainWindow::on_actionDarkMode_toggled(bool checked)
{
    if (checked) {
        // 如果啟用深色模式
        // 定義深色主題的樣式表字串
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
        // 將深色樣式表套用到整個應用程式
        qApp->setStyleSheet(darkStyle);
    } else {
        // 如果停用深色模式，重設為預設淺色主題
        qApp->setStyleSheet("");
    }
}

// ============================================================
// 【新增功能】儲存檔案函數實作
// 功能說明：將文字編輯器的內容儲存到檔案
// ============================================================
void MainWindow::on_actionSave_triggered()
{
    // 步驟1：檢查是否已有檔案路徑
    // isEmpty()：QString的成員函數，判斷字串是否為空
    if (currentFilePath.isEmpty()) {
        // 如果currentFilePath為空字串，表示尚未儲存過檔案
        // 呼叫另存新檔函數，讓使用者選擇儲存位置
        on_actionASave_triggered();
        // 結束此函數（另存新檔內部會再次呼叫本函數進行儲存）
        return;
    }
    
    // 步驟2：建立檔案物件並開啟檔案
    // QFile：Qt的檔案類別，用於檔案操作
    // currentFilePath：檔案的完整路徑
    QFile file(currentFilePath);
    
    // 嘗試開啟檔案進行寫入
    // QIODevice::WriteOnly：唯寫模式（會清空原有內容）
    // QIODevice::Text：文字模式（自動處理不同系統的換行符號）
    // |：位元OR運算子，結合兩個開啟模式
    // !：邏輯NOT，如果開啟失敗則條件為true
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // 檔案開啟失敗（可能是權限問題或路徑無效）
        // 顯示警告訊息對話框
        // QMessageBox::warning()：靜態函數，顯示警告對話框
        // 參數1(this)：對話框的父視窗
        // 參數2("儲存失敗")：對話框標題
        // 參數3：對話框內容訊息，使用+運算子連接字串
        QMessageBox::warning(this, "儲存失敗", "無法寫入檔案：" + currentFilePath);
        // 結束函數，不繼續執行儲存操作
        return;
    }
    
    // 步驟3：將文字內容寫入檔案
    // QTextStream：Qt的文字串流類別，提供方便的文字I/O
    // &file：檔案物件的指標，串流會寫入此檔案
    QTextStream out(&file);
    // textEdit：UI中的QTextEdit元件（透過多重繼承取得）
    // toPlainText()：取得文字編輯器的純文字內容（不含格式）
    // <<：串流輸出運算子，將文字寫入串流（進而寫入檔案）
    out << textEdit->toPlainText();
    // 關閉檔案，確保資料完全寫入磁碟並釋放資源
    file.close();
    
    // 步驟4：顯示成功訊息給使用者
    // statusbar：UI中的QStatusBar元件（透過多重繼承取得）
    // showMessage()：在狀態列顯示訊息
    // 參數1：要顯示的訊息文字
    // 參數2(3000)：訊息顯示時間（毫秒），3000表示3秒後自動消失
    statusbar->showMessage("檔案已儲存：" + currentFilePath, 3000);
}

// ============================================================
// 【新增功能】另存新檔函數實作
// 功能說明：開啟檔案對話框讓使用者選擇儲存位置
// ============================================================
void MainWindow::on_actionASave_triggered()
{
    // 步驟1：開啟儲存檔案對話框
    // QFileDialog::getSaveFileName()：Qt提供的標準儲存檔案對話框
    // 這是一個靜態函數，會顯示對話框並返回使用者選擇的檔案路徑
    QString fileName = QFileDialog::getSaveFileName(
        this,                                    // 參數1：對話框的父視窗
        "另存新檔",                               // 參數2：對話框的標題文字
        "",                                      // 參數3：預設路徑（空字串表示使用系統預設位置）
        "文字檔案 (*.txt);;所有檔案 (*.*)"        // 參數4：檔案類型過濾器
                                                 // ;;用於分隔不同選項
                                                 // 第一個選項：只顯示.txt檔案
                                                 // 第二個選項：顯示所有檔案
    );
    
    // 步驟2：檢查使用者是否取消操作
    // isEmpty()：判斷字串是否為空
    // 如果使用者按下「取消」按鈕，getSaveFileName()會返回空字串
    if (fileName.isEmpty()) {
        // 使用者取消操作，直接結束函數，不執行儲存
        return;
    }
    
    // 步驟3：更新當前檔案路徑
    // 將使用者選擇的檔案路徑存入成員變數
    // 之後使用「儲存」功能時就可以直接使用此路徑
    currentFilePath = fileName;
    
    // 步驟4：呼叫儲存函數執行實際的檔案寫入
    // 重複使用儲存函數的程式碼，避免程式碼重複（DRY原則）
    // 此時currentFilePath已有值，所以會直接執行檔案寫入
    on_actionSave_triggered();
}
