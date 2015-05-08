#ifndef _DLL_TRADER_API_H
#define _DLL_TRADER_API_H
#define TRADER_API_EXPORTS
#ifdef TRADER_API_EXPORTS
#define TRADER_API extern "C" __declspec(dllexport)
#else
#define TRADER_API  __declspec(dllimport)
#endif
#include "ThostFtdcUserApiStruct.h"

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
//TRADER_API void RegisterSpi(CThostFtdcTraderSpi *pSpi);

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