#include "RangeAccrual.h"

double RangeAccrual::payoff(const vector<double>& S) const {

	Stats1 s1;
	//cout << S.size() << endl;
	int ctr = 0;
	for (int i = 0; i < S.size(); i++) {

		if (S[i]<m_Smax && S[i]>m_Smin) 
			s1.add(1.0);
		else s1.add(0.0);

	}
	const double mean=s1.mean();
	return mean*m_Notional;
}

double RangeAccrual::payoff(const double& S) const {

	return 0.0;
}