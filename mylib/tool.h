#ifndef TOOL_H
#define TOOL_H

#include <cstdlib>
#include "../mylib/mystl/my_string.h"
#include "../mylib/math_patch.h"
#include <sstream>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <chrono>

#define A2R(x) ((x) / 180 * M_PI)

inline int int2(double v) {return (int)floor(v);};


struct Date
{//儒略历结构，包含: 年 月 日 时 分 秒 (浮点型)
	int Y, M, D, h, m;
	double s;
    // 重载小于运算符
    bool operator<(const Date& other) const {
        if (Y != other.Y) return Y < other.Y;
        if (M != other.M) return M < other.M;
        if (D != other.D) return D < other.D;
        if (h != other.h) return h < other.h;
        if (m != other.m) return m < other.m;
        // 对于秒，由于是浮点数，直接比较可能会有精度问题，这里简单比较
        return s < other.s;
    }
};

//mystl::vector<mystl::string> split(const mystl::string& src, const mystl::string& separator);
void string_replace( mystl::string &strBig, const mystl::string &strsrc, const mystl::string &strdst);
mystl::string timeStr(double jd);
mystl::string rad2strE(double d, bool tim, int ext);
mystl::string rad2str(double d, bool tim);
mystl::string rad2str2(double d);
mystl::string m2fm(double v, int fx, int fs);
double toJD(Date date);
Date setFromJD(double jd);
mystl::string DD2str(Date r);
mystl::string JD2str(double jd);
mystl::string fill_str(mystl::string s, int n, mystl::string c);

void getPreMDate(Date &date);
void getNextMDate(Date &date);

Date timeToStruct(time_t t);
time_t structToTime(const struct Date date);

time_t string_to_time_t(const std::string& time_str);
std::string time_t_to_string(time_t time);

struct ClosestTimestamps {
    std::string closest_value_before;
    std::string closest_value_after;
    time_t closest_time_before;
    time_t closest_time_after;
};
ClosestTimestamps find_closest_timestamps(const std::map<std::string, std::string>& timestamps_map, const std::string& given_time_str);
Date getDateAfter(const Date before, const Date diff);
Date convFormat(int sec);
Date convFormatDy(int sec);
int findIndex(std::string str, const char *array[], int size, int offset);
int dayInMonth(const Date& date);

#endif
