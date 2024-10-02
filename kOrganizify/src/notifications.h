// notifications.h
#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QDateTime>
#include <QList>
#include <QMessageBox>
#include <QObject>
#include <QTimer>

#include "calendar.h"
#include "notificationswindow.h"

class Notifications : public QObject {
  Q_OBJECT
public:
  Notifications(Calendar *calendar);
  ~Notifications();
  void checkEvents(const QList<Event> &filteredEvents);

public slots:
  void enabledNotifications(const bool enabled);
  void updatedEvents();

private slots:
  static void showEvent(const Event &event);

private:
  Calendar *m_calendar;
  QTimer *m_timer;
  bool m_enabled;
  QList<Event> m_filteredEvents;
};

#endif // NOTIFICATIONS_H
