Name  : Ahmad Rangeen
Date  : 8 / 4 / 2018
Class : Csc 415: Operating Systems

Compile Instructions:
    
    1. Open Terminal
    2. change directory to csc415-p5-arangeen-part2
    3. run the command : gcc pandc.c 

Run Instructions:

    4. After compiling, run the command a.out with
       6 more arguments. 
       For example : ./a.out 7 5 3 15 1 1


Project Description:

    For part 2 of this project, we implemented our own Producer-Consumer
    program using Linux threads. We implemented the code in C  using 
    appropriate synchronization primitives so that our code always executes 
    correctly. The program accepts 6 command line arguments N, P, C, X,
    Ptime, Ctime, Where N is number of buffers to maintain, P is the 
    number of producer threads, C is the number of consumer threads, X 
    is the number of items each producer thread will produce, Ptime is 
    how long each producer thread will sleep after producing an item, 
    and Ctime is how long each consumer thread will sleep after consuming 
    an item. 

Test Strategy: 

    My test strategy is a simple approach where we have to maintain 
    a consumer array and a producer array. If everything works out 
    these two arrays should be identical and in order. 

