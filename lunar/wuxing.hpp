#ifndef WUXING_
#define WUXING_
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>

// 自定义哈希函数，适用于 std::pair<std::string, std::string>
struct pair_hash {
    std::size_t operator()(const std::pair<std::string, std::string>& pair) const {
        std::size_t hash = 0;
        // 使用 std::hash<std::string>{} 来分别哈希两个字符串，并组合哈希值
        hash ^= std::hash<std::string>{}(pair.first) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<std::string>{}(pair.second) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        return hash;
    }
};

// 自定义等价性比较函数，适用于 std::pair<std::string, std::string>
struct pair_equal {
    bool operator()(const std::pair<std::string, std::string>& lhs,
                    const std::pair<std::string, std::string>& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

static const std::unordered_map<std::pair<std::string, std::string>, std::string, pair_hash, pair_equal> relations = {
    {{"阳木", "阳木"}, "比肩"}, {{"阴木", "阳木"}, "劫财"}, {{"阳火", "阳木"}, "食神"}, {{"阴火", "阳木"}, "伤官"}, {{"阳土", "阳木"}, "偏财"}, 
    {{"阴土", "阳木"}, "正财"}, {{"阳金", "阳木"}, "七杀"}, {{"阴金", "阳木"}, "正官"}, {{"阳水", "阳木"}, "偏印"}, {{"阴水", "阳木"}, "正印"},

    {{"阳木", "阴木"}, "劫财"}, {{"阴木", "阴木"}, "比肩"}, {{"阳火", "阴木"}, "伤官"}, {{"阴火", "阴木"}, "食神"}, {{"阳土", "阴木"}, "正财"}, 
    {{"阴土", "阴木"}, "偏财"}, {{"阳金", "阴木"}, "正官"}, {{"阴金", "阴木"}, "七杀"}, {{"阳水", "阴木"}, "正印"}, {{"阴水", "阴木"}, "偏印"}, 

    {{"阳木", "阳火"}, "偏印"}, {{"阴木", "阳火"}, "正印"}, {{"阳火", "阳火"}, "比肩"}, {{"阴火", "阳火"}, "劫财"}, {{"阳土", "阳火"}, "食神"}, 
    {{"阴土", "阳火"}, "伤官"}, {{"阳金", "阳火"}, "偏财"}, {{"阴金", "阳火"}, "正财"}, {{"阳水", "阳火"}, "七杀"}, {{"阴水", "阳火"}, "正官"}, 

    {{"阳木", "阴火"}, "正印"}, {{"阴木", "阴火"}, "偏印"}, {{"阳火", "阴火"}, "劫财"}, {{"阴火", "阴火"}, "比肩"}, {{"阳土", "阴火"}, "伤官"}, 
    {{"阴土", "阴火"}, "食神"}, {{"阳金", "阴火"}, "正财"}, {{"阴金", "阴火"}, "偏财"}, {{"阳水", "阴火"}, "正官"}, {{"阴水", "阴火"}, "七杀"}, 

    {{"阳木", "阳土"}, "七杀"}, {{"阴木", "阳土"}, "正官"}, {{"阳火", "阳土"}, "偏印"}, {{"阴火", "阳土"}, "正印"}, {{"阳土", "阳土"}, "比肩"}, 
    {{"阴土", "阳土"}, "劫财"}, {{"阳金", "阳土"}, "食神"}, {{"阴金", "阳土"}, "伤官"}, {{"阳水", "阳土"}, "偏财"}, {{"阴水", "阳土"}, "正财"}, 

    {{"阳木", "阴土"}, "正官"}, {{"阴木", "阴土"}, "七杀"}, {{"阳火", "阴土"}, "正印"}, {{"阴火", "阴土"}, "偏印"}, {{"阳土", "阴土"}, "劫财"}, 
    {{"阴土", "阴土"}, "比肩"}, {{"阳金", "阴土"}, "伤官"}, {{"阴金", "阴土"}, "食神"}, {{"阳水", "阴土"}, "正财"}, {{"阴水", "阴土"}, "偏财"}, 

    {{"阳木", "阳金"}, "偏财"}, {{"阴木", "阳金"}, "正财"}, {{"阳火", "阳金"}, "七杀"}, {{"阴火", "阳金"}, "正官"}, {{"阳土", "阳金"}, "偏印"}, 
    {{"阴土", "阳金"}, "正印"}, {{"阳金", "阳金"}, "比肩"}, {{"阴金", "阳金"}, "劫财"}, {{"阳水", "阳金"}, "食神"}, {{"阴水", "阳金"}, "伤官"}, 

    {{"阳木", "阴金"}, "正财"}, {{"阴木", "阴金"}, "偏财"}, {{"阳火", "阴金"}, "正官"}, {{"阴火", "阴金"}, "七杀"}, {{"阳土", "阴金"}, "正印"}, 
    {{"阴土", "阴金"}, "偏印"}, {{"阳金", "阴金"}, "劫财"}, {{"阴金", "阴金"}, "比肩"}, {{"阳水", "阴金"}, "伤官"}, {{"阴水", "阴金"}, "食神"}, 

    {{"阳木", "阳水"}, "食神"}, {{"阴木", "阳水"}, "伤官"}, {{"阳火", "阳水"}, "偏财"}, {{"阴火", "阳水"}, "正财"}, {{"阳土", "阳水"}, "七杀"}, 
    {{"阴土", "阳水"}, "正官"}, {{"阳金", "阳水"}, "偏印"}, {{"阴金", "阳水"}, "正印"}, {{"阳水", "阳水"}, "比肩"}, {{"阴水", "阳水"}, "劫财"}, 

    {{"阳木", "阴水"}, "伤官"}, {{"阴木", "阴水"}, "食神"}, {{"阳火", "阴水"}, "正财"}, {{"阴火", "阴水"}, "偏财"}, {{"阳土", "阴水"}, "正官"}, 
    {{"阴土", "阴水"}, "七杀"}, {{"阳金", "阴水"}, "正印"}, {{"阴金", "阴水"}, "偏印"}, {{"阳水", "阴水"}, "劫财"}, {{"阴水", "阴水"}, "比肩"}, 
};

// 五行类
class Wuxing {
private:
    std::string type;

    // 用于校验 type 是否为有效的五行阴阳类型
    bool isValidType(const std::string& t) {
        static const std::unordered_set<std::string> validTypes = {
            "阳木", "阴木", "阳火", "阴火", "阳土", "阴土", "阳金", "阴金", "阳水", "阴水"
        };
        return validTypes.find(t) != validTypes.end();
    }

public:
    Wuxing(){}

    // 构造函数
    explicit Wuxing(const std::string& t) : type(t) {
        if (!isValidType(t)) {
            throw std::invalid_argument("未知的五行阴阳类型");
        }
    }

    // 获取元素类型
    const std::string& getType() const {
        return type;
    }

    // 比较两个元素的关系
    std::string compareWith(const Wuxing& other) const {
        auto it = relations.find({type, other.getType()});
        if (it != relations.end()) {
            return it->second;
        } else {
            return "    ";
            //return "";
        }
    }
};

// 为了输出元素名称，可以重载<<运算符
inline std::ostream& operator<<(std::ostream& os, const Wuxing& e) {
    os << e.getType();
    return os;
}
#endif

//int main() {
//    Wuxing w1("阳木");
//    Wuxing w2("阴火");
//
//    // 输出金属与木的关系
//    std::cout << w1 << w2 <<"的关系是: " << w1.compareWith(w2) << std::endl;
//
//    // 输出木与金的关系
//    std::cout << w1 << w1 <<"的关系是: " << w1.compareWith(w1) << std::endl;
//
//    return 0;
//}

