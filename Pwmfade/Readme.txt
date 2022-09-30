Stm32 nucleo_l432kc board has an onboard led. Led is connected to D13 or PB3 port of nucleo_l432kc controller.
By default nucleo_l432kc does not work with zephyr PWM sample example. We need to make some modifications. 

In default device tree of nucleo_l432kc timer2 has a PWM channel attached to it and is activated. By default its 
working with Timer2 channel-1 PA0 port. Where as onboard led is connected to Timer2 channel-2 PB3. We must activate 
this port and channel. Also to use default zephyr PWM drivers we must specify a new node in our device tree which
refers to PWM node and initializes the PWM <node(Timer2-PWM) Channel(2) PWM-period PWM-pin-state >. All the settings
are done in overlay file.    

Overlay(Pwml432kc.overlay) file is present in Pwmfade folder.
Generated device tree is present in Pwmfade\build\zephyr\zephyr.dts
nucleo_l432kc board pin D13(PB4) or Port-b pin-3 is by default connected with on board user led..
Build, compiling and flashing commands are present in buildommands.txt file. 
You must set the correct paths. My advice is to place the Pwmfade folder in \zephyrproject\zephyr.  
