#include "listas.h"
#include "ui_listas.h"
#include <QDebug>

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

void Listas::atualizarCompras(){

    int linha = 0;

    ui->tabelaListaDeCompras->setRowCount(0);

    for(auto show : compras[nomeArquivoAtual]){

        add = false;

        QTableWidgetItem *uncheck = new QTableWidgetItem();
        QTableWidgetItem *check = new QTableWidgetItem();

        uncheck->setCheckState(Qt::Unchecked);
        check->setCheckState(Qt::Checked);

        ui->tabelaListaDeCompras->insertRow(linha);

        if(show.check) ui->tabelaListaDeCompras->setItem(linha, 0, check);
        else ui->tabelaListaDeCompras->setItem(linha, 0, uncheck);

        ui->tabelaListaDeCompras->setItem(linha, 1, new QTableWidgetItem(show.getNome()));
        ui->tabelaListaDeCompras->setItem(linha, 2, new QTableWidgetItem(QString::number(show.getQuantidade())));

        if(show.getPreco() != 0){
            ui->tabelaListaDeCompras->setItem(linha, 3, new QTableWidgetItem(QString::number(show.getPreco())));
            ui->tabelaListaDeCompras->setItem(linha, 4, new QTableWidgetItem(QString::number(show.getTotal())));
        }

        ui->tabelaListaDeCompras->setItem(linha, 5, new QTableWidgetItem(QString::number(show.getId())));

        ui->tabelaListaDeCompras->setRowHeight(linha++, 5);
    }

    add = true;
}

void Listas::setNAA(QString temp)
{
    nomeArquivoAtual = temp;
}

void Listas::setFormatacaoCompras(){

    ui->tabelaListaDeCompras->setColumnWidth(0,5);
    ui->tabelaListaDeCompras->setColumnWidth(1,405);
    ui->tabelaListaDeCompras->setColumnWidth(2,90);
    ui->tabelaListaDeCompras->setColumnWidth(3,80);
    ui->tabelaListaDeCompras->setColumnWidth(4,80);
    ui->tabelaListaDeCompras->hideColumn(5);

    QHeaderView *headerGoods = ui->tabelaListaDeCompras->horizontalHeader();

    headerGoods->setSortIndicator(0, Qt::DescendingOrder);
    headerGoods->setSortIndicatorShown(false);
    connect(headerGoods, SIGNAL(sectionClicked(int)), ui->tabelaListaDeCompras, SLOT (sortByColumn(int)));
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
        if(nlista.tipo == 't'){

            ui->paginas->setCurrentIndex(2);

            //setFormatacaoTarefas(); - implementar depois

            ui->tituloListaTarefas->setText(nlista.nomeNLista.toUpper());
        }
    }
}

void Listas::on_btnAddCompras_clicked()
{
    NItemDialog nitem;
    nitem.preencherVetor(compras[nomeArquivoAtual]);

    nitem.setModal(true);
    nitem.exec();

    if(nitem.novo){

        Compras temp;

        temp.setNome(nitem.ent1.getNome());
        temp.setId(idCompras++);

        setNAA(ui->tituloListaCompras->text());

        compras[nomeArquivoAtual].push_back(temp);

        atualizarCompras();
    }
}

bool Listas::procCompra(QString item){

    for(auto proc : compras[nomeArquivoAtual]){
        if(proc.getNome() == item) return true;
    }
    return false;
}

void Listas::on_tabelaListaDeCompras_cellChanged(int row, int column)
{
    if(add){

        int p = 0;
        int id = ui->tabelaListaDeCompras->item(row,5)->text().toInt();
        bool troca = false;
        for(auto proc : compras[nomeArquivoAtual]){

            if(proc.getId() == id){
                qDebug() << ui->tabelaListaDeCompras->item(row, column)->text();
                switch(column){

                case 0: break;
                case 1: if(procCompra(ui->tabelaListaDeCompras->item(row, column)->text()) or compras[nomeArquivoAtual][p].setNome(ui->tabelaListaDeCompras->item(row, column)->text())){
                        QMessageBox::warning(this, "Erro", "valor inválido!");
                            break;}
                        else{
                        troca = true;
                        break;}
                case 2: if(compras[nomeArquivoAtual][p].setQuantidade(ui->tabelaListaDeCompras->item(row, column)->text().toInt())){
                            QMessageBox::warning(this, "Erro", "valor inválido!");
                            break;}
                        else{
                        troca = true;
                        break;}
                case 3: if(compras[nomeArquivoAtual][p].setPreco(ui->tabelaListaDeCompras->item(row, column)->text().toFloat())){
                            QMessageBox::warning(this, "Erro", "valor inválido!");
                            break;}
                        else{
                        troca = true;
                        break;}
                default: break;
                }
            }

            if(troca) break;
            p++;
        }

        if(column > 0)atualizarCompras();
    }

    else add = false;
}


void Listas::on_btnOcultarSelecionados_clicked()
{
    for (int i = 0; i < ui->tabelaListaDeCompras->rowCount(); i++) {
        QTableWidgetItem *check = ui->tabelaListaDeCompras->item(i,0);
        if (check->checkState()) ui->tabelaListaDeCompras->hideRow(i);
    }
}

void Listas::on_ExibirOcultos_clicked()
{
    for (int i = 0; i < ui->tabelaListaDeCompras->rowCount(); i++) {
        QTableWidgetItem *check = ui->tabelaListaDeCompras->item(i,0);
        if (check->checkState()) ui->tabelaListaDeCompras->showRow(i);
    }
}

void Listas::on_btnApagarSelecionados_clicked()
{
    for (int i = ui->tabelaListaDeCompras->rowCount()-1; i >= 0; i--) {

        QTableWidgetItem *check = ui->tabelaListaDeCompras->item(i,0);

        if (check->checkState()){

            QString temp = ui->tabelaListaDeCompras->item(i,1)->text();

            for(int j = (compras[nomeArquivoAtual].size() - 1); j >= 0; j--){
                if(compras[nomeArquivoAtual][j].getNome() == temp) compras[nomeArquivoAtual].erase(compras[nomeArquivoAtual].begin()+j);
            }
        }
    }

    atualizarCompras();
}

void Listas::on_btnListasSalvas_clicked()
{
    ui->paginas->setCurrentIndex(3);
}

void Listas::on_btnSalvarListaCompras_clicked()
{
    QFile arquivo(salvos+nomeArquivoAtual);
}
