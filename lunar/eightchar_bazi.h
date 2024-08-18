#ifndef EIGHTCHAR_BAZI_H
#define EIGHTCHAR_BAZI_H

#include <list>
#include <set>
#include <vector>
#include <algorithm>
#include "../mylib/mystl/my_string.h"
#include "../mylib/mystl/vector.h"
#include "../mylib/tool.h"
#include "lunar.h"
#include <unordered_map>
#include "../mylib/lat_lon_data.h"
#include "../eph/eph0.h"
#include "lunar_bazi.h"

class EightChar
{
private:
    JINGWEI jngwei;
    std::string sex;
    double csjd;  //出生时刻儒略日数
    double dyjd;  //大运时刻儒略日数
    MLBZ csmlbz;  //出生八字
    MLBZ dymlbz;  //大运八字
    nJieQi csjieqi; //出生时刻前后节气
    nJieQi dyjieqi; //大运时刻前后节气
    Date dYunyear;  //起大运需要的年
    std::array<std::string, 13> daYun;  //大运
    std::array<std::string, 11> xiaoYu; //小运
    std::map<std::string, std::string> daYunMap;
    OB_DAY ob_day;

    int xXiuIdx(std::string str);
    std::string findLiuHe(std::string str);
    std::string findZSheng(int strzhiIdx, int strganIdx );
    std::map<std::string, std::string> calcDayunMap();

public:
    inline double getCsJd(){ return this->csjd; }
    inline double getDyJd(){ return this->dyjd; }
    inline MLBZ getCsMlbz(){ return this->csmlbz; }
    inline MLBZ getDyMlbz(){ return this->dymlbz; }
    inline nJieQi getCsJieQi(){ return this->csjieqi; }
    inline nJieQi getDyJieQi(){ return this->dyjieqi; }
    inline Date getdYunyear(){ return this->dYunyear; }
    inline std::array<std::string, 13> getDaYunArr(){ return this->daYun;}
    inline std::array<std::string, 11> getXiaoYunArr(){ return this->xiaoYu;}

    EightChar(Date csdate, JINGWEI jngwei = jw, std::string sex = "0");    //0男，1女

    //获取指定阳历日期对应的大运、流年、流月、流日、流时信息
    MLBZ calc(Lunar lunar);

    //获取指定阴历日期对应的大运、流年、流月、流日、流时信息
    MLBZ calc(Solar solar);

    inline OB_DAY getObDay() { return this->ob_day; }

    //人员司令分野
    std::string calcRenYuanFenYe();

    //星宿
    std::string calcXingXiu();

    //星宿吉凶
    std::string calcXingXiuJX();

    //胎元
    std::string calcTaiYuan();

    //空亡
    std::string calcKongWang(std::string zhu);

    //命宫
    std::string calcMingGong();

    //胎息
    std::string calcTaixi();

    //身宫
    std::string calcShengong();

    //命卦
    std::string calcMinggua();

    //星运
    std::string calcXingyun(std::string zhu);

    //自作
    std::string calcZizuo(std::string zhu);

    //纳音
    std::string calcNayin(std::string zhu);

    std::string calcHuanyun();

};

#endif
