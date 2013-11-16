# Tankdrive Teliop

## Design

Basic tankdrive.

## Controls

Controller 1 has the standard joystick to wheel mappings. Left joy maps to the left wheel; same for the right.

Button 4 (Y) on controller 1 is a toggle for Slow Mode. Slow Mode cuts all input from the driver's game controller in half, allowing fine motor movement.

## Features

"Slow mode" for fine motor movements. See the Controls section for details

## Planned features

Arm manipulation. Duh.

## Calculations used

## Generic arm movement, based on degrees

The arm's lowest position is 30 degrees, and the gear ratio is 1:27. You can use this formula for calculating the encoder counts needed to move the arm x degrees: f(x) = (x-30)*(1440/360)*(27/1).

Note that this number of degrees is absolute relative to the bar that the gears are mounted on. If you want relative degrees instead of absolute degrees, you can substitute 30 in the above formula for whatever number of degrees you're at, so that you get f(x, y) = (x-y)*(1440/360)*(27/1), where x is still the number of degrees you want to go up, and y is the absolute degree count that you're at right now.

### Bottom arm preset

This preset corresponds to when the pendulum is completely level. Measurements indicate that the arm needs to be 18" off the ground in order to successfully drop blocks while the pendulum is in this state. We measured the angle of the arm in this position to be 100 degrees. Therefore, the encoder counts end up being (100-30)*(1440/360)*(27/1) = 7560, assuming that you're in the bottommost position on the arm.

### Top arm preset

This preset corresponds to when the pendulum is completely in the air, as far as it can go. Measurements indicate that the arm needs to be 25" off the ground in order to successfully drop blocks in this state. We measured the angle of the arm in this position to be 130 degrees. Therefore, the number of encoder counts needed to get to this position are (130-30)*(1440/360)*(27/1). This assumes that you're in the bottommost position on the arm.
