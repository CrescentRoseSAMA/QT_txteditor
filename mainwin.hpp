#pragma once
#include <iostream>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QApplication>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QMetaObject>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QCloseEvent>
#include <QSettings>
#include <QFontDatabase>
static const struct LocalSetting
{
    QString OrganizationName = "KazeRose";
    QString ApplicationName = "txtEditor";
} local;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSettings settings;
    QString openingFileName;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    bool isTxtChanged;

public:
    explicit MainWindow(QWidget *parent = 0);
    void openFile(QString fileName);
    void saveFile(QString fileName);
    void autoChangeFileName(QString fileName);

protected:
    void closeEvent(QCloseEvent *event) override;
private Q_SLOTS:
    void on_openF_triggered();
    void on_saveF_triggered();
    void on_saveAsF_triggered();
    void on_autoWarp_triggered(bool checked);
    void on_editor_textChanged();
};
