#include "FCmatrixAlgo.h"
#include <Eigen/Core>
#include <iostream>

using namespace std;
using namespace Eigen;
//zqwkdj
void FCmatrixAlgo::GaussElimination(Matrix<double,Dynamic,Dynamic>& M,
Matrix<double,Dynamic,1>& MC ){
    if (M.cols() != MC.rows()){ //erros e tals
        throw invalid_argument("make sure the number of equations is the same as the number of constants."); 
    }
    else{
        for (int i=0; i<M.rows(); i++){
            if (M(i,i)== 0.){ //só p fazer swap nas rows caso a entrada seja nula e noutras rows mais abaixo tenha não nulas
                for (int j=i; j<M.rows(); j++){
                    if (M(i,j)!=0){M.row(i).swap(M.row(j)); MC.row(i).swap(MC.row(j)); break;}
                
                    for (int k=i+1; k<M.rows(); k++){ //pôr logo todas as rows abaixo com a entrada nula
                        if (k>=M.rows()){break;}
                        else{
                M.row(k) = M.row(k)-M.row(i)*(M(k,i)/M(i,i)); MC.row(k)=MC.row(k)-MC.row(i)*(M(k,i)/M(i,i));
                    }}

                }
        }
            else{
                for (int k=i+1; k<M.rows(); k++){ //pôr logo todas as rows abaixo com a entrada nula
                    if (k>=M.rows()){break;}
                else{
                MC.row(k)=MC.row(k)-MC.row(i)*(M(k,i)/M(i,i)); M.row(k) = M.row(k)-M.row(i)*(M(k,i)/M(i,i));
            }
                }
        }
    }
    } //estes parêntesis estão grande confusão..

void FCmatrixAlgo::GaussEliminationPivot(Matrix<double,Dynamic,Dynamic>& M,
Matrix<double,Dynamic,1>& MC ){

}
    

