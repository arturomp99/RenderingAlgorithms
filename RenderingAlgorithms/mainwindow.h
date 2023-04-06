#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "scenephong.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void show();

    void on_actionLoad_triggered(); // It opens a file dialog to load a ply mesh
private:
    void changeScene(Scene* sc);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
