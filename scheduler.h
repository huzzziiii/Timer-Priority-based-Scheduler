#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


typedef struct node
{
  struct node *head;
  char *name;
  int priority;
  unsigned int expiry;
  unsigned int refTime;
  unsigned int prevRefTime;
  struct node *nxt;
} Node;

void push(Node **node, char *name, int expiry, int priority);
void pop(Node **node);
Node *CreateNode(char *name, unsigned int expiry, int priority);
void print(Node *node);