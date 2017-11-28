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
	QWidget* m_xmlWidget;
	QWidget* m_zipWidget;
	QTreeView* m_zipTreeView;

	QFileSystemModel* m_fileSystemModel;
	QStyle* m_qStyle;
	QString m_strFileName;
	QString m_strFullFileName;
	QString m_strFilePath;
};

#endif // MAINWINDOW_H
