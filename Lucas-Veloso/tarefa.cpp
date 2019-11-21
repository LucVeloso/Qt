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

Tarefa::Tarefa()
{
    check = false;
}
