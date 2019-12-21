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
 - CLOCK = 15
 - LATCH = 18
 - DATA = 19

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
 - START = 7 presses  
 - SELECT = 8 presses  
 - N/A = 9 presses
 
 In the code folder there is another sketch labaled "SNES_Controller_Adapter_Remap_Autofire.ino" This is an experemental firmware that has the same button remapping system as the above version, but also adds auto fire capability as well. 
 
 To enter auto fire programming mode hold any 1 face button and START simultaniously for 3 seconds. 
 Once in auto fire programming mode press each button that you want to set as auto fire the number of times that corresponds to the desired speed in the list below.
 
  - ~30hz = 1 press
  - ~20hz = 2 presses
  - ~15hz = 3 presses
  - ~12hz = 4 presses
  - ~7.5hz = 5 presses
  - ~6hz = 6 presses

Button mapping and auto fire settings are saved in the EEPROM so they will persist after power cycling the AVR.

# Brook Fix #

The Brook Retro Board has been extremely difficult to get working properly with this code. After a large amount of tweaking, Retro Boards finally work almost completely bug free. There is still one lingering issue that I am trying to solve. Sometimes when holding multiple buttons for extended periods of time, the Retro Board will drop the held inputs for 1 cycle, which results in the button releasing for 1/2 of a frame. This could cause you to, for example, release a charged shot unintentionally in a shmup.

As a stopgap solution I have implemented the "Brook Fix". When the Brook Fix is enabled, every time a button is released the code waits one extra cycle to make sure the button is actually released before setting the button as released on the output. The resulting fix stops random button releases, but comes with the penalty of adding 16ms of lag on button releases. Button presses are not affected by this lag. 

 - To turn the Brook Fix on press and hold any 5 buttons (excluding select and d-pad) + START for 3 seconds.
 - To turn the Brook Fix off press and hold any 6 buttons (excluding select and d-pad) + START for 3 seconds.
 
 The Brook Fix setting is saved in the EEPROM so you don't have to set it every time you use it.
 
 # HAS Mode #
 
 The HAS (Home Arcade System) supergun already has built in button remapping and rapid fire functionality. It is programmed through the same process as these adapters, so to eleminate conflicts when using one of my adapters on a HAS supergun, I have implemented a special HAS mode that can be enabled at startup, which disables the button remapping and rapid fire functionality of the adapter, leaving those functions to the HAS. The buttonmap and rapid fire settings will be set to default when HAS mode is enabled, but previous button remapping and rapid fire settings will return once HAS mode is disabled again.
 
  **To enable/disable HAS mode, simply hold the A button while powering the adapter on.**
  
  When HAS mode is disabled, the status LED will blink rapidly for 1 second during power up. When HAS mode is enabled, the status LED will light up solid for 1 second during power up. 
  
  Has mode settings will be saved in the EEPROM and will persist after power cycles. 

# Custom PCB Info.

I have designed several prototype PCBs for this project. Currently they are available as Multi Console to DB15 adapters. They use the same DB15 pinout as Undamned's DB15 USB Decoders. You can order the most current version from <a href="https://oshpark.com/shared_projects/X40sm7os">Oshpark</a>
