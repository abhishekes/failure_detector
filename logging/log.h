#ifndef __LOG_H__
#define __LOG_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#define MACHINE_ID 1

extern FILE *log_fp;
extern char buf[500];
extern char buf1[200];

extern time_t timer;
extern char buffer[25];
extern struct tm* tm_info;

extern pthread_mutex_t log_mutex;

void log_init();
void log_exit();

typedef enum {
    DEBUG,
    TRACE,
    INFO,
    ERROR
}level;

extern level log_level;
#define LOG(level,str, ...)  do { \
  if (level >= log_level) { \
      pthread_mutex_lock(&log_mutex); \
      time(&timer); \
      tm_info = localtime(&timer); \
      strftime(buffer, 35, "\n[%Y-%m-%d  %H:%M:%S ] ",tm_info); \
      snprintf(buf,16,"%s", myIP); \
      strncat(buf,buffer, 51); \
      strcpy(buf1, __FILE__); \
      strcat(buf, buf1); \
      sprintf(buf1,"(%d) ", __LINE__); \
      strcat(buf, buf1); \
      strcat(buf," : "); \
      strcpy(buf1, str); \
      strcat(buf, buf1); \
      fprintf(log_fp, buf, __VA_ARGS__); \
      pthread_mutex_unlock(&log_mutex); \
  } \
}while (0) 

void log_init();
void log_exit();

#endif
