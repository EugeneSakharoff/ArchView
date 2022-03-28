#include "mainwindow.h"
#include "optionswindow.h"

#include <QApplication>
#include <QLocale>
#include <clocale>

//#ifdef Q_OS_WIN
//  #include <qt_windows.h>
//#endif

//--------------------------------------------------------
//int main(int argc, char *argv[])
//{
//    QCoreApplication::setOrganizationName("SKU-Systema");
//    QCoreApplication::setOrganizationDomain("sku-systema.ru");
//    QCoreApplication::setApplicationName("ArchiveViewer");
//    QSettings::setDefaultFormat(QSettings::IniFormat);


//    QApplication a(argc, argv);
//    MainWindow win;
//    win.show();
//    win.afterInit();
//    return a.exec();
//}

int main( int argc, char* argv[] )
{
setlocale( LC_ALL, "Russian" );
setlocale( LC_NUMERIC, "English" );

QLocale::setDefault( QLocale( QLocale::Russian, QLocale::RussianFederation ) );

QApplication app( argc, argv );

QCoreApplication::setOrganizationName( "SKU-Systema" );
QCoreApplication::setOrganizationDomain( "sku-systema.ru" );
QCoreApplication::setApplicationName( "ArchiveViewer" );
QSettings::setDefaultFormat( QSettings::IniFormat );

const char* tr_names[] =
{
  ":translations/qt_ru.qm",
  ":translations/qtbase_ru.qm",
  nullptr
};

for ( int i = 0; tr_names[ i ] != NULL; ++i )
  {
  QTranslator* qt_translator = new QTranslator( &app );
  if ( qt_translator->load( tr_names[ i ] ) )
	{
	app.installTranslator( qt_translator );
	}
  }

MainWindow win;
win.show();

QTimer::singleShot( 0, &win, SLOT( afterInit() ) );
return app.exec();
}
