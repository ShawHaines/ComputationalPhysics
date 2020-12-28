/******************** following lichters ****************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_COL 50

int already_open=0;
FILE *fd;
char buffer[MAX_LINE_LENGTH];
char result[MAX_LINE_LENGTH];

/*
readfile()
{
  already_open = 0;
  buffer = char [MAX_LINE_LENGTH];
  if(!buffer){ printf( "allocation error in readfile" ); exit(0);}
  result = char [MAX_LINE_LENGTH];
  if(!result){ printf( "allocation error in readfile" ); exit(0);}
}
*/
/*////////////////////////////////////////////////////////////////////////////
//   openinput() has to be called to open the file.
//   If the file is already open, the file pointer is reset to the begining  */

void
openinput(char *file)
{
  int i;
  char a_char[80];
   if(!already_open){
      fd=fopen(file,"r");
      if(fd==NULL){
	for (i=0; file[i] != 0; i++) a_char[i] = file[i];
	a_char[i++] = '.';		
	a_char[i++] = 'i';
	a_char[i++] = 'n';
	a_char[i++] = 'p';
	a_char[i++] = 0;
	fd=fopen(a_char,"r");
	strcpy(file, a_char);
      }
      if(!fd){
         printf("readfile::openinput: can't open file: '%s'\n", file);
	 printf("\nCorrect syntax is: clpic_file.inp");
         exit(1);
      }
      already_open=1;
    }
   else{
      rewind(fd);
   }
}

/***************************************************************************/

void
closeinput( void )
{
   if(already_open){
     int value=fclose( fd );
     already_open=0;
     if(value!=0){printf("file not correctly closed");exit(0);}
   }
}

/*/////////////////////////////////////////////////////////////////////////////////////////
//
// read one line into buffer, skip blanks and comments (following '#') */

int read_one_line( void )
{
   int i=0,c;
   while(i<MAX_LINE_LENGTH){
      c=getc(fd);
      if(c==EOF)return(0);
      else if(c=='\n'){
         buffer[i++]=0;
         return(1);
      }
      else if(c=='#'){
         buffer[i++]=0;
         while(getc(fd)!='\n');
         return(1);
      }
      else if(c!=' '){
         buffer[i++]=c;
      }
   }
   printf("readfile::read_one_line: line too long\n");
   exit(-1);
   return(-1);
}


/*////////////////////////////////////////////////////////////////////////////
 This funtion moves the file pointer beyond the line that contains string 'a'
 and returns 1. Blanks and comments ("#" followed by some text) are ignored.
//   If 'a' is not found, 0 is returned.
//   The file has to be opened previouslly by openinput().  */
int
setinput(char *a)
{
   int m,n;

   n = strlen(a);

   rewind(fd);

   while(read_one_line()){
      m=strlen(buffer);
      if(m==n){
          if(strncmp(buffer,a,n)==0)return(1);
      }
   }

   return(0);
}

/*/////////////////////////////////////////////////////////////////////////////////////////
//
// set file pointer beyond the key word 'key',
// scan following lines for variable 'a',
// and return string following 'a='.
// break, if next key word (beginning with '&') is reached before 'a' */

char*
setget(char *key, char *a)
{
   int m,i,n,j=0;

   n = strlen(a);

   if (!setinput(key)) {
     printf( "\n readfile::setget: key word '%s' missing\n", key );
     exit(-1);
     }

   while(read_one_line()){
     m=strlen(buffer);
     if (strchr(buffer,38)) break;
     if(m>n+1) {
       for(i=0;i<m-n;i++) {
	 if(strncmp(buffer+i,a,n)==0){
	   if(buffer[n+i]=='='){
	     i++;
	     while(buffer[n+i+j]!=',' && n+i+j<m ) {
	       result[j]=buffer[n+i+j];
	       j++;
	     }
	     result[j]=0;
	     return(result);
	   }
	 }
       }
     }
   }
   printf(" readfile::setget: can't find name ");
   for(i=0;i<n;i++)putchar(a[i]);
   printf(" following key word %s \n\n",key);
   exit(1);
   return(result);
}

/*/////////////////////////////////////////////////////////////////////////////////////////
//
// scan the file for variable name 'a' and return the string beyond 'a=' */

char*
getinput(char *a)
{
   int m,n,i=0,j=0;

   n = strlen(a);

   rewind(fd);

   while(read_one_line()){
     m=strlen(buffer);
     if(m>n+1) {
       for(i=0;i<m-n;i++) {
	 if(strncmp(buffer+i,a,n)==0){
	   if(buffer[n+i]=='='){
	     i++;
	     while(buffer[n+i+j]!=',' && n+i+j<m ) {
	       result[j]=buffer[n+i+j];
	       j++;
	     }
	     result[j]=0;
	     return(result);
	   }
	 }
       }
     }
   }
   printf("readfile::getinput: can't find name ");
   for(i=0;i<n;i++)putchar(a[i]);
   printf(" in input file \n");
   exit(1);
   return(result);
}


/****************************************************************************/

void write_one_line( void )
{
  int i=0;

  printf( "\n" );
  while( buffer[i]!=0 ) putchar(buffer[i++]);
}

/*/////////////////////////////////////////////////////////////////////////////////////////
//
//  read several arguments from one line
//  arguments have to be se seperated by blanks
//  a line is terminated with '\n'
//  lines of blanks are skipped
//  comments are skipped ( anything following a '#' )
//
//  narg: number of arguments that have been read
//  arg[]: pointer to strings containing the arguments
//
//  return value: 0, if end of file was reached
//                1, if arguments were read successfully */

int read_line( int *narg, char **arg )
{
  int c, col=0, pos=0, skip=0;

  do
    {
      c=getc(fd);
      arg[col][pos]=0;
      if ( c=='#' )
	{
	  if (pos>0) col++;
	  pos=0;
	  skip++;
	}
      else if ( c==' ' )
	{
	  if (pos>0) col++;
	  pos=0;
	}
      else if ( c=='\n' )
	{
	  if (pos>0) col++;
	  pos=0;
	  *narg=col;
	  if (col>0) return 1;
	  else       skip=0;
	}
      else if ( c==EOF )
	{
	  if (pos>0) col++;
	  *narg=col;
	  return 0;
	}
      else if ( skip==0 ) arg[col][pos++] = c;
    }
  while( col<MAX_COL && pos<MAX_LINE_LENGTH);

  if (col>=MAX_COL) printf( "\n number of columns too large in 'fread_line'\n" );
  else              printf( "\n length of argument too large in 'fread_line'\n" );
  exit(-1);
  return(-1);
}


/*/////////////////////////////////////////////////////////////////////////////////////////
read file, count number of rows and find minimum and maximum number of columns */

int file_structure( int *col_min, int *col_max, int *rows )
{
  int check, narg;
  char **arg;

  rewind(fd);

  arg = cmatrix(0,MAX_COL,0,MAX_LINE_LENGTH);
  if(!arg){ printf( "allocation error in readfile" ); exit(0);}

  *col_min = MAX_COL;
  *col_max = 0;
  *rows    = 0;

  do
    {
      check = read_line( &narg, arg );
      if (check>0) {
	(*rows)++;
	if (narg<*col_min) *col_min=narg;
	if (narg>*col_max) *col_max=narg;
      }
    }
  while( check>0 );

  free_cmatrix(arg,0,MAX_COL,0,MAX_LINE_LENGTH);

  if ((*col_min)==(*col_max)) return 1;
  else                        return 0;
}


/*////////////////////////////////////////////////////////////////////////////
// read data from column 'col' into 'data', maximum number of rows ('rows_max')
*/

int read_col( double *data, int col, int rows_max )
{
  int rows_count=0;
  int narg, nmin=MAX_COL, nmax=0;
  char **arg;
  int check;

  if (col==0) { printf( "\n selected colum number %d invalid", col ); exit(-1); }

  arg = cmatrix(0,MAX_COL,0,MAX_LINE_LENGTH);
  if(!arg){ printf( "allocation error in readfile" ); exit(0);}

  rewind(fd);

  do
    {
      check = read_line( &narg, arg );
      if (narg>=col) data[rows_count++] = atof( arg[col-1] );
      else
	{
	  data[rows_count++] = 0;
	  printf( "\n warning: %d column(s) in line %d", narg, rows_count );
	}
      if (narg<nmin) nmin=narg;
      if (narg>nmax) nmax=narg;
    }
  while( check>0 && rows_count<rows_max );

  /*  if (nmin==nmax) printf( "\n %d rows, %d cols", rows_count, nmax );
  //  else            printf( "\n %d rows, %d...%d cols", rows_count, nmin, nmax ); */

  free_cmatrix(arg,0,MAX_COL,0,MAX_LINE_LENGTH);

  return rows_count;
}

/*/////////////////////////////////////////////////////////////////////////////////////////
//
// if one or two of these files do not exist: return -1
// else:  return number of different pairs of characters         */

int compare_files( char *name1, char *name2 )
{
  FILE *f1, *f2;
  int c1, c2;
  int differences=0;

  f1 = fopen( name1, "rb" );
  f2 = fopen( name2, "rb" );

  if ( (!f1) || (!f2) ) return -1;
  else {
    do {
      c1=fgetc(f1);
      c2=fgetc(f2);
      if (c1!=c2) differences++;
    } while( (c1 != EOF) && (c2 != EOF) );

    fclose( f1 );
    fclose( f2 );

    return differences;
  }
}

/*/////////////////////////////////////////////////////////////////////////////////////////
//
// copy file 'input' to file 'output' */

void copy_file( char *input, char *output )
{
  FILE *fin, *fout;
  int c, diff;
  char backup[MAX_LINE_LENGTH];

  diff=compare_files(input,output);

  if (diff>0) {
    printf( "readfile::copy_file: file %s does exist \n", output );
    printf( "                     and is different from %s\n", input );
    sprintf( backup, "%s-backup", output );
    copy_file( output, backup );
    printf( "                     %s saved to %s\n", output, backup );
  }

  if (diff==0) {
      printf( "readfile::copy_file: file %s does exist \n", output );
      printf( "                     and is equal to %s -> not copied\n", input );
  }
  else {
    fin = fopen( input, "rb" );
    fout = fopen( output, "wb" );
    while( (c=fgetc(fin)) != EOF ) fputc(c,fout);
    fclose( fin );
    fclose( fout );
  }
}
/**************** eof *****************/
