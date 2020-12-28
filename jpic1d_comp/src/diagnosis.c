/******************* Diagnosis ********************
 - - output desired data for normal incidence case
**************************************************/
#include "jpic.h"

Diagnosis(counter)
{
  int i,j,isp,n_divp,n_dive;
  double x,den_ion,max_eng=0.0,max_p=0.0,min_p=0.0,theta,
         dp_max,de_max,pp,ep,norm_den,eng_ion;
  char	*name_den,*name_eb,*name_j,*name_xp,*name_df;
	double Jy(),Jz();

  name_den=cvector(0,name_length);
  name_eb =cvector(0,name_length);
  name_j  =cvector(0,name_length);
  name_xp =cvector(0,name_length);
  name_df =cvector(0,name_length);

	if(counter==0)	printf(" normal diagnosis...\n\n");

/**** trace energy ****/
  if(Q_trace_energy&&counter_times%nstep_en==0){
    eng_yzf=eng_xf=0.0;
		for(j=0;j<ng;j++){
      eng_yzf	+=0.5*(pow(ey[j],2.0)+pow(ez[j],2.0)+pow(by[j],2.0)+pow(bz[j],2.0));
      eng_xf	+=0.5*pow(ex[j],2.0);
    }

    for(isp=0;isp<nsp;isp++){
			norm_den=fabs(zn[isp]/qs[isp]);
			eng_ei[isp]=0;
      for(i=0;i<np0;i++)
				eng_ei[isp]+=norm_den*ms[isp]*(gamm[isp][i]-1.0);
		}
		if(!i_move)	{
			eng_ion=0.0;
			eng_particle=eng_ei[0];
		}
		else{
			eng_ion=eng_ei[1];
			eng_particle=eng_ei[0]+eng_ei[1];
		}

    eng_field=eng_yzf+eng_xf;
    eng_total=eng_field+eng_particle;
   
    fprintf(ebflux,"%14.5e%14.5e%14.5e%14.5e%14.5e\n",t,prsr_in,prsr_out,plsl_in,plsl_out);
    fprintf(energy,"%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e\n",
			t,eng_field,eng_xf,eng_yzf,eng_particle,eng_ei[0],eng_ion,eng_total);
  }

/****** trace field & density &current *****/
  if(Q_trace_eb){
    //fprintf(tr_prsr,"%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e\n",t,pr[tr1_eb],pr[tr2_eb],pr[tr3_eb]);
    //fprintf(tr_plsl,"%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e\n",t,pl[tr1_eb],pl[tr2_eb],pl[tr3_eb],sl[tr1_eb],sl[tr2_eb],sl[tr3_eb]);
    fprintf(tr_plpr,"%14.5e%14.5e%14.5e\n",t,pl[tr2_eb],pr[tr2_eb]);
    //fprintf(tr_slsr,"%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e\n",t,sl[tr1_eb],sl[tr2_eb],sl[tr3_eb],sr[tr1_eb],sr[tr2_eb],sr[tr3_eb]);
	}
	if(Q_trace_dj){
    fprintf(tr_de,"%14.5e%14.5e%14.5e%14.5e\n",t,den[0][tr1_dj],den[0][tr2_dj],den[0][tr3_dj]);
		fprintf(tr_jx,"%14.5e%14.5e%14.5e%14.5e\n",t,jx[tr1_dj],jx[tr2_dj],jx[tr3_dj]);
		fprintf(tr_jy,"%14.5e%14.5e%14.5e%14.5e\n",t,Jy(tr1_dj),Jy(tr2_dj),Jy(tr3_dj)); //Jy,Jz on cell boundary as Jx 
		fprintf(tr_jz,"%14.5e%14.5e%14.5e%14.5e\n",t,Jz(tr1_dj),Jz(tr2_dj),Jz(tr3_dj));
		if(i_move)
			fprintf(tr_di,"%14.5e%14.5e%14.5e%14.5e\n",t,den[1][tr1_dj],den[1][tr2_dj],den[1][tr3_dj]);
	}

/***************** spacetime ****************/
  if(Q_spacetime&&counter_times%nstep_spt==0){
    for(j=cell_start;j<=cell_stop;j=j+cell_step){
			fprintf(spacetime_de,"%14.5e",den[0][j]);
			fprintf(spacetime_ex,"%14.5e",ex[j]);
			fprintf(spacetime_ey,"%14.5e",ey[j]);
			fprintf(spacetime_ez,"%14.5e",ez[j]);
			fprintf(spacetime_by,"%14.5e",by[j]);
			fprintf(spacetime_bz,"%14.5e",bz[j]);
			if(i_move)	fprintf(spacetime_di,"%14.5e",den[1][j]);
		}
		fprintf(spacetime_de,"\n");
		fprintf(spacetime_ex,"\n");
		fprintf(spacetime_ey,"\n");
		fprintf(spacetime_ez,"\n");
		fprintf(spacetime_by,"\n");
		fprintf(spacetime_bz,"\n");
		if(i_move)	fprintf(spacetime_di,"\n");
	}
  
/**************** snapshot **************/
  if(Q_snapshot&&counter_times%nstep_ss==0){
    sprintf(name_den,	"%s/x_ne_t%.f",path,t);
    sprintf(name_eb,	"%s/x_pl_pr_t%.f",path,t);
    //sprintf(name_j,		"%s/jxyz-%.f",path,t);
    file_den=fopen(name_den,"w");
    file_eb =fopen(name_eb,"w");
    //file_j  =fopen(name_j,"w");
    for(j=0;j<ng;j++){
			x=(double)j/nc_per_wl;
			if(i_move)	den_ion=den[1][j];
			else den_ion=deni[j];
			fprintf(file_den,"%14.5e%14.5e\n",x,den[0][j]);
			fprintf(file_eb, "%14.5e%14.5e%14.5e\n",x,pl[j],pr[j]); 
			//fprintf(file_j,  "%14.5e%14.5e%14.5e%14.5e\n",x,jx[j],Jy(j),Jz(j));	//Jy,Jz on cell boundary as Jx
		}
    fclose(file_den);
    fclose(file_eb);
    //fclose(file_j);
	}
  
/*** phase space & distribution function ***/
  if(Q_phasespace&&counter_times%nstep_ps==0){
    sprintf(name_xp,"%s/xpe-%.2f",path,t);
    sprintf(name_df,"%s/dfe-%.2f",path,t);
    file_xpe=fopen(name_xp,"w");
    file_dfe=fopen(name_df,"w");

		if(i_move){
      sprintf(name_xp,"%s/xpi-%.2f",path,t);
      sprintf(name_df,"%s/dfi-%.2f",path,t);
      file_xpi=fopen(name_xp,"w");
      file_dfi=fopen(name_df,"w");
		}
		
		for(isp=0;isp<nsp;isp++){
			for(i=0;i<np0;i=i+np_step){
				x=xpos[isp][i]/nc_per_wl;
				theta=atan(py[isp][i]/px[isp][i])*180.0/PI; // [-PI,PI],x-dir->0 degree,-x->-PI&PI
				if(px[isp][i]<0.0)
					theta+=sign(py[isp][i])*180.0;
				if(isp==0)
					fprintf(file_xpe,"%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e\n",
						x,px[isp][i],py[isp][i],pz[isp][i],gamm[isp][i],theta,gamm1[isp][i],gamm2[isp][i]);
				else
					fprintf(file_xpi,"%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e\n",
						x,px[isp][i],py[isp][i],pz[isp][i],gamm[isp][i],theta,gamm1[isp][i],gamm2[isp][i]);
			}
		}

		/******* distribution functions *****/
    for(isp=0;isp<nsp;isp++){
      for(i=0;i<np0;i++){
				max_eng=max(max_eng,gamm[isp][i]-1.0);
				max_p=max(max_p,px[isp][i]);
				max_p=max(max_p,py[isp][i]);
				max_p=max(max_p,pz[isp][i]);
				min_p=min(min_p,px[isp][i]);
				min_p=min(min_p,py[isp][i]);
				min_p=min(min_p,pz[isp][i]);
			}
      dp_max=(double)(NFP)/(max_p-min_p);
      de_max=(double)(NFP)/(max_eng);
      for(i=0;i<np0;i++){
				n_divp=(int)((px[isp][i]-min_p)*dp_max);
				fpx[isp][n_divp]+=1.0;
				n_divp=(int)((py[isp][i]-min_p)*dp_max);
				fpy[isp][n_divp]+=1.0;
				n_divp=(int)((pz[isp][i]-min_p)*dp_max);
				fpz[isp][n_divp]+=1.0;
				n_dive=(int)((gamm[isp][i]-1.0)*de_max);
				fgamm[isp][n_dive]+=1.0;
			}
	
			for(i=0;i<=NFP;i++){
				pp=(double)i/dp_max+min_p;
				ep=(double)i/de_max;
				if(isp==0)
					fprintf(file_dfe,"%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e\n",
						ep,fgamm[isp][i],pp,fpx[isp][i],fpy[isp][i],fpz[isp][i]);
				else
					fprintf(file_dfi,"%14.5e%14.5e%14.5e%14.5e%14.5e%14.5e\n",
						ep,fgamm[isp][i],pp,fpx[isp][i],fpy[isp][i],fpz[isp][i]);
			}
			max_p=min_p=max_eng=0.0;
			for(i=0;i<=NFP;i++)
				fpx[isp][i]=fpy[isp][i]=fpz[isp][i]=fgamm[isp][i]=0.0;
		}
    fclose(file_xpe);
    fclose(file_dfe);
    if(i_move){
      fclose(file_xpi);
      fclose(file_dfi);
    }
  }

  free_cvector(name_den,0,name_length);
  free_cvector(name_eb, 0,name_length);
  free_cvector(name_j,  0,name_length);
  free_cvector(name_xp, 0,name_length); 
  free_cvector(name_df, 0,name_length);
}
/********* end of diagosis() *********/

/*** interplate Jy,Jz,rho to cell boundary only for diagnosis ***/
double Jy(j)
int j;
{
	if(j==0)				return(0.5*jy[0]);
	else if(j==nc)	return(0.5*jy[nc-1]);
	else						return(0.5*(jy[j]+jy[j-1]));
}

double Jz(j)
int j;
{
	if(j==0)				return(0.5*jz[0]);
	else if(j==nc)	return(0.5*jz[nc-1]);
	else						return(0.5*(jz[j]+jz[j-1]));
}

double Rho(j)
int j;
{
	if(j==0)				return(0.5*rho[0]);
	else if(j==nc)	return(0.5*rho[nc-1]);
	else						return(0.5*(rho[j]+rho[j-1]));
}

