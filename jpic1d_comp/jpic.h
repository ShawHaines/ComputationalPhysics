/************** Head file ************** 
 - - define all variables and constants
***************************************/
#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define PI 			3.141592653589793
#define NFP     1000   /* grid number of distribution function */
#define name_length   100    /* not too small, otherwise error */

#ifndef max
#define max(x,y)			(((x)>(y))?(x):(y))
#endif
#ifndef min
#define min(x,y)			(((x)<(y))?(x):(y))
#endif
#define sign(x)				((x)/fabs(x))

/*********************** global variables **********************/
						
#if defined(GLOBALORIGIN)
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL double TWOPI;
GLOBAL double	**xpos,**px,**py,**pz,**gamm,**pyL,**gammL,**gamm1,**gamm2,
							**den,**jx2,**jy2,**jz2,*jx,*jy,*jz,*jye,*jyi,**rho2,*rho,*rhoi,*deni,
							*ex,*exx,*ey,*ez,*by,*bz,*pr,*pl,*sr,*sl,
							*ms,*qs,*zn,*temperature,np_cell_max,debyel,
							exp_scale,dx,dt,t,den0,second0,Gamm,Beta,tstart_mover;
GLOBAL double	RES_gamma0;

GLOBAL double	a0_1,polar_1,shape_1,duration_1,delay_1,phase_1,flat_1,angle,
							a0_2,polar_2,shape_2,duration_2,delay_2,phase_2,omega_2,dir_2;

GLOBAL double eng_yzf,eng_xf,eng_field,*eng_ei,eng_particle,
							eng_total,prsr_in,prsr_out,plsl_in,plsl_out,**fpx,**fpy,**fpz,**fgamm;

/********  numbers of particle, speices, cells, and grid points, etc.*****/
GLOBAL int np0,np0_cell,nsp,nc,ng,nc_per_wl,i_move,ramp_prof;
GLOBAL double nc_vac,nc_flat,nc_lramp,nc_rramp;
GLOBAL int np_flat,np_lramp,np_rramp;

/********************** diagnostic parameters ***************************/
GLOBAL FILE *ebflux,*energy;
GLOBAL FILE *file_den,*file_eb,*file_j,*file_xpe,*file_xpi,*file_dfe,*file_dfi;
GLOBAL FILE *spacetime_de,*spacetime_di,*spacetime_ex,*spacetime_ey,*spacetime_ez,
						*spacetime_by,*spacetime_bz,*tr_prsr,*tr_plsl,*tr_slsr,*tr_plpr,*tr_de,*tr_di,*tr_jx,*tr_jy,*tr_jz;

GLOBAL double	t_stop,tstep_spt,tstep_tr,tstep_en,tstep_ss,tstep_ps;	
GLOBAL int		Q_trace_energy,Q_trace_eb,Q_trace_dj,Q_spacetime,Q_snapshot,Q_phasespace,
							nstep_en,nstep_ss,nstep_ps,nstep_spt,cell_start,cell_step,cell_stop,np_step,
							tr1_eb,tr2_eb,tr3_eb,tr1_dj,tr2_dj,tr3_dj;

GLOBAL long int counter_times;

GLOBAL char		path[name_length];

#undef GLOBAL
/******************* end of jpic.h ************************/
