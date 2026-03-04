#include "barrier.h"
#include <unistd.h>
#include <pthread.h>

struct _ThreadBarrier {
    unsigned int count;       // Wie viele Threads müssen insgesamt ankommen?
    unsigned int arrived;     // Wie viele Threads sind schon da?
    unsigned int generation;  // Aktuelle Phase (verhindert das Überholen von Threads)
    pthread_mutex_t mutex;    // Schützt die Variablen count, arrived und generation
    pthread_cond_t cond;      // Hier legen sich die Threads schlafen
};

ThreadBarrier *createBarrier(int threads)
{
    if (threads == 0) {
        return NULL;
    }

    ThreadBarrier *barrier = (ThreadBarrier *)malloc(sizeof(ThreadBarrier));
    if (barrier == NULL) {
        return NULL; 
    }

    barrier->count = threads;
    barrier->arrived = 0;
    barrier->generation = 0;

    // Wenn die Initialisierung fehlschlägt, müssen wir den bereits 
    // allokierten Speicher wieder freigeben, um Leaks zu vermeiden.
    if (pthread_mutex_init(&barrier->mutex, NULL) != 0) {
        free(barrier);
        return NULL;
    }

    // 5. Condition Variable initialisieren
    if (pthread_cond_init(&barrier->cond, NULL) != 0) {
        pthread_mutex_destroy(&barrier->mutex); // Mutex wieder aufräumen
        free(barrier);
        return NULL;
    }

    return barrier;
}

void enterBarrier(ThreadBarrier *barrier)
{   
    pthread_mutex_lock(&barrier->mutex);

    unsigned int local_generation = barrier->generation;
    barrier->arrived++;
    if (barrier->count = barrier->arrived) {
        barrier->arrived = 0;
        barrier->generation++;
        pthread_cond_broadcast(&barrier->cond);
        phread_mutex_unlock(&barrier->mutex);

    } else {
        while (local_generation==barrier->generation) {
            pthread_cond_wait(&barrier->cond, &barrier->mutex);
        }
        phread_mutex_unlock(&barrier->mutex);
    }
}

void deleteBarrier(ThreadBarrier *barrier)
{
    if (barrier == NULL) {
        return;
    }

    // Zuerst die POSIX-Objekte zerstören, damit das OS die Ressourcen freigibt
    pthread_mutex_destroy(&barrier->mutex);
    pthread_cond_destroy(&barrier->cond);

    free(barrier);
}