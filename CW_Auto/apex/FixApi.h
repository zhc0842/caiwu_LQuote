/*
 * �����м����ƽ̨��Χ����ͷ�ļ� (C++���Ա�׼�ӿ��ļ�)
 * FixApi.h   2007��4�� ����
 * ��FixApi.lib FixApi.dllһ���ṩ��
 * �ʺ�ABOSS2.0��Χ���롣 V2.0.1.7
*/
/*��Ӧ�ڱ�׼ABOSS2�汾*/
#if !defined(AFX_FIXAPI_H__VER2001__INCLUDED_)
#define AFX_FIXAPI_H__VER2001__INCLUDED_

#ifdef USE_FIXAPI_CLASS
    #include <FixApi/FixConn.h>
#endif

#ifdef WIN32
    #ifndef FIX_API_EXPORT
        #define FIX_API_EXPORT  __declspec(dllexport)
    #endif
#else
    #define FIX_API_EXPORT extern "C"
    #define WINAPI
#endif


//���Ӿ��
#define HANDLE_CONN     long

//�Ự���
#define HANDLE_SESSION  long

//������
#define HANDLE_SVC      long

/*  ��������: Fix_Initialize
              �������ӿڿ��ʼ����ֻ�е���һ�ξͿ��ԣ����ܶ�ε��á�
    ��������: 
              ����True��ʾ��ʼ���ɹ���False��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_Initialize();
    FIX_API_EXPORT BOOL Fix_SetAppInfo( const char *pszAppName, const char *pszVer );
/*  ��������: Fix_Uninitialize
              �������ӿڿ�ж�ء�ֻ�е���һ�ξͿ��ԣ����ܶ�ε��á�
    ��������: 
              ����True��ʾ��ʼ���ɹ���False��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_Uninitialize();

/*
  ��������: Fix_SetDefaultInfo
            ����ÿ��ҵ�������ȱʡ��ͷ��Ϣ
  ����˵��: 
            pszUser     -- [in] ϵͳҪ��Ĺ�Ա����(��λ���ַ���)��
            pszWTFS     -- [in] ί�з�ʽ��
            pszFBDM     -- [in] ����Ӫҵ���Ĵ�����Ϣ(��λ���ַ���)
            pszDestFBDM -- [in] Ŀ��Ӫҵ���Ĵ�����Ϣ(��λ���ַ���)

  ��������: 
            ϵͳ��������ΪHANDLE_CONN�����Ӿ�����������ʧ���򷵻�0; �ɹ���Ϊ0;
*/
    FIX_API_EXPORT BOOL Fix_SetDefaultInfo( const char *pszUser, const char *pszWTFS, const char *pszFBDM, const char *pszDestFBDM );

/*
 *	��������:Fix_SetDefaultQYBM
    ����ȱʡ���������
 */
    FIX_API_EXPORT BOOL Fix_SetDefaultQYBM( const char *pszQYBM );
/*
  ��������: Fix_ConnectEx
            ���ӵ������м����������
  ����˵��: (�������²���������)
     pszAddr:��������ַ�ַ���,��ʽ [ip]@[port]/tcp ����:127.0.0.1@9901/tcp
     pszUser:ͨ���û��� (�ɿͻ��ṩ,��û������ͨ���û���Ϊ��)
     pszPwd: ͨ������ (�ɿͻ��ṩ,��û������ͨ���û���Ϊ��)
     pszFileCert: �ͻ���֤���ļ�(�ɿͻ��ṩ)
     pszCertPwd: �ͻ���֤������
     pszProcotol:
	             "SSLv3":����SSLv3Э��; 
				 "TLSv1":����TLSv1Э��; 
				 Ϊ�ջ�����: pszFileCert��Ϊ��,֤���׼��ȫ��֤��ʽ
				             pszFileCertΪ��, ��׼��֤��ʽ
	 pszFileCA:����֤���ļ�(һ�������Ϊ��,��Ϊ����֤���Ѿ��ڿͻ���֤���У����ǿͻ����ر��ṩ)     
	 bVerify:��֤������֤��; true��ʾ��֤; false:����֤������֤��; ��������Ϊ true
	 nTimeOUT:��֤��ʱʱ��(��λ��)
*/
    FIX_API_EXPORT HANDLE_CONN Fix_ConnectEx( const char *pszAddr, const char *pszUser, const char *pszPwd, const char *pszFileCert, const char *pszCertPwd, const char *pszFileCA, const char *pszProcotol, bool bVerify, long nTimeOut );
/*
  ��������: Fix_Connect(����ʹ��Fix_ConnectEx����)
            ���ӵ������м����������
  ����˵��: 
            pszAddr  -- [in] ΪҪ���ӵķ�������ַ; ��ʽΪ: "ip��ַ@�˿�/tcp"
            pszUser  -- [in]  ͨ���û�����; �ɿͻ��ṩ��
            pszPwd   -- [in] ͨ���û�������; �ɿͻ��ṩ��
            nTimeOut -- [in] ���ӳ�ʱ��ʱ�䡣��λΪ�롣

  ��������: 
            ϵͳ��������ΪHANDLE_CONN�����Ӿ�����������ʧ���򷵻�0; �ɹ���Ϊ0;
			������Ĭ�����ö����Զ��������ƣ����Ҫ�ر�����Fix_Connect�ɹ������Fix_SetAutoReconnect����
*/
    FIX_API_EXPORT HANDLE_CONN  Fix_Connect( const char *pszAddr, const char *pszUser, const char *pszPwd, long nTimeOut );
    FIX_API_EXPORT BOOL Fix_AddBackupSvrAddr( const char *pszAddr );
/*
  ��������: Fix_Close
            �붥���м�����ӹرա�
  ����˵��: 
            conn -- [in] ����ΪHANDLE_CONN�����Ӿ�����þ����Fix_Connect���ɵġ�
  ��������: 
            ����ֵΪTrue��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_Close( HANDLE_CONN conn );

/*
  ��������: Fix_AllocateSession
            ����һ�����Ӿ������һ���Ự������������ݽ�����
            ���û��Լ���Ӧ�ò�ͨ������Fix_AllocateSession��������Ķ���������û��Լ�����Fix_ReleaseSession���ͷš�
            ��֮�򲻱�Ҫ��ԭ������ѭ��˭����˭�ͷš��������Ϳ���ȷ���ڴ治й¶��
  ����˵��: 
            conn -- [in] ����ΪHANDLE_CONN�����Ӿ�����þ����Fix_Connect���ɵġ�
  ��������: 
            ����ֵ����ΪHANDLE_SESSION�ĻỰ�����������ֵΪ�ձ�ʾ�������ʧ�ܡ������ʾ�ɹ���
*/
    FIX_API_EXPORT HANDLE_SESSION Fix_AllocateSession( HANDLE_CONN conn );

/*
  ��������: Fix_ReleaseSession
            �ͷŻỰ�����
  ����˵��: 
            sess -- [in] ����ΪHANDLE_SESSION�ĻỰ����
  ��������: 
            ����ֵΪTrue��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_ReleaseSession( HANDLE_SESSION sess );

/*
  ��������: Fix_SetTimeOut
            ���ûỰ�����ĳ�ʱʱ�䡣
  ����˵��: 
            conn    -- [in] ����ΪHANDLE_CONN�����Ӿ�����þ����Fix_Connect���ɵġ�
            timeout -- [in] ҵ��Ӧ��ʱʱ�䣻��λΪ�룬ϵͳĬ��Ϊ30�롣
  ��������: 
            ����ֵΪTrue��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_SetTimeOut( HANDLE_SESSION sess, long timeout );

/*
   ��������: Fix_SetWTFS
             ���ûỰ��ί�з�ʽ.(������Fix_CreateHead����֮ǰ����)
   ����˵��: 
             sess -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
             val  -- [in] �ַ������͡����ڱ�ʾ�ͻ��Ľ��뷽ʽ��
                          ����绰ί�У��ſ�ί�У�������ί�еȡ�
   ��������: 
             ����ֵΪTrue��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_SetWTFS( HANDLE_SESSION sess, const char *val );

/*
   ��������: Fix_SetFBDM
             ���ûỰ�ķ���Ӫҵ������.(������Fix_CreateHead����֮ǰ����)
   ����˵��: 
             sess -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
             val  -- [in] �ַ������͡����ڱ�ʾ�ͻ�ҵ������Ӫҵ����,��������λ��Ӫҵ������;
   ��������: 
             ����ֵΪTrue��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_SetFBDM( HANDLE_SESSION sess, const char *val );

/*
   ��������: Fix_SetFBDM
             ���ûỰ�ķ���Ӫҵ������.(������Fix_CreateHead����֮ǰ����)
   ����˵��: 
             sess -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
             val  -- [in] �ַ������͡����ڱ�ʾ�ͻ�ҵ�񵽴��Ŀ���Ӫҵ����,��������λ��Ӫҵ������;
   ��������: 
             ����ֵΪTrue��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_SetDestFBDM( HANDLE_SESSION sess, const char *val );

/*
   ��������: Fix_SetNode
             ���ûỰ��ҵ�����Ľڵ���Ϣ.(������Fix_CreateHead����֮ǰ����)
   ����˵��: 
             sess -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
             val  -- [in] �ַ������͡�һ���ǿͻ�������Ϣ��IP��ַ��
   ��������: 
             ����ֵΪTrue��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_SetNode( HANDLE_SESSION sess, const char *val );

/*
   ��������: Fix_SetGYDM
            ���ûỰ��ҵ�����Ĺ�Ա������Ϣ.(������Fix_CreateHead����֮ǰ����)
   ����˵��: sess -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
             val  -- [in] �ַ������͡���һЩ��̨����ҵ����Ҫ�õ���Ա��Ϣ������֤��
   ��������: ����ֵΪTrue��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_SetGYDM( HANDLE_SESSION sess, const char *val );

/*
   ��������: Fix_CreateHead
             ���ûỰ��ҵ���ܺ�.����Ĺ��ܺŵĶ�������ա�����������ҵ��ӿ��ĵ�����
   ����˵��: 
             sess  -- [in]  ����ΪHANDLE_SESSION�ĻỰ�����
             nFunc -- [in]  ���͡���Ϊϵͳ�ṩ��ҵ���ܺš�
   ��������: 
             ����ֵΪTrue��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_CreateHead( HANDLE_SESSION sess, long nFunc );
#ifdef WIN32
    FIX_API_EXPORT BOOL Fix_CreateHead( HANDLE_SESSION sess, const char *pszFunc );
#endif
    FIX_API_EXPORT BOOL Fix_CreateReq( HANDLE_SESSION sess, long nFunc );
/*
   ��������: Fix_SetItem
             ���øûỰҪ���͸��м����ҵ������������� �����Ӧ�������ݡ�
             ע:( ����Ӧ��������ֻ�����һЩ�м��ҵ����Ҫ�������������������ʹ�á�
                  ������Ҫ��ͨ��ע�����ʵ��; һ�������²�ʹ�ø÷�ʽ���롣)
   ����˵��: 
             sess -- [in]  ����ΪHANDLE_SESSION�ĻỰ�����
             id   -- [in]  �������tagֵ������Ķ���ֵ��ο�������������ҵ��ӿ��ĵ�����
             val  -- [in]  �ַ�������;��Ӧ��id��ҵ�����ݡ�
   ��������: 
             ����ֵΪTrue��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_SetItem( HANDLE_SESSION sess, long id, const char *val );
    FIX_API_EXPORT BOOL Fix_SetString( HANDLE_SESSION sess, long id, const char *val );
    FIX_API_EXPORT BOOL Fix_SetLong( HANDLE_SESSION sess, long id, long val );
    FIX_API_EXPORT BOOL Fix_SetDouble( HANDLE_SESSION sess, long id, double val );

/*
   ��������: Fix_SetItem
             ���øûỰҪ���͸��м����ҵ������������� �����Ӧ�������ݡ�  
   ����˵��: 
             sess -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
             id   -- [in] �������tagֵ������Ķ���ֵ��ο�������������ҵ��ӿ��ĵ�����
             val  -- [in] ����;��Ӧ��id��ҵ�����ݡ�
   ��������: 
             ����ֵΪTrue��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
#ifdef WIN32
    FIX_API_EXPORT BOOL Fix_SetItem( HANDLE_SESSION sess, long id, long val );
#endif

/*
   ��������: Fix_SetItem
             ���øûỰҪ���͸��м����ҵ������������� �����Ӧ�������ݡ�  
   ����˵��: 
             sess -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
             id   -- [in] �������tagֵ������Ķ���ֵ��ο�������������ҵ��ӿ��ĵ�����
             val  -- [in] ��������;��Ӧ��id��ҵ�����ݡ�
   ��������: 
             ����ֵΪTrue��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
#ifdef WIN32
    FIX_API_EXPORT BOOL Fix_SetItem( HANDLE_SESSION sess, long id, double val );
#endif

/*
   ��������: Fix_Run
             �ύҵ�����ݣ����ȴ�ȫ����ҵ�������ء�  
   ����˵��: 
             sess -- [in]  ����ΪHANDLE_SESSION�ĻỰ�����

   ��������: 
             ����ֵΪTrue��ʾ����ҵ����ɹ�; FALSE��ʾʧ��,���ʧ���Ǳ�ʾҵ��ͨ���ϵ�ʧ�ܣ�
             ʧ�ܺ󣬿���ͨ��Fix_GetCodeȡ��������(�ض���һ������)��ͨ��Fix_GetErrMsgȡ���������Ϣ��
*/
    FIX_API_EXPORT BOOL Fix_Run( HANDLE_SESSION sess );

/*
   ��������: Fix_Cancel
             ֱ�ӷ����ȴ�ҵ���Ӧ�����ݡ�(��ͬ����ʽ��ʹ��)
   ����˵��: 
             sess -- [in]  ����ΪHANDLE_SESSION�ĻỰ�����

   ��������: 
             ����ֵΪTRUE��ʾ�ɹ�; FALSE��ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_Cancel( HANDLE_SESSION sess );


/*
   ��������: Fix_AsyncRun
             �첽�ύҵ�����ݣ����ȴ���ȫ����ҵ�������ء�
             �ͺ���Fix_IsReplyed���ʹ��.
   ����˵��: 
             sess -- [in]  ����ΪHANDLE_SESSION�ĻỰ�����

   ��������: 
             ����ֵΪTrue��ʾ����ҵ����ɹ�; FALSE��ʾʧ��,���ʧ���Ǳ�ʾҵ��ͨ���ϵ�ʧ�ܣ�
             ʧ�ܺ󣬿���ͨ��Fix_GetCodeȡ��������(�ض���һ������)��ͨ��Fix_GetErrMsgȡ���������Ϣ��
*/
    FIX_API_EXPORT BOOL Fix_AsyncRun( HANDLE_SESSION sess );

/*
   ��������: Fix_IsReplyed
             �첽�ύҵ�����ݺ󣬼�������Ƿ�ȫ�����ء�
   ����˵��: 
             sess -- [in]  ����ΪHANDLE_SESSION�ĻỰ�����
             nMSec [in/option] ָ���ȴ���ʱ�䣬Ĭ�ϲ��ȴ�����λΪ���롣

   ��������: 
             ����ֵΪTrue��ʾӦ������ȫ������; FALSE��ʾ��Ҫ�����ȴ���
*/
    FIX_API_EXPORT BOOL Fix_IsReplyed( HANDLE_SESSION sess, long nMSec=-1 );

/*
   ��������: Fix_GetCode
             ��ȡҵ���ύʧ�ܵĴ�����롣  
   ����˵��: 
             sess -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
   ��������: 
             ���ظ�������
*/
    FIX_API_EXPORT long Fix_GetCode( HANDLE_SESSION sess );

/*
   ��������: Fix_GetErrMsg
             ��ȡҵ���ύʧ�ܵĴ�����Ϣ��  
   ����˵��: 
             sess   -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
             out    -- [in/out] �������������Ϣ���ַ���.
             outlen -- [in] ����out�������Ĵ�С.
   ��������: 
             ���ش�����Ϣ�ַ�����
*/
    FIX_API_EXPORT char *Fix_GetErrMsg( HANDLE_SESSION sess, char *out, int outlen );

/*
   ��������: Fix_GetCount
             ��ȡ�м�����ص�ҵ��Ӧ�����ݵ�������  
   ����˵��: 
             sess -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
   ��������: 
             ������������
*/
    FIX_API_EXPORT long Fix_GetCount( HANDLE_SESSION sess );

/*
   ��������: Fix_GetItem
             1�����м���ķ��ؽ������ָ�����ж�ȡҵ��Ӧ�����ݡ�
             2�������Ƕ�ȡ�м�������ҵ������
   ����˵��: 
             sess   -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
             id     -- [in] ָ�����tagֵ������Ķ���ֵ��ο�������������ҵ��ӿ��ĵ�����
             out    -- [in/out] �������ҵ����Ϣ���ַ���.
             outlen -- [in] ָ��out�������Ĵ�С.
             row    -- [in][option] ָ���������ݽ�����е�����(��������ֵ��0��ʼ).������������ֵ��
                       ��ʾ��ȡ��һ�е����ݡ�
   ��������: 
             ����ָ���еĵ��ַ������ݡ�
*/
    FIX_API_EXPORT char *Fix_GetItem( HANDLE_SESSION sess, long id, char *out, int outlen, long row = -1 );
    
/*
   ��������: Fix_GetLong
             1�����м���ķ��ؽ������ָ�����ж�ȡҵ��Ӧ�����ݡ�
             2�������Ƕ�ȡ�м�������ҵ������
   ����˵��: 
             sess   -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
             id     -- [in] ָ�����tagֵ������Ķ���ֵ��ο�������������ҵ��ӿ��ĵ�����
             row    -- [in][option] ָ���������ݽ�����е�����(��������ֵ��0��ʼ).������������ֵ��
                       ��ʾ��ȡ��һ�е����ݡ�
   ��������: 
             ����ָ���е��������ݡ�
*/
    FIX_API_EXPORT long Fix_GetLong( HANDLE_SESSION sess, long id, long row = -1 );
  
/*
   ��������: Fix_GetDouble
             1�����м���ķ��ؽ������ָ�����ж�ȡҵ��Ӧ�����ݡ�
             2�������Ƕ�ȡ�м�������ҵ������
   ����˵��: 
             sess   -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
             id     -- [in] ָ�����tagֵ������Ķ���ֵ��ο�������������ҵ��ӿ��ĵ�����
             row    -- [in][option] ָ���������ݽ�����е�����(��������ֵ��0��ʼ).������������ֵ��
                       ��ʾ��ȡ��һ�е����ݡ�
   ��������: 
             ����ָ���еĸ������ݡ�
*/
    FIX_API_EXPORT double Fix_GetDouble( HANDLE_SESSION sess, long id, long row = -1 );

/*
   ��������: Fix_HaveItem
             1������м���ķ��ؽ������ָ�������Ƿ���ָ����
             2�����߼���м�������ҵ�������Ƿ���ָ����
   ����˵��: 
             sess   -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
             id     -- [in] ָ�����tagֵ������Ķ���ֵ��ο�������������ҵ��ӿ��ĵ�����
             row    -- [in][option] ָ���������ݽ�����е�����(��������ֵ��0��ʼ).������������ֵ��
                       ��ʾ��ȡ��һ�е����ݡ�
   ��������: 
             ����True��ʾ,����ָ���������ݣ�����û�С�
*/
    FIX_API_EXPORT BOOL Fix_HaveItem( HANDLE_SESSION sess, long id, long row = -1 );


/*
   ��������: Fix_CreateAnswer
             ��������Ӧ������;���ڵ��е�����Ӧ��
   ����˵��: 
             sess        -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
   ��������: 
             ����True��ʾ�ɹ��������ʾʧ�ܡ�
*/

    FIX_API_EXPORT BOOL Fix_CreateAnswer( HANDLE_SESSION sess );

/*
   ��������: Fix_CreateAnswerMul
             ��������Ӧ������;���ڶ��е�����Ӧ�𡣱����Fix_CreateNextAnswer��Fix_CreateEndMark���ʹ�á�
             ������Բ���Sample2�Ĵ��롣
   ����˵��: 
             sess        -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
   ��������: 
             ����True��ʾ�ɹ��������ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_CreateAnswerMul( HANDLE_SESSION sess );

/*
   ��������: Fix_CreateNextAnswer
             ��������Ӧ������;�ڶ��е�����Ӧ�𡣴�����һ����Ӧ�����ݡ�
             ������Բ���Sample2�Ĵ��롣
   ����˵��: 
             sess        -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
   ��������: 
             ����True��ʾ�ɹ��������ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_CreateNextAnswer( HANDLE_SESSION sess );

/*
   ��������: Fix_CreateEndMark
             ��������Ӧ������;�ڶ��е�����Ӧ�𡣴�������Ӧ�����ݡ�
             ������Բ���Sample2�Ĵ��롣
   ����˵��: 
             sess        -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
   ��������: 
             ����True��ʾ�ɹ��������ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_CreateEndMark( HANDLE_SESSION sess );

/*
   ��������: Fix_Write
             ����Ӧ�����ݡ�
             ������Բ���Sample2�Ĵ��롣
   ����˵��: 
             sess        -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
   ��������: 
             ����True��ʾ�ɹ��������ʾʧ�ܡ�
*/
    FIX_API_EXPORT BOOL Fix_Write( HANDLE_SESSION sess );

//�򵥼��ܺ���(�û��������)
    FIX_API_EXPORT char *Fix_Encode( char *pData );

/*
   ��������: Fix_GetToken
             ȡ�����ڵ������ַ���(��ѡ�����̨ϵͳ�����й�)
*/

    FIX_API_EXPORT char *Fix_GetToken( HANDLE_SESSION sess, char *out, int outlen );
/*
   ��������: Fix_SetToken
             ���ûỰ������(��ѡ�����̨ϵͳ�����й�)
*/
    FIX_API_EXPORT BOOL Fix_SetToken( HANDLE_SESSION sess, const char *val );

//����дͨ����־����
    FIX_API_EXPORT BOOL Fix_WriteLog( BOOL bWrite );
/*
   ��������: Fix_IsConnect
             �ж�����״̬
*/
FIX_API_EXPORT BOOL Fix_IsConnect( HANDLE_CONN conn );

//���ü����㷨����
FIX_API_EXPORT BOOL Fix_SetCrypto( const char *pszName );

//����ͨ���ж�/�����¼�

//�ص���������ԭ��
//bool Func( HANDLE_CONN conn, long nEvent, void *pRecv )
//nEvent = 0,��ʾ�����Ѿ�������
//nEvent = 1;��ʾ�����Ѿ��ж�
FIX_API_EXPORT BOOL Fix_SetConnEvent( HANDLE_CONN conn, void *pFunc );
//���ô���
FIX_API_EXPORT BOOL Fix_SetProxy( int nType, const char  *pszAddr, long nPort, const char *pszUser, const char *pszPwd );

// ����/����HANDLE_CONN�����Զ��������ƣ�Ĭ�����ã���������������Լ�����HANDLE_CONN����, ������Զ������رգ����ⲻ��Ҫ����Դ�˷�
FIX_API_EXPORT BOOL Fix_SetAutoReconnect(HANDLE_CONN conn, BOOL bAutoReconnect);

// ��ȡ����HANDLE_CONN�����Զ�����״̬
FIX_API_EXPORT BOOL Fix_GetAutoReconnect(HANDLE_CONN conn);

FIX_API_EXPORT char *Fix_GetLastErrMsg( char *out, int outlen );


/*
  ��������: Fix_SetSystemNo
            ���ñ���ҵ���������ϵͳ���(V2.2.1.2)
  ����˵��: 
            val     -- [in] ϵͳ��š�
*/
    FIX_API_EXPORT BOOL Fix_SetSystemNo( HANDLE_SESSION sess, const char *val );

/*
  ��������: Fix_SetDefaultSystemNo 
            ����ÿ��ҵ�������ȱʡ��ϵͳ���(V2.2.1.2)
  ����˵��: 
            val     -- [in] ϵͳ��š�
*/
    FIX_API_EXPORT BOOL Fix_SetDefaultSystemNo( const char *val );

//��׼��������

//ǰ����Ȩ���� V2.0.3.8

/*
   ��������: Fix_GetColumnCount
             ��ȡָ�������ݵ�������
   ����˵��: 
             sess   -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
			 nRow   -- [in] �����,���㿪ʼ
   ��������: 
             ������������
*/

FIX_API_EXPORT int Fix_GetColumnCount( HANDLE_SESSION sess, int nRow );


/*
    �ͻ����ݶ��ĺ���
    pFuncΪ�ص�����ָ��,��������Ϊ: bool CallBackFunc( HANDLE_CONN conn, HANDLE_SESS sess, long nSubs, void *pData )
    ����connΪ���Ӿ��, nSvc��ʾ����ţ�nSubsΪFix_SubscibeByCustomer���ػص�ֵ������ָ��ĳ�����ĵ����ݡ�
	pszKHH, pszPwd,�ֱ�Ϊ�ͻ�����ͻ����롣
    pData���Ƕ���ʱ��ָ��(����ΪNULLֵ)
	����ֵ����0,���ĳɹ�������ʧ��.����ֵ�������˶�����(�����˶�����)���������
*/
FIX_API_EXPORT long Fix_SubscibeByCustomer(HANDLE_CONN conn, long nSvc, void *pFunc, void *pData,const char *pszKHH, const char *pszPwd );

//�����˶�����
//nHandle: ���ľ����
FIX_API_EXPORT BOOL Fix_UnSubscibeByHandle( long nHandle );

/*
   ��������: Fix_GetValWithIdByIndex
             ��ȡָ���С�ָ�����µ��ֶ�id�� �Լ���Ӧ������
   ����˵��: 
             sess   -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
			 nRow   -- [in] �����,���㿪ʼ(���Fix_GetCount)
			 nIndex -- [in] �����,���㿪ʼ(Fix_GetColumnCount)

			 nFid   -- [out] ��id
			 out	-- [out] ���Ӧ������(�ڴ��ϲ����)
			 nSize	-- [in/out] out�Ĵ�С�������������Ӧ����ʵ���ݴ�С
   ��������: 
             true:�ɹ�
			 false:ʧ��(�������Խ�����out�ڴ治��)
*/
FIX_API_EXPORT BOOL Fix_GetValWithIdByIndex( HANDLE_SESSION sess, int nRow, int nIndex, long &nFid, char *out, int &nSize );

/*
   ��������: Fix_RegReplyCallFunc
             ���ø��첽�Ự��Ӧ��Ӧ��ص�����
   ����˵��: 
		sess   -- [in] ����ΪHANDLE_SESSION�ĻỰ�����
		pFunc  -- [in] 
/*pFuncΪӦ��ص�����, �����첽��������ԭ��
  bool OnSessRely( HANDLE_CONN, HANDLE_SESSION, long )
*/
FIX_API_EXPORT BOOL Fix_RegReplyCallFunc( HANDLE_SESSION hSess, void *pFunc );

//ǰ����Ȩ���� V2.0.3.8 End

#endif
