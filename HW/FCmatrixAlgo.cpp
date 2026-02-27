#include <Eigen/Core>
#include<iostream>

//include metodos FCmatrixAlog e EqSolver
#include "FCmatrixAlgo.h"


using namespace std;


int pivoting(Eigen::Matrix<double,Eigen::Dynamic,1> M_coef,Eigen::VectorXd V_row_max,int i){

    int pos,size;
    
    size=M_coef.size()-i;
    Eigen::VectorXd Vet_cort_coef = M_coef.tail(size);

    //cout << "teste pivoting \n" << Vet_cort_coef << endl;

    Eigen::VectorXd Vet_cort_max = V_row_max.tail(size);


    (Vet_cort_coef.array()/Vet_cort_max.array()).maxCoeff(&pos);

    //temos de somar i pq lhe cortamos o rabo (não perdi 2 horas com isto ....... )

    return (pos+i);

}




//no pivoting 

void FCmatrixAlgo::GaussElimination(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& M_coef, Eigen::Matrix<double,Eigen::Dynamic,1>& M_consts)
{
    if((M_coef.rows() != M_consts.rows())){
        cout << "Garanta que tem tantas equações quanto constantes \n";
        return;
    }

    
    float k;
    


 for(int i=0;i<M_coef.rows()-1;i++){    
    for(int j=i+1;j<M_coef.rows();j++){
        //calculo do coeficiente
        k = M_coef(j,i)/M_coef(i,i);

        //subtração da linha i*k à j 
        M_coef.row(j)=(M_coef.row(j) - M_coef.row(i)*k);

        //subtração const linha i à const linha j
        M_consts(j)=M_consts(j)-M_consts(i)*k;
    }
 }
  return;

}


// ISTO SÓ FUNCIONA POR ACASO 

void FCmatrixAlgo::GaussEliminationPivot(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& M_coef,Eigen::Matrix<double,Eigen::Dynamic,1>& M_consts,
Eigen::Matrix<double,Eigen::Dynamic,1>& V_row_order)
{
    Eigen::VectorXd V_row_max = M_coef.cwiseAbs().rowwise().maxCoeff();

    double temp;
        cout <<"mat inicial     :\n "<< M_coef << endl;
    //matriz diagonal com
    //Eigen::MatrixXd M_row_max = V_row_max.matrix().asDiagonal();

    float k;
    int linha;
    
    for(int i=0;i<M_coef.rows()-1;i++){    

        int pos;
        //divisão termo a termo
       
        pos = pivoting(M_coef.col(i),V_row_max,i);

        //cout <<"pos "<< pos << endl;

        //troca as linhas se a linha o melhor termo não for a atual.
        if(pos != i){
            M_coef.row(i).swap(M_coef.row(pos));
            M_consts.row(i).swap(M_consts.row(pos));
            temp=V_row_order(i);
            V_row_order(i)=V_row_order(pos);
            V_row_order(pos)=temp;
        }

        cout <<"mat \n "<< M_coef << endl;


        for(int j=i+1;j<M_coef.rows();j++){
            //calculo do coeficiente
            k = M_coef(j,i)/M_coef(i,i);

            //subtração da linha i*k à j (tive de susbtituir k pela expressão pq ele estava a tripar todo)
            M_coef.row(j)=(M_coef.row(j) - M_coef.row(i)*(M_coef(j,i)/M_coef(i,i)));

            //subtração const linha i à const linha j
            M_consts(j)=M_consts(j)-M_consts(i)*(M_coef(j,i)/M_coef(i,i));
        }
        cout <<"mat apos elim ---------------- \n "<< M_coef << endl;
        
    }

}


 void FCmatrixAlgo::LUdecomposition(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& M_coef,Eigen::Matrix<double,Eigen::Dynamic,1>& M_consts, 
bool bpivot){

    double temp,k;
    Eigen::MatrixXd L = Eigen::MatrixXd::Identity(M_coef.rows(), M_coef.rows());

    if(((M_coef.rows() != M_consts.rows()))|| (M_coef.rows() != M_coef.cols())){
        cout << "Garanta que tem tantas equações quanto constantes \n";
        return;
    }

    Eigen::VectorXd V_row_max = M_coef.cwiseAbs().rowwise().maxCoeff();

    for(int i=0;i<M_coef.rows()-1;i++){    

        if(bpivot){

            int pos;
      
            pos = pivoting(M_coef.col(i),V_row_max,i);

            //cout <<"pos "<< pos << endl;

            //troca as linhas se a linha o melhor termo não for a atual.
            if(pos != i){
                M_coef.row(i).swap(M_coef.row(pos));
                M_consts.row(i).swap(M_consts.row(pos));
                
            }        
        }

        for(int j=i+1;j<M_coef.rows();j++){
            //calculo do coeficiente
            k = M_coef(j,i)/M_coef(i,i);

            //subtração da linha i*k à j (tive de susbtituir k pela expressão pq ele estava a tripar todo)
            M_coef.row(j)=(M_coef.row(j) - M_coef.row(i)*(M_coef(j,i)/M_coef(i,i)));

            //subtração const linha i à const linha j
            M_consts(j)=M_consts(j)-M_consts(i)*(M_coef(j,i)/M_coef(i,i));
            L(j,i)=M_coef(j,i)/M_coef(i,i);

        }
    }
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(M_coef.rows(), M_coef.rows());
    M_coef = M_coef+L-I;
    return;
}


/*static void FCmatrixAlgo:: GaussEliminationPivot(Matrix<double,Dynamic,Dynamic>& coeffs, Matrix<double,Dynamic,1>& consts,Matrix<double,Dynamic,1>& indexing){
    const int rows = coeffs.rows();
    const int cols = coeffs.cols();
    indexing.resize(rows);
    const double tolerance=1e-6;

    for (int i = 0; i < rows-1; i++) {
        double valMax=0;
        int indexMax=i;

        for (int j=i; j<rows; j++){
            if (abs(coeffs(j,i))>valMax){
                valMax=abs(coeffs(j,i));
                indexMax=j;
            }
        }

        if(valMax<tolerance){
            cout<<"A matriz é singular."<<endl;
        }

        if (indexMax != i) {
            U.row(i).swap(coeffs.row(indexMax));
            swap(indexing(i), indexing(indexMax));
        }
  

        for (int j= i+1; j<rows; j++){ 
            const double lambda= coeffs(j,i)/coeffs(i,i);
            coeffs.row(j)-=lambda*coeffs(i); // alterar os coeficientes 
            consts(j)-= lambda*consts(i);// alterar as constantes (vetor)
        }
    }

    for (int i = rows - 1; i >= 0; i--) {
        consts(i) /= coeffs(i, i); 
        coeffs.row(i) /= coeffs(i, i);
        for (int j = i - 1; j >= 0; j--) {
            coeffs.row(j) -= coeffs(j, i) * coeffs.row(i);
            consts(j) -= coeffs(j, i) * consts(i);
        }
    }
}
*/



//LU decomposition


/*
static void FCmatrixAlgo::LUdecomposition(Matrix<double,Dynamic,Dynamic>& coeff){
  int rows = coeff.rows(); //Obtém o número de linhas da matriz coeff
    MatrixXd L = MatrixXd::Identity(n, n); // Criar uma matriz identidade L  
    MatrixXd U = coeff; // Criar uma matriz U que é uma cópia de coeff

    for(int k=0; k<rows; k++){ 
        for (int i=k+1; i<rows; i++){
            double s=U(i,k)/U(k,k); //aqui deviamos dividir pelo maximo em modulo de cada linha não por U(k,k)
            L(i,k)=s;
            for(int j=k; j<rows; j++){
                U(i,j)-=s*U(k,j);
            }
        }
    }
    cout << "A matriz é L:" << endl << L << endl;
    cout << "A matriz é U:" << endl << U << endl;
}


static void FCmatrixAlgo::LUdecompositionPivot(Matrix<double,Dynamic,Dynamic>& coeff, Matrix<double,Dynamic,1>& indexing){
    int rows = coeff.rows();
    MatrixXd L = MatrixXd::Identity(rows, rows);
    MatrixXd U = coeff;
    indexing.resize(rows);

    for (int k = 0; k < rows; k++) { //linhas da coef (não devia ser rows-1?)
        double valMax = 0.;
        int indexMax = k;

        for (int i = k; i < rows; i++) {
            if (abs(U(i, k)) > valMax) {
                valMax = abs(U(i, k));
                indexMax = i;
            }
        }

        if (valMax == 0.) {
            cout << "A matriz não pode ser decomposta LU com pivoting .\n" << endl;
        }

        if (indexMax != k) {
            U.row(k).swap(U.row(indexMax));
            L.row(k).swap(L.row(indexMax));
            swap(indexing(k), indexing(indexMax));
        }

        for (int i = k + 1; i < rows; ++i) {
            double s = U(i, k)/U(k, k);
            L(i,k) =s;
            for (int j=k; j<rows; j++) {
                U(i,j) -= s*U(k, j);
            }
        }
    } 
}

*/



