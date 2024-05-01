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
    rotationAngleBox->setRange(-360, 360);
    this->rotationAngleBox->setValue(45);
    velocityBox->setRange(1, 10);
    this->velocityBox->setValue(5);

    //Create layout with the spin boxes
    createLayout();
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

void RobotParamDialog::createLayout(){
    this->setWindowTitle("Robot parameters");
    QFormLayout *layout = new QFormLayout(this);
    layout->addRow(new QLabel("Robot map orientation (degrees):"), orientationBox);
    layout->addRow(new QLabel("Distance of detecting obstacles (5 max, 1 min):"), distanceBox);
    layout->addRow(new QLabel("Rotation after detection obstacle (degrees):"), rotationAngleBox);
    layout->addRow(new QLabel("Robot speed (10 max, 1 min):"), velocityBox);

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
    connect(confirmButton, &QPushButton::clicked, this, &QDialog::accept);
}
