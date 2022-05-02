# COMP2401A4

Compile Instructions:

make

Run Instructions:

./rrtTester \<growthLength\> \<maxNodes\> \<enviromentVariable\>
  
  growthLength:  the edge growth length for each tree branch
  
  maxNodes: the maximum number of tree nodes to create
  
  enviromentVariable: the environment number to test \[1-5\]

Sample Mem Test Instructions:

valgrind ./rrtTester 25 200 1 leakcheck==yes
