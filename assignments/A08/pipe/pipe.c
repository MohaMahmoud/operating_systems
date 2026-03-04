// This changes the way some includes behave.
// This should stay before any include.
#define _GNU_SOURCE

#include "pipe.h"
#include <sys/wait.h> /* For waitpid */
#include <unistd.h> /* For fork, pipe */
#include <stdlib.h> /* For exit */
#include <fcntl.h>
#include <errno.h>

int run_program(char *file_path, char *argv[])
{

    if ((file_path == NULL) || (argv == NULL)) {
        return -1;
    }

    // -------------------------
    // TODO: Open a pipe
    // -------------------------
    int pipe_fd[2]; 
    pipe2(pipe_fd, O_CLOEXEC);

    int child_pid = fork();
    if (child_pid == -1) {
        return -1;
    } else if (child_pid == 0) {

        // Replace program
        execvp(file_path, argv);

        // -------------------------
        // TODO: Write the error on the pipe
        // -------------------------
        int err = errno; 
        write(pipe_fd[1], &err, sizeof(err));
        close(pipe_fd[1]);
        _exit(127); // Benutze _exit in Kindprozessen nach Fehlern

    } else { //Vaterprozess
        int status, hadError = 0;

        int waitError = waitpid(child_pid, &status, 0);
        if (waitError == -1) {
            // Error while waiting for child.
            hadError = 1;
        } else if (!WIFEXITED(status)) {
            // Our child exited with another problem (e.g., a segmentation fault)
            // We use the error code ECANCELED to signal this.
            hadError = 1;
            errno = ECANCELED;
        } else {
            // -------------------------
            // TODO: If there was an execvp error in the child, set errno
            //       to the value execvp set it to.
            // -------------------------
            int err;
            ssize_t bytesRead = read(pipe_fd[0], &err, sizeof(err));
            if (bytesRead == sizeof(err)) {
                errno = err;
                hadError = 1;
            }
            close(pipe_fd[0]); // Close read end in parent
            close(pipe_fd[1]); // Close write end in parent
        }

        return hadError ? -1 : WEXITSTATUS(status);
    }
}
