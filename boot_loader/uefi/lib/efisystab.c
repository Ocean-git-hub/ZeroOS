#include <efisystab.h>
#include <efi/efi.h>

EFI_SYSTEM_TABLE *system_table;

void init_systab(EFI_SYSTEM_TABLE *_system_table) {
    system_table = _system_table;
}
