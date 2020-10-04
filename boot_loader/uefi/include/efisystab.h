#ifndef ZEROOS_EFISYSTAB_H
#define ZEROOS_EFISYSTAB_H

#include <efi/efi.h>

extern EFI_SYSTEM_TABLE *system_table;

void init_systab(EFI_SYSTEM_TABLE *_system_table);

#endif //ZEROOS_EFISYSTAB_H
