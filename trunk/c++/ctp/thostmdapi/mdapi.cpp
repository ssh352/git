// mdapi.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "mdapi.h"
#include "mdspi.h"
#include "Windows.h"

///����ص��¼�
CMdSpi *mdspi;

///����api
CThostFtdcMdApi *mdapi;

///����MdApi
///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
///@return ��������UserApi
///modify for udp marketdata
//static CThostFtdcMdApi *CreateFtdcMdApi(const char *pszFlowPath = "", const bool bIsUsingUdp=false);
MD_API void CreateFtdcMdApi(const char *pszFlowPath, const bool bIsUsingUdp)
{
	mdapi = CThostFtdcMdApi::CreateFtdcMdApi(pszFlowPath, bIsUsingUdp);
	mdspi = new CMdSpi();
}

///ɾ���ӿڶ�����
///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
MD_API void Release()
{
	mdapi->Release();
}

///��ʼ��
///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
MD_API void Init()
{
	mdapi->Init();
}

///�ȴ��ӿ��߳̽�������
///@return �߳��˳�����
MD_API int Join()
{
	return mdapi->Join();
}

///��ȡ��ǰ������
///@retrun ��ȡ���Ľ�����
///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
MD_API const char *GetTradingDay()
{
	return mdapi->GetTradingDay();
}

///ע��ǰ�û������ַ
///@param pszFrontAddress��ǰ�û������ַ��
///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
MD_API void RegisterFront(char *pszFrontAddress)
{
	mdapi->RegisterFront(pszFrontAddress);
}

///ע�����ַ����������ַ
///@param pszNsAddress�����ַ����������ַ��
///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
///@remark RegisterNameServer������RegisterFront
MD_API void RegisterNameServer(char *pszNsAddress)
{
	mdapi->RegisterNameServer(pszNsAddress);
}

///ע��ص��ӿ�
///@param pSpi �����Իص��ӿ����ʵ��
//MD_API void RegisterSpi(CThostFtdcMdSpi *pSpi) = 0;
MD_API void RegisterSpifp(OnFrontConnectedfp onFrontConnectedfp, OnFrontDisconnectedfp onFrontDisconnectedfp, OnRspUserLoginfp onRspUserLoginfp, OnRspUserLogoutfp onRspUserLogoutfp, OnRspErrorfp onRspErrorfp, OnRspSubMarketDatafp onRspSubMarketDatafp, OnRspUnSubMarketDatafp onRspUnSubMarketDatafp, OnRtnDepthMarketDatafp onRtnDepthMarketDatafp)
{
	mdspi->onFrontConnectedfp = onFrontConnectedfp;
	mdspi->onFrontDisconnectedfp = onFrontDisconnectedfp;
	mdspi->onRspUserLoginfp = onRspUserLoginfp;
	mdspi->onRspUserLogoutfp = onRspUserLogoutfp;
	mdspi->onRspErrorfp = onRspErrorfp;
	mdspi->onRspSubMarketDatafp = onRspSubMarketDatafp;
	mdspi->onRspUnSubMarketDatafp = onRspUnSubMarketDatafp;
	mdspi->onRtnDepthMarketDatafp = onRtnDepthMarketDatafp;
	mdapi->RegisterSpi(mdspi);
}

///�������顣
///@param ppInstrumentID ��ԼID  
///@param nCount Ҫ����/�˶�����ĺ�Լ����
///@remark 
MD_API int SubscribeMarketData(char *ppInstrumentID[], int nCount)
{
	return mdapi->SubscribeMarketData(ppInstrumentID, nCount);
}

///�˶����顣
///@param ppInstrumentID ��ԼID  
///@param nCount Ҫ����/�˶�����ĺ�Լ����
///@remark 
MD_API int UnSubscribeMarketData(char *ppInstrumentID[], int nCount)
{
	return mdapi->UnSubscribeMarketData(ppInstrumentID, nCount);
}

///�û���¼����
MD_API int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID)
{
	char buf[512];
	sprintf(buf, "login:%s|%s|%s|%d",pReqUserLoginField->BrokerID,pReqUserLoginField->UserID, pReqUserLoginField->Password, nRequestID);
	OutputDebugString(buf);
	return mdapi->ReqUserLogin(pReqUserLoginField, nRequestID);
}

///�ǳ�����
MD_API int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	return mdapi->ReqUserLogout(pUserLogout, nRequestID);
}
