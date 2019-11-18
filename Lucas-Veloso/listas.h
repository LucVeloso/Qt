#ifndef LISTAS_H
#define LISTAS_H

#include <QMainWindow>
#include "nitemdialog.h"
#include "tarefa.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Listas; }
QT_END_NAMESPACE

class Listas : public QMainWindow
{
    Q_OBJECT

public:
    Listas(QWidget *parent = nullptr);
    ~Listas();

    void setFormatacao();

private slots:


    void on_btnNLista_clicked();

    void on_btnAdd_clicked();

private:
    Ui::Listas *ui;
    Tarefa tEnt;
    NItemDialog nitem;
};
#endif // LISTAS_H
