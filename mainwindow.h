#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void quitApp();
    void loadGame();

private slots:
    void createNewWindow();

private:
    Ui::MainWindow *ui;

signals:
    void createNewMapWindow();
    void loadFile();
};
#endif // MAINWINDOW_H
