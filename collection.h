#ifndef COLLECTION_H
#define COLLECTION_H
#include "record.h"
#include "checkrecord.h"
class Collection{
public:
  Collection();//Конструктор по умолчанию
  Collection(Collection& list);
  ~Collection();//Деструктор по умолчанию
  void add(Moment* info);//Добавляет в конец
  Moment* get(int index);//Возвращет элемент с индексом index, либо нулевой
  void set(int index,Moment* info);
  void insert(int index,Moment* info);
  void insert(int index,Collection& list);
  int size() { return count; }
  bool isEmpty() { return !(bool)count; }
  void del(int index);
  Moment* operator[](int index); //Без проверки на индекс
  Collection& operator+=(Collection &list);
  void save(QString filename);
  bool load(QString filename);
  CoffeeMachine getMachine() { return machine; }
  void setMachine(CoffeeMachine coffee) {machine = coffee;}
  bool check();
  void clear();
  CoffeeMachine machine;
private:
  Moment* createptr(Moment* info);
  void grow(int num=3);
  int count,allocated;
  Moment **data;
};
#endif // COLLECTION_H
