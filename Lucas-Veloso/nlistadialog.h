#ifndef NLISTADIALOG_H
#define NLISTADIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class NListaDialog;
}

class NListaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NListaDialog(QWidget *parent = nullptr);
    ~NListaDialog();

    bool novo = false;
    char tipo;
    QString nomeNLista;

    bool validNome(QString nome);

private slots:
    void on_btnNListaCompras_clicked();

    void on_btnNListaTarefas_clicked();

private:
    Ui::NListaDialog *ui;
};

#endif // NLISTADIALOG_H
