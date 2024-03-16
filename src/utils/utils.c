#include <sys/stat.h>
#include "utils.h"

int new_fifo(){
    int fifo = mkfifo("../so-orchestrator/tmp/pipe", 0666);
    if(fifo != 0){
        return 1;
    }
    return 0;
}