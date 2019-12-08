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
#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Listas; }
QT_END_NAMESPACE

class Listas : public QMainWindow
{
    Q_OBJECT

public:
    Listas(QWidget *parent = nullptr);
    ~Listas();

    QString tirarExt(QString &a);
    void carregar();
////////////////////////////////////////////////
    void atualizarCompras();
    void atualizarEstatisticasLCompras();
    void setNAA(QString temp);
    bool procCompra(QString item);
    void limparCompras();
////////////////////////////////////////////////
    void atualizarTarefas();
    void atualizarEstatisticasLTarefas();
    bool procTarefa(QString item);
    void limparTarefas();


private slots:

    void on_btnNLista_clicked();

    void on_btnAddCompras_clicked();

    void on_tabelaListaDeCompras_cellChanged(int row, int column);

    void on_btnOcultarSelecionados_clicked();

    void on_btnApagarSelecionados_clicked();

    void on_ExibirOcultos_clicked();

    void on_btnListasSalvas_clicked();

    void on_btnSalvarListaCompras_clicked();

    void on_btn_home_ListaCompras_clicked();

    void on_btn_home_ListaTarefas_clicked();

    void on_btnSalvarListaTarefas_clicked();

    void on_btnOcultarSelecionados_Tarefas_clicked();

    void on_ExibirOcultos_Tarefas_clicked();

    void on_btnApagarSelecionados_Tarefas_clicked();

    void on_btnAddTarefas_clicked();

    void on_tabelaListaDeTarefas_cellChanged(int row, int column);

    void on_btn_home_ListasSalvas_clicked();

    void on_btnSalvarListaComprasTemplate_clicked();

    void on_btnSalvarListaTarefasTemplate_clicked();

    void on_tabelaMostrarSalvosCompras_cellDoubleClicked(int row, int column);

    void on_tabelaMostrarSalvosTarefas_cellDoubleClicked(int row, int column);

    void on_tabelaMostrarTemplateCompras_cellDoubleClicked(int row, int column);

    void on_tabelaMostrarTemplateTarefas_cellDoubleClicked(int row, int column);

private:
    Ui::Listas *ui;

    QString pastaComprasSalvas;
    QString pastaTarefasSalvas;
    QString pastaComprasTemplate;
    QString pastaTarefasTemplate;

    bool salvo;
    bool add;
    bool oculto;

    int idCompras = 0;
    int idTarefas = 0;

    QString nomeArquivoAtual;

    QMap<QString, QVector<Tarefa>> tarefas;
    QMap<QString, QVector<Compras>> compras;
    QMap<QString, QVector<Tarefa>> templatesTarefas;
    QMap<QString, QVector<Compras>> templatesCompras;
};
#endif // LISTAS_H
