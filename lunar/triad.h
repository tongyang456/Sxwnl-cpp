#ifndef TRIAD_H
#define TRIAD_H

#include <list>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "../mylib/tool.h"
#include "lunar.h"
#include "lunar_ssq.h"
#include <unordered_map>
#include "../mylib/lat_lon_data.h"
#include "../eph/eph0.h"


class Triad {
private:
    int Lyear_;              /* 农历年 */
    std::string Lmonth_;     /* 农历月 */
    std::string Lday_;       /* 农历日 */
    std::string Leap_;       /* 闰月标志 */
    int year_;               /* 阳历年 */
    int month_;              /* 阳历月 */
    int day_;                /* 阳历日 */
    int hour_;               /* 阳历时 */
    int minute_;             /* 阳历分 */
    double second_;          /* 阳历秒 */
    double jd_;              /* 儒略日数 */
    OB_DAY ob_day_;          /* 三合历 */

    bool calcJulianDay(int lunarYear, std::string lunarMonth, std::string lunarDay , int hour, int minute, std::string leap, double &JulianDay);

public:
    inline int lyear() { return Lyear_; }

    inline std::string lmonth() { return Lmonth_; }

    inline std::string lday() { return Lday_; }

    inline std::string leap() { return Leap_; }

    inline int year() { return year_; }

    inline int month() { return month_; }

    inline int day() { return day_; }

    inline int hour() { return hour_; }

    inline int minute() { return minute_; }

    inline double second() { return second_; }

    inline int jd() { return jd_; }

    inline OB_DAY ob_day() { return ob_day_; }

    Triad(int LYear, std::string Month, std::string Day, int hour=0, int minute=0, std::string Leap = "");

    Triad(int year, int month, int day, int hour, int minute, double second);

    Triad(std::string nian, std::string yue, std::string ri, std::string shi, int baseyear = 1900);

    Triad(double jd);

    std::string to_string();

    static OB_DAY riLiCalc(int By, int Bm, int Bd, int Bh = 0, int Bmin = 0, double Bs = 0.0, double J = jw.J / radd);

    static std::list<Date> fromBaZi(std::string yearGanZhi, std::string monthGanZhi,
                                    std::string dayGanZhi, std::string timeGanZhi, int sect, int baseYear = 1900);

    static std::map<std::string, std::string> getJqMap(Date JD, int idx = 3);

    static nJieQi getxiangLinJieqi(const std::map<std::string, std::string> &jieqi_map, Date date);

    static nJieQi getXianglinJieQi(Date JD);

    static Date calcDaYun(const std::string sex, const std::string nianzhi, time_t Solartime, const nJieQi result, Date &diff);

    static std::list<LN_MONTH> getLunarDate(int Year);
};

#endif