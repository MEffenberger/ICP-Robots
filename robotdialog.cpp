#include "robotdialog.h"

CustomDialog::CustomDialog(QWidget *parent, bool robotExists) : QDialog(parent) {
    orientationSpinBox = new QSpinBox(this);
    distanceSpinBox = new QSpinBox(this);
    rotationAngleSpinBox = new QSpinBox(this);
    velocitySpinBox = new QSpinBox(this);

    orientationSpinBox->setRange(0, 360);
    distanceSpinBox->setRange(1, 5);
    distanceSpinBox->setEnabled(!robotExists);
    rotationAngleSpinBox->setRange(-360, 360);
    rotationAngleSpinBox->setEnabled(!robotExists);
    velocitySpinBox->setRange(1, 10);
    
    this->setWindowTitle("Robot parameters");
    QFormLayout *layout = new QFormLayout(this);
    layout->addRow(new QLabel("Robot map orientation (degrees):"), orientationSpinBox);
    layout->addRow(new QLabel("Distance of detecting obstacles (5 max, 1 min):"), distanceSpinBox);
    layout->addRow(new QLabel("Rotation after detection obstacle (degrees):"), rotationAngleSpinBox);
    layout->addRow(new QLabel("Robot speed (10 max, 1 min):"), velocitySpinBox);

    QHBoxLayout* buttonLayout = new QHBoxLayout;  // Horizontal layout for buttons
    QPushButton *cancelButton = new QPushButton("Cancel", this);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    QPushButton *confirmButton = new QPushButton("Confirm", this);
    connect(confirmButton, &QPushButton::clicked, this, &QDialog::accept);
    buttonLayout->addWidget(cancelButton); 
    buttonLayout->addWidget(confirmButton); 
    buttonLayout->setAlignment(Qt::AlignRight);
    layout->addRow(buttonLayout);
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
