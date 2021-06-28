#pragma once

#include <QMainWindow>
#include <QLabel>

class MainWindow :
    public QMainWindow
{
    Q_OBJECT 
public:
    MainWindow(QMainWindow* parent = Q_NULLPTR);

    void open_fb2();
    void write_log(const QString& info);

private:
    QLabel m_title;
};