#ifndef ROBOTDIALOG_H
#define ROBOTDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>

/**
 * @brief The RobotParamDialog class
 * 
 * This class is used to create a dialog where the user can input the parameters of the robot
 */
class RobotParamDialog : public QDialog {
    Q_OBJECT

public:
    explicit RobotParamDialog(QWidget *parent = nullptr, bool robotExists = false);

    /**
     * @brief Gets the orientation of the controlled or enemy robot
     * 
     * @return int orientation
     */
    int getOrientation();

    /**
     * @brief Gets the distance of the controlled or enemy robot
     * 
     * @return int distance
     */
    int getDistance();

    /**
     * @brief Gets the rotation angle of the controlled or enemy robot
     * 
     * @return int angle
     */
    int getRotationAngle();

    /**
     * @brief Gets the velocity of the controlled or enemy robot
     * 
     * @return int velocity
     */
    int getVelocity();

    /**
     * @brief Creates the layout of the dialog 
     */
    void createLayout();

private:
    QSpinBox *orientationBox;
    QSpinBox *distanceBox;
    QSpinBox *rotationAngleBox;
    QSpinBox *velocityBox;
};

#endif // ROBOTDIALOG_H
