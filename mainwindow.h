/**
 * @file mainwindow.h
 * @brief Main Window Class Header file
 * @version 1.0
 * @details This class is responsible for creating the main window of the robot game
 * @project ICP Project - Epic Robot Survival
 * @author Samuel Hejnicek
 */

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

/**
 * @brief The MainWindow class
 * 
 * This class is used to hold the main window of the application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief Quits the app when the exit button is pressed
     * 
     */
    void quitApp();

    /**
     * @brief Starts loading game from JSON file when the load button is pressed
     * 
     */
    void loadGame();

    /**
     * @brief Applies background and font to the main window
     * 
     */
    void applyGraphics();

private slots:
    /**
     * @brief Emits signal to create a new map window
     * 
     */
    void createNewWindow();

private:
    /** Ui object */
    Ui::MainWindow *ui;

signals:
    /**
     * @brief Signal to create a new map window
     * 
     */
    void createNewMapWindow();

    /**
     * @brief Signal to start loading a JSON file
     * 
     */
    void loadFile();
};
#endif // MAINWINDOW_H
