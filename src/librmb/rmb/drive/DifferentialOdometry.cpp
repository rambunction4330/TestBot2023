// #include "rmb/drive/DifferentialOdometry.h"

// #include <frc/kinematics/DifferentialDriveKinematics.h>

// namespace rmb {

// DifferentialOdometry::DifferentialOdometry(
//   std::shared_ptr<LinearEncoder> left, std::shared_ptr<LinearEncoder> right,
//   frc::DifferentialDriveKinematics& kinematics, std::shared_ptr<frc::Gyro> gyroscope, 
//   std::shared_ptr<nt::NetworkTable> visionTable, const frc::Pose2d& initalPose) : 
//   leftEncoder(left), rightEncoder(right), gyro(gyroscope), 
//   poseEstimator(kinematics, gyro->GetRotation2d(), leftEncoder->getPosition(), 
//                 rightEncoder->getPosition(), initalPose) {

// }


// } // namespace rmb