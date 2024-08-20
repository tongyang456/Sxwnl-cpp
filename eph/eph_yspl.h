#ifndef EPH_YSPL_H
#define EPH_YSPL_H

#include <string>
#include <array>

struct RE0
{
	double e_mRad;
	double eShadow;
	double eShadow2;
	double x;
	double y;
	double mr;
	double er;
	double Er;
	double t;
};

class YS_PL
{ //月食快速计算器
public:
    std::array<double, 4> lT;
	std::string LX;
	double sf;
	void lecXY(double jd, RE0 &re);
	double lineT(RE0 G,double v,double u, double r, bool n);
	void lecMax(double jd);
};

#endif