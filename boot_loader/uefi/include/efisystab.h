#ifndef ZEROOS_EFISYSTAB_H
#define ZEROOS_EFISYSTAB_H

#include <efi/efi.h>

void efi_system_table_initilize(EFI_SYSTEM_TABLE *_system_table);

const EFI_SYSTEM_TABLE *get_system_table();

#endif //ZEROOS_EFISYSTAB_H
