#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPalette>
#include <QMap>

#include "settings.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
    void setColor(QString color);
    QString getColor();

private slots:
    void on_btnSave_clicked();

signals:
    void colorChanged(const QString& color);

private:
    Ui::SettingsWindow *ui;
    Settings *settings;
};

#endif // SETTINGSWINDOW_H
