#!/usr/bin/env bash
set -e

cd /workspaces
sudo git clone https://github.com/google/glog.git
cd glog
sudo cmake -S . -B build -G "Unix Makefiles"
sudo cmake --build build
sudo cmake --build build --target test
sudo cmake --build build --target install