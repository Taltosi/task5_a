Ex5

Submit the assignment:
Tal Tosiano 208846600
Maya Hadad 209963784

## the assignment process
   partA-In the first part we check for primality, 
   partB-Than we implemented a queue in a busy environment.
   partC-We implemented an active object that supports three functions: (1)CreateActiveObject, (2)getQueue, (3)stop
   partD-We wrote a program called pipelie_st(collection of active object (AO)) that accepts one or two arguments in the input line, 
         the first is N (representing the number of tasks). The second is seed random. If a random seed is not received, one can be generated using null (time)


# The files of the assignment
  st_pipeline.c
  activeObject.c
  activeObject.h
  ThreadSafeQueue.c
  ThreadSafeQueue.h

# Run the task
  $ make
  $ ./st_pipeline <random number> <random seed>
For example:

# The Usage :
./st_pipelins 2 12345

