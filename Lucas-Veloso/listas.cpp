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

void Listas::atualizarCompras(QVector<Compras> vetor){

    int linha = 0;

    ui->tabelaListaDeCompras->setRowCount(0);



    for(auto show : vetor){

        QTableWidgetItem *uncheck = new QTableWidgetItem();
        QTableWidgetItem *check = new QTableWidgetItem();

        uncheck->setCheckState(Qt::Unchecked);
        check->setCheckState(Qt::Checked);

        ui->tabelaListaDeCompras->insertRow(linha);

        if(show.check) ui->tabelaListaDeCompras->setItem(linha, 0, check);
        else ui->tabelaListaDeCompras->setItem(linha, 0, uncheck);

        ui->tabelaListaDeCompras->setItem(linha, 1, new QTableWidgetItem(show.getNome()));
        ui->tabelaListaDeCompras->setItem(linha, 2, new QTableWidgetItem(QString::number(show.getQuantidade())));

        ui->tabelaListaDeCompras->setRowHeight(linha++, 5);
    }
}

void Listas::setFormatacaoCompras(){

    ui->tabelaListaDeCompras->setColumnWidth(0,20);
    ui->tabelaListaDeCompras->setColumnWidth(1,205);
    ui->tabelaListaDeCompras->setColumnWidth(2,50);
    ui->tabelaListaDeCompras->setColumnWidth(3,75);
    ui->tabelaListaDeCompras->setColumnWidth(4,75);
}

void Listas::on_btnNLista_clicked()
{
    QString lista;
    NListaDialog nlista;

    nlista.setModal(true);
    nlista.exec();

    if(nlista.novo){
        if(nlista.tipo == 'c'){
            ui->paginas->setCurrentIndex(1);
            setFormatacaoCompras();
            ui->tituloListaCompras->setText(nlista.nomeNLista.toUpper());
        }
        else ui->paginas->setCurrentIndex(2);
    }
}

void Listas::on_btnAddCompras_clicked()
{
    QString chave = ui->tituloListaCompras->text();
    NItemDialog nitem;
    nitem.setModal(true);
    nitem.exec();

    if(nitem.novo){

        Compras temp;

        temp.setNome(nitem.ent.getNome());
        temp.setId(idCompras++);

        compras[chave].push_back(temp);
        mostrarCompras.push_back(temp);

        atualizarCompras(mostrarCompras);


//        QString nome = nitem.ent.getNome();

//        int linhas = ui->tabelaListaDeCompras->rowCount();

//        QTableWidgetItem *check = new QTableWidgetItem();

//        check->setCheckState(Qt::Unchecked);

//        ui->tabelaListaDeCompras->insertRow(linhas);
//        ui->tabelaListaDeCompras->setItem(linhas, 0, check);
//        ui->tabelaListaDeCompras->setItem(linhas, 1, new QTableWidgetItem(nome));

//        ui->tabelaListaDeCompras->setRowHeight(linhas, 5);
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

void Listas::on_tabelaListaDeCompras_cellChanged(int row, int column)
{

    int proc = mostrarCompras[row].getId();

    QVector<Compras> vetor = compras.second;

    for(auto change : vetor){

        if(proc == change.getId()){

            switch(column){

            case 0: break;
            case 1: change.setNome(ui->tabelaListaDeCompras->item(row, column)->text());
            }
        }
    }




}
