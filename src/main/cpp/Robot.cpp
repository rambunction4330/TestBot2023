#include "Robot.h"

#include <iostream>

void Robot::RobotInit() {}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic()  {} 
void Robot::TeleopExit() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic()  {} 
void Robot::AutonomousExit()  {} 

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
void Robot::TestExit() {}