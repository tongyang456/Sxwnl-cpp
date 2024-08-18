#ifndef TIANGAN_
#define TIANGAN_
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include "wuxing.hpp"

static const std::unordered_map<std::string, std::string> tianganWuxingMap = {
	{"甲", "阳木"}, {"乙", "阴木"},
	{"丙", "阳火"}, {"丁", "阴火"},
	{"戊", "阳土"}, {"己", "阴土"},
	{"庚", "阳金"}, {"辛", "阴金"},
	{"壬", "阳水"}, {"癸", "阴水"},
};

class Tiangan {
private:
    std::string element;
    Wuxing wuxingAttribute; // 每个天干元素对应的五行属性

    // 私有成员函数，用于校验element的有效性
    bool isValidElement(const std::string& elem) {
        // 定义一个包含所有有效元素的集合
        static const std::unordered_set<std::string> validElements = {
            "甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"
        };

        // 检查elem是否为有效元素之一
        return validElements.find(elem) != validElements.end();
    }

    // 私有成员函数，用于设置天干对应的五行属性
    void setWuxingAttribute(const std::string& elem) {
        auto it = tianganWuxingMap.find(elem);
        if (it != tianganWuxingMap.end()) {
            wuxingAttribute = Wuxing(it->second); // 初始化Wuxing对象
        } else {
            throw std::invalid_argument("Invalid element for Tiangan.");
        }
    }

public:
    enum Relationship {
        NONE,
        SHENG,
        KE,
        HE
    };

    Tiangan(const std::string& elem) : element(elem), wuxingAttribute(getWuxing(elem)) {
        if (!isValidElement(elem)) {
            throw std::invalid_argument("Invalid element. It must be one of '甲, 乙, 丙, 丁, 戊, 己, 庚, 辛, 壬, 癸'.");
        }
        setWuxingAttribute(elem); // 根据天干元素设置五行属性
    }

    // 根据天干返回对应的五行属性字符串
    static std::string getWuxing(const std::string& tiangan) {
        auto it = tianganWuxingMap.find(tiangan);
        if (it != tianganWuxingMap.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Invalid Tiangan element.");
        }
    }

    // 获取天干元素对应的五行属性
    Wuxing getWuxing() const {
        return wuxingAttribute;
    }

    std::string getElement() const {
        return element;
    }

    void setElement(const std::string& elem) {
        if (!isValidElement(elem)) {
            throw std::invalid_argument("Invalid element. It must be one of '甲, 乙, 丙, 丁, 戊, 己, 庚, 辛, 壬, 癸'.");
        }
        element = elem;
    }

    std::string comp(const Wuxing& other) const {
        return getWuxing().compareWith(other);
    }

    static bool isSheng(const Tiangan& elem1, const Tiangan& elem2) {
        static const std::unordered_map<std::string, std::string> xiangSheng = {
            {"甲", "丙"}, {"乙", "丁"},
            {"丙", "戊"}, {"丁", "己"},
            {"戊", "庚"}, {"己", "辛"},
            {"庚", "壬"}, {"辛", "癸"},
            {"壬", "甲"}, {"癸", "乙"}
        };
        return xiangSheng.find(elem1.element) != xiangSheng.end() && xiangSheng.at(elem1.element) == elem2.element;
    }

    static bool isKe(const Tiangan& elem1, const Tiangan& elem2) {
        static const std::unordered_map<std::string, std::string> xiangKe = {
            {"甲", "戊"}, {"乙", "己"},
            {"戊", "壬"}, {"己", "癸"},
            {"壬", "丙"}, {"癸", "丁"},
            {"丙", "庚"}, {"丁", "辛"},
            {"庚", "甲"}, {"辛", "乙"},
        };
        return xiangKe.find(elem1.element) != xiangKe.end() && xiangKe.at(elem1.element) == elem2.element;
    }

    static bool isHe(const Tiangan& elem1, const Tiangan& elem2) {
        static const std::unordered_map<std::string, std::string> xiangHe = {
            {"甲", "己"}, {"己", "甲"},
            {"乙", "庚"}, {"庚", "乙"},
            {"丙", "辛"}, {"辛", "丙"},
            {"丁", "壬"}, {"壬", "丁"},
            {"戊", "癸"}, {"癸", "戊"},
        };
        return xiangHe.find(elem1.element) != xiangHe.end() && xiangHe.at(elem1.element) == elem2.element;
    }

    // 天干合化
    static std::string getHeHua(const Tiangan& elem1, const Tiangan& elem2) {
        static const std::unordered_map<std::string, std::string> heHuaRules = {
            {"甲己", "土"},{"己甲", "土"},
            {"乙庚", "金"},{"庚乙", "金"},
            {"丙辛", "水"},{"辛丙", "水"},
            {"丁壬", "木"},{"壬丁", "木"},
            {"戊癸", "火"},{"癸戊", "火"},
        };
        std::string key = elem1.getElement() + elem2.getElement();
        auto it = heHuaRules.find(key);
        if (it != heHuaRules.end()) {
            return it->second;
        }
        key = elem2.getElement() + elem1.getElement(); // 交换顺序再查找
        it = heHuaRules.find(key);
        if (it != heHuaRules.end()) {
            return it->second;
        }
        return "无合化"; // 没有合化结果
    }

    static Relationship rela(const Tiangan& elem1, const Tiangan& elem2) {
        if (isSheng(elem1, elem2)) {
            return SHENG;
        } else if (isKe(elem1, elem2)) {
            return KE;
        } else if (isHe(elem1, elem2)) {
            return HE;
        } else {
            return NONE;
        }
    }

    static std::string relationshipToString(Relationship rel) {
        switch (rel) {
            case SHENG: return "生";
            case KE:    return "克";
            case HE:    return "合";
            default:    return "无";
        }
    }
};
#endif

//int main() {
//    try {
//        Tiangan tiangan1("戊");
//        Tiangan tiangan2("甲");
//
//        Tiangan::Relationship rel = Tiangan::rela(tiangan1, tiangan2);
//        std::string relationship = Tiangan::relationshipToString(rel);
//        std::cout << tiangan1.getElement() << " 和 " << tiangan2.getElement()
//            << " 是 " << relationship << " 关系。" << std::endl;
//
//        std::string heHuaResult = Tiangan::getHeHua(tiangan1, tiangan2);
//        std::cout << tiangan1.getElement() << "和" << tiangan2.getElement()
//            << "合化结果是: " << heHuaResult << std::endl;
//	std::cout << "天干 '" << tiangan1.getElement() << "' 对应的五行属性是: " << tiangan1.getWuxing().getType() << std::endl;
//	        std::cout << "天干 '" << tiangan2.getElement() << "' 对应的五行属性是: " << tiangan2.getWuxing().getType() << std::endl;
//
//		        std::string relationship1 = tiangan1.comp(tiangan2);
//			        std::cout << tiangan1.getElement() << " 和 " << tiangan2.getElement()
//					                  << " 的十神属性关系是: " << relationship1 << "。" << std::endl;
//    } catch (const std::invalid_argument& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//    return 0;
//}

