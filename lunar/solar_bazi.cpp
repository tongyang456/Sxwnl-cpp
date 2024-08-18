#include <list>
#include "solar_bazi.h"
#include "lunar_bazi.h"
#include "lunar_ssq.h"
#include "lunar_ob.h"
#include "../eph/eph0.h"
#include "../mylib/lat_lon_data.h"
#include <iostream>
#include <stdexcept>
#include <vector>

bool Solar::isLeapYear(int year) {
    if (year < 1600) {
        return year % 4 == 0;
    }
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Solar::getDaysOfYear(int year) {
    if (1582 == year) {
        return 355;
    }
    return isLeapYear(year) ? 366 : 365;
}

int Solar::getDaysOfMonth(int year, int month) {
    if (1582 == year && 10 == month) {
        return 21;
    }
    int m = month - 1;
    int d = DAYS_OF_MONTH[m];
    // 公历闰年2月多一天
    if (m == 1 && isLeapYear(year)) {
        d++;
    }
    return d;
}

int Solar::getDaysInYear(int year, int month, int day) {
    int days = 0;
    for (int i = 1; i < month; i++) {
        days += getDaysOfMonth(year, i);
    }
    int d = day;
    if (1582 == year && 10 == month) {
        if (day >= 15) {
            d -= 10;
        } else if (day > 4) {
            std::string message =
                    "wrong solar year " + std::to_string(year) + " month " + std::to_string(month) + " day " +
                    std::to_string(day);
            throw std::invalid_argument(message);
        }
    }
    days += d;
    return days;
}

int Solar::getWeeksOfMonth(int year, int month, int start) {
    return (int) ceil((getDaysOfMonth(year, month) + Solar(year, month, 1).getWeek() - start) * 1 / 7);
}

int Solar::getDaysBetween(int ay, int am, int ad, int by, int bm, int bd) {
    int n;
    int days;
    int i;
    if (ay == by) {
        n = getDaysInYear(by, bm, bd) - getDaysInYear(ay, am, ad);
    } else if (ay > by) {
        days = getDaysOfYear(by) - getDaysInYear(by, bm, bd);
        for (i = by + 1; i < ay; i++) {
            days += getDaysOfYear(i);
        }
        days += getDaysInYear(ay, am, ad);
        n = -days;
    } else {
        days = getDaysOfYear(ay) - getDaysInYear(ay, am, ad);
        for (i = ay + 1; i < by; i++) {
            days += getDaysOfYear(i);
        }
        days += getDaysInYear(by, bm, bd);
        n = days;
    }
    return n;
}

Solar::Solar() {
    struct tm *bjs;
    time_t time0;
    time0 = time(NULL);
    bjs = localtime(&time0);
    this->year = bjs->tm_year + 1900,
    this->month = bjs->tm_mon + 1,
    this->day = bjs->tm_mday,
    this->hour = bjs->tm_hour,
    this->minute = bjs->tm_min,
    this->second = bjs->tm_sec;
}

Solar::Solar(int year, int month, int day, int hour, int minute, int second) {
    if (1582 == year && 10 == month) {
        if (day > 4 && day < 15) {
            std::string message =
                    "wrong solar year " + std::to_string(year) + " month " + std::to_string(month) + " day " +
                    std::to_string(day);
            throw std::invalid_argument(message);
        }
    }
    if (month < 1 || month > 12) {
        std::string message = "wrong month " + std::to_string(month);
        throw std::invalid_argument(message);
    }

    if (day < 1 || day > 31) {
        std::string message = "wrong day " + std::to_string(day);
        throw std::invalid_argument(message);
    }

    if (hour < 0 || hour > 23) {
        std::string message = "wrong hour " + std::to_string(hour);
        throw std::invalid_argument(message);
    }

    if (minute < 0 || minute > 59) {
        std::string message = "wrong min " + std::to_string(minute);
        throw std::invalid_argument(message);
    }

    if (second < 0 || second > 59) {
        std::string message = "wrong second " + std::to_string(second);
        throw std::invalid_argument(message);
    }

    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

Solar::Solar(Date date) {
    if (1582 == date.Y && 10 == date.M) {
        if (date.D > 4 && date.D < 15) {
            std::string message =
                    "wrong solar year " + std::to_string(date.Y) + " month " + std::to_string(date.M) + " day " +
                    std::to_string(date.D);
            throw std::invalid_argument(message);
        }
    }
    if (date.M < 1 || date.M > 12) {
        std::string message = "wrong month " + std::to_string(date.M);
        throw std::invalid_argument(message);
    }

    if (date.D < 1 || date.D > 31) {
        std::string message = "wrong day " + std::to_string(date.D);
        throw std::invalid_argument(message);
    }

    if (date.h < 0 || date.h > 23) {
        std::string message = "wrong hour " + std::to_string(date.h);
        throw std::invalid_argument(message);
    }

    if (date.m < 0 || date.m > 59) {
        std::string message = "wrong min " + std::to_string(date.m);
        throw std::invalid_argument(message);
    }

    if (static_cast<int>(date.s) < 0 || static_cast<int>(date.s) > 59) {
        std::string message = "wrong second " + std::to_string(date.s);
        throw std::invalid_argument(message);
    }

    this->year = date.Y;
    this->month = date.M;
    this->day = date.D;
    this->hour = date.h;
    this->minute = date.m;
    this->second = static_cast<int>(date.s);
}

Solar::Solar(double jd) {
    int D = int2(jd + 0.5), c;
    double F = jd + 0.5 - D; // 取得日数的整数部份A及小数部分F
    if (D >= 2299161)
        c = int2((D - 1867216.25) / 36524.25), D += 1 + c - int2(c / 4.0);
    D += 1524;
    this->year = int2((D - 122.1) / 365.25); // 年数
    D -= int2(365.25 * this->year);
    this->month = int2(D / 30.601); // 月数
    D -= int2(30.601 * this->month);
    this->day = D; // 日数
    if (this->month > 13)
        this->month -= 13, this->year -= 4715;
    else
        this->month -= 1, this->year -= 4716;

    // 日的小数转为时分秒
    F *= 24.0;
    this->hour = int2(F);
    F -= this->hour;
    F *= 60.0;
    this->minute = int2(F);
    F -= this->minute;
    F *= 60.0;
    this->minute = F;
    this->second = 0;
}

Date Solar::toDate(){
    return Date{this->year, this->month, this->day, this->hour, this->month, static_cast<double>(this->second) };
}

// 获取儒略日
double Solar::getJulianDay() {
    double y = this->year, m = this->month, n = 0; // 取出年月
    if (m <= 2)
        m += 12, y--;
    if (this->year * 372 + this->month * 31 + this->day >= 588829)
        // 判断是否为格里高利历日1582*372+10*31+15
        n = (int) (y / 100), n = 2 - n + (int) (n / 4); // 加百年闰
    n += (int) (365.25 * (y + 4716) + 0.01);         // 加上年引起的偏移日数
    n += (int) (30.6 * (m + 1)) + this->day;         // 加上月引起的偏移日数及日偏移数
    n += ((this->second / 60.0 + this->minute) / 60.0 + this->hour) / 24.0 - 1524.5;
    return n;
}

int Solar::getWeek() {
    return (static_cast<int>(getJulianDay() + 0.5) + 7000001) % 7;
}

std::string Solar::getWeekInChinese() {
    return str_xqmc[getWeek()];
}

// 通过给定的八字，返回对应的阳历TUDO
std::list<std::string> Solar::fromBaZi(std::string yearGanZhi, std::string monthGanZhi,
                                       std::string dayGanZhi, std::string timeGanZhi, int sect, int baseYear)
{
    sect = (1 == sect) ? 1 : 2;

    // 月地支距寅月的偏移值
    int m = (findIndex(monthGanZhi.substr(3,3), str_zhi, 12, 0) - 2 + 12) % 12;

    // 月天干要一致
    if(((findIndex(yearGanZhi.substr(0,3), str_gan, 10, 0) +1 ) * 2 + m ) % 10 != findIndex( monthGanZhi.substr(0,3), str_gan, 10, 0)){
        exit(-1);
    }

    // 1年的立春是辛酉，序号57
    int y = (findIndex(yearGanZhi, sixth, 60, 0) -57 + 60)% 60 + 1;

    int startYear = baseYear - 1;

    struct tm *bjs;
    time_t time0;
    time0 = time(NULL);
    bjs = localtime(&time0);
    int endYear = bjs->tm_year + 1900;

    OBB obb;
    MLBZ ob={};
    std::map<std::string, std::string> yearMap;
    std::list<std::string> monthList;
    std::list<std::string> dayList;
    std::list<std::string> timeList;

    while( y < endYear){
        if( y > startYear){
            Date date = {y, 1, 1, 0, 0, 0.00 };
            yearMap = getJqMap(date, 15);
            for (std::map<std::string, std::string>::iterator it = yearMap.begin(); it != yearMap.end(); ++it) {
                time_t tt = string_to_time_t(it->first);
                Date datetmp = timeToStruct(tt);
                datetmp = getDateAfter(datetmp, {0, 0, 0, 0, 0, 10.0});//往后延10s
                obb.mingLiBaZi( toJD(datetmp)+(-8.0)/24-J2000, jw.J/radd, ob ); //八字计算
                if( (ob.bz_jn == yearGanZhi) && (ob.bz_jy == monthGanZhi) ){
                    monthList.push_back(it->first);
                }
            }
        }
        y+=60;
    }

    for (const auto& month : monthList) {
        time_t tt = string_to_time_t(month);
        Date datetmp = timeToStruct(tt);
        datetmp = getDateAfter(datetmp, {0, 0, 0, 0, 0, 10.0});//往后延10s
        while(1){
            datetmp = getDateAfter(datetmp, {0, 0, 1, 0, 0, 0.0});//往后延1day
            obb.mingLiBaZi( toJD(datetmp)+(-8.0)/24-J2000, jw.J/radd, ob ); //八字计算
            if( (ob.bz_jn == yearGanZhi) && (ob.bz_jy == monthGanZhi) ){
                if( ob.bz_jr == dayGanZhi ){
                    dayList.push_back(DD2str(datetmp));
                }
            }else{
                break;
            }
        }
    }

    for (const auto& day : dayList) {
        time_t tt = string_to_time_t(day);
        Date datetmp = timeToStruct(tt);
        datetmp = getDateAfter(datetmp, {0, 0, 0, 0, 0, 10.0});//往后延10s
        obb.mingLiBaZi( toJD(datetmp)+(-8.0)/24-J2000, jw.J/radd, ob ); //八字计算

        if( (ob.bz_jn == yearGanZhi) && (ob.bz_jy == monthGanZhi) && (ob.bz_jr == dayGanZhi) ){
            std::vector<std::string> elements;
            std::istringstream iss(ob.bz_JS);
            std::string token;

            // 使用空格作为分隔符分割字符串
            while (iss >> token) {
                elements.push_back(token);
            }

            for (size_t i = 0; i < elements.size(); ++i) {
                if( timeGanZhi == elements[i] ){
                    Date date1;
                    if( i == 0 ){
                        date1 = getDateAfter(datetmp, {0,0,-1,0,0,0.0} );
                    }else{
                        date1 = datetmp;
                    }
                    date1.h = (i*2 - 1 + 24) % 24;
                    date1.m = 0;
                    date1.s = 0.00;
                    std::cout << "DD2str(date1)" << DD2str(date1) << elements[i] << std::endl;
                    timeList.push_back(DD2str(date1));
                }
            }
        }
    }
    return timeList;
}

std::map<std::string, std::string> Solar::getJqMap(Date JD, int idx)
{
    std::map<std::string, std::string> myMap;
    JD.M--;
    if( JD.M == 0 ){
        JD.M = 12;
        JD.Y --;
    }else{
        JD.M--;
    }
    for(int i = 0; i < idx; i++){
        //日历物件初始化
        int D, xn;
        int Bd0 = int2(toJD(JD)) - J2000;	//公历月首,中午
        JD.M++;
        if (JD.M > 12)
            JD.Y++, JD.M = 1;
        int	Bdn = int2(toJD(JD)) - J2000 - Bd0;	//本月天数(公历)

        //以下是月相与节气的处理
        double d, jd2 = Bd0 + dt_T(Bd0) - 8 / 24.0;
        //节气查找
        double w = S_aLon(jd2 / 36525, 3);
        w = int2((w - 0.13) / pi2 * 24) * pi2 / 24;
        do
        {
            d = OBB::qi_accurate(w);
            D = int2(d + 0.5);
            xn = int2(w / pi2 * 24 + 24000006.01) % 24;
            w += pi2 / 24.0;
            if (D >= Bd0 + Bdn)
                break;
            if (D < Bd0)
                continue;
            if( xn%2 == 0) continue;
            myMap.insert(std::make_pair(JD2str(d+J2000), str_jqmc[xn]));
        }
        while (D + 12 < Bd0 + Bdn);
    }
    return myMap;
}

nJieQi Solar::getxiangLinJieqi(const std::map<std::string, std::string>& jieqi_map, Date date)
{
    time_t given_time = string_to_time_t(DD2str(date));
    time_t closest_time_before = 0;
    time_t closest_time_after = 0;
    std::string closest_value_before, closest_value_after;
    std::ptrdiff_t min_diff_before = std::numeric_limits<std::ptrdiff_t>::max();
    std::ptrdiff_t min_diff_after = std::numeric_limits<std::ptrdiff_t>::max();

    for (const auto& pair : jieqi_map) {
        time_t current_time = string_to_time_t((pair.first));
        std::ptrdiff_t diff = std::abs(static_cast<std::ptrdiff_t>(given_time - current_time));

        if (current_time < given_time) {
            if (diff < min_diff_before) {
                min_diff_before = diff;
                closest_time_before = current_time;
                closest_value_before = pair.second;
            }
        } else {
            if (diff < min_diff_after) {
                min_diff_after = diff;
                closest_time_after = current_time;
                closest_value_after = pair.second;
            }
        }
    }
    return nJieQi{closest_value_before, closest_value_after, closest_time_before, closest_time_after};
}

nJieQi Solar::getXianglinJieQi( Date JD ){
    std::map<std::string, std::string> jieqiMap =  Solar::getJqMap(JD);
    return Solar::getxiangLinJieqi(jieqiMap, JD);
}

//排大运
//看年支 阳男阴女顺排，阴男阳女逆排
//阳支：子 寅 辰 午 申 戌
//阴支：丑 卯 巳 未 酉 亥
//三天一岁、一天四个月、一个时辰10天；
Date Solar::calcDaYun(const std::string sex, const std::string nianzhi, time_t Solartime, const nJieQi result, Date &diffs ){
    const std::set<std::string> yangDiZhi = {"子", "寅", "辰", "午", "申", "戌"};
    const std::set<std::string> yinDiZhi = {"丑", "卯", "巳", "未", "酉", "亥"};

    auto it1 = std::find(yangDiZhi.begin(), yangDiZhi.end(), nianzhi);
    bool foundInFirst1 = (it1 != yangDiZhi.end());

    auto it2 = std::find(yinDiZhi.begin(), yinDiZhi.end(), nianzhi);
    bool foundInFirst2 = (it2 != yinDiZhi.end());

    //阳男阴女，顺排
    if( (sex=="0" && foundInFirst1==true) || (sex=="1" && foundInFirst2==true ) )
        diffs = convFormatDy(result.aft_jqsj - Solartime);

    //阴男阳女，逆排
    if( (sex=="0" && foundInFirst2==true) || (sex=="1" && foundInFirst1==true ) )
        diffs = convFormatDy( Solartime - result.pre_jqsj);

    return getDateAfter(timeToStruct(Solartime), diffs);
}

// 获取节日，有可能一天会有多个节日TUDO
std::list<std::string> Solar::getFestivals() {
    std::list<std::string> solarList;
    std::string key = std::to_string(this->month) + "-" + std::to_string(this->day);
    auto it = FESTIVAL_S.find(key);
    if (it != FESTIVAL_S.end()) {
        solarList.push_back(it->second);
    }

    // 计算几月第几个星期几对应的节日
    int weeks = (int) ceil(day / 7);
    int week = getWeek();

    std::string key1 = std::to_string(this->month) + "-" + std::to_string(weeks) + "-" + std::to_string(week);
    auto it1 = WEEK_FESTIVAL_S.find(key1);
    if (it1 != WEEK_FESTIVAL_S.end()) {
        solarList.push_back(it1->second);
    }

    if (day + 7 > Solar::getDaysOfMonth(year, month)) {
        std::string key2 = std::to_string(this->month) + "-0-" + std::to_string(week);
        auto it2 = WEEK_FESTIVAL_S.find(key2);
        if (it2 != WEEK_FESTIVAL_S.end()) {
            solarList.push_back(it2->second);
        }
    }

    return solarList;
}

// 获取非正式的节日，有可能一天会有多个节日 TUDO
std::list<std::string> Solar::getOtherFestivals() {
    std::list<std::string> solarList;
    std::string key = std::to_string(this->month) + "-" + std::to_string(this->day);
    auto it = OTHER_FESTIVAL_S.find(key);
    if (it != OTHER_FESTIVAL_S.end()) {
        solarList.push_back(it->second);
    }
    return solarList;
}

// 获取星座  TUDO
std::string Solar::getXingZuo() {
    int index = 11;
    int y = month * 100 + day;
    if (y >= 321 && y <= 419) {
        index = 0;
    } else if (y >= 420 && y <= 520) {
        index = 1;
    } else if (y >= 521 && y <= 621) {
        index = 2;
    } else if (y >= 622 && y <= 722) {
        index = 3;
    } else if (y >= 723 && y <= 822) {
        index = 4;
    } else if (y >= 823 && y <= 922) {
        index = 5;
    } else if (y >= 923 && y <= 1023) {
        index = 6;
    } else if (y >= 1024 && y <= 1122) {
        index = 7;
    } else if (y >= 1123 && y <= 1221) {
        index = 8;
    } else if (y >= 1222 || y <= 119) {
        index = 9;
    } else if (y <= 218) {
        index = 10;
    }
    return str_xz[(index + 3) % 12];
}

std::string Solar::toString() {
    return std::to_string(this->year) + "-" +
        std::to_string(this->month) + "-" +
        std::to_string(this->day) + " " +
        std::to_string(this->hour) + ":" +
        std::to_string(this->minute) + ":" +
        std::to_string(this->second);
}

Lunar Solar::getLunar(){
    return Lunar(getJulianDay());
}

int Solar::subtract(Solar other) {
    return Solar::getDaysBetween(other.year, other.month, other.day, this->year, this->month, this->day);
}

int Solar::subtractMinute(Solar solar) {
    int days = subtract(solar);
    int cm = hour * 60 + minute;
    int sm = solar.getHour() * 60 + solar.getMinute();
    int m = cm - sm;
    if (m < 0) {
        m += 1440;
        days--;
    }
    m += days * 1440;
    return m;
}

bool Solar::isAfter(Solar solar) {
    if (this->year > solar.getYear()) {
        return true;
    }
    if (this->year < solar.getYear()) {
        return false;
    }
    if (this->month > solar.getMonth()) {
        return true;
    }
    if (this->month < solar.getMonth()) {
        return false;
    }
    if (this->day > solar.getDay()) {
        return true;
    }
    if (this->day < solar.getDay()) {
        return false;
    }
    if (this->hour > solar.getHour()) {
        return true;
    }
    if (this->hour < solar.getHour()) {
        return false;
    }
    if (this->minute > solar.getMinute()) {
        return true;
    }
    if (this->minute < solar.getMinute()) {
        return false;
    }
    return this->second > solar.getSecond();
}

bool Solar::isBefore(Solar solar) {
    if (this->year > solar.getYear()) {
        return false;
    }
    if (this->year < solar.getYear()) {
        return true;
    }
    if (this->month > solar.getMonth()) {
        return false;
    }
    if (this->month < solar.getMonth()) {
        return true;
    }
    if (this->day > solar.getDay()) {
        return false;
    }
    if (this->day < solar.getDay()) {
        return true;
    }
    if (this->hour > solar.getHour()) {
        return false;
    }
    if (this->hour < solar.getHour()) {
        return true;
    }
    if (this->minute > solar.getMinute()) {
        return false;
    }
    if (this->minute < solar.getMinute()) {
        return true;
    }
    return this->second < solar.getSecond();
}

Solar Solar::nextYear(int years) {
    int y = this->year + years;
    int m = this->month;
    int d = this->day;
    if (1582 == y && 10 == m) {
        if (d > 4 && d < 15) {
            d += 10;
        }
    } else if (2 == m) {
        if (d > 28) {
            if (!Solar::isLeapYear(y)) {
                d = 28;
            }
        }
    }
    return Solar(y, m, d, hour, minute, second);
}

Solar Solar::nextMonth(int months) {
    int n = months < 0 ? -1 : 1;
    int m = abs(months);
    int y = year + m / 12 * n;
    m = month + m % 12 * n;
    if (m > 12) {
        m -= 12;
        y++;
    } else if (m < 1) {
        m += 12;
        y--;
    }

    int d = day;
    if (1582 == y && 10 == m) {
        if (d > 4 && d < 15) {
            d += 10;
        }
    } else {
        int maxDay = Solar::getDaysOfMonth(y, m);
        if (d > maxDay) {
            d = maxDay;
        }
    }
    return Solar(y, m, d, hour, minute, second);
}

Solar Solar::next(int days) {
    int y = this->year;
    int m = this->month;
    int d = this->day;
    if (1582 == y && 10 == m) {
        if (d > 4) {
            d -= 10;
        }
    }
    if (days > 0) {
        d += days;
        int daysInMonth = Solar::getDaysOfMonth(y, m);
        while (d > daysInMonth) {
            d -= daysInMonth;
            m++;
            if (m > 12) {
                m = 1;
                y++;
            }
            daysInMonth = Solar::getDaysOfMonth(y, m);
        }
    } else if (days < 0) {
        while (d + days <= 0) {
            m--;
            if (m < 1) {
                m = 12;
                y--;
            }
            d += Solar::getDaysOfMonth(y, m);
        }
        d += days;
    }
    if (1582 == y && 10 == m) {
        if (d > 4) {
            d += 10;
        }
    }

    return Solar(y, m, d, this->hour, this->minute, this->second);
}

Solar Solar::nextHour(int hours) {
    int h = this->hour + hours;
    int n = h < 0 ? -1 : 1;
    int hour = abs(h);
    int days = hour / 24 * n;
    hour = (hour % 24) * n;
    if (hour < 0) {
        hour += 24;
        days--;
    }
    Solar solar = next(days);
    return Solar(solar.getYear(), solar.getMonth(), solar.getDay(), hour, solar.getMinute(), solar.getSecond());
}

/*返回公历某一个日的'公农回'三合历*/
OB_DAY Solar::riLiCalc(int By, int Bm, int Bd, int Bh, int Bmin, double Bs, double J)
{
    //std::cout << "By " << By << " Bm " <<Bm <<" Bd "<< Bd << "Bh" << Bh << "Bmin" << Bmin << "Bs" << Bs << std::endl;
    int i, j, k, D, Bd0, Bdn, xn;
    //日历物件初始化
    Date JD = { By, Bm, 1, 12, 0, 0.1 };
    Bd0 = int2(toJD(JD)) - J2000;	//公历月首,中午
    JD.M++;
    if (JD.M > 12)
        JD.Y++, JD.M = 1;
    Bdn = int2(toJD(JD)) - J2000 - Bd0;	//本月天数(公历)

    OB_DAY ob;
    i = Bd - 1;
    SSQ ssq;

    ob.d0 = Bd0 + i;		//儒略日,北京时12:00
    ob.di = i;				//公历月内日序数
    ob.y  = By;    //公历年
    ob.m  = Bm;    //公历月
    ob.dn = Bdn;   //公历月天数
    ob.week0 = (Bd0 + J2000 + 1 + 7000000) % 7; //月首的星期
    ob.week = (ob.week0 + i) % 7;	//当前日的星期
    ob.weeki = int2((ob.week0 + i) / 7);	//本日所在的周序号
    ob.weekN = int2((ob.week0 + Bdn - 1) / 7) + 1;	//本月的总周数
    JD = setFromJD(ob.d0 + J2000);
    ob.d = JD.D;			//公历日名称

    Date dateBz = { By, Bm,  Bd, Bh, Bmin, Bs };
    double jdBz = toJD(dateBz) + (-8.0)/24-J2000;
    double jd2s = jdBz + dt_T(jdBz);	//力学时
    jdBz += pty_zty2(jd2s / 36525) + J / M_PI / 2;	//本地真太阳时(使用低精度算法计算时差)
    ob.date_zty = jdBz;

    //农历月历
    //if (!ssq.ZQ[0] || ob.d0 < ssq.ZQ[0] || ob.d0 >= ssq.ZQ[24])	//如果d0已在计算农历范围内则不再计算
    ssq.calcY(ob.d0);
    int mk = int2((ob.d0 - ssq.HS[0]) / 30.0);
    if (mk < 13 && ssq.HS[mk + 1] <= ob.d0)
        mk++;				//农历所在月的序数

    ob.Ldi = ob.d0 - ssq.HS[mk];	//距农历月首的编移量,0对应初一
    ob.Ldc=str_rmc[ob.Ldi];	//农历日名称
    ob.cur_dz = ob.d0 - ssq.ZQ[0]; 	// 距冬至的天数
    ob.cur_lc = ob.d0 - ssq.ZQ[3]; 	// 距立春的天数
    ob.cur_xz = ob.d0 - ssq.ZQ[12];	// 距夏至的天数
    ob.cur_lq = ob.d0 - ssq.ZQ[15];	// 距立秋的天数
    ob.cur_mz = ob.d0 - ssq.ZQ[11];	// 距芒种的天数
    ob.cur_xs = ob.d0 - ssq.ZQ[13];	// 距小暑的天数
    ob.Lmc = ssq.ym[mk];	//月名称
    ob.Ldn = ssq.dx[mk];	//月大小
    ob.Lleap = (ssq.leap && ssq.leap == mk) ? "闰" : "";	//闰状况
    ob.Lmc2= mk<13?ssq.ym[mk+1]:"未知";

    int qk = int2((ob.d0 - ssq.ZQ[0] - 7) / 15.2184);
    if (qk < 23 && ob.d0 >= ssq.ZQ[qk + 1])
        qk++;	//节气的取值范围是0-23
    if (ob.d0 == ssq.ZQ[qk])
        ob.Ljq =str_jqmc[qk];
    else
        ob.Ljq = "";

    ob.yxmc = "";	//月相名称,月相时刻(儒略日),月相时间串
    ob.jqmc = "";	//定气名称,节气时刻(儒略日),节气时间串

    //干支纪年处理
    //以立春为界定年首
    D = ssq.ZQ[3] + (ob.d0 < ssq.ZQ[3] ? -365 : 0) + 365.25 * 16 - 35;	//以立春为界定纪年
    ob.Lyear = floor(D / 365.2422 + 0.5);	//农历纪年(10进制,1984年起算)
    //以下几行以正月初一定年首
    D = ssq.HS[2];	//一般第3个月为春节
    for (j = 0; j < 14; j++)
    {						//找春节
        if (ssq.ym[j] != "正" || ssq.leap == j && j)
            continue;
        D = ssq.HS[j];
        if (ob.d0 < D)
        {
            D -= 365;
            break;
        }//无需再找下一个正月
    }
    D = D + 5810;//计算该年春节与1984年平均春节(立春附近)相差天数估计
    ob.Lyear0 = floor(D / 365.2422 + 0.5);
    D = ob.Lyear + 12000;
    ob.Lyear2 = str_gan[D % 10];
    ob.Lyear2 += str_zhi[D % 12];//干支纪年(立春)
    D = ob.Lyear0 + 12000;
    ob.Lyear3 = str_gan[D % 10];
    ob.Lyear3 += str_zhi[D % 12];//干支纪年(正月)
    ob.Lyear4 = ob.Lyear0 + 1984 + 2698;//黄帝纪年

    //纪月处理,1998年12月7(大雪)开始连续进行节气计数,0为甲子
    mk = int2((ob.d0 - ssq.ZQ[0]) / 30.43685);
    if (mk < 12 && ob.d0 >= ssq.ZQ[2 * mk + 1])
        mk++;//相对大雪的月数计算,mk的取值范围0-12

    D = mk + int2((ssq.ZQ[12] + 390) / 365.2422) * 12 + 900000;	//相对于1998年12月7(大雪)的月数,900000为正数基数
    ob.Lmonth = D % 12;
    ob.Lmonth2 = str_gan[D % 10];
    ob.Lmonth2 += str_zhi[D % 12];

    //纪日,2000年1月7日起算
    D = ob.d0 - 6 + 9000000;
    ob.Lday2 = str_gan[D % 10];
    ob.Lday2 += str_zhi[D % 12];

    //纪时
    jdBz += 13.0 / 24;
    int D1 = floor( jdBz);
    int SC = int2((jdBz - D1) * 12);
    int v = (D1 - 1) * 12 + 90000000 + SC;
    std::string js = mystl::string(str_gan[v % 10]) + str_zhi[v % 12];
    ob.Ltime2 = js;
    v -= SC, ob.bz_JS = "";		//全天纪时表
    for (i = 0; i < 13; i++)
    {							//一天中包含有13个纪时
        mystl::string c = mystl::string(str_gan[(v + i) % 10]) + str_zhi[(v + i) % 12];	//各时辰的八字
        ob.bz_JS += (i ? " " : "") + c;
    }

    //星座
    mk = int2((ob.d0 - ssq.ZQ[0] - 15) / 30.43685);
    if (mk < 11 && ob.d0 >= ssq.ZQ[2 * mk + 2])
        mk++;				//星座所在月的序数,(如果j=13,ob.d0不会超过第14号中气)
    ob.XiZ = str_xz[(mk + 12) % 12];

    //回历
    OBA::getHuiLi(ob.d0,ob);
    //节日
    OBA::getDayName(ob); //公历
    OBB::getDayName2(ob); //农历

    return ob;
}
