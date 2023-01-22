#include <zephyr/device.h>
#include <zephyr/toolchain.h>

/* alter() here is providing the 
driver with milliseconds after 
which led needs to be toggled */

void alter(int milliseconds);