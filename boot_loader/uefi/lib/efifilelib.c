#include <efifilelib.h>

#include <efi/efi.h>
#include <efiprotocol.h>
#include <efiutils.h>
#include <efimemory.h>

#define MAX_FILE_NAME_SIZE 255

void get_root_file_protocol(EFI_FILE_PROTOCOL **root) {
    efi_check_error(simple_file_system_protocol->
            EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME(simple_file_system_protocol, root), L"OpenVolume");
}

EFI_FILE_INFO *efi_get_file_info(CHAR16 *file_name) {
    EFI_FILE_PROTOCOL *root;
    get_root_file_protocol(&root);

    EFI_FILE_PROTOCOL *file_protocol;
    efi_check_error(root->EFI_FILE_OPEN(root, &file_protocol, file_name, EFI_FILE_MODE_READ, 0),
                    L"read_file_to_address");

    EFI_GUID file_info_guid = EFI_FILE_INFO_ID;
    UINTN buffer_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * MAX_FILE_NAME_SIZE;
    EFI_FILE_INFO *file_info;
    efi_allocate_pool(buffer_size, (void **) &file_info);
    efi_check_error(file_protocol->
            EFI_FILE_GET_INFO(file_protocol, &file_info_guid, &buffer_size, file_info), L"FileGetInfo");

    root->EFI_FILE_CLOSE(root);
    file_protocol->EFI_FILE_CLOSE(file_protocol);

    return file_info;
}

void read_file_to_address(CHAR16 *file_name, uint64_t address) {
    EFI_FILE_PROTOCOL *root;
    get_root_file_protocol(&root);
    EFI_FILE_PROTOCOL *file;
    efi_check_error(root->EFI_FILE_OPEN(root, &file, file_name, EFI_FILE_MODE_READ, 0), L"read_file_to_address");

    EFI_FILE_INFO *file_info = efi_get_file_info(file_name);
    uint64_t file_size = file_info->FileSize;
    efi_free_pool(file_info);

    file->EFI_FILE_READ(file, &file_size, (void *) address);
    file->EFI_FILE_CLOSE(root);
}
