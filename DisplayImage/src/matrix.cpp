#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


struct matrix init_matrix(unsigned int _rows, unsigned int _columns, unsigned int* tab){
	struct matrix init = zeros(_rows, _columns);
	unsigned int k=0;
	unsigned int i;
	unsigned int j;

	 for(i=0;i<init.rows;++i){

		 for(j=0;j<init.columns;++j){
			 init.values[i][j] = tab[k];
			 k++;
		 }

	 }
	 return init;


}


struct matrix zeros(unsigned int _rows, unsigned int _columns){

	struct matrix zeros;
	unsigned int i;
	zeros.columns = _columns;
	zeros.rows = _rows;

	zeros.values = (unsigned int**)malloc(_rows*sizeof(unsigned int *));
	for(i=0;i<_rows;++i){

		  zeros.values[i] = (unsigned int*)calloc(_columns,sizeof(unsigned int));
	  }

	  return zeros;

}



struct matrix coef_matrix(struct matrix  m, unsigned int coef){

	unsigned int i,j;

	 for(i=0;i<m.rows;++i){

			 for(j=0;j<m.columns;++j){
				 m.values[i][j] *= coef;

			 }

	 }
	 return m;
}


struct matrix add_matrix(struct matrix  input_m1, struct matrix  input_m2, struct matrix  output_m3){

	unsigned int i,j;

	if ((input_m1.columns != input_m2.columns) || (input_m1.rows != input_m2.rows) || (input_m1.columns != output_m3.columns)  || (input_m1.rows != output_m3.rows)){
			fprintf(stderr,"I can't add these matrices");
			return output_m3;
	}
	else{
			 for(i=0;i<input_m1.rows;++i){

					 for(j=0;j<input_m1.columns;++j){
						 output_m3.values[i][j] =  input_m1.values[i][j] +  input_m2.values[i][j];

					 }

			 }
			 return output_m3;

	}
}


struct matrix mult_matrix(struct matrix  input_m1, struct matrix  input_m2){

	unsigned int i,j,k;
	unsigned int _rows = input_m1.rows;
	unsigned int _columns = input_m2.columns;

	struct matrix output_m3 = zeros(_rows, _columns);
	printf("output_m3 : \n");
	print_matrix(output_m3);

	if (input_m1.columns != input_m2.rows){
			fprintf(stderr,"I can't do scalar multiplication with these matrices");
			return output_m3;
	}
	else{

			for(i=0;i<output_m3.rows;++i){

					 for(j=0;j<output_m3.columns;++j){

						 for(k=0;k<input_m1.columns;++k){
							 output_m3.values[i][j] +=   input_m1.values[i][k] * input_m2.values[k][j];
						 }

					 }

			 }
			 return output_m3;

	}
}



void delete_matrix(struct matrix * m){
  unsigned int i;
  for(i=0;i<m->columns;++i) free(m->values[i]);
  free(m->values);
  free(m);
}




int get(struct matrix m,unsigned int _rows,unsigned int _columns){
  if (_rows >= m.rows){
    fprintf(stderr,"get : out of range\n");
    return 0;
  }
  if (_columns >= m.columns){
    fprintf(stderr,"get : out of range\n");
    return 0;
  }

  return m.values[_rows][_columns];
}


void print_matrix(struct matrix m){
	unsigned int i;
	unsigned int j;
	printf("[ ");
	 for(i=0;i<m.rows;++i){

		 for(j=0;j<m.columns;++j){
			printf("%d ,", m.values[i][j]);
		 }
		 printf("\n");
	 }
	 printf("];\n");


}



