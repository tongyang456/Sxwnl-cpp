#ifndef EPH_RSGS_H
#define EPH_RSGS_H

#include <array>
#include <string>
#include <vector>

struct _VXY
{
	double vx;
	double vy;
	double Vx;
	double Vy;
	double V;	
};

struct _RSM
{
	double r1;
	double r2;
	double ar2;
	double sf;
};

struct _FEATURE
{
	double jdSuo;
	double dT;
	double ds;
	double vx;
	double vy;
	double ax;
	double ay;
	double v;
	double k;

	double t0;
	double jd;
	double xc;
	double yc;
	double zc;
	double D;
	double d;
	std::array<double, 3> I;
	std::array<double, 3> gk1;
	std::array<double, 3> gk2;
	std::array<double, 3> gk3;
	std::array<double, 3> gk4;
	std::array<double, 3> gk5;
	std::string lx;

	double zxJ;
	double zxW;
	double dw;
	double sf;
	double tt;
	std::array<double, 3> Sdp;

	std::vector <double> p1;
	std::vector <double> p2;
	std::vector <double> p3;
	std::vector <double> p4;
	std::vector <double> q1;
	std::vector <double> q2;
	std::vector <double> q3;
	std::vector <double> q4;
	std::vector <double> L0;
	std::vector <double> L1;
	std::vector <double> L2;
	std::vector <double> L3;
	std::vector <double> L4;
	std::vector <double> L5;
	std::vector <double> L6;
};

struct _JIEX2
{
	std::vector <double> p1;
	std::vector <double> p2;
	std::vector <double> p3;
};

struct _FLAG
{
	int f;
	int f2;
};

class RS_GS
{
public:
	RS_GS();
	 double Zjd;
	 void init(double jd,int n);
	 _FEATURE feature(double jd);
	// _FEATURE __rsGS::jieX(double jd);
	// _JIEX2 __rsGS::jieX2(double jd);
	 std::string jieX3(double jd);
	 inline std::array<double, 3> sun (double jd){ return chazhi(jd,0); } //传回值可能超过360度
	 inline std::array<double, 3> moon(double jd){ return chazhi(jd,1); }
	 inline std::array<double, 3> bse (double jd){ return chazhi(jd,2); }

private:
	 std::vector<double> Zs;
	 double Zdt;
	 double dT;
	 double tanf1;
	 double tanf2;
	 double srad;
	 double bba;
	 double bhc;
	 double dyj; 
	
	 std::array<double, 3> chazhi(double jd,int xt);
	 std::array<double, 3> cd2bse(std::array<double, 3> z,std::array<double, 3> I);
	 std::array<double, 3> bse2cd(std::array<double, 3> z,std::array<double, 3> I );
	 std::array<double, 3> bse2db(std::array<double, 3> z,std::array<double, 3> I ,bool f);
	 std::array<double, 3> bseXY2db(double x,double y,std::array<double, 3> I,bool f);
	 std::array<double, 3> bseM(double jd);
	 _VXY Vxy(double x,double y,double s, double vx,double vy);
	 _RSM rSM(double mR);
	 std::array<double, 3> qrd(double jd,double dx,double dy,bool fs);
	 void push(std::array<double, 3> z,std::vector<double> &p);
     std::array<double, 4> nanbei(std::array<double, 3> M,double vx0,double vy0, double h,double r,std::array<double, 3> I);
	 bool mDian(std::array<double, 3> M,double vx0,double vy0,bool AB, double r,std::array<double, 3> I,std::vector<double> &A);
	// void __rsGS::elmCpy(std::vector<double> &a,int n,std::vector<double> b,int m);
	// void __rsGS::mQie(std::array<double, 3> M,double vx0,double vy0,double h, double r,std::array<double, 3> I, std::vector<double> &A,_FLAG &FLAG);
	
};

// extern std::map<std::string,std::string> lxb;
#endif
