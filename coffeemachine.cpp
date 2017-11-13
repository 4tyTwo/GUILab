#include "coffeemachine.h"

CoffeeMachine::CoffeeMachine(int max,QString name,int current_state){//Конструктор, создающий кофемашину с объемом max и остатком current_state
    this->max = (max>0)?  max: 0;
    if (current_state > max)
      current_state = max;
    remain = current_state;
    model = name;
}

bool CoffeeMachine::addcoffee(int diff){//diff - количество выпитого/залитого кофе
   if (!(remain + diff > max || remain + diff < 0)){
       remain+=diff;
       return true;
   }
   else
       return false;
}
CoffeeMachine::CoffeeMachine(QString name){//Конструктор по названию
    max=0;
    remain=0;
    model=name;
}

CoffeeMachine::~CoffeeMachine(){
}

void CoffeeMachine::load(QString filename){//Загрузить данные
  QFile file(filename);
  if (file.exists()){
      file.open(QIODevice::ReadOnly | QFile::Text);
      QTextStream in(&file);
      max=in.readLine().toInt();
      remain=in.readLine().toInt();
      model=in.readLine();
  }
}

void CoffeeMachine::save(QString filename){
  QFile file(filename);
  file.open(QIODevice::WriteOnly | QFile::Text);
  QTextStream out(&file);
  out<<max<<'\n'<<remain<<'\n'<<model;
  file.close();
}

int CoffeeMachine::getMax(){
    return max;
}

int CoffeeMachine::getRemain(){
    return remain;
}

QString CoffeeMachine::getModel(){
    return model;
}

void CoffeeMachine::setModel(QString name){
    if (name.length()>0)
      model=name;
    else
      model="Unknown";
}

void CoffeeMachine::setMax(int maximum){
    if (maximum > 0){
        if (maximum < remain)
            setRemain(maximum);
        max=maximum;}
    else
        max=0;
}

void CoffeeMachine::setRemain(int remaining){
    if (remaining >= 0)
      if (remaining > max)
          remain = max;
      else
          remain = remaining;
    else
      remain = 0;
}
