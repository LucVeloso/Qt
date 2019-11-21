#ifndef TAREFA_H
#define TAREFA_H

#include <QString>


class Tarefa
{

private:


    QString nome;
    int id;

public:
    Tarefa();

    bool check;


    QString getNome() const;
    bool setNome(const QString &value);
    int getId() const;
    void setId(int value);
};

#endif // TAREFA_H
