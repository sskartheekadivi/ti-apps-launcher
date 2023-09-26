/* Configuration file for AM68 SK*/

#include <iostream>
#include "backend/includes/common.h"
#include "backend/includes/live_camera.h"
#include "backend/includes/run_cmd.h"
#include "backend/includes/settings.h"
#include "backend/includes/gpu_performance.h"
#include "backend/includes/benchmarks.h"

#define PLATFORM "am68-sk"
using namespace std;
int include_apps_count = 7;
QString platform = "am68-sk";

app_info include_apps[] = {
    {
        .qml_source = "industrial_control.qml",
        .name = "Industrial HMI",
        .icon_source = "qrc:/images/hmi.png"
    },
    {
        .qml_source = "live_camera.qml",
        .name = "Live Camera",
        .icon_source = "qrc:/images/camera.png"
    },
    {
        .qml_source = "benchmarks_jacinto.qml",
        .name = "Benchmarks",
        .icon_source = "qrc:/images/benchmarks.png"
    },
    {
        .qml_source = "gpu_performance.qml",
        .name = "GPU Performance",
        .icon_source = "qrc:/images/gpu_performance.png"
    },
    {
        .qml_source = "seva_store.qml",
        .name = "Seva Store",
        .icon_source = "qrc:/images/seva_store.png"
    },
    {
        .qml_source = "firefox_browser.qml",
        .name = "Firefox",
        .icon_source = "qrc:/images/firefox.png"
    },
    {
        .qml_source = "settings.qml",
        .name = "Settings",
        .icon_source = "qrc:/images/settings.png"
    }
};

Settings settings;
LiveCamera live_camera;
Benchmarks benchmarks;
Gpu_performance gpuperformance;

QString seva_command = QString::fromStdString("seva-launcher-aarch64");
RunCmd *seva_store = new RunCmd(seva_command);
RunCmd *firefox_browser = new RunCmd(QStringLiteral("docker run -v /run/user/1000/:/tmp/ -i --env http_proxy --env https_proxy --env no_proxy --env XDG_RUNTIME_DIR=/tmp/ --env WAYLAND_DISPLAY=wayland-1 -u user ghcr.io/texasinstruments/seva-browser:v1.0.0 https://www.ti.com/microcontrollers-mcus-processors/arm-based-processors/overview.html"));
RunCmd *sdk_datasheet = new RunCmd(QStringLiteral("docker run -v /run/user/1000/:/tmp/ -i --env http_proxy --env https_proxy --env no_proxy --env XDG_RUNTIME_DIR=/tmp/ --env WAYLAND_DISPLAY=wayland-1 -u user ghcr.io/texasinstruments/seva-browser:v1.0.0 https://software-dl.ti.com/jacinto7/esd/processor-sdk-linux-am68/latest/exports/docs/devices/J7_Family/linux/Release_Specific_Performance_Guide.html"));

void platform_setup(QQmlApplicationEngine *engine) {
    std::cout << "Running Platform Setup of AM68x!" << endl;
    engine->rootContext()->setContextProperty("live_camera", &live_camera);
    engine->rootContext()->setContextProperty("seva_store", seva_store);
    engine->rootContext()->setContextProperty("firefox_browser", firefox_browser);
    engine->rootContext()->setContextProperty("sdk_datasheet", sdk_datasheet);
    engine->rootContext()->setContextProperty("settings", &settings);
    engine->rootContext()->setContextProperty("benchmarks", &benchmarks);
    engine->rootContext()->setContextProperty("gpuperformance", &gpuperformance);

    docker_load_images();
}

