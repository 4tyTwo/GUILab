#ifndef CHECKRECORD_H
#define CHECKRECORD_H
#include "moment.h"
class CheckRecord : public Moment
{
public:
  CheckRecord();
  CheckRecord(int remain,timeSt time);
  CheckRecord(int remain,int minutes,int hours,int day,int month,int year);
  CheckRecord(CheckRecord& object);
  inline int getRemaining() { return remaining; }
  void setRemaining(int remain);
  virtual int isBase();
  virtual ~CheckRecord();
private:
  int remaining;
};

#endif // CHECKRECORD_H
