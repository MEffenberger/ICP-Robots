#include "robotdialog.h"

CustomDialog::CustomDialog(QWidget *parent, bool robotExists) : QDialog(parent) {
    orientationSpinBox = new QSpinBox(this);
    distanceSpinBox = new QSpinBox(this);
    rotationAngleSpinBox = new QSpinBox(this);
    velocitySpinBox = new QSpinBox(this);

    orientationSpinBox->setRange(0, 360);
    distanceSpinBox->setRange(1, 1000);
    distanceSpinBox->setEnabled(!robotExists);
    rotationAngleSpinBox->setRange(-360, 360);
    velocitySpinBox->setRange(1, 10);

    QFormLayout *layout = new QFormLayout(this);
    layout->addRow(new QLabel("Robot map orientation (degrees):"), orientationSpinBox);
    layout->addRow(new QLabel("Distance of detecting obstacles (pixels):"), distanceSpinBox);
    layout->addRow(new QLabel("Rotation after detection obstacle (degrees):"), rotationAngleSpinBox);
    layout->addRow(new QLabel("Robot speed (10 max, 1 min):"), velocitySpinBox);

    QPushButton *okButton = new QPushButton("OK", this);
    layout->addWidget(okButton);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
}

int CustomDialog::getOrientation() const {
    return orientationSpinBox->value();
}

int CustomDialog::getDistance() const {
    return distanceSpinBox->value();
}

int CustomDialog::getRotationAngle() const {
    return rotationAngleSpinBox->value();
}

int CustomDialog::getVelocity() const {
    return velocitySpinBox->value();
}
