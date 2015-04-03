/***********************************************************************
*         Copyright (C) 2004  ��������������޹�˾ All rights reserved. 
*
*�ļ����ƣ�blsdef.h
*��Ŀ���ƣ�
*ժҪ��    BLS����c/c++�����ͷ�ļ���    
*
*ԭ���ߣ�  ������ҵ��֤ȯ���н���ϵͳABOSS2
*�������ڣ�2007.05.18
*��ע��
*
*��ʷ�޸ļ�¼��
*
*���    ����             �汾                ����                         
*1.      2007.05.18       v1.0.0.1            ������ҵ��֤ȯ���н���ϵͳABOSS2
*    ������
*
**********************************************************************/

#if !defined(_BLSDEF_DEFINE_H)
#define _BLSDEF_DEFINE_H

#include "fiddef.h"  //��ϢԪ����


#define  FUN_SECU_LIST_SFBZ_ZHYW         104010  //��ѯ�ʻ���ҵ���շѱ�׼
#define  FUN_SECU_LIST_QZXX              104027  //��ѯȨ֤��Ϣ
#define  FUN_QUOTE_GETHQ                 104101  //֤ȯ�����ѯ
#define  FUN_SECU_LIST_ETFXX             104105  //��ѯETF������Ϣ
#define  FUN_OFS_LIST_TAXX               105001  //��ѯ����˾����
#define  FUN_OFS_LIST_JJXX               105002  //��ѯ����������
#define  FUN_OFS_LIST_DQDESGPZ           105008  //��ѯ���ڶ����깺Ʒ��
#define  FUN_CUSTOM_CHKTRDPWD            190101  //��������Ч��
#define  FUN_CUSTOM_MODI_TRDPWD          202010  //�ͻ����������޸�
#define  FUN_CUSTOM_MODI_FUNDPWD         202012  //�ͻ��ʽ������޸�
#define  FUN_WBZH_REG_ASSOCIATE_REQ      203101  //�Ǽ���֤ת�ʶ�Ӧ��ϵ����
#define  FUN_WBZH_DESTROY_ASSOCIATE_REQ  203103  //ע����֤ת�ʶ�Ӧ��ϵ����
#define  FUN_WBZH_TRANSFER_SAVING_ZQ     203111  //֤ȯ�����ʽ����(����ת֤ȯ)
#define  FUN_WBZH_TRANSFER_TAKEOUT_ZQ    203113  //֤ȯ�����ʽ�ȡ��(֤ȯת����)
#define  FUN_WBZH_TRANSFER_SAVING_WB     203131  //�����ⲿ�����ʽ�ת��(��ת֤)ҵ��
#define  FUN_WBZH_TRANSFER_TAKEOUT_WB    203133  //�����ⲿ�����ʽ�ת��(֤ת��)ҵ��
#define  FUN_WBZH_YZT_GET_BALANCE        203201  //��ѯ�ⲿ�������ʻ����
#define  FUN_FUND_ACCESS                 203501  //�ʽ��ȡ
#define  FUN_FUND_BOOKING_ACCESS         203515  //�����ȡԤԼ
#define  FUN_SECU_MODI_GDH               204002  //�ɶ��ʻ���Ϣ�޸�
#define  FUN_SECU_ENTRUST_TRADE          204501  //��Ʊ����ί��
#define  FUN_SECU_ENTRUST_WITHDRAW       204502  //��Ʊί�г���
#define  FUN_SECU_CAL_TRADEABLEAMOUNT    204503  //��������������
#define  FUN_SECU_BAT_ENTRUST_BUY        204509  //��������ί��
#define  FUN_SECU_BAT_ENTRUST_SALE       204510  //��������ί��
#define  FUN_SECU_BAT_ENTRUST_WITHDRAW   204511  //��������
#define  FUN_SECU_MIXBAT_ENTRUST_TRADE   204513  //�������ί������
#define  FUN_SECU_ETF_BOOKING_ENTRUST    204518  //ETF����ԤԼί��
#define  FUN_SECU_ETF_WITHDRAW_WXYYWT    204519  //ETF����ԤԼί�г���
#define  FUN_OFS_JJZHKH_ZZ               205004  //�����ʻ���������
#define  FUN_OFS_CXYYWT                  205010  //��������ԤԼί��
#define  FUN_OFS_CXDRWT                  205011  //����������ί��
#define  FUN_OFS_JJWT                    205021  //�����Ϲ��깺���
#define  FUN_OFS_SZFHFS                  205022  //���÷ֺ췽ʽ
#define  FUN_OFS_JJZH                    205025  //����ת��
#define  FUN_CUSTOM_GET_CUSTINFO         302001  //��ѯָ���ͻ�������Ϣ
#define  FUN_CUSTOM_LIST_EXINFO          302005  //��ѯ�ͻ���������
#define  FUN_ACCOUNT_GETZJXXBYZJZH       303001  //���ʽ��ʺŲ�ѯ�ʽ���Ϣ
#define  FUN_ACCOUNT_LIST_ZJXXBYKHH      303002  //���ͻ��Ų�ѯ�ʽ�
#define  FUN_ACCOUNT_LIST_ZJMX           303010  //��ѯ�ͻ��ʽ���ϸ
#define  FUN_WBZH_LIST_YZZZDY            303103  //��ѯ��֤ת�ʶ�Ӧ��ϵ
#define  FUN_WBZH_LIST_ZJJYSQ_ZQ         303111  //��ѯ֤ȯ�����ʽ�������
#define  FUN_WBZH_LIST_ZJJYSQ_WB         303112  //��ѯ�ⲿ�����ʽ�������
#define  FUN_SECU_LIST_GDHBYKHH          304001  //�ͻ��ɶ��Ų�ѯ
#define  FUN_SECU_GETKHHBYGDH            304003  //���ݹɶ��ʺŻ�ȡ�ͻ���
#define  FUN_SECU_LIST_HOLDSTOCK         304101  //�ͻ��ֲֲ�ѯ
#define  FUN_SECU_LIST_ENTRUST           304103  //�ͻ�����ί�в�ѯ
#define  FUN_SECU_LIST_ETFWXRGWT         304108  //��ѯ�ͻ�ETF�����Ϲ�ί��
#define  FUN_SECU_LIST_SSCJ              304109  //�ͻ�ʵʱ�ɽ���ѯ
#define  FUN_SECU_LIST_FBCJ              304110  //�ͻ��ֱʳɽ���ѯ
#define  FUN_SECU_LIST_ETFCFG_HOLDSTOCK  304119  //��ѯ�ͻ�ETF�ɷݹɵĳֲ���Ϣ
#define  FUN_OFS_LIST_JJZHBYKHH          305001  //��ѯ�����ʻ���Ϣ
#define  FUN_OFS_LIST_JJFE               305002  //��ѯ�ͻ�����ݶ�
#define  FUN_OFS_LIST_JJWT               305003  //��ѯ�ͻ�����ί��
#define  FUN_OFS_GETKHHBYJJZH            305004  //�������ʺŲ�ѯ�ͻ���
#define  FUN_ACCOUNT_LIST_ZJMXLS_KH      403201  //�ͻ��ʽ���ϸ��ʷ��ѯ
#define  FUN_SECU_LIST_JGMXLS_KH         404201  //�ͻ�������ϸ��ʷ��ѯ
#define  FUN_SECU_LIST_WTLS_KH           404202  //�ͻ�ί����ʷ��ѯ
#define  FUN_OFS_LIST_JJJGLS             405003  //��ѯ�ͻ���ʷ���𽻸�
#endif // !defined(_BLSDEF_DEFINE_H)
