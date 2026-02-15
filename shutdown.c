#include "shutdown.h"
#include <stdio.h>
#include <stdlib.h>

void shutdown_system(int minutes) {
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "shutdown -h +%d", minutes); // Linux
    system(cmd);
}

void reboot_system(int minutes) {
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "shutdown -r +%d", minutes); // Linux
    system(cmd);
}