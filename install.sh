#! /bin/bash

# Create installations file
sudo mkdir installations/
cd installations/

# Boost libraries installation for C++
sudo apt update -y && sudo apt upgrade -y
sudo apt-get install -y build-essential g++ python3-dev autotools-dev libicu-dev libbz2-dev libboost-all-dev
sudo wget https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.gz
sudo tar xvf boost_1_80_0.tar.gz
cd boost_1_80_0
sudo ./bootstrap.sh --prefix=/usr/
sudo ./b2 install
cd ..

# Paho-Mqtt-C installation
sudo apt-get install -y libssl-dev
sudo apt-get install -y build-essential gcc make cmake cmake-gui cmake-curses-gui
sudo apt-get install -y doxygen graphviz
sudo git clone https://github.com/eclipse/paho.mqtt.c.git
cd paho.mqtt.c
git checkout v1.3.8
sudo cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
sudo cmake --build build/ --target install
sudo ldconfig
cd ..

# Paho-Mqtt-Cpp installation
sudo git clone https://github.com/eclipse/paho.mqtt.cpp
cd paho.mqtt.cpp
sudo cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON \
    -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
sudo cmake --build build/ --target install
sudo ldconfig
cd ..

# Delete installations file
cd ..
sudo rm -rf installation/

# Installation python GUI app dependecies
cd GUI/
sudo apt install -y python3-pip
sudo pip3 install -r requirements.txt