#include "ThostFtdcTraderApi.h"
#include "thosttraderapi.h"

class CTraderSpi : public CThostFtdcTraderSpi
{
public:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����¼��������Ӧ
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ԥ��¼��������Ӧ
	virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ԥ�񳷵�¼��������Ӧ
	virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������������Ӧ
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��ѯ��󱨵�������Ӧ
	virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ɾ��Ԥ����Ӧ
	virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ɾ��Ԥ�񳷵���Ӧ
	virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ������Ӧ
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ�ɽ���Ӧ
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���ֲ߳���Ӧ
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ�ʽ��˻���Ӧ
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ������Ӧ
	virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ���ױ�����Ӧ
	virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Լ��֤������Ӧ
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Լ����������Ӧ
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��������Ӧ
	virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ������Ӧ
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ�ͻ�֪ͨ��Ӧ
	virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����֪ͨ
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

	///�ɽ�֪ͨ
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

	///����¼�����ر�
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);

	///������������ر�
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);

	///��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);

	///����֪ͨ
	virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);

	///��ʾ������У�����
	virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);

	///�����ѯԤ����Ӧ
	virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯԤ�񳷵���Ӧ
	virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ����֪ͨ��Ӧ
	virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

public:
	///���ӳɹ��ص�
	OnFrontConnectedfp onFrontConnectedfp;

	///����ʧ�ܻص�
	OnFrontDisconnectedfp onFrontDisconnectedfp;

	///��������ص�
	//OnHeartBeatWarningfp onHeartBeatWarningfp;

	///��¼��Ӧ�ص�
	OnRspUserLoginfp onRspUserLoginfp;

	///�ǳ���Ӧ�ص�
	OnRspUserLogoutfp onRspUserLogoutfp;

	///����¼��������Ӧ�ص�
	OnRspOrderInsertfp onRspOrderInsertfp;

	///Ԥ��¼��������Ӧ�ص�
	OnRspParkedOrderInsertfp onRspParkedOrderInsertfp;

	///Ԥ�񳷵�¼��������Ӧ�ص�
	OnRspParkedOrderActionfp onRspParkedOrderActionfp;

	///��������������Ӧ�ص�
	OnRspOrderActionfp onRspOrderActionfp;

	///��ѯ��󱨵�������Ӧ�ص�
	OnRspQueryMaxOrderVolumefp onRspQueryMaxOrderVolumefp;

	///ɾ��Ԥ����Ӧ�ص�
	OnRspRemoveParkedOrderfp onRspRemoveParkedOrderfp;

	///ɾ��Ԥ�񳷵���Ӧ�ص�
	OnRspRemoveParkedOrderActionfp onRspRemoveParkedOrderActionfp;

	///�����ѯ������Ӧ�ص�
	OnRspQryOrderfp onRspQryOrderfp;

	///�����ѯ�ɽ���Ӧ�ص�
	OnRspQryTradefp onRspQryTradefp;

	///�����ѯͶ���ֲ߳���Ӧ�ص�
	OnRspQryInvestorPositionfp onRspQryInvestorPositionfp;

	///�����ѯ�ʽ��˻���Ӧ�ص�
	OnRspQryTradingAccountfp onRspQryTradingAccountfp;

	///�����ѯͶ������Ӧ�ص�
	OnRspQryInvestorfp onRspQryInvestorfp;

	///�����ѯ���ױ�����Ӧ�ص�
	OnRspQryTradingCodefp onRspQryTradingCodefp;

	///�����ѯ��Լ��֤������Ӧ�ص�
	OnRspQryInstrumentMarginRatefp onRspQryInstrumentMarginRatefp;

	///�����ѯ��Լ����������Ӧ�ص�
	OnRspQryInstrumentCommissionRatefp onRspQryInstrumentCommissionRatefp;

	///�����ѯ��������Ӧ�ص�
	OnRspQryExchangefp onRspQryExchangefp;

	///�����ѯ��Լ��Ӧ�ص�
	OnRspQryInstrumentfp onRspQryInstrumentfp;

	///�����ѯ������Ӧ�ص�
	OnRspQryDepthMarketDatafp onRspQryDepthMarketDatafp;

	///�����ѯͶ���ֲ߳���ϸ��Ӧ�ص�
	OnRspQryInvestorPositionDetailfp onRspQryInvestorPositionDetailfp;

	///�����ѯ�ͻ�֪ͨ��Ӧ�ص�
	OnRspQryNoticefp onRspQryNoticefp;

	///�����ѯͶ���ֲ߳���ϸ��Ӧ�ص�
	OnRspQryInvestorPositionCombineDetailfp onRspQryInvestorPositionCombineDetailfp;

	//����Ӧ��ص�
	OnRspErrorfp onRspErrorfp;

	///����֪ͨ
	OnRtnOrderfp onRtnOrderfp;

	///�ɽ�֪ͨ
	OnRtnTradefp onRtnTradefp;

	///����¼�����ر�
	OnErrRtnOrderInsertfp onErrRtnOrderInsertfp;

	///������������ر�
	OnErrRtnOrderActionfp onErrRtnOrderActionfp;

	///��Լ����״̬֪ͨ
	OnRtnInstrumentStatusfp onRtnInstrumentStatusfp;

	///����֪ͨ
	OnRtnTradingNoticefp onRtnTradingNoticefp;

	///��ʾ������У�����
	OnRtnErrorConditionalOrderfp onRtnErrorConditionalOrderfp;

	///�����ѯԤ����Ӧ�ص�
	OnRspQryParkedOrderfp onRspQryParkedOrderfp;

	///�����ѯԤ�񳷵���Ӧ�ص�
	OnRspQryParkedOrderActionfp onRspQryParkedOrderActionfp;

	///�����ѯ����֪ͨ��Ӧ�ص�
	OnRspQryTradingNoticefp onRspQryTradingNoticefp;
};

