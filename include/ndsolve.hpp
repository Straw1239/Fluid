#ifndef NDSOLVE_HPP_INCLUDED
#define NDSOLVE_HPP_INCLUDED
#include <functional>
using std::function;



template<typename DCalc>
inline double deltaRK4(double x, double t, double h, DCalc dxdt)
{
    double hs = 0.5 * h;
    double k1 = dxdt(x, t);
    double k2 = dxdt(x + hs*k1, t + hs);
    double k3 = dxdt(x + hs*k2, t + hs);
    double k4 = dxdt(x + h*k3, t + h);

    return h/6 * (k1 + 2*(k2 + k3) + k4);
}

template<typename State, typename Derivatives>
void masterRK4(State start, Derivatives d, double h)
{
    double hs = 0.5 * h;
    double k1[start.size()];
    double temp[start.size()] = start;

    for(int i = 0; i < start.size(); i++)
    {
        k1[i] = d[i](temp);
    }
    double k2[start.size()];
    for(int i = 0; i < start.size(); i++)
    {
       temp[i] += hs * k1[i];
    }
    for(int i = 0; i < start.size(); i++)
    {
        k2[i] = d[i](temp);
    }
    double k3[start.size()];
    for(int i = 0; i < start.size(); i++)
    {
       temp[i] = state[i] + hs*k2[i];
    }
    for(int i = 0; i < start.size(); i++)
    {
        k3[i] = d[i](temp);
    }
    double k4[start.size()];
    for(int i = 0; i < start.size(); i++)
    {
       temp[i] = state[i] + h*k3[i];
    }
    for(int i = 0; i < start.size(); i++)
    {
        k4[i] = d[i](temp);
    }
    for(int i = 0; i < start.size(); i++)
    {
        start[i] += h / 6 * (k1[i] + 2*(k2[i] + k3[i]) + k4[i]);
    }


}




template<typename D>
void arrayRK4(vector<double>& x, D&& dxdt, double h)
{
    #define getDTempDT(name) for(int i = 0; i < n; i++) name[i] = dxdt(temp)[i];
    #define getTemp(xprime, step) for(int i = 0; i < n; i++) temp[i] = x[i] + step * xprime[i];
    double hs = h / 2;
    int n = x.size();
    vector<double> k1(n);
    vector<double> temp(n);
    getDTempDT(k1);
    getTemp(k1, hs);
    vector<double> k2(n);
    getDTempDT(k2);
    getTemp(k2, hs);
    vector<double> k3(n);
    getDTempDT(k3);
    getTemp(k3, h);
    vector<double> k4(n);
    getDTempDT(k4);

    for(int i = 0; i < n; i++)
    {
        x[i] += h * (k1[i] + 2*(k2[i] + k3[i]) + k4[i]) / 6;
    }


    #undef getTemp
    #undef getDTempDT

}








#endif // NDSOLVE_HPP_INCLUDED
