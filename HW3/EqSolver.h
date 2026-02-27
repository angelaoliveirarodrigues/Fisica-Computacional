#include <iostream>
#include <memory>
#include<Eigen/Dense>

using namespace std;
using namespace Eigen;

class EqSolver {
        public:
        // constructors and destructor
        EqSolver();
        EqSolver(const Matrix<double,Dynamic,Dynamic>& M, // matrix coeffs
        const Matrix<double,Dynamic,1>& b); // vector of constants
        ~EqSolver() = default;

        // output (optional)
        friend ostream& operator<<(ostream& os, const EqSolver& solver);
        
        // solvers
        const Matrix<double,Dynamic,1>& GaussSolver(bool pivot=false);

        const Matrix<double,Dynamic,1>& LUSolver(bool pivot=false);

        void IterativeJacobiSolver(Matrix<double,Dynamic,1>& x,
        int& itmax, //nb of max iterations
        double tol=1.E-3); // tolerance on convergence


        void IterativeGaussSeidelSolver(Matrix<double,Dynamic,1>& x,
        int& itmax,
        double tol=1.E-3);


        private:
        Matrix<double,Dynamic,Dynamic> M; // coefficients matrix
        Matrix<double,Dynamic,1> b; // constants vector
        Matrix<double,Dynamic, 1> x_sol; //solution vector
};



