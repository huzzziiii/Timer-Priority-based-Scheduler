#include <stdio.h>
#include "list.h"
#include <time.h>
#include <pthread.h>
typedef struct
{
  char *type;
  int expiry;
  int priority; 
} ExecSchedule;

ExecSchedule execSchedule[] = {
    {
      .type = "cellularTask",
      .expiry = 5,
      .priority = 10
    },
    {
      .type = "ledTask",
      .expiry = 4,
      .priority = 1
    },
    {
      .type = "batteryTask",
      .expiry = 5,
      .priority = 1
    },
    {
      .type = "gpsTask",
      .expiry = 2,
      .priority = 11
    },
    {
      .type = "ranTask",
      .expiry = 5,
      .priority = 10
    },
    {
      .type = "haTask",
      .expiry = 4,
      .priority = 12
    }
}; 

Node *head; 
unsigned int initTime; 

void *Scheduler(void *arg)
{ 
  unsigned int currentTime;

  printf (">>>>> Scheduler starts <<<<<\n");

  while(1)
  { 
    currentTime = (unsigned) time(NULL) - initTime;
    if (currentTime >= head->refTime)
    {
      printf ("%s (%d) expires - time elasped: %d\n", head->name, head->refTime, currentTime);

      pop(&head);
    }
  }
}


#define BILLION 1E9

int main(void) 
{
  initTime = time(NULL);

  time_t uh = time(NULL);
  printf ("...UH: %d\n", sizeof(uh));

  struct timespec requestStart, requestEnd;
    
    clock_gettime(CLOCK_MONOTONIC, &requestStart);
    sleep(5);
    clock_gettime(CLOCK_MONOTONIC, &requestEnd);

    // Calculate time it took
    double accum = ( requestEnd.tv_sec - requestStart.tv_sec ) + (requestEnd.tv_nsec - requestStart.tv_nsec ) / BILLION;
    printf( "%lf\n", accum );
    
    

// //   clock_t begin = clock();

// // /* here, do your time-consuming job */
// sleep(2);
// unsigned int b = time(NULL);
// // clock_t end = clock();
// // double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
// printf ("--timeSpent: %u\n", (b-a));

  pthread_t tId;
  

  head = CreateNode(execSchedule[1].type, execSchedule[1].expiry, execSchedule[1].priority);
  
  print(head);

  // push(&head, head->name, head->expiry, head->priority);
  push(&head, execSchedule[0].type, execSchedule[0].expiry, execSchedule[0].priority);
  push(&head, execSchedule[2].type, execSchedule[2].expiry, execSchedule[2].priority);

  // sleep(3);
  pthread_create(&tId, NULL, Scheduler, NULL);


  // for (int i=0; i<3; i++)
  // {
  //   pop(&head);
  //   sleep(1);
  // }
  // printf ("new head: %s\n", head->name);

  // push(&head, execSchedule[3].type, execSchedule[3].expiry, execSchedule[3].priority);
  // push(&head, execSchedule[4].type, execSchedule[4].expiry, execSchedule[4].priority);
  // push(&head, execSchedule[5].type, execSchedule[5].expiry, execSchedule[5].priority);
  
  // print(head);

  pthread_join(tId, NULL);

  return 0;
}