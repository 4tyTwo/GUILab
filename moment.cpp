#include "moment.h"

Moment::Moment()
{
  accessTime.year=1970;
  accessTime.month=1;
  accessTime.day = 1;
  accessTime.hours = 0;
  accessTime.minutes = 0;
}

int Moment::isBase(){
 return 1; //1 если база, 0 если Record, -1 если CheckRecord
}


Moment::Moment(timeSt time){
  accessTime.year=time.year;
  if (time.month<=12 && time.month > 0)
    accessTime.month = time.month;
  else
    accessTime.month = 01;
  if (time.day<=31 && time.day > 0)
    accessTime.day = time.day;
  else
    accessTime.day = 01;//Забьем на високосный/невисокосный год и кол-во дней в месяце
  if (time.hours<=23 && time.hours >=0)
    accessTime.hours = time.hours;
  else
    accessTime.hours = 23;
  if (time.minutes<=59 && time.minutes >=0)
    accessTime.minutes = time.minutes;
  else
    accessTime.minutes = 0;
}

Moment::Moment(int min,int hour,int day,int month,int year){
  accessTime.year=year;
  if (month<=12 && month>0)
    accessTime.month = month;
  else
    accessTime.month = 01;
  if (day<=31 && day>0)
    accessTime.day = day;
  else
    accessTime.day = 01;//Забьем на високосный/невисокосный год и кол-во дней в месяце
  if (hour<=23 && hour >= 0)
    accessTime.hours = hour;
  else
    accessTime.hours = 0;
  if (min<=59 && min >= 0)
    accessTime.minutes = min;
  else
    accessTime.minutes = 0;
}

timeSt Moment::getTime(){
    return accessTime;
}

void Moment::setTime(int min,int hour,int day,int month,int year){
  accessTime.year=year;
  if (month<=12 && month>0)
    accessTime.month = month;
  else
    accessTime.month = 01;
  if (day<=31 && day>0)
    accessTime.day = day;
  else
    accessTime.day = 01;//Забьем на високосный/невисокосный год и кол-во дней в месяце
  if (hour<=23 && hour >= 0)
    accessTime.hours = hour;
  else
    accessTime.hours = 0;
  if (min<=59 && min >= 0)
    accessTime.minutes = min;
  else
    accessTime.minutes = 0;
}

void Moment::setTime(timeSt time){
    accessTime.year=time.year;
    if (time.month<=12 && time.month > 0)
      accessTime.month = time.month;
    else
      accessTime.month = 01;
    if (time.day<=31 && time.day > 0)
      accessTime.day = time.day;
    else
      accessTime.day = 01;//Забьем на високосный/невисокосный год и кол-во дней в месяце
    if (time.hours<=23 && time.hours >=0)
      accessTime.hours = time.hours;
    else
      accessTime.hours = 23;
    if (time.minutes<=59 && time.minutes >=0)
      accessTime.minutes = time.minutes;
    else
      accessTime.minutes = 0;
}
