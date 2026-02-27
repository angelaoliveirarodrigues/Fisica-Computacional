#ifndef __INTEGDERIV__
#define __INTEGDERIV__
#include "Functor.h"
using namespace std;

class IntegDeriv {
    public:
        IntegDeriv(Functor&);
        ~IntegDeriv() = default;

    // integration methods
        void TrapezoidalRule(double xi, double xf, double& Integral, double& Error);
        void simpsonRule(double xi, double xf, double& Integral, double& Error);
        void MidPoint(double xi, double xf, double& Integral, double& Error);

//derivative methods
        double forwarddiff(double xi, double xf, double& Derivative);
        double centraldiff (double xi, double xf,double& Derivative);
        double backwarddiff (double xi, double xf, double& Derivative);
        double fivepoint (double xi, double xf, double& Derivative);
        double threepoint (double xi, double xf, double& Derivative);
        double threePointDiff(double xi, double xf, int order);
        double fivePointDiff(double xi, double xf, int order);
    private:
        Functor& F;
};

#endif