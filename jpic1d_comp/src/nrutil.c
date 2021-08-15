#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define NR_END 1
#define FREE_ARG char*

typedef struct DCOMPLEX{
        double r;
        double i;
} dcomplex;


void nrerror(char error_text[])
/* Numerical Recipes standard error handler */
{
  fprintf(stderr,"Numerical Recipes run-time error...\n");
  fprintf(stderr,"%s\n",error_text);
  fprintf(stderr,"...now exiting to system...\n");
}


unsigned char *ucvector(long nl, long nh)
/* allocate an char vector with subscript range v[nl..nh] */
{
  unsigned char *v;

  v=(unsigned char *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(unsigned char)));
  if (!v) nrerror("allocation failure in ucvector()");
  return v-nl+NR_END;
}


char *cvector(long nl, long nh)
/* allocate an char vector with subscript range v[nl..nh] */
{
  char *v;

  v=(char *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(char)));
  if (!v) nrerror("allocation failure in cvector()");
  return v-nl+NR_END;
}


int *ivector(long nl, long nh)
/* allocate an int vector with subscript range v[nl..nh] */
{
  int *v;

  v=(int *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(int)));
  if (!v) nrerror("allocation failure in ivector()");
  return v-nl+NR_END;
}


short int *isvector(long nl, long nh)
/* allocate an int vector with subscript range v[nl..nh] */
{
  short int *v;

  v=(short int *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(short int)));
  if (!v) nrerror("allocation failure in isvector()");
  return v-nl+NR_END;
}


float *vector(long nl, long nh)
/* allocate a float vector with subscript range v[nl..nh] */
{
  float *v;

  v=(float *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(float)));
  if (!v) nrerror("allocation failure in vector()");
  return v-nl+NR_END;
}


double *dvector(long nl, long nh)
/* allocate a double vector with subscript range v[nl..nh] */
{
  double *v;

  v=(double *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(double)));
  if (!v) nrerror("allocation failure in dvector()");
  return v-nl+NR_END;
}

dcomplex *dcvector(long nl, long nh)
/* allocate a double complex vector with subscript range v[nl..nh] */
{
  dcomplex *v;

  v=(dcomplex *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(dcomplex)));
  if (!v) nrerror("allocation failure in dcvector()");
  return v-nl+NR_END;
}

unsigned char **ucmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a unsigned char matrix with subscript range m[nrl..nrh][ncl..nch] */
{
  long i, nrow=nrh-nrl+1, ncol=nch-ncl+1;
  unsigned char **m;

  /* allocate pointers to rows */
  m=(unsigned char **) malloc((size_t)((nrow+NR_END)*sizeof(unsigned char*)));
  if (!m) nrerror("allocation failure 1 in ucmatrix()");
	m += NR_END;
	m -= nrl;
  /* allocate rows and set pointers to them */
  m[nrl]=(unsigned char *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(unsigned char)));
  if (!m[nrl]) nrerror("allocation failure 2 in ucmatrix()");
  m[nrl]+=NR_END;
  m[nrl]-=ncl;

  for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

  /* return pointer to array of pointers to rows */
  return m;
}


char **cmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a char matrix with subscript range m[nrl..nrh][ncl..nch] */
{
  long i, nrow=nrh-nrl+1, ncol=nch-ncl+1;
  char **m;

  /* allocate pointers to rows */
  m=(char **) malloc((size_t)((nrow+NR_END)*sizeof(char*)));
  if (!m) nrerror("allocation failure 1 in cmatrix()");
	m += NR_END;
	m -= nrl;
  /* allocate rows and set pointers to them */
  m[nrl]=(char *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(char)));
  if (!m[nrl]) nrerror("allocation failure 2 in cmatrix()");
  m[nrl]+=NR_END;
  m[nrl]-=ncl;

  for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

  /* return pointer to array of pointers to rows */
  return m;
}


float **matrix(long nrl, long nrh, long ncl, long nch)
/* allocate a float matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	float **m;
	/* allocate pointers to rows */
	m=(float **) malloc((size_t)((nrow+NR_END)*sizeof(float*)));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m += NR_END;
	m -= nrl;
	/* allocate rows and set pointers to them */
	m[nrl]=(float *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float)));
	if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
	m[nrl] += NR_END;
	m[nrl] -= ncl;
	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
	/* return pointer to array of pointers to rows */
	return m;
}


double **dmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a double matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	double **m;
	/* allocate pointers to rows */
	m=(double **) malloc((size_t)((nrow+NR_END)*sizeof(double*)));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m += NR_END;
	m -= nrl;
	/* allocate rows and set pointers to them */
	m[nrl]=(double *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));
	if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
	m[nrl] += NR_END;
	m[nrl] -= ncl;
	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
	/* return pointer to array of pointers to rows */
	return m;
}


int **imatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a int matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	int **m;
	/* allocate pointers to rows */
	m=(int **) malloc((size_t)((nrow+NR_END)*sizeof(int*)));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m += NR_END;
	m -= nrl;
	/* allocate rows and set pointers to them */
	m[nrl]=(int *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(int)));
	if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
	m[nrl] += NR_END;
	m[nrl] -= ncl;
	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
	/* return pointer to array of pointers to rows */
	return m;
}


/************************ free matrix *****************************/

void free_ucvector(unsigned char *v, long nl, long nh)
/* free an unsigned char vector allocated with ucvector() */
{
  free((FREE_ARG) (v+nl-NR_END));
}

void free_cvector(char *v, long nl, long nh)
/* free an char vector allocated with cvector() */
{
  free((FREE_ARG) (v+nl-NR_END));
}


void free_ivector(int *v, long nl, long nh)
/* free an int vector allocated with ivector() */
{
  free((FREE_ARG) (v+nl-NR_END));
}


void free_vector(float *v, long nl, long nh)
/* free a float vector allocated with vector() */
{
  free((FREE_ARG) (v+nl-NR_END));
}


void free_dvector(double *v, long nl, long nh)
/* free a double vector allocated with dvector() */
{
  free((FREE_ARG) (v+nl-NR_END));
}

void free_dcvector(dcomplex *v, long nl, long nh)
/* free a double complex vector allocated with dcvector() */
{
  free((FREE_ARG) (v+nl-NR_END));
}


void free_ucmatrix( unsigned char **m, long nrl, long nrh, long ncl, long nch)
/* free a unsigned char matrix allocated by ucmatrix() */
{
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}


void free_cmatrix( char **m, long nrl, long nrh, long ncl, long nch)
/* free a char matrix allocated by cmatrix() */
{
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}


void free_matrix( float **m, long nrl, long nrh, long ncl, long nch)
/* free a float matrix allocated by matrix() */
{
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

void free_dmatrix( double **m, long nrl, long nrh, long ncl, long nch)
/* free a double matrix allocated by dmatrix() */
{
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

void free_imatrix( int **m, long nrl, long nrh, long ncl, long nch)
/* free a int matrix allocated by dmatrix() */
{
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}







