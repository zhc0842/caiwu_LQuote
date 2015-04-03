
// CW_Auto.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CW_Auto.h"
#include "CW_AutoDlg.h"
#include "my3.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCW_AutoApp

BEGIN_MESSAGE_MAP(CCW_AutoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCW_AutoApp construction

CCW_AutoApp::CCW_AutoApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCW_AutoApp object

CCW_AutoApp theApp;


// CCW_AutoApp initialization

BOOL CCW_AutoApp::InitInstance()
{
	
	cfg_map = Load_Configuration(NULL);

	//AfxMessageBox(_T("Starting...\n"), MB_OK);

	//check...
	char* strKsrq = const_cast<char*>(cfg_map[MY_KSRQ].c_str());
	char* strJsrq = const_cast<char*>(cfg_map[MY_JSRQ].c_str());
	//

	long nKsrq = atol(strKsrq);
	long nJsrq = atol(strJsrq);

	if (!checkDate(nKsrq, nJsrq))
	{
		//return FALSE;
		exit(0);
	}


	string finalAddr;
	finalAddr.append(cfg_map[MY_Addr]).append("@").append(cfg_map[MY_Port].c_str()).append("/").append(cfg_map[MY_Protocol]).c_str();

	//connect...
	HANDLE_CONN conn = Fix_Connect(finalAddr.c_str(), cfg_map[MY_User].c_str(), cfg_map[MY_Pwd].c_str(), atol(cfg_map[MY_TimeOut].c_str()));
	if (conn == NULL)
	{
		AfxMessageBox(_T("failed : Connect Server ! check VPN or connection arguments .\n"), MB_OK);
		//return FALSE;
		exit(0);
	}


	//query...
	map<long, list<ZJMXLS>> zjmxls_map = Query_ZJMXLS(conn, nKsrq, nJsrq);
	for (map<long, list<ZJMXLS>>::iterator zjmxls_it = zjmxls_map.begin(); zjmxls_it != zjmxls_map.end(); zjmxls_it++)
	{
		long n_rq = zjmxls_it->first;
		char str_rq[20] = "0";
		_ltoa_s(n_rq, str_rq, 10);
		list<ZJMXLS> zjmxls_list = zjmxls_it->second;
		Write_ZJMXLS(zjmxls_list, NULL, str_rq, str_rq);
	}

	//list<CC> cc_list = Query_CC(conn);
	//Write_CC(cc_list,NULL);	

	map<long, list<JGMXLS>> jgmxls_map = Query_JGMXLS(conn, nKsrq, nJsrq);
	for (map<long, list<JGMXLS>>::iterator jgmxls_it = jgmxls_map.begin(); jgmxls_it != jgmxls_map.end(); jgmxls_it++)
	{
		long n_rq = jgmxls_it->first;
		char str_rq[20] = "0";
		_ltoa_s(n_rq, str_rq, 10);
		list<JGMXLS> jgmxls_list = jgmxls_it->second;
		Write_JGMXLS(jgmxls_list, NULL, str_rq, str_rq);
	}



	if (!Fix_Close(conn))
	{
		AfxMessageBox(_T("failed: Close Connection !\n"), MB_OK);
	}


	Save_Configuration(NULL);


	//AfxMessageBox(_T("Ending...\n"), MB_OK);

	//-------------------------------------------------------


	return FALSE;
}


//-------------------------------------------------

map<long, list<ZJMXLS>> Query_ZJMXLS(HANDLE_CONN conn, long ksrq, long jsrq)
{
	//AfxMessageBox(_T("Start:Query_ZJMXLS..."), MB_OK);
	HANDLE_SESSION sess = Fix_AllocateSession(conn);

	long nAllRowCount = 0L;
	char strBrowIndex[130] = "0";

	map<long, list<ZJMXLS>> zjmxls_map;
	do
	{
		Fix_CreateHead(sess, FUN_ACCOUNT_LIST_ZJMXLS_KH);
		Fix_SetItem(sess, FID_KHH, cfg_map[MY_KHH].c_str());
		Fix_SetItem(sess, FID_KSRQ, ksrq);
		Fix_SetItem(sess, FID_JSRQ, jsrq);
		Fix_SetItem(sess, FID_ROWCOUNT, MY_ROWCOUNT);
		Fix_SetItem(sess, FID_BROWINDEX, strBrowIndex);

		if (Fix_Run(sess))
		{
			long nThisRowCount = Fix_GetCount(sess) - nAllRowCount;
			nAllRowCount = Fix_GetCount(sess);
			for (int i = 0; i < nThisRowCount; i++)
			{
				ZJMXLS zjmxls;

				Fix_GetItem(sess, FID_BROWINDEX, zjmxls.fid_browindex, sizeof(zjmxls.fid_browindex) - 1, i);

				zjmxls.fid_seqno = Fix_GetLong(sess, FID_SEQNO, i);
				zjmxls.fid_rq = Fix_GetLong(sess, FID_RQ, i);
				zjmxls.fid_rzrq = Fix_GetLong(sess, FID_RZRQ, i);
				zjmxls.fid_srje = Fix_GetDouble(sess, FID_SRJE, i);
				zjmxls.fid_fcje = Fix_GetDouble(sess, FID_FCJE, i);
				zjmxls.fid_bczjye = Fix_GetDouble(sess, FID_BCZJYE, i);
				zjmxls.fid_sqfs = Fix_GetLong(sess, FID_SQFS, i);

				Fix_GetItem(sess, FID_FSYYB, zjmxls.fid_fsyyb, sizeof(zjmxls.fid_fsyyb) - 1, i);
				Fix_GetItem(sess, FID_NODE, zjmxls.fid_node, sizeof(zjmxls.fid_node) - 1, i);
				repComma(zjmxls.fid_node);

				Fix_GetItem(sess, FID_ZJLY, zjmxls.fid_zjly, sizeof(zjmxls.fid_zjly) - 1, i);
				Fix_GetItem(sess, FID_XGDM, zjmxls.fid_xgdm, sizeof(zjmxls.fid_xgdm) - 1, i);
				Fix_GetItem(sess, FID_YYB, zjmxls.fid_yyb, sizeof(zjmxls.fid_yyb) - 1, i);
				Fix_GetItem(sess, FID_GSFL, zjmxls.fid_gsfl, sizeof(zjmxls.fid_gsfl) - 1, i);
				Fix_GetItem(sess, FID_BZ, zjmxls.fid_bz, sizeof(zjmxls.fid_bz) - 1, i);
				Fix_GetItem(sess, FID_ZY, zjmxls.fid_zy, sizeof(zjmxls.fid_zy) - 1, i);
				repComma(zjmxls.fid_zy);

				Fix_GetItem(sess, FID_CZBZ, zjmxls.fid_czbz, sizeof(zjmxls.fid_czbz) - 1, i);
				Fix_GetItem(sess, FID_ZJZH, zjmxls.fid_zjzh, sizeof(zjmxls.fid_zjzh) - 1, i);
				Fix_GetItem(sess, FID_YWKM, zjmxls.fid_ywkm, sizeof(zjmxls.fid_ywkm) - 1, i);
				Fix_GetItem(sess, FID_WBZH, zjmxls.fid_wbzh, sizeof(zjmxls.fid_wbzh) - 1, i);
				Fix_GetItem(sess, FID_KHQZ, zjmxls.fid_khqz, sizeof(zjmxls.fid_khqz) - 1, i);

				zjmxls.fid_ywsqh = Fix_GetLong(sess, FID_YWSQH, i);

				Fix_GetItem(sess, FID_KHH, zjmxls.fid_khh, sizeof(zjmxls.fid_khh) - 1, i);
				Fix_GetItem(sess, FID_KHXM, zjmxls.fid_khxm, sizeof(zjmxls.fid_khxm) - 1, i);
				Fix_GetItem(sess, FID_FSSJ, zjmxls.fid_fssj, sizeof(zjmxls.fid_fssj) - 1, i);
				Fix_GetItem(sess, FID_FHGY, zjmxls.fid_fhgy, sizeof(zjmxls.fid_fhgy) - 1, i);

				zjmxls.fid_lsh = Fix_GetLong(sess, FID_LSH, i);

				zjmxls_map[zjmxls.fid_rq].push_back(zjmxls);

				if (i == nThisRowCount - 1)
				{
					strcpy_s(strBrowIndex, zjmxls.fid_browindex);
				}
			}
		}
		else
		{
			char out[512];
			Fix_GetErrMsg(sess, out, sizeof(out));
			AfxMessageBox((LPCTSTR)out, MB_OK);
			break;
		}
	} while (nAllRowCount != 0 && nAllRowCount%MY_ROWCOUNT == 0);

	//AfxMessageBox(_T("End:Query_ZJMXLS..."), MB_OK);

	Fix_ReleaseSession(sess);
	return zjmxls_map;
}


//查询持仓
list<CC> Query_CC(HANDLE_CONN conn)
{
	//AfxMessageBox(_T("Start:Query_CC..."), MB_OK);

	HANDLE_SESSION sess = Fix_AllocateSession(conn);
	Fix_CreateHead(sess, FUN_SECU_LIST_HOLDSTOCK);
	Fix_SetItem(sess, FID_KHH, cfg_map[MY_KHH].c_str());
	long nAllRowCount = 0L;
	if (Fix_Run(sess))
	{
		nAllRowCount = Fix_GetCount(sess);
	}
	else
	{
		char out[512];
		Fix_GetErrMsg(sess, out, sizeof(out));
		AfxMessageBox((LPCTSTR)out, MB_OK);
	}

	list<CC> cc_list;
	for (int i = 0; i < nAllRowCount; i++)
	{
		CC cc;

		Fix_GetItem(sess, FID_ZQMC, cc.fid_zqmc, sizeof(cc.fid_zqmc) - 1, i);
		Fix_GetItem(sess, FID_JYS, cc.fid_jys, sizeof(cc.fid_jys) - 1, i);
		Fix_GetItem(sess, FID_GDH, cc.fid_gdh, sizeof(cc.fid_gdh) - 1, i);

		cc.fid_zqsl = Fix_GetLong(sess, FID_ZQSL, i);

		Fix_GetItem(sess, FID_ZQDM, cc.fid_zqdm, sizeof(cc.fid_zqdm) - 1, i);
		Fix_GetItem(sess, FID_ZQLB, cc.fid_zqlb, sizeof(cc.fid_zqlb) - 1, i);

		cc.fid_jydw = Fix_GetLong(sess, FID_JYDW, i);

		Fix_GetItem(sess, FID_BZ, cc.fid_bz, sizeof(cc.fid_bz) - 1, i);

		cc.fid_drmrwtsl = Fix_GetLong(sess, FID_DRMRWTSL, i);
		cc.fid_bdrq = Fix_GetLong(sess, FID_BDRQ, i);
		cc.fid_bbj = Fix_GetDouble(sess, FID_BBJ, i);
		cc.fid_pgsl = Fix_GetLong(sess, FID_PGSL, i);
		cc.fid_lxbj = Fix_GetDouble(sess, FID_LXBJ, i);
		cc.fid_drmcwtsl = Fix_GetLong(sess, FID_DRMCWTSL, i);
		cc.fid_pgje = Fix_GetDouble(sess, FID_PGJE, i);
		cc.fid_mrje = Fix_GetDouble(sess, FID_MRJE, i);
		cc.fid_mcje = Fix_GetDouble(sess, FID_MCJE, i);
		cc.fid_mrsl = Fix_GetLong(sess, FID_MRSL, i);
		cc.fid_kshsl = Fix_GetLong(sess, FID_KSHSL, i);
		cc.fid_ksgsl = Fix_GetLong(sess, FID_KSGSL, i);
		cc.fid_kmcsl = Fix_GetLong(sess, FID_KMCSL, i);
		cc.fid_djsl = Fix_GetLong(sess, FID_DJSL, i);
		cc.fid_fltsl = Fix_GetLong(sess, FID_FLTSL, i);
		cc.fid_jccl = Fix_GetLong(sess, FID_JCCL, i);
		cc.fid_wjssl = Fix_GetLong(sess, FID_WJSSL, i);
		cc.fid_mrjj = Fix_GetDouble(sess, FID_MRJJ, i);
		cc.fid_ccjj = Fix_GetDouble(sess, FID_CCJJ, i);
		cc.fid_tbcbj = Fix_GetDouble(sess, FID_TBCBJ, i);
		cc.fid_ljyk = Fix_GetDouble(sess, FID_LJYK, i);
		cc.fid_fdyk = Fix_GetDouble(sess, FID_FDYK, i);
		cc.fid_tbbbj = Fix_GetDouble(sess, FID_TBBBJ, i);
		cc.fid_tbfdyk = Fix_GetDouble(sess, FID_TBFDYK, i);
		cc.fid_zxsz = Fix_GetDouble(sess, FID_ZXSZ, i);
		cc.fid_zxj = Fix_GetDouble(sess, FID_ZXJ, i);
		cc.fid_kcrq = Fix_GetLong(sess, FID_KCRQ, i);
		cc.fid_mcsl = Fix_GetLong(sess, FID_MCSL, i);
		cc.fid_drmrcjje = Fix_GetDouble(sess, FID_DRMRCJJE, i);
		cc.fid_drmccjje = Fix_GetDouble(sess, FID_DRMCCJJE, i);
		cc.fid_drmrcjsl = Fix_GetLong(sess, FID_DRMRCJSL, i);
		cc.fid_sgsl = Fix_GetLong(sess, FID_SGSL, i);
		cc.fid_hlje = Fix_GetDouble(sess, FID_HLJE, i);
		cc.fid_drmccjsl = Fix_GetLong(sess, FID_DRMCCJSL, i);
		cc.fid_shcjsl = Fix_GetLong(sess, FID_SHCJSL, i);
		cc.fid_mcdxsl = Fix_GetLong(sess, FID_MCDXSL, i);
		cc.fid_sgcjsl = Fix_GetLong(sess, FID_SGCJSL, i);
		cc.fid_mrdxsl = Fix_GetLong(sess, FID_MRDXSL, i);

		cc_list.push_back(cc);
	}

	//AfxMessageBox(_T("End:Query_CC..."), MB_OK);

	Fix_ReleaseSession(sess);

	return cc_list;
}

//查询历史交割明细
map<long, list<JGMXLS>> Query_JGMXLS(HANDLE_CONN conn, long ksrq, long jsrq)
{
	//AfxMessageBox(_T("Start:Query_JGMXLS..."), MB_OK);
	HANDLE_SESSION sess = Fix_AllocateSession(conn);

	long nAllRowCount = 0L;
	char strBrowIndex[130] = "0";
	map<long, list<JGMXLS>> jgmxls_map;
	//map<long, int> jgmxls_seqnoCount;
	do
	{
		Fix_CreateHead(sess, FUN_SECU_LIST_JGMXLS_KH);
		Fix_SetItem(sess, FID_KHH, cfg_map[MY_KHH].c_str());
		Fix_SetItem(sess, FID_KSRQ, ksrq);
		Fix_SetItem(sess, FID_JSRQ, jsrq);
		Fix_SetItem(sess, FID_ROWCOUNT, MY_ROWCOUNT);
		Fix_SetItem(sess, FID_BROWINDEX, strBrowIndex);
		if (Fix_Run(sess))
		{
			long nThisRowCount = Fix_GetCount(sess) - nAllRowCount;
			nAllRowCount = Fix_GetCount(sess);
			for (int i = 0; i < nThisRowCount; i++)
			{
				JGMXLS jgmxls;

				Fix_GetItem(sess, FID_GDXM, jgmxls.fid_gdxm, sizeof(jgmxls.fid_gdxm) - 1, i);
				Fix_GetItem(sess, FID_JYS, jgmxls.fid_jys, sizeof(jgmxls.fid_jys) - 1, i);
				Fix_GetItem(sess, FID_JSZH, jgmxls.fid_jszh, sizeof(jgmxls.fid_jszh) - 1, i);

				jgmxls.fid_wtfs = Fix_GetLong(sess, FID_WTFS, i);

				Fix_GetItem(sess, FID_XWDM, jgmxls.fid_xwdm, sizeof(jgmxls.fid_xwdm) - 1, i);
				Fix_GetItem(sess, FID_ZQDM, jgmxls.fid_zqdm, sizeof(jgmxls.fid_zqdm) - 1, i);
				Fix_GetItem(sess, FID_ZQLB, jgmxls.fid_zqlb, sizeof(jgmxls.fid_zqlb) - 1, i);
				Fix_GetItem(sess, FID_CJSJ, jgmxls.fid_cjsj, sizeof(jgmxls.fid_cjsj) - 1, i);
				Fix_GetItem(sess, FID_SBSJ, jgmxls.fid_sbsj, sizeof(jgmxls.fid_sbsj) - 1, i);

				jgmxls.fid_lxjg = Fix_GetDouble(sess, FID_LXJG, i);
				jgmxls.fid_cjje = Fix_GetDouble(sess, FID_CJJE, i);
				jgmxls.fid_lxje = Fix_GetDouble(sess, FID_LXJE, i);
				jgmxls.fid_bzs1 = Fix_GetDouble(sess, FID_BZS1, i);
				jgmxls.fid_s3 = Fix_GetDouble(sess, FID_S3, i);
				jgmxls.fid_s5 = Fix_GetDouble(sess, FID_S5, i);
				jgmxls.fid_bczjye = Fix_GetDouble(sess, FID_BCZJYE, i);
				jgmxls.fid_bbyk = Fix_GetDouble(sess, FID_BBYK, i);

				Fix_GetItem(sess, FID_LOGINID, jgmxls.fid_loginid, sizeof(jgmxls.fid_loginid) - 1, i);
				Fix_GetItem(sess, FID_FHGY, jgmxls.fid_fhgy, sizeof(jgmxls.fid_fhgy) - 1, i);
				Fix_GetItem(sess, FID_YYB, jgmxls.fid_yyb, sizeof(jgmxls.fid_yyb) - 1, i);
				Fix_GetItem(sess, FID_CJBH, jgmxls.fid_cjbh, sizeof(jgmxls.fid_cjbh) - 1, i);

				jgmxls.fid_s1 = Fix_GetDouble(sess, FID_S1, i);
				jgmxls.fid_s4 = Fix_GetDouble(sess, FID_S4, i);

				Fix_GetItem(sess, FID_JSJG, jgmxls.fid_jsjg, sizeof(jgmxls.fid_jsjg) - 1, i);
				Fix_GetItem(sess, FID_ZQMC, jgmxls.fid_zqmc, sizeof(jgmxls.fid_zqmc) - 1, i);

				jgmxls.fid_wtlb = Fix_GetLong(sess, FID_WTLB, i);
				jgmxls.fid_cjrq = Fix_GetLong(sess, FID_CJRQ, i);
				jgmxls.fid_cjbs = Fix_GetLong(sess, FID_CJBS, i);
				jgmxls.fid_cjsl = Fix_GetLong(sess, FID_CJSL, i);
				jgmxls.fid_cjjg = Fix_GetDouble(sess, FID_CJJG, i);
				jgmxls.fid_jsj = Fix_GetDouble(sess, FID_JSJ, i);
				jgmxls.fid_s2 = Fix_GetDouble(sess, FID_S2, i);
				jgmxls.fid_s6 = Fix_GetDouble(sess, FID_S6, i);
				jgmxls.fid_ysje = Fix_GetDouble(sess, FID_YSJE, i);
				jgmxls.fid_bczqsl = Fix_GetLong(sess, FID_BCZQSL, i);
				jgmxls.fid_rzrq = Fix_GetLong(sess, FID_RZRQ, i);

				Fix_GetItem(sess, FID_BZ, jgmxls.fid_bz, sizeof(jgmxls.fid_bz) - 1, i);

				jgmxls.fid_jsrq = Fix_GetLong(sess, FID_JSRQ, i);
				jgmxls.fid_yjdjcl = Fix_GetLong(sess, FID_YJDJCL, i);
				jgmxls.fid_yjdjfs = Fix_GetLong(sess, FID_YJDJFS, i);

				Fix_GetItem(sess, FID_BROWINDEX, jgmxls.fid_browindex, sizeof(jgmxls.fid_browindex) - 1, i);
				Fix_GetItem(sess, FID_GDH, jgmxls.fid_gdh, sizeof(jgmxls.fid_gdh) - 1, i);

				jgmxls.fid_djsl = Fix_GetLong(sess, FID_DJSL, i);
				jgmxls.fid_dlsf = Fix_GetLong(sess, FID_DLSF, i);
				jgmxls.fid_bcdjsl = Fix_GetLong(sess, FID_BCDJSL, i);
				jgmxls.fid_yssl = Fix_GetLong(sess, FID_YSSL, i);

				Fix_GetItem(sess, FID_ZJMXLSH, jgmxls.fid_zjmxlsh, sizeof(jgmxls.fid_zjmxlsh) - 1, i);
				Fix_GetItem(sess, FID_KHQZ, jgmxls.fid_khqz, sizeof(jgmxls.fid_khqz) - 1, i);
				Fix_GetItem(sess, FID_GSFL, jgmxls.fid_gsfl, sizeof(jgmxls.fid_gsfl) - 1, i);

				jgmxls.fid_seqno = Fix_GetLong(sess, FID_SEQNO, i);
				jgmxls.fid_jgzllb = Fix_GetLong(sess, FID_JGZLLB, i);
				jgmxls.fid_wth = Fix_GetLong(sess, FID_WTH, i);



				Fix_GetItem(sess, FID_KHXM, jgmxls.fid_khxm, sizeof(jgmxls.fid_khxm) - 1, i);
				Fix_GetItem(sess, FID_KHH, jgmxls.fid_khh, sizeof(jgmxls.fid_khh) - 1, i);

				jgmxls.fid_wth = jgmxls.fid_seqno;//因为委托号可能为0 ， 所以统一使用流水号

				jgmxls_map[jgmxls.fid_cjrq].push_back(jgmxls);
				//jgmxls_seqnoCount[jgmxls.fid_seqno]++;

				if (i == nThisRowCount - 1)
				{
					strcpy_s(strBrowIndex, jgmxls.fid_browindex);
				}
			}
		}
		else
		{
			char out[512];
			Fix_GetErrMsg(sess, out, sizeof(out));
			AfxMessageBox((LPCTSTR)out, MB_OK);
			break;
		}
	} while (nAllRowCount != 0 && nAllRowCount % MY_ROWCOUNT == 0);

	//AfxMessageBox(_T("End:Query_JGMXLS..."), MB_OK);

	Fix_ReleaseSession(sess);
	return jgmxls_map;
}

void Write_ZJMXLS(list<ZJMXLS> zjmxls_list, char* zjmxlsFilePath, char* strKsrq, char* strJsrq)
{
	//AfxMessageBox(_T("Start:Write_ZJMXLS..."), MB_OK);
	/*
	if(fout == NULL)
	{
	MessageBox(0,("filed:Open file !\n"), "信息", MB_ICONASTERISK);
	}
	*/

	ZJMXLS zjmxls;

	int zjHeadCount = 0;
	int elseCount = 0;
	list<ZJMXLS> zj_list;

	ofstream otherFout;
	for (list<ZJMXLS>::iterator it = zjmxls_list.begin(); it != zjmxls_list.end(); it++)
	{
		zjmxls = *it;
		int nYWKM = atoi(zjmxls.fid_ywkm);
		//筛选 银证转正存、取，销户利息、季度利息
		if (nYWKM == MY_YWKM_YZZZ_C || nYWKM == MY_YWKM_YZZZ_Q || nYWKM == MY_YWKM_XHLXRBJ || nYWKM == MY_YWKM_JDLXRBJ)
		{
			zj_list.push_back(zjmxls);
		}
		else
		{
			if (nYWKM == MY_YWKM_HGHCZJ || nYWKM == MY_YWKM_GHHRZJ || nYWKM == MY_YWKM_MRHCZJ || nYWKM == MY_YWKM_MCHRZJ)
			{
				continue;
			}

			elseCount++;
			if (elseCount == 1)
			{
				otherFout.open(Get_FileName("other_zjmxls", strKsrq, strJsrq).c_str());
				otherFout << "流水号" << "," << "发生日期" << "," << "入账日期" << "," << "收入金额" << "," << "付出金额" << "," << "本次资金余额" << "," << "申请方式" << "," << "发生营业部" << "," << "操作站点" << "," << "资金来源" << "," << "相关代码" << "," << "营业部" << "," << "公司分类" << "," << "币种" << "," << "摘要" << "," << "冲账标志" << "," << "资金账号" << "," << "业务科目" << "," << "外部账号" << "," << "客户群号" << "," << "业务申请号" << "," << "客户号" << "," << "客户姓名" << "," << "发生时间" << "," << "复核柜员" << "," << "流水号" << endl;
			}

			//otherFout<<zjmxls.fid_browindex<<","<<zjmxls.fid_seqno<<","<<zjmxls.fid_rq<<","<<zjmxls.fid_rzrq<<","<<zjmxls.fid_srje<<","<<zjmxls.fid_fcje<<","<<zjmxls.fid_bczjye<<","<<zjmxls.fid_sqfs<<","<<zjmxls.fid_fsyyb<<","<<zjmxls.fid_node<<","<<zjmxls.fid_zjly<<","<<zjmxls.fid_xgdm<<","<<zjmxls.fid_yyb<<","<<zjmxls.fid_gsfl<<","<<zjmxls.fid_bz<<","<<zjmxls.fid_zy<<","<<zjmxls.fid_czbz<<","<<zjmxls.fid_zjzh<<","<<zjmxls.fid_ywkm<<","<<zjmxls.fid_wbzh<<","<<zjmxls.fid_khqz<<","<<zjmxls.fid_ywsqh<<","<<zjmxls.fid_khh<<","<<zjmxls.fid_khxm<<","<<zjmxls.fid_fssj<<","<<zjmxls.fid_fhgy<<","<<zjmxls.fid_lsh<<endl;
			otherFout << zjmxls.fid_seqno << "," << zjmxls.fid_rq << "," << zjmxls.fid_rzrq << "," << zjmxls.fid_srje << "," << zjmxls.fid_fcje << "," << zjmxls.fid_bczjye << "," << zjmxls.fid_sqfs << "," << zjmxls.fid_fsyyb << "," << zjmxls.fid_node << "," << zjmxls.fid_zjly << "," << zjmxls.fid_xgdm << "," << zjmxls.fid_yyb << "," << zjmxls.fid_gsfl << "," << zjmxls.fid_bz << "," << zjmxls.fid_zy << "," << zjmxls.fid_czbz << "," << zjmxls.fid_zjzh << "," << zjmxls.fid_ywkm << "," << zjmxls.fid_wbzh << "," << zjmxls.fid_khqz << "," << zjmxls.fid_ywsqh << "," << zjmxls.fid_khh << "," << zjmxls.fid_khxm << "," << zjmxls.fid_fssj << "," << zjmxls.fid_fhgy << "," << zjmxls.fid_lsh << endl;
		}
	}
	otherFout.close();

	Write_ZJ(zj_list, NULL, strKsrq, strJsrq);
	zj_list.clear();
	zjmxls_list.clear();

	//AfxMessageBox(_T("End:Write_ZJMXLS..."), MB_OK);
}

void Write_ZJ(list<ZJMXLS> zj_list, char* filePath, char* strKsrq, char* strJsrq)
{
	list<ZJMXLS>::iterator it;
	list<long> lsh_list;
	for (it = zj_list.begin(); it != zj_list.end();)
	{
		string strZY = it->fid_zy;
		int l_idx = strZY.find_first_of("[");
		if (l_idx >= 0)
		{
			int r_idx = strZY.find_first_of("]", l_idx + 1);
			char charArrLSH[20];
			memset(charArrLSH, '\0', sizeof(charArrLSH));
			//strZY.copy(charArrLSH, (r_idx - l_idx - 1), l_idx + 1);
			for (int i = l_idx + 1, j = 0; i < r_idx; i++)
			{
				charArrLSH[j++] = strZY[i];
			}
			it = zj_list.erase(it);

			lsh_list.push_back(atol(charArrLSH));
		}
		else
		{
			it++;
		}
	}
	list<long>::iterator it_long;
	for (it_long = lsh_list.begin(); it_long != lsh_list.end(); it_long++)
	{
		long lsh = *it_long;
		for (it = zj_list.begin(); it != zj_list.end();)
		{
			if (it->fid_lsh == lsh)
			{
				it = zj_list.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	ofstream zjFout;

	int zjHeadCount = 0;
	for (it = zj_list.begin(); it != zj_list.end(); it++)
	{
		ZJMXLS zjmxls = *it;

		zjHeadCount++;
		if (zjHeadCount == 1)
		{
			zjFout.open(Get_FileName("zj", strKsrq, strJsrq).c_str());
			zjFout << setprecision(12);
			zjFout << "pk_corp" << MY_SEPARATOR << "bill_code" << MY_SEPARATOR << "trade_date" << MY_SEPARATOR << "trade_sum" << MY_SEPARATOR << "operationcode" << MY_SEPARATOR << "operationname" << MY_SEPARATOR << "accountcode" << MY_SEPARATOR << "accountname" << MY_SEPARATOR << "partnercode" << MY_SEPARATOR << "partnername" << MY_SEPARATOR << "cumandoccode" << MY_SEPARATOR << "cumandocname" << MY_SEPARATOR << "partner" << MY_SEPARATOR << "operatesite" << MY_SEPARATOR << "securitiescode" << MY_SEPARATOR << "securitiesname" << MY_SEPARATOR << "ndef1" << MY_SEPARATOR << "ndef2" << MY_SEPARATOR << "ndef3" << MY_SEPARATOR << "ndef4" << MY_SEPARATOR << "ndef5" << MY_SEPARATOR << "vdef1" << MY_SEPARATOR << "vdef2" << MY_SEPARATOR << "vdef3" << MY_SEPARATOR << "vdef4" << MY_SEPARATOR << "vdef5" << MY_SEPARATOR << "boursecode" << endl;
		}
		zjFout << MY_PK_CORP << MY_SEPARATOR << "DX" << zjmxls.fid_rq << "000001" << MY_SEPARATOR << zjmxls.fid_rq << MY_SEPARATOR;

		int nYWKM = atoi(zjmxls.fid_ywkm);
		if (nYWKM == MY_YWKM_YZZZ_Q)
		{
			zjFout << zjmxls.fid_fcje << MY_SEPARATOR;
		}
		else
		{
			zjFout << zjmxls.fid_srje << MY_SEPARATOR;
		}
		if (nYWKM == MY_YWKM_YZZZ_Q)
		{
			zjFout << MY_PK_OPERATIONCODE_JSZJ << MY_SEPARATOR << MY_PK_OPERATIONNAME_JSZJ << MY_SEPARATOR;
		}
		else if (nYWKM == MY_YWKM_YZZZ_C)
		{
			zjFout << MY_PK_OPERATIONCODE_ZJZJ << MY_SEPARATOR << MY_PK_OPERATIONNAME_ZJZJ << MY_SEPARATOR;
		}
		else
		{
			zjFout << MY_PK_OPERATIONCODE_LXSR << MY_SEPARATOR << MY_PK_OPERATIONNAME_LXSR << MY_SEPARATOR;
		}
		zjFout << zjmxls.fid_zjzh << MY_SEPARATOR << zjmxls.fid_khxm << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << 0 << MY_SEPARATOR << 0 << MY_SEPARATOR << 0 << MY_SEPARATOR << 0 << MY_SEPARATOR << 0 << MY_SEPARATOR << zjmxls.fid_zjzh << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << endl;
	}

	zjFout.close();
	zj_list.clear();
}

void Write_CC(list<CC> cc_list, char* ccFilePath)
{
	//AfxMessageBox(_T("Start:Write_CC..."), MB_OK);
	if (ccFilePath == NULL)
	{
		ccFilePath = "cc.csv";
	}
	ofstream fout;

	/*
	if(fout == NULL)
	{
	MessageBox(0,("filed:Open file !\n:Write_CC"), "异常", MB_ICONASTERISK);
	}
	*/
	CC cc;
	list<CC>::iterator it;
	int nHeadCount = 0;

	for (it = cc_list.begin(); it != cc_list.end(); it++)
	{
		cc = *it;
		nHeadCount++;
		if (nHeadCount == 1)
		{
			fout.open(ccFilePath);
			fout << setprecision(12);
			fout << "证券名称" << MY_SEPARATOR << "交易所" << MY_SEPARATOR << "股东号" << MY_SEPARATOR << "证券数量" << MY_SEPARATOR << "证券代码" << MY_SEPARATOR << "证券类别" << MY_SEPARATOR << "交易单位" << MY_SEPARATOR << "币种" << MY_SEPARATOR << "当日买入委托数量" << MY_SEPARATOR << "最近变动日期" << MY_SEPARATOR << "保本价" << MY_SEPARATOR << "配股数量" << MY_SEPARATOR << "利息报价" << MY_SEPARATOR << "当日卖出委托数量" << MY_SEPARATOR << "配股金额" << MY_SEPARATOR << "买入金额" << MY_SEPARATOR << "卖出金额" << MY_SEPARATOR << "买入数量" << MY_SEPARATOR << "可赎回数量" << MY_SEPARATOR << "可申购数量" << MY_SEPARATOR << "可卖出数量" << MY_SEPARATOR << "冻结数量" << MY_SEPARATOR << "非流通数量" << MY_SEPARATOR << "今持仓量" << MY_SEPARATOR << "未交收数量" << MY_SEPARATOR << "买入均价" << MY_SEPARATOR << "持仓均价" << MY_SEPARATOR << "摊薄成本价" << MY_SEPARATOR << "累计盈亏" << MY_SEPARATOR << "浮动盈亏" << MY_SEPARATOR << "摊薄保本价" << MY_SEPARATOR << "摊薄浮动盈亏" << MY_SEPARATOR << "最新市值" << MY_SEPARATOR << "最新价" << MY_SEPARATOR << "开仓日期" << MY_SEPARATOR << "卖出数量" << MY_SEPARATOR << "当日买入成交金额" << MY_SEPARATOR << "当日卖出成交金额" << MY_SEPARATOR << "当日买入成交数量" << MY_SEPARATOR << "送股数量" << MY_SEPARATOR << "红利金额" << MY_SEPARATOR << "当日卖出成交数量" << MY_SEPARATOR << "赎回成交数量" << MY_SEPARATOR << "卖出抵消数量" << MY_SEPARATOR << "申购成交数量" << MY_SEPARATOR << "买入抵消数量" << endl;
		}
		fout << cc.fid_zqmc << "," << cc.fid_jys << "," << cc.fid_gdh << "," << cc.fid_zqsl << "," << cc.fid_zqdm << "," << cc.fid_zqlb << "," << cc.fid_jydw << "," << cc.fid_bz << "," << cc.fid_drmrwtsl << "," << cc.fid_bdrq << "," << cc.fid_bbj << "," << cc.fid_pgsl << "," << cc.fid_lxbj << "," << cc.fid_drmcwtsl << "," << cc.fid_pgje << "," << cc.fid_mrje << "," << cc.fid_mcje << "," << cc.fid_mrsl << "," << cc.fid_kshsl << "," << cc.fid_ksgsl << "," << cc.fid_kmcsl << "," << cc.fid_djsl << "," << cc.fid_fltsl << "," << cc.fid_jccl << "," << cc.fid_wjssl << "," << cc.fid_mrjj << "," << cc.fid_ccjj << "," << cc.fid_tbcbj << "," << cc.fid_ljyk << "," << cc.fid_fdyk << "," << cc.fid_tbbbj << "," << cc.fid_tbfdyk << "," << cc.fid_zxsz << "," << cc.fid_zxj << "," << cc.fid_kcrq << "," << cc.fid_mcsl << "," << cc.fid_drmrcjje << "," << cc.fid_drmrcjsl << "," << cc.fid_drmccjje << "," << cc.fid_sgsl << "," << cc.fid_hlje << "," << cc.fid_drmccjsl << "," << cc.fid_shcjsl << "," << cc.fid_mcdxsl << "," << cc.fid_sgcjsl << "," << cc.fid_mrdxsl << endl;
	}
	fout.close();
	cc_list.clear();

	//AfxMessageBox(_T("End:Write_CC..."), MB_OK);
}

void Write_JGMXLS(list<JGMXLS> jgmxls_list, char* jgmxlsFilePath, char* ksrq, char* jsrq)
{
	//AfxMessageBox(_T("Start:Write_JGMXLS..."), MB_OK);
	/*
	if (jgmxlsFilePath == NULL)
	{
	jgmxlsFilePath = "jgmxls.csv";
	}
	*/

	ofstream jyFout;
	ofstream hgFout;
	ofstream otherFout;

	/*
	if(jyFout == NULL || hgFout == NULL || otherFout == NULL)
	{
	MessageBox(0,("failed:Open file !\n:Write_JGMXLS"), "异常", MB_ICONASTERISK);
	}
	*/
	JGMXLS jgmxls;
	list<JGMXLS>::iterator it;
	int jyHeadCount = 0;
	int hgHeadCount = 0;
	int otherHeadCount = 0;
	for (it = jgmxls_list.begin(); it != jgmxls_list.end(); it++)
	{
		jgmxls = *it;
		if (jgmxls.fid_wtlb == MY_WTLB_MR || jgmxls.fid_wtlb == MY_WTLB_SG || jgmxls.fid_wtlb == MY_WTLB_MC)
		{
			jyHeadCount++;
			if (jyHeadCount == 1)
			{
				jyFout.open(Get_FileName("jy", ksrq, jsrq).c_str());
				jyFout << setprecision(12);
				jyFout << "pk_selfstrade" << MY_SEPARATOR << "pk_corp" << MY_SEPARATOR << "bill_code" << MY_SEPARATOR << "trade_date" << MY_SEPARATOR << "pk_operationcode" << MY_SEPARATOR << "pk_operationname" << MY_SEPARATOR << "pk_securitiescode" << MY_SEPARATOR << "pk_securitiesname" << MY_SEPARATOR << "pk_selfsgroup" << MY_SEPARATOR << "pk_partner" << MY_SEPARATOR << "pk_account" << MY_SEPARATOR << "pk_cumando" << MY_SEPARATOR << "pk_operatesite" << MY_SEPARATOR << "pk_seat" << MY_SEPARATOR << "pk_econtract" << MY_SEPARATOR << "bargain_num" << MY_SEPARATOR << "bargain_sum" << MY_SEPARATOR << "commision" << MY_SEPARATOR << "handle_fee" << MY_SEPARATOR << "stamp_tax" << MY_SEPARATOR << "transfer_fee" << MY_SEPARATOR << "liquidate_fee" << MY_SEPARATOR << "other_fee" << MY_SEPARATOR << "fact_sum" << MY_SEPARATOR << "operator" << MY_SEPARATOR << "operate_date" << MY_SEPARATOR << "if_voucher" << MY_SEPARATOR << "if_audit" << MY_SEPARATOR << "assessor" << MY_SEPARATOR << "audit_date" << MY_SEPARATOR << "state" << MY_SEPARATOR << "ndef1" << MY_SEPARATOR << "ndef2" << MY_SEPARATOR << "ndef3" << MY_SEPARATOR << "ndef4" << MY_SEPARATOR << "ndef5" << MY_SEPARATOR << "vdef1" << MY_SEPARATOR << "vdef2" << MY_SEPARATOR << "vdef3" << MY_SEPARATOR << "vdef4" << MY_SEPARATOR << "vdef5" << MY_SEPARATOR << "ts" << MY_SEPARATOR << "dr" << MY_SEPARATOR << "begin_date" << MY_SEPARATOR << "end_date" << MY_SEPARATOR << "boursecode" << endl;
			}
			jyFout << MY_SEPARATOR << MY_PK_CORP << MY_SEPARATOR << jgmxls.fid_jys << jgmxls.fid_cjrq << MY_PK_CORP << jgmxls.fid_wth << MY_SEPARATOR << jgmxls.fid_cjrq << MY_SEPARATOR;
			if (jgmxls.fid_wtlb == MY_WTLB_MR || jgmxls.fid_wtlb == MY_WTLB_SG)
			{
				jyFout << MY_PK_OPERATIONCODE_MR << MY_SEPARATOR << MY_PK_OPERATIONNAME_MR << MY_SEPARATOR;
			}
			else
			{
				jyFout << MY_PK_OPERATIONCODE_MC << MY_SEPARATOR << MY_PK_OPERATIONNAME_MC << MY_SEPARATOR;
			}
			jyFout << jgmxls.fid_zqdm << MY_SEPARATOR << jgmxls.fid_zqmc << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << jgmxls.fid_jszh << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << jgmxls.fid_cjsl << MY_SEPARATOR << jgmxls.fid_cjje << MY_SEPARATOR << jgmxls.fid_s1 << MY_SEPARATOR << "0" << MY_SEPARATOR << jgmxls.fid_s2 << MY_SEPARATOR << jgmxls.fid_s3 << MY_SEPARATOR << "0" << MY_SEPARATOR << "0" << MY_SEPARATOR << jgmxls.fid_ysje << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << jgmxls.fid_jszh << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR;
			if (strcmp(jgmxls.fid_jys, MY_JYS_SH) == 0)
			{
				jyFout << MY_BOURSECODE_SH;
			}
			else
			{
				jyFout << MY_BOURSECODE_SZ;
			}
			jyFout << endl;
		}
		else if (jgmxls.fid_wtlb == MY_WTLB_RQ || jgmxls.fid_wtlb == MY_WTLB_RQGH)
		{
			hgHeadCount++;
			if (hgHeadCount == 1)
			{
				hgFout.open(Get_FileName("hg", ksrq, jsrq).c_str());
				hgFout << setprecision(12);
				hgFout << "bill_code" << MY_SEPARATOR << "pk_corp" << MY_SEPARATOR << "trade_date" << MY_SEPARATOR << "pk_operationcode" << MY_SEPARATOR << "pk_operationname" << MY_SEPARATOR << "pk_account" << MY_SEPARATOR << "pk_partner" << MY_SEPARATOR << "pk_selfsgroup" << MY_SEPARATOR << "pk_operatesite" << MY_SEPARATOR << "pk_cumando" << MY_SEPARATOR << "pk_seat" << MY_SEPARATOR << "pk_econtra" << MY_SEPARATOR << "pk_securities" << MY_SEPARATOR << "bargain_nu" << MY_SEPARATOR << "bargain_su" << MY_SEPARATOR << "commision" << MY_SEPARATOR << "handle_fee" << MY_SEPARATOR << "stamp_tax" << MY_SEPARATOR << "other_fee" << MY_SEPARATOR << "fact_sum" << MY_SEPARATOR << "end_date" << MY_SEPARATOR << "pk_repurchase" << MY_SEPARATOR << "backbuy_rate" << MY_SEPARATOR << "backbuy_sum" << MY_SEPARATOR << "outtrade_date" << MY_SEPARATOR << "pk_operator" << MY_SEPARATOR << "operate_date" << MY_SEPARATOR << "pk_assessor" << MY_SEPARATOR << "audit_date" << MY_SEPARATOR << "state" << MY_SEPARATOR << "ndef1" << MY_SEPARATOR << "ndef2" << MY_SEPARATOR << "ndef3" << MY_SEPARATOR << "ndef4" << MY_SEPARATOR << "ndef5" << MY_SEPARATOR << "vdef1" << MY_SEPARATOR << "vdef2" << MY_SEPARATOR << "vdef3" << MY_SEPARATOR << "vdef4" << MY_SEPARATOR << "vdef5" << MY_SEPARATOR << "boursecode" << endl;
			}
			hgFout << jgmxls.fid_jys << jgmxls.fid_cjrq << jgmxls.fid_wth << MY_SEPARATOR << MY_PK_CORP << MY_SEPARATOR << jgmxls.fid_cjrq << MY_SEPARATOR;
			if (jgmxls.fid_wtlb == MY_WTLB_RQ)
			{
				hgFout << MY_PK_OPERATIONCODE_HG << MY_SEPARATOR;
				hgFout << MY_PK_OPERATIONNAME_RQHG << MY_SEPARATOR;
			}
			else
			{
				hgFout << MY_PK_OPERATIONCODE_GH << MY_SEPARATOR;
				hgFout << MY_PK_OPERATIONNAME_RQGH << MY_SEPARATOR;
			}
			hgFout << jgmxls.fid_jszh << MY_SEPARATOR << MY_PK_PARTER << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_PK_PARTER << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << jgmxls.fid_zqdm << MY_SEPARATOR << jgmxls.fid_cjsl << MY_SEPARATOR << jgmxls.fid_cjsl * 1000L << MY_SEPARATOR << jgmxls.fid_s1 << MY_SEPARATOR << 0 << MY_SEPARATOR << 0 << MY_SEPARATOR << 0 << MY_SEPARATOR << jgmxls.fid_ysje << MY_SEPARATOR << jgmxls.fid_cjrq << MY_SEPARATOR << MY_SEPARATOR << jgmxls.fid_lxje << MY_SEPARATOR;
			hgFout << (jgmxls.fid_cjsl * 1000L + jgmxls.fid_lxje) << MY_SEPARATOR << jgmxls.fid_cjrq << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << jgmxls.fid_jszh << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR << MY_SEPARATOR;
			if (strcmp(jgmxls.fid_jys, MY_JYS_SH) == 0)
			{
				hgFout << MY_BOURSECODE_SH;
			}
			else
			{
				hgFout << MY_BOURSECODE_SZ;
			}
			hgFout << endl;
		}
		else
		{
			otherHeadCount++;
			if (otherHeadCount == 1)
			{
				otherFout.open(Get_FileName("other_jgmxls", ksrq, jsrq).c_str());
				otherFout << setprecision(12);
				otherFout << "股东姓名" << "," << "交易所" << "," << "结算帐户" << "," << "委托方式" << "," << "席位代码" << "," << "证券代码" << "," << "证券类别" << "," << "成交时间" << "," << "申报时间" << "," << "利息价格" << "," << "成交金额" << "," << "利息金额" << "," << "标志佣金" << "," << "过户费" << "," << "结算费" << "," << "本次资金余额" << "," << "本次盈亏" << "," << "登录ID" << "," << "审核柜员" << "," << "营业部" << "," << "成交编号" << "," << "佣金" << "," << "附加费" << "," << "结算机构" << "," << "证券名称" << "," << "委托类别" << "," << "成交日期" << "," << "成交笔数" << "," << "成交数量" << "," << "成交价格" << "," << "结算价" << "," << "印花税" << "," << "交易规费" << "," << "应收金额" << "," << "本次股份余额" << "," << "入帐日期" << "," << "币种" << "," << "交收日期" << "," << "佣金定价策略" << "," << "佣金定价方式" << "," << "股东号" << "," << "冻结数量" << "," << "登录身份" << "," << "本次冻结数量" << "," << "应收数量" << "," << "资金明细流水号" << "," << "客户群组" << "," << "公司分类" << "," << "流水号" << "," << "交割资料类别" << "," << "委托号" << "," << "客户姓名" << "," << "客户号" << endl;
				//otherFout<<"股东姓名"<<MY_SEPARATOR<<"交易所"<<MY_SEPARATOR<<"结算帐户"<<MY_SEPARATOR<<"委托方式"<<MY_SEPARATOR<<"席位代码"<<MY_SEPARATOR<<"证券代码"<<MY_SEPARATOR<<"证券类别"<<MY_SEPARATOR<<"成交时间"<<MY_SEPARATOR<<"申报时间"<<MY_SEPARATOR<<"利息价格"<<MY_SEPARATOR<<"成交金额"<<MY_SEPARATOR<<"利息金额"<<MY_SEPARATOR<<"标志佣金"<<MY_SEPARATOR<<"过户费"<<MY_SEPARATOR<<"结算费"<<MY_SEPARATOR<<"本次资金余额"<<MY_SEPARATOR<<"本次盈亏"<<MY_SEPARATOR<<"登录ID"<<MY_SEPARATOR<<"审核柜员"<<MY_SEPARATOR<<"营业部"<<MY_SEPARATOR<<"成交编号"<<MY_SEPARATOR<<"佣金"<<MY_SEPARATOR<<"附加费"<<MY_SEPARATOR<<"结算机构"<<MY_SEPARATOR<<"证券名称"<<MY_SEPARATOR<<"委托类别"<<MY_SEPARATOR<<"成交日期"<<MY_SEPARATOR<<"成交笔数"<<MY_SEPARATOR<<"成交数量"<<MY_SEPARATOR<<"成交价格"<<MY_SEPARATOR<<"结算价"<<MY_SEPARATOR<<"印花税"<<MY_SEPARATOR<<"交易规费"<<MY_SEPARATOR<<"应收金额"<<MY_SEPARATOR<<"本次股份余额"<<MY_SEPARATOR<<"入帐日期"<<MY_SEPARATOR<<"币种"<<MY_SEPARATOR<<"交收日期"<<MY_SEPARATOR<<"佣金定价策略"<<MY_SEPARATOR<<"佣金定价方式"<<MY_SEPARATOR<<"当前分页索引值"<<MY_SEPARATOR<<"股东号"<<MY_SEPARATOR<<"冻结数量"<<MY_SEPARATOR<<"登录身份"<<MY_SEPARATOR<<"本次冻结数量"<<MY_SEPARATOR<<"应收数量"<<MY_SEPARATOR<<"资金明细流水号"<<MY_SEPARATOR<<"客户群组"<<MY_SEPARATOR<<"公司分类"<<MY_SEPARATOR<<"流水号"<<MY_SEPARATOR<<"交割资料类别"<<MY_SEPARATOR<<"委托号"<<MY_SEPARATOR<<"客户姓名"<<MY_SEPARATOR<<"客户号"<<endl;
			}
			otherFout << jgmxls.fid_gdxm << MY_SEPARATOR << jgmxls.fid_jys << MY_SEPARATOR << jgmxls.fid_jszh << MY_SEPARATOR << jgmxls.fid_wtfs << MY_SEPARATOR << jgmxls.fid_xwdm << MY_SEPARATOR << jgmxls.fid_zqdm << MY_SEPARATOR << jgmxls.fid_zqlb << MY_SEPARATOR << jgmxls.fid_cjsj << MY_SEPARATOR << jgmxls.fid_sbsj << MY_SEPARATOR << jgmxls.fid_lxjg << MY_SEPARATOR << jgmxls.fid_cjje << MY_SEPARATOR << jgmxls.fid_lxje << MY_SEPARATOR << jgmxls.fid_bzs1 << MY_SEPARATOR << jgmxls.fid_s3 << MY_SEPARATOR << jgmxls.fid_s5 << MY_SEPARATOR << jgmxls.fid_bczjye << MY_SEPARATOR << jgmxls.fid_bbyk << MY_SEPARATOR << jgmxls.fid_loginid << MY_SEPARATOR << jgmxls.fid_fhgy << MY_SEPARATOR << jgmxls.fid_yyb << MY_SEPARATOR << jgmxls.fid_cjbh << MY_SEPARATOR << jgmxls.fid_s1 << MY_SEPARATOR << jgmxls.fid_s4 << MY_SEPARATOR << jgmxls.fid_jsjg << MY_SEPARATOR << jgmxls.fid_zqmc << MY_SEPARATOR << jgmxls.fid_wtlb << MY_SEPARATOR << jgmxls.fid_cjrq << MY_SEPARATOR << jgmxls.fid_cjbs << MY_SEPARATOR << jgmxls.fid_cjsl << MY_SEPARATOR << jgmxls.fid_cjjg << MY_SEPARATOR << jgmxls.fid_jsj << MY_SEPARATOR << jgmxls.fid_s2 << MY_SEPARATOR << jgmxls.fid_s6 << MY_SEPARATOR << jgmxls.fid_ysje << MY_SEPARATOR << jgmxls.fid_bczqsl << MY_SEPARATOR << jgmxls.fid_rzrq << MY_SEPARATOR << jgmxls.fid_bz << MY_SEPARATOR << jgmxls.fid_jsrq << MY_SEPARATOR << jgmxls.fid_yjdjcl << MY_SEPARATOR << jgmxls.fid_yjdjfs << MY_SEPARATOR << jgmxls.fid_gdh << MY_SEPARATOR << jgmxls.fid_djsl << MY_SEPARATOR << jgmxls.fid_dlsf << MY_SEPARATOR << jgmxls.fid_bcdjsl << MY_SEPARATOR << jgmxls.fid_yssl << MY_SEPARATOR << jgmxls.fid_zjmxlsh << MY_SEPARATOR << jgmxls.fid_khqz << MY_SEPARATOR << jgmxls.fid_gsfl << MY_SEPARATOR << jgmxls.fid_seqno << MY_SEPARATOR << jgmxls.fid_jgzllb << MY_SEPARATOR << jgmxls.fid_wth << MY_SEPARATOR << jgmxls.fid_khxm << MY_SEPARATOR << jgmxls.fid_khh << endl;
		}
	}

	jyFout.close();
	hgFout.close();
	otherFout.close();
	jgmxls_list.clear();

	//AfxMessageBox(_T("End:Write_JGMXLS..."), MB_OK);
}

bool checkDate(long nKsrq, long nJsrq)
{
	if (nKsrq < 20000000L || nJsrq < 20000000L || nKsrq > nJsrq)
	{
		AfxMessageBox(_T("invalid date ! please check ."), MB_OK);
		//exit(0);
		return false;
	}
	return true;
}

void initCharArr(char charArr[])
{
	//charArr = "";
	memset(charArr, '\0', sizeof(charArr));
	//memset(charArr,0,sizeof(charArr));
}

void repComma(char charArr[])
{
	for (unsigned int i = 0; (i<strlen(charArr) - 1) && charArr[i] != '\0'; i++)
	{
		if (charArr[i] == ',')
		{
			charArr[i] = ':';
		}
	}
}

char* d2str(double d, char s[])
{
	memset(s, '\0', sizeof(s));
	sprintf_s(s, sizeof(s), "%.2lf", d);
	return s;
}

LPCWSTR C2LPCWSTR(const char* str)
{
	USES_CONVERSION;
	CString Cstr(str);
	return A2CW(W2A(Cstr));
}

void Split_RQ(TCHAR StrKsrq[], TCHAR StrJsrq[])
{
	CString cmdCStr = (CString)AfxGetApp()->m_lpCmdLine;
	int blank_idx = cmdCStr.Find(' ');
	for (int i = 0; i < blank_idx; i++)
	{
		StrKsrq[i] = cmdCStr[i];
	}
	for (int i = blank_idx + 1, j = 0; i < cmdCStr.GetLength(); i++)
	{
		StrJsrq[j++] = cmdCStr[i];
	}
}

string Get_FileName(char* prefix, char* strKsrq, char* strJsrq)
{
//	string fileName(prefix);
	string datePeriod(strKsrq);
	if (strcmp(strKsrq, strJsrq) != 0)
	{
		datePeriod.append("-");
		datePeriod.append(strJsrq);
	}
//	datePeriod.append(".csv");

	string fileDir(cfg_map[MY_DestDir]);
	fileDir.append(datePeriod);
	fileDir.append("/");
	ofstream outDir(fileDir.c_str());
	if (!outDir.is_open())
	{
		_mkdir(fileDir.c_str());
	}
	else
	{
		outDir.close();
	}
	string fileName(fileDir);
	fileName.append(prefix).append(datePeriod).append(".csv");

	return fileName;
}

map<string, string> Load_Configuration(char* cfgFilePath)
{
	if (cfgFilePath == NULL)
	{
		cfgFilePath = "caiwu.cfg";
	}
	ifstream cfgFin;
	cfgFin.open(cfgFilePath);
	if (!cfgFin.is_open())
	{
		AfxMessageBox(_T("can not open caiwu.cfg ! program will exit!"), MB_OK);
		exit(0);
	}
	int lines = 0;
	map<string, string> cfg_map;
	while (!cfgFin.eof())
	{
		char line[256];
		cfgFin.getline(line, sizeof(line));
		string s = line;
		int i = s.find("=");
		//空白行,#,不包含=或第1个为=，跳过  
		if (s.empty() || s[0] == '#' || i <= 0)
		{
			continue;
		}
		string str_key = s.substr(0, i);
		string str_val = s.substr(i + 1);

		cfg_map[str_key] = str_val;
	}
	string queryDate = Get_QueryDate();
	cfg_map[MY_KSRQ] = queryDate;
	cfg_map[MY_JSRQ] = queryDate;

	cfgFin.close();
	return cfg_map;
}

string WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen <= 0)
		return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst)
		return std::string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;
	std::string strTemp(pszDst);
	delete[] pszDst;
	return strTemp;
}

void Save_Configuration(char* cfgFilePath)
{
	if (cfgFilePath == NULL)
	{
		cfgFilePath = "caiwu.cfg";
	}
	ofstream cfgFout;
	cfgFout.open(cfgFilePath);
	if (!cfgFout.is_open())
	{
		AfxMessageBox(_T("can not open caiwu.cfg ! faild to write configuration to caiwu.cfg!"), MB_OK);
		return;
	}
	/*map<string, string>::iterator it;
	for (it = cfg_map.begin(); it != cfg_map.end();it++)
	{
	cfgFout << it->first.c_str() << "=" << it->second.c_str() << endl;
	}*/
	cfgFout << MY_KHH << "=" << cfg_map[MY_KHH].c_str() << endl;
	cfgFout << MY_User << "=" << cfg_map[MY_User].c_str() << endl;
	cfgFout << MY_Pwd << "=" << cfg_map[MY_Pwd].c_str() << endl;
	cfgFout << MY_Addr << "=" << cfg_map[MY_Addr].c_str() << endl;
	cfgFout << MY_Port << "=" << cfg_map[MY_Port].c_str() << endl;
	cfgFout << MY_Protocol << "=" << cfg_map[MY_Protocol].c_str() << endl;
	cfgFout << MY_TimeOut << "=" << cfg_map[MY_TimeOut].c_str() << endl;
	cfgFout << MY_DestDir << "=" << cfg_map[MY_DestDir].c_str() << endl;

	cfgFout.close();
	cfg_map.clear();
}

void write_TradeDates()
{
	map<string, string> month_days_map = Load_Configuration("2015.csv");
	ofstream fout("2015.txt");
	map<string, string>::iterator it;
	for (it = month_days_map.begin(); it != month_days_map.end(); it++)
	{
		string days = it->second;
		for (unsigned int i = 0; i < days.size(); i++)
		{
			if (days.at(i) == '1')
			{
				fout << "2015";
				fout << (it->first).c_str();

				int d = i + 1;
				if (d < 10)
				{
					fout << "0";
				}
				char aa[10];
				_itoa_s(d, aa, 10);
				fout << aa << endl;
			}
		}
	}
	fout.close();
}

string Get_QueryDate()
{
	//读取今年的交易日历文件，获取最近的交易日
	CTime ct_now = CTime::GetCurrentTime();
	CString date_cstr = ct_now.Format("%Y%m%d");
	long date = _ttol(date_cstr);
	//long date = 20150319L;

	int y = ct_now.GetYear();
	int m = ct_now.GetMonth();
	int d = ct_now.GetDay();
	char y_str[12];
	if (m == 1 && d == 1)//1月1日则读取去年的交易日历
	{
		_itoa_s(y - 1, y_str, 10);
	}
	else
	{
		_itoa_s(y, y_str, 10);
	}
	string filePath("tradeDates/");
	filePath.append(y_str).append(".txt");
	ifstream fin(filePath.c_str());
	if (!fin.is_open())
	{
		CString err_cstr;
		err_cstr.Append(_T("can not open "));
		CString ss(filePath.c_str());
		err_cstr.Append(ss);
		err_cstr.Append(_T(" ! program will exit."));

		AfxMessageBox(err_cstr, MB_OK);
		exit(0);
	}
	long validTradeDate = -1;
	string validTradeDate_str;
	while (!fin.eof())
	{
		char line[20];
		fin.getline(line, sizeof(line));
		string s = line;
		if (s.empty())
		{
			continue;
		}
		long tmp_TradeDate = atol(s.c_str());
		if (tmp_TradeDate < date)
		{
			if (tmp_TradeDate > validTradeDate)
			{
				validTradeDate = tmp_TradeDate;
				validTradeDate_str = s;
			}
		}
	}

	return validTradeDate_str;
}
