/************ Setrho ***********
 - - get initial charge density
********************************/
#include "jpic.h"

Setrho(int isp)
{
  int i,j;
  double norm_den,norm_rho,dj,delta;

  norm_den=fabs(zn[isp]/qs[isp]);
  norm_rho=zn[isp];

  for(i=0;i<np0;i++){
    j=(int)xpos[isp][i];
    dj=(double)j;
    delta=xpos[isp][i]-dj;
    if(xpos[isp][i]<(dj+0.5)){
      rho[j]  +=(0.5+delta)*norm_rho;
      rho[j-1]+=(0.5-delta)*norm_rho;
    }
    if(xpos[isp][i]>=(dj+0.5)){
      rho[j]  +=(1.5-delta)*norm_rho;
      rho[j+1]+=(delta-0.5)*norm_rho;
    }
    den[isp][j]  +=(1.0-delta)*norm_den;
    den[isp][j+1]+=delta*norm_den;
  }
	
	if(!i_move){
		for(j=0;j<nc;j++){
			rhoi[j]=-rho[j];
			rho[j]+=rhoi[j];
		}
		for(j=0;j<ng;j++)
			deni[j]=den[0][j]/qs[1];
	}

}
/****** end of setrho() ******/


/******** get simualtion time in minute *********/
double
Timer()
{
	int second1;
	double minute;

	second1=time(NULL);
	minute=(second1-second0)/60.0;
	return(minute);
}
