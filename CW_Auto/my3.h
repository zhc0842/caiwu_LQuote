
//����������������
#define MY_ROWCOUNT 200L
//�������ʼ����
#define MY_BROWINDEX 0L
//#define MY_KHH "000707005891" //��ѯjy
//#define MY_KHH "005353005168" //��ѯhg
//#define MY_KHH "003737004885" //��ѯmr mc rq rqgh sg

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

#define MY_WTLB_MR 1L //����
#define MY_WTLB_SG 16L //�͹�

#define MY_WTLB_MC 2L //����
#define MY_WTLB_RZ 4L //����
#define MY_WTLB_RQ 5L //��ȯ
#define MY_WTLB_RZGH 34L //���ʹ���
#define MY_WTLB_RQGH 35L //��ȯ����

#define MY_PK_OPERATIONCODE_MR "40000"
#define MY_PK_OPERATIONCODE_MC "40001"
#define MY_PK_OPERATIONNAME_MR "��Ʊ����"
#define MY_PK_OPERATIONNAME_MC "��Ʊ����"
#define MY_PK_CORP "9001"
#define MY_PK_OPERATIONCODE_HG "40006"
#define MY_PK_OPERATIONCODE_GH "40009"
#define MY_PK_OPERATIONNAME_RQHG "��ȯ�ع�"
#define MY_PK_OPERATIONNAME_RQGH "��ȯ����"
#define MY_PK_PARTER "D890767292"
#define MY_SEPARATOR ","
#define MY_BOURSECODE_SH "101"
#define MY_BOURSECODE_SZ "102"
#define MY_JYS_SH "SH"
#define MY_JYS_SZ "SZ"

#define MY_YWKM_YZZZ_C 10113 //��֤ת�˴�
#define MY_YWKM_YZZZ_Q 10213 //��֤ת��ȡ
#define MY_YWKM_XHLXRBJ 10501 //������Ϣ�뱾��
#define MY_YWKM_JDLXRBJ 10503 //������Ϣ�뱾��

#define MY_YWKM_HGHCZJ 13021 //�ع���ȯ�ɽ������ʽ�
#define MY_YWKM_GHHRZJ 13122 //�ع���ȯ�����ʽ���
#define MY_YWKM_MRHCZJ 13001 //����ɽ������ʽ�
#define MY_YWKM_MCHRZJ 13101 //�����ɽ������ʽ�

#define MY_PK_OPERATIONCODE_ZJZJ "20300"
#define MY_PK_OPERATIONCODE_JSZJ "20301"
#define MY_PK_OPERATIONCODE_LXSR "2030001"
#define MY_PK_OPERATIONNAME_ZJZJ "�����ʽ�"
#define MY_PK_OPERATIONNAME_JSZJ "�����ʽ�"
#define MY_PK_OPERATIONNAME_LXSR "��Ϣ����"

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



//�ʽ���ϸ403201
struct ZJMXLS
{
	//long fid_code;//������
	//char fid_message[256];//���ش���˵��
	char fid_browindex[130];//��ǰ��ҳ����ֵ

	long fid_seqno;//��ˮ��
	long fid_rq;//��������
	long fid_rzrq;//��������
	double fid_srje;//������
	double fid_fcje;//��������
	double fid_bczjye;//�����ʽ����
	long fid_sqfs;//���뷽ʽ

	char fid_fsyyb[6];//����Ӫҵ��
	char fid_node[32];//����վ�� 20
	char fid_zjly[6];//�ʽ���Դ 2
	char fid_xgdm[12];//��ش���
	char fid_yyb[6];//Ӫҵ��
	char fid_gsfl[4];//��˾����
	char fid_bz[6];//����
	char fid_zy[82];//ժҪ
	char fid_czbz[3];//���˱�־
	char fid_zjzh[32];//�ʽ��˺�
	char fid_ywkm[8];//ҵ���Ŀ 4
	char fid_wbzh[32];//�ⲿ�˺�
	char fid_khqz[4];//�ͻ�Ⱥ��

	long fid_ywsqh;//ҵ�������

	char fid_khh[14];//�ͻ���
	char fid_khxm[18];//�ͻ�����
	char fid_fssj[10];//����ʱ��
	char fid_fhgy[10];//���˹�Ա

	long fid_lsh;//��ˮ��
};

//�ֲ�304101
struct CC
{
	//long fid_code;//������
	//char fid_message[256];//���ش���˵��
	char fid_zqmc[10];//֤ȯ����
	char fid_jys[4];//������

	char fid_gdh[12];//�ɶ���

	long fid_zqsl;//֤ȯ����
	char fid_zqdm[8];//֤ȯ����
	char fid_zqlb[4];//֤ȯ���
	long fid_jydw;//���׵�λ FID_EXFLG=1ʱ��Ч
	char fid_bz[6];//����
	long fid_drmrwtsl;//��������ί������
	long fid_bdrq;//����䶯����
	double fid_bbj;//������ FID_EXFLG=1ʱ��Ч
	long fid_pgsl;//�������
	double fid_lxbj;//��Ϣ����
	long fid_drmcwtsl;//��������ί������
	double fid_pgje;//��ɽ��
	double fid_mrje;//������
	double fid_mcje;//�������
	long fid_mrsl;//��������
	long fid_kshsl;//���������
	long fid_ksgsl;//���깺����
	long fid_kmcsl;//����������
	long fid_djsl;//��������
	long fid_fltsl;//����ͨ����
	long fid_jccl;//��ֲ���
	long fid_wjssl;//δ��������
	double fid_mrjj;//�������
	double fid_ccjj;//�ֲ־���
	double fid_tbcbj;//̯���ɱ���
	double fid_ljyk;//�ۼ�ӯ��
	double fid_fdyk;//����ӯ��
	double fid_tbbbj;//̯��������
	double fid_tbfdyk;//̯������ӯ��
	double fid_zxsz;//������ֵ
	double fid_zxj;//���¼�
	long fid_kcrq;//��������
	long fid_mcsl;//��������
	double fid_drmrcjje;//��������ɽ����
	long fid_drmrcjsl;//���������ɽ����
	double fid_drmccjje;//��������ɽ�����
	long fid_sgsl;//�͹�����
	double fid_hlje;//�������
	long fid_drmccjsl;//���������ɽ�����
	long fid_shcjsl;//��سɽ�����
	long fid_mcdxsl;//������������
	long fid_sgcjsl;//�깺�ɽ�����
	long fid_mrdxsl;//�����������
};

//������ϸ404201
struct JGMXLS
{
	char fid_gdxm[18];//�ɶ�����
	char fid_jys[4];//������
	char fid_jszh[32];//�����ʻ�
	long fid_wtfs;//ί�з�ʽ
	char fid_xwdm[8];//ϯλ����
	char fid_zqdm[8];//֤ȯ����
	char fid_zqlb[4];//֤ȯ���
	char fid_cjsj[10];//�ɽ�ʱ��
	char fid_sbsj[10];//�걨ʱ��
	double fid_lxjg;//��Ϣ�۸�
	double fid_cjje;//�ɽ����
	double fid_lxje;//��Ϣ���
	double fid_bzs1;//��־Ӷ��
	double fid_s3;//������
	double fid_s5;//�����
	double fid_bczjye;//�����ʽ����
	double fid_bbyk;//����ӯ��
	char fid_loginid[14];//��¼ ID
	char fid_fhgy[10];//��˹�Ա
	char fid_yyb[6];//Ӫҵ��
	char fid_cjbh[32];//�ɽ����
	double fid_s1;//Ӷ��
	double fid_s4;//���ӷ�
	char fid_jsjg[6];//�������
	char fid_zqmc[10];//֤ȯ����
	long fid_wtlb;//ί�����
	long fid_cjrq;//�ɽ�����
	long fid_cjbs;//�ɽ�����
	long fid_cjsl;//�ɽ�����
	double fid_cjjg;//�ɽ��۸�
	double fid_jsj;//�����
	double fid_s2;//ӡ��˰
	double fid_s6;//���׹��
	double fid_ysje;//Ӧ�ս��
	long fid_bczqsl;//���ιɷ����
	long fid_rzrq;//��������

	char fid_bz[6];//����
	long fid_jsrq;//��������
	long fid_yjdjcl;//Ӷ�𶨼۲���
	long fid_yjdjfs;//Ӷ�𶨼۷�ʽ
	char fid_browindex[130];//��ǰ��ҳ����ֵ

	char fid_gdh[12];//�ɶ���
	long fid_djsl;//��������
	long fid_dlsf;//��¼���
	long fid_bcdjsl;//���ζ�������
	long fid_yssl;//Ӧ������

	char fid_zjmxlsh[12];//�ʽ���ϸ��ˮ�� 8

	char fid_khqz[4];//�ͻ�Ⱥ��
	char fid_gsfl[4];//��˾����
	long fid_seqno;//��ˮ��
	long fid_jgzllb;//�����������
	long fid_wth;//ί�к�
	char fid_khxm[18];//�ͻ�����
	char fid_khh[14];//�ͻ���
};



//ϵͳ״̬101020
struct XTZT
{
	long fid_qsbz;//�����־
	long fid_xtcsbz;//ϵͳ���Ա�־
	long fid_code;//������
	char fid_message[202];//���ش���˵��
};


//��ѯ��ʷ�ʽ���ϸ
map<long, list<ZJMXLS>> Query_ZJMXLS(HANDLE_CONN, long, long);
//map<long, list<ZJMXLS>> Group_ZJMXLS(list<ZJMXLS>);
//��ѯ�ֲ�
list<CC> Query_CC(HANDLE_CONN);
//��ѯ��ʷ������ϸ
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
//��ʼ��char[] ��memset 0
void initCharArr(char[]);
//�滻,Ϊ:
void repComma(char[]);
//ת��doubleΪchar*
char* d2str(double, char[]);

LPCWSTR C2LPCWSTR(const char* str);
//��������в���
void Split_RQ(TCHAR[], TCHAR[]);
//�����ļ���
string Get_FileName(char*, char*, char*);
//���������ļ�
map<string, string> Load_Configuration(char*);
//CStringת��Ϊstring
string WChar2Ansi(LPCWSTR pwszSrc);
//������ȫִ�гɹ���������Ϣ
void Save_Configuration(char* cfgFilePath);

//���߷�����ת��������������Ϊ20150310��ʽ
void write_TradeDates();
//��ȡ���1�ν���������
string Get_QueryDate();
