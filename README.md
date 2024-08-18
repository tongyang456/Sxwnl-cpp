# Sxwnl-cpp
寿星万年历 八字 国学

目前已经完成基本排盘功能，基本阳历农历相互转换，真太阳时计算、交运计算、流年、大运计算、十神等功能；

运行环境：centos8

使用方法：
cd Sxwnl-cpp;
sh rebuild.sh;
cd build;
./test1

项目整体布局：
    参考开源项目sxwnl进行创作，
    lunar/lunar_bazi.cpp .hpp 农历相关信息
    lunar/solar_bazi.cpp .hpp 公历相关信息
    lunar/eightchar_bazi.cpp .hpp 八字相关信息
    wuxing.hpp、  五行、
    tiangan.hpp、  天干、
    dizhi.hpp、  地支、
    shishen.hpp 十神相关信息

完毕！
