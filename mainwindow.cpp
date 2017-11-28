#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	m_qStyle = QApplication::style();
	initTool();
	initZipWidget();
	initXMLWidget();
	initMainWin();
}

void MainWindow::initZipWidget()
{
	m_zipWidget = new QWidget();
	m_zipTreeView = new QTreeView(m_zipWidget);
	m_fileSystemModel = new QFileSystemModel();

//	m_fileSystemModel->setRootPath(QDir::currentPath());
//	m_zipTreeView->setModel(m_fileSystemModel);
//	m_zipTreeView->setRootIndex(m_fileSystemModel->index(QDir::currentPath()));
	connect(m_zipTreeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(getTreeViewSelectedFileName(QModelIndex)));

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(m_zipTreeView);
	layout->setContentsMargins(1,1,1,1);
	m_zipWidget->setLayout(layout);
}

void MainWindow::getTreeViewSelectedFileName(QModelIndex index)
{
	QString strFilePath = m_fileSystemModel->filePath(index);
	return;
}

void MainWindow::openFile()
{
	QString strFilter = "*.docx";
	QString strDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
	m_strFullFileName = QFileDialog::getOpenFileName(this,"ZipViewer", strDir, strFilter);
	if(m_strFullFileName.isEmpty())
		return;

	int nCount = m_strFullFileName.length();
	int nFlag = m_strFullFileName.lastIndexOf("\/");
	m_strFilePath = m_strFullFileName.mid(0, nFlag);
	m_strFileName = m_strFullFileName.mid(nFlag + 1, nCount);

	// init zipWidget
	QString strCurrentPath = QDir::currentPath();
	m_fileSystemModel->setRootPath(QDir::currentPath());
	m_zipTreeView->setModel(m_fileSystemModel);
	m_zipTreeView->setRootIndex(m_fileSystemModel->index(QDir::currentPath()));

	// init xmlwidget
}

void MainWindow::closeApp()
{
	close();
}

void MainWindow::initXMLWidget()
{
	m_xmlWidget = new QWidget();
	QTextEdit* xmlEdit = new QTextEdit();

	//xml reader
	QString strPathFile = "D:\\QTProject\\OFDReader\\ofd_file\\OFD.xml";
	QFile file(strPathFile);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	xmlEdit->setText(in.readAll());
	xmlEdit->setFontFamily("Consolas");
	file.close();


	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(xmlEdit);
	layout->setContentsMargins(1,1,1,1);
	m_xmlWidget->setLayout(layout);

}

void MainWindow::initMainWin()
{
	QSplitter* mainSplitter = new QSplitter(Qt::Horizontal, 0);
	mainSplitter->addWidget(m_zipWidget);
	mainSplitter->addWidget(m_xmlWidget);
	//分割条宽度
	mainSplitter->setHandleWidth(2);
	setCentralWidget(mainSplitter);
}

void MainWindow::initTool()
{
	QToolBar* toolBar = new QToolBar(this);
	addToolBar(Qt::TopToolBarArea, toolBar);

	QAction* openAction = new QAction(this);
	QIcon iconOpen = m_qStyle->standardIcon(QStyle::SP_DirOpenIcon);
	openAction->setIcon(iconOpen);
	QAction* exitAction = new QAction(this);
	QIcon iconClose = m_qStyle->standardIcon(QStyle::SP_DirClosedIcon);
	exitAction->setIcon(iconClose);
	toolBar->addAction(openAction);
	toolBar->addAction(exitAction);

	connect(openAction,SIGNAL(triggered()), this, SLOT(openFile()));
	connect(exitAction,SIGNAL(triggered()), this, SLOT(closeApp()));

}

MainWindow::~MainWindow()
{

}
