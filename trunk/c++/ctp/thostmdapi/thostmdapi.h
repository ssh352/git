#ifndef _DLL_MD_API_H
#define _DLL_MD_API_H
#define MD_API_EXPORTS
#ifdef MD_API_EXPORTS
#define MD_API extern "C" __declspec(dllexport)
#else
#define MD_API  __declspec(dllimport)
#endif
#include "ThostFtdcUserApiStruct.h"
#include "ThostFtdcMdApi.h"
//#include "mdspi.h"

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

///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
//typedef void (*OnHeartBeatWarningfp)(int nTimeLapse);

///��¼������Ӧ
typedef void (*OnRspUserLoginfp)(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�ǳ�������Ӧ
typedef void (*OnRspUserLogoutfp)(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///����Ӧ��
typedef void (*OnRspErrorfp)(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///��������Ӧ��
typedef void (*OnRspSubMarketDatafp)(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///ȡ����������Ӧ��
typedef void (*OnRspUnSubMarketDatafp)(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

///�������֪ͨ
typedef void (*OnRtnDepthMarketDatafp)(CThostFtdcDepthMarketDataField *pDepthMarketData);

///����MdApi
///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
///@return ��������UserApi
///modify for udp marketdata
//static CThostFtdcMdApi *CreateFtdcMdApi(const char *pszFlowPath = "", const bool bIsUsingUdp=false);
MD_API void CreateFtdcMdApi(const char *pszFlowPath, const bool bIsUsingUdp);

///ɾ���ӿڶ�����
///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
MD_API void Release();

///��ʼ��
///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
MD_API void Init();

///�ȴ��ӿ��߳̽�������
///@return �߳��˳�����
MD_API int Join();

///��ȡ��ǰ������
///@retrun ��ȡ���Ľ�����
///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
MD_API const char *GetTradingDay();

///ע��ǰ�û������ַ
///@param pszFrontAddress��ǰ�û������ַ��
///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
MD_API void RegisterFront(char *pszFrontAddress);

///ע�����ַ����������ַ
///@param pszNsAddress�����ַ����������ַ��
///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
///@remark RegisterNameServer������RegisterFront
MD_API void RegisterNameServer(char *pszNsAddress);

///ע��ص��ӿ�
///@param pSpi �����Իص��ӿ����ʵ��
//MD_API void RegisterSpi(CThostFtdcMdSpi *pSpi);
MD_API void RegisterSpifp(OnFrontConnectedfp onFrontConnectedfp, OnFrontDisconnectedfp onFrontDisconnectedfp, OnRspUserLoginfp onRspUserLoginfp, OnRspUserLogoutfp onRspUserLogoutfp, OnRspErrorfp onRspErrorfp, OnRspSubMarketDatafp onRspSubMarketDatafp, OnRspUnSubMarketDatafp onRspUnSubMarketDatafp, OnRtnDepthMarketDatafp onRtnDepthMarketDatafp);

///�������顣
///@param ppInstrumentID ��ԼID  
///@param nCount Ҫ����/�˶�����ĺ�Լ����
///@remark 
MD_API int SubscribeMarketData(char *ppInstrumentID[], int nCount);

///�˶����顣
///@param ppInstrumentID ��ԼID  
///@param nCount Ҫ����/�˶�����ĺ�Լ����
///@remark 
MD_API int UnSubscribeMarketData(char *ppInstrumentID[], int nCount);

///�û���¼����
MD_API int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID);

///�ǳ�����
MD_API int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID);

///����ص��¼�
//CMdSpi *mdspi;

///����api
//CThostFtdcMdApi *mdapi;
#endif