#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
  int i, j;
  printf("Printing out row by row...\n");
  
  for (i = 0; i < m->rows; i++) {
    printf("\n%d: ", i);
    for (j = 0; j < m->lastcol; j++) {
      printf("%f\t", m->m[i][j]);
    }
  }
  printf("\n");
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int i, j;
  for (i = 0; i < m->rows; i++) {
    for (j = 0; j < m->cols; j++) {
      m->m[i][j] = 0;
    }
  }
  for (i = 0; i < m->rows; i++) {
    m->m[i][i] = 1;
  }
  m->lastcol = m->cols;
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  if ( a > 0  && b > 0 && a->lastcol != b->rows ) {
    printf("Matrix is not proper size\n");
    return;
  }

  int i, j, k;
  struct matrix *new_mat = new_matrix(a->rows, b->lastcol);

  for (i = 0; i < new_mat->rows; i++) {
    for (j = 0; j < new_mat->cols; j++) {
      new_mat->m[i][j] = 0;
      for (k = 0; k < b->rows; k++) {
	new_mat->m[i][j] += (a->m[i][k] * b->m[k][j]);
      }
    }
  }
  new_mat->lastcol = new_mat->cols;

  for (i=0;i<b->rows;i++) {
      free(b->m[i]);
    }
  free(b->m);
  
  b->m = new_mat->m;
  b->rows = new_mat->rows;
  b->cols = new_mat->cols;
  b->lastcol = new_mat->lastcol;

}



/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}
