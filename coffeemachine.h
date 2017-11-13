#ifndef COFFEEMACHINE_H
#define COFFEEMACHINE_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>

class CoffeeMachine
{
public:
    CoffeeMachine(int maximum=0,QString name="unknown",int remain=0);//Инициализирующий конструктор
    CoffeeMachine(QString name);//Инициализирующий конструктор, принимает только модель
    void load(QString filename);//Загрузить данные
    void save(QString filename);//Сохранить данные
    bool addcoffee(int diff);//diff - количество выпитого/залитого кофе
    int getMax();//Возвращает максимальный объем
    int getRemain();//Возвращает остаток кофе
    QString getModel();//Возвращает модель кофемашины
    void setModel(QString name);//Устанавливает модель кофемашины
    void setMax(int maximum);//Устанавливает максимальный объем
    void setRemain(int remain);//Устанавливает остаток кофе
    ~CoffeeMachine();//Деструктор
private:
    int max,remain;//максимальный объем и текущий объем
    QString model;//Модель (имя) кофемашины
};
void deln(char *s);
#endif // COFFEEMACHINE_H
