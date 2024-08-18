#ifndef EPH_RSGS_H
#define EPH_RSGS_H

#include "../mylib/mystl/vector.h"
#include "../mylib/mystl/my_string.h"
#include "../mylib/mystl/static_array.h"

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
	mystl::array3 I;
	mystl::array3 gk1;
	mystl::array3 gk2;
	mystl::array3 gk3;
	mystl::array3 gk4;
	mystl::array3 gk5;
	mystl::string lx;

	double zxJ;
	double zxW;
	double dw;
	double sf;
	double tt;
	mystl::array3 Sdp;

	mystl::vector <double> p1;
	mystl::vector <double> p2;
	mystl::vector <double> p3;
	mystl::vector <double> p4;
	mystl::vector <double> q1;
	mystl::vector <double> q2;
	mystl::vector <double> q3;
	mystl::vector <double> q4;
	mystl::vector <double> L0;
	mystl::vector <double> L1;
	mystl::vector <double> L2;
	mystl::vector <double> L3;
	mystl::vector <double> L4;
	mystl::vector <double> L5;
	mystl::vector <double> L6;
};

struct _JIEX2
{
	mystl::vector <double> p1;
	mystl::vector <double> p2;
	mystl::vector <double> p3;
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
	 mystl::string jieX3(double jd);
	 inline mystl::array3 sun (double jd){ return chazhi(jd,0); } //传回值可能超过360度
	 inline mystl::array3 moon(double jd){ return chazhi(jd,1); }
	 inline mystl::array3 bse (double jd){ return chazhi(jd,2); }

private:
	 mystl::vector<double> Zs;
	 double Zdt;
	 double dT;
	 double tanf1;
	 double tanf2;
	 double srad;
	 double bba;
	 double bhc;
	 double dyj; 
	
	 mystl::array3 chazhi(double jd,int xt);
	 mystl::array3 cd2bse(mystl::array3 z,mystl::array3 I);
	 mystl::array3 bse2cd(mystl::array3 z,mystl::array3 I );
	 mystl::array3 bse2db(mystl::array3 z,mystl::array3 I ,bool f);
	 mystl::array3 bseXY2db(double x,double y,mystl::array3 I,bool f);
	 mystl::array3 bseM(double jd);
	 _VXY Vxy(double x,double y,double s, double vx,double vy);
	 _RSM rSM(double mR);
	 mystl::array3 qrd(double jd,double dx,double dy,bool fs);
	 void push(mystl::array3 z,mystl::vector<double> &p);
	 mystl::array4 nanbei(mystl::array3 M,double vx0,double vy0, double h,double r,mystl::array3 I);
	 bool mDian(mystl::array3 M,double vx0,double vy0,bool AB, double r,mystl::array3 I,mystl::vector<double> &A);
	// void __rsGS::elmCpy(mystl::vector<double> &a,int n,mystl::vector<double> b,int m);
	// void __rsGS::mQie(mystl::array3 M,double vx0,double vy0,double h, double r,mystl::array3 I, mystl::vector<double> &A,_FLAG &FLAG);
	
};

// extern std::map<mystl::string,mystl::string> lxb;
#endif
