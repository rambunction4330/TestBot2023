// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <iostream>

#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/Trajectory.h>

#include <frc2/command/ScheduleCommand.h>
#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SequentialCommandGroup.h>

RobotContainer::RobotContainer() {
  // driveSubsystem.SetDefaultCommand(driveSubsystem.arcadeDriveCommand(driveGamepad));

  // Configure the button bindings
  ConfigureBindings();
}

void RobotContainer::scheduleAutoCommand() {
  if (autoCommand.IsScheduled()) { return; }
  
  // Zero dometry
  driveSubsystem.resetOdometry(frc::Pose2d(0.0_m, 0.0_m, 0.0_rad));

  // Generate Trajectory
  frc::TrajectoryConfig config{1.0_mps, 2.0_mps_sq};
  config.SetKinematics(DriveConstants::kinematics);
  config.SetReversed(false);

  frc::Trajectory trajectory = frc::TrajectoryGenerator::GenerateTrajectory(
    frc::Pose2d(0.0_m, 0.0_m, 0.0_rad), 
    {{1.2_m, 0.0_m}, {1.7_m, -0.75_m}}, 
    frc::Pose2d(1.6_m, -1.4_m, 180.0_deg),
    config
  );

  // Drives a trajectory to the front of the charging pad and  the balances on it
  autoCommand = driveSubsystem.getTrajectoryCommand(trajectory).AndThen(frc2::CommandPtr(BalanceCommand(driveSubsystem)));

  // Start to command
  autoCommand.Schedule();
}

void RobotContainer::ConfigureBindings() {
  // Configure your trigger bindings here
  driveGamepad.A().WhileTrue(frc2::CommandPtr(frc2::cmd::Wait(0.5_s)).AndThen(LedSubsystem.ledIncreaseCommand()).AndThen(LedSubsystem.SetledToCommand()).Repeatedly());
  driveGamepad.B().WhileTrue(frc2::CommandPtr(frc2::CommandPtr(frc2::InstantCommand([&] { LedSubsystem.setledToThis(LedSubsystem.red); }))));
  driveGamepad.X().WhileTrue(frc2::CommandPtr(frc2::CommandPtr(frc2::InstantCommand([&] { LedSubsystem.setledToThis(LedSubsystem.blue); }))));
  driveGamepad.Y().WhileTrue(frc2::CommandPtr(frc2::CommandPtr(frc2::InstantCommand([&] { LedSubsystem.setledToThis(LedSubsystem.yellow); }))));
  // search up rev robotics led docs to customize the led colors and pass them into the parameters
}
