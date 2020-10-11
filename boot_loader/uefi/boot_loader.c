#include <efi/efi.h>
#include <efilib.h>

#define KERNEL_FILE_NAME L"kernel"

typedef struct {
    uint64_t bssStart;
    uint64_t bssEnd;
    uint64_t textStart;
} KernelHeader;

typedef struct {
    EFI_FRAME_BUFFER_INFO frameBufferInfo;
} BootParameter;

EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table) {
    efi_lib_initialize(system_table);
    efi_set_largest_screen_mode();
    efi_clear_screen();

    EFI_TIME time = efi_get_datetime();
    efi_printf(L"ZeroOS Boot Loader [FirmwareVendor: %s(%s)] [%u/%u/%u %02u:%02u]\r\n",
               efi_get_firmware_vendor(), efi_get_uefi_version(),
               time.Year, time.Month, time.Day, time.Hour, time.Minute);

    EFI_FILE_INFO *kernel_info = efi_get_file_info(KERNEL_FILE_NAME);
    uint64_t kernel_size = kernel_info->FileSize;
    efi_printf(L"KernelSize: %luB\r\n", kernel_size);
    efi_free_pool(kernel_info);

    uint64_t kernel_start_address = efi_get_free_page_address(kernel_size);
    efi_allocate_pages((kernel_size + 4095) / 4096, &kernel_start_address);
    efi_printf(L"kernelStart: 0x%lx\r\n", kernel_start_address);
    efi_read_file_to_address(KERNEL_FILE_NAME, kernel_start_address);

    KernelHeader *kernel_header = (KernelHeader *) kernel_start_address;
    efi_set_memory((void *) (kernel_start_address + kernel_header->bssStart),
                   kernel_header->bssEnd - kernel_header->bssStart, 0);
    uint64_t stack_pointer = kernel_start_address + kernel_header->bssEnd;
    efi_printf(L"stackPointer: 0x%016lx\r\n", stack_pointer);

    BootParameter bootParameter = {.frameBufferInfo=efi_get_frame_buffer_info()};

    EFI_MEMORY_MAP memoryMap;
    efi_exit_boot_services(&memoryMap, image_handle);

    __asm__ volatile ("mov %0, %%rsp\r\n"
                      "mov %1, %%rdi\r\n"
                      "jmp *%2\r\n"
    ::"r"(stack_pointer), "r"(&bootParameter), "r"(&kernel_header->textStart));

    efi_get_input_key();
    efi_shutdown();
    return EFI_SUCCESS;
}
