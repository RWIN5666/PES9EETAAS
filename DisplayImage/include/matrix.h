/*
 * matrix.h
 *
 *  Created on: Oct 8, 2015
 *      Author: t1audrai
 */

#ifndef MATRIX_H_
#define MATRIX_H_


typedef struct matrix
{
    unsigned int rows = 1;
    unsigned int columns = 1 ;
    unsigned int** values;
};


int get(struct matrix m,unsigned int _rows,unsigned int _columns);
void delete_matrix(struct matrix * m);

struct matrix zeros(unsigned int _rows, unsigned int _columns);
struct matrix init_matrix(unsigned int _rows, unsigned int _columns, unsigned int* tab);


struct matrix coef_matrix(struct matrix  m, unsigned int coef);
struct matrix add_matrix(struct matrix  input_m1, struct matrix  input_m2, struct matrix  output_m3);
struct matrix mult_matrix(struct matrix  input_m1, struct matrix  input_m2);

void print_matrix(struct matrix m);

#endif /* MATRIX_H_ */
