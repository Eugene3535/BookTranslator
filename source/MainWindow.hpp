#pragma once

#include <QApplication>
#include <QMainWindow>
//#include <QTextBrowser>

class MainWindow :
    public QMainWindow
{
    Q_OBJECT 
public:
    MainWindow(QMainWindow* parent = 0);

    void open_fb2();
    void write_log(const QString& info);

private:
    //QTextBrowser m_text_browser;
};