#include <QObject>
#include <iostream>

#include <sstream>
#include <fstream>
#include <map>
#include <QStringListModel>
#include <QProcess>
#include <QDebug>
#include<QMediaPlayer>
using namespace std;


class Backendstats : public QObject {
    Q_OBJECT

private:

public:

    Q_INVOKABLE QString getgpuload() {
        QProcess process;
        process.start("cat /sys/kernel/debug/pvr/status");
        process.waitForFinished(-1);
        QString output = process.readAllStandardOutput();

        return output.mid(output.indexOf("GPU Utilisation")+17,output.indexOf("%")-output.indexOf("GPU Utilisation")-17);
    }
    Q_INVOKABLE QString getcpuload(){
        QProcess process;
        process.start("cat /proc/stat");
        process.waitForFinished(-1);
        QString cpuoutput = process.readAllStandardOutput();
        int spc=0;
        int totaltime=0,idletime=0;
        int curr=0,i;
        for(i=0;i<cpuoutput.length();i++)
        {
            QChar c= cpuoutput.at(i);
            if(c==" "||c=='\n')
            {spc++;
             totaltime+=curr;
             if(spc==6||spc==7)
             idletime+=curr;
             curr=0;
            }
            if(c=="\n")
            break;
            if(c.isDigit())
            {
                int d = QString(c).toInt();
                curr*=10;curr+=d;
            }
        }
        double load = (totaltime-idletime)*100;
        load/=totaltime;
        QString res = QString::number(load);
        //qDebug()<<res;
        return res.mid(0,5);
    }


};