#include "mainwindow.h"
#include <QApplication>
#include "JlCompress.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    JlCompress::extractDir("D:\\QTProject\\OFDReader\\ofd_file\\123.zip", "D:\\QTProject\\OFDReader\\ofd_file\\");

    return a.exec();
}
