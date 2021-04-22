# Command reference
This Is the command reference page.
## ChangeSpeed(_int newspeed_)
This changes the speed of both motors to the same value defined as _newspeed_. This function does not return any value.
## HaltMotors()
This function requires no perameters and will simpily set all forward/backward values to LOW
## Forward(), Backward(), Left(), Right()
None of the above functions require nor accept arguments. They will complete the task as named by the function.
## Swerve(_int offset%_)
This function requires 1 integer argument to work. It will adjust motor speeds to x% of the other. This is reversed when travelling backwards