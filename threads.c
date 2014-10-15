#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// following needed for fork() and exec()
// #include <unistd.h>

// Note that this is a C program, not C++ since the pthread library is
// available only in C.  (There are libraries available for C++ as well 
// but not as popular.) To compile, use: gcc -o threads threads.c


// There are multiple programs in this file.  Uncomment one at a time to see what each does.

//----------------------------------------------------------------------------------------------------
/* Creating threads and waiting for them to finish before exiting the program */

void *print_message_function( void *ptr );
 
int main()
{
  pthread_t thread1, thread2;
  char *message1 = "Thread 1";
  char *message2 = "Thread 2";
  int  iret1, iret2;

  // Create independent threads each of which will execute function
  // function prototype:
  // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
  //                    void * (*func)(void *), void *arg_to_func);
  iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);
  iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);

  // Wait till threads are complete before main() continues. Unless we wait we run 
  // the risk of executing an exit which will terminate the process and all threads 
  // before the threads have completed.
  // function prototype:
  // int pthread_join(pthread_t th, void **thread_return);
  // If thread_return is not NULL, the return value of "th" is stored in the location pointed to by thread_return
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Thread 1 returns: %d\n", iret1);
  printf("Thread 2 returns: %d\n", iret2);
  exit(0);
}

void *print_message_function(void *ptr)
{
  char *message;
  message = (char *) ptr;
  printf("%s \n", message);
}

//----------------------------------------------------------------------------------------------------
/* Thread synchronization 

void *functionC();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

int main()
{
   int rc1, rc2;
   pthread_t thread1, thread2;

   // Create independent threads each of which will execute functionC 

   if( (rc1=pthread_create(&thread1, NULL, &functionC, NULL)) ) {
     printf("Thread creation failed: %d\n", rc1);
   }

   if( (rc2=pthread_create(&thread2, NULL, &functionC, NULL)) ) {
     printf("Thread creation failed: %d\n", rc2);
   }

   // Wait till threads are complete before main continues. Unless we 
   // wait we run the risk of executing an exit which will terminate 
   // the process and all threads before the threads have completed.
   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);

   exit(0);
}

void *functionC()
{
   pthread_mutex_lock(&mutex1);
   counter++;
   printf("Counter value: %d\n",counter);
   pthread_mutex_unlock(&mutex1);
}
*/
//----------------------------------------------------------------------------------------------------
/* Thread joins 

#define NTHREADS 10
void *thread_function(void *);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;

int main()
{
   pthread_t thread_id[NTHREADS];
   int i, j;

   for(i=0; i < NTHREADS; i++) {
      pthread_create(&thread_id[i], NULL, thread_function, NULL);
   }

   for(j=0; j < NTHREADS; j++) {
      pthread_join(thread_id[j], NULL);
   }

   // Now that all threads are complete I can print the final result.
   // Without the join I could be printing a value before all the threads
   // have been completed.                                               
   printf("Final counter value: %d\n", counter);
}

void *thread_function(void *dummyPtr)
{
  // pthread_self() returns identifier for the current thread
  // printf("Thread number %ld\n", pthread_self());
   pthread_mutex_lock(&mutex1 );
   counter++;
   pthread_mutex_unlock(&mutex1 );
}
 */
