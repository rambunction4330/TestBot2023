// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "drivetrain/DriveSubsystem.h"

#include <iostream>

void DriveSubsystem::arcadeDrive(double xSpeed, double zRotation) {
  drive.arcadeDrive(xSpeed, zRotation);
}

void DriveSubsystem::arcadeDrive(const rmb::LogitechJoystick& joystick) {
  arcadeDrive(joystick.GetX(), joystick.GetTwist());
}

void DriveSubsystem::arcadeDrive(const rmb::LogitechGamepad& gamepad) {
  arcadeDrive(gamepad.GetLeftX(), gamepad.GetRightY());
}


void DriveSubsystem::curvatureDrive(double xSpeed, double zRotation, bool turnInPlace) {
  drive.curvatureDrive(xSpeed, zRotation, turnInPlace);
}

void DriveSubsystem::curvatureDrive(const rmb::LogitechJoystick& stick) {
  curvatureDrive(stick.GetX(), stick.GetTwist(), stick.GetTrigger());
}

void DriveSubsystem::curvatureDrive(const rmb::LogitechGamepad& controller) {
  curvatureDrive(controller.GetLeftX(), controller.GetRightY(), controller.GetLeftBumper());
}

void DriveSubsystem::tankDrive(double leftSpeed, double rightSpeed) {
  drive.tankDrive(leftSpeed, rightSpeed);
}

void DriveSubsystem::tankDirve(const rmb::LogitechJoystick& left, const rmb::LogitechJoystick& right) {
  tankDrive(left.GetX(), right.GetX());
}

void DriveSubsystem::tankDrive(const rmb::LogitechGamepad& gamepad) {
  tankDrive(gamepad.GetLeftX(), gamepad.GetRightX());
}

// This method will be called once per scheduler run
void DriveSubsystem::Periodic() {
  odometry.updatePose();
}
