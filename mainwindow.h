#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QSplitter>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void getTreeViewSelectedFileName(QModelIndex);

private:
    void initZipWidget();
    void initXMLWidget();
    void initMainWin();

private:
    QWidget* m_zipWidget;
    QWidget* m_xmlWidget;
    QFileSystemModel* m_fileSystemModel;
};

#endif // MAINWINDOW_H
