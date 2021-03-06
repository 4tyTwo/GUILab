#include "checkrecord.h"

CheckRecord::CheckRecord(){
  remaining = 0;
}

CheckRecord::CheckRecord(int remain,timeSt time){
  setRemaining(remain);
  setTime(time);
}

CheckRecord::CheckRecord(int remain,int minutes,int hours,int day,int month,int year){
  setRemaining(remain);
  setTime(minutes,hours,day,month,year);
}

CheckRecord::CheckRecord(CheckRecord& object){
  accessTime = object.getTime();
  remaining = object.getRemaining();
}

CheckRecord::~CheckRecord(){

}

int CheckRecord::isBase(){
  return -1;
}

void CheckRecord::setRemaining(int remain){
  remaining = (remain<0)? 0:remain;
}

QString CheckRecord::getText(){
  timeSt curr = accessTime;
  return QString("Remains: "
  +QString::number(remaining)+"ml Time: "+QString::number(curr.hours)
  +":"+QString::number(curr.minutes)+" Date: "+QString::number(curr.day)
  +"/"+QString::number(curr.month)+"/"+QString::number(curr.year));
}
