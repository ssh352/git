// traderapi.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "thosttraderapi.h"
#include "thosttraderspi.h"

///���׻ص��¼�
CTraderSpi *traderspi;

///����Դapi
CThostFtdcTraderApi *traderapi;

/////////////////////////////////////������ýӿں���///////////////////////
///����TraderApi
///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
///@return ��������UserApi
//modify for udp marketdata
TRADER_API void CreateFtdcTraderApi(const char *pszFlowPath, const bool bIsUsingUdp)
{
	traderapi = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath, bIsUsingUdp);
	traderspi = new CTraderSpi();
}

///ɾ���ӿڶ�����
///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
TRADER_API void Release()
{
	traderapi->Release();
}

///��ʼ��
///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
TRADER_API void Init()
{
	traderapi->Init();
}

///�ȴ��ӿ��߳̽�������
///@return �߳��˳�����
TRADER_API int Join()
{
	return traderapi->Join();
}

///��ȡ��ǰ������
///@retrun ��ȡ���Ľ�����
///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
TRADER_API const char *GetTradingDay()
{
	return traderapi->GetTradingDay();
}

///ע��ǰ�û������ַ
///@param pszFrontAddress��ǰ�û������ַ��
///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
TRADER_API void RegisterFront(char *pszFrontAddress)
{
	traderapi->RegisterFront(pszFrontAddress);
}

///ע�����ַ����������ַ
///@param pszNsAddress�����ַ����������ַ��
///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
///@remark RegisterNameServer������RegisterFront
TRADER_API void RegisterNameServer(char *pszNsAddress)
{
	traderapi->RegisterNameServer(pszNsAddress);
}

///ע��ص��ӿ�
TRADER_API void RegisterSpifp(OnFrontConnectedfp onFrontConnectedfp, OnFrontDisconnectedfp onFrontDisconnectedfp, OnRspUserLoginfp onRspUserLoginfp, OnRspUserLogoutfp onRspUserLogoutfp, OnRspOrderInsertfp onRspOrderInsertfp, OnRspParkedOrderInsertfp onRspParkedOrderInsertfp, OnRspParkedOrderActionfp onRspParkedOrderActionfp, OnRspOrderActionfp onRspOrderActionfp, OnRspQueryMaxOrderVolumefp onRspQueryMaxOrderVolumefp, OnRspRemoveParkedOrderfp onRspRemoveParkedOrderfp, OnRspRemoveParkedOrderActionfp onRspRemoveParkedOrderActionfp, OnRspQryOrderfp onRspQryOrderfp, OnRspQryTradefp onRspQryTradefp, OnRspQryInvestorPositionfp onRspQryInvestorPositionfp, OnRspQryTradingAccountfp onRspQryTradingAccountfp, OnRspQryInvestorfp onRspQryInvestorfp, OnRspQryTradingCodefp onRspQryTradingCodefp, OnRspQryInstrumentMarginRatefp onRspQryInstrumentMarginRatefp, OnRspQryInstrumentCommissionRatefp onRspQryInstrumentCommissionRatefp, OnRspQryExchangefp onRspQryExchangefp, OnRspQryInstrumentfp onRspQryInstrumentfp, OnRspQryDepthMarketDatafp onRspQryDepthMarketDatafp, OnRspQryInvestorPositionDetailfp onRspQryInvestorPositionDetailfp, OnRspQryNoticefp onRspQryNoticefp, OnRspQryInvestorPositionCombineDetailfp onRspQryInvestorPositionCombineDetailfp, OnRspErrorfp onRspErrorfp, OnRtnOrderfp onRtnOrderfp, OnRtnTradefp onRtnTradefp, OnErrRtnOrderInsertfp onErrRtnOrderInsertfp, OnErrRtnOrderActionfp onErrRtnOrderActionfp, OnRtnInstrumentStatusfp onRtnInstrumentStatusfp, OnRtnTradingNoticefp onRtnTradingNoticefp, OnRtnErrorConditionalOrderfp onRtnErrorConditionalOrderfp, OnRspQryParkedOrderfp onRspQryParkedOrderfp, OnRspQryParkedOrderActionfp onRspQryParkedOrderActionfp, OnRspQryTradingNoticefp onRspQryTradingNoticefp)
{

}
///����˽������
///@param nResumeType ˽�����ش���ʽ  
///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
///        THOST_TERT_RESUME:���ϴ��յ�������
///        THOST_TERT_QUICK:ֻ���͵�¼��˽����������
///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
TRADER_API void SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType)
{
	traderapi->SubscribePrivateTopic(nResumeType);
}

///���Ĺ�������
///@param nResumeType �������ش���ʽ  
///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
///        THOST_TERT_RESUME:���ϴ��յ�������
///        THOST_TERT_QUICK:ֻ���͵�¼�󹫹���������
///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
TRADER_API void SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType)
{
	traderapi->SubscribePublicTopic(nResumeType);
}

///�û���¼����
TRADER_API int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID)
{
	return traderapi->ReqUserLogin(pReqUserLoginField, nRequestID);
}

///�ǳ�����
TRADER_API int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	return traderapi->ReqUserLogout(pUserLogout, nRequestID);
}

///����¼������
TRADER_API int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID)
{
	return traderapi->ReqOrderInsert(pInputOrder, )
}

///Ԥ��¼������
TRADER_API int ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID)
{
	return traderapi->ReqParkedOrderInsert(pParkedOrder, nRequestID);
}

///Ԥ�񳷵�¼������
TRADER_API int ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID)
{
	return traderapi->ReqParkedOrderAction(pParkedOrderAction, nRequestID);
}

///������������
TRADER_API int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID)
{
	return traderapi->ReqOrderAction(pInputOrderAction, nRequestID);
}

///��ѯ��󱨵���������
TRADER_API int ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID)
{
	return traderapi->ReqQueryMaxOrderVolume(pQueryMaxOrderVolume, nRequestID);
}

///����ɾ��Ԥ��
TRADER_API int ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID)
{
	return traderapi->ReqRemoveParkedOrder(pRemoveParkedOrder, nRequestID);
}

///����ɾ��Ԥ�񳷵�
TRADER_API int ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID)
{
	return traderapi->ReqRemoveParkedOrderAction(pRemoveParkedOrderAction, nRequestID);
}

///�����ѯ����
TRADER_API int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID)
{
	return traderapi->ReqQryOrder(pQryOrder, nRequestID);
}

///�����ѯ�ɽ�
TRADER_API int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID)
{
	return traderapi->ReqQryTrade(pQryTrade, nRequestID);
}

///�����ѯͶ���ֲ߳�
TRADER_API int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID)
{
	return traderapi->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
}

///�����ѯ�ʽ��˻�
TRADER_API int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID)
{
	return traderapi->ReqQryTradingAccount(pQryTradingAccount, nRequestID);
}

///�����ѯͶ����
TRADER_API int ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID)
{
	return traderapi->ReqQryInvestor(pQryInvestor, nRequestID);
}

///�����ѯ���ױ���
TRADER_API int ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID)
{
	return traderapi->ReqQryTradingCode(pQryTradingCode, nRequestID);
}

///�����ѯ��Լ��֤����
TRADER_API int ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID)
{
	return traderapi->ReqQryInstrumentMarginRate(pQryInstrumentMarginRate, nRequestID);
}

///�����ѯ��Լ��������
TRADER_API int ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID)
{
	return traderapi->ReqQryInstrumentCommissionRate(pQryInstrumentCommissionRate, nRequestID);
}

///�����ѯ������
TRADER_API int ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID)
{
	return traderapi->ReqQryExchange(pQryExchange, nRequestID);
}

///�����ѯ��Լ
TRADER_API int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID)
{
	return traderapi->ReqQryInstrument(pQryInstrument, nRequestID);
}

///�����ѯ����
TRADER_API int ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID)
{
	return traderapi->ReqQryDepthMarketData(pQryDepthMarketData, nRequestID);
}

///�����ѯͶ���ֲ߳���ϸ
TRADER_API int ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID)
{
	return traderapi->ReqQryInvestorPositionDetail(pQryInvestorPositionDetail, nRequestID);
}

///�����ѯ�ͻ�֪ͨ
TRADER_API int ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID)
{
	return traderapi->ReqQryNotice(pQryNotice, nRequestID);
}

///�����ѯ������Ϣȷ��
TRADER_API int ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID)
{
	return traderapi->ReqQrySettlementInfoConfirm(pQrySettlementInfoConfirm, nRequestID);
}

///�����ѯͶ���ֲ߳���ϸ
TRADER_API int ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID)
{
	return traderapi->ReqQryInvestorPositionCombineDetail(pQryInvestorPositionCombineDetail, nRequestID);
}

///�����ѯԤ��
TRADER_API int ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID)
{
	return traderapi->ReqQryParkedOrder(pQryParkedOrder, nRequestID);
}

///�����ѯԤ�񳷵�
TRADER_API int ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID)
{
	return traderapi->ReqQryParkedOrderAction(pQryParkedOrderAction, nRequestID);
}

///�����ѯ����֪ͨ
TRADER_API int ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID)
{
	return traderapi->ReqQryTradingNotice(pQryTradingNotice, nRequestID);
}
