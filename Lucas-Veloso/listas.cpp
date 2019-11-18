#include "listas.h"
#include "ui_listas.h"


Listas::Listas(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Listas)
{
    ui->setupUi(this);
}

Listas::~Listas()
{
    delete ui;
}

void Listas::setFormatacao(){

    ui->tabelaListaDeCompras->setColumnWidth(0,20);
    ui->tabelaListaDeCompras->setColumnWidth(1,205);
    ui->tabelaListaDeCompras->setColumnWidth(2,50);
    ui->tabelaListaDeCompras->setColumnWidth(3,75);
    ui->tabelaListaDeCompras->setColumnWidth(4,75);
}

void Listas::on_btnNLista_clicked()
{
    ui->paginas->setCurrentIndex(1);
    setFormatacao();

}

void Listas::on_btnAdd_clicked()
{
    nitem.setModal(true);
    nitem.exec();

    if(nitem.novo){
    QString nome = nitem.ent.getNome();

    int linhas = ui->tabelaListaDeCompras->rowCount();

    QTableWidgetItem *check = new QTableWidgetItem();

    check->setCheckState(Qt::Unchecked);

    ui->tabelaListaDeCompras->insertRow(linhas);
    ui->tabelaListaDeCompras->setItem(linhas, 0, check);
    ui->tabelaListaDeCompras->setItem(linhas, 1, new QTableWidgetItem(nome));

    ui->tabelaListaDeCompras->setRowHeight(linhas, 5);
    }

//    for (int i = 0; i < t->rowCount(); i++) {
//        for (int j = 0; j < t->columnCount(); j++) {
//            QWidget *pWidget = t->cellWidget(i, j);
//            QCheckBox *checkbox = pWidget->findChild<QCheckBox *>();
//            if (checkbox && checkbox->isChecked())
//                qDebug() << t->horizontalHeaderItem(j)->text() << i;
//        }
//    } laço para varrer célular procurando por checkboxes

}
