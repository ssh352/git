#include "stdafx.h"
#include "thostmdapi.h"
#include "thostmdspi.h"
#include "Windows.h"

///���ӳɹ�
void CMdSpi::OnFrontConnected()
{
	if (onFrontConnectedfp != 0)
	{
		(*onFrontConnectedfp)();
	} else 
	{
		OutputDebugString("onFrontConnectedfp failure!\n");
	}
}

///����ʧ��
void CMdSpi::OnFrontDisconnected(int nReason)
{
	if (onFrontDisconnectedfp != 0)
	{
		OutputDebugString("onFrontDisconnectedfp success!\n");
		(*onFrontDisconnectedfp)(nReason);
	}else
	{
		OutputDebugString("onFrontDisconnectedfp failure!\n");
	}
}

///��¼��Ӧ
void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspUserLoginfp != 0)
	{
		(*onRspUserLoginfp)(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
	}
}

///�ǳ���Ӧ
void CMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspUserLogoutfp != 0)
	{
		(*onRspUserLogoutfp)(pUserLogout, pRspInfo, nRequestID, bIsLast);
	}
}

///����Ӧ��
void CMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspErrorfp != 0)
	{
		(*onRspErrorfp)(pRspInfo, nRequestID, bIsLast);
	}
}

///��������
void CMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspSubMarketDatafp != 0)
	{
		(*onRspSubMarketDatafp)(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
	}
}

///ȡ����������
void CMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (onRspUnSubMarketDatafp != 0)
	{
		(*onRspUnSubMarketDatafp)(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
	}
}

///�������
void CMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	if (onRtnDepthMarketDatafp != 0)
	{
		(*onRtnDepthMarketDatafp)(pDepthMarketData);
	}
}