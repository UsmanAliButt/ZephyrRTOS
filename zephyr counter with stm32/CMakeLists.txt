#SPDX-License-Identifier: Apache-2.0
#pick and compile headers from include directory
#traverse drivers directory for sources and Kconfig compilation
zephyr_include_directories(include)
add_subdirectory(drivers)