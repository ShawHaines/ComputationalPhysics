/************************ Pulse ***********************
 - - intialize two laser pulses with 6 shape choises:
		1) sin^2(PI*t/T)		FWHM=0.364T
		2) sin^4(PI*t/T)		FWHM=0.26T, close to Gaussian
		3) exp(-t^2/T^2)		FWHM=1.1774T
		4) a0; 
		5) tanh(t/T)				rising time ~=3T
		6) tanh^2(t/T)			rising time ~=3T, gentler
 - - 1st pulse is always injected from left boundary
 - - 2nd pulse can be varied with frequency & direciton
*******************************************************/
#include "jpic.h"

void
Pulse(double t)
{
  int Q_s1=0,Q_p1=0;
  double t1,t2,phase,env_1,env_2;

	t1=t-delay_1;
	t2=t-delay_2;

/********* 1st pulse **********/
	if(a0_1){
		if(shape_1==1){
			if(t1>=0.0&&t1<=duration_1)
				env_1=a0_1*pow(sin(PI*t1/duration_1),2.0);
			else	env_1=0.0;
			phase=TWOPI*(t1-0.5*duration_1)+phase_1;
		}
		else if(shape_1==2){
			if(t1>=0.0&&t1<=duration_1)
				env_1=a0_1*pow(sin(PI*t1/duration_1),4.0);
			else	env_1=0.0;
			phase=TWOPI*(t1-0.5*duration_1)+phase_1;
		}
		else if(shape_1==3){
			if(t1>=0.0&&t1<=6.0*duration_1)
				env_1=a0_1*exp(-pow((t1-3.0*duration_1)/duration_1,2.0));
			else	env_1=0.0;
			phase=TWOPI*(t1-3.0*duration_1)+phase_1;
		}
		else if(shape_1==4){
			if(t1>=0.0&&t1<=duration_1)
				env_1=a0_1;
			else	env_1=0.0;
			phase=TWOPI*t1+phase_1;
		}
		else if(shape_1==5){
			if(t1>=0.0)
				env_1=a0_1*tanh(t1/duration_1);
			else	env_1=0.0;
			phase=TWOPI*t1+phase_1;
		}
		else if(shape_1==6){
			if(t1>=0.0)
				env_1=a0_1*pow(tanh(t1/duration_1),2.0);
			else	env_1=0.0;
			phase=TWOPI*t1+phase_1;
		}
		else if(shape_1==7){
			if(t1>=0.0&&t1<=duration_1/2.0)
				env_1=a0_1*pow(sin(PI*t1/duration_1),2.0);
			else if(t1>duration_1/2.0&&t1<=duration_1/2.0+flat_1)
				env_1=a0_1;
			else if(t1>duration_1/2.0+flat_1&&t1<=duration_1+flat_1)
				env_1=a0_1*pow(sin(PI*(t1-flat_1)/duration_1),2.0);
			else	env_1=0.0;
			phase=TWOPI*(t1-0.5*duration_1)+phase_1;
		}

	/******** polarization ***********/
		if(polar_1==1){     /* p-polarization */
			Q_p1=1;
			//pr[0] =env_1*cos(phase);
			pl[nc]=env_1*cos(phase);
		}
		else if(polar_1==2){  /* s-polarization */
			Q_s1=1;
			sr[0] =env_1*cos(phase);
		}
		else if(polar_1==3){  /* circular polarization  */
			Q_p1=1;
			Q_s1=1;
			pr[0] =env_1*cos(phase);
			sr[0] =env_1*sin(phase);
		}
	}

/********* 2nd pulse **********/
	if(a0_2){
		if(shape_2==1){
			if(t2>=0.0&&t2<=duration_2)
				env_2=a0_2*pow(sin(PI*t2/duration_2),2.0);
			else	env_2=0.0;
			phase=TWOPI*(t2-0.5*duration_2)*omega_2+phase_2;
		}
		else if(shape_2==2){
			if(t2>=0.0&&t2<=duration_2)
				env_2=a0_2*pow(sin(PI*t2/duration_2),4.0);
			else	env_2=0.0;
			phase=TWOPI*(t2-0.5*duration_2)*omega_2+phase_2;
		}
		else if(shape_2==3){
			if(t2>=0.0&&t2<=6.0*duration_2)
				env_2=a0_2*exp(-pow((t2-3.0*duration_2)/duration_2,2.0));
			else	env_2=0.0;
			phase=TWOPI*(t2-3.0*duration_2)*omega_2+phase_2;
		}
		else if(shape_2==4){
			if(t2>=0.0&&t2<=duration_2)
				env_2=a0_2;
			else	env_2=0.0;
			phase=TWOPI*t2*omega_2+phase_2;
		}
		else if(shape_2==5){
			if(t2>=0.0)
				env_2=a0_2*tanh(t2/duration_2);
			else	env_2=0.0;
			phase=TWOPI*t2*omega_2+phase_2;
		}
		else if(shape_2==6){
			if(t2>=0.0)
				env_2=a0_2*pow(tanh(t2/duration_2),2.0);
			else	env_2=0.0;
			phase=TWOPI*t2*omega_2+phase_2;
		}

	/******** polarization ***********/
		if(polar_2==1){     /* p-polarization */
			pr[0] =0.5*(1.0+dir_2)*env_2*cos(phase)+Q_p1*pr[0];
			pl[nc]=0.5*(1.0-dir_2)*env_2*cos(phase);
		}
		else if(polar_2==2){  /* s-polarization */
			sr[0] =0.5*(1.0+dir_2)*env_2*cos(phase)+Q_s1*sr[0];
			sl[nc]=0.5*(1.0-dir_2)*env_2*cos(phase);
		}
		else if(polar_2==3){  /* circular polarization  */
			pr[0] =0.5*(1.0+dir_2)*env_2*cos(phase)+Q_p1*pr[0];
			sr[0] =0.5*(1.0+dir_2)*env_2*sin(phase)+Q_s1*sr[0];
			pl[nc]=0.5*(1.0-dir_2)*env_2*cos(phase);
			sl[nc]=0.5*(1.0-dir_2)*env_2*sin(phase);
		}
	}

}
/********* end of pulse() ***********/
