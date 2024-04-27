#ifndef ROBOTDIALOG_H
#define ROBOTDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>

class CustomDialog : public QDialog {
    Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = nullptr, bool robotExists = false);

    int getOrientation() const;
    int getDistance() const;
    int getRotationAngle() const;
    int getVelocity() const;

private:
    QSpinBox *orientationSpinBox;
    QSpinBox *distanceSpinBox;
    QSpinBox *rotationAngleSpinBox;
    QSpinBox *velocitySpinBox;
};

#endif // ROBOTDIALOG_H
