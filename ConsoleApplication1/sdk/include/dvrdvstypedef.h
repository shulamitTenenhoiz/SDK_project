/***********************************************************************
** Copyright (C) Tongwei Video Technology Co.,Ltd. All rights reserved.
** Author       : YSW
** Date         : 2010-11-19
** Name         : dvrdvstypedef.h
** Version      : 1.0
** Description  :	����DVR/DVS��ص�һЩ��������
** Modify Record:
1:����
***********************************************************************/
#ifndef __DVR_DVS_TYPEDEF_H__
#define __DVR_DVS_TYPEDEF_H__

#ifdef WIN32 ////////////////////�����Windowsƽ̨
//#include "stdafx.h"  --���� �� �����
typedef DWORD				THREAD_ID;
typedef long                POINTERHANDLE;

//����PACKED ��Ҫ���ڽ����Windows�������һ��ʹ��#pragma pack(n)��Linux��һ��ʹ��__attribute__((packed))
//�ڴ˽ṹ��Ҫд���ļ������ڿ�ƽ̨֮�����ʱ����Ҫ���¶��壬ע��__attribute__((packed))ֻ���ڵ��ֽڶ���
#define PACKED
#else ////////////////////linuxƽ̨
#include <sys/types.h>
#include <stddef.h>

#define PACKED __attribute__((packed))

typedef pid_t				THREAD_ID;
typedef unsigned int       DWORD, *LPDWORD;
typedef unsigned int       ULONG;
//��ż�����ڲ�LONG��ʹ�ã����ֺܶ�ط���ָ��ֱ��ת��LONG,��ĳЩ�ط�LONGֵ����Ϊ��ֵ�������׵Ķ����long long
#if defined (__ENVIRONMENT_LINUX_ANDROID__) || defined (__ENVIRONMENT_IOS__)
    typedef int                LONG;
#else
    #if defined(OS_IS_64BIT)
        typedef long long               LONG;
    #else
        typedef long                LONG;
    #endif
#endif

//�ֻ���handle�õ�long long��win��linux���õ�LONG����Ϊ��ͳһһ�״����Ҳ�Ӱ��ͻ�������POINTERHANDLE������
#if defined (__ENVIRONMENT_LINUX_ANDROID__) || defined (__ENVIRONMENT_IOS__)
    typedef long long                POINTERHANDLE;
#else
    #if defined(OS_IS_64BIT)
        typedef long long               POINTERHANDLE;
    #else
        typedef long                POINTERHANDLE;
    #endif
#endif


typedef unsigned long long  ULONGLONG;


//zld 2016/10/22
#ifdef __ENVIRONMENT_IOS__

#if (TARGET_OS_IPHONE && __LP64__)  ||  TARGET_OS_WATCH
#define OBJC_BOOL_IS_BOOL 1
typedef bool BOOL;
#else
#define OBJC_BOOL_IS_CHAR 1
typedef signed char BOOL;  //wyf
//typedef bool BOOL;
#endif

#else
typedef bool                BOOL;
#endif

typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef int                 INT;
typedef unsigned int        UINT;
typedef long long           LONGLONG; 
typedef void				*HWND, *HDC, *LPVOID;

#define CALLBACK
#define FALSE				false
#define TRUE				true
//#define NULL				0
#endif //WIN32

//��Ƶ��ʽ����
typedef enum _dd_video_format_
{
	DD_VIDEO_FORMAT_NTSC	= 0x01,
	DD_VIDEO_FORMAT_PAL		= 0x02
}DD_VIDEO_FORMAT;

typedef enum _dd_frame_type_
{
	DD_FRAME_TYPE_NONE				= 0x00,//����������֡
	DD_FRAME_TYPE_VIDEO				= 0x01,//��Ƶ����֡
	DD_FRAME_TYPE_AUDIO				= 0x02,//��Ƶ����֡
	DD_FRAME_TYPE_TALK_AUDIO		= 0x03,//�Խ���Ƶ����֡
	DD_FRAME_TYPE_JPEG				= 0x04,//JPEGͼƬ������֡

	DD_FRAME_TYPE_VIDEO_FORMAT		= 0x05,//��Ƶ��ʽ֡
	DD_FRAME_TYPE_AUDIO_FORMAT		= 0x06,//��Ƶ��ʽ֡
	DD_FRAME_TYPE_TALK_AUDIO_FORMAT	= 0x07,//�Խ���Ƶ��ʽ֡

	DD_FRAME_TYPE_RESV1				= 0x08,
	DD_FRAME_TYPE_RESV2				= 0x09,

	DD_FRAME_TYPE_END				= 0x0a,
}DD_FRAME_TYPE;

typedef enum _dd_frame_attrib_
{
	DD_PLAY_FRAME_NO_SHOW			= 0x01,		//��֡����ʾ
	DD_PLAY_FRAME_SHOW				= 0x02,		//��֡����ʾ
	DD_PLAY_FRAME_ALL_END			= 0x04,		//���ݶ�ȡ�����ˣ�������û������
	DD_PLAY_FRAME_SEC_END			= 0x08,		//���¼��ν�����
	DD_PLAY_FRAME_NO_TIME_STAMP		= 0x10,		//��֡������ʱ�����ץͼ��ʱ��ע��Ҫ���δ�ʱ��Ĺ���
	DD_PLAY_FRAME_FF				= 0x20,		//��ǰ֡���ڿ��

	DD_LIVE_FRAME_FIRST_STREAM		= 0x40,		//��֡Ϊ�ֳ�������
	DD_LIVE_FRAME_SECOND_STREAM		= 0x80,		//��֡Ϊ�ֳ�������
	DD_LIVE_FRAME_JPEG				= 0x100,	//��֡ΪJPEGͼƬ
	DD_LIVE_FRAME_TALK				= 0x200,		//��֡Ϊ�Խ���������
    DD_LIVE_FRAME_THIRD_STREAM		= 0x400,		//��֡Ϊ�ֳ���������
    DD_LIVE_FRAME_FOURTH_STREAM		= 0x800,		//��֡Ϊ�ֳ���������
}DD_FRAME_ATTRIB;

//��λ���档��಻�ܳ���32��
typedef enum _dd_video_size_
{
	DD_VIDEO_SIZE_QCIF	= 0x0001,	//QCIF
	DD_VIDEO_SIZE_CIF	= 0x0002,	//CIF
	DD_VIDEO_SIZE_HD1	= 0x0004,	//HD1
	DD_VIDEO_SIZE_D1	= 0x0008,	//D1

	DD_VIDEO_SIZE_QVGA	= 0x0010,	//QVGA
	DD_VIDEO_SIZE_VGA	= 0x0020,	//VGA
	DD_VIDEO_SIZE_XVGA	= 0x0040,	//XVGA
	DD_VIDEO_SIZE_QQVGA	= 0x0080,	//QQVGA

	DD_VIDEO_SIZE_480P	= 0x0100,	//480P
	DD_VIDEO_SIZE_720P	= 0x0200,	//720P
	DD_VIDEO_SIZE_1080P	= 0x0400,	//1080P
	DD_VIDEO_SIZE_960H  = 0x0800,   //960H

	DD_VIDEO_SIZE_960P   = 0x01000,	//(1280 X 960)
	DD_VIDEO_SIZE_SXGA   = 0x02000,	//(1280 X 1024)
	DD_VIDEO_SIZE_3M     = 0x04000,	//(2048 X 1536)

	DD_VIDEO_SIZE_16_9_3M     = 0x10000,	//(2304 X 1296)
	DD_VIDEO_SIZE_2K          = 0x20000,	//(2560 X 1440)
	DD_VIDEO_SIZE_HDLITE      = 0x40000,	//(960 X 1080)
}DD_VIDEO_SIZE;

//��λ���棬���ֻ��Ϊ32����
typedef enum _dd_video_encode_mode_
{
	DD_VIDEO_ENCODE_MODE_VBR	=	0x01,	//������
	DD_VIDEO_ENCODE_MODE_CBR	=	0x02	//�̶�����
}DD_VIDEO_ENCODE_MODE;

typedef enum _dd_video_encode_format_
{
    DD_VIDEO_ENCODE_FORMAT_H264	=	0x0,
    DD_VIDEO_ENCODE_FORMAT_H265	=	0x01,
    DD_VIDEO_ENCODE_FORMAT_MJPEG=	0x02,
    DD_VIDEO_ENCODE_FORMAT_H264PLUS=	0x03,
    DD_VIDEO_ENCODE_FORMAT_H265PLUS=	0x04,
}DD_VIDEO_ENCODE_FORMAT;

typedef enum _dd_image_quality_
{
	DD_IMAGE_QUALITY_LOWEST		= 0x01,
	DD_IMAGE_QUALITY_LOWER		= 0x02,
	DD_IMAGE_QUALITY_LOW		= 0x03,
	DD_IMAGE_QUALITY_MEDIUM		= 0x04,
	DD_IMAGE_QUALITY_HEIGHTER	= 0x05,
	DD_IMAGE_QUALITY_HEIGHTEST	= 0x06
}DD_IMAGE_QUALITY;

//VGA�ֱ��ʣ��ȿ������ڱ���Ҳ��������֧�ֹ��ܲ���,'
//ע�⣺Ҫ��λ��ʾ
typedef enum _dd_vga_resolution_
{
	DD_VGA_640X480		= 0x0001,
	DD_VGA_720X480		= 0x0002,
	DD_VGA_720X576		= 0x0004,
	DD_VGA_800X600		= 0x0008,
	DD_VGA_1024X768		= 0x0010,
	DD_VGA_1280X960		= 0x0020,
	DD_VGA_1280X1024	= 0x0040,
	DD_VGA_1920X1080	= 0x0080,
	DD_VGA_320X240		= 0x0100,
	DD_VGA_352X240		= 0x0200,
	DD_VGA_480X240		= 0x0400,
	DD_VGA_704X480		= 0x0800,
	DD_VGA_704X576		= 0x1000,
	DD_VGA_960X480		= 0x2000,
	DD_VGA_960X576		= 0x4000,
	DD_VGA_960X1080		= 0x8000,
	DD_VGA_1280X720		= 0x00010000,
	DD_VGA_1600X1200	= 0x00020000,
	DD_VGA_1920X1536	= 0x00040000,
	DD_VGA_2048X1536	= 0x00080000,
	DD_VGA_2304X1296	= 0x00100000,
	DD_VGA_2560X1440	= 0x00200000,
	DD_VGA_2592X1520	= 0x00400000,
	DD_VGA_2592X1944	= 0x00800000,
	DD_VGA_3840X2160	= 0x01000000,
}DD_VGA_RESOLUTION;

//��ʾ�����յ�ģʽ
typedef enum _dd_date_mode_
{
	DD_DATE_MODE_YMD	= 0x01,		//������ģʽ
	DD_DATE_MODE_MDY	= 0x02,		//������ģʽ
	DD_DATE_MODE_DMY	= 0x03		//������ģʽ
}DD_DATE_MODE;

typedef enum _dd_time_zone_name_
{
	DD_TIME_ZONE_GMT_D12	= 0,
	DD_TIME_ZONE_GMT_D11,
	DD_TIME_ZONE_GMT_D10,
	DD_TIME_ZONE_GMT_D9,
	DD_TIME_ZONE_GMT_D8,
	DD_TIME_ZONE_GMT_D7,
	DD_TIME_ZONE_GMT_D6,
	DD_TIME_ZONE_GMT_D5,
	DD_TIME_ZONE_GMT_D4_30,
	DD_TIME_ZONE_GMT_D4,
	DD_TIME_ZONE_GMT_D3_30,
	DD_TIME_ZONE_GMT_D3,
	DD_TIME_ZONE_GMT_D2,
	DD_TIME_ZONE_GMT_D1,
	DD_TIME_ZONE_GMT,
	DD_TIME_ZONE_GMT_A1,
	DD_TIME_ZONE_GMT_A2,
	DD_TIME_ZONE_GMT_A3,
	DD_TIME_ZONE_GMT_A3_30,
	DD_TIME_ZONE_GMT_A4,
	DD_TIME_ZONE_GMT_A4_30,
	DD_TIME_ZONE_GMT_A5,
	DD_TIME_ZONE_GMT_A5_30,
	DD_TIME_ZONE_GMT_A5_45,
	DD_TIME_ZONE_GMT_A6,
	DD_TIME_ZONE_GMT_A6_30,
	DD_TIME_ZONE_GMT_A7,
	DD_TIME_ZONE_GMT_A8,
	DD_TIME_ZONE_GMT_A9,	
	DD_TIME_ZONE_GMT_A9_30,
	DD_TIME_ZONE_GMT_A10,
	DD_TIME_ZONE_GMT_A11,
	DD_TIME_ZONE_GMT_A12,
	DD_TIME_ZONE_GMT_A13,
	DD_TIME_ZONE_NUM,
}DD_TIME_ZOME_NAME;

//�����û�Ȩ�ޣ�ÿ���û�����Ĭ��Ȩ�ޣ����ǿ������µ��ھ���Ȩ�ޣ��������ϵ��ڣ���
typedef enum _dd_user_group_
{
	DD_USER_GROUP_NONE		= 0x00,	//
	DD_USER_GROUP_ADMIN		= 0x01,	//����Ա��ӵ�����е�Ȩ��
	DD_USER_GROUP_ADVANCE	= 0x02,	//�߼��û���Ĭ�Ͼ��У�������¼�����á��طš����ݡ����ݹ������̹�����̨���ƣ�Զ�̵�¼����ȫͨ��Ȩ��
	DD_USER_GROUP_NORMAL	= 0x04	//һ���û���Ĭ�Ͼ��У�������¼�񡢻طš����ݡ���̨���ơ�Զ�̵�¼����ȫͨ��Ȩ��
}DD_USER_GROUP;

typedef enum _dd_record_type_
{
	DD_RECORD_TYPE_NONE		= 0x0000,			//��¼������

	DD_RECORD_TYPE_MANUAL	= 0x0001,			//�ֶ�¼��
	DD_RECORD_TYPE_SCHEDULE	= 0x0002,			//��ʱ¼��
	DD_RECORD_TYPE_MOTION	= 0x0004,			//�ƶ����¼��
	DD_RECORD_TYPE_SENSOR	= 0x0008,			//����������¼��

	DD_RECORD_TYPE_BEHAVIOR = 0x0010,			//��Ϊ��������¼��
    DD_RECORD_TYPE_SHELTER     = 0x20,		//�ڵ�����
    DD_RECORD_TYPE_OVERSPEED   = 0x40,		//����
    DD_RECORD_TYPE_OVERBOUND   = 0x80,		//Խ��
    DD_RECORD_TYPE_OSC         = 0x0100,     //��Ʒ�������¼��
    DD_RECORD_TYPE_AVD         = 0x0200,     //�쳣���
    DD_RECORD_TYPE_TRIPWIRE    = 0x0400,     //Խ�����
    DD_RECORD_TYPE_PERIMETER   = 0x0800,     //�����������
    DD_RECORD_TYPE_VFD         = 0x1000,     //����ʶ��
    DD_RECORD_TYPE_POS         = 0x2000,     //POS
	DD_RECORD_TYPE_PIR         = 0x4000,	 //C12 IPC��pir����¼��
    DD_RECORD_TYPE_INTELLIGENT = DD_RECORD_TYPE_OSC | DD_RECORD_TYPE_AVD | DD_RECORD_TYPE_TRIPWIRE | DD_RECORD_TYPE_PERIMETER | DD_RECORD_TYPE_VFD,
    DD_RECORD_TYPE_ALL         = 0xFFFFFFFF, //���е�¼������
}DD_RECORD_TYPE;
typedef enum _dd_record_status_
{
	DD_RECORD_STATUS_OFF = 0,     //ֹͣ¼��
	DD_RECORD_STATUS_ON,		  //¼����				
	DD_RECORD_STATUS_ABNORMAL 	  //¼���쳣
}DD_RECORD_STATUS;

typedef enum _dd_event_type_
{
	DD_EVENT_TYPE_MOTION    = 0x00000001,		//�ƶ����
	DD_EVENT_TYPE_SENSOR    = 0x00000002,		//����������
	DD_EVENT_TYPE_V_LOSS    = 0x00000004,		//��Ƶ��ʧ
	DD_EVENT_TYPE_V_COVER   = 0x00000008,		//��Ƶ�ڵ�
}DD_EVENT_TYPE;

typedef enum _dd_view_split_mode_
{
	DD_VIEW_SPLIT_1X1	= 0x00010000,	//1X1

	DD_VIEW_SPLIT_2X2	= 0x00020000,	//2X2

	DD_VIEW_SPLIT_1A2	= 0x00040000,	//2X3
	DD_VIEW_SPLIT_2X3,

	DD_VIEW_SPLIT_1A5	= 0x00080000,	//3X3
	DD_VIEW_SPLIT_3X3,

	DD_VIEW_SPLIT_1A7	= 0x00100000,	//4X4
	DD_VIEW_SPLIT_1A12,
	DD_VIEW_SPLIT_4X4,

	DD_VIEW_SPLIT_2A6	= 0x00200000,	//4X6
	DD_VIEW_SPLIT_4X6,

	DD_VIEW_SPLIT_1A9	= 0x00400000,	//5X5
	DD_VIEW_SPLIT_4A9,
	DD_VIEW_SPLIT_1A16,
	DD_VIEW_SPLIT_4A16,
	DD_VIEW_SPLIT_5X5,

	DD_VIEW_SPLIT_1A11	= 0x00800000,	//6X6
	DD_VIEW_SPLIT_1A20,
	DD_VIEW_SPLIT_4A20,
	DD_VIEW_SPLIT_6X6,
}DD_VIEW_SPLIT_MODE;

inline unsigned char DDSplitModeToNum(DD_VIEW_SPLIT_MODE mode)
{
	unsigned char num = 1;
	switch(mode)
	{
	case DD_VIEW_SPLIT_2X2:
		num = 4;
		break;
	case DD_VIEW_SPLIT_2X3:
		num = 6;
		break;
	case DD_VIEW_SPLIT_3X3:
		num = 9;
		break;
	case DD_VIEW_SPLIT_4X4:
		num = 16;
		break;
	case DD_VIEW_SPLIT_5X5:
		num = 25;
		break;
	case DD_VIEW_SPLIT_6X6:
		num = 36;
		break;
	default:
		num = 1;
		break;
	}

	return num;
}

//////////////////////////////////////////////////////////////////////////
//����ΪN9000�������
typedef enum _n9000_log_type
{
	//ȫ������
	//	LOG_ALL,

	//������־
	//	LOG_ALARM_ALL,
	LOG_ALARM_MOTION = 0x100,			//�ƶ���ⱨ��
	LOG_ALARM_SENSOR,					//����������
	LOG_ALARM_ALARMOUTPUT,				//�������	

	//������־
	//	LOG_OPERATE_ALL,
	LOG_OPERATE_RECORD_SPB,				//¼�����/�ط�/����
	LOG_OPERATE_MANUAL_RECORD,			//�ֶ�¼��
	LOG_OPERATE_MANUAL_ALARM,			//�ֶ�����
	LOG_OPERATE_SYSTEM_MAINTENANCE,		//ϵͳά��
	LOG_OPERATE_PTZ_CONTROL,			//��̨����
	LOG_OPERATE_AUDIO_TALK,				//�����Խ�
	LOG_OPERATE_SYSTEM_SCR,				//���ػ�
	LOG_OPERATE_LOGIN_LOGOUT,			//��¼/�ǳ�
	LOG_OPERATE_SNAPSHOT_MSPB,			//ͼƬ
	LOG_OPERATE_FORMAT_HD,				//��ʽ������

	//������־
	//	LOG_CONFIG_ALL,
	LOG_CONFIG_CHANNEL,					//ͨ������
	LOG_CONFIG_RECORD,					//¼�����
	LOG_CONFIG_ALARM,					//��������
	LOG_CONFIG_DISK,					//���̲���
	LOG_CONFIG_NETWORK,					//�������
	LOG_CONFIG_SCHEDULE,				//�ų̲���
	LOG_CONFIG_USER,					//�û�����
	LOG_CONFIG_BASIC,					//��������

	//�쳣��־
	//	LOG_EXCEPTION_ALL,
	LOG_EXCEPTION_UNLAWFUL_ACCESS,		//�Ƿ�����
	LOG_EXCEPTION_DISK_FULL,			//������
	LOG_EXCEPTION_DISK_IO_ERROR,		//���̶�д����
	LOG_EXCEPTION_IP_COLLISION,			//IP��ַ��ͻ
	LOG_EXCEPTION_INTERNET_DISCONNECT,	//����Ͽ�
	LOG_EXCEPTION_IPC_DISCONNECT,		//ǰ�˵���
	LOG_EXCEPTION_ABNORMAL_SHUTDOWN,	//ϵͳ�쳣�ػ�
	LOG_EXCEPTION_NO_DISK,				//�޴���
	LOG_EXCEPTION_VIDEO_LOSS,			//��Ƶ��ʧ
}N9000_LOG_TYPE;

typedef enum _n9000_log_major_type
{
	LOG_ALL		= 0x01,//ȫ������
	LOG_ALARM_ALL,		//������־
	LOG_OPERATE_ALL,	//������־
	LOG_CONFIG_ALL,		//������־
	LOG_EXCEPTION_ALL,	//�쳣��־
	LOG_INFOR_ALL,		//������־
	LOG_MAJOR_TYPE_END,
}N9000_LOG_MAJOR_TYPE;

//��λ���档��಻�ܳ���32��
typedef enum _dd_video_size_n9000_
{
	DD_VIDEO_SIZE_640X480		= 0x0001,
	DD_VIDEO_SIZE_720X480		= 0x0002,
	DD_VIDEO_SIZE_720X576		= 0x0004,
	DD_VIDEO_SIZE_800X600		= 0x0008,
	DD_VIDEO_SIZE_1024X768		= 0x0010,
	DD_VIDEO_SIZE_1280X960		= 0x0020,
	DD_VIDEO_SIZE_1280X1024		= 0x0040,
	DD_VIDEO_SIZE_1920X1080		= 0x0080,
	DD_VIDEO_SIZE_320X240		= 0x0100,
	DD_VIDEO_SIZE_352X240		= 0x0200,
	DD_VIDEO_SIZE_480X240		= 0x0400,
	DD_VIDEO_SIZE_704X480		= 0x0800,
	DD_VIDEO_SIZE_704X576		= 0x1000,
	DD_VIDEO_SIZE_960X480		= 0x2000,
	DD_VIDEO_SIZE_960X576		= 0x4000,
	DD_VIDEO_SIZE_960X1080		= 0x8000,
	DD_VIDEO_SIZE_1280X720		= 0x00010000,
	DD_VIDEO_SIZE_1600X1200		= 0x00020000,
	DD_VIDEO_SIZE_1920X1536		= 0x00040000,
	DD_VIDEO_SIZE_2048X1536		= 0x00080000,
	DD_VIDEO_SIZE_2304X1296		= 0x00100000,
	DD_VIDEO_SIZE_2560X1440		= 0x00200000,
	DD_VIDEO_SIZE_2592X1520		= 0x00400000,
	DD_VIDEO_SIZE_2592X1944		= 0x00800000,
	DD_VIDEO_SIZE_3840X2160		= 0x01000000,
    DD_VIDEO_SIZE_352x288		= 0x02000000,
}DD_VIDEO_SIZE_N9000;

const unsigned int DD_INVALID_CLIENT_ID	= (~0x0);
const unsigned int DD_LOCAL_CLIENT_ID		= 0;
//const unsigned int DD_LOCAL_DEVICE_ID		= 0;


typedef enum _dd_ptz_config_e_
{
    DD_PTZ_CONFIG_PRESET    = 0x1,
    DD_PTZ_CONFIG_CRUISE,
    DD_PTZ_CONFIG_CRUISE_POINT,
}DD_PTZ_CONFIG_E;

#ifdef __CHONGQING_ZHONGRAN__

const unsigned int DD_MAX_CERTIFICATE_NUM = 64;
#else
const unsigned int DD_MAX_CERTIFICATE_NUM = 20;
#endif
#endif //__DVR_DVS_TYPEDEF_H__
//end
