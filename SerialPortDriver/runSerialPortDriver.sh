#! /bin/bash

sudo cmake -S . -B build/
sudo cmake --build build/
sudo ./bin/SerialPortDriver
