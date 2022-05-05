## Rapidly-exploring Random Tree (RRT) generator


This program generates a RRT which avoids obsticles from a given environment and traces a path from root to the closest node in the tree to a given (x,y) coordinate.

### Screenshot:
<img src="https://github.com/men9xuan/Rapidly-exploring-Random-Tree/raw/main/screenshots.gif" width="500" >




### Compile Instructions:

```make```

### Run Instructions:

```./rrtTester \<growthLength\> \<maxNodes\> \<enviromentVariable\>```
  
  > growthLength:  the edge growth length for each tree branch
  
  > maxNodes: the maximum number of tree nodes to create
  
  > enviromentVariable: the environment number to test \[1-5\]

Sample run instruction:

```./rrtTester 25 200 1 ```
