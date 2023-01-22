/*
Author: Usman Ali Butt usa_butt@hotmail.com
Dated : 20-January-2023
*/
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <toggledriver.h>
#include <zephyr/drivers/counter.h>

/*
Get device from node label. See toggle.overlay file. Compiled
files contains full device tree.
*/
static const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(drivertoggle));
static const struct device *counter = DEVICE_DT_GET(DT_NODELABEL(count));

void main(void){
	uint32_t ticks,val,sec=500;
	int ret=0;
	
	if (!device_is_ready(dev)) {		//Check if device is created and ready
		printk("Driver not ready");
		return;
	}
	
	if (!device_is_ready(counter)) {		//Check if device is created and ready
		printk("counter not ready");
		return;
	}
	
	ret	= counter_start(counter);
	if(ret<0){
		return;
	}
	
	//Print device name and object instance address
	printk("Device is %p, name is %s\n", dev, dev->name);
		
	//Get top value of counter since 16-bit so 65535	
	val	=	counter_get_top_value(counter);
	printk("Top Value %u\n", val);
	
	//Get counter frequency
	val	=	counter_get_frequency(counter);
	printk("Frequency %u\n", val);
	
	//Convert ticks to microseconds
	val	=	counter_ticks_to_us(counter,65535);
	printk("Microseconds %u\n", val);
	
	//Counter counting
	bool up	=	counter_is_counting_up(counter);
	printk(up ? "true\n" : "false\n");
		
	while(1){
		alter(sec);			//Initial alter led after every 0.5 seconds
							//afterwards according to counter 
		
		//Get counter value
		ret	=	counter_get_value(counter, &ticks);
	
		if(ret!=0){
			printk("Problem in fetching counter value\n");
		}
		else
			printk("Current Value %u\n", ticks);
		
		

	}
	
}