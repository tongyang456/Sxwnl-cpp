#include <list>
#include "triad.h"
#include "lunar.h"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include "../eph/eph0.h"

Triad::Triad(int year, int month, int day, int hour, int minute, double second) {
    year_ = year;
    month_ = month;
    day_ = day;
    hour_ = hour;
    minute_ = minute;
    second_ = second;
    jd_ = toJD({year_, month_, day_, hour_, minute_, second_});
    ob_day_ = riLiCalc(year_, month_, day_, hour_, minute_, second_);
    Lyear_ = ob_day_.Lyear0 + 1984; //春节
    Lmonth_ = ob_day_.Lmc;
    Lday_ = ob_day_.Ldc;
    Leap_ = ob_day_.Lleap;
}

Triad::Triad(int Lyear, std::string Lmonth, std::string Lday, int hour, int minute,std::string Leap) {
    Lyear_ = Lyear;
    Lmonth_ = Lmonth;
    Lday_ = Lday;
    Leap_ = Leap;
    hour_ = hour;
    minute_ = minute;

    bool exist_flag = calcJulianDay(Lyear_, Lmonth_, Lday_, hour_, minute_, Leap_, jd_);
    if (exist_flag == false) {
        std::cout << "lunarYear" << Lyear_ << "lunarMonth" << Lmonth_ << "lunarDay" << Lday_ << std::endl;
        std::string message = "2wrong lunar year " + std::to_string(Lyear_) + " lunarMonth " + Lmonth_;
        throw std::invalid_argument(message);
    }

    Date sdate = setFromJD(jd_);
    year_ = sdate.Y;
    month_ = sdate.M;
    day_ = sdate.D;
    hour_ = sdate.h;
    minute_ = sdate.m;
    second_ = sdate.s;
    ob_day_ = riLiCalc(year_, month_, day_, hour_, minute_, second_);
}


Triad::Triad(std::string nian, std::string yue, std::string ri, std::string shi, int baseyear) {
    std::list<Date> tstLst = fromBaZi(nian, yue, ri, shi, 2, 1970);
    if (tstLst.size() > 1) {
        throw std::invalid_argument("符合条件八字过多");
    } else if (tstLst.empty()) {
        throw std::invalid_argument("无符合条件八字");
    }
    Date sdate = tstLst.front(); // 获取第一个元素
    jd_ = toJD(sdate);
    year_ = sdate.Y;
    month_ = sdate.M;
    day_ = sdate.D;
    hour_ = sdate.h;
    minute_ = sdate.m;
    second_ = sdate.s;
    ob_day_ = riLiCalc(year_, month_, day_, hour_, minute_, second_);
    Lyear_ = ob_day_.Lyear0 + 1984; //春节
    Lmonth_ = ob_day_.Lmc;
    Lday_ = ob_day_.Ldc;
    Leap_ = ob_day_.Lleap;
}

Triad::Triad(double jd) {
    jd_ = jd;
    Date sdate = setFromJD(jd_);
    year_ = sdate.Y;
    month_ = sdate.M;
    day_ = sdate.D;
    hour_ = sdate.h;
    minute_ = sdate.m;
    second_ = sdate.s;
    ob_day_ = riLiCalc(year_, month_, day_, hour_, minute_, second_);
    Lyear_ = ob_day_.Lyear0 + 1984; //春节
    Lmonth_ = ob_day_.Lmc;
    Lday_ = ob_day_.Ldc;
    Leap_ = ob_day_.Lleap;
}

std::string Triad::to_string(){
    return std::to_string(Lyear_) +" "+ Lmonth_ +" "+ Lday_ +" "+ Leap_ +" "+
        std::to_string(year_) +" "+ std::to_string(month_) +" "+ std::to_string(day_) +" "+
        std::to_string( hour_) +" "+ std::to_string(minute_) +" "+ std::to_string(second_) +" "+ std::to_string(jd_);
}

/*返回公历某一个日的'公农回'三合历*/
OB_DAY Triad::riLiCalc(int By, int Bm, int Bd, int Bh, int Bmin, double Bs, double J) {
    //std::cout << "By " << By << " Bm " <<Bm <<" Bd "<< Bd << "Bh" << Bh << "Bmin" << Bmin << "Bs" << Bs << std::endl;
    int i, j, k, D, Bd0, Bdn, xn;
    //日历物件初始化
    Date JD = {By, Bm, 1, 12, 0, 0.1};
    Bd0 = int2(toJD(JD)) - J2000;    //公历月首,中午
    JD.M++;
    if (JD.M > 12)
        JD.Y++, JD.M = 1;
    Bdn = int2(toJD(JD)) - J2000 - Bd0;    //本月天数(公历)

    OB_DAY ob;
    i = Bd - 1;
    SSQ ssq;

    ob.d0 = Bd0 + i;        //儒略日,北京时12:00
    ob.di = i;                //公历月内日序数
    ob.y = By;    //公历年
    ob.m = Bm;    //公历月
    ob.dn = Bdn;   //公历月天数
    ob.week0 = (Bd0 + J2000 + 1 + 7000000) % 7; //月首的星期
    ob.week = (ob.week0 + i) % 7;    //当前日的星期
    ob.weeki = int2((ob.week0 + i) / 7);    //本日所在的周序号
    ob.weekN = int2((ob.week0 + Bdn - 1) / 7) + 1;    //本月的总周数
    JD = setFromJD(ob.d0 + J2000);
    ob.d = JD.D;            //公历日名称

    Date dateBz = {By, Bm, Bd, Bh, Bmin, Bs};
    double jdBz = toJD(dateBz) + (-8.0) / 24 - J2000;
    double jd2s = jdBz + dt_T(jdBz);    //力学时
    jdBz += pty_zty2(jd2s / 36525) + J / M_PI / 2;    //本地真太阳时(使用低精度算法计算时差)
    ob.date_zty = jdBz;

    //农历月历
    //if (!ssq.ZQ[0] || ob.d0 < ssq.ZQ[0] || ob.d0 >= ssq.ZQ[24])	//如果d0已在计算农历范围内则不再计算
    ssq.calcY(ob.d0);
    int mk = int2((ob.d0 - ssq.HS[0]) / 30.0);
    if (mk < 13 && ssq.HS[mk + 1] <= ob.d0)
        mk++;                //农历所在月的序数

    ob.Ldi = ob.d0 - ssq.HS[mk];    //距农历月首的编移量,0对应初一
    ob.Ldc = str_rmc[ob.Ldi];    //农历日名称
    ob.cur_dz = ob.d0 - ssq.ZQ[0];    // 距冬至的天数
    ob.cur_lc = ob.d0 - ssq.ZQ[3];    // 距立春的天数
    ob.cur_xz = ob.d0 - ssq.ZQ[12];    // 距夏至的天数
    ob.cur_lq = ob.d0 - ssq.ZQ[15];    // 距立秋的天数
    ob.cur_mz = ob.d0 - ssq.ZQ[11];    // 距芒种的天数
    ob.cur_xs = ob.d0 - ssq.ZQ[13];    // 距小暑的天数
    ob.Lmc = ssq.ym[mk];    //月名称
    ob.Ldn = ssq.dx[mk];    //月大小
    ob.Lleap = (ssq.leap && ssq.leap == mk) ? "闰" : "";    //闰状况
    ob.Lmc2 = mk < 13 ? ssq.ym[mk + 1] : "未知";

    int qk = int2((ob.d0 - ssq.ZQ[0] - 7) / 15.2184);
    if (qk < 23 && ob.d0 >= ssq.ZQ[qk + 1])
        qk++;    //节气的取值范围是0-23
    if (ob.d0 == ssq.ZQ[qk])
        ob.Ljq = str_jqmc[qk];
    else
        ob.Ljq = "";

    ob.yxmc = "";    //月相名称,月相时刻(儒略日),月相时间串
    ob.jqmc = "";    //定气名称,节气时刻(儒略日),节气时间串

    //干支纪年处理
    //以立春为界定年首
    D = ssq.ZQ[3] + (ob.d0 < ssq.ZQ[3] ? -365 : 0) + 365.25 * 16 - 35;    //以立春为界定纪年
    ob.Lyear = floor(D / 365.2422 + 0.5);    //农历纪年(10进制,1984年起算)
    //以下几行以正月初一定年首
    D = ssq.HS[2];    //一般第3个月为春节
    for (j = 0; j < 14; j++) {                        //找春节
        if (ssq.ym[j] != "正" || ssq.leap == j && j)
            continue;
        D = ssq.HS[j];
        if (ob.d0 < D) {
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

    D = mk + int2((ssq.ZQ[12] + 390) / 365.2422) * 12 + 900000;    //相对于1998年12月7(大雪)的月数,900000为正数基数
    ob.Lmonth = D % 12;
    ob.Lmonth2 = str_gan[D % 10];
    ob.Lmonth2 += str_zhi[D % 12];

    //纪日,2000年1月7日起算
    D = ob.d0 - 6 + 9000000;
    ob.Lday2 = str_gan[D % 10];
    ob.Lday2 += str_zhi[D % 12];

    //纪时
    jdBz += 13.0 / 24;
    int D1 = floor(jdBz);
    int SC = int2((jdBz - D1) * 12);
    int v = (D1 - 1) * 12 + 90000000 + SC;
    std::string js = std::string(str_gan[v % 10]) + str_zhi[v % 12];
    ob.Ltime2 = js;
    v -= SC, ob.bz_JS = "";        //全天纪时表
    for (i = 0; i < 13; i++) {                            //一天中包含有13个纪时
        std::string c = std::string(str_gan[(v + i) % 10]) + str_zhi[(v + i) % 12];    //各时辰的八字
        ob.bz_JS += (i ? " " : "") + c;
    }

    //星座
    mk = int2((ob.d0 - ssq.ZQ[0] - 15) / 30.43685);
    if (mk < 11 && ob.d0 >= ssq.ZQ[2 * mk + 2])
        mk++;                //星座所在月的序数,(如果j=13,ob.d0不会超过第14号中气)
    ob.XiZ = str_xz[(mk + 12) % 12];

    //回历
    OBA::getHuiLi(ob.d0, ob);
    //节日
    OBA::getDayName(ob); //公历
    OBB::getDayName2(ob); //农历

    return ob;
}

//农历日期返回一个最符合条件的儒略日
bool
Triad::calcJulianDay(int lunarYear, std::string lunarMonth, std::string lunarDay , int hour, int minute,  std::string leap, double &JulianDay) {
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
    int jd = int2((lunarYear - 2000.0) * 365.2422 + 180);
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

    int monthIdx, dayCount;
    double v, firstJulianDay;
    bool exist_flag = false;

    for (int i1 = 0; i1 < 16; i1++) {
        if (HS1[i1 + 1] > ZQ1[28]) break;
        v = OBB::so_accurate2(HS1[i1]);
        firstJulianDay = v + J2000;    //农历月月首儒略日

        int D1 = ZQ1[3] + (v < ZQ1[3] ? -365 : 0) + 365.25 * 16 - 35;    //以立春为界定纪年
        int Lyear = floor(D1 / 365.2422 + 0.5);    //农历纪年(10进制,1984年起算)

        if (leap1 && i1 == leap1)
            monthIdx = findIndex(ym1[i1], str_ymc, 12, +11) % 12 * -1;
        else
            monthIdx = findIndex(ym1[i1], str_ymc, 12, +11) % 12;

        dayCount = dx1[i1] > 29 ? 30 : 29;

        if( ((Lyear + 1984) == lunarYear) && (ym1[i1] == lunarMonth)){
            int monIdx = (findIndex(ym1[i1], str_ymc, 12, +11) % 12);
            if((leap == "闰") && ( monIdx == leap1)){
                exist_flag = true;
                break;
            }

            if( (leap != "闰") && (monIdx != leap1) ){
                exist_flag = true;
                break;
            }

            exist_flag = false;
            break;
        }
    }

    if (findIndex(lunarDay, str_rmc, 30, 1) > dayCount) {
        std::string message = "1wrong lunar year " + std::to_string(lunarYear) +
                              " lunarMonth " + lunarMonth + " lunarDay " + lunarDay;
        throw std::invalid_argument(message);
    }

    //这块后续可以优化
    Date tmpJd = setFromJD(firstJulianDay + findIndex(lunarDay, str_rmc, 30, 1) - 1);
    JulianDay = toJD({tmpJd.Y, tmpJd.M, tmpJd.D, hour, minute, 0.0});

    return exist_flag;
}

// 通过给定的八字，返回对应的阳历TUDO
std::list<Date> Triad::fromBaZi(std::string yearGanZhi, std::string monthGanZhi,
                                std::string dayGanZhi, std::string timeGanZhi, int sect, int baseYear) {
    sect = (1 == sect) ? 1 : 2;

    // 月地支距寅月的偏移值
    int m = (findIndex(monthGanZhi.substr(3, 3), str_zhi, 12, 0) - 2 + 12) % 12;

    // 月天干要一致
    if (((findIndex(yearGanZhi.substr(0, 3), str_gan, 10, 0) + 1) * 2 + m) % 10 !=
        findIndex(monthGanZhi.substr(0, 3), str_gan, 10, 0)) {
        std::cout << "无符号条件数据" << std::endl;
        exit(-1);
    }

    // 1年的立春是辛酉，序号57
    int y = (findIndex(yearGanZhi, sixth, 60, 0) - 57 + 60) % 60 + 1;

    int startYear = baseYear - 1;

    struct tm *bjs;
    time_t time0;
    time0 = time(NULL);
    bjs = localtime(&time0);
    int endYear = bjs->tm_year + 1900;

    OBB obb;
    MLBZ ob = {};
    std::map<std::string, std::string> yearMap;
    std::list<std::string> monthList;
    std::list<std::string> dayList;
    std::list<Date> timeList;

    while (y < endYear) {
        if (y > startYear) {
            Date date = {y, 1, 1, 0, 0, 0.00};
            yearMap = getJqMap(date, 15);
            for (std::map<std::string, std::string>::iterator it = yearMap.begin(); it != yearMap.end(); ++it) {
                time_t tt = string_to_time_t(it->first);
                Date datetmp = timeToStruct(tt);
                datetmp = getDateAfter(datetmp, {0, 0, 0, 0, 0, 10.0});//往后延10s
                obb.mingLiBaZi(toJD(datetmp) + (-8.0) / 24 - J2000, jw.J / radd, ob); //八字计算
                if ((ob.bz_jn == yearGanZhi) && (ob.bz_jy == monthGanZhi)) {
                    monthList.push_back(it->first);
                }
            }
        }
        y += 60;
    }

    for (const auto &month: monthList) {
        time_t tt = string_to_time_t(month);
        Date datetmp = timeToStruct(tt);
        datetmp = getDateAfter(datetmp, {0, 0, 0, 0, 0, 10.0});//往后延10s
        while (1) {
            datetmp = getDateAfter(datetmp, {0, 0, 1, 0, 0, 0.0});//往后延1day
            obb.mingLiBaZi(toJD(datetmp) + (-8.0) / 24 - J2000, jw.J / radd, ob); //八字计算
            if ((ob.bz_jn == yearGanZhi) && (ob.bz_jy == monthGanZhi)) {
                if (ob.bz_jr == dayGanZhi) {
                    dayList.push_back(DD2str(datetmp));
                }
            } else {
                break;
            }
        }
    }

    for (const auto &day: dayList) {
        time_t tt = string_to_time_t(day);
        Date datetmp = timeToStruct(tt);
        datetmp = getDateAfter(datetmp, {0, 0, 0, 0, 0, 10.0});//往后延10s
        obb.mingLiBaZi(toJD(datetmp) + (-8.0) / 24 - J2000, jw.J / radd, ob); //八字计算

        if ((ob.bz_jn == yearGanZhi) && (ob.bz_jy == monthGanZhi) && (ob.bz_jr == dayGanZhi)) {
            std::vector<std::string> elements;
            std::istringstream iss(ob.bz_JS);
            std::string token;

            // 使用空格作为分隔符分割字符串
            while (iss >> token) {
                elements.push_back(token);
            }

            for (size_t i = 0; i < elements.size(); ++i) {
                if (timeGanZhi == elements[i]) {
                    Date date1;
                    if (i == 0) {
                        date1 = getDateAfter(datetmp, {0, 0, -1, 0, 0, 0.0});
                    } else {
                        date1 = datetmp;
                    }
                    date1.h = (i * 2 - 1 + 24) % 24;
                    date1.m = 0;
                    date1.s = 0.00;
                    std::cout << "DD2str(date1)" << DD2str(date1) << elements[i] << std::endl;
                    timeList.push_back(date1);
                }
            }
        }
    }
    return timeList;
}


std::map<std::string, std::string> Triad::getJqMap(Date JD, int idx) {
    std::map<std::string, std::string> myMap;
    JD.M--;
    if (JD.M == 0) {
        JD.M = 12;
        JD.Y--;
    } else {
        JD.M--;
    }
    for (int i = 0; i < idx; i++) {
        //日历物件初始化
        int D, xn;
        int Bd0 = int2(toJD(JD)) - J2000;    //公历月首,中午
        JD.M++;
        if (JD.M > 12)
            JD.Y++, JD.M = 1;
        int Bdn = int2(toJD(JD)) - J2000 - Bd0;    //本月天数(公历)

        //以下是月相与节气的处理
        double d, jd2 = Bd0 + dt_T(Bd0) - 8 / 24.0;
        //节气查找
        double w = S_aLon(jd2 / 36525, 3);
        w = int2((w - 0.13) / pi2 * 24) * pi2 / 24;
        do {
            d = OBB::qi_accurate(w);
            D = int2(d + 0.5);
            xn = int2(w / pi2 * 24 + 24000006.01) % 24;
            w += pi2 / 24.0;
            if (D >= Bd0 + Bdn)
                break;
            if (D < Bd0)
                continue;
            if (xn % 2 == 0) continue;
            myMap.insert(std::make_pair(JD2str(d + J2000), str_jqmc[xn]));
        } while (D + 12 < Bd0 + Bdn);
    }
    return myMap;
}

nJieQi Triad::getxiangLinJieqi(const std::map<std::string, std::string> &jieqi_map, Date date) {
    time_t given_time = string_to_time_t(DD2str(date));
    time_t closest_time_before = 0;
    time_t closest_time_after = 0;
    std::string closest_value_before, closest_value_after;
    std::ptrdiff_t min_diff_before = std::numeric_limits<std::ptrdiff_t>::max();
    std::ptrdiff_t min_diff_after = std::numeric_limits<std::ptrdiff_t>::max();

    for (const auto &pair: jieqi_map) {
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

nJieQi Triad::getXianglinJieQi(Date JD) {
    std::map<std::string, std::string> jieqiMap = getJqMap(JD);
    return getxiangLinJieqi(jieqiMap, JD);
}

//排大运
//看年支 阳男阴女顺排，阴男阳女逆排
//阳支：子 寅 辰 午 申 戌
//阴支：丑 卯 巳 未 酉 亥
//三天一岁、一天四个月、一个时辰10天；
Date Triad::calcDaYun(const std::string sex, const std::string nianzhi, time_t Solartime, const nJieQi result, Date &diffs) {
    const std::set<std::string> yangDiZhi = {"子", "寅", "辰", "午", "申", "戌"};
    const std::set<std::string> yinDiZhi = {"丑", "卯", "巳", "未", "酉", "亥"};

    auto it1 = std::find(yangDiZhi.begin(), yangDiZhi.end(), nianzhi);
    bool foundInFirst1 = (it1 != yangDiZhi.end());

    auto it2 = std::find(yinDiZhi.begin(), yinDiZhi.end(), nianzhi);
    bool foundInFirst2 = (it2 != yinDiZhi.end());

    //阳男阴女，顺排
    if ((sex == "0" && foundInFirst1 == true) || (sex == "1" && foundInFirst2 == true))
        diffs = convFormatDy(result.aft_jqsj - Solartime);

    //阴男阳女，逆排
    if ((sex == "0" && foundInFirst2 == true) || (sex == "1" && foundInFirst1 == true))
        diffs = convFormatDy(Solartime - result.pre_jqsj);

    return getDateAfter(timeToStruct(Solartime), diffs);
}

//返回指定年的农历月信息
std::list<LN_MONTH> Triad::getLunarDate(int Year)
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