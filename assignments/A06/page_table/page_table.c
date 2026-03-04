#define _POSIX_C_SOURCE 200112L
#include "page_table.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// The pointer to the base directory.
// You can safely assume that this is set before any address conversion is done.
static PageDirectory *_cr3 = NULL;

typedef struct {
    uint32_t accessCounter;
    int valid;

    // ----------------
    // Add more data that needs to be stored in the TLB here.
    // ----------------
} TLBEntry;

typedef struct {
    TLBEntry entries[TLB_SIZE];
    uint32_t accessCounter;
} TLB;

// This is reset to all 0.
static TLB _tlb;

void setPageDirectory(PageDirectory *directory)
{
    _cr3 = directory;
    flushTLB();
}

void flushTLB()
{
    memset(&_tlb, 0, sizeof(_tlb));
}

int _setPte(uint32_t virtualBase, uint32_t pte)
{
    assert(_cr3 != NULL);
    assert(_getOffset(virtualBase) == 0);

    // (1) Get the page table from the given address
    uint32_t pdi = _getPageDirectoryIndex(virtualBase);
    assert(pdi < ENTRIES_PER_TABLE);

    uint64_t pde = _cr3->entries[pdi];
    PageTable *pageTable = NULL;
    if (!(pde & PAGE_PRESENT_MASK)) {
        // The page table has not been allocated yet. Allocate a new,
        // aligned one and clear it to reset all present bits in the PTEs.
        if (posix_memalign((void**)&pageTable, sizeof(PageTable),
                sizeof(PageTable)) != 0) {
            return -1;
        }

        assert(pageTable != NULL);
        memset(pageTable, 0, sizeof(PageTable));

        // Register the new page table in the page directory.
        uint64_t address = pointerToInt(pageTable);
        assert((address & OFFSET_MASK) == 0);

        pde = address | PAGE_PRESENT_MASK;
        _cr3->entries[pdi] = pde;
    } else {
        uint64_t pageTableAddress = pde & PAGE_DIRECTORY_ADDRESS_MASK;
        pageTable = (PageTable*)intToPointer(pageTableAddress);
    }

    // (2) Set the specified page table entry
    uint32_t pti = _getPageTableIndex(virtualBase);
    assert(pti < ENTRIES_PER_TABLE);

    pageTable->entries[pti] = pte;

    return 0;
}

int mapPage(uint32_t virtualBase, uint32_t physicalBase, ReadWrite accessMode,
    PrivilegeLevel privileges)
{
    if ((_getOffset(virtualBase) != 0) || (_getOffset(physicalBase) != 0)) {
        return -1;
    }

    // Build the page table entry from the physical base and flags
    uint32_t pte = physicalBase | PAGE_PRESENT_MASK;

    if (accessMode == ACCESS_WRITE) {
        pte |= PAGE_READWRITE_MASK;
    }

    if (privileges == USER_MODE) {
        pte |= PAGE_USERMODE_MASK;
    }

    // Set the new PTE and invalidate any cached version in the TLB
    int res = _setPte(virtualBase, pte);
    invalidateTLBEntry(virtualBase);

    return res;
}

int translatePageTable(uint32_t *address, ReadWrite accessMode,
    PrivilegeLevel privileges)
{
    assert(_cr3 != NULL);

    if (address == NULL) {
        return -1;
    }

    (void) accessMode;
    (void) privileges;

    // ----------------
    // Implement the address translation here.
    // ----------------

    return -1;
}

void invalidateTLBEntry(uint32_t virtualBase)
{
    assert(_getOffset(virtualBase) == 0);

    // ----------------
    // Implement the TLB invalidation here.
    // ----------------
}

static void _addToTLBAt(int index, uint32_t virtualBase, uint32_t pte)
{
    _tlb.entries[index].accessCounter = _tlb.accessCounter;
    _tlb.entries[index].valid = 1;
    _tlb.accessCounter++;

    (void) virtualBase;
    (void) pte;

    // ----------------
    // Add the entry to your TLB.
    // ----------------
}

int addToTLB(uint32_t virtualBase, uint32_t pte)
{
    if (_getOffset(virtualBase) != 0) {
        return -1;
    }

    int oldestEntry = 0;
    for (int i = 1; i < TLB_SIZE; i++) {
        if (!_tlb.entries[i].valid) {
            oldestEntry = i;
            break;
        }

        if (_tlb.entries[i].accessCounter < _tlb.entries[oldestEntry].accessCounter) {
            oldestEntry = i;
        }
    }

    _addToTLBAt(oldestEntry, virtualBase, pte);

    return 0;
}

int translateTLB(uint32_t *address, ReadWrite accessMode,
    PrivilegeLevel privileges)
{
    if (address == NULL) {
        return -1;
    }

    (void) accessMode;
    (void) privileges;

    // ----------------
    // Implement the TLB translation here.
    // ----------------

    return -1;
}
