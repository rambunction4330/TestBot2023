// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "drivetrain/DriveSubsystem.h"

#include <iostream>

void DriveSubsystem::arcadeDrive(double xSpeed, double zRotation) {
  drive.arcadeDrive(xSpeed, zRotation);
}

void DriveSubsystem::arcadeDrive(frc2::CommandJoystick& stick) {
  arcadeDrive(stick.GetY(), stick.GetTwist());
}

void DriveSubsystem::arcadeDrive(frc2::CommandXboxController& controller) {
  arcadeDrive(controller.GetRawAxis(1), controller.GetRawAxis(2));
}

void DriveSubsystem::arcadeDrive(frc2::CommandPS4Controller& controller) {
  arcadeDrive(controller.GetRawAxis(1), controller.GetRawAxis(2));
}

void DriveSubsystem::curvatureDrive(double xSpeed, double zRotation, bool turnInPlace) {
  drive.curvatureDrive(xSpeed, zRotation, turnInPlace);
}

void DriveSubsystem::curvatureDrive(frc2::CommandJoystick& stick) {
  curvatureDrive(stick.GetY(), stick.GetTwist(), stick.GetTrigger());
}

void DriveSubsystem::curvatureDrive(frc2::CommandXboxController& controller) {
  curvatureDrive(controller.GetRawAxis(1), controller.GetRawAxis(2), controller.GetLeftBumper());
}

void DriveSubsystem::curvatureDrive(frc2::CommandPS4Controller& controller) {
  curvatureDrive(controller.GetRawAxis(1), controller.GetRawAxis(2), controller.GetL2Button());
}

void DriveSubsystem::tankDrive(double leftSpeed, double rightSpeed) {
  drive.tankDrive(leftSpeed, rightSpeed);
}

void DriveSubsystem::tankDrive(frc2::CommandXboxController& controller) {
  tankDrive(controller.GetRawAxis(1), controller.GetRawAxis(3));
}

void DriveSubsystem::tankDrive(frc2::CommandPS4Controller& controller) {
  tankDrive(controller.GetRawAxis(1), controller.GetRawAxis(3));
}

// This method will be called once per scheduler run
void DriveSubsystem::Periodic() {}
