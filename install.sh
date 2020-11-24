#!/bin/sh

mkdir -p cmake-build-debug
cd cmake-build-debug
cmake ..
make
cd ../
sh deploy.sh
cp /usr/share/ovmf/OVMF.fd qemu/
