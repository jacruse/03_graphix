#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  struct matrix *edges;
  struct matrix *identity;

  c.red = 0;
  c.green = 0;
  c.blue = MAX_COLOR;

  clear_screen(s);

  edges = new_matrix(4, 4);
  
  identity = new_matrix(4, 4);
  ident(identity);

  print_matrix(identity);

  //turn identity into transformation matrix
  identity->m[0][0] = 2;
  identity->m[1][1] = 2;
  identity->m[2][2] = 2;
  identity->m[3][3] = 2;  

  print_matrix(identity);

  /*rand des
  add_point(edges, 0, 500, 350);
  add_point(edges, 250, 250, 350);
  add_point(edges, 250, 375, 400);
  add_edge(edges, 0, 0, 0, 500, 500, 500);
  add_edge(edges, 250, 250, 250, 375, 125, 250);
  */

  //box
  add_edge(edges, 0, 0, 0, 0, 50, 0);
  add_edge(edges, 0, 50, 0, 50, 50, 0);
  add_edge(edges, 50, 50, 0, 50, 0, 0);
  add_edge(edges, 50, 0, 0, 0, 0, 0);
  

  print_matrix(edges);

  matrix_mult(identity, edges);

  print_matrix(edges);

  draw_lines(edges, s, c);
  display(s);
  free_matrix( edges );
  free_matrix( identity );
}
