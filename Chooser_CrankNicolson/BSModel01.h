#ifndef BSModel01_h
#define BSModel01_h

using namespace std;
#include <vector>
//#include <cstdlib>
//#include <ctime>

//typedef vector<double> SamplePath;

class BSModel
{
   public:
       BSModel(double S0_, double r_, double sigma_) :m_S0(S0_), m_r(r_), m_sigma(sigma_) {}
      //void GenerateSamplePath(double T,int m,SamplePath& S);
       double getRate() const { return m_r; }
       double getStockPrice() const { return m_S0; }
       double getSigma() const { return m_sigma; }
       double N(const double x) const {
           return 0.5 * erfc(-(x) / sqrt(2.0));
       }
       
private:
      const double m_S0, m_r, m_sigma;
};

#endif
