# Command reference
This Is the command reference page.
## ChangeSpeed(_int newspeed_)
This changes the speed of both motors to the same value defined as _newspeed_. This function does not return any value.
## HaltMotors()
This function requires no perameters and will simpily set all forward/backward values to LOW
## Forward(), Backward(), Left(), Right()
None of the above functions require nor accept arguments. They will complete the task as named by the function.
## Swerve(_int offset%_)
This function requires 1 integer argument to work. It will adjust motor speeds to x% of the other. This is reversed when travelling backwards. Negative integers will make the bot veer to the left (when going forward) otherwise it will veer right. To reset motor speeds to the highest value, call the function with the parameter 0.
## IRSense()
This will read the data from 4 infared sensors. It will return an array of values in the order: BackRight, FrontRight, FrontLeft, BackLeft
## CheckIRVals(boolean adjust, boolean UseOldValues)
Calling this function with the first parameter set to false will return if any one of the sensors is HIGH. Otherwise this will be done automatically and compensated for by adjusting the position. The second parameter determines whether to use old values or not. If set to false, this shall check all the Infared sensors again, otherwise it will use previous values.
## UltraSonic()
This requires no parameters and will simply return the result of the untrasonic scan in mm.
