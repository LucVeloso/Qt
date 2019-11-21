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

void Compras::setQuantidade(int value)
{
    quantidade = value;
}

float Compras::getPreco() const
{
    return preco;
}

void Compras::setPreco(float value)
{
    preco = value;
}

float Compras::getTotal() const
{
    return total;
}

void Compras::setTotal(float value)
{
    total = value;
}
