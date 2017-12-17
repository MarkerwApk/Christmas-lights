#!/bin/bash 
#Włączenie UART4
echo ADAFRUIT-UART4 > /sys/devices/bone_capemgr.9/slots
chmod 777 /dev/ttyO4

#Ustawienie GPIO
#echo BB-GPIO > /sys/devices/bone_capemgr.9/slots

#Export dla Lampki Mikołaj
echo 45 > /sys/class/gpio/export
cd /sys/class/gpio/gpio45
echo out > direction
chmod 777 /sys/class/gpio/gpio45/value

#Export dla Lampki 
echo 44 > /sys/class/gpio/export
cd /sys/class/gpio/gpio44
echo out > direction
chmod 777 /sys/class/gpio/gpio44/value

#Export dla Lampki 
echo 26 > /sys/class/gpio/export
cd /sys/class/gpio/gpio26
echo out > direction
chmod 777 /sys/class/gpio/gpio26/value

#Export dla Lampki 
echo 47 > /sys/class/gpio/export
cd /sys/class/gpio/gpio47
echo out > direction
chmod 777 /sys/class/gpio/gpio47/value

#Export dla Lampki 
echo 46 > /sys/class/gpio/export
cd /sys/class/gpio/gpio46
echo out > direction
chmod 777 /sys/class/gpio/gpio46/value

#Export dla Lampki 
echo 27 > /sys/class/gpio/export
cd /sys/class/gpio/gpio27
echo out > direction
chmod 777 /sys/class/gpio/gpio27/value


/home/debian/bbb
/home/debian/main
