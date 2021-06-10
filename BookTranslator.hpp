#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BookTranslator.h"

class BookTranslator : public QMainWindow
{
    Q_OBJECT

public:
    BookTranslator(QWidget *parent = Q_NULLPTR);

    bool openFB2File(QString& path);

private:
    QString book;
    QString imgId;
    QString imgType;

    Ui::BookTranslatorClass ui;
};
