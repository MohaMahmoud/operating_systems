#include "run_program.h"
#include <unistd.h>    // Für fork, execvp
#include <sys/wait.h>  // Für waitpid, WIFEXITED, WEXITSTATUS
#include <stdlib.h>    // Für malloc, free, exit

#define ERROR_CODE 127

int run_program(char *file_path, char *arguments[])
{   
    pid_t pid = fork(); // pid_t ist der saubere Datentyp für PIDs

    if (pid < 0) {
        return ERROR_CODE;
    }
    
    if (pid == 0) {
        // --- CHILD PROCESS ---
        int arg_count = 0;
        if (arguments != NULL) {
            while (arguments[arg_count] != NULL) {
                arg_count++;
            }
        }

        char **new_args = malloc((arg_count + 2) * sizeof(char*));
        
        new_args[0] = file_path;
        
        for (int i = 0; i < arg_count; i++) {
            new_args[i + 1] = arguments[i];
        }
        
        new_args[arg_count + 1] = NULL;

        execvp(file_path, new_args); //returns 0 if succeeded
        
        free(new_args);
        exit(ERROR_CODE); //else returns 127
    }
    else {
        // --- PARENT PROCESS ---
        int status;
        //go to sleep, if failed waitpid returned -1 => return error code
        if (waitpid(pid, &status, 0) == -1) {
            return ERROR_CODE; 
        }

        // HIER IST DIE WICHTIGE ÄNDERUNG:
        // Prüfen, ob das Kind normal mit exit() beendet wurde
        if (WIFEXITED(status)) {
            // Prüfen, ob der Exit-Code genau 127 war (execvp fehlgeschlagen)
            if (WEXITSTATUS(status) == 127) {
                return ERROR_CODE;
            }
            // Alles lief gut
            return 0;
        }

        // Wenn wir hier landen, wurde das Kind z.B. durch ein Signal abgewürgt
        return ERROR_CODE;
    }
} 