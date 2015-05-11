#include "stdafx.h"
#include "thosttraderspi.h"

///���ӳɹ���Ӧ
void CTraderSpi::OnFrontConnected()
{
	if (onFrontConnectedfp)
	{
		(*onFrontConnectedfp)();
	}
}
///���ӶϿ���Ӧ
void CTraderSpi::OnFrontDisconnected(int nReason)
{
	if (onFrontDisconnectedfp)
	{
		(*onFrontDisconnectedfp)(nReason);
	}
}

///��¼������Ӧ
void CTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspUserLoginfp)
	{
		(*onRspUserLoginfp)(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
	}
}

///�ǳ�������Ӧ
void CTraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspUserLogoutfp)
	{
		(*onRspUserLogoutfp)(pUserLogout, pRspInfo, nRequestID, bIsLast);
	}
}

///����¼��������Ӧ
void CTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspOrderInsertfp)
	{
		(*onRspOrderInsertfp)(pInputOrder, pRspInfo, nRequestID, bIsLast);
	}
}

///Ԥ��¼��������Ӧ
void CTraderSpi::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspParkedOrderInsertfp)
	{
		(*onRspParkedOrderInsertfp)(pParkedOrder, pRspInfo, nRequestID, bIsLast);
	}
}

///Ԥ�񳷵�¼��������Ӧ
void CTraderSpi::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspParkedOrderActionfp)
	{
		(*onRspParkedOrderActionfp)(pParkedOrderAction, pRspInfo, nRequestID, bIsLast);
	}
}

///��������������Ӧ
void CTraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspOrderActionfp)
	{
		(*onRspOrderActionfp)(pInputOrderAction, pRspInfo, nRequestID, bIsLast);
	}
}

///��ѯ��󱨵�������Ӧ
void CTraderSpi::OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQueryMaxOrderVolumefp)
	{
		(*onRspQueryMaxOrderVolumefp)(pQueryMaxOrderVolume, pRspInfo, nRequestID, bIsLast);
	}
}

///ɾ��Ԥ����Ӧ
void CTraderSpi::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspRemoveParkedOrderfp)
	{
		(*onRspRemoveParkedOrderfp)(pRemoveParkedOrder, pRspInfo, nRequestID, bIsLast);
	}
}

///ɾ��Ԥ�񳷵���Ӧ
void CTraderSpi::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspRemoveParkedOrderActionfp)
	{
		(*onRspRemoveParkedOrderActionfp)(pRemoveParkedOrderAction, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯ������Ӧ
void CTraderSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryOrderfp)
	{
		(*onRspQryOrderfp)(pOrder, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯ�ɽ���Ӧ
void CTraderSpi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryTradefp)
	{
		(*onRspQryTradefp)(pTrade, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯͶ���ֲ߳���Ӧ
void CTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryInvestorPositionfp)
	{
		(*onRspQryInvestorPositionfp)(pInvestorPosition, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯ�ʽ��˻���Ӧ
void CTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryTradingAccountfp)
	{
		(*onRspQryTradingAccountfp)(pTradingAccount, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯͶ������Ӧ
void CTraderSpi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryInvestorfp)
	{
		(*onRspQryInvestorfp)(pInvestor, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯ���ױ�����Ӧ
void CTraderSpi::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryTradingCodefp)
	{
		(*onRspQryTradingCodefp)(pTradingCode, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯ��Լ��֤������Ӧ
void CTraderSpi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryInstrumentMarginRatefp)
	{
		(*onRspQryInstrumentMarginRatefp)(pInstrumentMarginRate, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯ��Լ����������Ӧ
void CTraderSpi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryInstrumentCommissionRatefp)
	{
		(*onRspQryInstrumentCommissionRatefp)(pInstrumentCommissionRate, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯ��������Ӧ
void CTraderSpi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryExchangefp)
	{
		(*onRspQryExchangefp)(pExchange, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯ��Լ��Ӧ
void CTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryInstrumentfp)
	{
		(*onRspQryInstrumentfp)(pInstrument, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯ������Ӧ
void CTraderSpi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryDepthMarketDatafp)
	{
		(*onRspQryDepthMarketDatafp)(pDepthMarketData, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯͶ���ֲ߳���ϸ��Ӧ
void CTraderSpi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryInvestorPositionDetailfp)
	{
		(*onRspQryInvestorPositionDetailfp)(pInvestorPositionDetail, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯ�ͻ�֪ͨ��Ӧ
void CTraderSpi::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryNoticefp)
	{
		(*onRspQryNoticefp)(pNotice, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯͶ���ֲ߳���ϸ��Ӧ
void CTraderSpi::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryInvestorPositionCombineDetailfp)
	{
		(*onRspQryInvestorPositionCombineDetailfp)(pInvestorPositionCombineDetail, pRspInfo, nRequestID, bIsLast);
	}
}

///����Ӧ��
void CTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspErrorfp)
	{
		(*onRspErrorfp)(pRspInfo, nRequestID, bIsLast);
	}
}

///����֪ͨ
void CTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	if (onRtnOrderfp)
	{
		(*onRtnOrderfp)(pOrder);
	}
}

///�ɽ�֪ͨ
void CTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
	if (onRtnTradefp)
	{
		(*onRtnTradefp)(pTrade);
	}
}

///����¼�����ر�
void CTraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
	if (onErrRtnOrderInsertfp)
	{
		(*onErrRtnOrderInsertfp)(pInputOrder, pRspInfo);
	}
}

///������������ر�
void CTraderSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
	if (onErrRtnOrderActionfp)
	{
		(*onErrRtnOrderActionfp)(pOrderAction, pRspInfo);
	}
}

///��Լ����״̬֪ͨ
void CTraderSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
	if (onRtnInstrumentStatusfp)
	{
		(*onRtnInstrumentStatusfp)(pInstrumentStatus);
	}
}

///����֪ͨ
void CTraderSpi::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)
{
	if (onRtnTradingNoticefp)
	{
		(*onRtnTradingNoticefp)(pTradingNoticeInfo);
	}
}

///��ʾ������У�����
void CTraderSpi::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder)
{
	if (onRtnErrorConditionalOrderfp)
	{
		(*onRtnErrorConditionalOrderfp)(pErrorConditionalOrder);
	}
}

///�����ѯԤ����Ӧ
void CTraderSpi::OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryParkedOrderfp)
	{
		(*onRspQryParkedOrderfp)(pParkedOrder, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯԤ�񳷵���Ӧ
void CTraderSpi::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryParkedOrderActionfp)
	{
		(*onRspQryParkedOrderActionfp)(pParkedOrderAction, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯ����֪ͨ��Ӧ
void CTraderSpi::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspQryTradingNoticefp)
	{
		(*onRspQryTradingNoticefp)(pTradingNotice, pRspInfo, nRequestID, bIsLast);
	}
}