#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	m_qStyle = QApplication::style();
	initTool();
	initZipWidget();
	initXMLWidget();
	initMainWin();
	resize(500, 500);
}

MainWindow::~MainWindow()
{
	m_file->close();
	_deleteDir(m_strNewFolder);
}

void MainWindow::initZipWidget()
{
	m_zipWidget = new QWidget();
	m_zipTreeView = new QTreeView(m_zipWidget);
	m_fileSystemModel = new QFileSystemModel();

	connect(m_zipTreeView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(showXml(const QModelIndex&)));

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(m_zipTreeView);
	layout->setContentsMargins(1,1,1,1);
	m_zipWidget->setLayout(layout);
}

void MainWindow::showXml(const QModelIndex& index)
{
	if (!index.isValid())
		return;

	QString strFilePath = m_fileSystemModel->filePath(index);

	m_file->setFileName(strFilePath);
	m_file->open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(m_file);
	m_xmlTextEdit->setText(in.readAll());
	m_file->close();

	QFont font;
	font.setFamily("Consolas");
	font.setPointSize(16);
	m_xmlTextEdit->setFont(font);

	return;
}

void MainWindow::openFile()
{
	QString strFilter = "*.docx *.pptx *.xlsx *.ofd";
	QString strDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
	m_strFullFileName = QFileDialog::getOpenFileName(this,"ZipViewer", strDir, strFilter);
	if(m_strFullFileName.isEmpty())
		return;

	int nCount = m_strFullFileName.length();
	//qt内部默认是符号/
	int nFlag = m_strFullFileName.lastIndexOf("\/");
	m_strFilePath = m_strFullFileName.mid(0, nFlag);
	m_strFileName = m_strFullFileName.mid(nFlag + 1, nCount);

	nFlag = m_strFileName.indexOf(".");
	m_strName = m_strFileName.mid(0, nFlag);

	// init after open
	initAterOpen();
}

void MainWindow::initAterOpen()
{
	// 创建新的文件夹并解压
	m_strNewFolder = m_strFilePath + "\/" + m_strName;
	bool bIsExists = m_Dir.exists(m_strNewFolder);
	if (!bIsExists)
	{
		if (!m_Dir.mkdir(m_strNewFolder))
		{
			QMessageBox::question(this, "warnning", "创建缓存失败");
			return;
		}
	}
	else
	{
		//已经存在咋办？
	}

	// 解压文件
	JlCompress::extractDir(m_strFullFileName, m_strNewFolder + "\/");
	m_fileSystemModel->setRootPath(m_strNewFolder);
	m_zipTreeView->setModel(m_fileSystemModel);
	m_zipTreeView->setRootIndex(m_fileSystemModel->index(m_strNewFolder));
}

void MainWindow::closeApp()
{
	close();
}

void MainWindow::initXMLWidget()
{
	m_xmlWidget = new QWidget();
	m_xmlTextEdit = new QTextEdit();
	m_file = new QFile();

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(m_xmlTextEdit);
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

bool MainWindow::_deleteDir(const QString &dirName)
{
	QDir directory(dirName);
	if (!directory.exists())
	{
		return true;
	}

	QString srcPath = QDir::toNativeSeparators(dirName);
	if (!srcPath.endsWith(QDir::separator()))
		srcPath += QDir::separator();

	QStringList fileNames = directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
	bool error = false;
	for (QStringList::size_type i=0; i != fileNames.size(); ++i)
	{
		QString filePath = srcPath + fileNames.at(i);
		QFileInfo fileInfo(filePath);
		if (fileInfo.isFile() || fileInfo.isSymLink())
		{
			QFile::setPermissions(filePath, QFile::WriteOwner);
			if (!QFile::remove(filePath))
			{
//				qDebug() << "remove file" << filePath << " faild!";
				error = true;
			}
		}
		else if (fileInfo.isDir())
		{
			if (!_deleteDir(filePath))
			{
				error = true;
			}
		}
	}

	if (!directory.rmdir(QDir::toNativeSeparators(directory.path())))
	{
//		qDebug() << "remove dir" << directory.path() << " faild!";
		error = true;
	}

	return !error;
}
