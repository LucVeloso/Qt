#include "listas.h"
#include "ui_listas.h"
#include <QDebug>

Listas::Listas(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Listas)
{
    ui->setupUi(this);
    add = true;
    salvo = true;

    caminho = qApp->applicationDirPath();
    qDebug() << caminho;
    QStringList op;

    op = caminho.split("/");
    caminho.clear();

    for(int i = 0; i < op.size() - 2; i++){
        caminho += op[i];
        if(i < op.size() - 3) caminho += "/";
    }

    caminho += "/Lucas-Veloso";

    caminhoPastaCompras = caminho + "/ComprasSalvas/";
    caminhoPastaTCompras = caminho + "/ComprasTemplate/";
    caminhoPastaTarefas = caminho + "/TarefasSalvas/";
    caminhoPastaTTarefas = caminho + "/TarefasTemplate/";

    qDebug() << caminho;

    QAction *acaoCompras = new QAction(this);
    acaoCompras->setShortcut(QKeySequence("Ctrl+Q"));
    connect(acaoCompras, SIGNAL(triggered()), this, SLOT(on_btnSalvarListaCompras_clicked()));
    this->addAction(acaoCompras);

    QAction *acaoTarefas = new QAction(this);
    acaoTarefas->setShortcut(QKeySequence("Ctrl+E"));
    connect(acaoTarefas, SIGNAL(triggered()), this, SLOT(on_btnSalvarListaTarefas_clicked()));
    this->addAction(acaoTarefas);

    ui->tabelaListaDeCompras->setColumnWidth(0,5);
    ui->tabelaListaDeCompras->setColumnWidth(1,255);
    ui->tabelaListaDeCompras->setColumnWidth(2,90);
    ui->tabelaListaDeCompras->setColumnWidth(3,80);
    ui->tabelaListaDeCompras->setColumnWidth(4,80);
    ui->tabelaListaDeCompras->hideColumn(5);

    QHeaderView *headerCompras = ui->tabelaListaDeCompras->horizontalHeader();

    headerCompras->setSortIndicator(1, Qt::DescendingOrder);
    headerCompras->setSortIndicatorShown(false);
    connect(headerCompras, SIGNAL(sectionClicked(int)), ui->tabelaListaDeCompras, SLOT (sortByColumn(int)));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ui->tabelaListaDeTarefas->setColumnWidth(0,5);
    ui->tabelaListaDeTarefas->hideColumn(2);

    QHeaderView *headerTarefas = ui->tabelaListaDeTarefas->horizontalHeader();

    headerTarefas->setSortIndicator(1, Qt::DescendingOrder);
    headerTarefas->setSortIndicatorShown(false);
    connect(headerTarefas, SIGNAL(sectionClicked(int)), ui->tabelaListaDeTarefas, SLOT (sortByColumn(int)));

    QDir directory(caminhoPastaCompras);

    QStringList entrada = directory.entryList(QStringList() << "*.csv", QDir::Files);

    for(auto &mudar : entrada){


        QFile arquivo(caminhoPastaCompras + mudar);

        arquivo.open(QIODevice::ReadOnly);

        QString linha;
        QStringList dados;

        QString chave = tirarExt(mudar);

        while(!arquivo.atEnd()){
            Compras temp;

            linha = arquivo.readLine();
            dados = linha.split(",");

            if(dados[0] == "V") temp.setCheck(true);
            else temp.setCheck(false);

            temp.setId(dados[1].toInt());
            temp.setNome(dados[2]);
            temp.setQuantidade(dados[3].toInt());
            temp.setPreco(dados[4].toFloat());

            compras[mudar].push_back(temp);
        }
    }
    //começo da função de carregar
}

Listas::~Listas()
{
    delete ui;
}

QString Listas::tirarExt(QString &a){

    QStringList l = a.split(".");
    QString saida = l[0];

    return saida;
}

////////////////////////////////////HOME///////////////////////////////////////////////////////////

void Listas::on_btnNLista_clicked()
{
    QString lista;
    NListaDialog nlista;

    nlista.setModal(true);
    nlista.exec();

    if(nlista.novo){

        nomeArquivoAtual = nlista.nomeNLista.toUpper();

        if(nlista.tipo == 'c'){

            ui->paginas->setCurrentIndex(1);

            ui->tituloListaCompras->setText(nomeArquivoAtual);

            ui->info_NItens_ListaCompras->setText(QString::number(0));
            ui->info_ValorTotal->setText(QString::number(0.00));
            ui->info_NIntensSelecionados->setText(QString::number(0));
        }
        if(nlista.tipo == 't'){

            ui->paginas->setCurrentIndex(2);

            ui->tituloListaTarefas->setText(nomeArquivoAtual);

            ui->info_NItens_ListaTarefas->setText(QString::number(0));
            ui->info_NIntensSelecionados_Tarefas->setText(QString::number(0));
        }
    }
}

void Listas::on_btnListasSalvas_clicked()
{
    ui->paginas->setCurrentIndex(3);


}

///////////////////////////////////COMPRAS/////////////////////////////////////////////////////////////

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

        if(show.getCheck()) ui->tabelaListaDeCompras->setItem(linha, 0, check);
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

bool Listas::procCompra(QString item){

    for(auto proc : compras[nomeArquivoAtual]){
        if(proc.getNome() == item) return true;
    }
    return false;
}

void Listas::atualizarEstatisticasLCompras()
{
    int itensSelecionados = 0;
    double total = 0;

    for (int i = 0; i < ui->tabelaListaDeCompras->rowCount(); i++) {
        QTableWidgetItem *check = ui->tabelaListaDeCompras->item(i,0);
        if (check->checkState()) itensSelecionados++;
    }

    for (auto soma : compras[nomeArquivoAtual]) {
        total += soma.getTotal();
    }

    ui->info_NItens_ListaCompras->setText(QString::number(compras[nomeArquivoAtual].size()));
    ui->info_ValorTotal->setText(QString::number(total));
    ui->info_NIntensSelecionados->setText(QString::number(itensSelecionados));
}

void Listas::on_btnSalvarListaCompras_clicked()
{
    salvo = true;

    qDebug() << caminhoPastaCompras;

    QFile arquivo(caminhoPastaCompras + nomeArquivoAtual + ".csv");

    arquivo.open(QIODevice::WriteOnly);

    for(auto a : compras[nomeArquivoAtual]){

        QString check;

        if(a.getCheck()) check = "V";
        else check = "F";

        QString linha = check + ","
                        + QString::number(a.getId()) + ","
                        + a.getNome() + ","
                        + QString::number(a.getQuantidade()) + ","
                        + QString::number(a.getPreco()) + ","
                        + "\n";

        arquivo.write(linha.toLocal8Bit());
    }

    arquivo.close();
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

        compras[nomeArquivoAtual].push_back(temp);

        atualizarCompras();
        on_btnOcultarSelecionados_clicked();
        atualizarEstatisticasLCompras();

        salvo = false;
    }
}

void Listas::on_tabelaListaDeCompras_cellChanged(int row, int column)
{
    if(add){

        int p = 0;
        int id = ui->tabelaListaDeCompras->item(row,5)->text().toInt();
        bool troca = false;
        for(auto proc : compras[nomeArquivoAtual]){

            if(proc.getId() == id){
                switch(column){

                case 0: if(ui->tabelaListaDeCompras->item(row, 0)->checkState())
                            compras[nomeArquivoAtual][p].setCheck(true);
                        else compras[nomeArquivoAtual][p].setCheck(false);
                        break;
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
        if(column > 0){
            atualizarCompras();
            on_btnOcultarSelecionados_clicked();
            atualizarEstatisticasLCompras();
        }
        else atualizarEstatisticasLCompras();
        salvo = false;
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
    salvo = false;
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
    atualizarEstatisticasLCompras();
}

void Listas::limparCompras(){

    ui->tabelaListaDeCompras->setRowCount(0);
    ui->info_NIntensSelecionados->setText(QString::number(0));
    ui->info_ValorTotal->setText(QString::number(0));
    ui->info_NItens_ListaCompras->setText(QString::number(0));
}

void Listas::on_btn_home_ListaCompras_clicked()
{
    if(salvo)ui->paginas->setCurrentIndex(0);
    else{
        QMessageBox::StandardButton resposta = QMessageBox::question(this, "Sair", "Sair sem salvar?", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);

        if (resposta == QMessageBox::Yes){
            on_btnSalvarListaCompras_clicked();
            salvo = true;
            ui->paginas->setCurrentIndex(0);
            limparCompras();
        }
        else{
            ui->paginas->setCurrentIndex(0);
            limparCompras();
        }
    }
}

///////////////////////////////////TAREFAS///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Listas::atualizarTarefas()
{

    int linha = 0;

    ui->tabelaListaDeTarefas->setRowCount(0);

    for(auto show : tarefas[nomeArquivoAtual]){

        add = false;

        QTableWidgetItem *uncheck = new QTableWidgetItem();
        QTableWidgetItem *check = new QTableWidgetItem();

        uncheck->setCheckState(Qt::Unchecked);
        check->setCheckState(Qt::Checked);

        ui->tabelaListaDeTarefas->insertRow(linha);

        if(show.getCheck()) ui->tabelaListaDeTarefas->setItem(linha, 0, check);
        else ui->tabelaListaDeTarefas->setItem(linha, 0, uncheck);

        ui->tabelaListaDeTarefas->setItem(linha, 1, new QTableWidgetItem(show.getNome()));

        ui->tabelaListaDeTarefas->setItem(linha, 2, new QTableWidgetItem(QString::number(show.getId())));

        ui->tabelaListaDeTarefas->setRowHeight(linha++, 5);
    }

    add = true;
}

void Listas::atualizarEstatisticasLTarefas()
{
    int itensSelecionados = 0;

    for (int i = 0; i < ui->tabelaListaDeTarefas->rowCount(); i++) {
        QTableWidgetItem *check = ui->tabelaListaDeTarefas->item(i,0);
        if (check->checkState()) itensSelecionados++;
    }

    ui->info_NItens_ListaTarefas->setText(QString::number(tarefas[nomeArquivoAtual].size()));
    ui->info_NIntensSelecionados_Tarefas->setText(QString::number(itensSelecionados));
}

bool Listas::procTarefa(QString item){

    for(auto proc : tarefas[nomeArquivoAtual]){
        if(proc.getNome() == item) return true;
    }
    return false;
}

void Listas::limparTarefas(){

    ui->tabelaListaDeTarefas->setRowCount(0);
    ui->info_NIntensSelecionados_Tarefas->setText(QString::number(0));
    ui->info_NItens_ListaTarefas->setText(QString::number(0));
}

void Listas::on_btn_home_ListaTarefas_clicked()
{
    if(salvo)ui->paginas->setCurrentIndex(0);
    else{
        QMessageBox::StandardButton resposta = QMessageBox::question(this, "Sair", "Sair sem salvar?", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);

        if (resposta == QMessageBox::Yes){
            on_btnSalvarListaTarefas_clicked();
            salvo = true;
            ui->paginas->setCurrentIndex(0);
            limparTarefas();
        }
        else{
            ui->paginas->setCurrentIndex(0);
            limparTarefas();
        }
    }
}

void Listas::on_btnSalvarListaTarefas_clicked()
{
    salvo = true;

    QFile arquivo(caminhoPastaTarefas + nomeArquivoAtual + ".csv");

    arquivo.open(QIODevice::WriteOnly);

    for(auto a : tarefas[nomeArquivoAtual]){

        QString check;

        if(a.getCheck()) check = "V";
        else check = "F";

        QString linha = check + ","
                        + QString::number(a.getId()) + ","
                        + a.getNome() + ","
                        + "\n";

        arquivo.write(linha.toLocal8Bit());
    }

    arquivo.close();
}

void Listas::on_btnAddTarefas_clicked()
{
    NItemDialog nitem;
    nitem.preencherVetor(tarefas[nomeArquivoAtual]);

    nitem.setModal(true);
    nitem.exec();

    if(nitem.novo){

        Tarefa temp;

        temp.setNome(nitem.ent.getNome());
        temp.setId(idTarefas++);

        tarefas[nomeArquivoAtual].push_back(temp);

        atualizarTarefas();
        on_btnOcultarSelecionados_Tarefas_clicked();
        atualizarEstatisticasLTarefas();

        salvo = false;
    }
}

void Listas::on_tabelaListaDeTarefas_cellChanged(int row, int column)
{
    if(add){

        int p = 0;
        int id = ui->tabelaListaDeTarefas->item(row,2)->text().toInt();
        bool troca = false;
        for(auto proc : tarefas[nomeArquivoAtual]){

            if(proc.getId() == id){
                switch(column){

                case 0: if(ui->tabelaListaDeTarefas->item(row, 0)->checkState())
                            tarefas[nomeArquivoAtual][p].setCheck(true);
                        else tarefas[nomeArquivoAtual][p].setCheck(false);
                        break;
                case 1: if(procTarefa(ui->tabelaListaDeTarefas->item(row, column)->text()) or tarefas[nomeArquivoAtual][p].setNome(ui->tabelaListaDeTarefas->item(row, column)->text())){
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
        if(column > 0){
            atualizarTarefas();
            on_btnOcultarSelecionados_Tarefas_clicked();
            atualizarEstatisticasLTarefas();
        }
        else atualizarEstatisticasLTarefas();
        salvo = false;
    }

    else add = false;
}

void Listas::on_btnOcultarSelecionados_Tarefas_clicked()
{
    for (int i = 0; i < ui->tabelaListaDeTarefas->rowCount(); i++) {
        QTableWidgetItem *check = ui->tabelaListaDeTarefas->item(i,0);
        if (check->checkState()) ui->tabelaListaDeTarefas->hideRow(i);
    }
}

void Listas::on_ExibirOcultos_Tarefas_clicked()
{
    for (int i = 0; i < ui->tabelaListaDeTarefas->rowCount(); i++) {
        QTableWidgetItem *check = ui->tabelaListaDeTarefas->item(i,0);
        if (check->checkState()) ui->tabelaListaDeTarefas->showRow(i);
    }
}

void Listas::on_btnApagarSelecionados_Tarefas_clicked()
{

    salvo = false;
    for (int i = ui->tabelaListaDeTarefas->rowCount()-1; i >= 0; i--) {

        QTableWidgetItem *check = ui->tabelaListaDeTarefas->item(i,0);

        if (check->checkState()){

            QString temp = ui->tabelaListaDeTarefas->item(i,1)->text();

            for(int j = (tarefas[nomeArquivoAtual].size() - 1); j >= 0; j--){
                if(tarefas[nomeArquivoAtual][j].getNome() == temp) tarefas[nomeArquivoAtual].erase(tarefas[nomeArquivoAtual].begin()+j);
            }
        }
    }

    atualizarTarefas();
    atualizarEstatisticasLTarefas();
}

////////////////////////////////////////////CARREGAR///////////////////////////////////////////////////////////////////////////////////////////

void Listas::on_btn_home_ListasSalvas_clicked()
{
    ui->paginas->setCurrentIndex(0);
}
