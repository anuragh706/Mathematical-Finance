#pragma once
class NRG
{
public:
	double generate();

	NRG() :flag(0), norm_rand1(0.0), norm_rand2(0.0),count(0) {};
private:
	bool flag;
	double norm_rand1, norm_rand2;
	int count;
};
