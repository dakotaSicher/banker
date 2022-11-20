Dakota Sicher
Operating Systems 
Assignment #2 

Banker's Algorithm 

compile: g++ banker.cpp -o banker 

libraries used: iostream, fstream

process.txt format: 
line1: is the # of types of resources 
line2: the total amount of each type of resource separated by a space 
line3: the number of processes line4: alocated amounts of each resource and the max of each resources for process 0, each separated by a space 
each line after is same as line 4 for each additional process

In implimenting the banker's algorithm I decided to use dynamic multi arrays to allow for variable amounts of resources and process to be used as input states.
The program first reads in from the file based on the formating above to determine the size of the multi arrays needed and then populates the arrays accordingly.

The program then evaluates the processes in order, evaluating each one to see if the available resources meet the maximum demand or that that process might require.
If the process is able to execute with the current available resources the process is updated as finished, and the next process is selected. 
If the process is not able to execute, then the loop moves on to the next, until it either finds the next process able to execute.
If no executable processes are found prior to returning to the last executed process in the list and not all processes have been marked 
finished (processes remaining > 0), then the set of processes and available resources are determined to be in an unsafe state.
If all process are able to execute, then the system is in a safe state. 
