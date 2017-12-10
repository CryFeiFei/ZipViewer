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
#include <QMessageBox>

#include "JlCompress.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void showXml(const QModelIndex&);
	void openFile();
	void closeApp();

private:
	void initZipWidget();
	void initXMLWidget();
	void initMainWin();
	void initTool();
	void initAterOpen();

private:
	bool _deleteDir(const QString &dirName);

private:
	QWidget* m_xmlWidget;
	QTextEdit* m_xmlTextEdit;

	QWidget* m_zipWidget;
	QTreeView* m_zipTreeView;

	QFileSystemModel* m_fileSystemModel;
	QStyle* m_qStyle;

	QString m_strFullFileName;  //文件路径+名字
	QString m_strFilePath;   //文件路径
	QString m_strFileName;   //带后缀的名字
	QString m_strName;   //不带后缀的名字

	QString m_strNewFolder;

	QDir m_Dir;
	QFile* m_file;
};

#endif // MAINWINDOW_H
