cmake_minimum_required(VERSION 3.17)
project(ZeroOS C)

set(CMAKE_C_STANDARD 99)
set(ARCH x64)
set(MINGW32_64_GCC /usr/bin/x86_64-w64-mingw32-gcc)
set(NATIVE_GCC /usr/bin/gcc)

add_subdirectory(boot_loader)
add_subdirectory(kernel)
