//日食批量快速计算器

#ifndef EPH_RSPL_H
#define EPH_RSPL_H

#include "../mylib/mystl/my_string.h"
#include "../mylib/mystl/static_array.h"

struct _SECXY
{
	double mCJ;
	double mCW;
	double mR;
	double mCJ2;
	double mCW2;
	double mR2;
	
	double sCJ;
	double sCW;
	double sR;
	double sCJ2;
	double sCW2;
	double sR2;	
	
	double mr;
	double sr;
	double x;
	double y;
	double t;
};

struct _ZB
{
	mystl::array3 S;
	mystl::array3 M;
	double sr;
	double mr;
	double x;
	double y;
	double g;
};

struct _GJW
{
	double J;
	double W;
	mystl::string c;
};


class RS_PL
{
public:
	 bool nasa_r;//为1表示采用NASA的视径比
	 mystl::array5 sT;//地方日食时间表
	 mystl::string LX;
	 double sf;
	 double sf2; //食分(日出食分)
     double sf3; //食分(日没食分)
     mystl::string sflx; //食分类型
	 double b1;
	 double dur;
	 double sun_s;
	 double sun_j;
	 double P1;
	 double V1;
	 double P2;
	 double V2;
	 void secMax(double jd,double L,double fa,double high);
	 void nbj(double jd);
	//以下涉及南北界计算
	 mystl::array3 A;
	 mystl::array3 B; //本半影锥顶点坐标
	 _ZB P;//t1时刻的日月坐标,g为恒星时
	 _ZB Q;//t2时刻的日月坐标
	 mystl::array10 V;//食界表
	 mystl::string Vc;
	 mystl::string Vb;  //食中心类型,本影南北距离
	
	 double lineT(_SECXY G, double v,double u, double r, bool n);
	 void zbXY(_ZB &p,double L,double fa);
	 void zb0(double jd);
	 void p2p(double L,double fa,_GJW &re,bool fAB,int f);
	 void pp0(_GJW &re);
	 void secXY(double jd,double L,double fa,double high,_SECXY &re);

};

#endif
