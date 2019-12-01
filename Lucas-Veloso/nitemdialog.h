#ifndef NITEMDIALOG_H
#define NITEMDIALOG_H

#include <QDialog>
#include "tarefa.h"
#include "compras.h"
#include <QVector>

namespace Ui {
class NItemDialog;
}

class NItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NItemDialog(QWidget *parent = nullptr);
    ~NItemDialog();

    Tarefa ent;
    int novo = 0;

    bool proc(QString item);

    void preencherVetor(QVector<Compras> v);

private slots:

    void on_btnAdd_clicked();

    void on_btnCancelar_clicked();



private:
    Ui::NItemDialog *ui;
    QVector<Compras> comp;

};

#endif // NITEMDIALOG_H
