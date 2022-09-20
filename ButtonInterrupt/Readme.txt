Zephyr button support is added to nucleo l432kc board. See the ButtonUsman example in same repo.
Overlay(button.overlay) file is present in blinky folder.
Generated device tree is present in ButtonUsman\build\zephyr\zephyr.dts
nucleo_l432kc board pin D12(PB_4) or Port-b pin 4 is connected with push button.
Build, compiling and flashing commands are present in CompilingCommands.txt file. 
You must set the correct paths. My advice is to place the ButtonUsman folder in \zephyrproject\zephyr  

Interrupt callback static struct gpio_callback button_callback;
Interrupt handler  void button_pressed(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins);

Initialize and register callback
	gpio_init_callback(&button_callback,button_pressed,BIT(button.pin));
	gpio_add_callback(button.port,&button_callback);

printk() function in handler prints the message on serial console.
Open example, PuTTY serial port and set Baud rate to 115200 for debugging.