#include <efisystab.h>
#include <efi/efi.h>

const EFI_SYSTEM_TABLE *system_table;

const EFI_SYSTEM_TABLE *get_system_table() {
    return system_table;
}

void efi_system_table_initilize(EFI_SYSTEM_TABLE *_system_table) {
    system_table = _system_table;
}
