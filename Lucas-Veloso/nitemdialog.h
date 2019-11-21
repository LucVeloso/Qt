#ifndef NITEMDIALOG_H
#define NITEMDIALOG_H

#include <QDialog>
#include "tarefa.h"

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
    bool novo = false;

private slots:
    void on_btnAdd_clicked();

    void on_btnCancelar_clicked();

private:
    Ui::NItemDialog *ui;

};

#endif // NITEMDIALOG_H
