#ifndef DIZHI_
#define DIZHI_
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm> 
#include "tiangan.hpp"
#include "wuxing.hpp"

static const std::unordered_map<std::string, std::string> dizhiBenqiMap = {
    {"子", "癸"}, {"丑", "己"},
    {"寅", "甲"}, {"卯", "乙"},
    {"辰", "戊"}, {"巳", "丙"},
    {"午", "丁"}, {"未", "己"},
    {"申", "庚"}, {"酉", "辛"},
    {"戌", "戊"}, {"亥", "壬"}
};

static const std::unordered_map<std::string, std::string> dizhiZhongqiMap = {
    {"丑", "癸"}, {"寅", "丙"},
    {"辰", "乙"}, {"巳", "戊"},
    {"午", "己"}, {"未", "丁"},
    {"申", "壬"}, {"戌", "辛"}, 
    {"亥", "甲"}
};

static const std::unordered_map<std::string, std::string> dizhiYuqiMap = {
    {"丑", "辛"}, {"寅", "戊"},
    {"辰", "癸"}, {"巳", "庚"},
    {"未", "乙"}, {"申", "戊"}, 
    {"戌", "丁"}
};    

class Dizhi {
private:
	std::string br;
    std::string benqi;
	std::string zhongqi;
	std::string yuqi;

    Wuxing bqAttr;
    Wuxing zqAttr;
    Wuxing yqAttr;

    // 私有成员函数，用于校验element的有效性
    bool isValidElement(const std::string& br) {
        // 定义一个包含所有有效元素的集合
        static const std::unordered_set<std::string> validElements = {
            "子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"
        };
        // 检查elem是否为有效元素之一
        return validElements.find(br) != validElements.end();
    }

    // 私有成员函数，用于设置地支的五行中气
    void setBenqi(const std::string& br) {
        auto it = dizhiBenqiMap.find(br);
        if (it != dizhiBenqiMap.end()) {
            benqi = it->second;
            bqAttr = Tiangan(it->second).getWuxing();
        } else{
            benqi = "";
            bqAttr = Wuxing();
        }
    }

    // 私有成员函数，用于设置地支的五行中气
    void setZhongqi(const std::string& br) {
        auto it = dizhiZhongqiMap.find(br);
        if (it != dizhiZhongqiMap.end()) {
            zhongqi = it->second;
            zqAttr = Tiangan(it->second).getWuxing();
        } else{
            zhongqi = "";
            zqAttr = Wuxing();
        }
    }

    // 私有成员函数，用于设置地支的五行余气
    void setYuqi(const std::string& br) {
        auto it = dizhiYuqiMap.find(br);
        if (it != dizhiYuqiMap.end()) {
            yuqi = it->second;
            yqAttr = Tiangan(it->second).getWuxing();
        }else{
            yuqi = "";
            yqAttr = Wuxing();
        }
    }

public:
    Dizhi(const std::string& br) {
        if (!isValidElement(br)) {
            throw std::invalid_argument("Invalid element for Dizhi.");
        }
        this->br = br;
        setBenqi(this->br);
        setZhongqi(this->br);
        setYuqi(this->br);
    }

    std::string getBenqi() const {
        return benqi;
    }

    Wuxing getBenqiAttr() const {
        return bqAttr;
    }

    std::string getZhongqi() const {
        return zhongqi;
    }

    Wuxing getZhongqiAttr() const {
        return zqAttr;
    }

    std::string getYuqi() const {
        return yuqi;
    }

    Wuxing getYuqiAttr() const {
        return yqAttr;
    }

    std::string getBr() const {
        return br;
    }

    bool operator==(const Dizhi& other) const {
        return br == other.br;
    }

    std::string compB(const Wuxing& other) const {
        return getBenqiAttr().compareWith(other);
    }

    std::string compZ(const Wuxing& other) const {
        return getZhongqiAttr().compareWith(other);
    }

    std::string compY(const Wuxing& other) const {
        return getYuqiAttr().compareWith(other);
    }

    // 六合
    static bool isLiuHe(const Dizhi& d1, const Dizhi& d2) {
        if(d1 == d2) return false;
        static const std::unordered_map<std::string, std::string> liuHe = {
            // 六合关系映射
            {"子", "丑"}, {"丑", "子"}, {"寅", "亥"}, {"亥", "寅"},
            {"卯", "戌"}, {"戌", "卯"}, {"辰", "酉"}, {"酉", "辰"},
            {"巳", "申"}, {"申", "巳"}, {"午", "未"}, {"未", "午"}
        };
        return liuHe.find(d1.br) != liuHe.end() && liuHe.at(d1.br) == d2.br;
    }

    //三合
    static bool isSanHe(const Dizhi& d1, const Dizhi& d2, const Dizhi& d3, std::string &wuxing) {
        if( d1 == d2 || d2 == d3 || d1 == d3 ){
            return false;
        }
        static const std::unordered_map<std::string, std::string> sanHeBureaus = {
            {"寅", "火"}, {"午", "火"}, {"戌", "火"},
            {"申", "水"}, {"子", "水"}, {"辰", "水"},
            {"巳", "金"}, {"酉", "金"}, {"丑", "金"},
            {"亥", "木"}, {"卯", "木"}, {"未", "木"}
        };

        // 首先检查三个地支是否都在sanHeBureaus中
        auto it1 = sanHeBureaus.find(d1.br);
        auto it2 = sanHeBureaus.find(d2.br);
        auto it3 = sanHeBureaus.find(d3.br);
        if (it1 == sanHeBureaus.end() || it2 == sanHeBureaus.end() || it3 == sanHeBureaus.end()) {
            return false;
        }

        // 检查三个地支是否属于同一个局
        wuxing = it1->second;
        return it1->second == it2->second && it2->second == it3->second;
    }

    // 三会的判断函数
    static bool isSanHui(const Dizhi& d1, const Dizhi& d2, const Dizhi& d3, std::string& wuxing) {
        if( d1 == d2 || d2 == d3 || d1 == d3 ){
            return false;
        }
        static const std::unordered_map<std::string, std::string> sanHuiBureaus = {
            {"寅", "木"}, {"卯", "木"}, {"辰", "木"},
            {"巳", "火"}, {"午", "火"}, {"未", "火"},
            {"申", "金"}, {"酉", "金"}, {"戌", "金"},
            {"亥", "水"}, {"子", "水"}, {"丑", "水"}
        };

        // 首先检查三个地支是否都在sanHuiBureaus中
        auto it1 = sanHuiBureaus.find(d1.br);
        auto it2 = sanHuiBureaus.find(d2.br);
        auto it3 = sanHuiBureaus.find(d3.br);
        if (it1 == sanHuiBureaus.end() || it2 == sanHuiBureaus.end() || it3 == sanHuiBureaus.end()) {
            return false;
        }

        // 检查三个地支是否属于同一个局
        wuxing = it1->second;
        return it1->second == it2->second && it2->second == it3->second;
    }

    // 相刑的判断函数
    static bool isXing(const Dizhi& d1, const Dizhi& d2, const Dizhi& d3) {
        // 定义相刑的组合
        static const std::unordered_map<std::string, std::string> xingCombinations = {
            {"子卯", "相刑"}, {"寅巳申", "相刑"}, {"丑戌未", "相刑"},
            {"辰辰", "相刑"}, {"午午", "相刑"}, {"酉酉", "相刑"}, {"亥亥", "相刑"},
        };

        // 将三个地支的benqi值存入数组并排序
        std::string brs[3] = {d1.br, d2.br, d3.br};
        std::sort(brs, brs + 3);

        // 构造排序后的地支组合字符串
        std::string combination = brs[0] + brs[1] + brs[2];

        // 检查组合是否在相刑的映射中
        auto it = xingCombinations.find(combination);
        if (it != xingCombinations.end()) {
            return true; // 构成相刑
        }

        // 自刑的判断，单个地支重复三次
        bool isSelfXing = (brs[0] == brs[1] && brs[1] == brs[2]);
        if (isSelfXing) {
            return xingCombinations.at(brs[0] + brs[0] + brs[0]) == "相刑";
        }
        return false; // 不构成相刑
    }

    // 六冲的判断函数
    static bool isSixChong(const Dizhi& d1, const Dizhi& d2) {
        // 定义六冲的组合
        static const std::unordered_map<std::string, std::string> sixChongCombinations = {
            {"子","午"},{"午","子"}, {"丑","未"},{"未","丑"}, {"寅","申"},{"申","寅"},
            {"卯","酉"},{"酉","卯"}, {"辰","戌"},{"戌","辰"}, {"巳","亥"},{"亥","巳"}
        };
        
        // 检查两个地支是否构成六破关系
        return sixChongCombinations.find(d1.br) != sixChongCombinations.end() && sixChongCombinations.at(d1.br) == d2.br;
    }

    // 六破的判断函数
    static bool isLiuPo(const Dizhi& d1, const Dizhi& d2) {
        // 定义六破关系映射
        static const std::unordered_map<std::string, std::string> liuPo = {
            // 六破关系映射
            {"子", "酉"}, {"酉", "子"}, {"寅", "亥"}, {"亥", "寅"}, {"卯", "午"}, {"午", "卯"},
            {"辰", "丑"}, {"丑", "辰"}, {"巳", "申"}, {"申", "巳"}, {"未", "戌"}, {"戌", "未"}
        };

        // 检查两个地支是否构成六破关系
        return liuPo.find(d1.br) != liuPo.end() && liuPo.at(d1.br) == d2.br;
    }

    // 六害的判断函数
    static bool isSixHai(const Dizhi& d1, const Dizhi& d2) {
        static const std::unordered_map<std::string, std::string> sixHai = {
            // 六害关系映射
            {"子", "未"}, {"未", "子"}, {"丑", "午"}, {"午", "丑"}, {"寅", "巳"}, {"巳", "寅"},
            {"申", "亥"}, {"亥", "申"}, {"卯", "辰"}, {"辰", "卯"}, {"酉", "戌"}, {"戌", "酉"}
        };
        // 检查两个地支是否构成六害关系
        return sixHai.find(d1.br) != sixHai.end() && sixHai.at(d1.br) == d2.br;
    }

    // 用于输出地支之间的关系
    static std::string getRelationship(const Dizhi& d1, const Dizhi& d2, const Dizhi& d3, std::string &wuxing) {
        if (isLiuHe(d1, d2)) {
            return "六合";
        } else if (isSanHe(d1, d2, d3, wuxing)) {
            return "三合";
        } else if (isSanHui(d1, d2, d3, wuxing)) {
            return "三会";
        } else if (isXing(d1, d2, d3)) {
            return "三刑";
        } else if (isSixChong(d1, d2)) {
            return "六冲";
        } else if (isLiuPo(d1, d2)) {
            return "六破";
        } else if (isSixHai(d1, d2)) {
            return "六害";
        }
        return "无特定关系";
    }

};
#endif

//int main() {
//    try {
//        // 创建地支实例
//        Dizhi dizhi1("子");
//        Dizhi dizhi2("丑");
//        Dizhi dizhi3("寅");
//        Dizhi dizhi4("卯");
//        Dizhi dizhi5("辰");
//        Dizhi dizhi6("巳");
//
//        // 测试地支的构造和属性
//        std::cout << "地支 本气: " << dizhi3.getBenqi()
//         << " 中气: " << dizhi3.getZhongqi()
//         << " 余气: " << dizhi3.getYuqi() << std::endl;
//
//
//        // 测试六合
//        std::cout << "地支 '" << dizhi1.getBr() << "' 和地支 '" << dizhi2.getBr()
//            << "' 是否六合: " << (Dizhi::isLiuHe(dizhi1, dizhi2) ? "是" : "否") << std::endl;
//
//        // 测试三合
//        std::string wuxing;
//        if (Dizhi::isSanHe(dizhi3, dizhi4, dizhi5, wuxing)) {
//            std::cout << "地支 '" << dizhi3.getBr() << "', '" << dizhi4.getBr()
//                << "' 和地支 '" << dizhi5.getBr() << "' 三合, 五行: " << wuxing << std::endl;
//        }
//
//        // 测试三会
//        if (Dizhi::isSanHui(dizhi3, dizhi4, dizhi5, wuxing)) {
//            std::cout << "地支 '" << dizhi3.getBr() << "', '" << dizhi4.getBr()
//                << "' 和地支 '" << dizhi5.getBr() << "' 三会, 五行: " << wuxing << std::endl;
//        }
//
//        // 测试相刑
//        Dizhi dizhi7("午");
//        if (Dizhi::isXing(dizhi1, dizhi2, dizhi7)) {
//            std::cout << "地支 '" << dizhi1.getBr() << "', '" << dizhi2.getBr()
//                << "' 和地支 '" << dizhi7.getBr() << "' 相刑" << std::endl;
//        }
//
//        // 测试六冲
//        std::cout << "地支 '" << dizhi1.getBr() << "' 和地支 '" << dizhi7.getBr()
//            << "' 是否六冲: " << (Dizhi::isSixChong(dizhi1, dizhi7) ? "是" : "否") << std::endl;
//
//        // 测试六破
//        std::cout << "地支 '" << dizhi1.getBr() << "' 和地支 '" << dizhi2.getBr()
//            << "' 是否六破: " << (Dizhi::isLiuPo(dizhi1, dizhi2) ? "是" : "否") << std::endl;
//
//        // 测试六害
//        std::cout << "地支 '" << dizhi1.getBr() << "' 和地支 '" << dizhi2.getBr()
//            << "' 是否六害: " << (Dizhi::isSixHai(dizhi1, dizhi2) ? "是" : "否") << std::endl;
//
//        // 测试地支之间的关系
//        std::cout << "地支 '" << dizhi1.getBr() << "', '" << dizhi2.getBr()
//            << "' 和 '" << dizhi3.getBr() << "' 之间的关系: "
//            << Dizhi::getRelationship(dizhi1, dizhi2, dizhi3, wuxing) << std::endl;
//
//    } catch (const std::invalid_argument& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//
//    return 0;
//}
//

