#include "compras.h"

Compras::Compras()
{
    quantidade = 1;
    preco = 0;
    total = 0;
}

int Compras::getQuantidade() const
{
    return quantidade;
}

bool Compras::setQuantidade(int value)
{
    if(value > 0)
    {
        quantidade = value;
        setTotal();
        return false;
    }
    else return true;
}

float Compras::getPreco() const
{
    return preco;
}

bool Compras::setPreco(float value)
{
    if(value >= 0)
    {
        preco = value;
        setTotal();
        return false;
    }
    else return true;
}

float Compras::getTotal() const
{
    return total;
}

void Compras::setTotal()
{
    total = quantidade * preco;
}
