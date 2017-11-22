#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
//    initTool();
	initZipWidget();
	initXMLWidget();
	initMainWin();
}

void MainWindow::initZipWidget()
{
	m_zipWidget = new QWidget();

	m_fileSystemModel = new QFileSystemModel();
	m_fileSystemModel->setRootPath(QDir::currentPath());
	QTreeView* treeView = new QTreeView(m_zipWidget);
	treeView->setModel(m_fileSystemModel);
	treeView->setRootIndex(m_fileSystemModel->index(QDir::currentPath()));

	connect(treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(getTreeViewSelectedFileName(QModelIndex)));

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(treeView);
	layout->setContentsMargins(1,1,1,1);
	m_zipWidget->setLayout(layout);
}

void MainWindow::getTreeViewSelectedFileName(QModelIndex index)
{
	QString strFilePath = m_fileSystemModel->filePath(index);
	return;
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


	this->setCentralWidget(mainSplitter);
}

MainWindow::~MainWindow()
{

}
