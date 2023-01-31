/*
Author: Usman Ali Butt usa_butt@hotmail.com
Dated : 25-January-2023
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
	uint32_t /*ticks,*/val,sec=500; 
	int ret=0;
	bool turnaround=true;
	
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
	printk(up ? "Counter Counting=true\n" : "Counter Counting=false\n");
	
	//See pending interrupts
	ret	=	counter_get_pending_int(counter);
	printk(ret?"Pending interrupt\n":"No pending interrupt\n");
	
	
	while(1){
		alter(sec);			
		//Initial toggle led set to 0.5 seconds (500) 
		//819 microseconds taken for timer(16-bit) overflow/update at 80MHz
		//1221 * 819 micro seconds = 0.99 seconds
		//after 1 second decrease toogle time 50 points or 20% in steps
		//eventually at 0 rollup to 0.5 seconds with 20% increase in steps
		/**In simple words: Update toggle time after every second. Where
		toggle time range is between 0 - 0.5 seconds*/ 
		if(machinecycles>=1221){
			machinecycles=0;
			
			if (sec==0 || !turnaround){
				turnaround=false;
				sec=sec+50;
				}
			if (sec==500 || turnaround){
					turnaround=true;
					sec=sec-50;
				}
		}
		
		/**
		printk("Machine cycles=%d\n",machinecycles);
		printk("Sec=%d\n",sec);
		*/
		
		/**
		ret	=	counter_get_value(counter, &ticks); //Get counter value
	
		if(ret!=0){
			printk("Problem in fetching counter value\n");
		}
		else
			printk("Current counter Value %u\n", ticks);
		*/

	}
	
}