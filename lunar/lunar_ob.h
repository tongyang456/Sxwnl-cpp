#ifndef LUNAR_OB_H
#define LUNAR_OB_H

#include "../mylib/tool.h"
#include <string>
#include <vector>

struct OB_DAY
{
	/* 日的公历信息 */
	int d0;		// 2000.0起算儒略日,北京时12:00
	int di;		// 所在公历月内日序数
	int y;      // 公历年
	int m;      // 公历月
	int d; 		// 日名称(公历)
	int dn;     // 本月天数
	int week0;  // 月首的星期
	int week;  	// 星期
	int weeki; 	// 在本月中的周序号
	int weekN; 	// 本月的总周数
	/* 日的农历信息 */
	int Ldi;	   // 日距农历月首偏移
	std::string Ldc;   // 日名称(农历),即'初一,初二等'
	
	int cur_dz; //冬至的天数
    int cur_lc; //立春的天数
	int cur_xz; //夏至的天数
	int cur_lq; //立秋的天数
	int cur_mz; //芒种的天数
	int cur_xs; //小暑的天数
	std::string Lmc;  // 月名称
	std::string Lmc2; // 月名称,这个+1
	int Ldn;   		// 月大小
	std::string Lleap; 	// 闰状况 
	/* 日的农历纪年、月、日、时及星座 */
	int Lyear;		 	// 农历纪年(10进制,1984年起算,分界点可以是立春也可以是春节,在程序中选择一个)
	int Lyear0;			// 农历纪年(春节)
	std::string Lyear2;	// 干支纪年(立春)
	std::string Lyear3;	// 干支纪年(春节)
	int Lyear4;			// 干支纪年(黄帝纪元)
	int Lmonth;			// 纪月处理,1998年12月7日(大雪)开始连续进行节气计数,0为甲子
	std::string Lmonth2;   // 干支纪月
	std::string Lday2; 	// 纪日
	std::string Ltime2;	// 纪时
	std::string Ljq;	   // 节气
	std::string XiZ;   	// 星座
	/* 日的回历信息 */
	int Hyear;	 	// 年(回历)
	int Hmonth;		// 月(回历)
	int Hday;	  	// 日(回历)
	/* 日的其它信息 */
	std::string yxmc;	// 月相名称
	double yxjd;   	  // 月相时刻(儒略日)
	std::string yxsj;	// 月相时间串
	std::string jqmc;	// 节气名称
	double jqjd;	     // 节气时刻(儒略日)
	std::string jqsj;	// 节气时间串
	
	bool Fjia;          //放假日子
	std::string A;    //重要喜庆日子名称
	std::string B;    //重要日子名称
	std::string C;    //各种日子名称

    double date_zty;
    std::string bz_JS;
};

struct MLBZ
{
    std::string bz_dy;		//大运
	std::string bz_jn;		//纪年
	std::string bz_jy;		//纪月
	std::string bz_jr;		//纪日
	std::string bz_js;		//纪时
	std::string bz_JS;		//纪时 数组形式13个
	std::string bz_zty;		//真太阳时
	Date date_zty;              //真太阳时
};

class OBA//获取指定日期的节假日
{
public:
	static void init();
	static void getDayName(OB_DAY &r);	//计算公历节假日
	static void getHuiLi(double d0,OB_DAY &r);	//计算回历信息

private:
	static std::vector<std::vector<std::string>> sFtv; //假日表,由init初始化
	static std::vector<std::string> wFtv;
    static int a;
    static std::vector<std::vector<std::string>> sFtv1; //假日表,由init初始化
};
constexpr int a  = 1;


class OBB//农历对象，气朔计算等
{
public:
	static void init();
	static std::string getNH(int y);
	static void getDayName2(OB_DAY &r);
	static void mingLiBaZi(double jd, double J, MLBZ &ob);
	static double qi_accurate(double W);
	static double so_accurate(double W);
	static double qi_accurate2(double jd);
	static double so_accurate2(double jd);
	
private:
	static std::vector<std::string> JNB;
};

extern const char *str_num[];
extern const char *str_ymc[];
extern const char *str_yxmc[];
extern const char *str_jqmc[];
extern const char *str_gan[];
extern const char *str_zhi[];
extern const char *str_sxmc[];
extern const char *str_nywx[];
extern const char *str_xqmc[];
extern const char *str_rmc[];
extern const char *str_rmc0[];
extern const char *str_xz[];
extern const char *str_dx[];
extern const char *str_ago[];
extern const char *str_fw[];
extern const char *str_sjd[];
extern const char *str_ry[];
extern const char *str_ry2[];
extern const char *str_yx[];
extern const char *str_xxiu[4][7];
extern const char *str_xxjx[2][14];
extern const char *str_guax[];
extern const char *str_zsheng[];
extern const char *sixth[];

#endif
