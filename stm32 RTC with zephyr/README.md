# Zephyr stm32 RTC how to
Adding a support to zephyr project. Driver development is not well documented and explained in zephyr project. So i decided to create a simple out of tree driver and make is public.
<br><br>Just one GPIO pin is utilized here. Tested on physical hardware STM32 nucleol432kc board. GPIO pin-3 of module has default led connected to it.


<br><br>Output of main.c instruction below can be viewed on UART serial terminal. I used PUTTY baudrate is set 115200 and COM port can be verified from Device Manager. 

![Output on UART](Untitled.png)

<h2>Folders</h2>
<ol>
  <li>app     - Contains sources and overlay file</li>
</ol>

<h3>Download driver with west and initialize workspace</h3>
<code># Download main branch
west init -m https://github.com/UsmanAliButt/zephyr-simple-driver-toggleled.git --mr main zephyr-simple-driver-toggleled
# Zephyr local repository needs to be updated to dowload zephyr support 
# See west.yml in project for proper dependencies
cd zephyr-simple-driver-toggleled
west update</code>

<br>update will look in west.yml file what to do? It simply contains information regarding packages which needs to be downloaded
and necessary for our project. An out of tree project will be created. If you dosent like out of tree project, simply add the main.c 
file in your zephyr tree and update the counter_ll_stm32_rtc.c file. This way space in your machine can be saved.  
<br>To enable RTC driver include in prj.conf 
<code>
	CONFIG_COUNTER=y
	CONFIG_COUNTER_RTC_STM32=y
</code> 
