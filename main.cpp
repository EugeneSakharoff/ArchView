#include "mainwindow.h"
#include <QApplication>
#include "optionswindow.h"



int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("SKU-Systema");
    QCoreApplication::setOrganizationDomain("sku-systema.ru");
    QCoreApplication::setApplicationName("ArchiveViewer");
    QSettings::setDefaultFormat(QSettings::IniFormat);


    QApplication a(argc, argv);
    MainWindow win;
    win.show();
    win.afterInit();
    return a.exec();
}
