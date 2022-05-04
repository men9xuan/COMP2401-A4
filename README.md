## Rapidly-exploring Random Tree (RRT) generator


This program generates a RRT which avoids obsticles from a given environment and traces a path from root to the closest node in the tree to a given (x,y) coordinate.

![Screenshots for 5 environments ](https://github.com/men9xuan/COMP2401-A4/raw/main/screenshots.gif | width=200)

### Compile Instructions:

make

### Run Instructions:

```./rrtTester \<growthLength\> \<maxNodes\> \<enviromentVariable\>```
  
  > growthLength:  the edge growth length for each tree branch
  
  > maxNodes: the maximum number of tree nodes to create
  
  > enviromentVariable: the environment number to test \[1-5\]

Sample run instruction:

```./rrtTester 25 200 1 ```
