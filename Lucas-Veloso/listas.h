#ifndef LISTAS_H
#define LISTAS_H

#include <QMainWindow>
#include <QString>
#include "nitemdialog.h"
#include "tarefa.h"
#include "compras.h"
#include "nlistadialog.h"
#include <QMap>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class Listas; }
QT_END_NAMESPACE

class Listas : public QMainWindow
{
    Q_OBJECT

public:
    Listas(QWidget *parent = nullptr);
    ~Listas();

    void setFormatacaoCompras();
    void atualizarCompras(QVector<Compras> vetor);

    QMap<QString, QVector<Tarefa>> tarefas;
    QMap<QString, QVector<Compras>> compras;
    QVector<Tarefa> mostrarTarefas;
    QVector<Compras> mostrarCompras;

private slots:


    void on_btnNLista_clicked();

    void on_btnAddCompras_clicked();

private:
    Ui::Listas *ui;
    Tarefa tEnt;

};
#endif // LISTAS_H
