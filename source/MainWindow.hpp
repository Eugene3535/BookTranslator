#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QTextBrowser>

class MainWindow :
    public QMainWindow
{
    Q_OBJECT 
public:
    MainWindow(QMainWindow* parent = Q_NULLPTR);

    void open_fb2();

private:
    QLabel m_title;
    QTextBrowser m_browser;
};