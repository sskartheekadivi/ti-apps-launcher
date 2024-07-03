#include <QObject>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <QStringListModel>
#include <QProcess>
#include <QDebug>
#include "include/common.h"
#include "include/appsmenu.h"

extern int include_apps_count;
extern app_info include_apps[];

int apps_menu::button_getcount(){
    return include_apps_count;
}

QString apps_menu::button_getname(int n) {
    return include_apps[n].name;
}

QString apps_menu::button_getqml(int n) {
    return include_apps[n].qml_source;
}

QString apps_menu::button_geticon(int n) {
    return include_apps[n].icon_source;
}

void apps_menu::cache_flush() {
    int returnCode = system("echo \"1\" > /proc/sys/vm/drop_caches");
}
