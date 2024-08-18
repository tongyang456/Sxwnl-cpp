#ifndef EPH_MSC_H
#define EPH_MSC_H

#include "../mylib/mystl/my_string.h"

//========太阳月亮计算类=============
class MSC
{
public:
	 double T;	//TD力学时
	 double L;	//地理纬度
	 double fa;	//地理经度
	 double dt;	//力学-世界时时差
	 double jd;	//UT世界时
	 double dL;	//黄经章动
	 double dE;	//黄纬章动
	 double E;	//交角章动
	 double gst;	//真恒星时
	
	 double mHJ;	//月球视黄经
	 double mHW;	//月球视黄纬
	 double mR;	//地月质心距
	 double mCJ;	//月球视赤经
	 double mCW;	//月球视赤纬
	 double mShiJ;	//月球时角
	
	 double mCJ2;	//时差修正后的赤道坐标
	 double mCW2;	
	 double mR2;
	 double mDJ;	//高度角
	 double mDW;	//方位角
	 double mPJ;	//大气折射修正后的高度角
	 double mPW;	//大气折射修正后的方位角
	
	 double sHJ;	//太阳视黄经
	 double sHW;	//太阳视黄纬
	 double sCJ;	//太阳视赤经
	 double sCW;	//太阳视赤纬
	 double sCJ2;	//时差修正后的赤道坐标
	 double sCW2;	
	 double sR2;
	 double sShiJ;	//太阳时角
		
	 double sDJ;	//高度角
	 double sDW;	//方位角
	 double sR;
	 double sPJ;	//方位角
	 double sPW;	//高度角
	 double sc;	//时差

	 double pty;	//平恒星时
	 double zty;	//真恒星时
	 double mRad;	//月亮视半径
	 double sRad;	//太阳视半径
	 double e_mRad;	//月亮地心视半径
	 double eShadow;	//地本影在月球向径处的半径(角秒)
	 double eShadow2;	//地半影在月球向径处的半径(角秒)
	 double mIll;	//月面被照亮比例
	 double zx_J;	//中心食坐标
	 double zx_W;
public:
	 void calc(double T,double L,double fa,double high);
	 mystl::string toStr(bool fs);
};
#endif
