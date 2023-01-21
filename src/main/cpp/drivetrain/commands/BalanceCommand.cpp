// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "drivetrain/commands/BalanceCommand.h"

#include <units/math.h>
#include <iostream>

BalanceCommand::BalanceCommand(DriveSubsystem& drive, bool r) : 
  driveSubsystem(drive), reversed(r ? -1 : 1) {
  AddRequirements({&driveSubsystem});

  
}

// Called when the command is initially scheduled.
void BalanceCommand::Initialize() {
  offset = driveSubsystem.getPose();
}

// Called repeatedly when this Command is scheduled to run
void BalanceCommand::Execute() {
  goal = std::clamp(goal + (driveSubsystem.getRobotPitch() * -gain), minX, maxX) * reversed;
  
  frc::TrapezoidProfile<units::meters> profile = {constraints, 
                                                  {goal, 0.0_mps}, 
                                                  {(driveSubsystem.getPose() - offset).X(), driveSubsystem.getChassisSpeeds().vx}};

  driveSubsystem.driveChassisSpeeds({profile.Calculate(20_ms).velocity, 0.0_mps, 0.0_rpm});

  if (units::math::abs(driveSubsystem.getRobotPitch()) < 2.5_deg) {
    balanceTimer.Start();
  } else {
    balanceTimer.Stop();
    balanceTimer.Reset();
  }
}

// Called once the command ends or is interrupted.
void BalanceCommand::End(bool interrupted) {
  driveSubsystem.stop(); 
}

// Returns true when the command should end.
bool BalanceCommand::IsFinished() {
  return balanceTimer.Get() > 0.5_s;
}
