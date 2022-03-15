#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

#include "obstacles.h"
#include "display.h"

// This is a helper function that determines whether or not line segment (v1---v2) intersects line segment (v3---v4)
unsigned char linesIntersect(short v1x, short v1y, short v2x, short v2y, short v3x, short v3y, short v4x, short v4y)
{
	float uA = ((v4x - v3x) * (v1y - v3y) - (v4y - v3y) * (v1x - v3x)) / (float)(((v4y - v3y) * (v2x - v1x) - (v4x - v3x) * (v2y - v1y)));
	float uB = ((v2x - v1x) * (v1y - v3y) - (v2y - v1y) * (v1x - v3x)) / (float)(((v4y - v3y) * (v2x - v1x) - (v4x - v3x) * (v2y - v1y)));

	// If uA and uB are between 0-1, there is an intersection
	if (uA > 0 && uA < 1 && uB > 0 && uB < 1)
		return 1;

	return 0;
}

// helper function to see if (x,y) is inside obstacles
unsigned char insideObstacles(unsigned short x, unsigned short y, Environment *env)
{
	unsigned short a, b, w, h;
	for (int i = 0; i < (env->numObstacles); i++)
	{
		a = env->obstacles[i].x;
		b = env->obstacles[i].y;
		w = env->obstacles[i].w;
		h = env->obstacles[i].h;
		if (x <= (a + w) && x >= a && y <= b && y >= (b - h))
		{
			return 1;
		}
	}
	return 0;
}

// check if line(x1,y1) - (x2,y2) intersects any object
unsigned char intersectObstacles(unsigned x1, unsigned y1, unsigned x2, unsigned y2, Environment *env)
{
	unsigned short x, y, w, h;
	for (int i = 0; i < (env->numObstacles); i++)
	{
		// printf("i: %d\n", i);
		x = env->obstacles[i].x;
		y = env->obstacles[i].y;
		w = env->obstacles[i].w;
		h = env->obstacles[i].h;
		// linesIntersect( v1x,  v1y,  v2x,  v2y,  v3x,  v3y,  v4x,  v4y)
		if (linesIntersect(x1, y1, x2, y2, x, y, w + x, y))
			return 1;
		if (linesIntersect(x1, y1, x2, y2, w + x, y, w + x, y - h))
			return 1;
		if (linesIntersect(x1, y1, x2, y2, w + x, y - h, x, y - h))
			return 1;
		if (linesIntersect(x1, y1, x2, y2, x, y - h, x, y))
			return 1;
	}
	return 0;
}

// helper function to generate (x,y) that is not inside obstacle
void generatePoint(unsigned short *x, unsigned short *y, Environment *env)
{

	unsigned short x1 = rand() % (env->maximumX);
	unsigned short y1 = rand() % (env->maximumY);
	while (insideObstacles(x1, y1, env) == 1)
	{
		// x1 = rand() % ((env->maximumX) - (env->startX) + 1) + (env->startX);
		// y1 = rand() % ((env->maximumY) - (env->startY) + 1) + (env->startY);
		x1 = rand() % (env->maximumX);
		y1 = rand() % (env->maximumY);
	}
	*x = x1;
	*y = y1;
}

TreeNode *findClosest(unsigned short x, unsigned short y, Environment *env)
{
	TreeNode *closetNode = NULL;
	int minDist = INT_MAX;
	int dist;
	for (int i = 0; i < (env->numNodes) && (env->rrt[i] != NULL); i++)
	{
		dist = ((env->rrt[i]->x) - x) * ((env->rrt[i]->x) - x) + ((env->rrt[i]->y) - y) * ((env->rrt[i]->y) - y);
		if (dist < minDist)
		{
			minDist = dist;
			closetNode = env->rrt[i];
		}
	}
	// exit(1);
	return closetNode;
}

// Create a rrt using the growthAmount and maximumNodes parameters in the given environment.
void createRRT(Environment *env)
{
	TreeNode **newRRT = NULL;
	newRRT = (TreeNode **)malloc(sizeof(TreeNode *) * (env->maximumNodes));
	printf("env->maximumNodes %d \n", env->maximumNodes);
	if (newRRT == NULL)
	{
		printf("error: could not allocate memory for rrt\n");
		exit(1);
	}
	for (int i = 0; i < (env->maximumNodes); i++)
	{
		newRRT[i] = NULL;
	}

	for (int i = 0; i < (env->maximumNodes); i++)
	{
		newRRT[i] = (TreeNode *)malloc(sizeof(TreeNode));
		if (newRRT[i] == NULL)
		{
			printf("error: could not allocate memory for TreeNode\n");
			exit(1);
		}
	}

	env->rrt = newRRT;
	newRRT[0]->parent = NULL;
	newRRT[0]->x = env->startX;
	newRRT[0]->y = env->startY;
	newRRT[0]->firstChild = NULL;
	env->numNodes = 1;
	unsigned short qx, qy, cx, cy;
	qx = qy = cx = cy = 0;
	srand(time(NULL));
	while ((env->numNodes) < (env->maximumNodes))
	{
		generatePoint(&qx, &qy, env);
		// printf("qx: %d\n qy:%d\n", qx, qy);
		TreeNode *n = findClosest(qx, qy, env);
		double angle = atan2(qy - (n->y), qx - (n->x));
		cx = n->x + cos(angle) * env->growthAmount;
		cy = n->y + sin(angle) * env->growthAmount;
		if (intersectObstacles(n->x, n->y, cx, cy, env) == 0)
		// if (intersectObstacles(qx, qy, cx, cy, env) == 0)

		{
			// double angle = atan2(qy - (n->y), qx - (n->x));
			// cx = n->x + cos(angle) * env->growthAmount;
			// cy = n->y + sin(angle) * env->growthAmount;

			/*add(x, y) to rrt */
			newRRT[env->numNodes]->parent = n;
			newRRT[env->numNodes]->x = cx;
			newRRT[env->numNodes]->y = cy;
			newRRT[env->numNodes]->firstChild = NULL;
			TreeNode *node = newRRT[env->numNodes];
			(env->numNodes)++;
			if (n->firstChild == NULL)
			{
				n->firstChild = (Child *)malloc(sizeof(Child));
				n->firstChild->node = node;
				n->firstChild->nextSibling = NULL;
			}
			else
			{
				Child *prevChild = NULL;
				Child *currChild = n->firstChild;
				while (currChild != NULL)
				{
					prevChild = currChild;
					currChild = currChild->nextSibling;
				}
				Child *newChild = (Child *)malloc(sizeof(Child));
				newChild->node = node;
				newChild->nextSibling = NULL;
				prevChild->nextSibling = newChild;
			}
		}
	}
}

// Trace the path back from the node that is closest to the given (x,y) coordinate to the root
void tracePath(Environment *env, unsigned short x, unsigned short y)
{
}

// This procedure cleans up everything by creeing all alocated memory
void cleanupEverything(Environment *env)
{
	free(env->obstacles);
}
