#include "record.h"
#include <ctime>

Record::Record(Record& object) {
 firstName = object.getFirstName();
 lastName = object.getlastname();
 patronymic = object.getPatronymic();
 degree = object.getDegree();
 position = object.getPosition();
 coffeeDiff = object.getCoffeeDiff();
 accessTime = object.accessTime;
}

Record::Record(){
  firstName = lastName = degree = patronymic = position = "not set";
  coffeeDiff = 0;
}

Record::Record(QString name, QString surname, QString patronymic, QString degree, QString position, int coffeeDiff){
  if (!name.length())
    firstName = "Unknown";
  else
    firstName = name;
  if (!surname.length())
    lastName = "Unknown";
  else
    lastName = surname;
  this->patronymic = patronymic;
  if (!degree.length())
    this->degree = "Unknown";
  else
    this->degree = degree;
  if (!position.length())
    this->position = "Unknown";
  else
    this->position = position;
  this->coffeeDiff=coffeeDiff;
  time_t seconds = time(NULL);
  tm *timeinfo = new tm;
  timeinfo = localtime(&seconds);
  accessTime.year= timeinfo->tm_year + 1900;
  accessTime.month = timeinfo->tm_mon + 1;
  accessTime.day = timeinfo->tm_mday;
  accessTime.hours = timeinfo->tm_hour;
  accessTime.minutes = timeinfo->tm_min;
  delete timeinfo;
}
Record::~Record(){
}

QString Record::getFirstName(){
  return firstName;
}
QString Record::getlastname(){
  return lastName;
}
QString Record::getPatronymic(){
  return patronymic;
}
QString Record::getDegree(){
  return degree;
}
QString Record::getPosition(){
  return position;
}
int Record::getCoffeeDiff(){
  return coffeeDiff;
}
void Record::setFirstName(QString str){
 if (!str.length())
   firstName = "Unknown";
 else
   firstName = str;
}
void Record::setLastName(QString str){
  if (!str.length())
    lastName = "Unknown";
  else
    lastName = str;
}
void Record::setPatronymic(QString str){
    patronymic = str;
}
void Record::setDegree(QString str){
    if (!str.length())
      degree = "Unknown";
    else
      degree = str;
}
void Record::setPosition(QString str){
  if (!str.length())
    position = "Unknown";
  else
    position = str;
}
void Record::setCoffeeDiff(int diff){
    coffeeDiff = diff;
}

void Record::copy(Record object){
    firstName = object.getFirstName();
    lastName = object.getlastname();
    patronymic = object.getPatronymic();
    degree = object.getDegree();
    position = object.getPosition();
    coffeeDiff = object.getCoffeeDiff();
    accessTime = object.accessTime;
}

QString Record::getText(){
  timeSt curr = accessTime;
  return QString(firstName+" "+lastName
  +" "+patronymic+" "+degree+" "+position
  +" "+QString::number(coffeeDiff)+"ml Time: "
  +QString::number(curr.hours)+":"+QString::number(curr.minutes)+" Date: "+
  QString::number(curr.day)+"/"+QString::number(curr.month)+"/"
  +QString::number(curr.year));
}

int Record::isBase(){
  return 0;
}
