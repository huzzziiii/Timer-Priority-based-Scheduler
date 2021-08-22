#include "list.h"

// static int initTime;
extern unsigned int initTime; 
struct timespec endTime;
extern struct timespec startTime;

void print(Node *node)
{
  for (; node != NULL; node = node->nxt)
  {
    printf ("%d (%s,%d,%u) -> ", node->refTime, node->name, node->priority, node->expiry);
  }
  printf ("\n=============================================\n\n");
}

Node *CreateNode(char *name, unsigned int expiry, int priority)
{
  // initTime = (unsigned) time(NULL);

  Node *node = malloc(sizeof(*node) + strlen(name) + 1);
  node->name = name;
  clock_gettime(CLOCK_MONOTONIC, &endTime);
  // int timeElapsed = (unsigned) time (NULL) - initTime;
  unsigned int timeElapsed = ( endTime.tv_sec - startTime.tv_sec );

  // int timee
  // node->refTime = (unsigned) time (NULL) + expiry;
  node->refTime = timeElapsed + expiry;
  // node->refTime = timeElapsed + expiry;
  node->expiry = expiry;
  node->priority = priority;
  node->nxt = NULL;
  unsigned int diff = node->refTime - node->prevRefTime;

  printf ("Create - name: %s, expiry: %u, refTime: %u, priority: %d,  diff: %u, timeElapsed: %u\n", node->name, node->expiry, node->refTime, node->priority, diff, timeElapsed);
  return node;
}

void push(Node **node, char *name, int expiry, int priority)
{ 
  unsigned int curTime; //  (unsigned)time(NULL)
  unsigned int updatedTime;

  Node *head = *node;
  // updatedTime = (unsigned) time (NULL) + expiry;
  Node *tmp = CreateNode(name, expiry, priority);

  // printf ("New - name: %s, expiry: %d, updatedTime: %u, priority: %d\n", name, expiry, updatedTime, priority);

  printf ("[Head] name: %s,       nxt: %p, headExpiry: %d, refTime: %u\n", head->name, head->nxt, head->expiry, head->refTime);
  printf ("[Temp] name: %s,   nxt: %p, headExpiry: %d, refTime: %u, Head>Tmp: %d\n", tmp->name, tmp->nxt, tmp->expiry, tmp->refTime, head->expiry > tmp->expiry);


  if (tmp->refTime <= head->refTime)       // append before head
  {
    printf ("New node expiry <= head expiry -- ");
    if (tmp->priority > head->priority || tmp->refTime < head->refTime)   // append before head only when HIGH prio
    {
      printf ("tmp->priority > head->priority - append tmp before Head\n");
      tmp->nxt = head;
      *node = tmp;
    }
    else                                  // append after head
    {
      printf ("tmp->priority < head->priority - append tmp after Head\n");
      tmp->nxt = head->nxt;
      head->nxt = tmp;
    }
  }
  else
  {
    while(head->nxt)
    {
      if (tmp->refTime < head->nxt->refTime)
      {
         break;
      } 
      else if (tmp->refTime == head->nxt->refTime)
      {
        if (tmp->priority > head->nxt->priority)
        {
          break;
        }
      }
      head = head->nxt;
    }
      tmp->nxt = head->nxt;
      head->nxt = tmp;      
  
    // while(head->nxt && tmp->expiry >= head->nxt->expiry)
    // {
    //   head = head->nxt;
    // }
    // tmp->nxt = head->nxt;
    // head->nxt = tmp;

  }
  printf ("\n");
  print(*node);
}

void pop(Node **node)
{
  Node *tmp = *node;

  printf ("....Popping node (%s,%d,%d)......\n", tmp->name, tmp->priority, tmp->expiry);

  // changing head
  *node = (*node)->nxt;

  printf ("New head: %s\n", (*node)->name);

  // Node *newNode = malloc(sizeof(*newNode) + strlen(tmp->name) + 1);
  char *name = tmp->name;
  unsigned int expiry = tmp->expiry;
  unsigned int priority = tmp->priority;
  
  // delete the node
  free(tmp);

  // pushing new node
  push(node, name, expiry, priority);
}