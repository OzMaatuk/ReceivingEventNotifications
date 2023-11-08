#!/usr/bin/env bash
set -e

apt-get update && apt-get upgrade -y && apt-get autoremove && apt-get autoclean

# install booststacktrace
sudo apt --assume-yes install libboost-stacktrace-dev

# install glog
sudo git clone https://github.com/google/glog.git
cd glog
sudo cmake -S . -B build -G "Unix Makefiles"
sudo cmake --build build
sudo cmake --build build --target test
sudo cmake --build build --target install
cd ..

# install gtest
sudo git clone https://github.com/google/googletest.git
cd googletest
sudo cmake CMakeLists.txt
sudo make
sudo cp lib/*.a /usr/lib
cd ..

# install linux monitoring tool

# install jsoncpp
sudo apt-get -y install libjsoncpp-dev