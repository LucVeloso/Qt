#include "nitemdialog.h"
#include "ui_nitemdialog.h"
#include <QDebug>
NItemDialog::NItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NItemDialog)
{
    ui->setupUi(this);
    setWindowTitle("Novo Item");
}

NItemDialog::~NItemDialog()
{
    delete ui;
}

bool NItemDialog::procComp(QString item)
{
    for(auto &proc : comp){
        if(proc.getNome() == item){
            return true;}
    }
    return false;
}

bool NItemDialog::procTar(QString item)
{
    for(auto &proc : tar){
        if(proc.getNome() == item){
            return true;}
    }
    return false;
}

void NItemDialog::preencherVetor(QVector<Compras> &v)
{
    comp = v;
}

void NItemDialog::preencherVetor(QVector<Tarefa> &v)
{
    tar = v;
}

void NItemDialog::on_btnAdd_clicked()
{
    QString entrada = ui->NItemEnt->text();

    if(procComp(entrada) or procTar(entrada) or ent1.setNome(entrada) or ent.setNome(entrada)) ui->msgErro->setText("Item inválido");
    else{

        ui->NItemEnt->clear();
        ui->msgErro->clear();
        novo = true;
        close();
    }
}

void NItemDialog::on_btnCancelar_clicked()
{
    ui->NItemEnt->clear();
    novo = false;
    close();
}
