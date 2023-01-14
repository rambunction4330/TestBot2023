// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/button/CommandJoystick.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/button/CommandPS4Controller.h>

#include <rmb/motorcontrol/feedback/LinearVelocityFeedbackController.h>
#include <rmb/motorcontrol/sparkmax/SparkMaxVelocityController.h>
#include <rmb/drive/DifferentialDrive.h>

#include <frc2/command/SubsystemBase.h>

namespace DriveConstants {

  const rmb::SparkMaxVelocityController::MotorConfig leftLeader {
    21, rev::CANSparkMax::MotorType::kBrushless, true
  };

  const rmb::SparkMaxVelocityController::MotorConfig leftFollower {
    22, rev::CANSparkMax::MotorType::kBrushless, false
  };

  const rmb::SparkMaxVelocityController::MotorConfig rightLeader {
    11, rev::CANSparkMax::MotorType::kBrushless, false
  };

  const rmb::SparkMaxVelocityController::MotorConfig rightFollower {
    12, rev::CANSparkMax::MotorType::kBrushless, false
  };

  const rmb::SparkMaxVelocityController::PIDConfig pidConfig {
    0.0 /*  <- P */ , 0.0 /* <- I */, 0.0 /* <- D */,
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

  const rmb::SimpleFeedforward<units::radians> feedforward { 
    rmb::SimpleFeedforward<units::radians>::Ks_t{0.0} /* <- Ks */, 
    rmb::SimpleFeedforward<units::radians>::Kv_t{0.0} /* <- Kv */, 
    rmb::SimpleFeedforward<units::radians>::Ka_t{0.0} /* <- Ka */ 
  };

  static frc::DifferentialDriveKinematics kinematics{ 27.75_in /* <- track width */};

  const units::meter_t wheelDiameter = 7_in;
}

class DriveSubsystem : public frc2::SubsystemBase {
 public:
  DriveSubsystem() = default;

  void arcadeDrive(double xSpeed, double zRotation);
  void arcadeDrive(frc2::CommandJoystick& stick);
  void arcadeDrive(frc2::CommandXboxController& controller);
  void arcadeDrive(frc2::CommandPS4Controller& controller);

  void curvatureDrive(double xSpeed, double zRotation, bool turnInPlace);
  void curvatureDrive(frc2::CommandJoystick& stick);
  void curvatureDrive(frc2::CommandXboxController& controller);
  void curvatureDrive(frc2::CommandPS4Controller& controller);

  void tankDrive(double leftSpeed, double rightSpeed);
  void tankDrive(frc2::CommandXboxController& controller);
  void tankDrive(frc2::CommandPS4Controller& controller);

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
        DriveConstants::feedforward, DriveConstants::profileConfig, 
        DriveConstants::feedbackConfig, 
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
        DriveConstants::feedforward, DriveConstants::profileConfig, 
        DriveConstants::feedbackConfig, 
        std::initializer_list<const rmb::SparkMaxVelocityController::MotorConfig>{DriveConstants::rightFollower}
      ), 
      DriveConstants::wheelDiameter / 2.0_rad
    )
  };

  rmb::DifferentialDrive drive{ left, right, DriveConstants::kinematics };
};