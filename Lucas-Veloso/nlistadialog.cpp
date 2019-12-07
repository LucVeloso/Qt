#include "nlistadialog.h"
#include "ui_nlistadialog.h"



NListaDialog::NListaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NListaDialog)
{
    ui->setupUi(this);

    novo = false;

    setWindowTitle("Nova Lista");

    QPixmap pix(":/icones/cart.png");
    QIcon btn(pix.scaled(100,100,Qt::KeepAspectRatio));
    ui->btnNListaCompras->setIcon(btn);
    ui->btnNListaCompras->setIconSize(QSize(100, 100));

    QPixmap pix1(":/icones/checkbox.png");
    QIcon btn1(pix1.scaled(100,100,Qt::KeepAspectRatio));
    ui->btnNListaTarefas->setIcon(btn1);
    ui->btnNListaTarefas->setIconSize(QSize(100, 100));
}

bool NListaDialog::validCompras(QString nome){
    if(nome.size() < 3)
        for(auto c : compras.keys()) if(c == nome) return false;
    else return true;
}

bool NListaDialog::validTarefas(QString nome){
    if(nome.size() < 3)
        for(auto c : compras.keys()) if(c == nome) return false;
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

    if(validCompras(nomeNLista)){

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
    if(validTarefas(nomeNLista)){

        novo = true;
        close();
    }
    else{

        ui->NListaInvalido->setText("Nome Inválido");
    }
}

char NListaDialog::getTipo() const
{
    return tipo;
}

void NListaDialog::carregarMap(QMap<QString, QVector<Compras> > c, QMap<QString, QVector<Tarefa> > t)
{
    compras = c;
    tarefas = t;
}

QString NListaDialog::getNomeNLista() const
{
    return nomeNLista;
}

bool NListaDialog::getNovo() const
{
    return novo;
}
