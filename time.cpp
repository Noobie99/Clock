#include "time.h"
#include <string>
#include <ctime>
#include <glibmm/main.h>

std::string formatString(int x) {
    std::string s = "";
    if (x < 10) return "0" + std::to_string(x);
    return std::to_string(x);
}

std::string getTime() {
    std::time_t time = std::time(0);
    std::tm* now = std::localtime(&time);

    std::string s = "";
    s += formatString(now->tm_hour) + ":";
    s += formatString(now->tm_min) + ":";
    s += formatString(now->tm_sec) + "\n";

    std::string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    s += days[now->tm_wday] + ", ";
    s += months[now->tm_mon] + " ";

    s += std::to_string(now->tm_mday);
    switch (now->tm_mday % 10) {
        case 1:
            if (now->tm_mday != 11) {
                s += "st";
                break;
            }
        case 2:
            if (now->tm_mday != 12) {
                s += "nd";
                break;
            }
        case 3:
            if (now->tm_mday != 13) {
                s += "rd";
                break;
            }
        default:
            s += "th";
    }
    return s;
}

Clock::Clock()
: conn(idk())
{
    add(m_label);
    m_label.show();
    m_label.set_justify(Gtk::JUSTIFY_CENTER);
    add_events(Gdk::KEY_PRESS_MASK);
}

Clock::~Clock()
{
    conn.disconnect();
}

sigc::connection Clock::idk() {
    sigc::slot<bool> my_slot = sigc::mem_fun(*this, &Clock::updateTime);
    return Glib::signal_timeout().connect(my_slot, 100);
}

bool Clock::updateTime() {
    set_opacity(0.7);
    m_label.set_markup("<span font_desc=\"monospace bold 100.0\">" + getTime() + "</span>");
    return true;
}

#include <iostream>
bool Clock::on_key_press_event(GdkEventKey* key_event) {
    if (key_event->keyval == GDK_KEY_l && (key_event->state & GDK_CONTROL_MASK))
        hide();
    return true;
}
