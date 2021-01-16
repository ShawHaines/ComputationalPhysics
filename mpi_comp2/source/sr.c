#include "pic.h"

int
SR( )

{
	int tag_emp=1;

	MPI_Status	status;
	
	/*send emp[0] to left process*/
	if (my_rank>0){
		rank_left = my_rank - 1;
		MPI_Send(&emp[0],1,MPI_DOUBLE,rank_left,tag_emp,MPI_COMM_WORLD);
	}

	/*receive emp[0] from right process*/	
	if (my_rank<num_rank-1){
		rank_right=my_rank+1;
		MPI_Recv(&emp[I_rank+1],1,MPI_DOUBLE,rank_right,tag_emp,MPI_COMM_WORLD,&status);
	}

	return(0);
}	
/****************** end of main() *************************/









