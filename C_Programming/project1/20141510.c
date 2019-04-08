#include "20141510.h"

int main(){

	double result; //value of det(A)
	double **A; //matrix which was inputed
	double **invA_Th2; //inverse matrix which is obtained by using theorem2.
	double **invA_Gau; //inverse matrix which is obtained by using Gaussian Elimination.
	double **mul_matrix_Th2; //mul_matrix_Th2 is a product of A and inverse of A which was obtained by Th2
	double **mul_matrix_Gau; //mul_matrix_Gau is a product of A and inverse of A which was obtained by Gaussian elimination
	double **lowerMatrix; //lower triangular matrix
	double **upperMatrix; //upper triangular matrix
	double **mul_lower_upper;//mul_lower_upper is a product of lower triangular matrix and upper triangular matrix
	int n; //row and column of matrix.
	int i,j; //i and j is needed when using for loops.

	while(1){
		printf("system> input size n : ");
		scanf("%d",&n);

		//procedure which checks whether program user type valid n.
		if(n>=6){
			printf("Input Error!\n"); //if user input more than 6, then user have to input agian.
			continue;
		}
		else if(n<=0){
			printf("Good Bye\n"); //if user input a negative number, then the program ends.
			break;
		}

		A = (double**)malloc(sizeof(double*)*n); //procedure which allocates an memory dynamically

		for(i=0;i<n;i++)
			*(A+i) = (double*)malloc(sizeof(double)*n);

		printf("system> input %d * %d elements\n",n,n);

		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				scanf("%lf",(*(A+i)+j));

		printf("system> input matrix A\n"); //print the result
		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				printf("%7.2lf",*(*(A+i)+j));
			puts("");
		}

		result = detA(A,n);

		if(result==0){
			printf("system> A is singular\n"); //if A is singular,then a loop stops and  we should input n again
			//freeing a dynamically allocated memory
			for(i=0;i<n;i++)
				free(*(A+i));
			free(A);

			continue;
		}
		else
			printf("system> A is nonsingular\n"); //if A is not singular,then we move to a next step

		if(n<5){
			invA_Th2 = inverseA(A,n);
			invA_Gau = inverseA_gaussian(A,n);
		}
		else{
			invA_Th2 = inverseA55(A);
			invA_Gau = inverseA_gaussian(A,n);
		}

		mul_matrix_Th2 = mulMatrix(A,invA_Th2,n);
		mul_matrix_Gau = mulMatrix(A,invA_Gau,n);

		printf("system> inverse of matrix A(Theorem 2)\n");

		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				printf("%7.2lf",*(*(invA_Th2+i)+j));
			puts("");
		}

		printf("system> A*A-1\n");

		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				printf("%7.2lf",*(*(mul_matrix_Th2+i)+j));
			puts("");
		}

		printf("system> inverse of matrix A(Gaussian Elimination)\n");

		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				printf("%7.2lf",*(*(invA_Gau+i)+j));
			puts("");
		}

		printf("system> A*A-1\n");

		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				printf("%7.2lf",*(*(mul_matrix_Gau+i)+j));
			puts("");
		}

		upperMatrix = (double**)malloc(sizeof(double*)*n);
		lowerMatrix = (double**)malloc(sizeof(double*)*n);
		for(i=0;i<n;i++){
			*(upperMatrix+i) = (double*)malloc(sizeof(double)*n);
			*(lowerMatrix+i) = (double*)malloc(sizeof(double)*n);
		}

		mul_lower_upper = matrix_LU(A,upperMatrix,lowerMatrix,n);

		if(mul_lower_upper == NULL){  //if mul_lower_upper is NULL,then loop stops and we should input n again
			printf("Not available(Matrix Triangularization)\n");
			//freeing a dynamically allocated memory
			for(i=0;i<n;i++){
				free(*(A+i));
				free(*(invA_Th2+i));
				free(*(invA_Gau+i));
				free(*(mul_matrix_Th2+i));
				free(*(mul_matrix_Gau+i));
				free(*(lowerMatrix+i));
				free(*(upperMatrix+i));
			}
			free(lowerMatrix);
			free(upperMatrix);
			free(mul_matrix_Th2);
			free(mul_matrix_Gau);
			free(invA_Gau);
			free(invA_Th2);
			free(A);
			continue;
		}


		printf("system> Lower triangular matrix\n");

		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				printf("%7.2lf",*(*(lowerMatrix+i)+j));
			puts("");
		}

		printf("system> Upper triangular matrix\n");

		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				printf("%7.2lf",*(*(upperMatrix+i)+j));
			puts("");
		}

		printf("system> L*U\n");

		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				printf("%7.2lf",*(*(mul_lower_upper+i)+j));
			puts("");
		}

		//freeing a dynamically allocated memory
		for(i=0;i<n;i++){
			free(*(A+i));
			free(*(invA_Th2+i));
			free(*(invA_Gau+i));
			free(*(mul_matrix_Th2+i));
			free(*(mul_matrix_Gau+i));	
			free(*(lowerMatrix+i));
			free(*(upperMatrix+i));
			free(*(mul_lower_upper+i));
		}
		free(lowerMatrix);
		free(upperMatrix);
		free(mul_lower_upper);
		free(mul_matrix_Th2);
		free(mul_matrix_Gau);
		free(invA_Gau);	
		free(invA_Th2);
		free(A);
	}

	return 0;
}
double** addMatrix(double** A, double** B, int n){ 

	//we use this function in order to get an A+B matrix's address

	double **C; //C is result of this function
	int i,j; //i and j are needed when we use for loops

	if(A==NULL || B==NULL) //if A or B is NULL, then we can't calculate it
		return NULL;

	C = (double**)malloc(sizeof(double*)*n); //if system fails to allocate a memory, then function returns NULL
	if(C == NULL){
		printf("System fails to allocate memory\n");
		return NULL;
	}

	for(i=0;i<n;i++){
		*(C+i) = (double*)malloc(sizeof(double)*n);
		if(*(C+i) == NULL){
			printf("System fails to allocate memory\n");
			return NULL;
		}
	}

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			*(*(C+i)+j) = *(*(A+i)+j) + *(*(B+i)+j);

	return C;
}
double** subMatrix(double** A, double** B, int n){

	//we use this function in order to get an A-B matrix's address

	double **C; //C is result of this function
	int i,j; // i and j are needed when we use for loops

	if(A==NULL || B==NULL) //if A or B is NULL, then we can't calculate it
		return NULL;

	C = (double**)malloc(sizeof(double*)*n); //if system fails to allocate a memory, then function returns NULL
	if(C == NULL){
		printf("System fails to allocate memory\n");
		return NULL;
	}

	for(i=0;i<n;i++){
		*(C+i) = (double*)malloc(sizeof(double)*n);
		if(*(C+i) == NULL){
			printf("System fails to allocate memory\n");
			return NULL;
		}
	}

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			*(*(C+i)+j) = *(*(A+i)+j) - *(*(B+i)+j);

	return C;
}
double** mulMatrix(double** A, double** B, int n){

	//we use this function in order to get a AB matrix's address

	double **C; //C is result of this function
	int i,j,k; // i, j,k are needed when we use for loops

	if(A==NULL || B==NULL) //if A or B is NULL, then we can't calculate it
		return NULL;

	C = (double**)malloc(n*sizeof(double*)); //if system fails to allocate a memory, then function returns NULL
	if(C == NULL){
		printf("System fails to allocate memory\n");
		return NULL;
	}

	for(i=0;i<n;i++){
		*(C+i) = (double*)calloc(n,sizeof(double));
		if(*(C+i) == NULL){
			printf("System fails to allocate memory\n");
			return NULL;
		}
	}

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			for(k=0;k<n;k++)
				*(*(C+i)+j) += *(*(A+i)+k) * *(*(B+k)+j);
		}
	}

	return C;
}
double detA(double **A, int n){

	// this function returns a value of determinant of A

	if(n==1)
		return *(*(A+0)+0);
	else if(n==2)
		return *(*(A+0)+0) * *(*(A+1)+1) - *(*(A+1)+0) * *(*(A+0)+1);
	else if(n==3)
		return *(*(A+0)+0) * *(*(A+1)+1) * *(*(A+2)+2)
			+ *(*(A+0)+1) * *(*(A+1)+2) * *(*(A+2)+0)
			+ *(*(A+0)+2) * *(*(A+1)+0) * *(*(A+2)+1)
			- *(*(A+0)+2) * *(*(A+1)+1) * *(*(A+2)+0)
			- *(*(A+0)+1) * *(*(A+1)+0) * *(*(A+2)+2)
			- *(*(A+0)+0) * *(*(A+1)+2) * *(*(A+2)+1);
	else if(n==4)
		return detA44(A);
	else
		return detA55(A);
}
double** inverseA(double **A, int n){

	// this function returns an inverse of A's address

	double **result,**revResult;//result and revResult are result of this function
	double **A1,**B1,**C1,**D1,**E1; //A1,B1,C1,D1 are submatrix of A
	int i,j; // i and j are needed  when we use for loops
	double **invA,**CinvAB,**CinvA,**DCinvAB,**invDCinvAB,**invAB,**invABinvDCinvAB,**invABinvDCinvABCinvA,**invDCinvABCinvA;
	// variables are needed in order to free a memory

	if(A==NULL) // if A is NULL, then this function return NULL
		return NULL;

	result = (double**)malloc(sizeof(double*)*n); // if system fails to allocate a memory, then function returns NULL
	if(result == NULL){
		printf("System fails to allocate memory\n");
		return NULL;
	}
	for(i=0;i<n;i++){
		*(result+i) = (double*)malloc(sizeof(double)*n);
		if(*(result+i) == NULL){
			printf("System fails to allocate memory\n");
			return NULL;
		}
	}

	//in this function, how we get inverse of A depends on a value of n

	if(n==1)
		**result = 1 / **A;
	else if(n==2){
		*(*(result+0)+0) = *(*(A+1)+1) / detA(A,n);
		*(*(result+0)+1) = -(*(*(A+0)+1)) / detA(A,n);
		*(*(result+1)+0) = -(*(*(A+1)+0)) / detA(A,n);
		*(*(result+1)+1) = *(*(A+0)+0) / detA(A,n);
	}	
	else if(n==3){
		*(*(result+0)+0) = (*(*(A+1)+1) * *(*(A+2)+2) - *(*(A+1)+2) * *(*(A+2)+1)) / detA(A,n);
		*(*(result+0)+1) = -(*(*(A+1)+0) * *(*(A+2)+2) - *(*(A+1)+2) * *(*(A+2)+0)) / detA(A,n);
		*(*(result+0)+2) = (*(*(A+1)+0) * *(*(A+2)+1) - *(*(A+1)+1) * *(*(A+2)+0)) / detA(A,n);
		*(*(result+1)+0) = -(*(*(A+0)+1) * *(*(A+2)+2) - *(*(A+0)+2) * *(*(A+2)+1)) / detA(A,n);
		*(*(result+1)+1) = (*(*(A+0)+0) * *(*(A+2)+2) - *(*(A+0)+2) * *(*(A+2)+0)) / detA(A,n);
		*(*(result+1)+2) = -(*(*(A+0)+0) * *(*(A+2)+1) - *(*(A+0)+1) * *(*(A+2)+0)) / detA(A,n);
		*(*(result+2)+0) = (*(*(A+0)+1) * *(*(A+1)+2) - *(*(A+0)+2) * *(*(A+1)+1)) / detA(A,n);
		*(*(result+2)+1) = -(*(*(A+0)+0) * *(*(A+1)+2) - *(*(A+0)+2) * *(*(A+1)+0)) / detA(A,n);
		*(*(result+2)+2) = (*(*(A+0)+0) * *(*(A+1)+1) - *(*(A+0)+1) * *(*(A+1)+0)) / detA(A,n);

		revResult = transposeA(result,n);

		for(i=0;i<n;i++)
			free(*(result+i));
		free(result);

		return revResult;
	}
	else{
		A1 = (double**)malloc(sizeof(double*)*2);
		B1 = (double**)malloc(sizeof(double*)*2);
		C1 = (double**)malloc(sizeof(double*)*2);
		D1 = (double**)malloc(sizeof(double*)*2);
		E1 = (double**)calloc(2,sizeof(double*));
		if(A1 == NULL){  //if system fails to allocate memory, function returns NULL
			printf("System fails to allocate memory\n");
			return NULL;
		}
		if(B1 == NULL){
			printf("System fails to allocate memory\n");
			return NULL;
		}
		if(C1 == NULL){
			printf("System fails to allocate memory\n");
			return NULL;
		}
		if(D1 == NULL){
			printf("System fails to allocate memory\n");
			return NULL;
		}
		if(E1 == NULL){
			printf("System fails to allocate memory\n");
			return NULL;
		}

		for(i=0;i<2;i++){
			*(A1+i) = (double*)malloc(sizeof(double)*2);
			*(B1+i) = (double*)malloc(sizeof(double)*2);
			*(C1+i) = (double*)malloc(sizeof(double)*2);
			*(D1+i) = (double*)malloc(sizeof(double)*2);
			*(E1+i) = (double*)calloc(2,sizeof(double));
			if(*(A1+i) == NULL){
				printf("System fails to allocate memory\n");
				return NULL;
			}
			if(*(B1+i) == NULL){
				printf("System fails to allocate memory\n");
				return NULL;
			}
			if(*(C1+i) == NULL){
				printf("System fails to allocate memory\n");
				return NULL;
			}
			if(*(D1+i) == NULL){
				printf("System fails to allocate memory\n");
				return NULL;
			}
			if(*(E1+i) == NULL){
				printf("System fails to allocate memory\n");
				return NULL;
			}
		}

		for(i=0;i<2;i++){
			for(j=0;j<2;j++){
				*(*(A1+i)+j) = *(*(A+i)+j);
				*(*(B1+i)+j) = *(*(A+i)+j+2);
				*(*(C1+i)+j) = *(*(A+i+2)+j);
				*(*(D1+i)+j) = *(*(A+i+2)+j+2);
				if(i==j)
					*(*(E1+i)+j) = -1;
			}
		}

		invA = inverseA(A1,2);
		invAB = mulMatrix(invA,B1,2);
		CinvA = mulMatrix(C1,invA,2);
		CinvAB = mulMatrix(C1,invAB,2);
		DCinvAB = subMatrix(D1,CinvAB,2);
		invDCinvAB = inverseA(DCinvAB,2);
		invABinvDCinvAB = mulMatrix(invAB,invDCinvAB,2);
		invDCinvABCinvA = mulMatrix(invDCinvAB,CinvA,2);
		invABinvDCinvABCinvA = mulMatrix(invABinvDCinvAB,CinvA,2);

		for(i=0;i<2;i++){
			free(*(A1+i));
			free(*(B1+i));
			free(*(C1+i));
			free(*(D1+i));
		}
		free(A1);
		free(B1);
		free(C1);
		free(D1);

		A1 = addMatrix(invA,invABinvDCinvABCinvA,2);
		B1 = mulMatrix(E1,invABinvDCinvAB,2);
		C1 = mulMatrix(E1,invDCinvABCinvA,2);
		D1 = invDCinvAB;

		for(i=0;i<2;i++){
			for(j=0;j<2;j++){
				*(*(result+i)+j) = *(*(A1+i)+j);
				*(*(result+i)+j+2) = *(*(B1+i)+j); 
				*(*(result+i+2)+j) = *(*(C1+i)+j); 
				*(*(result+i+2)+j+2) = *(*(D1+i)+j); 
			}
		}

		for(i=0;i<2;i++){  //freeing dynamically allocated memory
			free(*(A1+i));
			free(*(B1+i));
			free(*(C1+i));
			free(*(D1+i));
			free(*(E1+i));
			free(*(invA+i));
			free(*(CinvAB+i));
			free(*(CinvA+i));
			free(*(DCinvAB+i));
			free(*(invAB+i));
			free(*(invABinvDCinvAB+i));
			free(*(invABinvDCinvABCinvA+i));
			free(*(invDCinvABCinvA+i));
		}
		free(A1);
		free(B1);
		free(C1);
		free(D1);
		free(E1);
		free(invA);
		free(CinvAB);
		free(CinvA);
		free(DCinvAB);	
		free(invAB);
		free(invABinvDCinvAB);
		free(invABinvDCinvABCinvA);
		free(invDCinvABCinvA);
	}

	return result;
}
double** inverseA55(double** A){

	// this function returns the inverse of A's address when n is 5 by using theorem2

	double** result,**realResult;//realResult is a result of function and result is a variable which needs free function
	int i,j,k;//i,j and k are needed when we use for loops
	double** temp;//in order to free a getMijFromA, we use a temp

	if(A==NULL) //if A is NULL, we can't calculate it
		return NULL;

	result = (double**)malloc(sizeof(double*)*5);

	for(i=0;i<5;i++){
		*(result+i) = (double*)malloc(sizeof(double)*5);
		if( *(result+i) == NULL ){
			printf("system fails to allocate memory\n");
			return NULL;
		}
	}

	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if((i+j)%2==0){
				temp = getMijFromA(A,i,j,5);
				*(*(result+i)+j) = detA(temp,4) / detA55(A);
				for(k=0;k<4;k++)
					free(*(temp+k));
				free(temp);
			}
			else{
				temp = getMijFromA(A,i,j,5);
				*(*(result+i)+j) = -detA(temp,4) / detA55(A);
				for(k=0;k<4;k++)
					free(*(temp+k));
				free(temp);
			}
		}
	}

	realResult = transposeA(result,5);

	for(i=0;i<5;i++)
		free(*(result+i));
	free(result);

	return realResult;
}
double** inverseA_gaussian(double **A, int n){

	// this function returns the inverse of A's address by using gaussian elimination

	double** result; //result is a result of function
	double** E; //identity matrix
	double t;
	double ratio;//ratio and t are needed when we calculate equations
	int i,k,l,j,m;//i,k,l,j are needed when we use for loops 

	if(A==NULL) //if A is NULL,then we can't calculate it
		return NULL;

	E = (double**)malloc(sizeof(double*)*n);
	result = (double**)malloc(sizeof(double*)*n);
	if( E == NULL || result == NULL ){ //if system fails to allocate a memory, then this function returns NULL
		printf("System fails to allocate memory\n");
		return NULL;
	}
	for(i=0;i<n;i++){
		*(E+i) = (double*)malloc(sizeof(double)*n);
		*(result+i) = (double*)malloc(sizeof(double)*n);
		if( *(E+i) == NULL || *(result+i) == NULL ){
			printf("System fails to allocate memory\n");
			return NULL;
		}
	}

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j)
				*(*(E+i)+j) = 1;
			else
				*(*(E+i)+j) = 0;
		}
	}

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			*(*(result+i)+j) = *(*(A+i)+j);

	for(i=0;i<n;i++){ 
		ratio = *(*(result+i)+i);
		if( ratio == 0 ){
			for(l=i+1;l<n;l++){
				if( *(*(result+l)+l) != 0 ){
					for(m=0;m<n;m++){
						*(*(result+i)+m) += *(*(result+l)+m);
						*(*(E+i)+m) += *(*(E+l)+m);
					}
				}
			}	
		}
		ratio = *(*(result+i)+i);
		for(l=0;l<n;l++){
			*(*(result+i)+l) /= ratio;
			*(*(E+i)+l) /= ratio;
		}
		for(j=i+1;j<n;j++){
			t = *(*(result+j)+i);
			for(k=0;k<n;k++){
				*(*(result+j)+k) -= *(*(result+i)+k) * t;
				*(*(E+j)+k) -= *(*(E+i)+k) * t;
			}
		}
	}

	for(i=1;i<n;i++){
		for(j=i-1;j>=0;j--){
			t = *(*(result+j)+i);
			for(k=i;k<n;k++)
				*(*(result+j)+k) -= *(*(result+i)+k) * t;
			for(k=0;k<n;k++)
				*(*(E+j)+k) -= *(*(E+i)+k) * t;
		}	
	}


	for(i=0;i<n;i++)
		free(*(result+i));
	free(result);

	return E;
}
double** matrix_LU(double **A, double **U, double **L, int n){

	// this function returns LU matrix's address

	double** result; //result is a result of function
	double t; 
	double ratio; //t and ratio are needed when we do calculate equations
	int i,k=0,j; //i,k and j are needed when we use for loops

	if(A==NULL) //if A is NULL, we cannot calculate it
		return NULL;

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j)
				*(*(L+i)+j) = 1;
			else if(j>i)
				*(*(L+i)+j) = 0;
		}
	}

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			*(*(U+i)+j) = *(*(A+i)+j);

	for(i=0;i<n;i++){
		ratio = *(*(U+i)+i);
		if(ratio == 0) //if one of elements of diagonal is 0, then you cannot find upper/lower triangular matrix
			return NULL;
		for(j=i+1;j<n;j++){
			t = *(*(U+j)+i);
			for(k=0;k<n;k++){
				*(*(U+j)+k) -= *(*(U+i)+k) * t/ratio;
				*(*(L+j)+i) = t/ratio;
			}
		}
	}

	result = mulMatrix(L,U,n);

	return result;
}
double** transposeA(double** A,int n){

	// this function returns transposeed matrix's address

	double** result; //result is a result of function
	int i,j; //i and j are needed when we use for loops

	result = (double**)malloc(sizeof(double*)*n);
	if(result==NULL){ //if system fails to allocate memory,then function returns NULL
		printf("System fails to allocate memory\n");
		return NULL;
	}
	for(i=0;i<n;i++){
		*(result+i) = (double*)malloc(sizeof(double)*n);
		if( *(result+i) == NULL ){
			printf("System fails to allocate memory\n");
			return NULL;
		}
	}

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			*(*(result+i)+j) = *(*(A+j)+i);

	return result;
}
double** getMijFromA(double** A,int i,int j,int n){

	// this function returns subset of A which excludes i+1 row's elements and j+1 column's elements

	double** result; //result is a result of function
	int resRow,resCol; //resRow and resCol are result's row and column
	int Arow=0,Acol=0; //Arow and Acol are A's row and A's column
	int a; //a is needed when we use for loops

	result = (double**)malloc(sizeof(double*)*(n-1));
	if(result == NULL){ //if system fails to allocate memory, function returns NULL
		printf("System fails to allocate memory\n");
		return NULL;
	}
	for(a=0;a<n-1;a++){
		*(result+a) = (double*)malloc(sizeof(double)*(n-1));
		if( *(result+a) == NULL ){
			printf("System fails to allocate memory\n");
			return NULL;
		}
	}

	if(n-j==1){ 
		for(resRow=0;resRow<n-1;resRow++){
			for(resCol=0;resCol<n-1;resCol++){
				while(1){
					if(Arow==i){
						Arow++;
						continue;
					}
					else if(Acol==j){
						Acol++;
						continue;
					}
					else{
						*(*(result+resRow)+resCol) = *(*(A+Arow)+Acol);
						Acol++;
						if(Acol==n-1){
							Acol=0;
							Arow++;
						}
						break;
					}
				}
			}
		}
	}
	else{
		for(resRow=0;resRow<n-1;resRow++){
			for(resCol=0;resCol<n-1;resCol++){
				while(1){
					if(Arow==i){
						Arow++;
						continue;
					}
					else if(Acol==j){
						Acol++;
						continue;
					}
					else{
						*(*(result+resRow)+resCol) = *(*(A+Arow)+Acol);
						Acol++;
						if(Acol==n){
							Acol=0;
							Arow++;
						}
						break;
					}
				}
			}
		}
	}

	return result;
}
double detA44(double** A){

	//detA44 determines whether A is singular or nonsingular (we use this determinant when n is 4) 

	double result; //result is a result of function
	double **SubA1,**SubA2,**SubA3,**SubA4; //SubA1,SubA2,SubA3 and SubA4 are submatrix if A (3*3)
	double **A1,**B1,**C1,**D1; //A1,B1,C1 and D1 are submatrix of A (2*2)
	double **CinvA,**CinvAB,**DCinvAB,**invA; //these variables are needed when we use free function
	int i,j; //i and j are needed when we use for loops

	A1 = (double**)malloc(sizeof(double*)*2);
	B1 = (double**)malloc(sizeof(double*)*2);
	C1 = (double**)malloc(sizeof(double*)*2);
	D1 = (double**)malloc(sizeof(double*)*2);

	for(i=0;i<2;i++){
		*(A1+i) = (double*)malloc(sizeof(double)*2);
		*(B1+i) = (double*)malloc(sizeof(double)*2);
		*(C1+i) = (double*)malloc(sizeof(double)*2);
		*(D1+i) = (double*)malloc(sizeof(double)*2);
	}

	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			*(*(A1+i)+j) = *(*(A+i)+j);
			*(*(B1+i)+j) = *(*(A+i)+j+2);
			*(*(C1+i)+j) = *(*(A+i+2)+j);
			*(*(D1+i)+j) = *(*(A+i+2)+j+2);
		}
	}

	if(detA(A1,2) == 0){ //if detA(A1,2) is 0, then A is singular
		for(i=0;i<2;i++){
			free(*(A1+i));
			free(*(B1+i));
			free(*(C1+i));
			free(*(D1+i));
		}
		free(A1);
		free(B1);
		free(C1);
		free(D1);
		return 0;
	}

	invA = inverseA(A1,2);
	CinvA = mulMatrix(C1,invA,2);
	CinvAB = mulMatrix(CinvA,B1,2);
	DCinvAB = subMatrix(D1,CinvAB,2);

	if(detA(DCinvAB,2) == 0){ //if detA(DCinvAB,2) is 0, then A is singular
		for(i=0;i<2;i++){
			free(*(A1+i));
			free(*(B1+i));
			free(*(C1+i));
			free(*(D1+i));
			free(*(invA+i));
			free(*(CinvAB+i));
			free(*(DCinvAB+i));
			free(*(CinvA+i));
		}
		free(A1);
		free(B1);
		free(C1);
		free(D1);
		free(invA);
		free(CinvAB);
		free(DCinvAB);
		free(CinvA);
		return 0;
	}

	SubA1 = getMijFromA(A,0,0,4);
	SubA2 = getMijFromA(A,0,1,4);
	SubA3 = getMijFromA(A,0,2,4);
	SubA4 = getMijFromA(A,0,3,4);

	result = *(*(A+0)+0) * detA(SubA1,3) - *(*(A+0)+1) * detA(SubA2,3) + *(*(A+0)+2) * detA(SubA3,3) - *(*(A+0)+3) * detA(SubA4,3);

	for(i=0;i<3;i++){
		free(*(SubA1+i));
		free(*(SubA2+i));
		free(*(SubA3+i));
		free(*(SubA4+i));
	}
	free(SubA1);
	free(SubA2);
	free(SubA3);
	free(SubA4);

	for(i=0;i<2;i++){
		free(*(A1+i));
		free(*(B1+i));
		free(*(C1+i));
		free(*(D1+i));
		free(*(invA+i));
		free(*(CinvAB+i));
		free(*(DCinvAB+i));
		free(*(CinvA+i));
	}
	free(A1);
	free(B1);
	free(C1);
	free(D1);
	free(invA);
	free(CinvAB);
	free(DCinvAB);
	free(CinvA);

	return result;
}
double detA55(double** A){

	//detA55 determines whether A is singular or nonsingular (we use this determinant when n is 5)

	double result; //result is a result of function
	double **SubA1,**SubA2,**SubA3,**SubA4,**SubA5; //SubA1,SubA2,SubA3,SubA4 and SubA5 are submatrix of A
	int i; //i is needed when we use for loops

	SubA1 = getMijFromA(A,0,0,5);
	SubA2 = getMijFromA(A,0,1,5);
	SubA3 = getMijFromA(A,0,2,5);
	SubA4 = getMijFromA(A,0,3,5);
	SubA5 = getMijFromA(A,0,4,5);

	result = *(*(A+0)+0) * detA44(SubA1) - *(*(A+0)+1) * detA44(SubA2) + *(*(A+0)+2) * detA44(SubA3) - *(*(A+0)+3) * detA44(SubA4) + *(*(A+0)+4) * detA44(SubA5);

	for(i=0;i<4;i++){
		free(*(SubA1+i));
		free(*(SubA2+i));
		free(*(SubA3+i));
		free(*(SubA4+i));
		free(*(SubA5+i));
	}
	free(SubA1);
	free(SubA2);
	free(SubA3);
	free(SubA4);
	free(SubA5);

	return result;
}
