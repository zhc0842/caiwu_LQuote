
//单次请求的最大行数
#define MY_ROWCOUNT 200L
//请求的起始索引
#define MY_BROWINDEX 0L
//#define MY_KHH "000707005891" //查询jy
//#define MY_KHH "005353005168" //查询hg
//#define MY_KHH "003737004885" //查询mr mc rq rqgh sg

//#define MY_Addr "192.168.35.170@9103/tcp"
//#define MY_User "003636000306"
//#define MY_Pwd "123321"
//#define MY_TimeOut 10

#define MY_KHH "khh"
#define MY_User "user"
#define MY_Pwd "pwd"
#define MY_Addr "addr"
#define MY_Port "port"
#define MY_Protocol "protocol"
#define MY_TimeOut "timeout"
#define MY_KSRQ "ksrq"
#define MY_JSRQ "jsrq"
#define MY_DestDir "destDir"

#define MY_WTLB_MR 1L //买入
#define MY_WTLB_SG 16L //送股

#define MY_WTLB_MC 2L //卖出
#define MY_WTLB_RZ 4L //融资
#define MY_WTLB_RQ 5L //融券
#define MY_WTLB_RZGH 34L //融资购回
#define MY_WTLB_RQGH 35L //融券购回

#define MY_PK_OPERATIONCODE_MR "40000"
#define MY_PK_OPERATIONCODE_MC "40001"
#define MY_PK_OPERATIONNAME_MR "股票买入"
#define MY_PK_OPERATIONNAME_MC "股票卖出"
#define MY_PK_CORP "9001"
#define MY_PK_OPERATIONCODE_HG "40006"
#define MY_PK_OPERATIONCODE_GH "40009"
#define MY_PK_OPERATIONNAME_RQHG "融券回购"
#define MY_PK_OPERATIONNAME_RQGH "融券购回"
#define MY_PK_PARTER "D890767292"
#define MY_SEPARATOR ","
#define MY_BOURSECODE_SH "101"
#define MY_BOURSECODE_SZ "102"
#define MY_JYS_SH "SH"
#define MY_JYS_SZ "SZ"

#define MY_YWKM_YZZZ_C 10113 //银证转账存
#define MY_YWKM_YZZZ_Q 10213 //银证转账取
#define MY_YWKM_XHLXRBJ 10501 //销户利息入本金
#define MY_YWKM_JDLXRBJ 10503 //季度利息入本金

#define MY_YWKM_HGHCZJ 13021 //回购融券成交划出资金
#define MY_YWKM_GHHRZJ 13122 //回购融券购回资金划入
#define MY_YWKM_MRHCZJ 13001 //买入成交清算资金
#define MY_YWKM_MCHRZJ 13101 //卖出成交清算资金

#define MY_PK_OPERATIONCODE_ZJZJ "20300"
#define MY_PK_OPERATIONCODE_JSZJ "20301"
#define MY_PK_OPERATIONCODE_LXSR "2030001"
#define MY_PK_OPERATIONNAME_ZJZJ "增加资金"
#define MY_PK_OPERATIONNAME_JSZJ "减少资金"
#define MY_PK_OPERATIONNAME_LXSR "利息收入"

#include "apex/blsdef_3rd.h"
#include "apex/FixApi.h"

#include "direct.h"

#include <CSTDLIB>
#include <CSTRING>
#include <algorithm>
#include <list>
#include <MAP>
#include <IOMANIP>
#include <FSTREAM>
#include <iostream>

using namespace std;

map<string, string> cfg_map;



//资金明细403201
struct ZJMXLS
{
	//long fid_code;//返回码
	//char fid_message[256];//返回错误说明
	char fid_browindex[130];//当前分页索引值

	long fid_seqno;//流水号
	long fid_rq;//发生日期
	long fid_rzrq;//入账日期
	double fid_srje;//收入金额
	double fid_fcje;//付出金融
	double fid_bczjye;//本次资金余额
	long fid_sqfs;//申请方式

	char fid_fsyyb[6];//发生营业部
	char fid_node[32];//操作站点 20
	char fid_zjly[6];//资金来源 2
	char fid_xgdm[12];//相关代码
	char fid_yyb[6];//营业部
	char fid_gsfl[4];//公司分类
	char fid_bz[6];//币种
	char fid_zy[82];//摘要
	char fid_czbz[3];//冲账标志
	char fid_zjzh[32];//资金账号
	char fid_ywkm[8];//业务科目 4
	char fid_wbzh[32];//外部账号
	char fid_khqz[4];//客户群号

	long fid_ywsqh;//业务申请号

	char fid_khh[14];//客户号
	char fid_khxm[18];//客户姓名
	char fid_fssj[10];//发生时间
	char fid_fhgy[10];//复核柜员

	long fid_lsh;//流水号
};

//持仓304101
struct CC
{
	//long fid_code;//返回码
	//char fid_message[256];//返回错误说明
	char fid_zqmc[10];//证券名称
	char fid_jys[4];//交易所

	char fid_gdh[12];//股东号

	long fid_zqsl;//证券数量
	char fid_zqdm[8];//证券代码
	char fid_zqlb[4];//证券类别
	long fid_jydw;//交易单位 FID_EXFLG=1时有效
	char fid_bz[6];//币种
	long fid_drmrwtsl;//当日买入委托数量
	long fid_bdrq;//最近变动日期
	double fid_bbj;//保本价 FID_EXFLG=1时有效
	long fid_pgsl;//配股数量
	double fid_lxbj;//利息报价
	long fid_drmcwtsl;//当日卖出委托数量
	double fid_pgje;//配股金额
	double fid_mrje;//买入金额
	double fid_mcje;//卖出金额
	long fid_mrsl;//买入数量
	long fid_kshsl;//可赎回数量
	long fid_ksgsl;//可申购数量
	long fid_kmcsl;//可卖出数量
	long fid_djsl;//冻结数量
	long fid_fltsl;//非流通数量
	long fid_jccl;//今持仓量
	long fid_wjssl;//未交收数量
	double fid_mrjj;//买入均价
	double fid_ccjj;//持仓均价
	double fid_tbcbj;//摊薄成本价
	double fid_ljyk;//累计盈亏
	double fid_fdyk;//浮动盈亏
	double fid_tbbbj;//摊薄保本价
	double fid_tbfdyk;//摊薄浮动盈亏
	double fid_zxsz;//最新市值
	double fid_zxj;//最新价
	long fid_kcrq;//开仓日期
	long fid_mcsl;//卖出数量
	double fid_drmrcjje;//当日买入成交金额
	long fid_drmrcjsl;//当日卖出成交金额
	double fid_drmccjje;//当日买入成交数量
	long fid_sgsl;//送股数量
	double fid_hlje;//红利金额
	long fid_drmccjsl;//当日卖出成交数量
	long fid_shcjsl;//赎回成交数量
	long fid_mcdxsl;//卖出抵消数量
	long fid_sgcjsl;//申购成交数量
	long fid_mrdxsl;//买入抵消数量
};

//交割明细404201
struct JGMXLS
{
	char fid_gdxm[18];//股东姓名
	char fid_jys[4];//交易所
	char fid_jszh[32];//结算帐户
	long fid_wtfs;//委托方式
	char fid_xwdm[8];//席位代码
	char fid_zqdm[8];//证券代码
	char fid_zqlb[4];//证券类别
	char fid_cjsj[10];//成交时间
	char fid_sbsj[10];//申报时间
	double fid_lxjg;//利息价格
	double fid_cjje;//成交金额
	double fid_lxje;//利息金额
	double fid_bzs1;//标志佣金
	double fid_s3;//过户费
	double fid_s5;//结算费
	double fid_bczjye;//本次资金余额
	double fid_bbyk;//本次盈亏
	char fid_loginid[14];//登录 ID
	char fid_fhgy[10];//审核柜员
	char fid_yyb[6];//营业部
	char fid_cjbh[32];//成交编号
	double fid_s1;//佣金
	double fid_s4;//附加费
	char fid_jsjg[6];//结算机构
	char fid_zqmc[10];//证券名称
	long fid_wtlb;//委托类别
	long fid_cjrq;//成交日期
	long fid_cjbs;//成交笔数
	long fid_cjsl;//成交数量
	double fid_cjjg;//成交价格
	double fid_jsj;//结算价
	double fid_s2;//印花税
	double fid_s6;//交易规费
	double fid_ysje;//应收金额
	long fid_bczqsl;//本次股份余额
	long fid_rzrq;//入帐日期

	char fid_bz[6];//币种
	long fid_jsrq;//交收日期
	long fid_yjdjcl;//佣金定价策略
	long fid_yjdjfs;//佣金定价方式
	char fid_browindex[130];//当前分页索引值

	char fid_gdh[12];//股东号
	long fid_djsl;//冻结数量
	long fid_dlsf;//登录身份
	long fid_bcdjsl;//本次冻结数量
	long fid_yssl;//应收数量

	char fid_zjmxlsh[12];//资金明细流水号 8

	char fid_khqz[4];//客户群组
	char fid_gsfl[4];//公司分类
	long fid_seqno;//流水号
	long fid_jgzllb;//交割资料类别
	long fid_wth;//委托号
	char fid_khxm[18];//客户姓名
	char fid_khh[14];//客户号
};



//系统状态101020
struct XTZT
{
	long fid_qsbz;//清算标志
	long fid_xtcsbz;//系统测试标志
	long fid_code;//返回码
	char fid_message[202];//返回错误说明
};


//查询历史资金明细
map<long, list<ZJMXLS>> Query_ZJMXLS(HANDLE_CONN, long, long);
//map<long, list<ZJMXLS>> Group_ZJMXLS(list<ZJMXLS>);
//查询持仓
list<CC> Query_CC(HANDLE_CONN);
//查询历史交割明细
map<long, list<JGMXLS>> Query_JGMXLS(HANDLE_CONN, long, long);
//map<long,list<JGMXLS>> Group_JGMXLS(list<JGMXLS>);

void Write_ZJMXLS(list<ZJMXLS>, char*, char*, char*);
void Write_ZJ(list<ZJMXLS>, char*, char*, char*);
void Write_CC(list<CC>, char*);
void Write_JGMXLS(list<JGMXLS>, char*, char*, char*);

void initZJMXLS(ZJMXLS);
void initCC(CC);
void initJGMXLS(JGMXLS);


bool checkDate(long nKsrq, long nJsrq);
//初始化char[] 即memset 0
void initCharArr(char[]);
//替换,为:
void repComma(char[]);
//转换double为char*
char* d2str(double, char[]);

LPCWSTR C2LPCWSTR(const char* str);
//拆分命令行参数
void Split_RQ(TCHAR[], TCHAR[]);
//产生文件名
string Get_FileName(char*, char*, char*);
//加载配置文件
map<string, string> Load_Configuration(char*);
//CString转换为string
string WChar2Ansi(LPCWSTR pwszSrc);
//保存完全执行成功后配置信息
void Save_Configuration(char* cfgFilePath);

//工具方法，转换根网交易日历为20150310格式
void write_TradeDates();
//获取最近1次交易日日期
string Get_QueryDate();
