#include "tmp.h"
 
FILE *log_fp;
char buf[500] = {0};
char buf1[200] = {0};

time_t timer;
char buffer[25] = {0};
struct tm* tm_info;
level log_level = DEBUG;
pthread_mutex_t log_mutex;

void log_init()
{
   sprintf(buf, "/tmp/machine.%d.log", MACHINE_ID);
   log_fp = fopen(buf, "a");
   pthread_mutex_init(&log_mutex, NULL);
}

void log_exit()
{
    fclose(log_fp);
}

/*void main() {
    char *myIP = "120.122.333.111";
    log_init();
    LOG(INFO, "Hello %s", "world");
}*/
