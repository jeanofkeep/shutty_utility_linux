#include "shutdown.h"
#include <stdio.h>
#include <stdlib.h>


void shutdown_system(int minutes) {
    if (minutes <= 0) {
        printf("Invalid shutdown time\n");
        return;
    }
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "shutdown -h +%d", minutes); // Linux
    system(cmd);

    int result = system(cmd);

    if (result == -1) {
        perror("system failed");
    }

}

void reboot_system(int minutes) {
    //minutes = 10;
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "shutdown -r +%d", minutes); // Linux
    system(cmd);
}

void undo_operation() {
    int undo = system("shutdown -c");

    if (undo == -1) {
        perror("system failed");
    }

    else if (undo >= 1) {
        perror("Undo ok!");
    }
}