#include "../mylib/tool.h"
#include "../mylib/math_patch.h"
#include "eph0.h"
#include "eph.h"
#include "eph_msc.h"

void MSC::calc(double T, double L, double fa, double high)
{								//sun_moon类的成员函数。参数：T是力学时,站点经纬L,fa,海拔high(千米)
	//基本参数计算
	this->T = T, this->L = L, this->fa = fa;
	this->dt = dt_T(T);			//TD-UT
	this->jd = T - this->dt;	//UT
	T /= 36525.0;
	mystl::array2 zd = nutation2(T);
	this->dL = zd[0];			//黄经章
	this->dE = zd[1];			//交角章动
	this->E = hcjj(T) + this->dE;	//真黄赤交角
	this->gst = pGST(this->jd, this->dt) + this->dL * cos(this->E);	//真恒星时(不考虑非多项式部分)
	mystl::array3 z;

	//=======月亮========
	//月亮黄道坐标
	z = m_coord(T, -1, -1, -1);	//月球坐标
	z[0] = rad2mrad(z[0] + gxc_moonLon(T) + this->dL);
	z[1] += gxc_moonLat(T);		//补上月球光行差及章动
	this->mHJ = z[0];
	this->mHW = z[1];
	this->mR = z[2];			//月球视黄经,视黄纬,地月质心距

	//月球赤道坐标
	z = llrConv(z, E);	//转为赤道坐标
	this->mCJ = z[0];
	this->mCW = z[1];			//月球视赤经,月球赤纬

	//月亮时角计算
	this->mShiJ = rad2mrad(this->gst + L - z[0]);	//得到此刻天体时角
	if (this->mShiJ > _pi)
		this->mShiJ -= pi2;

	//修正了视差的赤道坐标
	z = parallax(z, this->mShiJ, fa, high);	//视差修正
	mCJ2 = z[0], this->mCW2 = z[1], this->mR2 = z[2];

	//月亮时角坐标
	z[0] += _pi / 2 - gst - L;	//转到相对于地平赤道分点的赤道坐标(时角坐标)

	//月亮地平坐标
	z = llrConv(z, _pi / 2 - fa);	//转到地平坐标(只改经纬度)
	z[0] = rad2mrad(_pi / 2 - z[0]);
	this->mDJ = z[0];
	this->mDW = z[1];			//方位角,高度角
	if (z[1] > 0)
		z[1] += MQC(z[1]);		//大气折射修正
	this->mPJ = z[0];
	this->mPW = z[1];			//方位角,高度角

	//=======太阳========
	//太阳黄道坐标
	z = e_coord(T, -1, -1, -1);	//地球坐标
	z[0] = rad2mrad(z[0] + _pi + gxc_sunLon(T) + this->dL);	//补上太阳光行差及章动
	z[1] = -z[1] + gxc_sunLat(T);	//z数组为太阳地心黄道视坐标
	this->sHJ = z[0];
	this->sHW = z[1];
	this->sR = z[2];			//太阳视黄经,视黄纬,日地质心距

	//太阳赤道坐标
	z = llrConv(z, E);	//转为赤道坐标
	this->sCJ = z[0];
	this->sCW = z[1];			//太阳视赤经,视赤纬

	//太阳时角计算
	sShiJ = rad2mrad(this->gst + L - z[0]);	//得到此刻天体时角
	if (this->sShiJ > _pi)
		this->sShiJ -= pi2;

	//修正了视差的赤道坐标
	z = parallax(z, this->sShiJ, fa, high);	//视差修正
	this->sCJ2 = z[0], this->sCW2 = z[1], this->sR2 = z[2];

	//太阳时角坐标
	z[0] += _pi / 2 - this->gst - L;	//转到相对于地平赤道分点的赤道坐标

	//太阳地平坐标
	z = llrConv(z, _pi / 2 - fa);
	z[0] = rad2mrad(_pi / 2 - z[0]);
	//z[1] -= 8.794/rad/z[2]*cos(z[1]); //直接在地平坐标中视差修正(这里把地球看为球形,精度比parallax()稍差一些)
	this->sDJ = z[0];
	this->sDW = z[1];			//方位角,高度角

	if (z[1] > 0)
		z[1] += MQC(z[1]);		//大气折射修正
	this->sPJ = z[0];
	this->sPW = z[1];			//方位角,高度角

	//=======其它========
	//时差计算
	double t = T / 10, t2 = t * t, t3 = t2 * t, t4 = t3 * t, t5 = t4 * t;
	double Lon = (1753470142 + 6283319653318 * t + 529674 * t2 + 432 * t3 - 1124 * t4 - 9 * t5) / 1000000000 + _pi - 20.5 / rad;	//修正了光行差的太阳平黄经
	Lon = rad2mrad(Lon - (this->sCJ - this->dL * cos(this->E)));	//(修正了光行差的平黄经)-(不含dL*cos(E)的视赤经)
	if (Lon > _pi)
		Lon -= pi2;				//得到时差,单位是弧度
	this->sc = Lon / pi2;		//时差(单位:日)

	//真太阳与平太阳
	this->pty = this->jd + L / pi2;	//平太阳时
	this->zty = this->jd + L / pi2 + this->sc;	//真太阳时

	//视半径
	// this->mRad = moonRad(this->mR,this->mDW);  //月亮视半径(角秒)
	this->mRad = cs_sMoon / this->mR2;	//月亮视半径(角秒)
	this->sRad = 959.63 / this->sR2;	//太阳视半径(角秒)
	this->e_mRad = cs_sMoon / this->mR;	//月亮地心视半径(角秒)
	this->eShadow = (cs_rEarA / this->mR * rad - (959.63 - 8.794) / this->sR) * 51 / 50;	//地本影在月球向径处的半径(角秒),式中51/50是大气厚度补偿
	this->eShadow2 = (cs_rEarA / this->mR * rad + (959.63 + 8.794) / this->sR) * 51 / 50;	//地半影在月球向径处的半径(角秒),式中51/50是大气厚度补偿
	this->mIll = moonIll(T);	//月亮被照面比例

	//中心食计算
	if (fabs(rad2rrad(this->mCJ - this->sCJ)) < 50.0 / 180.0 * _pi)
	{
		COORDP pp = lineEar({ this->mCJ, this->mCW, this->mR }
							, { this->sCJ, this->sCW, this->sR * cs_AU }
							, this->gst);
		this->zx_J = pp.J;
		this->zx_W = pp.W;		//无解返回值是100
	}
	else
		this->zx_J = this->zx_W = 100;
}

mystl::string MSC::toStr(bool fs)
{
	mystl::string s;
	s = "-------------------------------------------\n";
	s = s + "平太阳 " + timeStr(this->pty) + " 真太阳 " + timeStr(this->zty) + "\n";
	s = s + "时差 " + m2fm(this->sc * 86400, 2, 1) + " 月亮被照亮 " + to_str(this->mIll * 100, 2) + "% ";
	s = s + "\n";

	s = s + "-------------------------------------------\n表一       月亮            太阳\n";
	s = s + "视黄经 " + rad2str(this->mHJ, 0) + "  " + rad2str(this->sHJ, 0) + "\n";
	s = s + "视黄纬 " + rad2str(this->mHW, 0) + "  " + rad2str(this->sHW, 0) + "\n";
	s = s + "视赤经 " + rad2str(this->mCJ, 1) + "  " + rad2str(this->sCJ, 1) + "\n";
	s = s + "视赤纬 " + rad2str(this->mCW, 0) + "  " + rad2str(this->sCW, 0) + "\n";
	s = s + "距离    " + to_str(this->mR, 2) + "千米    " + to_str(this->sR, 8) + "AU" + "\n";

	s = s + "-------------------------------------------\n表二       月亮            太阳\n";
	s = s + "方位角 " + rad2str(this->mPJ, 0) + "  " + rad2str(this->sPJ, 0) + "\n";
	s = s + "高度角 " + rad2str(this->mPW, 0) + "  " + rad2str(this->sPW, 0) + "\n";
	s = s + "时角   " + rad2str(this->mShiJ, 0) + "  " + rad2str(this->sShiJ, 0) + "\n";
	s = s + "视半径   " + m2fm(this->mRad, 2, 0) + "       " + m2fm(this->sRad, 2, 0) + " (观测点)\n";

	if (fs)
	{
		s = s + "-------------------------------------------\n";
		s = s + "力学时" + JD2str(this->T + J2000);
		s = s + " ΔT=" + to_str(this->dt * 86400, 1) + "秒\n";
		s = s + "黄经章 " + to_str(this->dL / pi2 * 360 * 3600, 2) + "\" ";
		s = s + "交角章 " + to_str(this->dE / pi2 * 360 * 3600, 2) + "\" ";
		s = s + "ε=" + rad2str(this->E, 0) + "\n";
		s = s + "-------------------------------------------\n";

	}
	return s;
}