#ifndef EPH_SHOW_H
#define EPH_SHOW_H

#include "../mylib/tool.h"
#include <string>

/*
日食时间周期定义：
  食年 346.620 eclipse_year
  沙罗 6585.32 saros
  朔望 29.5306 syzygy
*/
#define ECLPSE_YEAR 346.620
#define SAROS       6585.32
#define SYZYGY      29.5306


std::string rysCalc(Date d, bool is_utc, bool nasa_r);
std::string rs_search(int Y,int M,int n,bool fs);

// 不同周期下的日食概略推算
// fs 功能选择（function select）1
// jd0 初始儒略日
// step 步长
std::string rs2_calc(uint8_t fs,double jd0, double step = SYZYGY);

// 打印界线图
std::string rs2_jxb();

// 升降相关计算
std::string shengjiang(int y, int m, int d);
std::string shengjiang2(int y);
std::string shengjiang3(int y);
#endif