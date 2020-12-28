/****************************** JPIC1d *********************************
 - - One-Dimensional Laser Plasma Particle-In-Cell Simualtion Code	- - 
 - - 2011-02-07, authored by Hui-Chun Wu, email: huichunwu1@gmail.com
***********************************************************************/
#define GLOBALORIGIN
#include "jpic.h"
#undef GLOBALORIGIN
#include "nrutil.c"
#include "setrho.c"
#include "creator.c"
#include "start.c"
#include "history.c"
#include "diagnosis.c"
#include "field.c"
#include "mover.c"


int 
main(argc, argv)
int argc;
char *argv[];
{
  int isp,counter_cycle=0;

  Start(argc,argv);
  History(counter_cycle);  
  Diagnosis(counter_cycle);

/**** begin loop to evolve in time ******/
  while (t<t_stop)  {
    if(fabs(t-(double)counter_cycle)<0.5*dt){
			printf(">> t=%.2f,  time_steps=%d,  minutes=%.2f\n",t,counter_times,Timer());
      counter_cycle++;
		}

		Field();
		
		if(t>=tstart_mover) {
			for (isp=0;isp<nsp;isp++)
				Mover(isp);
		}
    
		t+=dt; counter_times++;
    Diagnosis(counter_cycle);
	}
/*** end of loop ****/

	History(counter_cycle);
  return (0);

}	
/************ end of main() ************/
