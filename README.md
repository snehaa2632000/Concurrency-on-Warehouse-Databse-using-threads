# Concurrency-on-Warehouse-Databse-using-threads
POSIX library threads are used to implement concurrency on the warehouse database for updating stocks and creating new products.

The objective of this assignment is to provide a practical view of the synchronization mechanisms available in the POSIX threads library. In particular, this assignment focuses on the basic structures of mutexes and conditional variables as a means to control the access to critical sections of the program. In this respect, the use of mutexes permits enforcement of mutual exclusion when several threads try to access the critical region at the same time. Condition variables on the other hand permit to wait until a certain condition is met. 
The synchronization will be implemented using POSIX thread syscalls.

 In particular: 
 pthread_create will be used to create and execute new threads. 
 pthread_join will be used if any thread must wait for the finalization of another thread. 
 Mutexes (pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock, and pthread_mutex_destroy) will be used to protect the access to critical sections. 
 Cond. variables (pthread_cond_init, pthread_cond_wait, pthread_cond_signal, and pthread_cond_destroy) will be used to wait until a certain condition is met. 

The objective is to design and implement a concurrent access library operating on the top of a warehouse database, in order to guarantee the consistency of all operations even if those operations are performed in a concurrent manner. 
