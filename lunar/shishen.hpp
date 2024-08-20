#include <iostream>
#include <string>
#include <utility>
#include "tiangan.hpp"
#include "dizhi.hpp"

struct BASE_SHISHEN{
    std::string ns,nzb,nzz,nzy;
    std::string ys,yzb,yzz,yzy;
    std::string rs,rzb,rzz,rzy;
    std::string ss,szb,szz,szy;
};

struct LN_SHISHEN{
    std::string dys,dyzb,dyzz,dyzy;
    std::string ns,nzb,nzz,nzy;
    std::string ys,yzb,yzz,yzy;
    std::string rs,rzb,rzz,rzy;
    std::string ss,szb,szz,szy;
};

// 十神类
class ShiShen {
private:
    std::string sex;
    MLBZ ob;
    BASE_SHISHEN baSs;
    Tiangan rg;
    
public:
    ShiShen(MLBZ csbz, std::string sex) : sex(sex), ob(csbz), rg(ob.bz_jr.substr(0, 3)){
        Tiangan ng(ob.bz_jn.substr(0, 3));
        Tiangan yg(ob.bz_jy.substr(0, 3));
        //Tiangan rg(ob.bz_jr.substr(0, 3));
        Tiangan sg(ob.bz_js.substr(0, 3));

        Dizhi nz(ob.bz_jn.substr(3, 3));
        Dizhi yz(ob.bz_jy.substr(3, 3));
        Dizhi rz(ob.bz_jr.substr(3, 3));
        Dizhi sz(ob.bz_js.substr(3, 3));

        //天干
        baSs.ns = ng.comp(rg.getWuxing());
        baSs.ys = yg.comp(rg.getWuxing());
        baSs.rs = sex == "0" ? "元男" : "元女";
        baSs.ss = sg.comp(rg.getWuxing());

        //地支
        baSs.nzb = nz.compB(rg.getWuxing());
        baSs.nzz = nz.compZ(rg.getWuxing());
        baSs.nzy = nz.compY(rg.getWuxing());

        baSs.yzb = yz.compB(rg.getWuxing());
        baSs.yzz = yz.compZ(rg.getWuxing());
        baSs.yzy = yz.compY(rg.getWuxing());

        baSs.rzb = rz.compB(rg.getWuxing());
        baSs.rzz = rz.compZ(rg.getWuxing());
        baSs.rzy = rz.compY(rg.getWuxing());

        baSs.szb = sz.compB(rg.getWuxing());
        baSs.szz = sz.compZ(rg.getWuxing());
        baSs.szy = sz.compY(rg.getWuxing());
    }

    LN_SHISHEN calcLiuNian(MLBZ lnbz){
        LN_SHISHEN liuSs;
        Tiangan dyg1(lnbz.bz_dy.substr(0, 3));
        Tiangan ng1(lnbz.bz_jn.substr(0, 3));
        Tiangan yg1(lnbz.bz_jy.substr(0, 3));
        Tiangan rg1(lnbz.bz_jr.substr(0, 3));
        Tiangan sg1(lnbz.bz_js.substr(0, 3));

        Dizhi dyz1(lnbz.bz_dy.substr(3, 3));
        Dizhi nz1(lnbz.bz_jn.substr(3, 3));
        Dizhi yz1(lnbz.bz_jy.substr(3, 3));
        Dizhi rz1(lnbz.bz_jr.substr(3, 3));
        Dizhi sz1(lnbz.bz_js.substr(3, 3));

        liuSs.dys = dyg1.comp(rg.getWuxing());
        liuSs.ns = ng1.comp(rg.getWuxing());
        liuSs.ys = yg1.comp(rg.getWuxing());
        liuSs.rs = rg1.comp(rg.getWuxing());
        liuSs.ss = sg1.comp(rg.getWuxing());
        liuSs.dyzb = dyz1.compB(rg.getWuxing());
        liuSs.dyzz = dyz1.compZ(rg.getWuxing());
        liuSs.dyzy = dyz1.compY(rg.getWuxing());
        liuSs.nzb = nz1.compB(rg.getWuxing());
        liuSs.nzz = nz1.compZ(rg.getWuxing());
        liuSs.nzy = nz1.compY(rg.getWuxing());
        liuSs.yzb = yz1.compB(rg.getWuxing());
        liuSs.yzz = yz1.compZ(rg.getWuxing());
        liuSs.yzy = yz1.compY(rg.getWuxing());
        liuSs.rzb = rz1.compB(rg.getWuxing());
        liuSs.rzz = rz1.compZ(rg.getWuxing());
        liuSs.rzy = rz1.compY(rg.getWuxing());
        liuSs.szb = sz1.compB(rg.getWuxing());
        liuSs.szz = sz1.compZ(rg.getWuxing());
        liuSs.szy = sz1.compY(rg.getWuxing());
        return liuSs;
    }

    std::string toString(){
        return std::string(
            "    年柱 月柱 日柱 时柱 \n"
            "主星 " + baSs.ns +" " + baSs.ys +" "+ baSs.rs +" "+ baSs.ss +
            "\n本气 " + baSs.nzb +" "+ baSs.yzb +" "+ baSs.rzb +" "+ baSs.szb +
            "\n中气 " + baSs.nzz +" "+ baSs.yzz +" "+ baSs.rzz +" "+ baSs.szz +
            "\n余气 " + baSs.nzy +" "+ baSs.yzy +" "+ baSs.rzy +" "+ baSs.szy
            );
    }

    std::string toString(LN_SHISHEN liuSs) {
        return std::string(
            "     流时 流日 流月 流年 大运\n"
            "主星 " + liuSs.ss +" "+ liuSs.rs +" "+ liuSs.ys +" "+ liuSs.ns +" "+ liuSs.dys +
            "\n本气 " + liuSs.szb +" "+ liuSs.rzb +" "+ liuSs.yzb +" "+ liuSs.nzb +" "+ liuSs.dyzb +
            "\n中气 " + liuSs.szz +" "+ liuSs.rzz +" "+ liuSs.yzz +" "+ liuSs.nzz +" "+ liuSs.dyzz +
            "\n余气 " + liuSs.szy +" "+ liuSs.rzy +" "+ liuSs.yzy +" "+ liuSs.nzy +" "+ liuSs.dyzy
        );
    }

    std::string toFullString( LN_SHISHEN liuSs ){
        return std::string(
            "     流时 流日 流月 流年 大运 年柱 月柱 日柱 时柱\n"
            "主星 " + liuSs.ss +" "+ liuSs.rs +" "+ liuSs.ys +" "+ liuSs.ns +" "+ liuSs.dys +" " + baSs.ns +" " + baSs.ys +" "+ baSs.rs +" "+ baSs.ss +
            "\n本气 " + liuSs.szb +" "+ liuSs.rzb +" "+ liuSs.yzb +" "+ liuSs.nzb +" "+ liuSs.dyzb +" " + baSs.nzb +" "+ baSs.yzb +" "+ baSs.rzb +" "+ baSs.szb +
            "\n中气 " + liuSs.szz +" "+ liuSs.rzz +" "+ liuSs.yzz +" "+ liuSs.nzz +" "+ liuSs.dyzz +" " + baSs.nzz +" "+ baSs.yzz +" "+ baSs.rzz +" "+ baSs.szz +
            "\n余气 " + liuSs.szy +" "+ liuSs.rzy +" "+ liuSs.yzy +" "+ liuSs.nzy +" "+ liuSs.dyzy +" " + baSs.nzy +" "+ baSs.yzy +" "+ baSs.rzy +" "+ baSs.szy
        );
    }
};
