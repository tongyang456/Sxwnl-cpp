#ifndef TOOL_H
#define TOOL_H

#include <cstdlib>
//#include "../mylib/std/my_string.h"
#include "../mylib/math_patch.h"
#include <sstream>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <chrono>
#include <string>

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

template <class T>
inline std::string to_str(T value, int precision = 4, int length = 0, bool right_align = false) {
    std::string str;

    if (std::is_floating_point<T>::value) { // 浮点数
        // 使用 sprintf 或者其他方式来格式化浮点数
        char temp[32];
        sprintf(temp, "%.*f", precision, static_cast<double>(value));
        str = temp;
    } else { // 整数
        str = std::to_string(value);
    }

    std::string fill(length > static_cast<int>(str.length()) ? length - static_cast<int>(str.length()) : 0, ' ');
    return right_align ? (fill + str) : (str + fill);
}

inline int my_stoi(const std::string &str, typename std::string::size_type *pos = nullptr, int base = 10)
{
    typename std::string::value_type *end;
    int answer = ::strtol(str.data(), &end, base);
    if (end == str.data())
    {
        throw std::invalid_argument("invalid stof argument");
    }

    if (errno == ERANGE)
    {
        throw std::out_of_range("stof argument out of range");
    }

    if (pos)
    {
        *pos = end - str.data();
    }

    return answer;
}



//std::vector<std::string> split(const std::string& src, const std::string& separator);
void string_replace( std::string &strBig, const std::string &strsrc, const std::string &strdst);
std::string timeStr(double jd);
std::string rad2strE(double d, bool tim, int ext);
std::string rad2str(double d, bool tim);
std::string rad2str2(double d);
std::string m2fm(double v, int fx, int fs);
double toJD(Date date);
Date setFromJD(double jd);
std::string DD2str(Date r);
std::string JD2str(double jd);
std::string fill_str(std::string s, int n, std::string c);

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
