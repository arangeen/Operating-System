Build Instructions:
    1. Open Terminal
    2. change directory to csc415-p1-arangeen
    3. run the command : make 

Run Instructions:
    4. After building, run the command : ./hw


What the program does:
    This program will ask the user for the name 
    of the file you want to copy. Then it will ask 
    the user for the name of the file you to to 
    paste the contents of the first file in. 
    It will let you know if the copy was successful 
    and if the program is successful, you will know 
    how many bytes were copied. 



dtruss output:

    CALL                                        COUNT
    bsdthread_register                              1
    exit                                            1
    getrlimit                                       1
    munmap                                          1
    proc_info                                       1
    shared_region_check_np                          1
    writev_nocancel                                 1
    fcntl                                           2
    getpid                                          2
    issetugid                                       2
    pread                                           2
    read_nocancel                                   2
    sysctl                                          2
    thread_selfid                                   2
    csops                                           3
    fstat64                                         3
    ioctl                                           3
    write_nocancel                                  3
    close                                           4
    mmap                                            4
    open                                            4
    mprotect                                        8
    stat64                                         45

dtruss output explained:
    The dtruss output shows us all the different calls that 
    we used during our program and the amount of times it 
    was used. 





