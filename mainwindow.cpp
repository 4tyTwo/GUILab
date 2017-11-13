#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setList(Collection array){
  list=array;
}

void MainWindow::initializeLog(){
  fillLog();
  ui->SaveChanges->hide();
  ui->diffEdit->setValidator( new QIntValidator(-INT_MAX, INT_MAX, this));
  ui->maxEdit->setValidator( new QIntValidator(-INT_MAX, INT_MAX, this));
  ui->remEdit->setValidator( new QIntValidator(-INT_MAX, INT_MAX, this));
  ui->diffEditCheck->setValidator( new QIntValidator(-INT_MAX, INT_MAX, this));
  currentItem=-1;
  ui->checkBoxCheckRecord->hide();
  ui->checkBoxRecord->hide();
  ui->CreateGroup->hide();
}
void MainWindow::fillLog(){
  ui->coffeelog->clear();
  QString text;
  for (int i =0;i<list.size();i++){
    timeSt curr = list[i]->getTime();
    if (list[i]->isBase()==0){
      Record* tmp = dynamic_cast<Record*>(list[i]);
      text="["+QString::number(i)+"] "+tmp->getFirstName()+" "+tmp->getlastname()
      +" "+tmp->getPatronymic()+" "+tmp->getDegree()+" "+tmp->getPosition()
      +" "+QString::number(tmp->getCoffeeDiff())+"ml Time: "
      +QString::number(curr.hours)+":"+QString::number(curr.minutes)+" Date: "+
      QString::number(curr.day)+"/"+QString::number(curr.month)+"/"
      +QString::number(curr.year);
    }
    else{
      CheckRecord* tmp = dynamic_cast<CheckRecord*>(list[i]);
      text="["+QString::number(i)+"] Remains: "
      +QString::number(tmp->getRemaining())+"ml Time: "+QString::number(curr.hours)
      +":"+QString::number(curr.minutes)+" Date: "+QString::number(curr.day)
      +"/"+QString::number(curr.month)+"/"+QString::number(curr.year);
      }
    ui->coffeelog->addItem(text);
  }
}

void MainWindow::on_coffeelog_itemClicked(QListWidgetItem *item)
{
  int index=QString(item->text()[item->text().indexOf('[')+1]).toInt();
  emptyRecordEdits();
  if (index!=currentItem)
    if (list[index]->isBase()==0){
      Record* tmp = dynamic_cast<Record*>(list[index]);
      ui->nameEdit->setText(tmp->getFirstName());
      ui->lnameEdit->setText(tmp->getlastname());
      ui->patronEdit->setText(tmp->getPatronymic());
      ui->degreeEdit->setText(tmp->getDegree());
      ui->positionEdit->setText(tmp->getPosition());
      ui->diffEdit->setText(QString::number(tmp->getCoffeeDiff()));
      ui->DateAndTime->setDate(QDate(tmp->getTime().year,tmp->getTime().month,
      tmp->getTime().day));
      ui->DateAndTime->setTime(QTime(tmp->getTime().hours,tmp->getTime().minutes));
      setEnabledRecordEdits(false);
    }
   else{
      CheckRecord* tmp = dynamic_cast<CheckRecord*>(list[index]);
      ui->diffEditCheck->setText(QString::number(tmp->getRemaining()));
      ui->DateAndTimeCheck->setDate(QDate(tmp->getTime().year,tmp->getTime().month,
      tmp->getTime().day));
      ui->DateAndTimeCheck->setTime(QTime(tmp->getTime().hours,tmp->getTime().minutes));
      ui->diffEditCheck->setEnabled(false);
      ui->DateAndTimeCheck->setEnabled(false);
    }
    currentItem = index;
    ui->SaveChanges->hide();
    ui->checkBoxRecord->hide();
    ui->checkBoxCheckRecord->hide();
  }

  void MainWindow::on_ChangeRecord_clicked()
  {
      if (ui->nameEdit->text().length()==0 && ui->diffEditCheck->text().length()==0)
        return;
      if (list[currentItem]->isBase()==0){
        setEnabledRecordEdits(true);
      }
      else{
        ui->DateAndTimeCheck->setEnabled(true);
        ui->diffEditCheck->setEnabled(true);
        setEnabledRecordEdits(false);
      }
  ui->SaveChanges->show();
}

void MainWindow::on_SaveChanges_clicked()
{
  if (list[currentItem]->isBase()==0){
    Record* tmp = dynamic_cast<Record*>(list[currentItem]);
    tmp->setFirstName(ui->nameEdit->text());
    tmp->setLastName(ui->lnameEdit->text());
    tmp->setPatronymic(ui->patronEdit->text());
    tmp->setPosition(ui->positionEdit->text());
    tmp->setDegree(ui->degreeEdit->text());
    tmp->setCoffeeDiff(ui->diffEdit->text().toInt());
    ui->SaveChanges->hide();
    tmp->setTime(ui->DateAndTime->time().minute(),ui->DateAndTime->time().hour()
    ,ui->DateAndTime->date().day(),ui->DateAndTime->date().month(),
    ui->DateAndTime->date().year());
    setEnabledRecordEdits(false);
    ui->SaveChanges->hide();
  }
  else{
    CheckRecord* tmp = dynamic_cast<CheckRecord*>(list[currentItem]);
    tmp->setRemaining(ui->diffEditCheck->text().toInt());
    tmp->setTime(ui->DateAndTimeCheck->time().minute(),ui->DateAndTimeCheck->time().hour()
    ,ui->DateAndTimeCheck->date().day(),ui->DateAndTimeCheck->date().month(),
    ui->DateAndTimeCheck->date().year());
    ui->diffEditCheck->setEnabled(false);
    ui->DateAndTimeCheck->setEnabled(false);
  }
 fillLog();
}

void MainWindow::setEnabledRecordEdits(bool enabled){
  ui->nameEdit->setEnabled(enabled);
  ui->lnameEdit->setEnabled(enabled);
  ui->patronEdit->setEnabled(enabled);
  ui->degreeEdit->setEnabled(enabled);
  ui->positionEdit->setEnabled(enabled);
  ui->diffEdit->setEnabled(enabled);
  ui->DateAndTime->setEnabled(enabled);
}

void MainWindow::setEnabledCheckEdits(bool enabled){
  ui->diffEditCheck->setEnabled(enabled);
  ui->DateAndTimeCheck->setEnabled(enabled);
}

void MainWindow::on_checkBoxRecord_stateChanged(int arg1)
{
    setEnabledCheckEdits(!bool(arg1));
    setEnabledRecordEdits(bool(arg1));
    ui->checkBoxCheckRecord->setChecked(!bool(arg1));
}

void MainWindow::on_checkBoxCheckRecord_stateChanged(int arg1)
{
  setEnabledCheckEdits(bool(arg1));
  setEnabledRecordEdits(!bool(arg1));
  ui->checkBoxRecord->setChecked(!bool(arg1));
}

void MainWindow::on_NewRecord_clicked()
{
    ui->checkBoxRecord->show();
    ui->SaveChanges->hide();
    ui->checkBoxRecord->setChecked(true);
    ui->checkBoxCheckRecord->show();
    ui->CreateGroup->show();
}

void MainWindow::emptyRecordEdits(){
  ui->nameEdit->setText("");
  ui->lnameEdit->setText("");
  ui->patronEdit->setText("");
  ui->positionEdit->setText("");
  ui->degreeEdit->setText("");
  ui->diffEdit->setText("");
  ui->diffEditCheck->setText("");
  ui->DateAndTime->setTime(QTime());
  ui->DateAndTime->setDate(QDate());
}

void MainWindow::on_CreateButton_clicked()
{
  int index = ui->spinBoxIndex->value();
    if (ui->checkBoxRecord->isChecked()){
      Record tmp;
      tmp.setFirstName(ui->nameEdit->text());
      tmp.setLastName(ui->lnameEdit->text());
      tmp.setPatronymic(ui->patronEdit->text());
      tmp.setPosition(ui->positionEdit->text());
      tmp.setDegree(ui->degreeEdit->text());
      tmp.setCoffeeDiff(ui->diffEdit->text().toInt());
      tmp.setTime(ui->DateAndTime->time().minute(),ui->DateAndTime->time().hour()
      ,ui->DateAndTime->date().day(),ui->DateAndTime->date().month(),
      ui->DateAndTime->date().year());
      Moment* base = new Record;
      base = &tmp;
      if (index<list.size() && index>=0)
        list.insert(index,base);
      else
        list.add(base);
      fillLog();
      setEnabledRecordEdits(false);
      }
    else{
      CheckRecord tmp;
      tmp.setRemaining(ui->diffEditCheck->text().toInt());
      tmp.setTime(ui->DateAndTimeCheck->time().minute(),ui->DateAndTimeCheck->time().hour()
      ,ui->DateAndTimeCheck->date().day(),ui->DateAndTimeCheck->date().month(),
      ui->DateAndTimeCheck->date().year());
      Moment* base = new CheckRecord;
      base = &tmp;
      if (index<list.size() && index>=0)
        list.insert(index,base);
      else
        list.add(base);
      fillLog();
      setEnabledCheckEdits(false);
    }
 emptyRecordEdits();
 ui->CreateGroup->hide();
 ui->checkBoxCheckRecord->hide();
 ui->checkBoxRecord->hide();
}

void MainWindow::on_deleteButton_clicked()
{
    if (currentItem >=0 && currentItem < list.size()){
      list.del(currentItem);
      currentItem = -1;
      fillLog();
    setEnabledCheckEdits(false);
    setEnabledRecordEdits(false);
    emptyRecordEdits();
    ui->SaveChanges->hide();
    }
}

void MainWindow::on_SaveInFileButton_clicked()
{
    list.save(ui->saveEdit->text());
}

void MainWindow::on_LoadFromFileButton_clicked()
{
    list.load(ui->loadEdit->text());
    fillLog();
}

void MainWindow::on_verifyButton_clicked()
{
  list.machine.setMax(ui->maxEdit->text().toInt());
  list.machine.setRemain(ui->remEdit->text().toInt());
    if (list.check())
      ui->verification->setText("Last time checked, log was OK");
    else
      ui->verification->setText("There is an error in the log");
}
