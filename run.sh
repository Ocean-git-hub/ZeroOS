#!/bin/sh

qemu-system-x86_64 -m 2G -smp 4 -drive if=pflash,format=raw,file=qemu/OVMF.fd -drive file=fat:rw:qemu/fs,format=raw
