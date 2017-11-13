#ifndef MOMENT_H
#define MOMENT_H

struct timeSt{ //Структура для описания времени
  int minutes,hours,day,month,year;
};
class Moment
{
public:
  Moment();
  Moment(timeSt time);
  Moment(int minutes,int hours,int day,int month,int year);//Инициализирующий конструктор
  void setTime(int min,int hour,int day,int month,int year);//Устанавливает время и дату записи
  void setTime(timeSt time);//Устанавливает дату и время при помощи структуры
  timeSt getTime(); //Возращает структуру с датой и временем записи
  virtual int isBase();
  virtual ~Moment()=0 {}
protected:
  timeSt accessTime;
};
#endif // MOMENT_H
