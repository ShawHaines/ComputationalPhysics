#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
				  
#if defined(GLOBALORIGIN)
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL double  *emp;
GLOBAL int my_rank,num_rank,rank_left,rank_right,I_rank;
GLOBAL char  file1[100];
GLOBAL FILE  *fp;

#undef GLOBAL









