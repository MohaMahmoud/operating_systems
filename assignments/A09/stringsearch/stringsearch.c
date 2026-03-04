#include "stringsearch.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Attempt to find needle within the first `len` bytes of haystack, returning
 * the first offset if successful, or -1 otherwise.
 */
ssize_t findFirstSubstring(const char *needle, const char *haystack, size_t len)
{   
    size_t needle_len = strlen(needle);
    
    // Wenn das Suchwort länger ist als der Text, kann es nicht drin sein
    if (needle_len > len) {
        return -1;
    }

    // Äußere Schleife
    for (size_t i = 0; i <= len - needle_len; i++) {
        size_t j;
        
        // Innere Schleife: Zeichen vergleichen
        for (j = 0; j < needle_len; j++) {
            if (haystack[i+j] != needle[j]) {
                break; // Passt nicht, innere Schleife abbrechen
            }
        }
        
        // Wenn die innere Schleife komplett bis zum Ende durchgelaufen ist,
        // haben wir das Wort gefunden!
        if (j == needle_len) {
            return (ssize_t)i; 
        }
    }
    
    // Nichts gefunden
    return -1;
}

/*
 * Allocate a new Lines structure.
 */
Lines *newLines()
{
    Lines *lines = malloc(sizeof(Lines) + LINES_DEFAULT_CAP * sizeof(Line));
    lines->len = 0;
    lines->cap = LINES_DEFAULT_CAP;
    return lines;
}

/*
 * Append a line to the Lines structure, growing it as necessary.
 */
void appendLine(Lines **lines, Line l)
{
    if ((*lines)->len == (*lines)->cap) {
        size_t new_cap = (*lines)->cap * 2;
        *lines = realloc(*lines, sizeof(Lines) + new_cap * sizeof(Line));
        (*lines)->cap = new_cap;
    }
    (*lines)->lines[(*lines)->len++] = l;
}

/*
 * Walk through `haystack` and find all lines (delimited by '\n').
 */
Lines *findLines(const char *haystack, size_t len)
{
    Lines *lines = newLines();
    int start = 0;
    int length = 0;
    for (size_t i = 0; i<len; i++) {
        if (haystack[i]=='\n') {
            length = i - start+1;
            Line current_line;
            current_line.start = haystack+start;
            current_line.len = length;
            appendLine(&lines,current_line);
            start=i+1;
        }
    }
    return lines;
}

/*
 * Use binary search to find the line corresponding to the given match,
 * where match is a pointer to the beginning of the matching sequence 
 * inside the haystack.
 */
Line *findLineContaining(Lines *l, const char *match)
{   
    long left = 0;
    long right = l->len - 1;

    while (left <= right) {
        long mid = left + (right - left) / 2;
        Line *mid_line = &(l->lines[mid]); 

        if (match >= mid_line->start && match < (mid_line->start + mid_line->len)) {
            return mid_line;
        }
        
        else if (match < mid_line->start) {
            right = mid - 1; 
        }
        
        else {
            left = mid + 1;
        }
    }

    return NULL;
    
}

typedef struct _LineSearcherState {
    Lines **lines;
    const char *haystack;
    size_t len;
} LineSearcherState;

/*
 * Entry point for the line searching thread.
 */
void *lineSearcher(void *arg)
{
    LineSearcherState *state = arg;
    *state->lines = findLines(state->haystack, state->len);
    return NULL;
}

/*
 * Entry point for the needle searching threads.
 */
void *needleSearcher(void *arg)
{
    NeedleSearcherState *state = arg;
    NeedleSearcherResult *results = NULL;

    /* TODO: Find all substrings by calling findFirstSubstring() and collect
     * them in a linked list with NeedleSearcherResult. */
    NeedleSearcherResult *tail = NULL;

    const char *current_haystack = state->haystack;
    size_t needle_len = strlen(state->needle);
    size_t current_len = state->len;
    while(current_len>=needle_len) {
        ssize_t offset = findFirstSubstring(state->needle, current_haystack, needle_len);
        if (offset == -1) {
            break; 
        }
        const char *match_ptr = current_haystack + offset;
        NeedleSearcherResult *new_node = malloc(sizeof(NeedleSearcherResult));
        new_node->match = match_ptr;
        new_node->line = NULL; 
        new_node->next = NULL;
        if (results == NULL) {
            results = new_node; 
            tail = new_node;
        } else {
            tail->next = new_node; 
            tail = new_node;
        }
        current_haystack = match_ptr + needle_len;
        current_len = current_len - offset - needle_len;
    }

    // Wait for line information to be ready.
    pthread_mutex_lock(state->mutex);
    while (!*state->lines_valid) {
        pthread_cond_wait(state->cond, state->mutex);
    }
    // Once the lines are valid, there are no more writes to them, so no
    // locking is necessary.
    pthread_mutex_unlock(state->mutex);

    /* TODO: Add line information to the results by calling findLineContaining(). */
    NeedleSearcherResult *curr = results;
    while (curr != NULL) {
        curr->line = findLineContaining(*state->lines, curr->match);
        curr = curr->next;
    }
    return results;
}


/*
 * Perform a parallel search for `needle` on `haystack`, printing all matching lines.
 */
void parallelStringSearch(const char *needle, const char *haystack, size_t hay_len, int threads)
{
    size_t needle_len = strlen(needle);

    Lines *lines;
    // Start the line searcher thread.
    LineSearcherState line_state = {.lines = &lines, .haystack = haystack, .len = hay_len};
    pthread_t line_thread;
    pthread_create(&line_thread, NULL, lineSearcher, &line_state);

    // Start the threads searching for the keyword.
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    bool lines_valid = false;
    NeedleSearcherState *state = malloc(sizeof(NeedleSearcherState) * threads);
    pthread_t *searcher_threads = malloc(sizeof(pthread_t) * threads);
    for (int i = 0; i < threads; i++) {
        state[i] = (NeedleSearcherState) {
            .needle = needle,
            // overlap by needle_len - 1
            .haystack = haystack + i * hay_len / threads - (i > 0 ? needle_len - 1 : 0),
            .len = hay_len / threads + (i > 0 ? needle_len - 1 : 0),

            .cond = &cond,
            .mutex = &mutex,
            .lines_valid = &lines_valid,
            .lines = &lines,
        };
        pthread_create(&searcher_threads[i], NULL, needleSearcher, &state[i]);
    }

    // Wait for the lines to be ready, then signal the search threads.
    pthread_join(line_thread, NULL);

    pthread_mutex_lock(&mutex);
    lines_valid = true;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    for (int i = 0; i < threads; i++) {
        NeedleSearcherResult *result;
        pthread_join(searcher_threads[i], (void **) &result);
        for (NeedleSearcherResult *r = result; r; r = result) {
            size_t lineno = r->line - lines->lines;
            printf("%zu:%zu\t%.*s\n", lineno, r->match - r->line->start, (int) r->line->len - 1, r->line->start);
            result = r->next;
            free(r);
        }
    }

    free(lines);
    free(state);
    free(searcher_threads);
}

