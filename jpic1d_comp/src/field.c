/********************* Field **********************
 - - update fields from currents and charge density
**************************************************/
#include "jpic.h"
#include "pulse.c"

void
Field()
{
  int	j;
	double norm_dt,norm_dt2,norm_dx2;

	norm_dt =dt*PI;
	norm_dt2=dt*TWOPI;
	norm_dx2=dx*TWOPI;

/***** input pulse *******/
  Pulse(t);

/******** EB(n)+J(n+1/2)->EB(n+1) ********/
	for(j=0;j<ng;j++) ex[j]-=jx[j]*norm_dt2;
	for(j=nc;j>0;j--){
		pr[j]=pr[j-1]-jy[j-1]*norm_dt;
    sr[j]=sr[j-1]-jz[j-1]*norm_dt;
  }
	for(j=0;j<nc;j++){
    pl[j]=pl[j+1]-jy[j]*norm_dt;
    sl[j]=sl[j+1]-jz[j]*norm_dt;
  }

/******** rho(n+1)->Exx(n+1) ********/
  for(j=0;j<nc;j++) 
		exx[j+1]=exx[j]+rho[j]*norm_dx2;

/*** pl,pr,sl,sr->ey,bz,ez,by ***/
  for(j=0;j<ng;j++){
		ey[j]=pr[j]+pl[j];
    bz[j]=pr[j]-pl[j];
    ez[j]=sl[j]+sr[j];
    by[j]=sl[j]-sr[j];
  } 

/* input & output laser energy through sim. box boundary */
  prsr_in		+=pr[0]*pr[0]+sr[0]*sr[0];
  prsr_out	+=pr[nc]*pr[nc]+sr[nc]*sr[nc];
	plsl_in		+=pl[nc]*pl[nc]+sl[nc]*sl[nc];
	plsl_out	+=pl[0]*pl[0]+sl[0]*sl[0];

}
/******* end of field() ********/
