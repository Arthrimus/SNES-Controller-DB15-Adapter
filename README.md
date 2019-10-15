# SNES Controller to DB-15 Adapter.

This is an Arduino sketch converting SNES controller inputs to discrete outputs. I desinged it for Arcade Supergun use but it could be adapted for use in many other control applications that require discrete outputs.

# Instructions

The upload the .ino file to an Arduino Uno or similar compatible device and connect the I/O pins according to the layout described in the .ino file. If you wish to remap the buttons you can modify the pin selections in the file to suit your needs. 

# Pinout (Arduino pin labels) 

  These values are hard coded and cannot be easily changed. This is because the code uses direct port maniplulation to set the button outputs to open drain when not pressed. This is a safety feature.

**Button Outputs**
  - UP    = 1
  - SELECT = 2
  - DOWN  = 4
  - LEFT  = 5
  - RIGHT = 6
  - X     = 7
  - Y     = 8
  - L     = 9
  - A     = 10
  - START = 11  
  - B     = 13
  - R     = 12

**SNES Pins**
 - DATA_CLOCK = 15
 - DATA_LATCH = 18
 - DATA_SERIAL = 19

# BUTTON REMAPPING AND AUTOFIRE

In the code folder there is an arduino sketch labeled "SNES_Controller_Adapter_Remap.ino" This firmware has full fledged on the fly remapping of A,B,R,X,Y and L. 

To enter button remapping mode hold any 2 face buttons and START simultaniously for 3 seconds.
Once in remapping mode press each button the corresponding number of times to achive the desired output based on the list below.

 - X = 1 press
 - Y = 2 presses
 - L = 3 presses
 - A = 4 presses
 - B = 5 presses
 - R = 6 presses
 - N/A = 7 presses
 
 In the code folder there is another sketch labaled "SNES_Controller_Adapter_Remap_Autofire.ino" This is an experemental firmware that has the same button remapping system as the above version, but also adds auto fire capability as well. 
 
 To enter auto fire programming mode hold any 1 face button and START simultaniously for 3 seconds. 
 Once in auto fire programming mode press each button that you want to set as auto fire the number of times that corresponds to the desired speed in the list below.
 
  - ~30hz = 1 press
  - ~20hz = 2 presses
  - ~15hz = 3 presses
  - ~12hz = 4 presses
  - ~7.5hz = 5 presses
  - ~6hz = 6 presses

# Custom PCB Info.

I have designed several prototype PCBs for this project. Currently they are available as Multi Console to DB15 adapters. They use the same DB15 pinout as Undamned's DB15 USB Decoders. You can order the most current version from <a href="https://oshpark.com/shared_projects/X40sm7os">Oshpark</a>
