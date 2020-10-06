include_directories(include)
set(CMAKE_C_COMPILER ${MINGW32_64_GCC})

FILE(GLOB UEFI_SRCS *.c lib/*.c)
add_executable(BootLoader ${UEFI_SRCS} ${LIBC_SRCS})
target_compile_options(BootLoader PUBLIC -O2 -fpic -mno-red-zone -ffreestanding -fno-stack-protector -fno-stack-check
        -maccumulate-outgoing-args -Wall -Wextra -Wno-missing-field-initializers)
target_link_options(BootLoader PUBLIC -nostdlib -Wl,-eefi_main,-s)

# Must be IMAGE_OPTIONAL_HEADER.Subsystem = IMAGE_SUBSYSTEM_EFI_APPLICATION (10) in PE32(+)
target_link_options(BootLoader PUBLIC -Wl,--subsystem,10)
