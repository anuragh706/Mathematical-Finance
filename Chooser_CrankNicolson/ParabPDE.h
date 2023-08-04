#ifndef ParabPDE_h
#define ParabPDE_h

class ParabPDE
{
   public:
      ParabPDE(const double T_, const double xl_, const double xu_) :m_T(T_), m_xl(xl_), m_xu(xu_) {}
      virtual double a(double t, double x)=0;
      virtual double b(double t, double x)=0;
      virtual double c(double t, double x)=0;
      virtual double d(double t, double x)=0;

      virtual double f(double x)=0;
      virtual double fu(double t)=0;
      virtual double fl(double t)=0;
      double getxl() { return m_xl; }
      double getxu() { return m_xu; }
      double getT() { return m_T; }
protected:
       const double m_T, m_xl, m_xu;
};

#endif
