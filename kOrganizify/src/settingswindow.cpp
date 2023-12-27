#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QDir>

SettingsWindow::SettingsWindow(Settings *settings, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SettingsWindow)
    , m_settings(settings)
//,
    // m_theme(Custom),
    // m_notifications(true),
    // m_nightMode(false)
{
    ui->setupUi(this);
    ui->lblNotificationsOn->setVisible(false);


    connect(ui->dropTheme, QOverload<const QString &>::of(&QComboBox::currentTextChanged), [=](const QString &text){
        QString color = this->textToColor(text);

        QString path = this->colorToPath(color);

        this->setColor(color);
        this->setBackgroundPath(path);

        QString styleSheet = QString("background-color: %1; ").arg(color);
        QString btnStyleSheet = QString("QPushButton{" + styleSheet + "border-radius: 10px; color:black;}");
        this->ui->btnSave->setStyleSheet(btnStyleSheet);
        this->ui->dropTheme->setStyleSheet(QString("QComboBox{color: black; border-radius:10px; background-color: %1; }").arg(color));
    });
}

void SettingsWindow::on_btnSave_clicked(){
    emit colorChanged(this->m_settings->color());
    this->close();
}

void SettingsWindow::changeColor(QString color)
{
    QString styleSheet = QString("background-color: %1; ").arg(color);
    QString btnStyleSheet = QString("QPushButton{" + styleSheet + "border-radius: 10px; color:black;}");
    this->ui->btnSave->setStyleSheet(btnStyleSheet);
    this->ui->dropTheme->setStyleSheet(QString("QComboBox{color: black; border-radius:10px; background-color: %1; }").arg(color));
}

void SettingsWindow::setColor(QString color){
    this->m_settings->setColor(color);
}

void SettingsWindow::setBackgroundPath(QString backgroundPath)
{
    this->m_settings->setBackgroundPath(backgroundPath);
}

QString SettingsWindow::getColor(){
    return this->m_settings->color();
}

QString SettingsWindow::getBackgroundPath()
{
    return this->m_settings->backgroundPath();
}

QString SettingsWindow::textToColor(QString text)
{
    QMap<QString, QString> themeColors {
        {"Blue", "#0050B5"},
        {"Green", "#006E33"},
        {"Orange", "#FE5000"},
        {"Pink", "#D62598"},
        {"Purple", "#9063CD"},
        {"Default", "#A5A9A0"}
    };

    return themeColors.value(text, themeColors["Default"]);
}

QString SettingsWindow::textToPath(QString text)
{
    QString sourceDir = QCoreApplication::applicationDirPath();
    QString pathBlue = QDir(sourceDir).filePath(":/images/images/backgroundBlue.png");
    QString pathGreen = QDir(sourceDir).filePath(":/images/images/backgroundGreen.png");
    QString pathOrange = QDir(sourceDir).filePath(":/images/images/backgroundOrange.png");
    QString pathPink = QDir(sourceDir).filePath(":/images/images/backgroundPink.png");
    QString pathPurple = QDir(sourceDir).filePath(":/images/images/backgroundPurple.png");
    QString pathDefault = QDir(sourceDir).filePath(":/images/images/backgroundDefault.png");

    QMap<QString, QString> themeBackgrounds {
        {"Blue", pathBlue},
        {"Green", pathGreen},
        {"Orange", pathOrange},
        {"Pink", pathPink},
        {"Purple", pathPurple},
        {"Default", pathDefault}
    };

    return themeBackgrounds.value(text, themeBackgrounds["Default"]);
}

QString SettingsWindow::colorToPath(QString color)
{
    QMap<QString, QString> colorNames {
        {"#0050B5", "Blue"},
        {"#006E33", "Green"},
        {"#FE5000", "Orange"},
        {"#D62598", "Pink"},
        {"#9063CD", "Purple"},
        {"#A5A9A0", "Default"}
    };

    return this->textToPath(colorNames.value(color));
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
