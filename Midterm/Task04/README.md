# FE 522 Fall 2017 Midterm Exam Task 2 (30 points)

Given the vector X of floating point numbers in the main.cpp file, design 2 functions that calculate the expected value and the median of the sample contained in the vector, respectively.

The sample mean of a data set X = (x_1, x_2, ..., x_n) is  
E[X] = (x_1 + x_2 + ... + x_n) / n  

The median of a data set is http://en.wikipedia.org/wiki/Median, first paragraph.
In the data set, first one must arrange all the observations in order. 

If n is odd then Median (M) = value of ((n + 1)/2)th item term.
If n is even then Median (M) = value of [(n/2)th item term + (n/2 + 1)th item term]/2

Put the function prototypes into a header file with name func.h. Put the function definitions into a source file called func.cpp. Include func.h in main.cpp and call the functions to output the results onto the standard output.

You will also have to modify your CMakeLists.txt file accordingly in the process.
