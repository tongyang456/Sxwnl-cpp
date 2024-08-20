#ifndef LUNAR_H
#define LUNAR_H

#include "lunar_ob.h"
#include <map>
#include <vector>
#include <list>
#include <string>

struct OB_LUN
{
	int w0;			// 本月第一天的星期
	int y;		 	// 公历年份
	int m;		 	// 公历月分
	int d0;			// 月首的J2000.0起算的儒略日数
	int dn;			// 本月的天数
	std::string nianhao;  // 年号纪年信息
	OB_DAY day[31];
};

struct LN_MONTH
{
    int index;		//索引序号
    int month;      //农历月：正月~十二
    int dayCount;   //天数，大月30天，小月29天
    double firstJulianDay;  //初一的儒略日
};

struct nJieQi {
    std::string pre_jqmc;
    std::string aft_jqmc;
    time_t pre_jqsj;
    time_t aft_jqsj;
};

void init_ob();
OB_LUN yueLiCalc(int By, int Bm);
std::string nianLiSTR(int y);
#endif