/********************* History ********************
 - - open file on the beginning of simulation
 - - close file at the end of simulation
***************************************************/
#include "jpic.h"

void
History(counter)
int counter;
{
  char	file1[name_length]="1",file2[name_length]="2",
				file3[name_length]="3",file4[name_length]="4",
				file5[name_length]="5",file6[name_length]="6";

  if(counter==0){
		if(Q_trace_energy){
			sprintf(file1,"%s/ebflux",path);
			sprintf(file2,"%s/energy",path);
			ebflux=fopen(file1,"w");
			energy=fopen(file2,"w");
		}

    if(Q_trace_eb){
      //sprintf(file1,"%s/tr_prsr",path);
      //sprintf(file2,"%s/tr_plsl",path);
		sprintf(file3,"%s/t_pl_pr",path);
      //sprintf(file4,"%s/tr_slsr",path);
      //tr_prsr=fopen(file1,"w");
      //tr_plsl=fopen(file2,"w");
			tr_plpr=fopen(file3,"w");
      //tr_slsr=fopen(file4,"w");
    }
		if(Q_trace_dj){
      sprintf(file1,"%s/tr_de",path);
      sprintf(file2,"%s/tr_jx",path);
			sprintf(file3,"%s/tr_jy",path);
			sprintf(file4,"%s/tr_jz",path);
      tr_de=fopen(file1,"w");
      tr_jx=fopen(file2,"w");
			tr_jy=fopen(file3,"w");
			tr_jz=fopen(file4,"w");
			if(i_move){
				sprintf(file1,"%s/tr_di",path);
				tr_di=fopen(file1,"w");
			}
    }
    if(Q_spacetime){
      sprintf(file1,"%s/spacetime_de",path);
      sprintf(file2,"%s/spacetime_ex",path);
      sprintf(file3,"%s/spacetime_ey",path);
      sprintf(file4,"%s/spacetime_ez",path);
      sprintf(file5,"%s/spacetime_by",path);
			sprintf(file6,"%s/spacetime_bz",path);
      spacetime_de=fopen(file1,"w");
      spacetime_ex=fopen(file2,"w");
      spacetime_ey=fopen(file3,"w");
      spacetime_ez=fopen(file4,"w");
      spacetime_by=fopen(file5,"w");
			spacetime_bz=fopen(file6,"w");
      if(i_move){
				sprintf(file1,"%s/spacetime_di",path);
				spacetime_di=fopen(file1,"w");
      }
    }
  }
  else{
		if(Q_trace_energy){
			fclose(ebflux);
			fclose(energy);
		}
    if(Q_trace_eb){
      //fclose(tr_prsr);
      //fclose(tr_plsl);
		fclose(tr_plpr);
      //fclose(tr_slsr);
    }
    if(Q_trace_dj){
      fclose(tr_de);
			fclose(tr_jx);
			fclose(tr_jy);
			fclose(tr_jz);
			if(i_move)	
				fclose(tr_di);
    }
    if(Q_spacetime){
      fclose(spacetime_de);
      fclose(spacetime_ex);
      fclose(spacetime_ey);
      fclose(spacetime_ez);
      fclose(spacetime_by);
			fclose(spacetime_bz);
      if(i_move)
				fclose(spacetime_di);
    }
    printf(">> programm is finished !!!\n");
  }
}
/******* end of history() ********/
