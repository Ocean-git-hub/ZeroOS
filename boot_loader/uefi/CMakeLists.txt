include_directories(include)
set(CMAKE_C_COMPILER ${MINGW32_64_GCC})

FILE(GLOB UEFI_SRCS *.c lib/*.c)
add_executable(BootLoader ${UEFI_SRCS})
target_compile_options(BootLoader PUBLIC -mno-red-zone -ffreestanding -Wall -Wextra -Wno-missing-field-initializers)
target_link_options(BootLoader PUBLIC -e efi_main -nostdlib -Wl,--subsystem,10)
