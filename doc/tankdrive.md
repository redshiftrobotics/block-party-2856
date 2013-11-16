# Tankdrive Teliop

## Design

Basic tankdrive.

## Controls

Controller 1 has the standard joystick to wheel mappings. Left joy maps to the left wheel; same for the right.

Button 4 (Y) is a toggle for Slow Mode. Slow Mode cuts all input from the driver's game controller in half, allowing fine motor movement.

## Features

"Slow mode" for fine motor movements. See the Controls section for details

## Planned features

Arm manipulation. Duh.

## Calculations used

### Bottom arm preset

This preset corresponds to when the pendulum is completely level. Measurements indicate that the arm needs to be 18" off the ground in order to successfully drop blocks. We measured the angle of the arm in this position to be 100 degrees. The arm's lowest position is 30 degrees, and the gear ratio is 1:27. TODO encoder calculations

### Top arm preset

This preset corresponds to when the pendulum is completely up as far as it can go. Measurements indicate that the arm needs to be 25" off the ground in order to successfully drop blocks. We measured the angle of the arm in this position to be 130 degrees. The arm's lowest position is 30 degrees, and the gear ratio is 1:27. TODO encoder calculations

