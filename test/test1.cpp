/*
寿星天文历v5.05js版 C++翻译工程
API测试
2018-8-28
*/
#include <ctime>
#include <iostream>
#include <array>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <list>

#include "../mylib/tool.h"
#include "../lunar/lunar.h"
#include "../lunar/tiangan.hpp"
#include "../lunar/lunar_ssq.h"
#include "../lunar/dizhi.hpp"
#include "../lunar/wuxing.hpp"
#include "../lunar/shishen.hpp"
#include "../eph/eph_show.h"
#include "../eph/eph0.h"
#include "../eph/eph.h"
#include "../mylib/lat_lon_data.h"
#include "../mylib/tool.h"
#include "../mylib/math_patch.h"
#include <array>
#include <map>
#include "bazi.h"
#include "triad.h"

#define MAP_H 18
#define MAP_W  7
std::array<std::array<std::string, MAP_W>, MAP_H> strmap;

#include <iostream>
#include <chrono>

Date get_time(void) {
    struct tm *bjs;
    time_t time0;
    time0 = time(NULL);
    bjs = localtime(&time0);
    Date dat =
            {
                    bjs->tm_year + 1900,
                    bjs->tm_mon + 1,
                    bjs->tm_mday,
                    bjs->tm_hour,
                    bjs->tm_min,
                    (double) bjs->tm_sec
            };
    return dat;
}

int main() {
#if defined(_WIN32) || defined(_MSC_VER)
    system("@chcp 65001");
#endif
    Date dat=get_time();
    std::cout << std::fixed << std::setprecision(10);

    // 农历基础
    init_ob();

    MLBZ mlbz;
    OBB::mingLiBaZi( toJD(dat)+(-8.0)/24-J2000, jw.J/radd, mlbz ); //八字计算

    std::string sex = "0"; //0男，1女
    JINGWEI jw1 = GeographicalPosition("北京");

    std::list<Date> tstLst = Triad::fromBaZi("甲辰", "壬申",
                                                    "丁巳", "丙午", 2, 1970);

    std::list<LN_MONTH> ss =  Triad::getLunarDate(1993);

    for (int i = 0; i < 1; i++) {
#if 1
        Date base = {1990, 1, 1, 1, 1, 1.0};
        Date date = getDateAfter(base, {0,0,i,0,0,0.0});
        //OB_DAY days = Lunar::riLiCalc(date.Y, date.M, date.D, date.h, date.m, date.s, jw1.J);
        // 返回，有用信息
        EightChar eightChar(date, jw1, sex);
        ShiShen shiShen(eightChar.getCsMlbz(), sex);

        double jd1 = toJD(date);
        MLBZ ob = eightChar.getCsMlbz();
        OB_DAY day = eightChar.getObDay();

        Date predate = getDateAfter(date, {0,0,-1,0,0,0.0});
        std::cout << "jd1 " << toJD(date) - toJD(predate) << " " << toJD(date) << " " << toJD(predate) << std::endl;

        std::cout <<
                  "\033[31;1m[日标]：\033[0m" << "公历 " << date.Y << "-" << date.M << "-" << date.D << " 儒略日数 "
                  << int2(jd1 + 0.5) << " 距2000年首" << int2(jd1 + 0.5 - J2000) << "日\n"
                  << "\033[31;1m[八字]：\033[0m" << ob.bz_jn << "年 " << ob.bz_jy << "月 " << ob.bz_jr << "日 " << ob.bz_js
                  << "时 真太阳 \033[31m" << ob.bz_zty << "\033[0m"
                  << "\n\033[1;32m[纪时]：\033[0m" << ob.bz_JS << "\n"
                  << "\033[1;32m[时标]：\033[0;1;35m" << "23　 01　 03　 05　 07　 09　 11　 13　 15　 17　 19　 21　 23\033[0m"
                  << std::endl;

        std::cout << "真太阳时" << DD2str(ob.date_zty) << std::endl;
        std::cout << "出生位置" << jw1.s << jw1.x << std::endl;

        //农历信息
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "农历年" << day.Lyear + 1984 << std::endl;
        std::cout << "闰(1闰0否)?" << day.Lleap.length() << std::endl;
        std::cout << "农历月" << day.Lmc << std::endl;
        std::cout << "农历日" << day.Ldc << std::endl;
        std::cout << "星座" << day.XiZ << std::endl;

        nJieQi njieqi = eightChar.getCsJieQi(); //出生前后节气
        std::cout << "出生前节气时间" << time_t_to_string(njieqi.pre_jqsj) << " 节气" << njieqi.pre_jqmc << std::endl;
        std::cout << "出生后节气时间" << time_t_to_string(njieqi.aft_jqsj) << " 节气" << njieqi.aft_jqmc << std::endl;

        Date diff2s = convFormat(structToTime(ob.date_zty) - (njieqi.pre_jqsj));
        std::cout << "出生于" << njieqi.pre_jqmc << "后" << DD2str(diff2s) << std::endl;

        Date diff3s = convFormat((njieqi.aft_jqsj) - structToTime(ob.date_zty));
        std::cout << "出生于" << njieqi.aft_jqmc << "前" << DD2str(diff3s) << std::endl;

        Date dayundate = setFromJD(eightChar.getDyJd());//+ J2000
        Date diff = eightChar.getdYunyear();
        std::cout << "大运起始日期" << DD2str(dayundate) << "间隔" << DD2str(diff) << std::endl;

        nJieQi njieqi1 = eightChar.getDyJieQi();
        std::cout << "交大运前节气时间: " << time_t_to_string(njieqi1.pre_jqsj) << " 节气 " << njieqi1.pre_jqmc << std::endl;
        std::cout << "交大运后节气时间: " << time_t_to_string(njieqi1.aft_jqsj) << " 节气 " << njieqi1.aft_jqmc << std::endl;

        Date diff4 = convFormat(structToTime(dayundate) - njieqi1.pre_jqsj);
        std::cout << time_t_to_string(njieqi1.pre_jqsj) << "后" << DD2str(diff4) << "交大运" << std::endl;

        std::cout << "人员司令分野" << eightChar.calcRenYuanFenYe() << std::endl;
        std::cout << "逢" << eightChar.calcHuanyun() << "换运" << std::endl;
        std::string xingxiu = eightChar.calcXingXiu();
        std::cout << "星宿" << xingxiu << std::endl;
        std::string jixiong = eightChar.calcXingXiuJX();
        std::cout << "星宿吉凶，【>0 吉 <0 凶】  " << jixiong << std::endl;
        std::cout << "胎元" << eightChar.calcTaiYuan() << std::endl;
        std::cout << "年柱空亡" << eightChar.calcKongWang(ob.bz_jn) << std::endl;
        std::cout << "日柱空亡" << eightChar.calcKongWang(ob.bz_jr) << std::endl;
        std::cout << "命宫" << eightChar.calcMingGong() << std::endl;
        std::cout << "胎息" << eightChar.calcTaixi() << std::endl;
        std::cout << "身宫" << eightChar.calcShengong() << std::endl;
        std::cout << "命卦" << eightChar.calcMinggua() << std::endl;

        //计算阳历某一日对应的流年大运信息
        Triad td = Triad(2026, 10, 1, 2, 1, 0);
        MLBZ bzs = eightChar.calc(td);
        std::cout << td.to_string() << bzs.bz_dy << bzs.bz_jn << bzs.bz_jy << bzs.bz_jr << bzs.bz_js << std::endl;
        std::cout << shiShen.toFullString(shiShen.calcLiuNian(bzs)) << std::endl;

        //计算农历某一日对应的流年大运信息
        Triad td1 = Triad(1999, "二", "初六",2,1);
        MLBZ bzs1 = eightChar.calc(td1);
        std::cout << td1.to_string() << bzs1.bz_dy << bzs1.bz_jn << bzs1.bz_jy << bzs1.bz_jr << bzs1.bz_js
                  << std::endl;
        std::cout << shiShen.toFullString(shiShen.calcLiuNian(bzs1)) << std::endl;

        Triad t(1999,2,26,1,1,1.0);
        std::cout << t.to_string() << std::endl;

        Triad t1(1999,"二","初六");
        std::cout << t1.to_string() << std::endl;

        Triad t2(toJD(dat) );
        std::cout << t2.to_string() << std::endl;

        Triad t3("己卯","壬申","乙巳","壬午");
        std::cout << t3.to_string() << std::endl;
#endif
    }
    return 0;
}
