#include "../mylib/mystl/my_string.h"
#include "../mylib/mystl/vector.h"

struct SJ
{
	double z;
	double x;
	double s;
	double j;
	double c;
	double h;
	double c2;
	double h2;
	double c3;
	double h3;
	double H0;
	double H;
	double H1;
	double H2;
	double H3;
	double H4;
	mystl::string sm;
};

struct SJ_S
{
	mystl::string s;
	mystl::string z;
	mystl::string j;
	mystl::string c;
	mystl::string h;
	mystl::string ch;
	mystl::string sj;
	mystl::string Ms;
	mystl::string Mz;
	mystl::string Mj;
};


class SZJ
{	//日月的升中天降,不考虑气温和气压的影响  
public:	
	SZJ();
	 mystl::vector <SJ_S> rts;	//多天的升中降
	 double getH(double h, double w);
	 void Mcoord(double jd, double H0, SJ & r);
	 void Scoord(double jd, int xm, SJ & r);
	 SJ Mt(double jd);
	 SJ Qt(double jd);
	 SJ St(double jd);
	 void calcRTS(double jd, int n, double Jdl, double Wdl, double sq);
		
	 double L;	//站点地理经度,向东测量为正
	 double fa;	//站点地理纬度
	
private:
	 double E = 0.409092614;	//黄赤交角
	 double dt;	//TD-UT
};
