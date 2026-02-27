
#include <Eigen/Core>
//#include<iostream>
#include <cmath>


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

    //temos de somar i pq lhe cortamos o final
    
    int pos_ret=pos+i;
    //return (pos+i);
    return pos_ret;

}




//no pivoting 

void FCmatrixAlgo::GaussElimination(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& M_coef, Eigen::Matrix<double,Eigen::Dynamic,1>& M_consts)
{
    if((M_coef.rows() != M_consts.rows())){
        cout << "Garanta que tem tantas equações quanto constantes \n";
        return;
    }

    double tol = 1.E-3;

    
    double k;
    

 for(int i=0;i<M_coef.rows()-1;i++){  

    if(abs(M_coef(i,i)) <= tol){

         cout << "matriz é singular ou quase singular \n";
         return;
    } 
    
 
    for(int j=i+1;j<M_coef.rows();j++){
        //calculo do coeficiente
        k = M_coef(j,i)/M_coef(i,i);

        //subtração da linha i*k à j 
        M_coef.row(j)=(M_coef.row(j) - M_coef.row(i)*(M_coef(j,i)/M_coef(i,i)));
        if(abs(M_coef(j,i)) < 1.E-5){M_coef(j,i)=0;}

        //subtração const linha i à const linha j
        M_consts(j)=M_consts(j)-M_consts(i)*k;
    }
 }

}


// ISTO SÓ FUNCIONA POR ACASO 

void FCmatrixAlgo::GaussEliminationPivot(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& M_coef,Eigen::Matrix<double,Eigen::Dynamic,1>& M_consts,
Eigen::VectorXi& V_row_order)
{
    Eigen::VectorXd V_row_max = M_coef.cwiseAbs().rowwise().maxCoeff();

    double temp,consts_temp;
    // cout <<"mat inicial     :\n "<< M_coef << endl;
    //matriz diagonal com
    //Eigen::MatrixXd M_row_max = V_row_max.matrix().asDiagonal();

    double k;
    int linha;

    double tol = 1.E-3;
    
    for(int i=0;i<M_coef.rows()-1;i++){    

        int pos;
        //posição do melhor termo para ser o pivot
        pos = pivoting(M_coef.col(i),V_row_max,i);

        //troca as linhas se a linha o melhor termo não for a atual.
        if(pos != i){
            //troca linhas matriz
            M_coef.row(i).swap(M_coef.row(pos));

            //troca constantes
            consts_temp = M_consts(i);
            M_consts(i)=M_consts(pos);
            M_consts(pos)=consts_temp;

           //M_consts.row(i).swap(M_consts.row(pos));

            //troca indices
            temp=V_row_order(i);
            V_row_order(i)=V_row_order(pos);
            V_row_order(pos)=temp;
        }

        //cout <<"mat \n "<< M_coef << endl;


        for(int j=i+1;j<M_coef.rows();j++){
            if(abs(M_coef(i,i)) <= tol){

                cout << "matriz é singular ou quase singular \n";
                return;
            }

            //calculo do coeficiente
            k = M_coef(j,i)/M_coef(i,i);

            //subtração da linha i*k à j 
            M_coef.row(j)=(M_coef.row(j) - M_coef.row(i)*(M_coef(j,i)/M_coef(i,i)));

            if(abs(M_coef(j,i)) < 1.E-5){M_coef(j,i)=0;}

            //subtração const linha i à const linha j
            M_consts(j)=M_consts(j)-M_consts(i)*k;
        }
        //cout <<"mat apos elim ---------------- \n "<< M_consts << endl;
        
    }

}

void FCmatrixAlgo::LUdecomposition(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& M_coef,Eigen::Matrix<int,Eigen::Dynamic,1>& M_consts, 
bool bpivot){

    double temp,k;
    Eigen::MatrixXd L = Eigen::MatrixXd::Identity(M_coef.rows(), M_coef.rows());

    if(((M_coef.rows() != M_consts.rows()))|| (M_coef.rows() != M_coef.cols())){
        cout << "Garanta que tem tantas equações quanto constantes \n";
        return;
    }
    
    double tol = 1.E-3;

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

         if(abs(M_coef(i,i)) <= tol){

                cout << "matriz é singular ou quase singular \n";
                return;
            }

        for(int j=i+1;j<M_coef.rows();j++){
            //calculo do coeficiente
            k = M_coef(j,i)/M_coef(i,i);

            //subtração da linha i*k à j (tive de susbtituir k pela expressão pq ele estava a tripar todo)
            M_coef.row(j)=(M_coef.row(j) - M_coef.row(i)*(M_coef(j,i)/M_coef(i,i)));

            if(abs(M_coef(j,i)) < 1.E-5){M_coef(j,i)=0;}

            //Preenchimento matriz L
            L(j,i)=k;

        }
    }
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(M_coef.rows(), M_coef.rows());
    M_coef = M_coef+L-I;
    return;
}

