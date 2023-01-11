#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/PS4Controller.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

#include <rev/CANSparkMax.h>

class Robot : public frc::TimedRobot {
public:
  void RobotInit() override;
  void TeleopPeriodic() override;

private:
  // left side
  rev::CANSparkMax left{11, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax leftFollow{12, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax right{21, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax rightFollow{22, rev::CANSparkMax::MotorType::kBrushless};

  // drive
  frc::DifferentialDrive drive{left, right};

  // controller
  frc::PS4Controller controller{0};
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
