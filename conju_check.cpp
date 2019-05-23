#include <bits/stdc++.h>
using namespace std;

const double NEARZERO = 1.0e-10;       // interpretation of "zero"

void print( double* V , int n);
void print( double** A , int n);
void matrixTimesVector( double** A, double* V, double* ans, int n);
void vectorCombination( double a, double* U, double b, double* V, double* W, int n );
double innerProduct( double* U, double* V, int n );
double vectorNorm( double* V , int n);
void conjugateGradientSolver( double** A, double* B, double* X, int n );
void transpose(double** A, double** B, int n);
//======================================================================


int main()
{	clock_t start, end; 
	
	int i, j, k;
	int n=22, m=1000;
	double error = 0.01;
	double** A = new double*[n];
	for(i=0; i<n; i++){
		A[i]= new double[n];
	}
	double* B = new double[n];
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			cin >> A[i][j];
		}
	}
	for(i=0; i<n; i++){
		cin >> B[i];
	}
	cout << "Generated Matrix a is " << endl;
    for(i=0; i<n; ++i){
        for(j=0; j<n; ++j){
			cout << A[i][j] << " ";
        }
        cout << endl;
	}

	cout << "Generated Matrix b is " << endl;
    for(i=0; i<n; ++i){
		cout << B[i] << " ";
	}
    cout << endl;
	
	double* X = new double[n]();
	start=clock();
	conjugateGradientSolver( A, B, X, n);
	end = clock();
	long double time_take = (long double)(end-start)/(long double)(CLOCKS_PER_SEC);
	cout << "Time taken " << time_take << " sec"<<endl;
	cout << "\nX:";
	print( X, n );
	matrixTimesVector( A, X, B, n ); 
	cout << "\nCheck AX:";
	print(B, n);
}


//======================================================================

void transpose(double** A, double** B, int n){
	int i, j;
	for (i = 0; i <n ; i++){
		for (j = 0; j < n; j++){
			B[i][j] = A[j][i];
		}
	}
}

void print( double* V , int n){
	int i;
	for (i = 0; i < n; i++ ){
		double x = V[i];   if ( abs( x ) < NEARZERO ) x = 0.0;
		cout << x << '\t';
	}
	cout << '\n';
}


//======================================================================


void print( double** A , int n){
	int i, j;								 // A is an n x n matrix
	for ( i = 0; i < n; i++ ){
		for ( j = 0; j < n; j++ ){
			double x = A[i][j];   if ( abs( x ) < NEARZERO ) x = 0.0;
			cout << x << '\t';	
		}
		cout << '\n';
	}
}


//======================================================================


void matrixTimesVector( double** A, double* V, double* ans, int n){
	int i;
	for ( i = 0; i < n; i++ ) ans[i] = innerProduct( A[i], V, n );
}


//======================================================================


void vectorCombination( double a, double* U, double b, double* V, double* W, int n ){        // Linear combination of vectors
	int j;
	for ( j = 0; j < n; j++ ) W[j] = a * U[j] + b * V[j];
}


//======================================================================


double innerProduct( double* U, double* V, int n ){
	double ans=0.0;
	int i;
	for(i=0; i<n; i++){
		ans+=U[i]*V[i];
	}
	return ans;
}


//======================================================================


double vectorNorm( double* V , int n){
	return sqrt( innerProduct( V, V, n ) );
}


//======================================================================


void conjugateGradientSolver( double** A, double* B, double* X, int n ){
	double TOLERANCE = 1.0e-10;
	double* P = new double[n];
	double* R = new double[n];
	double* Rold = new double[n];
	double* AP = new double[n];
	int i, k=0;
	for(i=0; i<n; i++){
		P[i]=B[i];
		R[i]=B[i];
	}

	while ( k < n ){
		for(i=0; i<n; i++){
			Rold[i] = R[i];
		}
		matrixTimesVector(A, P, AP, n);
		double alpha = innerProduct( R, R, n ) / max( innerProduct( P, AP, n ), NEARZERO );
		vectorCombination( 1.0, X, alpha, P, X, n );            // Next estimate of solution
		vectorCombination( 1.0, R, -alpha, AP, R, n );          // Residual

		if ( vectorNorm( R, n ) < TOLERANCE ) break;             // Convergence test

		double beta = innerProduct( R, R, n ) / max( innerProduct( Rold, Rold, n ), NEARZERO );
		vectorCombination( 1.0, R, beta, P,  P, n);             // Next gradient
		k++;
	}
	cout << "iterations --- " <<k << endl; 
	delete [] P;
	delete [] R;
	delete [] Rold;
	delete [] AP;

}
