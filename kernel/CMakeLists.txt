include_directories(include)
set(CMAKE_C_COMPILER ${NATIVE_GCC})
ENABLE_LANGUAGE(ASM-ATT)

FILE(GLOB PLATFORM_SRCS arch/${ARCH}/*.s arch/${ARCH}/*.c)
FILE(GLOB KERNEL_SRCS */*.c)
add_executable(Kernel ${PLATFORM_SRCS} ${KERNEL_SRCS} ${LIBC_SRCS})
set(CMAKE_C_FLAGS "-mno-red-zone -ffreestanding -Wall -Wextra -Wno-missing-field-initializers")
target_link_options(Kernel PUBLIC -nostdlib -lgcc)
