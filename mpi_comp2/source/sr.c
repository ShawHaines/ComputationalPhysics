#include "pic.h"

int
SR( )

{
	int tag_emp=1;

	MPI_Status	status;
	
	/*发送emp[I_rank+1]到右进程*/
	if (my_rank<num_rank-1){
		rank_right=my_rank+1;
		MPI_Send(&emp[I_rank+1],1,MPI_DOUBLE,rank_right,tag_emp,MPI_COMM_WORLD);
	}

	/*接受左进程的emp[I_rank+1]*/	
	if (my_rank>0){
		rank_left=my_rank-1;
		MPI_Recv(&emp[0],1,MPI_DOUBLE,rank_left,tag_emp,MPI_COMM_WORLD,&status);
	}
		

	return(0);
}	
/****************** end of main() *************************/









