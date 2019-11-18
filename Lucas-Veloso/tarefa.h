#ifndef TAREFA_H
#define TAREFA_H

#include <QString>


class Tarefa
{

private:

    QString nome;

public:
    Tarefa();

    QString getNome() const;
    bool setNome(const QString &value);
};

#endif // TAREFA_H
