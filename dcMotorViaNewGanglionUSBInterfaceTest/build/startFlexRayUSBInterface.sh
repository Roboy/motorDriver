#!/bin/bash
# start the FlexRay USB interface and makes sure the correct driver for the FTDI USB interface are loaded.


echo "Starting FlexRay USB test interface "
sudo rmmod ftdi_sio
sudo rmmod usbserial
sudo ./flexRayUSBInterfaceTest

