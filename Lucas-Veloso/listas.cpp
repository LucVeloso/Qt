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

void Listas::atualizarCompras(){

    int linha = 0;

    ui->tabelaListaDeCompras->setRowCount(0);

    for(auto show : mostrarCompras){

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

        setNAA(chave);

        compras[chave].push_back(temp);
        mostrarCompras.push_back(temp);

        atualizarCompras();
    }
}

void Listas::on_tabelaListaDeCompras_cellChanged(int row, int column)
{
    if(add){
        switch(column){

        case 0: break;
        case 1: if(mostrarCompras[row].setNome(ui->tabelaListaDeCompras->item(row, column)->text())){
                    QMessageBox::warning(this, "Erro", "valor inválido!");
                    break;}
                else  break;
        case 2: if(mostrarCompras[row].setQuantidade(ui->tabelaListaDeCompras->item(row, column)->text().toInt())){
                QMessageBox::warning(this, "Erro", "valor inválido!");
                break;}
            else  break;
        case 3: if(mostrarCompras[row].setPreco(ui->tabelaListaDeCompras->item(row, column)->text().toFloat())){
                    QMessageBox::warning(this, "Erro", "valor inválido!");
                    break;}
                else  break;
        case 4: break;
        }

        int proc = mostrarCompras[row].getId();

        QVector<Compras> vetor;

        for(auto nomeVetor : compras){
            vetor = nomeVetor;
        }

        for(auto &change : vetor){

            if(proc == change.getId()){

                switch(column){

                case 0: break;
                case 1: if(change.setNome(ui->tabelaListaDeCompras->item(row, column)->text())){
                            QMessageBox::warning(this, "Erro", "valor inválido!");
                            break;}
                        else  break;
                case 2: if(change.setQuantidade(ui->tabelaListaDeCompras->item(row, column)->text().toInt())){
                            QMessageBox::warning(this, "Erro", "valor inválido!");
                            break;}
                        else  break;
                case 3: if(change.setPreco(ui->tabelaListaDeCompras->item(row, column)->text().toFloat())){
                            QMessageBox::warning(this, "Erro", "valor inválido!");
                            break;}
                        else  break;
                case 4: break;


                }

            }
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

void Listas::on_btnApagarSelecionados_clicked()
{
    for (int i = ui->tabelaListaDeCompras->rowCount()-1; i >= 0; i--) {
        QTableWidgetItem *check = ui->tabelaListaDeCompras->item(i,0);
        if (check->checkState()){

            mostrarCompras.erase(mostrarCompras.begin()+i);
        }
    }
    atualizarCompras();
}

void Listas::on_ExibirOcultos_clicked()
{
    for (int i = 0; i < ui->tabelaListaDeCompras->rowCount(); i++) {
        QTableWidgetItem *check = ui->tabelaListaDeCompras->item(i,0);
        if (check->checkState()) ui->tabelaListaDeCompras->showRow(i);
    }
}

void Listas::on_btnListasSalvas_clicked()
{
    ui->paginas->setCurrentIndex(3);
}

void Listas::on_btnSalvarListaCompras_clicked()
{
    QFile arquivo(salvos+nomeArquivoAtual);
}
