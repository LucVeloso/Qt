#include "nlistadialog.h"
#include "ui_nlistadialog.h"

NListaDialog::NListaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NListaDialog)
{
    ui->setupUi(this);
    setWindowTitle("Nova Lista");
}

bool NListaDialog::validNome(QString nome){
    if(nome.size() < 3) return false;
    else return true;
}

NListaDialog::~NListaDialog()
{
    delete ui;
}

void NListaDialog::on_btnNListaCompras_clicked()
{

    tipo = 'c';
    nomeNLista = ui->NomeEnt->text();

    if(validNome(nomeNLista)){

        novo = true;
        close();
    }
    else{

        ui->NListaInvalido->setText("Nome Inválido");
    }

}

void NListaDialog::on_btnNListaTarefas_clicked()
{

    tipo = 't';
    nomeNLista = ui->NomeEnt->text();
    if(validNome(nomeNLista)){

        novo = true;
        close();
    }
    else{

        ui->NListaInvalido->setText("Nome Inválido");
    }
}
