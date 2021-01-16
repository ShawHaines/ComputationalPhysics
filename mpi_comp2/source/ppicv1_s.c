#define GLOBALORIGIN
#include "pic.h"
#undef GLOBALORIGIN
#include "nrutil.c"
#include "sr.c"


int
main(argc,argv)
int	argc;
char *argv[];
{
	int i,n=0,I=800;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&num_rank); // totally 8 ranks

	if(my_rank==0)	printf(">> Total_rank_num= %d\n",num_rank);

	I_rank=I/num_rank;
	emp=dvector(0,I_rank+1);

	for(i=0;i<=I_rank+1;i++) emp[i]=0.0;

	//初始化三角波
	if(my_rank==0){
		for(i=25;i<50;i++)  emp[i]=(i-25.0)/25.0;
		for(i=50;i<=75;i++) emp[i]=1.0-(i-50.0)/25.0;
	}

	//输出初始值
	if(my_rank==0)	printf("n = %03d\n",n);
	sprintf(file1,"data/emp_%03d_%d.txt",0,my_rank);
	fp=fopen(file1,"w");
	for(i=1;i<=I_rank;i++) 	fprintf(fp,"%03d%10.5f\n",i+my_rank*I_rank,emp[i]);
	fclose(fp);


	for(n=1;n<=700;n++){

		//向右移动
		for(i=I_rank;i>=0;i--) 	emp[i+1]=emp[i];

		//发送接收
		SR();

		//输出数据
		if(n%10==0){
			if(my_rank==0)	printf("n = %03d\n",n);
			sprintf(file1,"data/emp_%03d_%d.txt",n,my_rank);
			fp=fopen(file1,"w");
			for(i=1;i<=I_rank;i++) 	fprintf(fp,"%03d%10.5f\n",i+my_rank*I_rank,emp[i]);
			fclose(fp);
		}		
	}

	if(my_rank==0)	printf("Job done!\n");	
	MPI_Finalize();
	return(0);
}	
/****************** end of main() *************************/









