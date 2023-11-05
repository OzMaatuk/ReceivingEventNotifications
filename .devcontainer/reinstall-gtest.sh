#!/usr/bin/env bash
set -e

cd /workspaces
sudo git clone https://github.com/google/googletest.git
cd googletest
sudo cmake CMakeLists.txt
sudo make
sudo cp /workspaces/googletest/lib/*.a /usr/lib