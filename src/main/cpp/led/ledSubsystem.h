
#pragma once

#include <frc2/command/CommandPtr.h>

#include <frc/Timer.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/AddressableLED.h>

#include <frc2/command/SubsystemBase.h>

class ledSubsystem : public frc2::SubsystemBase {
    public: 
    
    ledSubsystem() = default;

    void SetledTo();
    void ledIncrease();
    void setledToThis(double number);
    frc2::CommandPtr ledIncreaseCommand();
    frc2::CommandPtr SetledToCommand();
    frc2::CommandPtr setledToThisCommand(double numbere);
    
    // robotcontainer needs access to these variables
    const double red = -0.25;
    const double blue = -0.23;
    const double yellow = 0.69;
    const double white = -0.05;

    private: 
    double ledCounter = -99.0;
    frc::Spark UnaddressableLED {0}; 
};
