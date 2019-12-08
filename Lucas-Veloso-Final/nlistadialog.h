#ifndef NLISTADIALOG_H
#define NLISTADIALOG_H

#include <QDialog>
#include <QString>
#include <QMap>
#include "compras.h"
#include "tarefa.h"

namespace Ui {
class NListaDialog;
}

class NListaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NListaDialog(QWidget *parent = nullptr);
    ~NListaDialog();



    bool validCompras(QString nome);
    bool validTarefas(QString nome);

    bool getNovo() const;

    QString getNomeNLista() const;

    char getTipo() const;

    void carregarMap(QMap<QString, QVector<Compras>> c, QMap<QString, QVector<Tarefa>> t);

private slots:
    void on_btnNListaCompras_clicked();

    void on_btnNListaTarefas_clicked();

private:
    Ui::NListaDialog *ui;
    bool novo;
    char tipo;
    QString nomeNLista;

    QMap<QString, QVector<Tarefa>> tarefas;
    QMap<QString, QVector<Compras>> compras;
};

#endif // NLISTADIALOG_H
