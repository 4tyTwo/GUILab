#ifndef RECORD_H
#define RECORD_H
#include "moment.h"
#include "coffeemachine.h"
class Record : public Moment
{
public:
  Record(); //Конструктор по умолчанию
  Record(QString name,QString surname
      ,QString patronymic,QString degree,QString position,int coffeeDiff=-250);
  //Инициализирующий конструктор, полный
  Record(Record& rec);//Копирующий конструктор
  virtual ~Record();
  QString getFirstName(); //Возвращает имя
  QString getlastname(); //Возвращает фамилию
  QString getPatronymic(); //Возвращает отчество
  QString getDegree(); //Возвращает ученую степень
  QString getPosition();//Возвращает должность
  int getCoffeeDiff();//Возвращает объем слитого/налитого кофе
  void setFirstName(QString str); //Устанавливает имя
  void setLastName(QString str); //Устанавливает фамилию
  void setPatronymic(QString str);//Устанавливает отчество
  void setDegree(QString str);//Устанавливает ученую степень
  void setPosition(QString);//Устанавливает должность
  void setCoffeeDiff(int diff);//Устанавливает объем слитого/налитого кофе
  void copy(Record object);
  virtual int isBase();
private:
  QString firstName,lastName,patronymic,degree,position; //Строки с информацией о сотруднике
  //timeSt accessTime; //Структура со следущими полями:
  //int year - год
  //int month - месяц
  //int day - день
  //int hours - часы
  //int minutes - минуты
  int coffeeDiff;//разница объема и остаток кофе
};
#endif // RECORD_H


