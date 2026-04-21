#include <forge.h>

#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#include <backtrace.h>

// Global state for libbacktrace
static struct backtrace_state *backtraceState = NULL;

// Callback for each frame in the stack
static int symCallback(void *data, uintptr_t pc, const char *filename,
                       int lineno, const char *function) {
        (void)data;

        // Print in a human-readable format
        if (function) {
                printf("  [0x%lx] %s (%s:%d)\n", (unsigned long)pc, function,
                       filename ? filename : "??", lineno);
        } else {
                printf("  [0x%lx] ?? (%s:%d)\n", (unsigned long)pc,
                       filename ? filename : "??", lineno);
        }
        return 0; // Continue unwinding
}

// Error callback for libbacktrace
static void errorCallback(void *data, const char *msg, int errnum) {
        (void)data;
        fprintf(stderr, "libbacktrace error: %s (errno: %d)\n", msg, errnum);
}

void printStackTrace() {
        if (!backtraceState) {
                backtraceState =
                    backtrace_create_state(NULL, 1, errorCallback, NULL);
        }

        if (backtraceState) {
                printf("Stack trace:\n");
                backtrace_full(backtraceState, 1, symCallback, errorCallback,
                               NULL);
        }
}
#endif
