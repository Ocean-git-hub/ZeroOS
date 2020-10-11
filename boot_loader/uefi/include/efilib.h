#ifndef ZEROOS_EFILIB_H
#define ZEROOS_EFILIB_H

#include <efiio.h>
#include <efifilelib.h>
#include <efiprotocol.h>
#include <efisystab.h>
#include <efistring.h>
#include <efiutils.h>
#include <efimemory.h>
#include <efimemorymap.h>

static void efi_lib_initialize(EFI_SYSTEM_TABLE *system_table) {
    efi_system_table_initilize(system_table);
    efi_located_protocol_initilize();
    efi_io_initialize();
}

#endif //ZEROOS_EFILIB_H
