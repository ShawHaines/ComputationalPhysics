/********************** Creator ********************
 - - load particles: set initial position & mementum 
***************************************************/
#include "jpic.h"

Creator(isp)
int isp;
{
  int		i,ii,iq;
  double fnc_lramp,fnc_rramp,frand(),df,fv,dp,pp,pmax;
	void	Transform(),Smear();

	zn[isp]=den0*sign(qs[isp])/np_cell_max*pow(Gamm,3.0);/* correction for boost frame */
	printf(" Creator: np_cell_max=%f,zn[%d]=%.2e\n\n",np_cell_max,isp,zn[isp]);

/************ initialize the particle velocities *****************/
/********* the following initialization taken from Birdsall *****/

   if(temperature[isp]){
    pmax=5.0*sqrt(temperature[isp]/ms[isp]);
    dp=2.0*pmax/(double)np0;
    xpos[isp][0]=0.0;
    for(i=1; i<np0;i++){
      pp=((double)i-0.5)*dp-pmax;
      fv=exp(-pp*pp*ms[isp]/(2.0*temperature[isp]));
      xpos[isp][i]=xpos[isp][i-1]+max(fv,0.0);
    }
    df=xpos[isp][np0-1]/(double)np0;
    iq=0;
    for(i=0; i<np0; i++){
      fv=((double)i+0.5)*df;
      while(fv>=xpos[isp][iq+1]){
				iq++;
				if(iq>(np0-2)){
					printf("Distribution Function f(p) Error");
					exit(1);
				}
			}
      px[isp][i]=py[isp][i]=pz[isp][i]=dp*((double)iq+
				(fv-xpos[isp][iq])/(xpos[isp][iq+1]-xpos[isp][iq]))-pmax;
    }
  }

/******** linear ramp + flat + linear ramp *****/
	if(ramp_prof==0){
		fnc_lramp=0.5*nc_lramp;
		fnc_rramp=0.5*nc_rramp;
		
		np_lramp=(int)(np_cell_max*fnc_lramp);
		np_rramp=(int)(np_cell_max*fnc_rramp);
		np_flat=np0-np_lramp-np_rramp;

		for(i=0;i<np0;i++){
			if(i<np_lramp)
	 			xpos[isp][i]=nc_vac+sqrt((double)i/(double)(np_lramp-1))*nc_lramp-0.5*dx;
			else if (i<np_lramp+np_rramp){
				ii=i-np_lramp;
				xpos[isp][i]=nc_vac+nc_lramp+nc_flat+(1.0-sqrt(1.0-(double)ii/(double)(np_rramp-1)))*nc_rramp+0.5*dx;
			}
			else{
				ii=i-np_lramp-np_rramp;
	 			xpos[isp][i]=nc_vac+nc_lramp+(0.5+(double)ii)/(double)np_flat*nc_flat;
			}
		}
	}

/******** exponential ramp + flat + exponential ramp *****/
	if(ramp_prof==1){
    fnc_lramp=exp_scale*(1.0-exp(-nc_lramp/exp_scale));
		fnc_rramp=exp_scale*(1.0-exp(-nc_rramp/exp_scale));

    np_lramp=(int)(np_cell_max*fnc_lramp);
		np_rramp=(int)(np_cell_max*fnc_rramp);
		np_flat=np0-np_lramp-np_rramp;

		for(i=0;i<np0;i++){
      if(i<np_lramp)
				xpos[isp][i]=nc_vac+exp_scale*log((double)i/(double)(np_lramp-1)*(exp(nc_lramp/exp_scale)-1.0)+1.0)-0.5*dx;
			else if (i<np_lramp+np_rramp){
				ii=i-np_lramp;
				xpos[isp][i]=nc_vac+nc_lramp+nc_flat-exp_scale*log((double)ii/(double)(np_rramp-1)*(exp(-nc_rramp/exp_scale)-1.0)+1.0)+0.5*dx;
			}
			else{
				ii=i-np_lramp-np_rramp;
	 			xpos[isp][i]=nc_vac+nc_lramp+(0.5+(double)ii)/(double)np_flat*nc_flat;
			}
			}
		}

  Smear(isp); /* randomize particle velocity and momentum */

  if(angle) 
		Transform(isp); /* Lorenz transform to moving frame */

	for(i=0;i<np0;i++){
		px[isp][i]=sqrt(pow(RES_gamma0,2.0)-1.0);
		py[isp][i]=0.0;
		pz[isp][i]=0.0;
		gamm[isp][i]=sqrt(1.0+pow(px[isp][i],2.0)+pow(py[isp][i],2.0)+pow(pz[isp][i],2.0));
	}

}
/********* end of creator() *********/


/* random number generator [0,1]: following Birdsall's */

double
frand()
{
  long a=16807, m=2147483647, q=127773, r=2836;
  long low, high;
  static long seed=31207321;
  double fnumb;

  high=seed/q;
  low=seed-q*high;
  seed=a*low-r*high;
  if(seed<=0) seed=seed+m;
  fnumb=(double)seed/2147483646.0;

  return(fnumb);
}


/********** smear particles ****/
void
Smear(isp)
int isp;
{
  int	i,ii;
	double x0,px0,py0,pz0;

  for(i=0; i<np0; i++){
    ii           =(int)(np0*frand());
    x0           =xpos[isp][i];
    xpos[isp][i] =xpos[isp][ii];
    xpos[isp][ii]=x0;
    ii           =(int)(np0*frand());
    px0          =px[isp][i];
    px[isp][i]   =px[isp][ii];
    px[isp][ii]  =px0;
    ii           =(int)(np0*frand());
    py0          =py[isp][i];
    py[isp][i]   =py[isp][ii];
    py[isp][ii]  =py0;
    ii           =(int)(np0*frand());
    pz0          =pz[isp][i];
    pz[isp][i]   =pz[isp][ii];
    pz[isp][ii]  =pz0;
  }
}

/**** end of smear() ****/


/******* Lorentz transform *********/
void
Transform(int isp)
{
  int i;
	double gamma0;
  for(i=0; i<np0; i++){
		gamma0=sqrt(1.0+pow(px[isp][i],2.0)+pow(py[isp][i],2.0)+pow(pz[isp][i],2.0));
    py[isp][i]=Gamm*(py[isp][i]-Beta*gamma0);
		}
	}

/******* end of transform() ******/
