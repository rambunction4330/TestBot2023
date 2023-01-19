// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <iostream>

#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/Trajectory.h>

RobotContainer::RobotContainer() {
  // Set Default Commands
  driveSubsystem.SetDefaultCommand(driveSubsystem.arcadeDriveCommand(driveGamepad));

  // Configure the button bindings
  ConfigureBindings();
}

void RobotContainer::scheduleAutoCommand() {
  driveSubsystem.resetOdometry(frc::Pose2d(0.0_m, 0.0_m, 0.0_rad));
  if (!autoCommand.IsScheduled()) {
    frc::TrajectoryConfig config{2.5_mps, 2.0_mps_sq};
    config.SetKinematics(DriveConstants::kinematics);

    frc::Trajectory trajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      frc::Pose2d(0.0_m, 0.0_m, 0.0_rad), 
      {{2.0_m, 1.0_m}, {1.2_m, 1.8_m}, {2.0_m, 2.7_m}}, 
      frc::Pose2d(3.0_m, 3.0_m, 0.0_deg),
      config
    );

    autoCommand = driveSubsystem.getTrajectoryCommand(trajectory);
    autoCommand.Schedule();
  }
}

void RobotContainer::ConfigureBindings() {
  // Configure your trigger bindings here
}
