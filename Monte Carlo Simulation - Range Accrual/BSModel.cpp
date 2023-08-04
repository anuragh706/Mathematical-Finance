#include "BSModel.h"
#include <iostream>
using namespace std;
void BSModel::GeneratePath(vector<double>& SamplePath, const double T, unsigned int D, const double eps) const {

	double St = m_S0;
	const double dt = T/D;
	//cout << SamplePath.size() << endl;
	for (int i = 0; i < SamplePath.size(); i++) {
		const double randnum = m_nrg.generate();
		const double S = St * exp((m_r - 0.5 * m_sigma * m_sigma) * dt + m_sigma * sqrt(dt) * randnum);
		SamplePath[i] = S;
		
		St = S;
	}
	//cout << SamplePath.size() << endl;
}