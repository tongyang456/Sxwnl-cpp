#include <cctype>

#include <cstring>
#include <cstdio>

#include "lat_lon_data.h"
#include "conio.h"

JINGWEI jw={116+23/60.0, 39.9, "默认", "北京"};

const char *JW[]={
	"北京市 dshN天安门 dshO北京市 djh8房山区 dihK大兴区 drhQ崇文区 dthQ朝阳区 dthd通州区 dvhI海淀区 duhP东城区 dthM西城区 dqhL宣武区 dphH丰台区 dshD石景山区 duh6门头沟区 eDhE昌平区 e8hd顺义区 eJhc怀柔区 e8i7平谷区 eRgw延庆县 eMho密云县",
	"福建省 Q5kI福州市 OTj5厦门市 OVid漳州市 Orje泉州市 QGib三明市 P6i2龙岩市 QdjA南平市 QekV宁德市 PQk0莆田市 QdjA延平区 QEia三元区 QGic梅列区 P6i2新罗区 QekV蕉城区 PRk6涵江区 PQk0城厢区 PQk1荔城区 PJk5秀屿区 P7jr泉港区 Ovje洛江区 Otja丰泽区 Otja鲤城区 Oij9同安区 ObjE翔安区 OYj6集美区 ORj5思明区 OVj5湖里区 OSix海沧区 OVih龙文区 OVid芗城区 OnjZ晋江市 Oijd石狮市 ORin龙海市 PIiP漳平市 OwjN南安市 PxiM永安市 R2jJ建瓯市 RKj7建阳市 Rkj2武夷山市 RMiT邵武市 R5kd福安市 RKlD福鼎市 PwkV长乐市 PhkN福清市 Q3kJ仓山区 Q4kI台江区 Q5kI鼓楼区 Q5kJ晋安区 PykR马尾区 Ohhi永定县 Nei0饶平县 NhiB诏安县 NviK云霄县 O8ib漳浦县 NgiQ东山县 OQjJ金门县 Obij长泰县 OMiI平和县 OViM南靖县 P1iW华安县 P4jB安溪县 PUjE德化县 PJjI永春县 QAjB尤溪县 Pgip大田县 QBhn清流县 QGhd宁化县 Phhj连城县 P3hP上杭县 P6h6武平县 PohL长汀县 QMiC明溪县 QsiA泰宁县 Qoho建宁县 RtjW浦城县 RXiK光泽县 Qmim顺昌县 QiiS将乐县 QOil沙县 QZjj古田县 Qtjx屏南县 QTkX罗源县 Qrky霞浦县 R7kK周宁县 RSkU寿宁县 RMjp政和县 RWjl松溪县 REks柘荣县 QCkW连江县 Q9k8闽侯县 QDjp闽清县 Pqju永泰县 PMjf仙游县 P2jm惠安县 PVkl平潭县",
	"安徽省 VoiF合肥市 UWi3安庆市 UeiT池州市 VkhU六安市 Wsgn阜阳市 Xpgl亳州市 Xchx宿州市 Xvhm淮北市 Wchy淮南市 WtiN蚌埠市 WIjJ滁州市 VgjU马鞍山市 Vaiq巢湖市 VKjN芜湖市 Uuin铜陵市 Uvjj宣城市 ThjK黄山市 Xchw埇桥区 Xshm烈山区 Xvhm相山区 Xyhn杜集区 Wtgp颍东区 Wrgm颍州区 Wugm颍泉区 Xrgk谯城区 WuiK禹会区 WviN龙子湖区 WviL蚌山区 WwiL淮上区 Wci3大通区 Wei0田家庵区 Wahp谢家集区 Wcho八公山区 Wlhn潘集区 WJjI南谯区 WIjI琅琊区 Vaip居巢区 VriF庐阳区 VqiI瑶海区 VpiG蜀山区 VmiI包河区 VkhT裕安区 VkhU金安区 U9h7宿松县 Uai0宜秀区 UUi3迎江区 UVi2大观区 UdiT贵池区 Util郊区 Uvip狮子山区 Uuin铜官山区 VfjT雨山区 VhjU花山区 VijT金家庄区 VJjM戈江区 VLjM镜湖区 VMjN鸠江区 VEjE三山区 Uvjj宣州区 UIj8黄山区 TnjK徽州区 ThjK屯溪区 V3hv桐城市 Wlix明光市 Wgjy天长市 Ucjx宁国市 UQhG太湖县 U6i1东至县 UDiT石台县 UgiC枞阳县 Uhho怀宁县 U8hf望江县 UchY潜山县 UphL岳西县 VOhK霍山县 VShu舒城县 VFiH庐江县 VhiA肥西县 VriS肥东县 Vhgt金寨县 WKhG霍邱县 WchG颍上县 WcgZ阜南县 XAgb太和县 X9hC利辛县 XVhD涡阳县 X4gF临泉县 Xthk濉溪县 YBhu萧县 YPhL砀山县 XJiJ固镇县 XXiX灵璧县 WwiB怀远县 XGhY蒙城县 Wghh凤台县 WZhl寿县 WqiY凤阳县 WTiA长丰县 WWie定远县 WRjQ来安县 X9ir五河县 XTir泗县 UskP广德县 V8kA郎溪县 VXjT当涂县 VhjM和县 W6jG全椒县 Vhj6含山县 VIit无为县 Uvil铜陵县 V5jC繁昌县 UtjK南陵县 V9jY芜湖县 UHjW旌德县 UgjO泾县 Udip青阳县 TljB休宁县 Tqih祁门县 Tuiu黟县 TqjQ歙县 U4ja绩溪县",
	"甘肃省 a4Un兰州市 YxTt甘南藏族自治州 ZaUD临夏回族自治州 buTc武威市 dmPG嘉峪关市 djPV酒泉市 cuRR张掖市 cUTB金昌市 ZiYc庆阳市 ZXXe平凉市 aXVB白银市 ZZVb定西市 YZWh天水市 XOVt陇南市 djPV肃州区 cuRR甘州区 cUTB金川区 a3Uo城关区 a6Ub西固区 aKTq红古区 buTc凉州区 aXVB白银区 aiVo平川区 ZXXe崆峒区 ZiYc西峰区 ZZVb安定区 YYWr麦积区 XOVt武都区 YxTt合作市 ZaUD临夏市 eHO3玉门市 e8Le敦煌市 YZWh秦州区 XyT4玛曲县 YZTT碌曲县 Y3UD迭部县 YZUU卓尼县 YgUL临潭县 ZTUZ广河县 ZUTy临夏县 ZQUL和政县 ZCTV夏河县 ZhTr积石山保安族东乡族撒拉族自治县 ZeUO东乡族自治县 ZuUJ永靖县 aiUG永登县 bSTr古浪县 axU8天祝藏族自治县 dxPs金塔县 d8RA临泽县 dNQn高台县 coQb肃南裕固族自治县 cQRn民乐县 clS5山丹县 cFSw永昌县 cbU5民勤县 eWMo瓜州县 dcLK阿克塞哈萨克族自治县 dVLr肃北蒙古族自治县 ZUZM正宁县 ZUYt宁县 ZnZ1合水县 ZyYr庆城县 aSYx华池县 aZYI环县 ZfYC镇原县 b9V4景泰县 aYVf靖远县 aKUv皋兰县 ZpV7榆中县 ZgW3会宁县 ZVWh静宁县 ZCX3庄浪县 YyXD张家川回族自治县 YjX8清水县 Y1WI西和县 YBWA礼县 YiWK甘谷县 YhVr武山县 ZCWF通渭县 YqWe秦安县 Z0Vc陇西县 YpVS漳县 ZNUq临洮县 ZMUh康乐县 Z8VD渭源县 YQV2岷县 Y3VN宕昌县 XlVM舟曲县 WvVf文县 XtXI两当县 XKWa康县 ZIY2崇信县 Z4Yb灵台县 XkX5徽县 XiWh成县 ZKYM泾川县 ZDXd华亭县",
	"广东省 N8eG广州市 LGbL湛江市 Lebt茂名市 Lqcx阳江市 MXf3深圳市 MVeN中山市 MGeY珠海市 MZe5江门市 N3dS肇庆市 N1e7佛山市 Nge2清远市 N3ej东莞市 N7fP惠州市 Nifg河源市 Onea韶关市 Mtd2云浮市 Nehb潮州市 OHh7梅州市 NXhM揭阳市 NLhf汕头市 MlgM汕尾市 N3dT端州区 NAdY鼎湖区 N5fO惠城区 MmfS惠阳区 MVet南山区 MYes宝安区 MWf3福田区 MXf7罗湖区 MXfD盐田区 MifG龙岗区 NIeo增城市 NXeZ从化市 MDeH斗门区 M4eO金湾区 MGeX香洲区 N2e9南海区 MmeI顺德区 NAdq三水区 Msdr高明区 MSe2新会区 Lqcv江城区 Mud2云城区 LSc1茂港区 Lcbt茂南区 LGbJ麻章区 LEbS坡头区 LCbO霞山区 LGbM赤坎区 LQbk吴川市 Ktb5雷州市 LbbG廉江市 MLbv信宜市 Ltbp高州市 Lebc化州市 MkcY罗定市 MBdI恩平市 MBcl阳春市 MNde开平市 MFdl台山市 Mkdw鹤山市 N2dR高要市 NKdf四会市 OBeO英德市 P7fI南雄市 P8eL乐昌市 OldN连州市 O9gi兴宁市 Mvgd陆丰市 NIhB普宁市 Nge1清城区 Ofea曲江区 Omea浈江区 OmeY武江区 Nifg源城区 OJh7梅江区 Nfhc湘桥区 Nehy饶平县 NThk澄海区 NMhg金平区 NMhh龙湖区 NHhi达濠区 NGha潮阳区 NFhQ潮南区 KKbA徐闻县 LNbF遂溪县 LUc0电白县 Ljcb阳西县 MgdE新兴县 Lrd1阳东县 MmeU南沙区 NcdQ广宁县 Nidx清新县 NreW佛冈县 NOeD花都区 N6eR黄埔区 N7eL天河区 N6eF海珠区 N8eE荔湾区 N8eG越秀区 NAeG白云区 MveL番禺区 NBeU萝岗区 NBfH博罗县 Mxfh惠东县 NcgB紫金县 Nnfk东源县 O4fC新丰县 NifF龙门县 OLf8翁源县 Ovf4始兴县 OMfT连平县 ORfu和平县 P5ej仁化县 OleG乳源瑶族自治县 OTdc阳山县 OhdH连南瑶族自治县 OYd5连山壮族瑶族自治县 NtdB怀集县 N5d0云安县 N9ck德庆县 NQcU封开县 NEcW郁南县 OLhg大埔县 OYgr平远县 OehA蕉岭县 NkhB丰顺县 OHh3梅县 O6gF龙川县 Nugk五华县 NIgd陆河县 NQgo揭西县 MwgK海丰县 N2hH惠来县 NYhP揭东县 NPi1南澳县 NRhf潮安县",
	"广西壮族自治区 MnZM南宁市 LgZL防城港市 LTa7北海市 LvZb钦州市 N6aa贵港市 MOYM崇左市 OgZ4河池市 NiaE来宾市 OKaP柳州市 NsXb百色市 PHbH桂林市 NTcG梧州市 OPcX贺州市 McbA玉林市 OgZ3金城江区 MjZT邕宁区 MkZJ良庆区 MqZN兴宁区 MlZH江南区 MoZI西乡塘区 OLaN柳南区 N8aP覃塘区 N5aa港南区 LWaQ铁山港区 LxZc钦北区 LkZL防城区 LdZM港口区 M7Xj凭祥市 LWYw东兴市 NnZq合山市 OUZe宜州市 NOb5桂平市 Mtbx岑溪市 MhbL北流市 N8XP靖西县 N5Y8天等县 MLXp龙州县 M8Y4宁明县 LeaC合浦县 MHaw博白县 MGaX浦北县 MQaI灵山县 MfaG横县 Mjaq兴业县 NDZm宾阳县 NAZG武鸣县 McYs扶绥县 M9Yx上思县 MoYC大新县 NBYf隆安县 NJYZ平果县 O9YF巴马瑶族自治县 OVYM东兰县 NuZ6都安瑶族自治县 NiYx大化瑶族自治县 NhZA马山县 NQZa上林县 Naae武宣县 Nwaf象州县 OGaK柳江县 OTai鹿寨县 O4Ze忻城县 OlZs罗城仫佬族自治县 P4aF融水苗族自治县 PEaO融安县 OdaE柳城县 Oxax永福县 Plaa三江侗族自治县 PjZs从江县 OoZF环江毛南族自治县 OxYW南丹县 OlXX乐业县 OyYA天峨县 OXY3凤山县 OLXY凌云县 NiXt田阳县 NaY7田东县 NKXb德保县 NPWo那坡县 OIXE田林县 OUW6西林县 OkWK隆林各族自治县 Puc4全州县 PTc9灌阳县 Pbbe兴安县 Q2bc资源县 Pmb0龙胜各族自治县 PPbJ灵川县 PEbC临桂县 OlbT阳朔县 Ocbc平乐县 Oobo恭城瑶族自治县 OocG富川瑶族自治县 OWcI钟山县 OAbm昭平县 OUbN荔浦县 O8bB金秀瑶族自治县 OCbV蒙山县 NXbN平南县 NNbt藤县 NPcE苍梧县 MqbX容县 MKbG陆川县",
	"贵州省 QdXc贵阳市 P5Vs黔西南布依族苗族自治州 QaVo六盘水市 RIWH毕节地区 QFWv安顺市 QZYw黔东南苗族侗族自治州 QGYV黔南布依族苗族自治州 RiXt遵义市 RhaB铜仁地区 QfXd白云区 REZt玉屏侗族自治县 PjZs从江县 QFWt西秀区 QWXg小河区 QYXh南明区 QbXh云岩区 QcXj乌当区 SZWg赤水市 RdXt红花岗区 RiXt汇川区 QaVo钟山区 P5Vs兴义市 RIWH毕节市 QZYw凯里市 QgYU福泉市 QGYV都匀市 QXXS清镇市 RhaB铜仁市 RnXP仁怀市 PhVS盘县 PlVv普安县 QqVH威宁彝族回族苗族自治县 R8Vh赫章县 QDWT六枝特区 QlWN纳雍县 QXVv水城县 R9Wa大方县 R2X2黔西县 RSXD金沙县 QeWk织金县 QJWj普定县 Q4Wk镇宁布依族苗族自治县 QPXF平坝县 PjX5紫云苗族布依族自治县 PvWb关岭布依族苗族自治县 PoWD晴隆县 PNWd贞丰县 PQWB兴仁县 P7WS安龙县 OxWn册亨县 PAX6望谟县 PQXj罗甸县 Q2XR长顺县 PoYJ平塘县 PoYW独山县 PuZV榕江县 PPYr荔波县 PxYq三都水族自治县 QNZ4雷山县 QeZJ台江县 QiZR剑河县 QEa8黎平县 QwZf三穗县 QfaC锦屏县 QtaC天柱县 RBZn岑巩县 R3ZP镇远县 R2Z7施秉县 QsYs黄平县 RDYr余庆县 R4YS瓮安县 QCYm丹寨县 QUYZ麻江县 QZYE贵定县 QRXw龙里县 Q8Xd惠水县 QoXZ修文县 R6Xi息烽县 R4Xw开阳县 RWXo遵义县 S8Xn桐梓县 SXYQ正安县 SrYa道真仡佬族苗族自治县 RwYh凤冈县 RvYB绥阳县 RkYT湄潭县 RuZF思南县 RyZO印江土家族苗族自治县 RVZE石阡县 RgZp江口县 RVaC万山特区 SYZU沿河土家族自治县 SAaC松桃苗族自治县 SGZ7德江县 SWYr务川仡佬族苗族自治县 SJXD习水县",
	"海南省 K2bJ海口市 IFaU三亚市 K2bI龙华区 K1bH秀英区 K0bL琼山区 K2bM美兰区 J6Zc东方市 IlaV五指山市 JFbS琼海市 ImbO万宁市 JXbm文昌市 JVaY儋州市 IjaA乐东黎族自治县 JFa3昌江黎族自治县 JEaR白沙黎族自治县 J2ao琼中黎族苗族自治县 Icag保亭黎族苗族自治县 IUb2陵水黎族自治县 JMb6屯昌县 Jib0澄迈县 JgbJ定安县 Jtaf临高县",
	"河北省 c3fV石家庄市 abfT邯郸市 b4fT邢台市 cqgS保定市 bigf衡水市 cIho沧州市 dVhg廊坊市 dcjC唐山市 ewiu承德市 enfr张家口市 duka秦皇岛市 dxi4三河市 dijP古冶区 dfjG开平区 dojA丰润区 dcjD路北区 dcjA路南区 dYj6丰南区 aPfC峰峰矿区 c5f3井陉矿区 c2fS桥西区 c1fV裕华区 c3fV长安区 c3fU桥东区 c3fS新华区 bigf桃城区 dWhh广阳区 dVhf安次区 cqgR新市区 cpgU南市区 cqgT北市区 eTgG下花园区 eag3宣化区 elfs桥东区 eofq桥西区 ewiu双桥区 evil双滦区 eXid鹰手营子矿区 e0kk山海关区 duka海港区 dokT北戴河区 agfC武安市 apfU沙河市 cLff新乐市 c2fo藁城市 c5fI鹿泉市 bYgY冀州市 c1gX深州市 btgD辛集市 c2g2晋州市 cVfw定州市 cPgJ安国市 chh6任丘市 cQh5河间市 aogg临清市 bLgN南宫市 cMiL黄骅市 c4hY泊头市 d6hO霸州市 e1jg迁安市 eBiv遵化市 dTgw涿州市 dKgp高碑店市 dki0香河县 drhx大厂回族自治县 acfT丛台区 aafT邯山区 acfR复兴区 b4fU桥东区 b3fS桥西区 cJhp运河区 cJhq新华区 aYee涉县 aLfM磁县 aLfb临漳县 aQff成安县 aXfm肥乡县 atfq鸡泽县 alfT永年县 aafW邯郸县 b8ff任县 ayff南和县 bIfV内丘县 bQfU临城县 bLfk隆尧县 b5fU邢台县 c2f8井陉县 cpfB阜平县 cFfC平山县 cIfM灵寿县 cQfX行唐县 cbfg曲阳县 brfd栾城县 c9fY正定县 befN赞皇县 bUff柏乡县 bafa高邑县 bjfk赵县 bjfV元氏县 bbft宁晋县 bWgF新河县 cBfw无极县 cBgC深泽县 cjfx唐县 chg9望都县 cog8顺平县 ckgT清苑县 cfgl高阳县 cTgY蠡县 cRgS博野县 cEgV安平县 cEgi饶阳县 cQgo肃宁县 cBh7献县 bqh9阜城县 c2gx武强县 bngr武邑县 bVgh枣强县 bghG景县 bLgw故城县 b4ge清河县 bDg2巨鹿县 b4g9广宗县 axgF威县 b4g2平乡县 alfv曲周县 angA邱县 apgU临西县 aWgI馆陶县 aTfu广平县 aMfu魏县 aHg9大名县 c8iT海兴县 c4i6孟村回族自治县 c3iD盐山县 bbhN吴桥县 c2hg南皮县 brhW东光县 cIhq沧县 cZhn青县 cghc大城县 cqhS文安县 dJhU永清县 dPjs乐亭县 dUjf滦南县 dGjR唐海县 djjg滦县 drjq卢龙县 e9jJ迁西县 drii玉田县 ekjA承德县 eajT宽城满族自治县 eOjv青龙满族自治县 f0jf平泉县 fJih隆化县 eQiV兴隆县 euiK滦平县 fChd丰宁满族自治县 fegg沽源县 eXg1宣化县 eNgD涿鹿县 eOgV怀来县 ewgG崇礼县 etgo赤城县 dQhI固安县 cxh6雄县 ctgu安新县 d3gq容城县 dOgh涞水县 dGgk定兴县 dLgU易县 d1gd徐水县 cvgJ满城县 e7fA阳原县 dpfY蔚县 dLff涞源县 ejfh万全县 eefP怀安县 f5ew尚义县 f9fg张北县 fpfb康保县 fuij围场满族蒙古族自治县 drkE抚宁县 dgkA昌黎县",
	"河南省 Yjeb郑州市 WydV南阳市 W8f4信阳市 Xbfd周口市 XZf1漯河市 Wxf1驻马店市 XkeB平顶山市 Y2ep许昌市 ZDeF焦作市 ZIes新乡市 YmfI开封市 YRgd商丘市 Zkg2濮阳市 a6fN安阳市 ZjfH鹤壁市 YbdR洛阳市 YlcC三门峡市 Xbfc汇川区 Y2en魏都区 XYf4召陵区 XYf0汇源区 XZey郾城区 Wwf3驿城区 W6f7平桥区 W7f3浉河区 Yjea中原区 Yied二七区 Yjee管城回族区 Yled金水区 Yqea惠济区 YneH上街区 XieK卫东区 XieI新华区 XieH湛河区 Xsdr石龙区 WxdW卧龙区 X1dX宛城区 YlcC湖滨区 YsdZ吉利区 YbdR洛龙区 YfdT瀍河回族区 YfdS老城区 YedQ西工区 YedO涧西区 ZGeJ马村区 ZDeF山阳区 ZFeD解放区 ZEeA中站区 ZsfB山城区 Zvf9鹤山区 ZifI淇滨区 ZJes牧野区 ZIeq红旗区 ZIep卫滨区 ZNet凤泉区 a5fL文峰区 a7fL北关区 a6fJ龙安区 a7fI殷都区 Zlg4华龙区 YAdo汝州市 Wfd5邓州市 XRfs项城市 XIeV舞钢市 YAeS禹州市 YWeN新密市 YOei新郑市 YDek长葛市 YleO荥阳市 ZSem辉县市 ZOf4卫辉市 a4en林州市 Z4dZ济源市 Z5du沁阳市 Ykdx巩义市 Yidl偃师市 YSe2登封市 Ysdl孟州市 Yjcq义马市 YVbq灵宝市 XthQ永城市 YNgc睢阳区 YRgc梁园区 YlfL禹王台区 YlfM金明区 YmfL顺河回族区 YlfL鼓楼区 YmfL龙亭区 ZqgU范县 Y3c3卢氏县 XHcT西峡县 Xlcb栾川县 X8cT淅川县 X3cp内乡县 X2dE镇平县 XUdQ南召县 Y9d6嵩县 Y9dS汝阳县 Xids鲁山县 Xre4宝丰县 XGdy方城县 X3du社旗县 Wgdo唐河县 WMeO桐柏县 WVdL新野县 WheJ泌阳县 Wmf1确山县 WafN正阳县 WCfW罗山县 Vcfq新县 W1fs光山县 VmgO商城县 WBgf固始县 Wjfx新蔡县 WQgO淮滨县 W8g2潢川县 WLfi息县 Wwfc平舆县 XOg4沈丘县 XqgT鹿邑县 Y4gI柘城县 Y4fp太康县 XdgC郸城县 Xifr淮阳县 XWfa商水县 XmfW西华县 Y4fN扶沟县 Y6fC鄢陵县 Xneu临颍县 X0fL汝南县 X9ey遂平县 XGfG上蔡县 XNf1西平县 XQea舞阳县 XbeL叶县 Y0eo许昌县 XpeT襄城县 XweD郏县 ZEeQ修武县 Z6eN武陟县 ZGed获嘉县 ZCem新乡县 Z9fC延津县 ZafC淇县 ZZfV滑县 Z3fP封丘县 YkfQ开封县 Z3ew原阳县 Yhew中牟县 YPfB尉氏县 YTfS通许县 YXfl杞县 Ynfn兰考县 Ydg8民权县 YRg4睢县 YRgJ宁陵县 YOgp虞城县 ZCff长垣县 Zvfs内黄县 a5gC南乐县 Zsg7清丰县 Zgg1濮阳县 Zygp台前县 a6fL安阳县 ZefX浚县 ZtfL汤阴县 ZAe4博爱县 Yue5温县 YodQ孟津县 Yhd9新安县 YPdP伊川县 YVdA宜阳县 Ykcj渑池县 YNcd洛宁县 Ygc5陕县 YEh8夏邑县",
	"黑龙江省 jmrW哈尔滨市 oPp7大兴安岭地区 lKov齐齐哈尔市 kZq2大庆市 iZua牡丹江市 jIvw鸡西市 jlvv七台河市 knvM佳木斯市 lKvG鹤岗市 kcw9双鸭山市 lits伊春市 kcrx绥化市 oFsT黑河市 pfpO新林区 q2oa呼中区 l9om昂昂溪区 lCob富拉尔基区 lJov龙沙区 lLov建华区 lLox铁锋区 oFsT爱辉区 kcrx北林区 k2pn大同区 kOpr红岗区 kWq6龙凤区 kaq1萨尔图区 kdpp让胡路区 jbrb平房区 jhrf香坊区 jkrf南岗区 jkrb道里区 jlrd道外区 jmrX松北区 jsrZ呼兰区 jXrx阿城区 jkw4茄子河区 jmvo新兴区 jkvw桃山区 l1u1带岭区 l8uH南岔区 lPuQ金山屯区 lTuH西林区 lcu8美溪区 lhtl乌马河区 lhtd翠峦区 lptn友好区 lwu1上甘岭区 m7uF五营区 mEuN红星区 mHuW新青区 mRuY汤旺河区 mauP乌伊岭区 lGvD兴安区 lMvI兴山区 lJvF工农区 lIvH南山区 lKvH向阳区 lKvJ东山区 knvM前进区 kmvJ郊区 kmvK向阳区 knvO东风区 kYwO宝山区 kZwK四方台区 kYw8岭东区 kcwA尖山区 jKw0城子河区 jIvw鸡冠区 jCvu恒山区 jMvl滴道区 jCvV麻山区 j5vf梨树区 iZuZ爱民区 iZub东安区 iYub西安区 iauc阳明区 kOqK安达市 mTpq讷河市 mVrC五大连池市 mErV北安市 jMrJ双城市 k4qx肇东市 its9五常市 jDsv尚志市 iYuN海林市 iLuS宁安市 itvV穆棱市 iPw9绥芬河市 jXwq密山市 lFx2富锦市 kxt1铁力市 lSrw海伦市 ldxV同江市 jkxx虎林市 ltoU甘南县 lKoB龙江县 kOoP泰来县 kqpR杜尔伯特蒙古族自治县 lBpq林甸县 lnpS富裕县 lrqI依安县 m2qq克山县 m2rF克东县 lar5拜泉县 korT望奎县 kfr6青冈县 lBqs明水县 kGrH兰西县 jgqG肇州县 jVq5肇源县 k5sO巴彦县 jjsT宾县 jvt2木兰县 jRtK延寿县 jwtj通河县 joto方正县 i4w7东宁县 jFw8鸡东县 jjvY勃利县 jIvG林口县 kius汤原县 l1vh桦川县 kEvY桦南县 khw8集贤县 klwm友谊县 kJxC宝清县 lHwp绥滨县 lZvo萝北县 mrvN嘉荫县 kJuX依兰县 krsV庆安县 lFs6绥棱县 nPsJ孙吴县 nZtS逊克县 qJpg塔河县 pird呼玛县 qwnW漠河县 kmz1饶河县 mMzH抚远县",
	"湖北省 UafI武汉市 UIaS恩施土家族苗族自治州 UKdE荆州市 Uuet孝感市 VheM随州市 V2dC荆门市 UgcH宜昌市 W1d9襄樊市 Wdbl十堰市 UCg2黄石市 UOfr鄂州市 URfq黄冈市 TpfJ咸宁市 TqfI咸安区 U5fe梁子湖区 UOfr鄂城区 UBfw下陆区 UCfs铁山区 UCg7西塞山区 UEg4黄石港区 UQfr黄州区 Utet孝南区 Upfm新洲区 UqfM黄陂区 UWfi华容区 ULfJ江夏区 UJf5汉南区 UZf2蔡甸区 Ubf8东西湖区 UUfK洪山区 UYfG硚口区 UYfI武昌区 UXfG汉阳区 UafG江汉区 UafI江岸区 UcfN青山区 Wabn茅箭区 Wdbl张湾区 W5dC襄阳区 W1d9襄城区 W2d8樊城区 UxdC掇刀区 V3dC东宝区 ULdB荆州区 VheM曾都区 UJdF沙市区 UkcJ夷陵区 UgcG西陵区 UgcG点军区 UdcL伍家岗区 UWcP猇亭区 UIaS恩施市 UIZu利川市 UOcR宜都市 UQck枝江市 UBck松滋市 TidO石首市 TmeR洪湖市 Ther赤壁市 UMeR仙桃市 UPdr潜江市 UeeA天门市 Udeo汉川市 UveY应城市 VGef安陆市 Vben广水市 VhdF宜城市 VAdZ钟祥市 Uncl当阳市 WXcV丹江口市 WNce老河口市 W8dj枣阳市 VBg2麻城市 U6fw大冶市 TpgX武穴市 Tfa9咸丰县 TVaO来凤县 TxaT宣恩县 Uaai建始县 VLbj兴山县 Vjbe神农架林区 V3bK巴东县 Uobx秭归县 UCbe五峰土家族自治县 Tsb2鹤峰县 UScB长阳土家族自治县 U4dE公安县 U2dP江陵县 TFen通城县 Txes嘉鱼县 Tndr监利县 UgdZ沙洋县 V1e6京山县 V1ej云梦县 VFew孝昌县 V4cc远安县 Vlco南漳县 VrcF保康县 WGcd谷城县 Wobn郧县 W4bi房县 WEbE竹山县 WJah竹溪县 WybP郧西县 Ujge英山县 VHfb红安县 VYf7大悟县 Ucfq团风县 UlgO罗田县 URgG浠水县 TpgC阳新县 TafV通山县 TXf2崇阳县 UEgQ蕲春县 U5gu黄梅县 U9h7宿松县",
	"湖南省 SEdu长沙市 QQcb永州市 RFcS邵阳市 RYay怀化市 SJai湘西土家族苗族自治州 T8bS张家界市 Rid0娄底市 Rodu湘潭市 SadJ益阳市 T3cf常德市 TMe7岳阳市 Roe8株洲市 QsdY衡阳市 Ple1郴州市 S7dx天心区 S8e2雨花区 SBe2芙蓉区 SFdx开福区 SEdu岳麓区 Rqds雨湖区 Rqdv岳塘区 Roe9芦淞区 RqeA荷塘区 Rqe6石峰区 Roe7天元区 RFdi南岳区 Qsda蒸湘区 Qrda雁峰区 Qsda石鼓区 Qsdb珠晖区 Pme1北湖区 Pme2苏仙区 QEcb零陵区 QQca冷水滩区 REcS双清区 REcR大祥区 RFcR北塔区 Ricy娄星区 RXav鹤城区 T8bT永定区 TLbW武陵源区 T2cf武陵区 T1cf鼎城区 SadJ资阳区 SadM赫山区 TMe6岳阳楼区 TQdy君山区 TSeI云溪区 Qibc武冈市 RCan洪江市 SJai吉首市 Rgce涟源市 RfcQ冷水江市 RidW湘乡市 RudV韶山市 Sme5汨罗市 SpdN沅江市 Tbcr津市市 TTeS临湘市 S9ec浏阳市 ReeT醴陵市 QPdN常宁市 QPdp耒阳市 PxeE资兴市 PBcZ江华瑶族自治县 PHcK江永县 PWcZ道县 Pwcd双牌县 QMbJ城步苗族自治县 QQbp新宁县 QOcH东安县 R7c2隆回县 QycG邵阳县 RJcR新邵县 R3bY洞口县 ROau中方县 RRaf芷江侗族自治县 Qqah会同县 QZb9绥宁县 QZaf靖州苗族侗族自治县 QAal通道侗族自治县 RMaA新晃侗族自治县 REZt玉屏侗族自治县 S0bB辰溪县 Rvaa凤凰县 Rqam麻阳苗族自治县 SDbD泸溪县 Sbav古丈县 Shad保靖县 SZaT花垣县 TSaQ龙山县 TOb9桑植县 T0ap永顺县 TZcN石门县 TRcd临澧县 TPc7慈利县 SscT桃源县 SNcD安化县 SSbN沅陵县 RtbZ溆浦县 RjcI新化县 Rldv湘潭县 SFdX宁乡县 SFe4长沙县 SMdn望城县 Sfdr湘阴县 SWd7桃江县 Sscw汉寿县 TPdA安乡县 Tccj澧县 TVdY华容县 TNdO南县 T9e7岳阳县 SheZ平江县 Rhe8株洲县 Q5eu桂东县 QTek炎陵县 Q8e6永兴县 QgeG安仁县 R0eK攸县 QmeW茶陵县 REdq衡山县 R5dv衡东县 RRdC双峰县 RFcj邵东县 Qld7祁东县 QwdM衡阳县 QZcp祁阳县 Qide衡南县 Pidi桂阳县 POdv宜章县 PtdD新田县 Pacu宁远县 PZdM嘉禾县 PHdX临武县 PMdB蓝山县 PXef汝城县",
	"吉林省 hsqJ长春市 hApL四平市 fiqu通化市 furP白山市 grq8辽源市 horX吉林市 j8pn松原市 jbno白城市 gruU延边朝鲜族自治州 jbnp洮北区 jUpH大安市 hApN铁东区 h9pL铁西区 hoqH朝阳区 hqqK南关区 hqqM二道区 htqJ宽城区 hrqF绿园区 hVqe双阳区 htrY龙潭区 hrrY昌邑区 hnrY丰满区 horW船营区 g3rZ江源区 furO八道江区 hVoU双辽市 f7rB集安市 fmrs临江市 gvr3磐石市 gwri桦甸市 gWqf梅河口市 hUpn公主岭市 iWqg德惠市 i9qo九台市 hhsK蛟河市 iPrv舒兰市 inrX榆树市 jKnl洮南市 gwuo图们市 gkuP龙井市 gruU延吉市 gWu0和龙市 gqvM珲春市 hMtE敦化市 jApm宁江区 gsq7龙山区 gtq9西安区 fkr2二道江区 fiqv东昌区 hJpK梨树县 ffqj通化县 gfr2辉南县 gOrm靖宇县 gKsH抚松县 hLqI伊通满族自治县 gHqi柳河县 gfqW东丰县 gtpy东辽县 iQqB农安县 herU永吉县 ixr1扶余县 j7pn前郭尔罗斯蒙古族自治县 jpoC镇赉县 j1p1乾安县 iHox长岭县 ino5通榆县 hJuj汪清县 h7ts安图县 fPtC长白朝鲜族自治县",
	"江苏省 W4jl南京市 Xbk1淮安市 WCkR镇江市 Vlkv常州市 VYlI无锡市 VIlZ苏州市 Vxlr南通市 XLl9盐城市 WRkt泰州市 WOkO扬州市 YakD连云港市 XwjH宿迁市 YGiB徐州市 YjkM连云区 YakA新浦区 YYk7海州区 YRiR贾汪区 YIi8九里区 YHiB鼓楼区 YFiD云龙区 YFiB泉山区 XvjJ宿豫区 XwjF宿城区 XUk8楚州区 Xck2淮阴区 Xak1清河区 XZk2清浦区 XOl8亭湖区 XKl9盐都区 W2lm港闸区 Vylp崇川区 WNkO邗江区 WNkQ广陵区 WPkO维扬区 W7jr栖霞区 W4jk鼓楼区 W3jm玄武区 W2jl白下区 W2jj建邺区 W1jm秦淮区 Vvjp江宁区 W8kR丹徒区 WCkO润州区 WCkS京口区 Vokw新北区 Vil3戚墅堰区 Vhku武进区 Vjku天宁区 Vlku钟楼区 VflH惠山区 ValL锡山区 VZlI崇安区 VZlH北塘区 VYlI南长区 VYlG滨湖区 VIlc沧浪区 VJlc平江区 VJla金阊区 VMlc相城区 VGlc吴中区 WGkB仪征市 VvkA句容市 VLkn宜兴市 VPkT溧阳市 VykY丹阳市 WEkn扬中市 VjkY金坛市 WAl1泰兴市 VslG江阴市 W1lG靖江市 VqlX张家港市 VAlc吴江市 VNlx昆山市 VRm6太仓市 Vnmd启东市 W5m4通州市 VsmA海门市 Vdlj常熟市 XClS大丰市 WplI东台市 WOlY如皋市 WVl9姜堰市 Wtkp兴化市 WQkX江都市 WlkQ高邮市 W5ji下关区 YJiv邳州市 Vyjk雨花台区 W3jb浦口区 WLjo六合区 VIlY虎丘区 YNjL新沂市 XSjD泗洪县 X0jT盱眙县 XIjo洪泽县 X1k1金湖县 Vdk1溧水县 VKjr高淳县 WJmB如东县 WXlR海安县 XEkI宝应县 XSkm建湖县 XlkG涟水县 Xlkm阜宁县 Xxko滨海县 YCkY响水县 Y5kL灌南县 YIkF灌云县 XllF射阳县 Yok7赣榆县 YWjk东海县 Xhjf泗阳县 Y8jk沭阳县 Xsiv睢宁县 YBiA铜山县 Yihu沛县 Ygha丰县",
	"江西省 Sfgp南昌市 Pofu赣州市 R7fx吉安市 Rcep萍乡市 Rnft新余市 RmfN宜春市 Tggy九江市 RyhL抚州市 SGi4鹰潭市 TGiA景德镇市 SRiw上饶市 SEi3月湖区 SQiv信州区 TIiC珠山区 TGiA昌江区 RxhL临川区 Shgi湾里区 Scgt青云谱区 Sfgv青山湖区 Sfgs东湖区 Segq西湖区 Tfgx庐山区 Tigx浔阳区 Rdei湘东区 Rdeq安源区 RmfN袁州区 Rmfu渝水区 R6fy青原区 R7fx吉州区 Pqfu章贡区 Pdfj南康市 Prh2瑞金市 QhfG井冈山市 Tfge瑞昌市 SCgl丰城市 SPgM高安市 S4gW樟树市 SHiD贵溪市 Swi7乐平市 SviY德兴市 PgfI崇义县 POfL大余县 PmfW上犹县 Pqg0赣县 PNfu信丰县 Otfl龙南县 OjfV全南县 Olg2定南县 P8gN安远县 Ovgd寻乌县 Pagl会昌县 QKgL兴国县 PvgP于都县 QKhK石城县 QTh1宁都县 QohJ广昌县 Qmfr泰和县 R3fs吉安县 RDg8吉水县 QSfl万安县 QKfV遂川县 QvfE永新县 R8ev莲花县 Rrem上栗县 Rcf2芦溪县 RNfb安福县 Rnfe分宜县 S7fQ万载县 SNfl宜丰县 SEft上高县 SWfM铜鼓县 T2fY修水县 SqgL靖安县 SpgX安义县 TGg6武宁县 TRh2星子县 Tbgr九江县 TihD湖口县 TGhB都昌县 TKgk德安县 T2gm永修县 SMhG进贤县 SXgu南昌县 Sggn新建县 SggN奉新县 RkgO新干县 RbgK峡江县 RJgQ永丰县 RQgo乐安县 Rkh3崇仁县 RXhD宜黄县 RXhc南城县 Rthk金溪县 Rgi4资溪县 SPia横峰县 SJig铅山县 SOiQ弋阳县 Sgi4万年县 SChn余江县 SEhb东乡县 Sghf余干县 Syhe鄱阳县 TshX彭泽县 TMiF浮梁县 TFip婺源县 SQjB广丰县 RDhW南丰县 RIht黎川县 SfjF玉山县 SQit上饶县",
	"辽宁省 fmoQ沈阳市 ehlo葫芦岛市 f6m8锦州市 ctmb大连市 e8pN丹东市 fIok本溪市 fGoA辽阳市 f6nx鞍山市 eenE营口市 f7n4盘锦市 frox抚顺市 gHoo铁岭市 g1me阜新市 fYlR朝阳市 fCn3双台子区 f7n4兴隆台区 f8oR弓长岭区 fCoC宏伟区 f4nw千山区 f6nx铁东区 f7nv铁西区 f9ny立山区 eenM老边区 eenD西市区 efnG站前区 eGn7鲅鱼圈区 cnmG旅顺口区 gHop银州区 floI于洪区 fkoS东陵区 fmoL铁西区 d6mg金州区 floO和平区 ctma西岗区 fmoR沈河区 gWp9清河区 ctmc中山区 cvmY甘井子区 csmZ沙河口区 fnoP皇姑区 fmoS大东区 feoK苏家屯区 g3oV新城子区 g1md海州区 g1me太平区 g2mf细河区 fjmP清河门区 fYlR双塔区 falQ龙城区 fZlS朝阳县 f7m9凌河区 f8m7古塔区 f6m6太和区 f6lj南票区 eklq连山区 ehlu龙港区 fFkO凌源市 eblh兴城市 fAmL凌海市 dOmv普兰店市 dbmy瓦房店市 dgnx庄河市 dqp9东港市 eRp4凤城市 fPoK灯塔市 erng海城市 eOnL盖州市 ednU大石桥市 famm北镇市 fynn新民市 gXp2开原市 gSoX调兵山市 fmlk北票市 fFoB太子河区 fGoB文圣区 fGoA白塔区 e5pL振兴区 eApP振安区 e8pN元宝区 f6oi南芬区 fKok溪湖区 fIon明山区 fIok平山区 fpol望花区 fpp1东洲区 fqor新抚区 frou顺城区 f8ki喀喇沁左翼蒙古族自治县 enkm建昌县 fOkc建平县 eJlK绥中县 dGnZ长海县 eHoH岫岩满族自治县 fIp7本溪满族自治县 fDo4辽阳县 fNnP台安县 exn4大洼县 fFn1盘山县 fgn7黑山县 g4mj阜新蒙古族自治县 gNnW彰武县 fVnh辽中县 fros抚顺县 glp6昌图县 gIoo铁岭县 gUoO法库县 gjoL康平县 fWmE义县 giph西丰县 g6pt清原满族自治县 fiq2新宾满族自治县 fGqL桓仁满族自治县 eipl宽甸满族自治县",
	"内蒙古自治区 eoci呼和浩特市 ejYP巴彦淖尔市 coWe阿拉善盟 deXn乌海市 dbam鄂尔多斯市 edao包头市 exe7乌兰察布市 gGjt赤峰市 hvh4锡林郭勒盟 nDkk呼伦贝尔市 k5n3兴安盟 hbnG通辽市 nDkk海拉尔区 ompH松岭区 oPp7加格达奇区 mSpU莫力达瓦达斡尔族自治旗 hbnG科尔沁区 g2kH元宝山区 gHjt松山区 gHjw红山区 f2e6集宁区 ejce玉泉区 emca回民区 emcf赛罕区 eqcd新城区 fkaw白云鄂博矿区 efbG石拐区 eZb1东河区 eaaw九原区 edas青山区 ecao昆都仑区 ejYO临河区 dnb0东胜区 dQXr海南区 dUXg乌达区 dgXo海勃湾区 eQe9丰镇市 huh4锡林浩特市 jWkd霍林郭勒市 hdcx二连浩特市 nZiR满洲里市 olmV根河市 oElB额尔古纳市 nHli牙克石市 lxnj扎兰屯市 lBku阿尔山市 k5n3乌兰浩特市 dCSf阿拉善右旗 fwS4额济纳旗 f6Y4乌拉特后旗 f6ZG五原县 erY9杭锦后旗 eKY1磴口县 coWe阿拉善左旗 cBYT鄂托克前旗 d6Yx鄂托克旗 caZp乌审旗 dqcE准格尔旗 dYai伊金霍洛旗 doZh杭锦旗 ehZd乌拉特前旗 fYZV乌拉特中旗 fgbQ达尔罕茂明安联合旗 f2b3固阳县 eOb2达拉特旗 eYbV土默特右旗 ehc8土默特左旗 eGcB托克托县 eNcn和林格尔县 eWdT凉城县 esdY卓资县 fGdc察哈尔右翼中旗 fVcg四子王旗 f5cR武川县 gjdd苏尼特右旗 gEeo镶黄旗 fsey化德县 fXeW商都县 fReB察哈尔右翼后旗 eleD察哈尔右翼前旗 erer兴和县 dtcf清水河县 fakK宁城县 fujg喀喇沁旗 guk1翁牛特旗 gBhS多伦县 gFgy正蓝旗 fsgH太仆寺旗 gIfy正镶白旗 i1fw阿巴嘎旗 hFiW克什克腾旗 hxkN巴林左旗 haj3林西县 hVje巴林右旗 iZia西乌珠穆沁旗 jVhw东乌珠穆沁旗 mDjG新巴尔虎左旗 mehn新巴尔虎右旗 hpec苏尼特左旗 nJkQ陈巴尔虎旗 n8kj鄂温克族自治旗 oZoh鄂伦春自治旗 kins扎赉特旗 m8oS阿荣旗 k4mt科尔沁右翼前旗 j3mS科尔沁右翼中旗 jNmY突泉县 iXlt扎鲁特旗 hrl5阿鲁科尔沁旗 hamI开鲁县 gvnL科尔沁左翼后旗 gpld奈曼旗 i8oJ科尔沁左翼中旗 gimk库伦旗 gHks敖汉旗",
	"宁夏回族自治区 cSXH银川市 a0XH固原市 bxXC吴忠市 bVWB中卫市 d1XN石嘴山市 dFXl惠农区 d1XN大武口区 cTXB西夏区 cTXH兴庆区 cSXF金凤区 bxXC利通区 bVWB沙坡头区 a0XH原州区 c1X4青铜峡市 c6XK灵武市 aYWd海原县 ZwWi西吉县 ZbX7隆德县 ZTXK泾源县 ZpXc彭阳县 axWt同心县 bTWe中宁县 csXW平罗县 cHXF永宁县 cXXL贺兰县 blYO盐池县",
	"青海省 abSl西宁市 X0O1玉树藏族自治州 YTRE果洛藏族自治州 aHRb海南藏族自治州 bMOM海西蒙古族藏族自治州 aUT7海东地区 ZVT1黄南藏族自治州 awRs海北藏族自治州 abSm城东区 abSl城中区 aPLs格尔木市 bMOM德令哈市 abSk城西区 aeSk城北区 WsMI杂多县 XpMb治多县 Y8Mm曲麻莱县 X0O1玉树县 XMO6称多县 WCNT囊谦县 XjQd达日县 YTRE玛沁县 XwQs甘德县 YtPB玛多县 ZFRY同德县 ZZQx兴海县 aHRb共和县 bIQ1天峻县 aIP5都兰县 auPT乌兰县 cBRF祁连县 bKR8刚察县 bNSb门源回族自治县 aKTm民和回族土族自治县 aTTO乐都县 a6TG化隆回族自治县 ZuT2尖扎县 aUT7平安县 aoSv互助土族自治县 aUSY湟中县 a3SQ贵德县 afSG湟源县 ZZRj贵南县 ZVT1同仁县 asRx海晏县 Z2SS泽库县 YiSa河南蒙古族自治县 ZpTT循化撒拉族自治县 XQST久治县 WuRi班玛县 auSf大通回族土族自治县",
	"山东省 aehx济南市 ZEgS菏泽市 aRgx聊城市 aDie莱芜市 aCi5泰安市 ZPhZ济宁市 YniJ枣庄市 Z3jL临沂市 ZPkV日照市 a4lN青岛市 agk9潍坊市 anj3淄博市 bNiw滨州市 bQje东营市 bRhI德州市 bRmQ烟台市 bVn7威海市 bUn7环翠区 ZwlB黄岛区 aIlM城阳区 a9lQ李沧区 a6lS崂山区 a6lL四方区 a5lN市北区 a4lN市南区 bNma牟平区 bUmF福山区 bUmQ莱山区 bWmN芝罘区 aekA坊子区 ahk7奎文区 ahk6潍城区 akkD寒亭区 bSjU东营区 brjW河口区 bRhI德城区 apgg临清市 aRgx东昌府区 aXhi长清区 adhu槐荫区 afi4历城区 aei5历下区 adhy市中区 afhx天桥区 a4im钢城区 aCid莱城区 bNj0滨城区 anjI临淄区 amiq周村区 anj2张店区 aUip博山区 aBhy岱岳区 aBi8泰山区 ZFgQ牡丹区 ZPhZ任城区 ZOhZ市中区 YYii台儿庄区 YmiF薛城区 YkiZ峄城区 YqiY市中区 Z5iR山亭区 Z4jK兰山区 YxjH罗庄区 Z5jO河东区 Z6kK岚山区 ZPkR东港区 aBhk肥城市 auhc禹城市 ahiW章丘市 ZZhx曲阜市 ZXho兖州市 ZOhw邹城市 Z5i9滕州市 ZykO诸城市 aQkC安丘市 aNkj高密市 Zql2胶南市 aNlR即墨市 aGl2胶州市 alkv平度市 bBku莱州市 aqkO昌邑市 arji寿光市 afjS青州市 Ztik新泰市 bMlO招远市 biiE乐陵市 bnlj蓬莱市 bdlV龙口市 bIlo栖霞市 bAnP荣成市 bCn3文登市 atmW乳山市 alm9海阳市 aqlU莱西市 axlg莱阳市 Z4gY定陶县 YogW曹县 Ymh5单县 ZOh5巨野县 Yvgr成武县 Zagu郓城县 Zmh5梁山县 ZYgU鄄城县 ZHg5东明县 aTgQ冠县 avgy夏津县 bDh4武城县 aqhE高唐县 aZhF茌平县 aKhF东阿县 a7gl阳谷县 aEge莘县 ZuhS东平县 aHhR平阴县 amhj齐河县 bAhQ平原县 bBhq临邑县 axiD济阳县 ZUic平邑县 ZeiG泗水县 Zkhm宁阳县 ZihT汶上县 ZPhK嘉祥县 Z4hI金乡县 Yyhd鱼台县 Yni8微山县 YbjL郯城县 Ypj3苍山县 ZGiw费县 Zhiu蒙阴县 ZBjo莒南县 ZZjo莒县 ZXjS沂南县 Zljb沂水县 Ytjd临沭县 ZjkC五莲县 b4jO广饶县 agjn昌乐县 aVjW临朐县 aBjA沂源县 awj5桓台县 b9j8博兴县 bAin高青县 arii邹平县 bgj8沾化县 bZjX垦利县 bTjF利津县 biia无棣县 bciZ阳信县 bTiU惠民县 bJi9商河县 bliN庆云县 bdhl宁津县 bKhY陵县 btli长岛县",
	"山西省 bqdX太原市 Z1bx运城市 a5cV临汾市 ZUdo晋城市 aCe7长治市 bpeY阳泉市 e5eI大同市 dKdQ朔州市 cPdi忻州市 bfdj晋中市 bVc8吕梁市 e0e8南郊区 eGe9新荣区 e2eA矿区 e5eH城区 dKdQ朔城区 cPdi忻府区 bueZ郊区 bqeY矿区 bpea城区 bVc8离石区 bidT晋源区 bidY小店区 budT尖草坪区 bqdV万柏林区 bqdY迎泽区 brdY杏花岭区 aCe7郊区 aDe7城区 ZUdo城区 a5cV尧都区 Z1bx盐湖区 YqbQ永济市 ZbcL侯马市 Zabg河津市 aYch霍州市 b2ct介休市 b9ck孝义市 bGcl汾阳市 Zmdt高平市 aKeD潞城市 cidg原平市 btdA古交市 bfdj榆次区 Z9bk临猗县 Ygbf芮城县 YocD平陆县 Z9cD夏县 Zabw稷山县 ZbcD新绛县 ZLcD闻喜县 ZTcY绛县 ZccS曲沃县 ZrcQ襄汾县 Zwbo乡宁县 ZPbo万荣县 a6bf吉县 aSbj大宁县 aPc5蒲县 agbu隰县 aybo石楼县 akbc永和县 awcC交口县 bKcB中阳县 adcY汾西县 aFce洪洞县 aGct古县 a9dF安泽县 aUdK沁源县 apck灵石县 bBdA平遥县 ajdg沁县 bLdK祁县 b4dw榆社县 aodp武乡县 aWe3襄垣县 aJdr屯留县 a3e2长治县 ZUdo泽州县 ZTdP阳城县 a7dq长子县 ZfdB沁水县 Zwco浮山县 Zich翼城县 ZIce垣曲县 ZleG陵川县 aCeQ平顺县 a7eC壶关县 aUeN黎城县 bKeY和顺县 b4eM左权县 bmeb平定县 bbeg昔阳县 breB寿阳县 cieF五台县 c5eO盂县 dkfH广灵县 dgef浑源县 dQfE灵丘县 dBeF繁峙县 dXeB应县 doe5怀仁县 e2ea大同县 dVdn山阴县 e0dg左云县 dxdS右玉县 d5dC神池县 cscp五寨县 d0dI宁武县 d4dv代县 cTdv定襄县 bPdX太谷县 c4de阳曲县 badL清徐县 bXd9交城县 bQd1文水县 c4cl娄烦县 cHce岚县 cMcu静乐县 cgcY岢岚县 cSc7兴县 brcE方山县 bvbx临县 eMej阳高县 ePf5天镇县 bQbs柳林县 dQcU偏关县 dNc8河曲县",
	"陕西省 YGZu西安市 YMY8宝鸡市 X4Y1汉中市 Wfa1安康市 Xqau商洛市 YUaU渭南市 YKZg咸阳市 YsZu铜川市 aaaT延安市 cHai榆林市 YMYM陈仓区 YNY8金台区 YMY9渭滨区 X4Y2汉台区 Wfa1汉滨区 Xqau商州区 YdaE阎良区 YHZu未央区 YGZu莲湖区 YGZv新城区 YEZu碑林区 YDZv雁塔区 YAZu长安区 YGa4灞桥区 YMaD临潼区 YLZh秦都区 YKZi渭城区 YHZ4杨凌区 Z6a6印台区 Z4a4王益区 YtZx耀州区 YUaT临渭区 aaaT宝塔区 cHaj榆阳区 YIZT兴平市 YYb5华阴市 ZTbQ韩城市 X9Xe勉县 WoXF宁强县 XKX9略阳县 XtXV凤县 XDYX洋县 XbXt留坝县 YVYN凤翔县 Y4YJ太白县 YHYj眉县 YMYq扶风县 YRYb岐山县 YWZE乾县 YGZC武功县 YAZC周至县 XWYx佛坪县 X3ZF石泉县 WWYs镇巴县 WxYk西乡县 X9YK城固县 X0Xu南郑县 WVZW紫阳县 WJZs岚皋县 WsZU汉阴县 WoaN旬阳县 WOaL平利县 VraV镇坪县 Wnb6白河县 XWar山阳县 XgbK丹凤县 XWbr商南县 YXbE潼关县 Y5b8洛南县 YVak华县 YWa5高陵县 Y9aJ蓝田县 Xfa6柞水县 XQa9镇安县 XJZJ宁陕县 Y6Za户县 YWZo泾阳县 YbZu三原县 YTZP礼泉县 YlZZ淳化县 Z7ZK旬邑县 ZZaF黄陵县 ZOa7宜君县 ZkaQ洛川县 YjaB富平县 Ymau大荔县 ZBaZ白水县 YvaZ蒲城县 ZEb9合阳县 ZBau澄城县 ZZao黄龙县 aZb0延长县 a3bA宜川县 b5b7清涧县 arbB延川县 b8ae子长县 aqaJ安塞县 ZxaM富县 aHaL甘泉县 anZk志丹县 auZA吴起县 Z2Z5彬县 YgZ8永寿县 YfYl麟游县 ZCYl长武县 YdY8千阳县 YsXp陇县 bZYa定边县 d2c4府谷县 d1c5保德县 cobU神木县 bvaH横山县 baZm靖边县 bbb2子洲县 bUbF绥德县 bjbB米脂县 bRbi吴堡县 c1bT佳县",
	"上海市 VEmS上海市 UjmK金山区 UtmS奉贤区 V2mD松江区 V7mN闵行区 VBmQ徐汇区 VDmP长宁区 VFmR闸北区 VEmT黄浦区 VDmS卢湾区 VEmR静安区 VDmW浦东新区 VGmV杨浦区 VGmU虹口区 VFmO普陀区 V9m7青浦区 VNmG嘉定区 VOmT宝山区 V3mj南汇区 VbmO崇明县",
	"四川省 UeV4成都市 QZSh攀枝花市 RsTG凉山彝族自治州 U3Sw甘孜藏族自治州 VsTD阿坝藏族羌族自治州 WQWo广元市 VpXk巴中市 VDYU达州市 UlX5南充市 USXc广安市 UVWY遂宁市 VSVi绵阳市 V8VN德阳市 U3Uo眉山市 TxTy雅安市 TYUk乐山市 TLVl自贡市 TZW3内江市 U7Vd资阳市 SqWQ泸州市 SkVb宜宾市 U7Vd雁江区 TZW3市中区 TaW4东兴区 TLVh贡井区 TLVk自流井区 TMVk大安区 TGVq沿滩区 SkWM纳溪区 SsWQ龙马潭区 SrWR江阳区 SkVb翠屏区 TPUX沙湾区 TOUn五通桥区 TYUk市中区 TFU5金口河区 U3Uo东坡区 TxTy雨城区 UrVE青白江区 UoV9新都区 UYVG龙泉驿区 UeV6成华区 UeV5锦江区 UgV3金牛区 UfV3青羊区 UdV3武侯区 UgUo温江区 V8VN旌阳区 UVWY船山区 ULWR安居区 VpXk巴州区 VDYT通川区 UkX3嘉陵区 UkX6高坪区 UlX5顺庆区 WdWr朝天区 WQWo利州区 WJWw元坝区 VSVj游仙区 VSVi涪城区 QaSa西区 QUSi仁和区 QXSg东区 RsTG西昌市 VlVj江油市 W4Z2万源市 UNXk华蓥市 VXWy阆中市 UOVX简阳市 VLVC绵竹市 V8VA什邡市 V0Ub都江堰市 UPUS邛崃市 UcUe崇州市 UxUu彭州市 UxVH广汉市 TaUT峨眉山市 SoVK屏山县 WZWE青川县 ShQH得荣县 RQSU盐源县 QgSp盐边县 QeTF会理县 QcTZ会东县 R4Tk宁南县 RNTW普格县 ROTB德昌县 QrT7米易县 RhTn布拖县 S1Tp昭觉县 SJTP喜德县 SdTV越西县 SXTA冕宁县 T0SU九龙县 RuSH木里藏族自治县 T2RI稻城县 TyRG理塘县 U2S1雅江县 U3Sw康定县 TETM石棉县 SwTk甘洛县 TLTd汉源县 U4Tj天全县 TmTp荥经县 U9Tt芦山县 TtTE泸定县 UrSr丹巴县 V0TM小金县 UMTn宝兴县 VTT4金川县 UxS7道孚县 UvRJ新龙县 VORf炉霍县 VbQx甘孜县 VnPZ德格县 VDPo白玉县 U0Q6巴塘县 SuQm乡城县 WxP6石渠县 XZTv若尔盖县 WsSg阿坝县 WGRK色达县 WGRx壤塘县 WmTX红原县 VsTD马尔康县 W4Tx黑水县 WcUa松潘县 VnVR北川羌族自治县 WPVW平武县 WHWV剑阁县 XGVE九寨沟县 WEXH旺苍县 ViWu苍溪县 WLXo南江县 VtYE通江县 VCYU达县 VLYh宣汉县 V5Yq开江县 UyWr西充县 UXXQ岳池县 ULXH武胜县 UKXu邻水县 UiYC大竹县 UoXw渠县 V5XY营山县 VYY6平昌县 V2XP蓬安县 VGXH仪陇县 VLX4南部县 VcWA梓潼县 VDWN盐亭县 UlWh蓬溪县 UZWF大英县 UqWN射洪县 UpVQ金堂县 VJVU罗江县 V2Vf中江县 V6W5三台县 VWVY安县 VfUp茂县 VTUZ汶川县 VQUA理县 UZUV大邑县 UPUn新津县 UZUt双流县 UnUr郫县 TyV9仁寿县 TdV4井研县 ToUp青神县 UCUq彭山县 UCUU蒲江县 U5U7名山县 TtUM洪雅县 U1UV丹棱县 TiUY夹江县 TEUG峨边彝族自治县 SwUs沐川县 TDUv犍为县 TBVx富顺县 TWVe威远县 TSVP荣县 TlVp资中县 UHW1乐至县 U6WK安岳县 T9WN泸县 TLWH隆昌县 SIWE兴文县 SAWQ叙永县 SAVV筠连县 SQVV高县 SRVh珙县 SZVt长宁县 SiW4江安县 SpVx南溪县 SgVX宜宾县 S3Wn古蔺县 SnWo合江县 SKU8美姑县 SGUY雷波县 RgUF金阳县 SoUX马边彝族自治县",
	"天津市 d7iC天津市 d2if滨海新区 d8i0西青区 d7iD河西区 d8i9南开区 dAi9红桥区 dDi8北辰区 d9iB河北区 d7iC和平区 d7iD河东区 d5iI东丽区 cxiN津南区 coiR大港区 dFim汉沽区 d1id塘沽区 dhiI宝坻区 dNi2武清区 cuht静海县 dKin宁河县 e3iO蓟县",
	"西藏自治区 TdI8拉萨市 WU76阿里地区 TGFr日喀则地区 TfLM林芝地区 VTJ4那曲地区 TEIk山南地区 V8OB昌都地区 XCFo双湖特别区 TGFr日喀则市 TdI8城关区 VT6m札达县 WO87革吉县 UI8A普兰县 TKCE萨嘎县 SpCI吉隆县 SACx聂拉木县 RTFs亚东县 T7GG白朗县 StGa江孜县 TfG6南木林县 TQFG谢通门县 T5Ec拉孜县 SsF1萨迦县 SHFV岗巴县 SMEk定结县 SeE7定日县 TIEE昂仁县 UuFg申扎县 VlEE尼玛县 V1CA措勤县 TkB2仲巴县 WIB4改则县 WU76噶尔县 XN6h日土县 UuLg边坝县 TrKF工布江达县 UdKF嘉黎县 VTKf比如县 VuL2巴青县 VrKl索县 W7JI聂荣县 VTJ4那曲县 WGIf安多县 VMH1班戈县 TdHy堆龙德庆县 UTI6当雄县 TRH9尼木县 TfIL达孜县 TsIF林周县 ToIi墨竹工卡县 TEIk乃东县 TGJ1桑日县 T4JC曲松县 T2If琼结县 RyIv错那县 SQIQ措美县 TFIK扎囊县 SNHq洛扎县 TMHi曲水县 TIHx贡嘎县 SwHO浪卡子县 TEGo仁布县 SYGf康马县 T9JZ加查县 SPJS隆子县 T3K4朗县 TDLD米林县 TfLM林芝县 SeOS察隅县 TKMK墨脱县 TqMk波密县 UjMo洛隆县 UqPG贡觉县 VUPD江达县 TfPa芒康县 VDNa类乌齐县 TeOp左贡县 VPMa丁青县 V8OB昌都县 U3Nt八宿县 UdOY察雅县",
	"新疆维吾尔 hnEb乌鲁木齐市 dh3A克孜勒苏柯尔克孜自治州 dS2x喀什地区 fA7G阿克苏地区 ht8J伊犁哈萨克自治州 is94博尔塔拉蒙古自治州 b76t和田地区 goKV哈密地区 gvGA吐鲁番地区 fkD9巴音郭楞蒙古自治州 i1EI昌吉回族自治州 jaBq克拉玛依市 kj9x塔城地区 lpF8阿勒泰地区 hoEc水磨沟区 hpEa新市区 hqEP头屯河区 hvEf东山区 hwEd米泉市 jaBq克拉玛依区 iJBp独山子区 dh3A阿图什市 dS2x喀什市 fA7G阿克苏市 eX8H阿拉尔市 ht8J伊宁市 is94博乐市 dp68图木舒克市 b76t和田市 goKV哈密市 iAEW五家渠市 i9Ex阜康市 gvGA吐鲁番市 fkD9库尔勒市 i1EI昌吉市 iID2石河子市 iPBs奎屯市 iQBf乌苏市 kj9x塔城市 lpF8阿勒泰市 k5Cf乌尔禾区 jgC8白碱滩区 bb5H皮山县 cP4E莎车县 cB4G泽普县 br4P叶城县 cs4d麦盖提县 dl5X巴楚县 dE3k岳普湖县 dO33疏勒县 dN2p疏附县 dh2F乌恰县 d92v阿克陶县 cu3A英吉沙县 bl2E塔什库尔干塔吉克自治县 dU3i伽师县 eu5R阿合奇县 eU63柯坪县 fD6E乌什县 fH7E温宿县 ec7N阿瓦提县 iw82温泉县 i37r霍城县 hx8V伊宁县 ho89察布查尔锡伯自治县 h988昭苏县 hD8o特克斯县 hT9E巩留县 hQAF新源县 hl9U尼勒克县 ia9r精河县 flBG轮台县 fm8q拜城县 fX9a新和县 fh9w库车县 fD9l沙雅县 bG6i墨玉县 ap8e于田县 b07m策勒县 b47B洛浦县 b66u和田县 b49f民丰县 c8CW且末县 d1FA若羌县 hFLg伊吾县 haK1巴里坤哈萨克自治县 hoHH木垒哈萨克自治县 glFd托克逊县 hyGB吉木萨尔县 i1GZ奇台县 gqHD鄯善县 gGDq和硕县 gJDO和静县 g4DY焉耆回族自治县 fxDc博湖县 fKDF尉犁县 hmEa乌鲁木齐县 iIDD玛纳斯县 iBDs呼图壁县 iKCb沙湾县 kmCh和布克赛尔蒙古自治县 lQCr吉木乃县 lgDp布尔津县 m4DP哈巴河县 kyGV富蕴县 l7EU福海县 kWAc额敏县 keHN青河县 juAa托里县 hLFI达坂城区 hlEa沙依巴克区 hlEd天山区 kC9x裕民县",
	"云南省 P3Th昆明市 NrR5临沧市 M1Rm西双版纳傣族自治州 MlRw普洱市 P2SX楚雄彝族自治州 OLTX玉溪市 PaRE大理白族自治州 P7QA保山市 OQPZ德宏傣族景颇族自治州 PpPp怒江傈僳族自治州 QrRE丽江市 RoQg迪庆藏族自治州 RKUh昭通市 PUUm曲靖市 NMVF文山壮族苗族自治州 NMUO红河哈尼族彝族自治州 MlRw普洱市 NrR5临翔区 P7QA隆阳区 QrRE古城区 P2Te西山区 P3Tg五华区 P2Th盘龙区 P1Tj官渡区 Q5UB东川区 RKUh昭阳区 PUUm麒麟区 M1Rm景洪市 P2SX楚雄市 OtTT安宁市 PaRE大理市 OQPZ潞西市 O1Op瑞丽市 QDV6宣威市 NhUG开远市 NMU9个旧市 SaUv绥江县 ScVO水富县 NlPo镇康县 N9QF沧源佤族自治县 NXQO耿马傣族佤族自治县 NSQo双江拉祜族佤族布朗族傣族自治县 McQb西盟佤族自治县 MXQu澜沧拉祜族自治县 LwRR勐海县 MKQZ孟连傣族拉祜族佤族自治县 LTSY勐腊县 MZSp江城哈尼族彝族自治县 MyTO绿春县 NETo元阳县 NbTo建水县 NhTU石屏县 NMTP红河县 NaT0元江哈尼族彝族傣族自治县 NQSf墨江哈尼族自治县 N4S3宁洱哈尼族彝族自治县 NURg景谷傣族彝族自治县 ORRo景东彝族自治县 P3RV南涧彝族自治县 PCSG南华县 OgSc双柏县 O0S6镇沅彝族哈尼族拉祜族自治县 O4Sx新平彝族傣族自治县 OBTO峨山彝族自治县 O7Tj通海县 OCTu华宁县 OHTj江川县 OeTa晋宁县 OeTt澄江县 OrTm呈贡县 PDTU富民县 P9T5禄丰县 OeTA易门县 PgSr元谋县 PWTO武定县 PXTS禄劝彝族苗族自治县 PLU2嵩明县 QcSG华坪县 Q4Se永仁县 PJSW牟定县 PUSE姚安县 PiSJ大姚县 PTRX祥云县 PLRT弥渡县 PoRZ宾川县 QfRj永胜县 QYRB鹤庆县 Q7Qv洱源县 QWQs剑川县 QRQP兰坪白族普米族自治县 PrQM云龙县 PSQW永平县 PeQv漾濞彝族自治县 PERI巍山彝族回族自治县 ORR8云县 OaQt凤庆县 O2QF永德县 OiQB施甸县 OoQa昌宁县 P2PU腾冲县 OnPI梁河县 OZPf龙陵县 OCOm陇川县 OhOu盈江县 PpPp泸水县 RiPe贡山独龙族怒族自治县 QsPq福贡县 RBQH维西傈僳族自治县 QnRE玉龙纳西族自治县 RoQg香格里拉县 STPt德钦县 RHRp宁蒗彝族自治县 QtTt巧家县 RCUX鲁甸县 RcV3彝良县 RjUr大关县 S7VE盐津县 RpW3威信县 RRVq镇雄县 SEUc永善县 QPUI会泽县 PYUF寻甸回族彝族自治县 PbUn沾益县 PQUZ马龙县 PeVF富源县 OrVI罗平县 OoUx师宗县 P2Ue陆良县 OtU9宜良县 OkUG石林彝族自治县 OWUk泸西县 OOUQ弥勒县 O3VB丘北县 O3W4广南县 NcWb富宁县 N7Vg麻栗坡县 NRVe西畴县 NbVK砚山县 NMVF文山县 NMUO蒙自县 MVUw河口瑶族自治县 N1VO马关县 MxUf屏边苗族自治县 MlUD金平苗族瑶族傣族自治县",
	"浙江省 UHl9杭州市 UFlA上城区 UHlA下城区 UJl8拱墅区 UGlC江干区 UGl8西湖区 UClC滨江区 UAlG萧山区 UPlI余杭区 UEkh临安市 Tmke桐庐县 U3kv富阳市 TTkH建德市 Tak2淳安县 TrmX宁波市 TqmX海曙区 TqmY江东区 TrmX江北区 Tump北仑区 Tvmh镇海区 TomW鄞州区 U2m9余姚市 UAmE慈溪市 TdmO奉化市 THmQ宁海县 TTmq象山县 Rylg温州市 S1ld鹿城区 Ruln龙湾区 S1lc瓯海区 Rllc瑞安市 S9lf永嘉县 S8lv乐清市 RelY平阳县 RUlO苍南县 Rll5文成县 RYkh泰顺县 Rom9洞头县 U0lY绍兴市 U0lY越城区 U5lS绍兴县 U2lq上虞市 TZln嵊州市 TUls新昌县 ThlE诸暨市 Ujlj嘉兴市 Uklj南湖区 Uklg秀洲区 UWlf海宁市 Uplt嘉善县 UWlv海盐县 UclY桐乡市 Ugm1平湖市 Usl5湖州市 Uql7吴兴区 UrlQ南浔区 UWkw德清县 V1ks长兴县 Uckf安吉县 T5kd金华市 T5kd婺城区 T5kg金东区 TDkR兰溪市 Ssl2永康市 Sskn武义县 THlE东阳市 T3lQ磐安县 TIl4义乌市 TRkr浦江县 Sujq衢州市 Sujq柯城区 Sxju衢江区 Sjjb江山市 SsjV常山县 T2kA龙游县 T8jP开化县 TynC舟山市 U1n6定海区 TvnI普陀区 UFnC岱山县 UinR嵊泗县 SfmQ台州市 SfmQ椒江区 SdmG黄岩区 SZmN路桥区 Spm7临海市 SkmU杜桥镇 SMmM温岭市 Sqli仙居县 T8m2天台县 T7mN三门县 S8mE玉环县 SRkt丽水市 SRkt莲都区 S9lH青田县 S7kY云和县 S5k8龙泉市 Rbk3庆元县 Sdl4缙云县 SakG遂昌县 SRkT松阳县 Rxkc景宁畲族自治县",
	"重庆市 TYXX重庆市 UKYL垫江县 TTWl双桥区 TLWs永川区 TIXF江津区 TWXR沙坪坝区 TTXT大渡口区 TUXU九龙坡区 TaXY江北区 TVXY南岸区 TXXY渝中区 TNXV巴南区 TAY6南川区 SwXt万盛区 TqY5长寿区 ThYO涪陵区 ThXc渝北区 TmXO北碚区 TxXG合川区 UnZO万州区 TWZk黔江区 TOWZ荣昌县 T2Xd綦江县 TKYj武隆县 TqYi丰都县 UIZ1忠县 UfYm梁平县 TaXD璧山县 TpX3铜梁县 UBWo潼南县 TgWh大足县 VBZP开县 VvZe城口县 VOac巫溪县 V1aS奉节县 V5ar巫山县 UvZe云阳县 U0Z7石柱土家族自治县 TIZA彭水苗族土家族自治县 SpZk酉阳土家族苗族自治县 SRZx秀山土家族苗族自治县",
	"港澳台 MCf5香港 M8eK澳门 P2mU台北市 MblH高雄市 P8mi基隆市 O9le台中市 N0lC台南市 Onlv新竹市 NTlQ嘉义市 P1mS台北县 Okmj宜兰县 OwmI桃园县 OWlm苗栗县 OFlh台中县 O5lW彰化县 Ntle南投县 NhlW云林县 NJlJ台南县 MclM高雄县 MelT屏东县 Mjm9台东县 Nxma花莲县 NZkZ澎湖县	"
	};

/****************
 [地理经纬度数据库]

 经纬度的压缩编码细节(以经度79度48分 北纬12度49分 为例,):
 字元表 s = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; 共62个字元
 数字0 编码为s中的第1个字符(0)
 数字1 编码为s中的第2个字符(1)
 数字10编码为s中的第11个字符(A)
 数字59编码为s中的第60个字符(x)
 ...
 1.将"度"减去73，即79-73 = 6，因为我国各地经度在73到133度之间,减73之后,经度就变为0到60之间的数
 2.使用字元表对 "6度"进行编码,得到字符6,编码后只用一个字母就可以表示"度"
 3.使用字元表对"48分"进行编码,得到字符m,编码后只用一个字母就可以表示"分"
 4.最后，79度48分被编码为 6m
 5.同样方法对纬度编码(但不用减73)得到 Cn
 6.经纬度的总编码为(纬度放在前) Cn6m
 7.解码过程是上面过程的逆运算。通过以上处理，比常规表示法减少60%的数据量
*****************/
JINGWEI GeographicalPosition(void) 
{
	JINGWEI jw0={116.3833333,39.000,"默认","北京"};
	JINGWEI jw = {};
	char ch[32][210][48]={};
	for (int i=0;i<32;i++)
	{
		for (int j=0,m=0,k=0;k<strlen(JW[i]);k++)
   	 {
   	 	if (JW[i][k]==32)
    		{
    			j++;
    			m=0;
    			continue;
    		}
        	if (!isalnum(JW[i][k])&&JW[i][k]!=32)
    		ch[i][j][m++]=JW[i][k];
    	}
	}
	for (int j=0;j<32;j++)
	{
		printf("\033[31;1m%02d \033[0;33m%-s\t",j+1,ch[j][0]);
		if ((j+1)%3==0)
		printf("\n");
	}
	
	printf("\n\033[32m请选择您所在的省市，输入'0'手动输入区/县查找");
	int num,num0;
	char str[48];
	scanf("%d",&num);
	clrscr();
	if (num==0)
	{
		printf("\n\033[37m请输入您所在的区/县:");
		scanf("%s",str);
	}
	else if (num < 33)
	{
		num>32?num%=33:0;
		num--;
		for (int i=1;ch[num][i][0];i++)
		{
			printf("\033[35;1m%02d\033[0;36m%-8s  ",i,ch[num][i]);
			if (i%5==0)
				printf("\n");
		}
		printf("\n\033[32m(若显示不全请收起输入法)\n请选择您所在的区县，'0'手动输入区/县查找");
		scanf("%d",&num0);
		if (num0==0)
		{
			printf("\n\033[37m请输入您所在的区/县:");
			scanf("%s",str);
		}
		else strcpy(str,ch[num][num0]);
	}
	
	clrscr();

	for (int i=0;i<32;i++)
	{
    	const char *s=strstr(JW[i]+8,str);
    	if (s)
    	{
    		strcpy(jw.s,ch[i][0]);
    		strcpy(jw.x,str);
    		char a[4]={(s-4)[0],(s-3)[0],(s-2)[0],(s-1)[0]};
    	    for (int i=0;i<4;i++)
    	    { //对经纬度解压缩
     	        if (a[i]>96) a[i] -= 97-36;
    	         else if (a[i]>64) a[i] -= 65-10;
    	         else a[i] -= 48;
     	   }
            jw.J = (a[2]+a[3]/60.0+73);
            jw.W = (a[0]+a[1]/60.0);
        	break;
    	}
    	else if (i==31)
    	{
    		printf("查找失败,已设置为默认位置\n");
    		return jw0;
    	}
	}
	return jw;
}

//入参num省市，num0区县
JINGWEI GeographicalPosition(int num, int num0) 
{
	JINGWEI jw0={116.3833333,39.000,"默认","北京"};
	JINGWEI jw = {};
	char str[48];
	char ch[32][210][48]={};
	strcpy(str,ch[num][num0]);

	for (int i=0;i<32;i++)
	{
    	const char *s=strstr(JW[i]+8,str);
    	if (s)
    	{
    		strcpy(jw.s,ch[i][0]);
    		strcpy(jw.x,str);
    		char a[4]={(s-4)[0],(s-3)[0],(s-2)[0],(s-1)[0]};
    	    for (int i=0;i<4;i++)
    	    { //对经纬度解压缩
     	        if (a[i]>96) a[i] -= 97-36;
    	         else if (a[i]>64) a[i] -= 65-10;
    	         else a[i] -= 48;
     	   }
            jw.J = (a[2]+a[3]/60.0+73);
            jw.W = (a[0]+a[1]/60.0);
        	break;
    	}
    	else if (i==31)
    	{
    		printf("查找失败,已设置为默认位置\n");
    		return jw0;
    	}
	}
	return jw;
}

JINGWEI GeographicalPosition(const char *area) 
{
	JINGWEI jw0={116.3833333,39.000,"默认","北京"};
	JINGWEI jw = {};
	char ch[32][210][48]={};
	for (int i=0;i<32;i++)
	{
		for (int j=0,m=0,k=0;k<strlen(JW[i]);k++)
   	 {
   	 	if (JW[i][k]==32)
    		{
    			j++;
    			m=0;
    			continue;
    		}
        	if (!isalnum(JW[i][k])&&JW[i][k]!=32)
    		ch[i][j][m++]=JW[i][k];
    	}
	}
	
	for (int i=0;i<32;i++)
	{
    	const char *s=strstr(JW[i]+8,area);
    	if (s)
    	{
    		strcpy(jw.s,ch[i][0]);
    		strcpy(jw.x,area);
    		char a[4]={(s-4)[0],(s-3)[0],(s-2)[0],(s-1)[0]};
    	    for (int i=0;i<4;i++)
    	    { //对经纬度解压缩
     	        if (a[i]>96) a[i] -= 97-36;
    	         else if (a[i]>64) a[i] -= 65-10;
    	         else a[i] -= 48;
     	   }
            jw.J = (a[2]+a[3]/60.0+73);
            jw.W = (a[0]+a[1]/60.0);
        	break;
    	}
    	else if (i==31)
    	{
    		printf("查找失败,已设置为默认位置\n");
    		return jw0;
    	}
	}
	return jw;
}
