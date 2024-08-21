#include "bazi.h"
#include "lunar_ob.h"
#include "../mylib/lat_lon_data.h"
#include "triad.h"

EightChar::EightChar(Date csdate, JINGWEI jngwei, std::string sex) {
    this->sex = sex;
    this->ob_day = Triad::riLiCalc(csdate.Y, csdate.M, csdate.D,csdate.h,csdate.m,csdate.s, jngwei.J);

    this->csjd = toJD(csdate);;
    OBB::mingLiBaZi(this->csjd + (-8.0) / 24 - J2000, jngwei.J / radd, this->csmlbz);  //出生时刻的命理八字信息
    this->csjieqi = Triad::getXianglinJieQi(this->csmlbz.date_zty);
    Date dayun = Triad::calcDaYun(sex, this->csmlbz.bz_jn.substr(3, 3),
                                  structToTime(this->csmlbz.date_zty), this->csjieqi, this->dYunyear);

    this->dyjd = toJD(dayun);
    OBB::mingLiBaZi(this->dyjd + (-8.0) / 24 - J2000, jngwei.J / radd, this->dymlbz);  //大运时刻的命理八字信息
    this->dyjieqi = Triad::getXianglinJieQi(this->dymlbz.date_zty);

    int nianzhi = findIndex(this->csmlbz.bz_jn.substr(3, 3), str_zhi, 12, 0);
    int yuezhu = findIndex(this->csmlbz.bz_jy, sixth, 60, 0);
    int shizhu = findIndex(this->csmlbz.bz_js, sixth, 60, 0);

    if (((nianzhi % 2 == 0) && (sex == "0")) || ((nianzhi % 2 == 1) && (sex == "1"))) {
        for (int i = 1; i <= 12; i++) {
            if (i <= 10) {
                //this->xiaoYu[i-1] = sixth[(shizhu + i + 60)%60];
                this->xiaoYu[i - 1] = sixth[(shizhu + 1 + 60) % 60];
            }
            this->daYun[i - 1] = sixth[(yuezhu + i + 60) % 60];
        }
    } else {
        for (int i = 1; i <= 12; i++) {
            if (i <= 10) {
                //this->xiaoYu[i-1] = sixth[(shizhu -i + 60)%60];
                this->xiaoYu[i - 1] = sixth[(shizhu - 1 + 60) % 60];
            }
            this->daYun[i - 1] = sixth[(yuezhu - i + 60) % 60];
        }
    }
    this->daYunMap = calcDayunMap();
}

std::map<std::string, std::string> EightChar::calcDayunMap() {
    std::map<std::string, std::string> DayunMaptmp;
    DayunMaptmp.insert(std::make_pair(JD2str(this->csjd), this->xiaoYu[0]));
    Triad lunar1 = Triad(this->dyjd);
    std::string bz_jn;
    for (int i = 0; i < 12; i++) {
        Date date = {lunar1.lyear() + i * 10, 2, 1, 0, 0, 0.0};
        std::map<std::string, std::string> jieqiMap = Triad::getJqMap(date, 3);
        for (const auto &pair: jieqiMap) {
            if (pair.second == "立春") {
                Date dd = timeToStruct(string_to_time_t(pair.first));
                OB_DAY ob_day = Triad::riLiCalc(dd.Y, dd.M, dd.D);
                if (ob_day.Lyear < this->ob_day.Lyear) continue;
                int offset = this->ob_day.Lyear + this->dYunyear.Y;
                if ((offset > ob_day.Lyear) || ((offset == ob_day.Lyear) && (ob_day.cur_lc < 0))) {
                    bz_jn = xiaoYu[ob_day.Lyear - this->ob_day.Lyear];
                } else {
                    bz_jn = daYun[(ob_day.Lyear - offset) / 10 % 10];
                }

                DayunMaptmp.insert(std::make_pair(pair.first, bz_jn));
                break;
            }
        }
    }
    return DayunMaptmp;
};

MLBZ EightChar::calc(Triad triad)
{
    if (triad.lyear() < this->ob_day.Lyear) {
        throw std::invalid_argument("要计算农历年不能小于出生农历年");
    }

    MLBZ ob = {};
    //OBB::mingLiBaZi(lunar.getJulianDay() + (-8.0) / 24 - J2000, jw.J / radd, ob);
    int offset = this->ob_day.Lyear + this->dYunyear.Y + 1984;
    if ((offset > triad.lyear()) || ((offset == triad.lyear()) && (triad.ob_day().cur_lc < 0))) {
        ob.bz_dy = xiaoYu[triad.lyear() - (this->ob_day.Lyear + 1984)];
    } else {
        ob.bz_dy = daYun[(triad.lyear() - offset) / 10 % 10];
    }

    ob.bz_jn = triad.ob_day().Lyear2;
    ob.bz_jy = triad.ob_day().Lmonth2;
    ob.bz_jr = triad.ob_day().Lday2;
    ob.bz_js = triad.ob_day().Ltime2;
    ob.date_zty = setFromJD(triad.jd());
    ob.bz_JS = triad.ob_day().bz_JS;
    ob.bz_zty = timeStr(triad.jd() - J2000);
    return ob;
}

/*
2寅月（始于立春）：余气：戊土占7天。中气：丙火占7天。本气：甲木占16天。
3卯月（始于惊蜇）：余气：甲木占10天。中气：无。本气：乙木占20天。
4辰月（始于清明）：余气：乙木占9天。中气：癸水占3天。本气：戊土占18天。
5巳月（始于立夏）：余气：戊土占5天。中气：庚金占9天。本气：丙火占16天。
6午月（始于芒种）：余气：丙火占10天。中气：己土占9天。本气：丁火占11天。
7未月（始于小暑）：余气：丁火占9天。中气：乙木占3天。本气：己土占18天。
8申月（始于立秋）：余气：己土占7天+戊土占3天。中气：壬水占3天。本气：庚金占17天。
9酉月（始于白露）：余气：庚金占10天。中气：无。本气：辛金占20天。
10戌月（始于寒露）：余气：辛金占9天。中气：丁火占3天。本气：戊土占18天。
11亥月（始于立冬）：余气：戊土占7天。中气：甲木占5天。本气：壬水占18天。
0子月（始于大雪）：余气：壬水占10天。中气：无。本气：癸水占20天。
1丑月（始于小雪）：余气：癸水占9天。中气：辛金占3天。本气：己土占18天
*/
std::string EightChar::calcRenYuanFenYe() {
    //出生前一个节气到出生时的天数
    Date diff2 = convFormat(structToTime(this->csmlbz.date_zty) - this->csjieqi.pre_jqsj);
    int day = diff2.D + diff2.h / 24 + diff2.m / 1440;
    int yueZhiIdx = findIndex(this->csmlbz.bz_jy.substr(3, 3), str_zhi, 12, 0);
    switch (yueZhiIdx) {
        case 0:
            return (day > 10) ? "癸" : "壬";
        case 1:
            return (day > 12) ? "己" : (day > 9) ? "辛" : "癸";
        case 2:
            return (day > 14) ? "甲" : (day > 7) ? "丙" : "戊";
        case 3:
            return (day > 10) ? "乙" : "甲";
        case 4:
            return (day > 12) ? "戊" : (day > 9) ? "癸" : "乙";
        case 5:
            return (day > 14) ? "丙" : (day > 5) ? "庚" : "戊";
        case 6:
            return (day > 19) ? "丁" : (day > 10) ? "己" : "丙";
        case 7:
            return (day > 12) ? "己" : (day > 9) ? "乙" : "丁";
        case 8:
            return (day > 13) ? "庚" : (day > 10) ? "壬" : "戊";
        case 9:
            return (day > 10) ? "辛" : "庚";
        case 10:
            return (day > 12) ? "戊" : (day > 9) ? "丁" : "辛";
        case 11:
            return (day > 12) ? "壬" : (day > 7) ? "甲" : "戊";
        default:
            return "未知";
    }
}

int EightChar::xXiuIdx(std::string str) {
    if (str == "申" || str == "子" || str == "辰") {
        return 0;
    } else if (str == "巳" || str == "酉" || str == "丑") {
        return 1;
    } else if (str == "寅" || str == "午" || str == "戌") {
        return 2;
    } else if (str == "亥" || str == "卯" || str == "未") {
        return 3;
    } else {
        return -1;
    }
}

std::string EightChar::calcXingXiu() {
    return str_xxiu[xXiuIdx(this->csmlbz.bz_jr.substr(3, 3))][(this->ob_day.week + 6) % 7];
}

std::string EightChar::calcXingXiuJX() {
    std::string xingxiu = calcXingXiu();
    return findIndex(xingxiu, str_xxjx[0], 14, 0) > 0 ? "吉" : "凶";
}

std::string EightChar::calcTaiYuan() {
    int yuegan = findIndex(this->csmlbz.bz_jy.substr(0, 3), str_gan, 10, 0);
    int yuezhi = findIndex(this->csmlbz.bz_jy.substr(3, 3), str_zhi, 12, 0);
    return std::string(str_gan[(yuegan + 1) % 10]) + std::string(str_zhi[(yuezhi + 3) % 12]);
}

std::string EightChar::calcKongWang(std::string zhu) {
    int ganIdx = findIndex(zhu.substr(0, 3), str_gan, 10, 0);
    int zhiIdx = findIndex(zhu.substr(3, 3), str_zhi, 12, 0);
    return std::string(str_zhi[(zhiIdx - ganIdx + 12 + 10) % 12]) +
           std::string(str_zhi[(zhiIdx - ganIdx + 11 + 12) % 12]);
}

std::string EightChar::calcMingGong() {
    int niangan = findIndex(this->csmlbz.bz_jn.substr(0, 3), str_gan, 10, 0);
    int yuezhi = findIndex(this->csmlbz.bz_jy.substr(3, 3), str_zhi, 12, 0);
    int shizhi = findIndex(this->csmlbz.bz_js.substr(3, 3), str_zhi, 12, 0);
    return std::string(str_gan[(2 * niangan + ((yuezhi + shizhi + 11) % 12)) % 10]) +
           std::string(str_zhi[(yuezhi + shizhi + 11) % 12]);
}

std::string EightChar::findLiuHe(std::string str) {
    int idx = findIndex(str, str_zhi, 12, 0);
    const int tmparr[12][2] = {
            {0,  1}, {1,  0}, {2,  11}, {3,  10},
            {4,  9}, {5,  8}, {6,  7}, {7,  6},
            {8,  5}, {9,  4}, {10, 3}, {11, 2}
    };
    return str_zhi[tmparr[idx][1]];
}

std::string EightChar::calcTaixi() {
    int riganIdx = findIndex(this->csmlbz.bz_jr.substr(0, 3), str_gan, 10, 0);
    return std::string(str_gan[(riganIdx + 5) % 10]) + findLiuHe(this->csmlbz.bz_jr.substr(3, 3));
}

std::string EightChar::calcShengong() {
    int nianIdx = findIndex(this->csmlbz.bz_jn.substr(0, 3), str_gan, 10, 0);
    int yuezhiIdx = findIndex(this->csmlbz.bz_jy.substr(3, 3), str_zhi, 12, 0);
    int shizhiIdx = findIndex(this->csmlbz.bz_js.substr(3, 3), str_zhi, 12, 0);
    return std::string(str_gan[(2 * nianIdx + ((yuezhiIdx + shizhiIdx + 1) % 12)) % 10]) +
           str_zhi[(yuezhiIdx + shizhiIdx + 1) % 12];
}

std::string EightChar::calcMinggua() {
    int res = (this->sex == "0") ? (100 - this->ob_day.y % 100 - 1) % 9 : (this->ob_day.y % 100 - 4 - 1) %9;
    return str_guax[res];
}

std::string EightChar::findZSheng(int strzhiIdx, int strganIdx) {
    const int zShengarr[12][10] = {
            {1,  6,  10, 9,  10, 9,  7,  0,  4,  3},
            {2,  5,  11, 8,  11, 8,  8,  11, 5,  2},
            {3,  4,  0,  7,  0,  7,  9,  10, 6,  1},
            {4,  3,  1,  6,  1,  6,  10, 9,  7,  0},
            {5,  2,  2,  5,  2,  5,  11, 8,  8,  11},
            {6,  1,  3,  4,  3,  4,  0,  7,  9,  10},
            {7,  0,  4,  3,  4,  3,  1,  6,  10, 9},
            {8,  11, 5,  2,  5,  2,  2,  5,  11, 8},
            {9,  10, 6,  1,  6,  1,  3,  4,  0,  7},
            {10, 9,  7,  0,  7,  0,  4,  3,  1,  6},
            {11, 8,  8,  11, 8,  11, 5,  2,  2,  5},
            {0,  7,  9,  10, 9,  10, 6,  1,  3,  4}
    };
    return str_zsheng[zShengarr[strzhiIdx][strganIdx]];
}


std::string EightChar::calcXingyun(std::string zhu) {
    int rigan = findIndex(this->csmlbz.bz_jr.substr(0, 3), str_gan, 10, 0);
    int zhiIdx = findIndex(zhu.substr(3, 3), str_zhi, 12, 0);
    return findZSheng(zhiIdx, rigan);
}

std::string EightChar::calcZizuo(std::string zhu) {
    int niangan = findIndex(this->csmlbz.bz_jn.substr(0, 3), str_gan, 10, 0);
    int zhiIdx = findIndex(zhu.substr(3, 3), str_zhi, 12, 0);
    return findZSheng(zhiIdx, niangan);
}

std::string EightChar::calcNayin(std::string zhu) {
    return str_nywx[findIndex(zhu, sixth, 60, 0) / 2];
}

std::string EightChar::calcHuanyun()
{
    int niangan = findIndex(this->dymlbz.bz_jn.substr(0, 3), str_gan, 10, 0);
    return std::string(str_gan[niangan]) +  str_gan[(niangan + 5) % 10];
}
