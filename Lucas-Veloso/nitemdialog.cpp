#include "nitemdialog.h"
#include "ui_nitemdialog.h"

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

void NItemDialog::on_btnAdd_clicked()
{
    QString entrada = ui->NItemEnt->text();
    if(ent.setNome(entrada)){

        ui->msgErro->setText("Item inválido");
    }
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
