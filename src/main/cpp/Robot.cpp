#include "Robot.hpp"

#include <cameraserver/CameraServer.h>

void Robot::RobotInit() {
  frc::CameraServer::StartAutomaticCapture();

  leftFollow.Follow(left);
  rightFollow.Follow(right);
}

void Robot::TeleopPeriodic()  {
  // y-axis of left stick determines power
  // x-axis of right stick turns
  // drive.CurvatureDrive(controller.GetLeftY(),
  //                      controller.GetRightX(), controller.GetL1Button());

  drive.ArcadeDrive(controller.GetLeftY(),
                    -controller.GetRightX());
}  