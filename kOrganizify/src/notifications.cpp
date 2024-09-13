#include "notifications.h"

Notifications::Notifications(Calendar* calendar) :
    m_calendar(calendar)
    , QObject(nullptr)
    , m_timer(new QTimer(this))
{
    QDateTime currentDateTime = QDateTime::currentDateTime();

    for (const Event& event : m_calendar->getEvents()) {
        int secs = currentDateTime.secsTo(event.getStartTime());
        if (currentDateTime.date() == event.getStartTime().date() && secs >= 30 * 60) {
            m_filteredEvents.append(event);
        }
    }

    int secondsUntilNextMinute = 60 - currentDateTime.time().second();
    int millisecondsUntilNextMinute = secondsUntilNextMinute * 1000;
    m_timer->start(millisecondsUntilNextMinute);

    connect(m_timer, &QTimer::timeout, this, [this]() {
        checkEvents(m_filteredEvents);
        m_timer->start(60000);
    });
}

void Notifications::checkEvents(const QList<Event>& filteredEvents) {

    QDateTime currentDateTime = QDateTime::currentDateTime();
    for (const Event& event : filteredEvents) {
        int secs = currentDateTime.secsTo(event.getStartTime());
        if (secs >= 29 * 60 && secs <= 30 * 60 && m_enabled)
            showEvent(event);
    }
}

void Notifications::showEvent(const Event& event) {
    NotificationsWindow* notif = new NotificationsWindow(nullptr);
    notif->updateWindow(event.getTitle(), event.getStartTime().toString("yyyy-MM-dd hh:mm:ss"), event.getLocation());
}

void Notifications::enabledNotifications(const bool enabled) {
    m_enabled = enabled;
}

void Notifications::updatedEvents() {
    m_filteredEvents = m_calendar->getEvents();
    checkEvents(m_filteredEvents);
}

Notifications::~Notifications() {
    delete m_timer;
}
