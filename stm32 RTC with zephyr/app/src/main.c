/*
Author: Usman Ali Butt usa_butt@hotmail.com
Dated : 25-January-2023
*/
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/counter.h>

/*
Get device from node label. See toggle.overlay file and zephyr.dts(after compilation). 
Compiled files contains full device tree.
*/
static const struct device *realTC = DEVICE_DT_GET(DT_NODELABEL(rtc));

void main(void){
	uint32_t ticks; 
	int ret=0;
	
	if (!device_is_ready(realTC)) {		//Check if RTC is created and ready
		printk("counter not ready");
		return;
	}
	
	ret	= counter_start(realTC);		//start RTC
		if(ret<0){
			return;
		}
	
	while(1){	
		k_msleep(1000);
		
		//Get updated seconds 
		ret	=	counter_get_value(realTC, &ticks); 
		
		//date time updated in counter_ll_stm32_rtc.c
		printk("weekday/month/year hour/minute/second \n");
		
		if(ret!=0){
			printk("Problem in fetching RTC value\n");
		}
		else
			printk("Seconds passed until start of RTC %u\n", ticks);

	}
	
}