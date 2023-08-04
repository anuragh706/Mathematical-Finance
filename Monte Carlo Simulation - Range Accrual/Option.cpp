#include "Option.h"
Results Option::PriceByMC(BSModel* Model, unsigned int N,unsigned int D, const double eps) const {

	Stats1 s1;
	unsigned int tempsim = 100;
	for (int i = 0; i < tempsim; i++) {
	
		vector<double> SamplePath(static_cast<int>(D * m_T));
		//cout << SamplePath.size() << endl;
		Model->GeneratePath(SamplePath, m_T, D, eps);
		const double p1 = payoff(SamplePath);
		//cout << p1<<endl;
		s1.add(p1);
	}


	const double pr = s1.mean() * exp(-Model->getRate() * m_T);
	const double std= s1.stdevP() * exp(-Model->getRate() * m_T) / (sqrt(tempsim - 1) * pr);
	unsigned int NumSim = static_cast<int>(tempsim * pow(std / eps,2))+50000;

	//cout << NumSim << endl;
	Stats1 s2;
	
	for (int i = 0; i < NumSim; i++) {

		vector<double> SamplePath(static_cast<int>(D * m_T));
		//cout << SamplePath.size() << endl;
		Model->GeneratePath(SamplePath, m_T, D, eps);
		const double p1 = payoff(SamplePath);
		//cout << p1<<endl;
		s2.add(p1);
	}

	Results res;
	
	res.Price = s2.mean() * exp(-Model->getRate() * m_T);
	res.error = s2.stdevP()*exp(-Model->getRate() * m_T)/ (sqrt(NumSim - 1)*res.Price);
	return res;
}