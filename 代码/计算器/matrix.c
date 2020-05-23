/*
	可进行9个10x10矩阵的加法，数乘，转置，乘法，求伴随矩阵，求行列式，求逆 
*/ 
#include<stdio.h>
#include<math.h>
#include<string.h>


double MatAns[11][11],Matt[11][11],Matt2[11][11],MatA[11][11],MatB[11][11];  //MatA,MatB: used to calc
double Mat[10][11][11];  //used to store; coded from 1 to 9;
int MatAns_info[2],Matt_info[2],Matt2_info[2],MatA_info[2],MatB_info[2],Mat_info[10][2];  //0: rows;1: cols
int er = 0;  //1：数组越界；2：加法矩阵不同型；3：乘法出错；4：行列式，伴随矩阵，求逆，不是方阵；5：逆矩阵不存在 

void Matplus(double Mata[11][11],double Matb[11][11],int Mata_info[2],int Matb_info[2]){
	int rowa = Mata_info[0],cola = Mata_info[1];
	int rowb = Matb_info[0],colb = Matb_info[1];
	
	int i,j;
	if(rowa>10 || rowb>10 || cola>10 || colb>10){er = 1;return;}
	if(rowa != rowb || cola != colb){er = 2;return;}
	
	Matt_info[0] = rowa;Matt_info[1] = cola;
	for(i=1;i<=rowa;i++){
		for(j=1;j<=cola;j++){
			Matt[i][j] = Mata[i][j] + Matb[i][j];
		}
	}
}

void MatnumMul(int k,double Mata[11][11],int Mata_info[2]){
	int rowa = Mata_info[0],cola = Mata_info[1];
	int i,j;
	
	Matt_info[0] = rowa;Matt_info[1] = cola;
	for(i=1;i<=rowa;i++){
		for(j=1;j<=cola;j++){
			Matt[i][j] = k*Mata[i][j];
		}
	}
}

void T(double Mata[11][11],int Mata_info[2]){
	int rowa = Mata_info[0],cola = Mata_info[1];
	int i,j;
	
	Matt2_info[0] = cola;Matt2_info[1] = rowa;
	for(j=1;j<=rowa;j++){
		for(i=1;i<=cola;i++){
			Matt2[i][j] = Mata[j][i];
		}
	}	
}
void MatMulti(double Mata[11][11],int Mata_info[2],double Matb[11][11],int Matb_info[2]){
	int rowa = Mata_info[0],cola = Mata_info[1];
	int rowb = Matb_info[0],colb = Matb_info[1];
	int i,j,k;
	if(rowa>10 || rowb>10 || cola>10 || colb>10){er = 1;return;}
	if(cola != rowb){er = 3;return;}
	
	Matt_info[0] = rowa;Matt_info[1] = colb;
	for(i=1;i<=rowa;i++){
		for(j=1;j<=colb;j++){
			double tmp = 0;
			for(k=1;k<=cola;k++){
				tmp += Mata[i][k]*Matb[k][j];
			}
			Matt[i][j] = tmp;
		}
	}
}
double MatDet(double Mata[11][11],int Mata_info[2]){
	int rowa = Mata_info[0],cola = Mata_info[1],mat_info[2];
	double mat[11][11];
	int i,j,k;
	memset(mat,0,sizeof(mat));
	if(rowa != cola){er = 4;return 0;}
	if(rowa == 1){return Mata[1][1];}
	if(rowa == 2){return Mata[1][1]*Mata[2][2] - Mata[2][1]*Mata[1][2];}
	mat_info[0] = mat_info[1] = rowa - 1;
	
	double res = 0;
	for(i=1;i<=rowa;i++){
		for(k=2;k<=rowa;k++){
			for(j=1;j<=cola;j++){
				if(j==i) continue;
				if(j<i) {mat[k-1][j] = Mata[k][j];} 
				if(j>i) {mat[k-1][j-1] = Mata[k][j];}
			}
		}
		int flag = 1;
		if((1+i)%2){flag = -1;}
		res += Mata[1][i] * flag * MatDet(mat,mat_info);
	}
	return res;
}

void MatAdj(double Mata[11][11],int Mata_info[2]){
	int rowa = Mata_info[0],cola = Mata_info[1],mat_info[2];
	double mat[11][11];
	int i,j,p,q;
	memset(mat,0,sizeof(mat));
	if(rowa != cola){er = 4;return;}
	mat_info[0] = mat_info[1] = rowa - 1;
	
	double res = 0;
	for(i=1;i<=rowa;i++){
		for(j=1;j<=cola;j++){
			for(p=1;p<=rowa;p++){
				if(p == i) continue;
				for(q=1;q<=cola;q++){
					if(q == j) continue;
					int row = p,col = q;
					if(p>i) row--;if(q>j) col--;
					mat[row][col] = Mata[p][q];
				}
			}
			res = MatDet(mat,mat_info);
			int flag = 1;
			if((i+j)%2) {flag = -1;}
			Matt2[j][i] = flag * res;
		}
	}
	Matt2_info[0] = Matt2_info[1] = rowa;
}
void MatInv(double Mata[11][11],int Mata_info[2]){
	int rowa = Mata_info[0],cola = Mata_info[1],mat_info[2];
	double mat[11][11];
	int i,j,p,q;
	memset(mat,0,sizeof(mat));
	if(rowa != cola){er = 4;return;}
	double t = MatDet(Mata,Mata_info);
	if(t == 0){er = 5;return;}
	mat_info[0] = mat_info[1] = rowa - 1;
	
	
	double res = 0;
	for(i=1;i<=rowa;i++){
		for(j=1;j<=cola;j++){
			for(p=1;p<=rowa;p++){
				if(p == i) continue;
				for(q=1;q<=cola;q++){
					if(q == j) continue;
					int row = p,col = q;
					if(p>i) row--;if(q>j) col--;
					mat[row][col] = Mata[p][q];
				}
			}
			res = MatDet(mat,mat_info);
			int flag = 1;
			if((i+j)%2){flag = -1;}
			Matt2[j][i] = flag * res / t;
		}
	}
	
	Matt2_info[0] = Matt2_info[1] = rowa;
}
int main(){
//	example
	int i,j;
	for(i=1;i<=4;i++){
		for(j=1;j<=4;j++){
			Mat[0][i][j] = 0;
			Mat[1][i][j] = 2;
		}
	}
	Mat_info[0][0] = 3;Mat_info[0][1] = 3;
	Mat_info[1][0] = Mat_info[1][1] = 4;
	Mat[0][1][1] = Mat[0][2][2] = Mat[0][3][3] = Mat[0][4][4] = 3;
	Mat[0][1][4] = 3;
	
//	plus
//	Matplus(Mat[0],Mat[1],Mat_info[0],Mat_info[1]);

//	number multiply
//	MatnumMul(5,Mat[0],Mat_info[0]);

//  Transpose
//	T(Mat[0],Mat_info[0]);

//	multiply
//	MatMulti(Mat[0],Mat[1],Mat_info[0],Mat_info[1]);

//	determinant
//	printf("%.2f\n",MatDet(Mat[0],Mat_info[1]));

//	adjoint matrix
//	MatAdj(Mat[0],Mat_info[1]);

//	inverse matrix
//	MatInv(Mat[0],Mat_info[1]);
//	for(i=1;i<=4;i++){
//		for(j=1;j<=4;j++){
//			printf("%.2f ",Matt2[i][j]);
//		}
//		printf("\n");
//	}
//	MatMulti(Matt2,Matt2_info,Mat[0],Mat_info[1]);
//	for(i=1;i<=4;i++){
//		for(j=1;j<=4;j++){
//			printf("%.2f ",Matt[i][j]);
//		}
//		printf("\n");
//	}
} 
