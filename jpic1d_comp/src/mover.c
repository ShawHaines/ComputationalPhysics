/********************* Mover ********************
 - - 1.move particles by Lorentz force
 - - 2.update position & momentum
 - - 3.update current & charge density by new 2 
*************************************************/
#include "jpic.h"

void
Mover(isp)
int isp;
{
  int i,j,j_new;
  double norm_den,norm_rho,fnc;
  double afield,delta0,delta1,deltan,delta_new,exp,eyp,ezp,byp,bzp,vx,vy,vz;
/********************* fields at particle positions ***************/
  double px1,py1,pz1,gm1,ty,tz,tt,sy,sz,px2,py2,pz2;
  double xpos_new,displace,dj,dj_new,eps,f1,f2,f3,f4,f5,frand(),ran1,ran2,ran3;

  norm_den=fabs(zn[isp]/qs[isp]);
  norm_rho=zn[isp];
  fnc=(double)nc;
  afield=qs[isp]/ms[isp]*dt*PI;

  for(j=0;j<ng;j++)   den[isp][j]=jx2[isp][j]=0.0;
	for(j=0;j<nc;j++)  rho2[isp][j]=jy2[isp][j]=jz2[isp][j]=0.0;

/*********** begin of loop for particle ***********/
/*********  P(n-1/2)+EB(n)->P(n+1/2) *******/
/*********  P(n+1/2)+xpos(n)->xpos(n+1) *******/
  for(i=0;i<np0;i++){
    j=(int)xpos[isp][i];
		dj=(double)j;
    delta0=xpos[isp][i]-dj;
		delta1=1.0-delta0;

	//exp=afield*(delta0*exx[j+1]+delta1*exx[j]);
    //exp=afield*(delta0*ex[j+1]+delta1*ex[j]);
	exp=0.0;
    eyp=afield*(delta0*ey[j+1]+delta1*ey[j]);
    ezp=afield*(delta0*ez[j+1]+delta1*ez[j]);
    byp=afield*(delta0*by[j+1]+delta1*by[j]);
    bzp=afield*(delta0*bz[j+1]+delta1*bz[j]);

    vx=px[isp][i]/gamm[isp][i];
    vy=py[isp][i]/gamm[isp][i];
    vz=pz[isp][i]/gamm[isp][i];
    gamm1[isp][i]+=exp*vx;				/* 0.5*E[n]*V[n-1/2] */
    gamm2[isp][i]+=eyp*vy+ezp*vz;

  /****** half acceleration ******/
    px1=px[isp][i]+exp;
    py1=py[isp][i]+eyp;
    pz1=pz[isp][i]+ezp;
    gm1=sqrt(1.0+px1*px1+py1*py1+pz1*pz1);

  /****** rotation **********/
    ty=byp/gm1;
    tz=bzp/gm1;
    tt=2.0/(1.0+ty*ty+tz*tz);
    sy=ty*tt;
    sz=tz*tt;

    px2=(1.0-sz*tz-sy*ty)*px1 +          sz*py1    -          sy*pz1;
    py2=              -sz*px1 + (1.0-sz*tz)*py1    +       sz*ty*pz1;
    pz2=               sy*px1 +       sy*tz*py1    + (1.0-sy*ty)*pz1;

  /*****half acceleration ******/
    px[isp][i]=px2+exp;
    py[isp][i]=py2+eyp;
    pz[isp][i]=pz2+ezp;
    gamm[isp][i]=sqrt(1.0+pow(px[isp][i],2.0)+pow(py[isp][i],2.0)+pow(pz[isp][i],2.0));

    vx=px[isp][i]/gamm[isp][i];
    vy=py[isp][i]/gamm[isp][i];
    vz=pz[isp][i]/gamm[isp][i];
		gamm1[isp][i]+=exp*vx;				/* 0.5*E[n]*V[n+1/2] */
    gamm2[isp][i]+=eyp*vy+ezp*vz;

    xpos_new=xpos[isp][i]+vx;

/******** reflection boundaries at grid points: 1.5 and nc-1.5 ***********
    if(xpos_new<1.5) {
      xpos_new=3.0-xpos_new;
      ran1=frand();      // reflection with thermal velocity 
      ran2=frand();
      ran3=frand();
      px[isp][i]=fabs(sqrt(-temperature[isp]*log(ran1))*cos(TWOPI*ran2));
      py[isp][i]=sqrt(-temperature[isp]*log(ran1))*cos(TWOPI*ran3);
      pz[isp][i]=sqrt(-temperature[isp]*log(ran1))*sin(TWOPI*ran3);
      gamm[isp][i]=sqrt(1.0+pow(px[isp][i],2.0)+pow(py[isp][i],2.0)+pow(pz[isp][i],2.0));
			vx=px[isp][i]/gamm[isp][i];
			vy=py[isp][i]/gamm[isp][i];
			vz=pz[isp][i]/gamm[isp][i];
    }
    if(xpos_new>=(fnc-1.5)) {
      xpos_new=2.0*(fnc-1.5)-xpos_new;
      ran1=frand();      // reflection with thermal velocity 
      ran2=frand();
      ran3=frand();
      px[isp][i]=-fabs(sqrt(-temperature[isp]*log(ran1))*cos(TWOPI*ran2));
      py[isp][i]=sqrt(-temperature[isp]*log(ran1))*cos(TWOPI*ran3);
      pz[isp][i]=sqrt(-temperature[isp]*log(ran1))*sin(TWOPI*ran3);
      gamm[isp][i]=sqrt(1.0+pow(px[isp][i],2.0)+pow(py[isp][i],2.0)+pow(pz[isp][i],2.0));
			vx=px[isp][i]/gamm[isp][i];
			vy=py[isp][i]/gamm[isp][i];
			vz=pz[isp][i]/gamm[isp][i];
    }*/

/********* xpos(n+1)->rho(n+1),den(n+1) *******/
		j_new=(int)xpos_new;
    dj_new=(double)j_new;
    delta_new=xpos_new-dj_new;
    if(xpos_new<dj_new+0.5){
      rho2[isp][j_new]  +=0.5+delta_new;	// normalized later
      rho2[isp][j_new-1]+=0.5-delta_new;
    }
    if(xpos_new>=dj_new+0.5){
      rho2[isp][j_new]  +=1.5-delta_new;
      rho2[isp][j_new+1]+=delta_new-0.5;
    }
    den[isp][j_new]  +=1.0-delta_new;			// normalized later
    den[isp][j_new+1]+=delta_new;

/* xpos(n)+xpos(n+1)+vy,vz(n+1/2)->Jx,Jy,Jz(n+1/2) */
		displace=xpos_new-xpos[isp][i];
		deltan=xpos_new-dj;
		if(xpos[isp][i]<dj+0.5){ // first three cases
			if(xpos_new>=dj-0.5&&xpos_new<dj+0.5){
				f1=displace;
				f2=0.5*(1.0+delta0+deltan);
				f3=1.0-f2;
				jx2[isp][j]	  +=f1;						// normalized later
				jy2[isp][j]	  +=f2*vy;
				jy2[isp][j-1] +=f3*vy;
				jz2[isp][j]	  +=f2*vz;
				jz2[isp][j-1] +=f3*vz;
			}
			else if(xpos_new<dj-0.5){
				eps=-(delta0+0.5)/displace;
				f1=-0.5-delta0;
				f2=displace-f1;
				f3=-0.5*eps*f1;
				f4=-0.5*(1.0-eps)*f2;
				f5=1.0-f3-f4;
				jx2[isp][j]		+=f1;
				jx2[isp][j-1]	+=f2;
				jy2[isp][j]		+=f3*vy;
				jy2[isp][j-2]	+=f4*vy;
				jy2[isp][j-1]	+=f5*vy;
				jz2[isp][j]		+=f3*vz;
				jz2[isp][j-2]	+=f4*vz;
				jz2[isp][j-1]	+=f5*vz;
			}
			else if(xpos_new>=dj+0.5){	
				eps=-(delta0-0.5)/displace;
				f1=0.5-delta0;
				f2=displace-f1;
				f3=0.5*eps*f1;
				f4=0.5*(1.0-eps)*f2;
				f5=1.0-f3-f4;
				jx2[isp][j]		+=f1;
				jx2[isp][j+1]	+=f2;
				jy2[isp][j-1]	+=f3*vy;
				jy2[isp][j+1]	+=f4*vy;
				jy2[isp][j]		+=f5*vy;
				jz2[isp][j-1]	+=f3*vz;
				jz2[isp][j+1]	+=f4*vz;
				jz2[isp][j]		+=f5*vz;
      }
    }
    else {  /* second three-cases */
      if(xpos_new>=dj+0.5&&xpos_new<dj+1.5){
				f1=displace;
				f2=0.5*(3.0-delta0-deltan);
				f3=1.0-f2;
				jx2[isp][j+1]	+=f1;
				jy2[isp][j]		+=f2*vy;
				jy2[isp][j+1]	+=f3*vy;
				jz2[isp][j]		+=f2*vz;
				jz2[isp][j+1]	+=f3*vz;
      }
      else if(xpos_new>=dj+1.5){
				eps=-(delta0-1.5)/displace;
				f1=1.5-delta0;
				f2=displace-f1;
				f3=0.5*eps*f1;
				f4=0.5*(1.0-eps)*f2;
				f5=1.0-f3-f4;
				jx2[isp][j+1]	+=f1;
				jx2[isp][j+2]	+=f2;
				jy2[isp][j]		+=f3*vy;
				jy2[isp][j+2]	+=f4*vy;
				jy2[isp][j+1]	+=f5*vy;
				jz2[isp][j]		+=f3*vz;
				jz2[isp][j+2]	+=f4*vz;
				jz2[isp][j+1]	+=f5*vz;
      }
      else if(xpos_new<dj+0.5){	
				eps=-(delta0-0.5)/displace;
				f1=0.5-delta0;
				f2=displace-f1;
				f3=-0.5*eps*f1;
				f4=-0.5*(1.0-eps)*f2;
				f5=1.0-f3-f4;
				jx2[isp][j+1]	+=f1;
				jx2[isp][j]		+=f2;
				jy2[isp][j+1]	+=f3*vy;
				jy2[isp][j-1]	+=f4*vy;
				jy2[isp][j]		+=f5*vy;
				jz2[isp][j+1]	+=f3*vz;
				jz2[isp][j-1]	+=f4*vz;
				jz2[isp][j]		+=f5*vz;
      }
    }
    xpos[isp][i]=xpos_new;
  }

/*********** end of loop for particle ***********/
	/*** normalize ****/
  for(j=0;j<nc;j++){
    rho2[isp][j]*=norm_rho;
		 jy2[isp][j]*=norm_rho;
		 jz2[isp][j]*=norm_rho;
	}
	for(j=0;j<ng;j++){
		jx2[isp][j]*=norm_rho;
    den[isp][j]*=norm_den;
	}

	/*** final J,rho for fixed ion ***/
	if(!i_move){
		for(j=0;j<nc;j++){
			rho[j]=rho2[0][j]+rhoi[j];			// ion charge
			 jy[j]=jy2[0][j]-rhoi[j]*Beta;	// ion current
			 jz[j]=jz2[0][j];
		}
		for(j=0;j<ng;j++)
			jx[j]=jx2[0][j];

		if(angle){// get electron-jy and ion-jy on cell boundary for oblique incidence case (only for diagnosis)
			if(Q_trace_dj||(Q_spacetime&&counter_times%nstep_spt==0)||(Q_snapshot&&counter_times%nstep_ss==0)){
				for(j=1;j<nc;j++){
					jye[j]=0.5*(jy2[0][j]+jy2[0][j-1]);
					jyi[j]=-0.5*(rhoi[j]+rhoi[j-1])*Beta;
				}
				jye[0] = 0.5*jy2[0][0];
				jye[nc]= 0.5*jy2[0][nc-1];
				jyi[0] =-0.5*rhoi[0]*Beta;			
				jyi[nc]=-0.5*rhoi[nc-1]*Beta;
			}
		}
  }
	
	/*** final J,rho for movable ion ***/
	if(i_move&&isp==1){
		for(j=0;j<nc;j++){
			rho[j]=rho2[0][j]+rho2[1][j];
			 jy[j]=jy2[0][j]+jy2[1][j];
			 jz[j]=jz2[0][j]+jz2[1][j];
		}
		for(j=0;j<ng;j++)
			jx[j]=jx2[0][j]+jx2[1][j];

		if(angle){// get electron-jy and ion-jy on cell boundary for oblique incidence case (only for diagnosis)
			if(Q_trace_dj||(Q_spacetime&&counter_times%nstep_spt==0)||(Q_snapshot&&counter_times%nstep_ss==0)){
				for(j=1;j<nc;j++){
					jye[j]=0.5*(jy2[0][j]+jy2[0][j-1]);
					jyi[j]=0.5*(jy2[1][j]+jy2[1][j-1]);
				}
				jye[0] =0.5*jy2[0][0];
				jye[nc]=0.5*jy2[0][nc-1];
				jyi[0] =0.5*jy2[1][0];
				jyi[nc]=0.5*jy2[1][nc-1];
			}
		}
  }

}
/******** end of mover() ********/
