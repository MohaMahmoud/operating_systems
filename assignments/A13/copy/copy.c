#define _POSIX_C_SOURCE 2
#include "copy.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

// Intermediate copy buffer. Use this buffer for your read() and write() calls.
char _buffer[BUFFER_SIZE];

int parseCopyArgs(int argc, char * const argv[], CopyArgs* args)
{
    if (args == NULL) {
        return -1;
    }

    // Initialize with default values
    args->skip  = 0;
    args->count = -1;

    // ----------------
    // Parse the arguments.
    // ----------------
    int opt;
    optind = 1; 

    // 2. Parsen der Optionen -s und -c, die jeweils ein Argument (:) erwarten
    while ((opt = getopt(argc, argv, "s:c:")) != -1) {
        switch (opt) {
            case 's':
                args->skip = atol(optarg);
                // Überprüfung auf positiven Integer (wie in der Aufgabenstellung verlangt)
                if (args->skip < 0) {
                    return -1;
                }
                break;
            case 'c':
                args->count = atol(optarg);
                // Überprüfung auf positiven Integer
                if (args->count < 0) {
                    return -1;
                }
                break;
            default: // Fängt alle unbekannten Optionen (z.B. -x) ab (getopt liefert '?')
                return -1;
        }
        if (argc - optind != 2) {
        return -1; // Zu viele oder zu wenige Argumente
    }

    // 4. Quell- und Zieldatei in die Struktur speichern
        args->src = argv[optind];
        args->dest = argv[optind + 1];

    // Alles war erfolgreich
    return 0;
    }
    return -1;
}

int doCopy(CopyArgs* args)
{
    if (args == NULL) {
        return -1;
    }

    // ----------------
    // Copy the file.
    // ----------------

    return -1;
}
