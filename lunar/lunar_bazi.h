#ifndef LUNAR_BAZI_H
#define LUNAR_BAZI_H

#include <list>
//#include "../mylib/mystl/my_string.h"
//#include "../mylib/mystl/vector.h"
#include <string>
#include <vector>
#include "../mylib/tool.h"
#include "lunar.h"
#include "lunar_ssq.h"
#include <unordered_map>
#include "../mylib/lat_lon_data.h"
#include "../eph/eph0.h"


class Solar; // 前向声明Solar类

class Lunar {
private:
    int year;               /* 农历年 */
    int month;              /* 农历月 */
    int day;                /* 农历日 */
    int hour;               /* 小时 */
    int minute;             /* 分钟 */
    int second;             /* 秒钟 */
    double JulianDay;       /* 儒略日数 */

    bool calcJulianDay( int lunarYear, int lunarMonth, int lunarDay, double &JulianDay );
public:
    OB_DAY ob_day;

    Lunar(Solar solar);

    Lunar(double JulianDay);

    Lunar(int lunarYear, int lunarMonth, int lunarDay, int hour = 0, int minute = 0, int second = 0);

    std::string toString();

    Solar getSolar();

    inline int getYear() { return this->year; }

    inline int getMonth() { return this->month; }

    inline int getDay() { return this->day; }

    inline int getHour() { return this->hour; }

    inline int getMinute() { return this->minute; }

    inline int getSecond() { return this->second; }

    inline double getJulianDay() { return this->JulianDay; }

    Lunar next(int days);

    static std::list<LN_MONTH> getLunarDate(int Year);

};
#endif