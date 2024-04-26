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
    explicit CustomDialog(QWidget *parent = nullptr);

    int getOrientation() const;
    int getDistance() const;
    int getRotationAngle() const;
    //int getDirection() const;

private:
    QSpinBox *orientationSpinBox;
    QSpinBox *distanceSpinBox;
    QSpinBox *rotationAngleSpinBox;
    //QSpinBox *directionSpinBox;
};

#endif // ROBOTDIALOG_H
