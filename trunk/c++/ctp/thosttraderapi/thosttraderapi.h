#ifndef _DLL_TRADER_API_H
#define _DLL_TRADER_API_H
#define TRADER_API_EXPORTS
#ifdef TRADER_API_EXPORTS
#define TRADER_API extern "C" __declspec(dllexport)
#else
#define TRADER_API  __declspec(dllimport)
#endif
#include "ThostFtdcUserApiStruct.h"

///////////////////////////////����ص�����ָ��////////////////////////////////////////////
///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
typedef void (*OnFrontConnectedfp)();

///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
///@param nReason ����ԭ��
///        0x1001 �����ʧ��
///        0x1002 ����дʧ��
///        0x2001 ����������ʱ
///        0x2002 ��������ʧ��
///        0x2003 �յ�������
typedef void (*OnFrontDisconnectedfp)(int nReason);

///��¼������Ӧ
typedef void (*OnRspUserLoginfp)(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�ǳ�������Ӧ
typedef void (*OnRspUserLogoutfp)(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///����¼��������Ӧ
typedef void (*OnRspOrderInsertfp)(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///Ԥ��¼��������Ӧ
typedef void (*OnRspParkedOrderInsertfp)(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///Ԥ�񳷵�¼��������Ӧ
typedef void (*OnRspParkedOrderActionfp)(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///��������������Ӧ
typedef void (*OnRspOrderActionfp)(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///��ѯ��󱨵�������Ӧ
typedef void (*OnRspQueryMaxOrderVolumefp)(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///ɾ��Ԥ����Ӧ
typedef void (*OnRspRemoveParkedOrderfp)(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///ɾ��Ԥ�񳷵���Ӧ
typedef void (*OnRspRemoveParkedOrderActionfp)(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯ������Ӧ
typedef void (*OnRspQryOrderfp)(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯ�ɽ���Ӧ
typedef void (*OnRspQryTradefp)(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯͶ���ֲ߳���Ӧ
typedef void (*OnRspQryInvestorPositionfp)(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯ�ʽ��˻���Ӧ
typedef void (*OnRspQryTradingAccountfp)(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯͶ������Ӧ
typedef void (*OnRspQryInvestorfp)(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯ���ױ�����Ӧ
typedef void (*OnRspQryTradingCodefp)(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯ��Լ��֤������Ӧ
typedef void (*OnRspQryInstrumentMarginRatefp)(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯ��Լ����������Ӧ
typedef void (*OnRspQryInstrumentCommissionRatefp)(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯ��������Ӧ
typedef void (*OnRspQryExchangefp)(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯ��Լ��Ӧ
typedef void (*OnRspQryInstrumentfp)(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯ������Ӧ
typedef void (*OnRspQryDepthMarketDatafp)(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯͶ���ֲ߳���ϸ��Ӧ
typedef void (*OnRspQryInvestorPositionDetailfp)(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯ�ͻ�֪ͨ��Ӧ
typedef void (*OnRspQryNoticefp)(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯͶ���ֲ߳���ϸ��Ӧ
typedef void (*OnRspQryInvestorPositionCombineDetailfp)(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///����Ӧ��
typedef void (*OnRspErrorfp)(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///����֪ͨ
typedef void (*OnRtnOrderfp)(CThostFtdcOrderField *pOrder);

///�ɽ�֪ͨ
typedef void (*OnRtnTradefp)(CThostFtdcTradeField *pTrade);

///����¼�����ر�
typedef void (*OnErrRtnOrderInsertfp)(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);

///������������ر�
typedef void (*OnErrRtnOrderActionfp)(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);

///��Լ����״̬֪ͨ
typedef void (*OnRtnInstrumentStatusfp)(CThostFtdcInstrumentStatusField *pInstrumentStatus);

///����֪ͨ
typedef void (*OnRtnTradingNoticefp)(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);

///��ʾ������У�����
typedef void (*OnRtnErrorConditionalOrderfp)(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);

///�����ѯԤ����Ӧ
typedef void (*OnRspQryParkedOrderfp)(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯԤ�񳷵���Ӧ
typedef void (*OnRspQryParkedOrderActionfp)(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�����ѯ����֪ͨ��Ӧ
typedef void (*OnRspQryTradingNoticefp)(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

/////////////////////////////////////������ýӿں���///////////////////////
///����TraderApi
///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
///@return ��������UserApi
//modify for udp marketdata
TRADER_API void CreateFtdcTraderApi(const char *pszFlowPath, const bool bIsUsingUdp);

///ɾ���ӿڶ�����
///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
TRADER_API void Release();

///��ʼ��
///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
TRADER_API void Init();

///�ȴ��ӿ��߳̽�������
///@return �߳��˳�����
TRADER_API int Join();

///��ȡ��ǰ������
///@retrun ��ȡ���Ľ�����
///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
TRADER_API const char *GetTradingDay();

///ע��ǰ�û������ַ
///@param pszFrontAddress��ǰ�û������ַ��
///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
TRADER_API void RegisterFront(char *pszFrontAddress);

///ע�����ַ����������ַ
///@param pszNsAddress�����ַ����������ַ��
///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
///@remark RegisterNameServer������RegisterFront
TRADER_API void RegisterNameServer(char *pszNsAddress);

///ע��ص��ӿ�
///@param pSpi �����Իص��ӿ����ʵ��
TRADER_API void RegisterSpifp(
	///���ӳɹ��ص�
	OnFrontConnectedfp onFrontConnectedfp,

	///����ʧ�ܻص�
	OnFrontDisconnectedfp onFrontDisconnectedfp,

	///��������ص�
	//OnHeartBeatWarningfp onHeartBeatWarningfp,

	///��¼��Ӧ�ص�
	OnRspUserLoginfp onRspUserLoginfp,

	///�ǳ���Ӧ�ص�
	OnRspUserLogoutfp onRspUserLogoutfp,

	///����¼��������Ӧ�ص�
	OnRspOrderInsertfp onRspOrderInsertfp,

	///Ԥ��¼��������Ӧ�ص�
	OnRspParkedOrderInsertfp onRspParkedOrderInsertfp,

	///Ԥ�񳷵�¼��������Ӧ�ص�
	OnRspParkedOrderActionfp onRspParkedOrderActionfp,

	///��������������Ӧ�ص�
	OnRspOrderActionfp onRspOrderActionfp,

	///��ѯ��󱨵�������Ӧ�ص�
	OnRspQueryMaxOrderVolumefp onRspQueryMaxOrderVolumefp,

	///ɾ��Ԥ����Ӧ�ص�
	OnRspRemoveParkedOrderfp onRspRemoveParkedOrderfp,

	///ɾ��Ԥ�񳷵���Ӧ�ص�
	OnRspRemoveParkedOrderActionfp onRspRemoveParkedOrderActionfp,

	///�����ѯ������Ӧ�ص�
	OnRspQryOrderfp onRspQryOrderfp,

	///�����ѯ�ɽ���Ӧ�ص�
	OnRspQryTradefp onRspQryTradefp,

	///�����ѯͶ���ֲ߳���Ӧ�ص�
	OnRspQryInvestorPositionfp onRspQryInvestorPositionfp,

	///�����ѯ�ʽ��˻���Ӧ�ص�
	OnRspQryTradingAccountfp onRspQryTradingAccountfp,

	///�����ѯͶ������Ӧ�ص�
	OnRspQryInvestorfp onRspQryInvestorfp,

	///�����ѯ���ױ�����Ӧ�ص�
	OnRspQryTradingCodefp onRspQryTradingCodefp,

	///�����ѯ��Լ��֤������Ӧ�ص�
	OnRspQryInstrumentMarginRatefp onRspQryInstrumentMarginRatefp,

	///�����ѯ��Լ����������Ӧ�ص�
	OnRspQryInstrumentCommissionRatefp onRspQryInstrumentCommissionRatefp,

	///�����ѯ��������Ӧ�ص�
	OnRspQryExchangefp onRspQryExchangefp,

	///�����ѯ��Լ��Ӧ�ص�
	OnRspQryInstrumentfp onRspQryInstrumentfp,

	///�����ѯ������Ӧ�ص�
	OnRspQryDepthMarketDatafp onRspQryDepthMarketDatafp,

	///�����ѯͶ���ֲ߳���ϸ��Ӧ�ص�
	OnRspQryInvestorPositionDetailfp onRspQryInvestorPositionDetailfp,

	///�����ѯ�ͻ�֪ͨ��Ӧ�ص�
	OnRspQryNoticefp onRspQryNoticefp,

	///�����ѯͶ���ֲ߳���ϸ��Ӧ�ص�
	OnRspQryInvestorPositionCombineDetailfp onRspQryInvestorPositionCombineDetailfp,

	//����Ӧ��ص�
	OnRspErrorfp onRspErrorfp,

	///����֪ͨ
	OnRtnOrderfp onRtnOrderfp,

	///�ɽ�֪ͨ
	OnRtnTradefp onRtnTradefp,

	///����¼�����ر�
	OnErrRtnOrderInsertfp onErrRtnOrderInsertfp,

	///������������ر�
	OnErrRtnOrderActionfp onErrRtnOrderActionfp,

	///��Լ����״̬֪ͨ
	OnRtnInstrumentStatusfp onRtnInstrumentStatusfp,

	///����֪ͨ
	OnRtnTradingNoticefp onRtnTradingNoticefp,

	///��ʾ������У�����
	OnRtnErrorConditionalOrderfp onRtnErrorConditionalOrderfp,

	///�����ѯԤ����Ӧ�ص�
	OnRspQryParkedOrderfp onRspQryParkedOrderfp,

	///�����ѯԤ�񳷵���Ӧ�ص�
	OnRspQryParkedOrderActionfp onRspQryParkedOrderActionfp,

	///�����ѯ����֪ͨ��Ӧ�ص�
	OnRspQryTradingNoticefp onRspQryTradingNoticefp);

///����˽������
///@param nResumeType ˽�����ش���ʽ  
///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
///        THOST_TERT_RESUME:���ϴ��յ�������
///        THOST_TERT_QUICK:ֻ���͵�¼��˽����������
///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
TRADER_API void SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType);

///���Ĺ�������
///@param nResumeType �������ش���ʽ  
///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
///        THOST_TERT_RESUME:���ϴ��յ�������
///        THOST_TERT_QUICK:ֻ���͵�¼�󹫹���������
///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
TRADER_API void SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType);

///�û���¼����
TRADER_API int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID);

///�ǳ�����
TRADER_API int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID);

///����¼������
TRADER_API int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID);

///Ԥ��¼������
TRADER_API int ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID);

///Ԥ�񳷵�¼������
TRADER_API int ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID);

///������������
TRADER_API int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID);

///��ѯ��󱨵���������
TRADER_API int ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID);

///����ɾ��Ԥ��
TRADER_API int ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID);

///����ɾ��Ԥ�񳷵�
TRADER_API int ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID);

///�����ѯ����
TRADER_API int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID);

///�����ѯ�ɽ�
TRADER_API int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID);

///�����ѯͶ���ֲ߳�
TRADER_API int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID);

///�����ѯ�ʽ��˻�
TRADER_API int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID);

///�����ѯͶ����
TRADER_API int ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID);

///�����ѯ���ױ���
TRADER_API int ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID);

///�����ѯ��Լ��֤����
TRADER_API int ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID);

///�����ѯ��Լ��������
TRADER_API int ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID);

///�����ѯ������
TRADER_API int ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID);

///�����ѯ��Լ
TRADER_API int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID);

///�����ѯ����
TRADER_API int ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID);

///�����ѯͶ���ֲ߳���ϸ
TRADER_API int ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID);

///�����ѯ�ͻ�֪ͨ
TRADER_API int ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID);

///�����ѯ������Ϣȷ��
TRADER_API int ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID);

///�����ѯͶ���ֲ߳���ϸ
TRADER_API int ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID);

///�����ѯԤ��
TRADER_API int ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID);

///�����ѯԤ�񳷵�
TRADER_API int ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID);

///�����ѯ����֪ͨ
TRADER_API int ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID);

#endif