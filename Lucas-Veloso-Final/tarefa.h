#ifndef TAREFA_H
#define TAREFA_H

#include <QString>


class Tarefa
{

private:

    QString nome;
    int id;
    bool check;

public:
    Tarefa();

    QString getNome() const;
    bool setNome(const QString &value);
    int getId() const;
    void setId(int value);
    bool getCheck() const;
    void setCheck(bool value);
};

#endif // TAREFA_H
