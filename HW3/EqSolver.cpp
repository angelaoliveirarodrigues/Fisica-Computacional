#include <Eigen/Dense>
#include<iostream>
#include<cassert>
#include <cmath>
#include "EqSolver.h"
#include "FCmatrixAlgo.h"


/*
Subsitui a matrix da MrowOrder por um vetor criado da maneira que estava no discord


Acrescentei no LuDecomp a parte de trocar a ordem das constantes 
(passei a usar o b da classe em vez do b_copy para fazer os calculos uma vez que o valor nunca é alterado)

!!Importante!! 
Troquei o nome do x na pertencente à classe EqSolver Havia 2 variaveis com o mesmo nome por todo o lado

---------------------------------------------------
O novo nome do x membro da classe eq solver é x_sol
----------------------------------------------------

De certeza que ia dar problemas e não permitia compilar pq estavamos a retornar 
uma variavel x (que era um Eigen::vector logo provavelmente um ponteiro, local)
Agora retornamos o proprio x membro da classe 
É possivel que dê problemas com estarmos sempre a alterar o valor do x mas só vai acontecer nos metodos iterativos
Uma vez que nesses metodos as funções não retornam nada. A solução é pô las a retornar um vetor como as outras.

Acrescenteu nos metodos de eliminação de gauss um if para colocar os termos que dão acima de 0 devido a erros de arredondamento =0

Troquei b_copy de sitio no GaussSolver

*/




using namespace std;
using namespace Eigen;

EqSolver::EqSolver(){}

EqSolver::EqSolver(const Matrix<double,Dynamic,Dynamic>& coeffs, const Matrix<double,Dynamic,1>& consts): M(coeffs), b(consts) {}


ostream& operator<<(ostream& out, const EqSolver& solver){
    out<< "Matriz de Coeficientes (M): \n"<< solver.M <<endl;
    out<< "Vetor de Constantes (b): \n" << solver.b <<endl;
    return out;
}

const Matrix<double,Dynamic,1>& EqSolver::GaussSolver(bool pivot){
    assert(M.cols()==b.rows()); //verificar se as dimensões são compatíveis

    Matrix<double,Dynamic, Dynamic> N=M; // cópia da matriz de coeficientes 
    VectorXi MrowOrder= VectorXi::LinSpaced(N.cols(), 0, N.cols()-1);


    Matrix<double,Dynamic,1> b_copy=b; //cópia do vetor das constantes


    if (!pivot){ // se pivot falso, GaussElimination
        FCmatrixAlgo::GaussElimination(N,b_copy);

    }else{// se pivot, GaussEliminationPivot
        FCmatrixAlgo::GaussEliminationPivot(N,b_copy,MrowOrder);
    }
    
    //back substitution algorithm
    int n = N.cols();

    Matrix<double,Dynamic,1> x(n); //vetor com as soluções
    Matrix<double, Dynamic,1> x_copy=x; //vetor cópia das soluções

    for (int i=n-1; i>=0;i--) {
        double sum=0.;
        for (int j=i+1; j<n;j++) {
            sum+= N(i,j)*x(j);
        }
        x(i)=(b_copy(i)-sum)/N(i,i);
    }

    
    /*if (pivot){
       for(int i=0; i<n; i++){
            x_copy(MrowOrder(i))=x(i);
       } 
        this->x_sol=x_copy;
        return x_sol; 
    }else{*/

    this->x_sol=x;
    return x_sol;
       
}


const Matrix<double,Dynamic,1>& EqSolver::LUSolver(bool pivot){
    assert(M.cols() == b.rows()); //verificar se as dimensões são compatíveis

    Matrix<double,Dynamic, Dynamic> N=M; // cópia da matriz de coeficientes 
    VectorXi MrowOrder= VectorXi::LinSpaced(N.cols(), 0, N.cols()-1);


    int n= N.rows();
    //LU decomp
    //Matrix<int,Dynamic,1> pivotIn(n);
    FCmatrixAlgo::LUdecomposition(N,MrowOrder, pivot);


    //trocar valor das constantes de acordo com as trocas que foram feitas na LUdecomp
    //se houver pivotagem
    Matrix<double,Dynamic,1> b_copy=b; 

    if(pivot){

        for(int i=0;i<b.rows();i++){
            b_copy(i) = b(MrowOrder(i));
        }
    }

    
    Matrix<double,Dynamic,1> y(n);
    Matrix<double,Dynamic,1> x(n);
    Matrix<double,Dynamic,1> x_copy=x; //vetor cópia das soluções

    
    //forward solution (Ly=b)
    for(int i=0; i<n; i++){
        double sum=0.;
        for(int j=0; j<i; j++){
            sum+= y(j)*N(i,j);
        }
        y(i)=b_copy(i)-sum;
    }
    
    //backward solution (Ux=y)
    for(int k=n-1; k>=0; k--){
        double sum=0.;
        for(int i=k+1; i<n; i++){
            sum+= x(i)*N(k,i);
        }
        x(k)=(y(k)-sum)/N(k,k);
    }
    //
    /*if (pivot){
       for(int i=0; i<n; i++){
            x_copy(MrowOrder(i))=x(i);
        } 
        this-> x_sol=x_copy;
        return x_sol; 
    }else{ }*/
    this->x_sol=x;
    return x_sol;
    
}



void EqSolver::IterativeJacobiSolver(Matrix<double,Dynamic,1>& x,int& itmax, double tol){

    assert(M.cols() == b.rows());

    Matrix<double, Dynamic, Dynamic> N = M;
    Matrix<double, Dynamic, 1> b_copy = b;
    int n = N.cols();
    x.setZero();
    Matrix<double, Dynamic, 1> x_anterior = x;

    cout << N << endl;

    cout << x(1) << endl;
    
    for (int iter = 0; iter < itmax; iter++) {
        x_anterior = x;
        cout << "tetseetetettetetetete \n" << N << endl;;

        for (int i = 0; i < n; i++) {
                      
            x(i) = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    x(i) = x(i) - N(i, j)*x_anterior(j);
                    //cout << x(i) << endl;

                }
            }
            x(i) =x(i)+b_copy(i);
            x(i) = x(i)/N(i, i);
            //cout << x(i) << endl;
        }
         if ((x - x_anterior).lpNorm<1>() < tol) {
            break;
        }
        //x_anterior = x;
    }
    this->x_sol = x;

   /* int iterations=0;
    float error = tol+1;
    while (iterations < itmax && error > tol) {
        x = (b - N * x_anterior).cwiseQuotient(N.diagonal()); // Jacobi update
        
        error = (x - x_anterior).norm(); // calculate error
        
        x_anterior = x; // update solution
        
        iterations++;
    }
*/
    std::cout << "Solution:\n" << x_anterior << std::endl;
    
}
  
    
    

void EqSolver::IterativeGaussSeidelSolver(Matrix<double,Dynamic,1>&x ,int& itmax,double tol){
    
    assert(M.cols() == b.rows());

    Matrix<double,Dynamic,Dynamic> N=M;
    Matrix<double, Dynamic,1> b_copy=b;
    int n =N.cols();
    Matrix<double,Dynamic,1> x_anterior=x;

    for(int iter=0; iter<itmax; iter++){
        for(int i=0; i<n; i++){
            x(i)=0;
            for(int j=0; j<n; j++){
                if(i!=j){
                    x(i)+=-N(i,j)*x(j);
                } 
            }    
            x(i)+=b_copy(i);
            x(i)/=N(i,i);   
        }
        if ((x-x_anterior).lpNorm<1>()<tol){
            break; 
        }
        x_anterior = x; // Update do valor de x_anterior 
    }
    this->x_sol = x;
}   