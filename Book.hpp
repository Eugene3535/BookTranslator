#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BookTranslator.h"

class Book : 
    public QMainWindow
{
    Q_OBJECT
public:
    Book(QWidget *parent = Q_NULLPTR);

    bool openFB2File(QString& file, QString& book, QStringList& content);

private:
    Ui::BookTranslatorClass ui;
};
