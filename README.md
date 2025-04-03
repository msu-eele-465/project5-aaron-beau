# EELE 465 project 5
## Reading an Analog Temperature Sensor with ADC

### Project Description
    In this project, the LM19 analog temperature sensor was used to provide an analog voltage to the Controller (MSP4302355).
    The overall system started in a locked state and could be opened and ready for user input with the code "6969".  The system
    had 3 user input modes, one would allow the user to set the window size for the moving average of the sampled ADC values.  The second
    allowed the user to choose a pattern on the LED bar, and the third was a mode that required no user input. To find the temperature as a moving
    average, the digital number provided by the ADC was sampled every 0.5s which was triggered off of Timer_B.  This sampled value would be stored in an
    array and more samples would continue to be added to the array until the number of user defined samples were met.  These values were then summed and 
    divided by the window size to find the average.  This value was then converted to celsius by multiplying by a conversion factor that was determined by comparing the ADC value to room temperature.  Once this was complete the temperature was sent over I2C to the slave and displayed on the LCD.  For every sample that was taken from this point on, the average would be recalculated to make it a true moving average.



