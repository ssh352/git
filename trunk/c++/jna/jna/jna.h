#if !defined(JNA_API_H)
#define JNA_API_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdio.h"

#if defined(WIN32)
#define JNA_API extern "C" __declspec(dllexport)
#define JNA_API_IMPORT __declspec(dllimport)
#else
#define JNA_API extern "C"
#endif

typedef int CallBackIntType;
typedef double CallBackDoubleType;
typedef char CallBackNameType[10];
typedef char CallBackDateType[9];
typedef char CallBackTimeType[9];
struct CallBackData
{
	CallBackIntType id;

	CallBackNameType name;

	CallBackDateType date;

	CallBackTimeType time;

	CallBackIntType millis;
	
	CallBackDoubleType price;

	CallBackDoubleType price1;

	CallBackDoubleType price2;

	CallBackDoubleType price3;

	CallBackDoubleType price4;
};

///�ص�����
typedef void (*Callback)(const char *str);

///�ṹ��ָ��ص�
typedef void (*Callback1)(CallBackData *data);

///ע��ص��¼�
JNA_API void regesiter(Callback callback);

///ע��ṹ��ָ��ص�
JNA_API void regesiter1(Callback1 callback);

///��������
JNA_API void subData();

///ȡ����������
JNA_API void unsubData();

#endif
