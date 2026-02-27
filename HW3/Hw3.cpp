#include<iostream>

#include"FCmatrixAlgo.h" // //include metodos FCmatrixAlog e classe EqSolver
#include "EqSolver.h"

using namespace std;
using namespace Eigen;


int main(){

    FCmatrixAlgo Algo;

    /*
    Eigen::MatrixXd M1(3,3);
    M1 << 2,2,3,
    4,6,7,
    7,7,7;

    Eigen::MatrixXd M2(3,3);
    M2 << 2,2,3,
    4,6,7,
    7,7,7;

    Eigen::VectorXd V1(3);
    V1 << 1,2,3;

    Eigen::VectorXd V2(3);
    V2 << 1,2,3;

    Eigen::VectorXi Row_order(3);
    Row_order << 1,2,3;



    Algo.GaussElimination(M1,V1);

    cout << "matriz nova \n\n\n" << M1 << "\n consts novas \n" << V1 << "\n";


    Algo.GaussEliminationPivot(M2,V2,Row_order);

    cout << "matriz nova \n\n\n" << M2 << "\n consts novas\n" << V2 << "\n";

    */



    Eigen::MatrixXd M(4,4);
    M <<80,-30,-50,0, 
    -30,65,-10,-20,  
    -50,-10,100,-25,
    0,-20,-25,100;

    Eigen::VectorXd b(4);
    b << 20,0,0,0;

    EqSolver Prob(M,b);

    cout << Prob.LUSolver(false) << endl << "\n";

    cout << Prob.LUSolver(true) << endl << "\n";

    Eigen::VectorXd results_jacob(b.rows()); //tem de se por o tamanho correro a priori
    int it_max = 2000;

    cout << Prob.GaussSolver(true) << endl << "\n";

    cout << Prob.GaussSolver(false) << endl;



    Prob.IterativeJacobiSolver(results_jacob,it_max,0.0001);

    cout << "iter jacob \n" << results_jacob << endl;

    Prob.IterativeGaussSeidelSolver(results_jacob,it_max,0.0001);

    cout << "iter gauss sei \n" << results_jacob << endl;





    return 0;
}


