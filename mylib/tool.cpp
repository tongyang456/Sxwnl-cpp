#include <cstdio>
#include <cstdlib>

//#include "std/my_string.h"
#include "tool.h"
#include "math_patch.h"
#include <map>
#include <string>


//实现字符替换
void string_replace( std::string &strBig, const std::string &strsrc, const std::string &strdst)
{
    std::string::size_type pos = 0;
    std::string::size_type srclen = strsrc.size();
    std::string::size_type dstlen = strdst.size();

    while( (pos=strBig.find(strsrc, pos)) != std::string::npos )
    {
        strBig.replace( pos, srclen, strdst );
        pos += dstlen;
    }
}

//提取jd中的时间(去除日期)
std::string timeStr(double jd)
{
	int h, m, s;
	jd += 0.5;
	jd = (jd - int2(jd));
	s = int2(jd * 86400 + 0.5);
	h = int2(s / 3600.0);
	s -= h * 3600;
	m = int2(s / 60.0);
	s -= m * 60;
	std::string H, M, S;
	H = "0" + to_str(h);
	M = "0" + to_str(m);
	S = "0" + to_str(s);
	return H.substr(H.length() - 2, 2) + ":" + M.substr(M.length() - 2, 2) + ":" + S.substr(S.length() - 2, 2);
}

//===============角度格式化==================
std::string rad2strE(double d, bool flag, int ext)
{	
	//将弧度转为字串,ext为小数保留位数
	//flag=0输出格式示例: -23°59" 48.23"
	//flag=1输出格式示例:  18h 29m 44.52s
	std::string s = " ", w1 = "°", w2 = "\'", w3 = "\"";
	if (d < 0)
		d = -d, s = "-";
	if (flag)
	{
		d *= 12 / M_PI;
		w1 = "h", w2 = "m", w3 = "s";
	}
	else
		d *= 180 / M_PI;
	int a = floor(d);
	d = (d - a) * 60;
	int b = floor(d);
	d = (d - b) * 60;
	int c = floor(d);

	double Q = pow(10, ext);

	d = floor((d - c) * Q + 0.5);
	if (d >= Q)
		d -= Q, c++;
	if (c >= 60)
		c -= 60, b++;
	if (b >= 60)
		b -= 60, a++;

	std::string A, B, C, D;
	A = "   " + to_str(a);
	B = "0" + to_str(b);
	C = "0" + to_str(c);
	D = "00000" + to_str((int)d);
	s += A.substr(A.length() - 3, 3) + w1;
	s += B.substr(B.length() - 2, 2) + w2;
	s += C.substr(C.length() - 2, 2);
	if (ext)
		s += "." + D.substr(D.length() - ext, ext) + w3;
	return s;
}

//将弧度转为字串,保留2位
std::string rad2str(double d, bool tim)
{	
	return rad2strE(d, tim, 2);
}

//将弧度转为字串,精确到分
std::string rad2str2(double d)
{	
	//输出格式示例: -23°59"
	std::string s = "+", w1 = "°", w2 = "\'", w3 = "\"";
	if (d < 0)
		d = -d, s = "-";
	d *= 180 / M_PI;
	int a = floor(d);
	int b = floor((d - a) * 60 + 0.5);
	if (b >= 60)
		b -= 60, a++;
	std::string A = "   " + to_str(a), B = "0" + to_str(b);
	s += A.substr(A.length() - 3, 3) + w1;
	s += B.substr(B.length() - 2, 2) + w2;
	return s;
}

//秒转为分秒,fx为小数点位数,fs为1转为"分秒"格式否则转为"角度分秒"格式
std::string m2fm(double v, int fx, int fs)
{
	std::string gn = "";
	if (v < 0)
		v = -v, gn = "-";
	int f = floor(v / 60);
	double m = v - f * 60;
	if (!fs)
		return gn + to_str(f) + "\'" + to_str(m, fx) + "\"";
	if (fs == 1)
		return gn + to_str(f) + "分" + to_str(m, fx) + "秒";
	if (fs == 2)
		return gn + to_str(f) + "m" + to_str(m, fx) + "s";
	else
		return "error";
}

//公历转儒略日
double toJD(Date date)
{
	double y = date.Y, m = date.M, n = 0;	//取出年月
	if (m <= 2)
		m += 12, y--;
	if (date.Y * 372 + date.M * 31 + date.D >= 588829)
		//判断是否为格里高利历日1582*372+10*31+15
		n = (int) (y / 100), n = 2 - n + (int) (n / 4);	//加百年闰
	n += (int) (365.25 * (y + 4716) + 0.01);	//加上年引起的偏移日数
	n += (int) (30.6 * (m + 1)) + date.D;	//加上月引起的偏移日数及日偏移数
	n += ((date.s / 60.0 + date.m) / 60.0 + date.h) / 24.0 - 1524.5;
	return n;
}

//儒略日数转公历
Date setFromJD(double jd)
{
	Date r = { 0 };
	int D = int2(jd + 0.5), c;
	double F = jd + 0.5 - D;	//取得日数的整数部份A及小数部分F
	if (D >= 2299161)
		c = int2((D - 1867216.25) / 36524.25), D += 1 + c - int2(c / 4.0);
	D += 1524;
	r.Y = int2((D - 122.1) / 365.25);	//年数
	D -= int2(365.25 * r.Y);
	r.M = int2(D / 30.601);		//月数
	D -= int2(30.601 * r.M);
	r.D = D;					//日数
	if (r.M > 13)
		r.M -= 13, r.Y -= 4715;
	else
		r.M -= 1, r.Y -= 4716;

	//日的小数转为时分秒
	F *= 24.0;
	r.h = int2(F);
	F -= r.h;
	F *= 60.0;
	r.m = int2(F);
	F -= r.m;
	F *= 60.0;
	r.s = F;
	return r;
}

// 日期对象转为字符串
std::string DD2str(Date r)
{ 
	std::string
	Y = "     " + to_str(r.Y), 
	M = "0" + to_str(r.M), 
	D = "0" + to_str(r.D);
	
	int h = r.h, m = r.m, s = int2(r.s + .5);
	if (s >= 60)
		s -= 60, m++;
	if (m >= 60)
		m -= 60, h++;

	std::string _h, _m, _s;
	_h = "0" + to_str(h);
	_m = "0" + to_str(m);
	_s = "0" + to_str(s);
	Y = Y.substr(Y.length() - 5, 5);
	M = M.substr(M.length() - 2, 2);
	D = D.substr(D.length() - 2, 2);
	_h = _h.substr(_h.length() - 2, 2);
	_m = _m.substr(_m.length() - 2, 2);
	_s = _s.substr(_s.length() - 2, 2);
	
	return Y + "-" + M + "-" + D + " " + _h + ":" + _m + ":" + _s;
}

// JD转为字符串
std::string JD2str(double jd)
{
	Date r=setFromJD(jd);
	return DD2str(r);
}

std::string fill_str(std::string s, int n, std::string c) {
	int len=s.length();
	for(int i=0;i<n-len;i++){
		s=c+s;
	}
	return s;
}

// 将time_t转换为Date结构体
Date timeToStruct(time_t t) {
    Date date = {0,0,0,0,0,0.00};
	struct tm *tm = localtime(&t);
    date.Y = tm->tm_year + 1900;
    date.M = tm->tm_mon + 1;
    date.D = tm->tm_mday;
    date.h = tm->tm_hour;
    date.m = tm->tm_min;
    date.s = (double)tm->tm_sec;
	return date;
}

// 将Date结构体转换回time_t
time_t structToTime(struct Date date) {
    struct tm tm = {0};
    tm.tm_year = date.Y - 1900;
    tm.tm_mon = date.M - 1;
    tm.tm_mday = date.D;
    tm.tm_hour = date.h;
    tm.tm_min = date.m;
    tm.tm_sec = (int)date.s;

    // 调整tm结构体，使其成为有效的本地时间
	return mktime(&tm);
}

time_t string_to_time_t(const std::string& time_str) {
    std::tm tm = {};
    std::istringstream ss(time_str);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return mktime(&tm);
}

// 将time_t转换回字符串形式
std::string time_t_to_string(time_t time) {
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&time));
    return std::string(buffer);
}

// 找到差距最小的两个时间戳及其对应的值
ClosestTimestamps find_closest_timestamps(const std::map<std::string, std::string>& timestamps_map, const std::string& given_time_str) {
    time_t given_time = string_to_time_t(given_time_str);
    time_t closest_time_before = 0;
    time_t closest_time_after = 0;
    std::string closest_value_before, closest_value_after;
    std::ptrdiff_t min_diff_before = std::numeric_limits<std::ptrdiff_t>::max();
    std::ptrdiff_t min_diff_after = std::numeric_limits<std::ptrdiff_t>::max();

    for (const auto& pair : timestamps_map) {
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

    return ClosestTimestamps{closest_value_before, closest_value_after, closest_time_before, closest_time_after};
}

Date getDateAfter(const Date before, const Date diff){
	time_t time_input = structToTime(before);
	std::tm tm_input = *std::localtime(&time_input);
	tm_input.tm_year += diff.Y;
    tm_input.tm_mon += diff.M;
    tm_input.tm_mday += diff.D;
    tm_input.tm_hour += diff.h;
	tm_input.tm_min += diff.m;
	tm_input.tm_sec += static_cast<int>(diff.s);
	time_t time_output = mktime(&tm_input);
	Date ret = timeToStruct(time_output);
	return ret;
}

Date convFormat(int sec){
	Date diff = {0,0,0,0,0,0.0};
	diff.D = sec/(60*60*24);
    sec %= 60*60*24;
    diff.h = sec/(60*60);
    sec %= 60*60;
    diff.m = sec/60;
    sec %= 60;
	diff.s = static_cast<double>(sec);
	return diff;
}

Date convFormatDy(int sec){//待优化
    Date diff = convFormat(sec);
    //三天一岁、一天四个月、一个时辰10天；
    int year = 0;
    int month = diff.D * 4;     //一天4个月
    int day = diff.h * 5;       //一个时辰10天
    int hour = diff.m * 2;      //一分钟2小时
    int min = diff.s * 2;       //一秒2分钟
    
    hour += min/60;
    min %= 60;

    day += hour/24;
    hour %= 24;

    month += day/30;
    day %=30;

    year += month/12;
    month %=12; 

	diff.Y = year;
	diff.M = month;
	diff.D = day;
	diff.h = hour;
	diff.m = min;
	diff.s = 0.0;
	return diff;
}

void getPreMDate(Date &date){
	if(date.M == 1){
		date.M = 12;
		date.Y--;
	}else{
		date.M--;
	}
}

void getNextMDate(Date &date){
	if(date.M == 12){
		date.M = 1;
		date.Y++;
	}else{
		date.M++;
	}
}

// 查找函数实现
int findIndex(std::string str, const char *array[], int size, int offset)
{
  for (int i = 0; i < size; i++)
  {
    if (array[i] == str)
    {
      return i + offset;
    }
  }
  return -1;
}

// 计算月份中的天数（从月首开始计算）
int dayInMonth(const Date& date) {
    // 这里简化处理，实际应考虑每个月的实际天数和闰年等
    return date.D + date.h / 24 + date.m / 1440;
}


/*
int main() {
	Date d = {-5621,11,12,10,30,50.6987};
	// std::cout<<to_str(555)<<"\n";
	// std::cout<<to_str(555.464,2)<<"\n";
	// std::string ss = to_str(1234);
	// std::cout<<ss.begin() <<"\n";
	std::cout<<DD2str(d)<<"\n";
	std::cout<<"-->"<<my_stoi("12333")<<"\n";
}
// */
