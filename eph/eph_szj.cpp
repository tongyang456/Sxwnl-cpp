#include "eph_szj.h"
#include "eph0.h"
#include "../mylib/tool.h"
#include "../mylib/math_patch.h"
//#include "../mylib/mystl/static_array.h"
#include <array>


SZJ::SZJ(){
	this->E = 0.409092614;
}

static inline double mod2(double a,double b)
{ //临界余数(a与最近的整倍数b相差的距离)

  double c=a/b;
  c -= floor(c);
  if(c>0.5) c-=1;
  return c*b;

}

double SZJ::getH(double h, double w)
{								//h地平纬度,w赤纬,返回时角
	double c = (sin(h) - sin(this->fa) * sin(w)) / cos(this->fa) / cos(w);
	if (fabs(c) > 1)
		return M_PI;
	return acos(c);
};

void SZJ::Mcoord(double jd, double H0, SJ &r)
{								//章动同时影响恒星时和天体坐标,所以不计算章动。返回时角及赤经纬
    std::array<double, 3> z = m_coord((jd + this->dt) / 36525, 40, 30, 8);	//低精度月亮赤经纬
	z = llrConv(z, this->E);	//转为赤道坐标
	r.H = rad2rrad(pGST(jd, this->dt) + this->L - z[0]);	//得到此刻天体时角
	if (H0)
		r.H0 = this->getH(0.7275 * cs_rEar / z[2] - 34 * 60 / rad, z[1]);	//升起对应的时角
}

SJ SZJ::Mt(double jd)
{								//月亮到中升降时刻计算,传入jd含义与St()函数相同
	this->dt = dt_T(jd);
	this->E = hcjj(jd / 36525);
	jd -= mod2(0.1726222 + 0.966136808032357 * jd - 0.0366 * this->dt + this->L / pi2, 1);	//查找最靠近当日中午的月上中天,mod2的第1参数为本地时角近似值

	SJ r = {};
	double sv = pi2 * 0.966;
	r.z = r.x = r.s = r.j = r.c = r.h = jd;
	this->Mcoord(jd, 1, r);		//月亮坐标
	r.s += (-r.H0 - r.H) / sv;
	r.j += (r.H0 - r.H) / sv;
	r.z += (0 - r.H) / sv;
	r.x += (M_PI - r.H) / sv;
	this->Mcoord(r.s, 1, r);
	r.s += rad2rrad(-r.H0 - r.H) / sv;
	this->Mcoord(r.j, 1, r);
	r.j += rad2rrad(+r.H0 - r.H) / sv;
	this->Mcoord(r.z, 0, r);
	r.z += rad2rrad(0 - r.H) / sv;
	this->Mcoord(r.x, 0, r);
	r.x += rad2rrad(M_PI - r.H) / sv;
	return r;
}

void SZJ::Scoord(double jd, int xm, SJ &r)
{								//章动同时影响恒星时和天体坐标,所以不计算章动。返回时角及赤经纬
    std::array<double, 3> z = {E_Lon((jd + this->dt) / 36525, 5) + M_PI - 20.5 / rad, 0, 1};	//太阳坐标(修正了光行差)
	z = llrConv(z, this->E);	//转为赤道坐标
	r.H = rad2rrad(pGST(jd, this->dt) + this->L - z[0]);	//得到此刻天体时角

	if (xm == 10 || xm == 1)
		r.H1 = this->getH(-50 * 60 / rad, z[1]);	//地平以下50分
	if (xm == 10 || xm == 2)
		r.H2 = this->getH(-6 * 3600 / rad, z[1]);	//地平以下6度
	if (xm == 10 || xm == 3)
		r.H3 = this->getH(-12 * 3600 / rad, z[1]);	//地平以下12度
	if (xm == 10 || xm == 4)
		r.H4 = this->getH(-18 * 3600 / rad, z[1]);	//地平以下18度
}

SJ SZJ::St(double jd)
{								//太阳到中升降时刻计算,传入jd是当地中午12点时间对应的2000年首起算的格林尼治时间UT
	this->dt = dt_T(jd);
	this->E = hcjj(jd / 36525);
	jd -= mod2(jd + this->L / pi2, 1);	//查找最靠近当日中午的日上中天,mod2的第1参数为本地时角近似值

	SJ r = {};
	double sv = pi2;
	r.z = r.x = r.s = r.j = r.c = r.h = r.c2 = r.h2 = r.c3 = r.h3 = jd;
	r.sm = "";
	this->Scoord(jd, 10, r);	//太阳坐标
	r.s += (-r.H1 - r.H) / sv;	//升起
	r.j += (r.H1 - r.H) / sv;	//降落

	r.c += (-r.H2 - r.H) / sv;	//民用晨
	r.h += (r.H2 - r.H) / sv;	//民用昏
	r.c2 += (-r.H3 - r.H) / sv;	//航海晨
	r.h2 += (r.H3 - r.H) / sv;	//航海昏
	r.c3 += (-r.H4 - r.H) / sv;	//天文晨
	r.h3 += (r.H4 - r.H) / sv;	//天文昏

	r.z += (0 - r.H) / sv;		//中天
	r.x += (M_PI - r.H) / sv;	//下中天
	this->Scoord(r.s, 1, r);
	r.s += rad2rrad(-r.H1 - r.H) / sv;
	if (r.H1 == M_PI)
		r.sm += "无升起.";
	this->Scoord(r.j, 1, r);
	r.j += rad2rrad(+r.H1 - r.H) / sv;
	if (r.H1 == M_PI)
		r.sm += "无降落.";

	this->Scoord(r.c, 2, r);
	r.c += rad2rrad(-r.H2 - r.H) / sv;
	if (r.H2 == M_PI)
		r.sm += "无民用晨.";
	this->Scoord(r.h, 2, r);
	r.h += rad2rrad(+r.H2 - r.H) / sv;
	if (r.H2 == M_PI)
		r.sm += "无民用昏.";
	this->Scoord(r.c2, 3, r);
	r.c2 += rad2rrad(-r.H3 - r.H) / sv;
	if (r.H3 == M_PI)
		r.sm += "无航海晨.";
	this->Scoord(r.h2, 3, r);
	r.h2 += rad2rrad(+r.H3 - r.H) / sv;
	if (r.H3 == M_PI)
		r.sm += "无航海昏.";
	this->Scoord(r.c3, 4, r);
	r.c3 += rad2rrad(-r.H4 - r.H) / sv;
	if (r.H4 == M_PI)
		r.sm += "无天文晨.";
	this->Scoord(r.h3, 4, r);
	r.h3 += rad2rrad(+r.H4 - r.H) / sv;
	if (r.H4 == M_PI)
		r.sm += "无天文昏.";

	this->Scoord(r.z, 0, r);
	r.z += (0 - r.H) / sv;
	this->Scoord(r.x, 0, r);
	r.x += rad2rrad(M_PI - r.H) / sv;
	return r;
}

void SZJ::calcRTS(double jd, int n, double Jdl, double Wdl, double sq)
{	//多天升中降计算,jd是当地起始略日(中午时刻),sq是时区
	int i, c;
	SJ_S rr;
	SJ r;
	if (!this->rts.size())
	{
		for (i = 0; i < 31; i++)
			this->rts.push_back({});
	}
	this->L = Jdl, this->fa = Wdl, sq /= 24;	//设置站点参数
	for (i = 0; i < n; i++)
	{
		rr = this->rts[i];
		rr.Ms = rr.Mz = rr.Mj = "--:--:--";
	}
	for (i = -1; i <= n; i++)
	{
		if (i >= 0 && i < n)
		{						//太阳
			r = this->St(jd + i + sq);
			this->rts[i].s = timeStr(r.s - sq);	//升
			this->rts[i].z = timeStr(r.z - sq);	//中
			this->rts[i].j = timeStr(r.j - sq);	//降
			this->rts[i].c = timeStr(r.c - sq);	//晨
			this->rts[i].h = timeStr(r.h - sq);	//昏
			this->rts[i].ch = timeStr(r.h - r.c - 0.5);	//光照时间,timeStr()内部+0.5,所以这里补上-0.5
			this->rts[i].sj = timeStr(r.j - r.s - 0.5);	//昼长
		}
		r = this->Mt(jd + i + sq);	//月亮
		c = int2(r.s - sq + 0.5) - jd;
		if (c >= 0 && c < n)
			this->rts[c].Ms = timeStr(r.s - sq);
		c = int2(r.z - sq + 0.5) - jd;
		if (c >= 0 && c < n)
			this->rts[c].Mz = timeStr(r.z - sq);
		c = int2(r.j - sq + 0.5) - jd;
		if (c >= 0 && c < n)
			this->rts[c].Mj = timeStr(r.j - sq);
	}
}