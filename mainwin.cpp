#include "mainwin.hpp"
/*保存时统一使用utf8保存*/
using namespace std;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          settings(local.OrganizationName, local.ApplicationName),
                                          openingFileName("临时文件")

{
    textEdit = new QTextEdit(this);
    menuBar = new QMenuBar(this);

    /*编辑部分初始化*/
    setWindowTitle(openingFileName);
    setCentralWidget(textEdit);
    textEdit->setObjectName("editor");
    isTxtChanged = false;

    /*菜单栏部分初始化*/
    setMenuBar(menuBar);
    auto fileMenu = menuBar->addMenu("文件");
    auto openAction = fileMenu->addAction("打开");
    openAction->setObjectName("openF");
    auto saveAction = fileMenu->addAction("保存");
    saveAction->setObjectName("saveF");
    auto saveAsAction = fileMenu->addAction("另存为");
    saveAsAction->setObjectName("saveAsF");

    auto editMenu = menuBar->addMenu("编辑");
    auto autoWarpAction = editMenu->addAction("自动换行");
    autoWarpAction->setCheckable(true);
    bool checked = settings.value("autoWarp").toBool();
    autoWarpAction->setChecked(checked);
    on_autoWarp_triggered(true);
    autoWarpAction->setObjectName("autoWarp");

    QMetaObject::connectSlotsByName(this);
}
void MainWindow::autoChangeFileName(QString fileName)
{
    this->openingFileName = fileName;
    setWindowTitle(openingFileName);
}

void MainWindow::openFile(QString fileName)
{
    QFile file(fileName);
    if (file.open(QFile::ReadOnly))
    {
        autoChangeFileName(fileName);
        QString text = QString::fromUtf8(file.readAll());
        textEdit->setPlainText(text);
        file.close();
    }
    else
    {
        QMessageBox::warning(this, "打开文件", "无法打开文件：" + fileName);
    }
}

void MainWindow::saveFile(QString fileName)
{
    QFile file(fileName);
    if (file.open(QFile::WriteOnly))
    {
        autoChangeFileName(fileName);
        file.write(textEdit->toPlainText().toUtf8());
        file.close();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isTxtChanged)
    {
        auto choice = QMessageBox::question(this, "关闭窗口", "文件已修改，是否保存？",
                                            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        switch (choice)
        {
        case QMessageBox::Yes:
            on_saveF_triggered();
            break;
        case QMessageBox::No:
            break;
        case QMessageBox::Cancel:
            event->ignore();
            return;
        }
    }
    QMainWindow::closeEvent(event);
}

/*槽函数*/
void MainWindow::on_openF_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", "", "文本文件 (*.txt) ;; 全部文件 (*)");
    if (!fileName.isEmpty())
    {
        openFile(fileName);
        isTxtChanged = false;
    }
}

void MainWindow::on_saveF_triggered()
{
    QString fileName = openingFileName;
    if (openingFileName == "临时文件")
        fileName = QFileDialog::getSaveFileName(this, "保存文件", "", "文本文件 (*.txt) ;; 全部文件 (*)");
    if (!fileName.isEmpty())
    {
        saveFile(fileName);
        isTxtChanged = false;
    }
}

void MainWindow::on_saveAsF_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "另存为", "", "文本文件 (*.txt) ;; 全部文件 (*)");
    if (!fileName.isEmpty())
    {
        saveFile(fileName);
        isTxtChanged = false;
    }
}

void MainWindow::on_autoWarp_triggered(bool checked)
{
    if (checked)
        textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    else
        textEdit->setLineWrapMode(QTextEdit::NoWrap);
    settings.setValue("autoWarp", checked);
}

void MainWindow::on_editor_textChanged()
{
    if (!isTxtChanged)
        setWindowTitle(openingFileName + "*");
    isTxtChanged = true;
}
