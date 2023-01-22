//Author: Usman Ali Butt usa_butt@hotmail.com
//Dated : 6-october-2022

/*
DT_DRV_COMPAT macro is matching with the compatible
property of device tree. It helps in device instanciation. 
*/
#define DT_DRV_COMPAT toggle

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <toggledriver.h>

/* 
Log module can be removed. Here its used(sole in toggledriver.c) just for 
logging error, if device is not initialzed correctly in toggle_init() function. 

Printk is not helpful in toggle_init(). Since its called during device defination.
At that time UART is not ready to take and print-> printk stream
*/

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(toggledriver, CONFIG_TOGGLEDRIVER_LOG_LEVEL);

/*
Config readonly part of our device. Gpio struct 'led' is 
initialized auto by DEVICE_DT_INST_DEFINE function. 

led struct is auto assigned the value 
switch-gpios   	=       <&gpiob 3 GPIO_ACTIVE_HIGH>;
taken from device tree overlay. 
*/ 
struct toggle_config {
	struct gpio_dt_spec led;
};

/*
Data part of our driver. Empty in this case.
*/
struct toggle_data {
};

/*
Global gpio device structure. Initialized in toggle_init().
Used in alter() function.
*/
const struct gpio_dt_spec *toggle;

/*
Toggle led at given milliseconds overflow.
1000	=	1 second
*/
void alter(int milliseconds){
	gpio_pin_toggle_dt(toggle);
    k_msleep(milliseconds);
}

/*
toggle_init() initializes the global gpio struct with 
new device driver gpio configurations.
Configures the led gpio pin as toggle.

Checks if the device is created and present.
*/
static int toggle_init(const struct device *dev)
{
	const struct toggle_config *config = dev->config;
	
	toggle = dev->config;
	gpio_pin_configure_dt(toggle, GPIO_OUTPUT_ACTIVE);
	
	if (!device_is_ready(config->led.port)) {
		LOG_ERR("\n Led-Driver not ready \n");
		return -ENODEV;
	}
	
	return 0;
}

/*
Define macro creates new device. You must have appropriate device node
defined in the device tree, better using the overlay file(same ar ours).

Only the config struct is assigned a GPIO instance. Data struct left void.
we kept it untouched. You can also remove it and pass NULL as parameter 
in DEVICE_DT_INST_DEFINE.

Power management and api parameters are passed NULL. since we are not
dealing with power and api yet.    
*/
#define TOGGLE_DEFINE(inst)                                     			\
	static struct toggle_data toggle_data_##inst;							\
	static const struct toggle_config toggle_config_##inst = {      		\
		.led	=	GPIO_DT_SPEC_INST_GET_OR(inst, switch_gpios, {}),		\
	};                                                             			\
																			\
	DEVICE_DT_INST_DEFINE(inst, 											\
							toggle_init,									\
							NULL,											\
							&toggle_data_##inst,   							\
							&toggle_config_##inst,							\
							APPLICATION,          	   						\
							CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,			\
							NULL);			

DT_INST_FOREACH_STATUS_OKAY(TOGGLE_DEFINE)
