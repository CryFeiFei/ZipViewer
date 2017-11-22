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
#include <QSplitter>
#include <QSplitterHandle>
#include <QToolBar>
#include <QStyle>
#include <QIcon>
#include <QApplication>
#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QDesktopServices>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void getTreeViewSelectedFileName(QModelIndex);
	void openFile();
	void closeApp();

private:
	void initZipWidget();
	void initXMLWidget();
	void initMainWin();
	void initTool();

private:
	QWidget* m_zipWidget;
	QWidget* m_xmlWidget;
	QFileSystemModel* m_fileSystemModel;
	QStyle* m_qStyle;
	QString m_strFileName;
};

#endif // MAINWINDOW_H
