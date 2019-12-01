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

bool NItemDialog::proc(QString item)
{
    for(auto &proc : comp){
        if(proc.getNome() == item){
            return true;}
    }
    return false;
}

void NItemDialog::preencherVetor(QVector<Compras> &v)
{
    comp = v;
}

void NItemDialog::on_btnAdd_clicked()
{
    QString entrada = ui->NItemEnt->text();

    if(proc(entrada) or ent1.setNome(entrada)) ui->msgErro->setText("Item inválido");
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
