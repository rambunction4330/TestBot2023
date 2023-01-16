// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <thread>

#include <frc2/command/CommandPtr.h>

#include <AHRS.h>

#include <rmb/motorcontrol/feedback/LinearVelocityFeedbackController.h>
#include <rmb/motorcontrol/sparkmax/SparkMaxVelocityController.h>
#include <rmb/drive/DifferentialDrive.h>
#include <rmb/drive/DifferentialOdometry.h>

#include <rmb/controller/LogitechGamepad.h>
#include <rmb/controller/LogitechJoystick.h>

namespace DriveConstants {

  const rmb::SparkMaxVelocityController::MotorConfig leftLeader {
    11, rev::CANSparkMax::MotorType::kBrushless, true
  };

  const rmb::SparkMaxVelocityController::MotorConfig leftFollower {
    12, rev::CANSparkMax::MotorType::kBrushless, false
  };

  const rmb::SparkMaxVelocityController::MotorConfig rightLeader {
    21, rev::CANSparkMax::MotorType::kBrushless, false
  };

  const rmb::SparkMaxVelocityController::MotorConfig rightFollower {
    22, rev::CANSparkMax::MotorType::kBrushless, false
  };

  const rmb::SparkMaxVelocityController::PIDConfig pidConfig {
    0.0 /*  <- P */ , 0.0 /* <- I */, 0.0 /* <- D */, 0.0 /* <- F */,
    0.0_rad_per_s /* <- Tolerance */, 
    0.0 /* <- iZone */, 0.0 /* <- iMaxAccumulator */,
    1.0 /* <- maxOutput */, -1.0 /* <- minOutput */
  };

  const rmb::SparkMaxVelocityController::ProfileConfig profileConfig {
    false /* <- useSmartMotion */, 
    0.0_rad_per_s /* <- maxVelocity */, 0.0_rad_per_s /* <- minVelocity */,
    0.0_rad_per_s_sq /* <- maxAcceleration */,
    rev::SparkMaxPIDController::AccelStrategy::kTrapezoidal /* <- accelStrategy */
  };

  const rmb::SparkMaxVelocityController::FeedbackConfig feedbackConfig {
    1.0 /* <- gearRatio */, 
    rmb::SparkMaxVelocityController::EncoderType::HallSensor/* <- encoderType */,
    42 /* <- countPerRev */,
    rmb::SparkMaxVelocityController::LimitSwitchConfig::Disabled /* <- forwardSwitch */,
    rmb::SparkMaxVelocityController::LimitSwitchConfig::Disabled /* <- reverseSwitch */
  };

  static frc::DifferentialDriveKinematics kinematics{ 27.75_in /* <- track width */};

  const units::meter_t wheelDiameter = 7_in;

  const frc::SerialPort::Port gyroPort = frc::SerialPort::Port::kMXP;
}

class DriveSubsystem : public frc2::SubsystemBase {
 public:
  DriveSubsystem() = default;

  void arcadeDrive(double xSpeed, double zRotation);
  void arcadeDrive(const rmb::LogitechJoystick& joystick);
  void arcadeDrive(const rmb::LogitechGamepad& gamepad);
  frc2::CommandPtr arcadeDriveCommand(const rmb::LogitechJoystick& joystick);
  frc2::CommandPtr arcadeDriveCommand(const rmb::LogitechGamepad& gamepad);

  void curvatureDrive(double xSpeed, double zRotation, bool turnInPlace);
  void curvatureDrive(const rmb::LogitechJoystick& stick);
  void curvatureDrive(const rmb::LogitechGamepad& gamepad);
  frc2::CommandPtr curvatureDriveCommand(const rmb::LogitechJoystick& stick);
  frc2::CommandPtr curvatureDriveCommand(const rmb::LogitechGamepad& gamepad);

  void tankDrive(double leftSpeed, double rightSpeed);
  void tankDrive(const rmb::LogitechJoystick& left, const rmb::LogitechJoystick& right);
  void tankDrive(const rmb::LogitechGamepad& gamepad);
  frc2::CommandPtr tankDirveCommand(const rmb::LogitechJoystick& left, const rmb::LogitechJoystick& right);
  frc2::CommandPtr tankDriveCommand(const rmb::LogitechGamepad& gamepad);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  std::shared_ptr<rmb::LinearVelocityFeedbackController> left {
    rmb::asLinear(
      (std::shared_ptr<rmb::AngularVelocityFeedbackController>)
      std::make_shared<rmb::SparkMaxVelocityController>(
        DriveConstants::leftLeader, DriveConstants::pidConfig, 
        DriveConstants::profileConfig, DriveConstants::feedbackConfig, 
        std::initializer_list<const rmb::SparkMaxVelocityController::MotorConfig>{DriveConstants::leftFollower}
      ),
      DriveConstants::wheelDiameter / 2.0_rad
    )
  };

  std::shared_ptr<rmb::LinearVelocityFeedbackController> right {
    rmb::asLinear(
      (std::shared_ptr<rmb::AngularVelocityFeedbackController>)
      std::make_shared<rmb::SparkMaxVelocityController>(
        DriveConstants::rightLeader, DriveConstants::pidConfig, 
        DriveConstants::profileConfig, DriveConstants::feedbackConfig, 
        std::initializer_list<const rmb::SparkMaxVelocityController::MotorConfig>{DriveConstants::rightFollower}
      ), 
      DriveConstants::wheelDiameter / 2.0_rad
    )
  };

  rmb::DifferentialDrive drive { 
    left, right, DriveConstants::kinematics 
  };

  rmb::DifferentialOdometry odometry { 
    left, right, 
    DriveConstants::kinematics, 
    std::make_shared<AHRS>(DriveConstants::gyroPort) 
  };
};
