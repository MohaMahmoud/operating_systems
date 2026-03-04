#include "tslock.h"
#include <sched.h>

void tslock_init(TicketSpinlock *tslock)
{
    tslock->currentTicket = 0;
    tslock->ticketCounter = 0;
}

void tslock_lock(TicketSpinlock *tslock)
{
    uint32_t my_ticket = 1; 

    // Inline-Assembler für atomares Ziehen des Tickets
    __asm__ volatile (
        "lock xaddl %0, %1\n"
        : "+r" (my_ticket), "+m" (tslock->ticketCounter) // my_ticket = ticket_counter++;
        : // Sagt dem Compiler: Achtung, der Hauptspeicher wurde verändert!
        : "memory"
    );


    while (tslock->currentTicket != my_ticket) {
        sched_yield(); 
    }

}

void tslock_unlock(TicketSpinlock *tslock)
{
    tslock->currentTicket++;
}