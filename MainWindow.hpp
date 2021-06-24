#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QApplication>

class MainWindow :
    public QMainWindow
{
    Q_OBJECT 
public:
    MainWindow(QMainWindow* parent = 0);

    void open_fb2();

    void write_log(const QString& info);
};