#include "nlistadialog.h"
#include "ui_nlistadialog.h"

#include <QDebug>

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

NListaDialog::~NListaDialog()
{
    delete ui;
}

bool NListaDialog::validCompras(QString nome){

    for(auto c : compras.toStdMap()){

        if(c.first == nome) return false;
    }
    if(nome.size() < 3) return false;
    else return true;
}

bool NListaDialog::validTarefas(QString nome){

    qDebug() << compras.size();
    for(auto t : tarefas.toStdMap()){

        if(t.first == nome) return false;
    }
    if(nome.size() < 3) return false;
    else return true;
}

void NListaDialog::on_btnNListaCompras_clicked()
{

    tipo = 'c';
    nomeNLista = ui->NomeEnt->text().toUpper();

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
    nomeNLista = ui->NomeEnt->text().toUpper();
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
