# Zephyr counter driver interface with stm32 microcontrollers
This example is add-on to the [simple zephyr toggleled custom driver](https://github.com/UsmanAliButt/zephyr-simple-driver-toggleled)
<br>zephyr official documents regarding stm32 does not list support for counters and timers. But in device tree sources and drivers folder, timers and counters support is present with minimal and ambigious functionality.
<br><br>In st,stm32-timers.yaml file counter property is present. Consult for more.
<br>Counter functions are present in counter_II_stm32_timer.c driver file. 
<br>For device tree counter support/activation st,stm32-counter.yaml empty file is required. 
<br> To enable counter include particular CONFIG in prj.conf file.

<code>CONFIG_COUNTER=y
CONFIG_COUNTER_TIMER_STM32=y
</code>

<br>Pass counter node in overlay file and activate timer as well. In this case timer-6, size is 16-bit.
Driver functions are called from main. Output can be seen in the picture below. Main source file is present in app/src folder.

<br><br>Output of main.c instruction below can be viewed on UART serial terminal. I used PUTTY baudrate is set 115200 and COM port can be verified from Device Manager. 
<code>printk("Device is %p, name is %s\n", dev, dev->name);</code>

![Output on UART](Untitled.png)

<h3>Download driver with west and initialize workspace</h3>
<code># Download main branch
west init -m https://github.com/UsmanAliButt/ZephyrRTOS.git --mr main ZephyrRTOS
# Zephyr local repository needs to be updated to dowload zephyr support and dependent modules 
# See west.yml in project for proper dependencies
cd ZephyrRTOS/zephyr counter with stm32
west update</code>
