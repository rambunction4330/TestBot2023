
#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/button/CommandPS4Controller.h>

#include "drivetrain/DriveSubsystem.h"

#include <rev/CANSparkMax.h>

class Robot : public frc::TimedRobot {
public:
  void RobotInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

private:
  DriveSubsystem drive;
  frc2::CommandPS4Controller controller{0};
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
