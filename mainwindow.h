#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "collection.h"
#include <QMainWindow>
#include <QListWidgetItem>
#include <climits>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void initializeLog();
  void setList(Collection array);
  void fillLog();
private slots:
  void on_coffeelog_itemClicked(QListWidgetItem *item);

  void on_ChangeRecord_clicked();

  void on_SaveChanges_clicked();

  void on_checkBoxRecord_stateChanged(int arg1);

  void on_checkBoxCheckRecord_stateChanged(int arg1);

  void on_NewRecord_clicked();

  void on_CreateButton_clicked();

  void on_deleteButton_clicked();

  void on_SaveInFileButton_clicked();

  void on_LoadFromFileButton_clicked();

  void on_verifyButton_clicked();

private:
  void emptyRecordEdits();
  void setEnabledRecordEdits(bool enabled);
  void setEnabledCheckEdits(bool endbled);
  Ui::MainWindow *ui;
  Collection list;
  int currentItem;
};

#endif // MAINWINDOW_H
