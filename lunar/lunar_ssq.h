#ifndef LUNAR_SSQ_H
#define LUNAR_SSQ_H

#include <string>
#include <array>

class SSQ
{
	static char str_qi[7567+1];
	static char str_so[16598+1];
	static double suoKB[];
	static double qiKB[];
	static char* jieya(int mood);
	static double so_low(double W);
	static double qi_low(double W);
	static double qi_high(double W);
	static double so_high(double W);

public:
    int leap;  //闰月位置
    std::array<std::string,14> ym;//各月名称
    int ZQ[25];//中气表
    int HS[15];//合朔表
    int dx[14];//各月大小
    int pe[2]; //补算二气
    static void init();
    void calcY(double jd);
    static int calc(double jd, int qs);
    std::string calcY1(double jd);
};

#endif
