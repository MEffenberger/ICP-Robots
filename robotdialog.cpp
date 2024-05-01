#include "robotdialog.h"

RobotParamDialog::RobotParamDialog(QWidget *parent, bool robotExists) : QDialog(parent) {
    orientationBox = new QSpinBox(this);
    distanceBox = new QSpinBox(this);
    rotationAngleBox = new QSpinBox(this);
    velocityBox = new QSpinBox(this);

    if(robotExists) {
        distanceBox->setEnabled(false);
        rotationAngleBox->setEnabled(false);
    } else {
        distanceBox->setEnabled(true);
        rotationAngleBox->setEnabled(true);
    }
    orientationBox->setRange(0, 360);
    distanceBox->setRange(1, 5);
    rotationAngleBox->setRange(-360, 360);
    velocityBox->setRange(1, 10);
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
    QPushButton *cancelButton = new QPushButton("Cancel", this);
    QPushButton *confirmButton = new QPushButton("Confirm", this);
    
    buttonLayout->addWidget(cancelButton); 
    buttonLayout->addWidget(confirmButton); 
    buttonLayout->setAlignment(Qt::AlignRight);

    layout->addRow(buttonLayout);

    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(confirmButton, &QPushButton::clicked, this, &QDialog::accept);
}
