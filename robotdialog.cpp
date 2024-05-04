/**
 * @file robotdialog.cpp
 * @brief Robot Dialog Class Implementation file
 * @version 1.0
 * @details This class is responsible for creating a dialog where user can input the parameters of the robot/enemy
 * @project ICP Project - Epic Robot Survival
 * @author Samuel Hejnicek
 */

#include "robotdialog.h"

RobotParamDialog::RobotParamDialog(QWidget *parent, bool robotExists) : QDialog(parent) {
    //Create spin boxes
    orientationBox = new QSpinBox(this);
    distanceBox = new QSpinBox(this);
    rotationAngleBox = new QSpinBox(this);
    velocityBox = new QSpinBox(this);

    //If robot exists, grey out the distance and rotation angle boxes
    if(robotExists) {
        distanceBox->setEnabled(false);
        rotationAngleBox->setEnabled(false);
    } else {
        distanceBox->setEnabled(true);
        rotationAngleBox->setEnabled(true);
    }

    //Set range and default values
    orientationBox->setRange(0, 360);
    distanceBox->setRange(1, 5);
    this->distanceBox->setValue(3);
    rotationAngleBox->setRange(0, 360);
    this->rotationAngleBox->setValue(45);
    velocityBox->setRange(1, 10);
    this->velocityBox->setValue(5);

    //Create layout with the spin boxes
    createLayout(robotExists);
}

int RobotParamDialog::getOrientation() {
    return orientationBox->value();
}

int RobotParamDialog::getDistance() {
    return distanceBox->value();
}

int RobotParamDialog::getRotationAngle() {
    return rotationAngleBox->value();
}

int RobotParamDialog::getVelocity() {
    return velocityBox->value();
}

void RobotParamDialog::createLayout(bool robotExists){
    //Set window title
    this->setWindowTitle("Robot parameters");

    //Create layout for dialog
    this->layout = new QFormLayout(this);
    layout->addRow(new QLabel("Robot map orientation (degrees):"), orientationBox);
    layout->addRow(new QLabel("Distance of detecting obstacles (5 max, 1 min):"), distanceBox);
    
    //Create sublayout for left/right button
    this->LRLayout = new QFormLayout;

    //Default direction is right
    this->directionButton = new QPushButton("Right", this);
    if(robotExists){
        //Robot exists, disable the button
        this->directionButton->setEnabled(false);
    }
    //Set button params
    directionButton->setFixedHeight(30);
    directionButton->setFixedWidth(50);

    //Add button to custom layout and add layout to main layout
    LRLayout->addRow(directionButton);
    LRLayout->setAlignment(Qt::AlignRight);

    //Add rest of the spin boxes to the layout
    layout->addRow(new QLabel("Rotation after detecting obstacle direction:"), LRLayout);
    layout->addRow(new QLabel("Rotation after detection obstacle (degrees):"), rotationAngleBox);
    layout->addRow(new QLabel("Robot speed (10 max, 1 min):"), velocityBox);

    //Create new sublayout for buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    
    //Create buttons
    QPushButton *cancelButton = new QPushButton("Cancel", this);
    QPushButton *confirmButton = new QPushButton("Confirm", this);
    
    //Add buttons to layout
    buttonLayout->addWidget(cancelButton); 
    buttonLayout->addWidget(confirmButton); 
    buttonLayout->setAlignment(Qt::AlignRight);

    //Add button layout to main layout
    layout->addRow(buttonLayout);

    //Connect buttons to slots
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(confirmButton, &QPushButton::clicked, this, &RobotParamDialog::confirmDialog);
    connect(directionButton, &QPushButton::clicked, this, &RobotParamDialog::changeTurningDirection);
}

void RobotParamDialog::changeTurningDirection(){

    //If button is Right, change it to left
    if(this->directionButton->text() == "Right"){
        this->directionButton->setText("Left");
    } else {
        this->directionButton->setText("Right");
    }
    
}

void RobotParamDialog::confirmDialog(){

    //If button isnt disabled and is left, change the rotation angle to negative
    if(this->directionButton->isEnabled()){
        if(this->directionButton->text() == "Left"){
            this->rotationAngleBox->setRange(-360, 360);
            this->rotationAngleBox->setValue(this->rotationAngleBox->value() * -1);
        }
    }
    //Close the dialog
    this->accept();
}
