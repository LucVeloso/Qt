#include "tarefa.h"
#define MINLETRAS 3
QString Tarefa::getNome() const
{
    return nome;
}

bool Tarefa::setNome(const QString &value)
{
    if(value.size() >= MINLETRAS){

        nome = value;
        return false;
    }
    else return true;
}

int Tarefa::getId() const
{
    return id;
}

void Tarefa::setId(int value)
{
    id = value;
}

bool Tarefa::getCheck() const
{
    return check;
}

void Tarefa::setCheck(bool value)
{
    check = value;
}

Tarefa::Tarefa()
{
    check = false;
    id = 0;
}
