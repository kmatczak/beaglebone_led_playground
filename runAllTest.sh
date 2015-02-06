#!/bin/sh 

echo "=== TESTING IOCTL ==="
./test_ioctl

echo "=== TESTING SYSFS ==="

echo "TEST 1 blink=50ms"
echo "blink=50" > /sys/kernel/led_gpio_54/mode
cat /sys/kernel/led_gpio_54/mode 
echo "1" > /sys/kernel/led_gpio_54/control
sleep 5
echo "0" > /sys/kernel/led_gpio_54/control

echo "TEST 2 blink=300ms"
echo "blink=300" > /sys/kernel/led_gpio_54/mode
cat /sys/kernel/led_gpio_54/mode 
echo "1" > /sys/kernel/led_gpio_54/control
sleep 5
echo "0" > /sys/kernel/led_gpio_54/control

echo "TEST 3 timeout=3000ms"
echo "timeout=3000" > /sys/kernel/led_gpio_54/mode
cat /sys/kernel/led_gpio_54/mode 
echo "1" > /sys/kernel/led_gpio_54/control
sleep 5

echo "TEST 4 normal"
echo "normal" > /sys/kernel/led_gpio_54/mode
cat /sys/kernel/led_gpio_54/mode 
echo "1" > /sys/kernel/led_gpio_54/control
sleep 2
echo "0" > /sys/kernel/led_gpio_54/control







