/******************* Start ******************
 - - read input file
 - - allocate array, initialize variables
 - - calculate total particle number 
********************************************/
#include "jpic.h"
#include "readfile.c"

Start(argc, argv)
int argc;
char *argv[];
{
  char input_copy[name_length],input_filename[name_length];
  double qs0,ms0,qs1,ms1,temp0,temp1,fnc_lexp,fnc_rexp;
  int i,j,isp,np_exp_ramp;
	
/*********** Read data from input file "*.inp" **************************/
	
  if (argc<2)	printf("\n Missing the input filename!\n");
  else {
    strcpy(input_filename,argv[1]);
    openinput(input_filename);
  }
  den0=atof(setget("&flying_mirror_parameters","mirror_density"));
  RES_gamma0=atof(setget("&flying_mirror_parameters","mirror_gamma"));
  qs0=-1;
  ms0=1;
  qs1=1;
  ms1=1836;
  temp0=0;
  temp1=0;
  i_move=0;
  tstart_mover=5.0;

  np0_cell=10000;
  nc=5000;
  nc_per_wl=1000;
  nc_vac=0;
  nc_lramp=0;
  nc_flat=1;
  nc_rramp=0;
  ramp_prof=0;
  exp_scale=1;

	angle=0;
	a0_1=atof(setget("&laser_parameters","amplitude_1"));
	polar_1=1;
    shape_1=1;
	duration_1=10;
	flat_1=0;
	delay_1=0;
	phase_1=0;
  
	a0_2=0;
	dir_2=-1;
	polar_2=1;
  shape_2=1;
	duration_2=10;
	delay_2=0;
	omega_2=1;
	phase_2=0;

  t_stop=12.0;
  Q_snapshot=1;
  tstep_ss=1;
	Q_phasespace=0;
  tstep_ps=1;
	np_step=1;
	Q_trace_eb=1;
	tr1_eb=0;
    tr2_eb=5000;
    tr3_eb=2500;
	Q_trace_energy=0;
	tstep_en=1;
	Q_trace_dj=0;
  tr1_dj=1;
  tr2_dj=1;
  tr3_dj=1;
  Q_spacetime=0;
  tstep_spt=0.1;
  cell_start=0;
  cell_step=1;
  cell_stop=10;

  strcpy(path,setget("&output","path"));

  closeinput();
  sprintf(input_copy,"%s/input.lpi",path);
  copy_file(input_filename,input_copy);

  printf("\nLaser pulse parameters:\n");
  printf(" a0_1=%.2e\t duration_1=%.2f\n a0_2=%.2e\t duration_2=%.2f\n\n",a0_1,duration_1,a0_2,duration_2);
  printf("Plasma parameters:\n");
  printf(" density0=%.2eNc\n temperature_electron=%.2feV\n temperature_ion=%.2feV\n",den0,temp0,temp1);

  /********************Initializing other variables******************/
	second0=time(NULL);
	TWOPI=2.0*PI;
	angle*=PI/180.0;
	phase_1*=PI/180.0;
	phase_2*=PI/180.0;
	counter_times=0;
	plsl_in=0.0;
	plsl_out=0.0;
	prsr_in=0.0;
	prsr_out=0.0;

  t		 = 0.0;
  dx   = 1.0/(double)nc_per_wl;  /* in unit of laser wavelength in M frame */
  dt   = dx;                     /* in unit of laser period in M frame */
  Gamm = 1.0/cos(angle);
  Beta = sin(angle);

	if(angle){
		nc				=(int)((double)nc/Gamm);
		cell_start=(int)((double)cell_start/Gamm);
		cell_stop =(int)((double)cell_stop/Gamm);
		nc_vac		/=Gamm;
		nc_lramp	/=Gamm;
		nc_flat		/=Gamm;
		nc_rramp	/=Gamm;

		tr1_eb=(int)((double)tr1_eb/Gamm);
		tr2_eb=(int)((double)tr2_eb/Gamm);
		tr3_eb=(int)((double)tr3_eb/Gamm);
		tr1_dj=(int)((double)tr1_dj/Gamm);
		tr2_dj=(int)((double)tr2_dj/Gamm);
		tr3_dj=(int)((double)tr3_dj/Gamm);
	}

  nstep_en=(int)(tstep_en/dt+0.5);
  nstep_ss=(int)(tstep_ss/dt+0.5);
  nstep_ps=(int)(tstep_ps/dt+0.5);
  nstep_spt=(int)(tstep_spt/dt+0.5);
  
  printf(" nc=%d\n nc_vac=%.1f\n nc_lramp=%.1f\n nc_flat=%.1f\n nc_rramp=%.1f\n",
		nc,nc_vac,nc_lramp,nc_flat,nc_rramp);
  printf(" ramp profile (0=linear,1=expo)=%d\n",ramp_prof);

  ng=nc+1;
	np_flat=(int)(nc_flat*np0_cell);
  if(ramp_prof==1){
    fnc_lexp=(exp_scale/dx)*(1.0-exp(-(double)nc_lramp*dx/exp_scale));
		fnc_rexp=(exp_scale/dx)*(1.0-exp(-(double)nc_rramp*dx/exp_scale));
    np_exp_ramp=(int)((fnc_lexp+fnc_rexp)*(double)np0_cell);
    np0=np_flat+np_exp_ramp;
  }
  else {
    np_lramp=(int)((double)nc_lramp*np0_cell/2.0);
		np_rramp=(int)((double)nc_rramp*np0_cell/2.0);
    np0=np_flat+np_lramp+np_rramp;
  }
  printf(" np0=%d\n",np0);

/********** allocate array & matrix *********/
	
	if(!i_move) nsp=1;
	else				nsp=2;
  ms					= dvector(0,nsp-1);
  qs					= dvector(0,nsp-1);
  zn					= dvector(0,nsp-1);
  temperature = dvector(0,nsp-1);
	eng_ei			= dvector(0,nsp-1);

	jx2	= dmatrix(0,nsp-1,0,ng-1);
	jx	= dvector(0,ng-1);
  jy2	= dmatrix(0,nsp-1,0,nc-1);
	jy	= dvector(0,nc-1);
	if(angle){
		jye= dvector(0,ng-1); // interpolate jy_electron into cell boundary for oblique-incidence diagnosis
		jyi= dvector(0,ng-1); // interpolate jy_ion into cell boundary for oblique-incidence diagnosis
	}
	jz2	= dmatrix(0,nsp-1,0,nc-1);
  jz	= dvector(0,nc-1);
	rho2= dmatrix(0,nsp-1,0,nc-1);
  rho	= dvector(0,nc-1);
	rhoi= dvector(0,nc-1); // ion charge density,used for fixed ion case 
  ex 	= dvector(0,ng-1);
  exx = dvector(0,ng-1); // induced from rho
  ey 	= dvector(0,ng-1);
  ez 	= dvector(0,ng-1);
  by 	= dvector(0,ng-1);
  bz 	= dvector(0,ng-1);
  pl  = dvector(0,ng-1);
  pr  = dvector(0,ng-1);
  sl  = dvector(0,ng-1);
  sr  = dvector(0,ng-1);
	deni= dvector(0,ng-1); // ion density,used for fixed ion case
  den = dmatrix(0,nsp-1,0,ng-1);
  xpos= dmatrix(0,nsp-1,0,np0-1);
  px  = dmatrix(0,nsp-1,0,np0-1);
  py  = dmatrix(0,nsp-1,0,np0-1);
  pz  = dmatrix(0,nsp-1,0,np0-1);
  gamm = dmatrix(0,nsp-1,0,np0-1);
	if(angle){
		pyL  = dmatrix(0,nsp-1,0,np0-1);
		gammL= dmatrix(0,nsp-1,0,np0-1);
	}
	gamm1= dmatrix(0,nsp-1,0,np0-1);
  gamm2= dmatrix(0,nsp-1,0,np0-1);
  fpx  = dmatrix(0,nsp-1,0,NFP);
  fpy  = dmatrix(0,nsp-1,0,NFP);
  fpz  = dmatrix(0,nsp-1,0,NFP);
  fgamm= dmatrix(0,nsp-1,0,NFP);

/******** Initializing Arrays, radiation fields at t=0 ************/

  for (j=0;j<ng;j++){
		ex[j]=exx[j]=0.0;
    pl[j]=pr[j]=sl[j]=sr[j]=0.0;
		ey[j]=ez[j]=by[j]=bz[j]=0.0;
		jx[j]=0.0;
		if(angle) jye[j]=jyi[j]=0.0;
		deni[j]=0.0;
	}

  for(j=0;j<nc;j++){
    jy[j]=jz[j]=rho[j]=rhoi[j]=0.0;
	}

  for (isp=0;isp<nsp;isp++){
    for (i=0;i<np0;i++){
      xpos[isp][i]=0.0;
      px[isp][i]=py[isp][i]=pz[isp][i]=0.0;
			gamm[isp][i]=gamm1[isp][i]=gamm2[isp][i]=0.0;
			if(angle)	pyL[isp][i]=gammL[isp][i]=0.0;
		}
    for(j=0;j<=NFP;j++)
      fpx[isp][j]=fpy[isp][j]=fpz[isp][j]=fgamm[isp][j]=0.0;
		for (j=0;j<ng;j++)
			den[isp][j]=jx2[isp][j]=0.0;
		for (j=0;j<nc;j++)
			jy2[isp][j]=jz2[isp][j]=rho2[isp][j]=0.0;
	}

  qs[0]=qs0;ms[0]=ms0;
	temperature[0]=temp0/0.51099891e6; // in mc^2
	debyel=sqrt(temperature[0])*nc_per_wl/(TWOPI*sqrt(den0));   /* Debye length in cell size */
  printf(" Debye length=%f\n", debyel);

	qs[1]=qs1;ms[1]=ms1;
	temperature[1]=temp1/0.51099891e6;

	np_cell_max=(double)np0_cell;

/********* load particles ********/
  for (isp=0;isp<nsp;isp++)	Creator(isp);
	
/********* set initial charge density *********/
  for (isp=0;isp<nsp;isp++)	Setrho(isp);

	printf("Diagnosis parameters:\n");
  printf(" dt=%f\n t_stop=%f\n",dt,t_stop);
  printf(" nstep_en=%d\n nstep_ss=%d\n nstep_ps=%d\n nstep_spt=%d\n",nstep_en,nstep_ss,nstep_ps,nstep_spt);
  if(nstep_en==0||nstep_ss==0||nstep_ps==0||nstep_spt==0){
    printf("START: output step error !!");
    exit(1);
  }
}
/********** end of start() ***********/
