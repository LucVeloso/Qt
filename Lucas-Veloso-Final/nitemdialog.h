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
    Compras ent1;
    int novo = 0;

    bool procComp(QString item);
    bool procTar(QString item);

    void preencherVetor(QVector<Compras> &v);
    void preencherVetor(QVector<Tarefa> &v);
    QVector<Compras> comp;
    QVector<Tarefa> tar;

private slots:

    void on_btnAdd_clicked();

    void on_btnCancelar_clicked();



private:
    Ui::NItemDialog *ui;


};

#endif // NITEMDIALOG_H
