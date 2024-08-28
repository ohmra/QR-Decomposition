//Harimbola RANAIVO 
//21205612
//M1 SFPN
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int M = 4; //ROWS
int N = 3; //COLS

void print_matrix(double *m, int row, int col){
	
	for(int i = 0; i < row*col; i++){
		if(!(i%col))
			printf("\n");
		printf(" %lg\t", m[i]);
	}
	printf("\n\n\n");
}

double* transpose(double *m, int row, int col){
    double *temp;
    temp = malloc(sizeof(double)*row*col);
    for(int i = 0; i<row; i++)
        for(int j = 0; j<col; j++){
            temp[j*row + i] = m[i*col + j];
       }
    return temp;
}

double* mult_mm(double *a, int row_a, int col_a, double *b, int row_b, int col_b){
    if(col_a != row_b){
        printf("Multiplication impossible\n");
        exit(1);
    }
    double *res;
    res = malloc(sizeof(double) * row_a * col_b);
    for(int i = 0; i<row_a; i++)
        for(int j = 0; j<col_b; j++)
            for(int k = 0; k<row_b; k++)
                res[i*col_b + j] += a[i*col_a + k] * b[k*col_b + j];
            
    return res;
}

double* create_matrix(int row, int col){
    double *m = malloc(sizeof(double)*row*col);
    for(int i = 0; i<row*col; i++)
        m[i] = 0;
    return m;
}

double* create_identity(int row, int col){
    double *m = create_matrix(row, col);
    for(int i = 0; i<col; i++)
        m[i*col + i] = 1;
    return m;
}

double* create_random_matrix(int row, int col){
    double *m = malloc(sizeof(double)*row*col);
    for(int i = 0; i<row*col; i++)
        m[i] = rand() % 5;
    return m;
}

double* g_rotation(int i, int j, double* r){
    double *g = create_identity(M, M);

    if(r[i*N + j] == 0)
        return g;

    g[i*M + i] = r[j*N + j] / sqrt(pow(r[j*N + j],2) + pow(r[i*N + j],2));
    g[j*M + j] = r[j*N + j] / sqrt(pow(r[j*N + j],2) + pow(r[i*N + j],2));

    g[j*M + i] = r[i*N + j] / sqrt(pow(r[j*N + j],2) + pow(r[i*N + j],2));
    g[i*M + j] = (-g[j*M + i]);
    
    return g;
}

double* givens(double *a, double **b){
    double *q = create_identity(M, M);
    double *r = a;
    for(int j = 0; j<N; j++){
        for(int i = j+1; i<M; i++){
            double *g = g_rotation(i, j, r);
            r = mult_mm(g, M, M, r, M, N);
            double *gt = transpose(g, M, M);
            q = mult_mm(q, M, M, gt, M, M);
        }
    }
    *b = r;
    return q;
}

int main(int argc, char** argv){
    if(argc != 3){
        printf("2 parameters are needed : number of rows and number of columns\n");
        return 0;
    }

    M = atoi(argv[1]);
    N = atoi(argv[2]);
    if(M<N){
        printf("Number of columns cannot exceed the number of rows\n");
        return 0;
    }
    double *a = create_random_matrix(M, N);
    
    print_matrix(a, M, N);

    double start = clock();
    double *q = givens(a,  &a);
    double end = clock();

    printf("R : \n");
    print_matrix(a, M, N);
    printf("Q : \n");
    print_matrix(q, M, M);

    printf("Completed in %f s\n", (end - start) / CLOCKS_PER_SEC);
    return 0;
}
