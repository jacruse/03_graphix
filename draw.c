#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  if (points->lastcol >= points->cols) {
    grow_matrix(points, (points->cols + 1) * 2);
  }
  
  points->m[0][points->lastcol] = x;
  points->m[1][points->lastcol] = y;
  points->m[2][points->lastcol] = z;
  points->m[3][points->lastcol] = 1;

  points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  if (points->lastcol >= points->cols) {
    grow_matrix(points, (points->cols + 1) * 2);
  }

  if (points->lastcol % 2 == 1) {
    printf("triggered odd case\n");
    points->m[0][points->lastcol] = points->m[0][points->lastcol - 1];
    points->m[1][points->lastcol] = points->m[1][points->lastcol - 1];
    points->m[2][points->lastcol] = points->m[2][points->lastcol - 1];
    points->m[3][points->lastcol] = 1;

    points->lastcol++;
  }

  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
  
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  int ctr;
  for (ctr = 0; ctr < points->lastcol - 1; ctr += 2) {
    draw_line(points->m[0][ctr], points->m[1][ctr], points->m[0][ctr+1], points->m[1][ctr+1], s, c);
  }
}




/*
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

  int x, y, d, A, B;
  //swap points if going right -> left
  int xt, yt;
  if (x0 > x1) {
    xt = x0;
    yt = y0;
    x0 = x1;
    y0 = y1;
    x1 = xt;
    y1 = yt;
  }

  x = x0;
  y = y0;
  A = 2 * (y1 - y0);
  B = -2 * (x1 - x0);

  //octant 1
  if ( abs(x1 - x0) >= abs(y1 - y0) ) {

    //octant 1
    if ( A > 0 ) {
      d = A + B/2; //not really division since B = 2B

      while ( x < x1 ) {
        plot( s, c, x, y );
        if ( d > 0 ) {
          y+= 1;
          d+= B;
        }
        x++;
        d+= A;
      } //end octant 1 while
      plot( s, c, x1, y1 );
    } //end octant 1
  }

} //end draw_line
*/


void swap(int * x0, int * y0, int * x1, int * y1) {
  int tx0 = *x0;
  int ty0 = *y0;

  *x0 = *x1;
  *y0 = *y1;

  *x1 = tx0;
  *y1 = ty0;
}


void oct2(int x0, int y0, int x1, int y1, screen s, color c, int a, int b) {
  int d = a + (2 * b);

  while ( y0 <= y1 ) {
    plot(s, c, x0, y0);
    if (d < 0) {
      d += (2 * a);
      x0++;
    }
    d += (2 * b);
    y0++;
  }
}

void oct1(int x0, int y0, int x1, int y1, screen s, color c, int a, int b) {
  int d = (2 * a) + b;

  while ( x0 <= x1 ) {
    plot(s, c, x0, y0);
    if (d > 0) {
      d += (2 * b);
      y0++;
    }
    d += (2 * a);
    x0++;
  }
}

void oct8(int x0, int y0, int x1, int y1, screen s, color c, int a, int b) {
  int d = (2 * a) - b;

  while ( x0 <= x1 ) {
    plot(s, c, x0, y0);
    if (d < 0) {
      d -= (2 * b);
      y0--;
    }
    d += (2 * a);
    x0++;
  }
}
  
void oct7(int x0, int y0, int x1, int y1, screen s, color c, int a, int b) {
  int d = a - (2 * b);

  while ( y0 >= y1 ) {
    plot(s, c, x0, y0);
    if (d > 0) {
      d += (2 * a);
      x0++;
    }
    d -= (2 * b);
    y0--;
  }
}
  

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  if (x0 > x1) {
    swap(&x0, &y0, &x1, &y1);
  }

  int a = y1 - y0;
  int b = x0 - x1;

  if (a >= 0 && a <= -b) {
    oct1(x0, y0, x1, y1, s, c, a, b);
  }

  else if (a > 0 && a > -b) {
    oct2(x0, y0, x1, y1, s, c, a, b);
  }

  else if (a < 0 && -a <= -b) {
    oct8(x0, y0, x1, y1, s, c, a, b);
  }

  else {
    oct7(x0, y0, x1, y1, s, c, a, b);
  }
}

