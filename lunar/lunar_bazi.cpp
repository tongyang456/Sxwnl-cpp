#include <list>
#include "lunar_bazi.h"
#include "solar_bazi.h"
#include "lunar.h"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include "../eph/eph0.h"

//通过农历日计算儒略日数
bool Lunar::calcJulianDay( int lunarYear, int lunarMonth, int lunarDay, double &JulianDay )
{
    int ZQ1[29] = {0};//中气表
    int HS1[17] = {0};;//合朔表
    int dx1[16] = {0};;//各月大小
    int ym[16] = {0};;
    int pe1[2] = {0};; //补算二气
    int leap1 = 0;  //闰月位置
    int *A = ZQ1, *B = HS1;  //中气表,日月合朔表(整日)
    int i;
    double W, w;

    //该年的气
    int jd = int2((lunarYear-2000.0)*365.2422+180);
    W = int2((jd - 355 + 183) / 365.2422) * 365.2422 + 355;  //355是2000.12冬至,得到较靠近jd的冬至估计值
    if (SSQ::calc(W, 1) > jd) W -= 365.2422;
    for (i = 0; i < 29; i++)    //节气
    {
        A[i] = SSQ::calc(W + 15.2184 * i, 1); //25个节气时刻(北京时间),从冬至开始到下一个冬至以后
    }
    pe1[0] = SSQ::calc(W - 15.2, 1), pe1[1] = SSQ::calc(W - 30.4, 1); //补算二气,确保一年中所有月份的“气”全部被计算在内

    //今年"首朔"的日月黄经差w
    w = SSQ::calc(A[0], 0); //求较靠近冬至的朔日
    if (w > A[0]) w -= 29.53;

    //该年所有朔,包含14个月的始末
    for (i = 0; i < 17; i++) {
        B[i] = SSQ::calc(w + 29.5306 * i, 0);
    }

    //月大小
    for (i = 0; i < 16; i++) {
        dx1[i] = B[i + 1] - B[i]; //月大小
        ym[i] = i;  //月序初始化
    }

    //无中气置闰法确定闰月,(气朔结合法,数据源需有冬至开始的的气和朔)
    if (B[15] <= A[28]) { //第13月的月末没有超过冬至(不含冬至),说明今年含有13个月
        for (i = 1; B[i + 1] > A[2 * i] && i < 15; i++); //在13个月中找第1个没有中气的月份
        leap1 = i;
        for (; i < 16; i++) ym[i]--;
    }

    //名称转换(月建别名)
    std::array<std::string, 16> ym1;//各月名称
    for (i = 0; i < 16; i++) {
        double Dm = B[i] + J2000;
        int v2 = ym[i]; //Dm初一的儒略日,v2为月建序号
        std::string mc = str_ymc[v2 % 12]; //月建对应的默认月名称：建子十一,建丑十二,建寅为正……
        if (Dm >= 1724360 && Dm <= 1729794) mc = str_ymc[(v2 + 1) % 12]; //  8.01.15至 23.12.02 建子为十二,其它顺推
        else if (Dm >= 1807724 && Dm <= 1808699) mc = str_ymc[(v2 + 1) % 12]; //237.04.12至239.12.13 建子为十二,其它顺推
        else if (Dm >= 1999349 && Dm <= 1999467) mc = str_ymc[(v2 + 2) % 12]; //761.12.02至762.03.30 建子为正月,其它顺推
        else if (Dm >= 1973067 && Dm <= 1977052) {
            if (v2 % 12 == 0) mc = "正";
            if (v2 == 2) mc = "一";
        } //689.12.18至700.11.15 建子为正月,建寅为一月,其它不变
        if (Dm == 1729794 || Dm == 1808699) mc = "拾贰"; //239.12.13及23.12.02均为十二月,为避免两个连续十二月，此处改名
        ym1[i] = mc;
    }

    int monthIdx,dayCount;
    double v, firstJulianDay;
    bool exist_flag = false;

    for(int i1=0;i1<16;i1++)
    {
        if(HS1[i1+1]>ZQ1[28]) break;
        v = OBB::so_accurate2(HS1[i1]);
        firstJulianDay= v + J2000;    //农历月月首儒略日

        int D1 = ZQ1[3] + (v < ZQ1[3] ? -365 : 0) + 365.25 * 16 - 35;	//以立春为界定纪年
        int Lyear = floor(D1 / 365.2422 + 0.5);	//农历纪年(10进制,1984年起算)

        if(leap1 && i1==leap1)
            monthIdx = findIndex(ym1[i1], str_ymc, 12, +11) % 12 * -1;
        else
            monthIdx = findIndex(ym1[i1], str_ymc, 12, +11) % 12;

        dayCount = dx1[i1]>29 ? 30 : 29;
        if( ((Lyear+1984)==lunarYear) && (monthIdx==lunarMonth) ){
            exist_flag = true;
            break;
        }
    }

    if( lunarDay > dayCount ){
        std::string message = "1wrong lunar year " + std::to_string(lunarYear) + " lunarMonth " +
                              std::to_string(lunarMonth) + " lunarDay " + std::to_string(lunarDay);
        throw std::invalid_argument(message);
    }

    Date tmpJd = setFromJD(firstJulianDay + lunarDay -1);
    JulianDay = toJD({ tmpJd.Y, tmpJd.M, tmpJd.D, hour, minute, static_cast<double >(second) });
    return exist_flag;
}

Lunar::Lunar(int lunarYear, int lunarMonth, int lunarDay, int hour, int minute, int second)
{
    this->year = lunarYear;
    this->month = lunarMonth;
    this->day = lunarDay;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
    this->JulianDay = JulianDay;

    bool exist_flag = calcJulianDay( lunarYear, lunarMonth, lunarDay, JulianDay );
    if( exist_flag == false ){
        std::cout << "lunarYear" << lunarYear << "lunarMonth" << lunarMonth << "lunarDay" << lunarDay << std::endl;
        std::string message = "2wrong lunar year " + std::to_string(lunarYear) + " lunarMonth ";
        throw std::invalid_argument(message);
    }

    Date dd = setFromJD(JulianDay);
    this->ob_day = Solar::riLiCalc(dd.Y,dd.M,dd.D,hour,minute,second);
}

Lunar::Lunar(Solar solar){
    this->ob_day = solar.riLiCalc(solar.getYear(),solar.getMonth(),solar.getDay(),
                                  solar.getHour(),solar.getMinute(),solar.getMinute());
    this->year = ob_day.Lyear0 + 1984;
    if( ob_day.Lleap == "闰" ){
        this->month = ob_day.Lmonth * -1;
    }else{
        this->month = ob_day.Lmonth;
    }
    this->day = ob_day.Ldi;
    this->hour = solar.getHour();
    this->minute = solar.getMinute();
    this->second = solar.getSecond();
    this->JulianDay = solar.getJulianDay();
}

Lunar::Lunar(double JulianDay){
    Solar solar(JulianDay);
    this->ob_day = solar.riLiCalc(solar.getYear(),solar.getMonth(),solar.getDay(),
                                  solar.getHour(),solar.getMinute(),solar.getMinute());
    this->year = ob_day.Lyear0 + 1984;
    if( ob_day.Lleap == "闰" ){
        this->month = ob_day.Lmonth * -1;
    }else{
        this->month = ob_day.Lmonth;
    }
    this->day = ob_day.Ldi;
    this->hour = solar.getHour();
    this->minute = solar.getMinute();
    this->second = solar.getSecond();
    this->JulianDay = JulianDay;
}

std::string Lunar::toString() {
    return ("农历年: " + std::to_string(this->year) +
            " 农历月: " + std::to_string(this->month) +
            " 农历日: " + std::to_string(this->day) +
            " 农历时: " + std::to_string(this->hour) +
            " 农历分: " + std::to_string(this->minute) +
            " 农历秒: " + std::to_string(this->second) +
            " 儒略日数 " + std::to_string(this->JulianDay));
            }

Lunar Lunar::next(int days){
    return Solar(getJulianDay()).next(days).getLunar();
}

//返回指定年的农历月信息
std::list<LN_MONTH> Lunar::getLunarDate(int Year)
{//农历排月序计算,可定出农历,有效范围：两个冬至之间(冬至一 <= d < 冬至二)
    int jd = int2((Year-2000.0)*365.2422+180);
    std::list<LN_MONTH> ret_M;
    std::array<std::string, 16> ym1;//各月名称
    int ZQ1[29];//中气表
    int HS1[17];//合朔表
    int dx1[16];//各月大小
    int ym[16];
    int pe1[2]; //补算二气
    int leap1 = 0;  //闰月位置

    int *A = ZQ1, *B = HS1;  //中气表,日月合朔表(整日)
    int i;
    double W, w;

    //该年的气
    W = int2((jd - 355 + 183) / 365.2422) * 365.2422 + 355;  //355是2000.12冬至,得到较靠近jd的冬至估计值
    if (SSQ::calc(W, 1) > jd) W -= 365.2422;
    for (i = 0; i < 29; i++)    //节气
    {
        A[i] = SSQ::calc(W + 15.2184 * i, 1); //25个节气时刻(北京时间),从冬至开始到下一个冬至以后
    }
    pe1[0] = SSQ::calc(W - 15.2, 1), pe1[1] = SSQ::calc(W - 30.4, 1); //补算二气,确保一年中所有月份的“气”全部被计算在内

    //今年"首朔"的日月黄经差w
    w = SSQ::calc(A[0], 0); //求较靠近冬至的朔日
    if (w > A[0]) w -= 29.53;

    //该年所有朔,包含14个月的始末
    for (i = 0; i < 17; i++) {
        B[i] = SSQ::calc(w + 29.5306 * i, 0);
    }

    //月大小
    for (i = 0; i < 16; i++) {
        dx1[i] = B[i + 1] - B[i]; //月大小
        ym[i] = i;  //月序初始化
    }

    //无中气置闰法确定闰月,(气朔结合法,数据源需有冬至开始的的气和朔)
    if (B[15] <= A[28]) { //第13月的月末没有超过冬至(不含冬至),说明今年含有13个月
        for (i = 1; B[i + 1] > A[2 * i] && i < 15; i++); //在13个月中找第1个没有中气的月份
        leap1 = i;
        for (; i < 16; i++) ym[i]--;
    }

    //名称转换(月建别名)
    for (i = 0; i < 16; i++) {
        double Dm = B[i] + J2000;
        int v2 = ym[i]; //Dm初一的儒略日,v2为月建序号
        std::string mc = str_ymc[v2 % 12]; //月建对应的默认月名称：建子十一,建丑十二,建寅为正……
        if (Dm >= 1724360 && Dm <= 1729794) mc = str_ymc[(v2 + 1) % 12]; //  8.01.15至 23.12.02 建子为十二,其它顺推
        else if (Dm >= 1807724 && Dm <= 1808699) mc = str_ymc[(v2 + 1) % 12]; //237.04.12至239.12.13 建子为十二,其它顺推
        else if (Dm >= 1999349 && Dm <= 1999467) mc = str_ymc[(v2 + 2) % 12]; //761.12.02至762.03.30 建子为正月,其它顺推
        else if (Dm >= 1973067 && Dm <= 1977052) {
            if (v2 % 12 == 0) mc = "正";
            if (v2 == 2) mc = "一";
        } //689.12.18至700.11.15 建子为正月,建寅为一月,其它不变
        if (Dm == 1729794 || Dm == 1808699) mc = "拾贰"; //239.12.13及23.12.02均为十二月,为避免两个连续十二月，此处改名
        ym1[i] = mc;
    }

    LN_MONTH lm_month;
    std::string s="", s1,s2;
    double v,qi;
    for(int i1=0;i1<16;i1++)
    {
        memset(&lm_month, 0, sizeof(LN_MONTH));
        lm_month.index = i1;
        if(HS1[i1+1]>ZQ1[28])
            break; //已包含下一年的冬至
        if(leap1 && i1==leap1)
            lm_month.month = findIndex(ym1[i1], str_ymc, 12, +11) % 12 * -1;
        else
            lm_month.month = findIndex(ym1[i1], str_ymc, 12, +11) % 12;

        dx1[i1]>29?(lm_month.dayCount=30):(lm_month.dayCount=29);

        v = OBB::so_accurate2(HS1[i1]);
        lm_month.firstJulianDay=v+J2000;
        ret_M.push_back(lm_month);
    }
    return ret_M;
}