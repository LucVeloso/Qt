#ifndef COMPRAS_H
#define COMPRAS_H

#include <QString>
#include "tarefa.h"

class Compras:public Tarefa
{
public:
    Compras();

    int getQuantidade() const;
    bool setQuantidade(int value);

    float getPreco() const;
    bool setPreco(float value);

    float getTotal() const;
    void setTotal();

private:

    int quantidade;
    float preco;
    float total;
};

#endif // COMPRAS_H
