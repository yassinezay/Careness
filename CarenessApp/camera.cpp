#include "camera.h"
#include "ui_mainwindow.h"



void camera::setCamera(const QCameraInfo &cameraInfo)
{
    Camera = new QCamera(cameraInfo);
    imageCapture = new QCameraImageCapture(Camera);
    connect(imageCapture, &QCameraImageCapture::readyForCaptureChanged, this, &camera::readyForCapture);
    Camera->start();
}
