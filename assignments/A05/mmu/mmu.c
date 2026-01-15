#include "mmu.h"

static SegmentTable *_table;

// ----------------
// Add your global data structures here.
// ----------------
typedef struct {
    uint32_t virtual;
    uint32_t physical;
    uint64_t lastAccessTime;
    int valid;
} TLBEntry;


static TLBEntry _tlb[TLB_SIZE];

static uint64_t globalAccessCounter;

void setSegmentTable(SegmentTable *newTable)
{
    _table = newTable;
    flushTLB();
}

int translateSegmentTable(uint32_t *address)
{
    uint32_t virtual = *address;
    uint32_t segmentIndex = virtual >> 29;
    uint32_t offset = virtual & 0x1FFFFFFF;
    if (segmentIndex >= SEGMENT_COUNT) {
        return -1;
    }
    Segment segment = _table->segments[segmentIndex];

    if (segment.length == 0 || offset >= segment.length) {
        return -1;
    }
    *address = segment.base + offset;
    return 0;
}

void flushTLB(void)
{
    for (int i = 0; i < TLB_SIZE; i++) {
        _tlb[i].virtual = 0;
        _tlb[i].physical = 0;
        _tlb[i].lastAccessTime = 0;
    }
    globalAccessCounter = 0;
}

void addToTLB(uint32_t virtual, uint32_t physical)
{
    
    uint64_t oldestTime = UINT64_MAX;
    int oldestIndex = -1;
    for (int i = 0; i < TLB_SIZE; i++) {
        if (_tlb[i].lastAccessTime < oldestTime) {
            oldestTime = _tlb[i].lastAccessTime;
            oldestIndex = i;
        }
        if (!_tlb[i].valid) {
            _tlb[i].virtual = virtual;
            _tlb[i].physical = physical;
            _tlb[i].lastAccessTime = globalAccessCounter++;
            _tlb[i].valid = 1;
            return;
        }
    } 
    _tlb[oldestIndex].virtual = virtual;
    _tlb[oldestIndex].physical = physical;
    _tlb[oldestIndex].valid = 1;
    _tlb[oldestIndex].lastAccessTime = globalAccessCounter++;
}

int translateTLB(uint32_t *address)
{   
    uint32_t virtual = *address;
    for (int i = 0; i < TLB_SIZE; i++) {
        if (_tlb[i].valid && _tlb[i].virtual == virtual) {
            _tlb[i].lastAccessTime = globalAccessCounter++;
            *address = _tlb[i].physical;
            return 0;
        }
    }
    return -1;
}