// you can also set the led to a non-spark max motor and use <frc/AddressableLED.h>, but it's more convenient using the rev robotics docs.
#include "led/ledSubsystem.h"

#include <iostream>

#include <frc2/command/InstantCommand.h>

void ledSubsystem::SetledTo(){ 
    UnaddressableLED.Set(ledCounter/100.0); 
}

void ledSubsystem::setledToThis(double number) {
    UnaddressableLED.Set(number); 
}

void ledSubsystem::ledIncrease() { 
    ledCounter <= 99 ? ledCounter += 2 : ledCounter = -99;
}

frc2::CommandPtr ledSubsystem::setledToThisCommand(double numbere) { 
    return frc2::CommandPtr(frc2::InstantCommand([&]() { setledToThis(numbere); }, {this}));
}

frc2::CommandPtr ledSubsystem::ledIncreaseCommand() { 
    return frc2::CommandPtr(frc2::InstantCommand([&]() { ledIncrease(); }, {this}));
}

frc2::CommandPtr ledSubsystem::SetledToCommand() { 
    return frc2::CommandPtr(frc2::InstantCommand([&]() { SetledTo(); }, {this}));
}
