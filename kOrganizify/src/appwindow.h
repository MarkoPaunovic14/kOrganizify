// appwindow.h
#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QCheckBox>
#include <QDir>

#include "mainwindow.h"
#include "settingswindow.h"

#include "user.h"
#include "toDoList.h"


namespace Ui {
class AppWindow;
}

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppWindow(User *user, QWidget *parent = nullptr);
    ~AppWindow();

private slots:
    // void addTask();
    // void addEvent();
    // void changeButtonColor(const QString &newColor);
    // void onCheckBoxStateChanged(int state);
    void logoutUser();

private:
    Ui::AppWindow *ui;
    User *m_user;

// private:
//     Ui::AppWindow *ui;
//     SettingsWindow *settingsWindow;
//     ToDoList m_toDoList;
//     User *m_user;
};

#endif // APPWINDOW_H
