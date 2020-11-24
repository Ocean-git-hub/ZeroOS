#!/bin/sh

mkdir -p qemu/fs/EFI/BOOT
cp cmake-build-debug/boot_loader/uefi/BootLoader.exe qemu/fs/EFI/BOOT/BOOTX64.EFI
cp cmake-build-debug/kernel/Kernel qemu/fs/kernel
