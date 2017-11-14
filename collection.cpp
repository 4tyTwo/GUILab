#include "collection.h"
Collection::Collection(){
  count = allocated = 0;
  data = NULL;
}

Collection::Collection(Collection& list){
  count = allocated = 0;
  data = NULL;
  grow(list.size());
  for (int i=0;i<list.size();i++){
    add(list[i]);
  }
  machine = list.machine;
}

Collection::~Collection(){

}

Moment* Collection::createptr(Moment* info){
  Moment* baseptr;
  if (info->isBase()==0)
    baseptr = new Record(*dynamic_cast<Record*>(info));
  else
    baseptr = new CheckRecord(*dynamic_cast<CheckRecord*>(info));
  return baseptr;
}

void Collection::grow(int num){
  if (num<0)
    num = 1;
  Moment **tmp = new Moment*[count+num];
  for (int i=0;i<count;i++){
    tmp[i] = data[i];
  }
  data = tmp;
  allocated+=num;
}

void Collection::add(Moment* info){
  if (count>=allocated)
    grow();
  data[count++] = createptr(info);
}

Moment* Collection::get(int index){
  index = (index < 0 || index > count-1) ? 0 : index;
  return data[index];
}

void Collection::set(int index,Moment* info){
  if (index < 0 || index > count-1)
    return;
  delete data[index];
  data[index] = createptr(info);
}

void Collection::insert(int index,Moment* info){
  if (index < 0 || index > count-1){
    add(info);
    return;
  }
  if (count>=allocated)
    grow();
  for(int i=count;i>index;i--){
    data[i]= createptr(data[i-1]);
    delete data[i-1];
  }
  data[index]=createptr(info);
  ++count;
}

void Collection::del(int index){
  if (index < 0 || index > count-1)
    return;
  for (int i=index;i<count-1;i++){
    delete data[i];
    data[i] = createptr(data[i+1]);
  }
  delete data[count-1];
  --count;
}

Moment* Collection::operator[] (int index){
  return data[index];
}

Collection& Collection::operator+=(Collection &list){
  if (count+list.size() > allocated)
    grow(count+list.size() - allocated);
  for (int i=0;i<list.size();i++)
    add(list[i]);
  return *this;
}

void Collection::insert(int index, Collection &list){
  if (index<0 || index>=size())
    *this+=list;
  else{
    if (allocated<count+list.size())
      grow(count+list.size() - allocated);
    for(int i=count+list.size()-1;i>index+list.size()-1;i--){
      data[i] = createptr(data[i-list.size()]);
        delete data[i-list.size()];
    }
    for (int i=0;i<list.size();i++)
      data[index+i] = createptr(list[i]);
    count+=list.size();
  }
}

void Collection::save(QString filename){
  QFile file(filename);
  file.open(QIODevice::WriteOnly | QFile::Text);
  QTextStream out(&file);
  timeSt curr;
  for (int i=0; i<count; i++){
    curr = data[i]->getTime();
    if (data[i]->isBase()==0){
      Record* tmp = dynamic_cast<Record*>(data[i]);
      out<<tmp->getFirstName()<<"~"<<tmp->getlastname()<<"~"
      <<tmp->getPatronymic()<<"~"<<tmp->getDegree()<<"~"<<tmp->getPosition()
      <<"~"<<tmp->getCoffeeDiff()<<"~"<<curr.minutes<<"~"<<curr.hours<<"~"<<
      curr.day<<"~"<<curr.month<<"~"<<curr.year<<"\n";
    }
    else{
      CheckRecord* tmp = dynamic_cast<CheckRecord*>(data[i]);
      out<<tmp->getRemaining()<<"~"<<curr.minutes<<"~"<<curr.hours<<"~"<<
      curr.day<<"~"<<curr.month<<"~"<<curr.year<<"\n";
      }
    }
  file.close();
}

bool Collection::load(QString filename){
  QFile file(filename);
  if (file.exists()){
    clear();
    file.open(QIODevice::ReadOnly | QFile::Text);
    QTextStream in(&file);
    QString str;
    while (!in.atEnd()){
      str = in.readLine();
      if (str.count("~")==10){
        //Moment* baseptr = new Record;
        Record* tmp = new Record;
        QStringList list = str.split("~");
        tmp->setFirstName(list.at(0));
        tmp->setLastName(list.at(1));
        tmp->setPatronymic(list.at(2));
        tmp->setDegree(list.at(3));
        tmp->setPosition(list.at(4));
        tmp->setCoffeeDiff(list.at(5).toInt());
        tmp->setTime(list.at(6).toInt(),list.at(7).toInt(),list.at(8).toInt(),
        list.at(9).toInt(),list.at(10).toInt());
        add(dynamic_cast<Moment*>(tmp));
        delete tmp;
      }
      if (str.count("~")==5){
        CheckRecord* tmp = new CheckRecord;
        QStringList list = str.split("~");
        tmp->setRemaining(list.at(0).toInt());
        tmp->setTime(list.at(1).toInt(),list.at(2).toInt(),list.at(3).toInt(),
        list.at(4).toInt(),list.at(5).toInt());
        add(dynamic_cast<Moment*>(tmp));
        delete tmp;
      }
    }
    return true;
  }
  else
  return false;
}

bool Collection::check(){
  int max, curr; max = machine.getMax(); curr = machine.getRemain();
  for (int i=0;i<count;i++){
    if (data[i]->isBase()==0){
      Record* tmp = dynamic_cast<Record*>(data[i]);
      curr+=tmp->getCoffeeDiff();
      if (curr>max || curr<0)
        return false;
    }
    else{
      CheckRecord* tmp = dynamic_cast<CheckRecord*>(data[i]);
      if (curr!=tmp->getRemaining())
        return false;
    }
  }
  return true;
}

void Collection::clear(){
  for (int i = count;i>=0;i--)
    del(i);
}
