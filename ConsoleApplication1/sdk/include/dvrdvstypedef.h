/***********************************************************************
** Copyright (C) Tongwei Video Technology Co.,Ltd. All rights reserved.
** Author       : YSW
** Date         : 2010-11-19
** Name         : dvrdvstypedef.h
** Version      : 1.0
** Description  :	ÃèÊöDVR/DVSÏà¹ØµÄÒ»Ð©»ù±¾ÌØÐÔ
** Modify Record:
1:´´½¨
***********************************************************************/
#ifndef __DVR_DVS_TYPEDEF_H__
#define __DVR_DVS_TYPEDEF_H__

#ifdef WIN32 ////////////////////Èç¹ûÊÇWindowsÆ½Ì¨
//#include "stdafx.h"  --äôéì ìé ùâéàä
typedef DWORD				THREAD_ID;
typedef long                POINTERHANDLE;

//¶¨ÒåPACKED Ö÷ÒªÓÃÓÚ½â¾öÔÚWindows½â¾ö¶ÔÆæÒ»°ãÊ¹ÓÃ#pragma pack(n)¶øLinuxÏÂÒ»°ãÊ¹ÓÃ__attribute__((packed))
//ÔÚ´Ë½á¹¹ÌåÒªÐ´ÈëÎÄ¼þ»òÕßÔÚ¿çÆ½Ì¨Ö®¼ä·ÃÎÊÊ±²ÅÐèÒªÒÔÏÂ¶¨Òå£¬×¢Òâ__attribute__((packed))Ö»ÓÃÓÚµ¥×Ö½Ú¶ÔÆë
#define PACKED
#else ////////////////////linuxÆ½Ì¨
#include <sys/types.h>
#include <stddef.h>

#define PACKED __attribute__((packed))

typedef pid_t				THREAD_ID;
typedef unsigned int       DWORD, *LPDWORD;
typedef unsigned int       ULONG;
//´ó¸Å¼ì²éÁËÄÚ²¿LONGµÄÊ¹ÓÃ£¬·¢ÏÖºÜ¶àµØ·½½«Ö¸ÕëÖ±½Ó×ª¸øLONG,ÇÒÄ³Ð©µØ·½LONGÖµ¿ÉÄÜÎª¸ºÖµ£¬×îÎÈÍ×µÄ¶¨Òå³Élong long
#if defined (__ENVIRONMENT_LINUX_ANDROID__) || defined (__ENVIRONMENT_IOS__)
    typedef int                LONG;
#else
    #if defined(OS_IS_64BIT)
        typedef long long               LONG;
    #else
        typedef long                LONG;
    #endif
#endif

//ÊÖ»ú¶ËhandleÓÃµÄlong long£¬win£¬linux¶ËÓÃµÄLONG¡£ÏÖÎªÁËÍ³Ò»Ò»Ì×´úÂëÇÒ²»Ó°Ïì¿Í»§£¬¶¨ÒåPOINTERHANDLEÀ´¼æÈÝ
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

//ÊÓÆµÖÆÊ½¶¨Òå
typedef enum _dd_video_format_
{
	DD_VIDEO_FORMAT_NTSC	= 0x01,
	DD_VIDEO_FORMAT_PAL		= 0x02
}DD_VIDEO_FORMAT;

typedef enum _dd_frame_type_
{
	DD_FRAME_TYPE_NONE				= 0x00,//¿ÕÀàÐÍÊý¾ÝÖ¡
	DD_FRAME_TYPE_VIDEO				= 0x01,//ÊÓÆµÊý¾ÝÖ¡
	DD_FRAME_TYPE_AUDIO				= 0x02,//ÒôÆµÊý¾ÝÖ¡
	DD_FRAME_TYPE_TALK_AUDIO		= 0x03,//¶Ô½²ÒôÆµÊý¾ÝÖ¡
	DD_FRAME_TYPE_JPEG				= 0x04,//JPEGÍ¼Æ¬Á÷Êý¾ÝÖ¡

	DD_FRAME_TYPE_VIDEO_FORMAT		= 0x05,//ÊÓÆµ¸ñÊ½Ö¡
	DD_FRAME_TYPE_AUDIO_FORMAT		= 0x06,//ÒôÆµ¸ñÊ½Ö¡
	DD_FRAME_TYPE_TALK_AUDIO_FORMAT	= 0x07,//¶Ô½²ÒôÆµ¸ñÊ½Ö¡

	DD_FRAME_TYPE_RESV1				= 0x08,
	DD_FRAME_TYPE_RESV2				= 0x09,

	DD_FRAME_TYPE_END				= 0x0a,
}DD_FRAME_TYPE;

typedef enum _dd_frame_attrib_
{
	DD_PLAY_FRAME_NO_SHOW			= 0x01,		//´ËÖ¡²»ÏÔÊ¾
	DD_PLAY_FRAME_SHOW				= 0x02,		//´ËÖ¡¿ÉÏÔÊ¾
	DD_PLAY_FRAME_ALL_END			= 0x04,		//Êý¾Ý¶ÁÈ¡½áÊøÁË£¬ºóÃæÔÙÃ»ÓÐÊý¾Ý
	DD_PLAY_FRAME_SEC_END			= 0x08,		//´ËÊÂ¼þ¶Î½áÊøÁË
	DD_PLAY_FRAME_NO_TIME_STAMP		= 0x10,		//´ËÖ¡Êý¾ÝÓÐÊ±¼ä´Á£¬×¥Í¼µÄÊ±ºò×¢ÒâÒªÆÁ±Î´òÊ±¼äµÄ¹¦ÄÜ
	DD_PLAY_FRAME_FF				= 0x20,		//µ±Ç°Ö¡ÓÃÓÚ¿ì½ø

	DD_LIVE_FRAME_FIRST_STREAM		= 0x40,		//´ËÖ¡ÎªÏÖ³¡Ö÷ÂëÁ÷
	DD_LIVE_FRAME_SECOND_STREAM		= 0x80,		//´ËÖ¡ÎªÏÖ³¡×ÓÂëÁ÷
	DD_LIVE_FRAME_JPEG				= 0x100,	//´ËÖ¡ÎªJPEGÍ¼Æ¬
	DD_LIVE_FRAME_TALK				= 0x200,		//´ËÖ¡Îª¶Ô½²ÓïÒôÊý¾Ý
    DD_LIVE_FRAME_THIRD_STREAM		= 0x400,		//´ËÖ¡ÎªÏÖ³¡µÚÈýÂëÁ÷
    DD_LIVE_FRAME_FOURTH_STREAM		= 0x800,		//´ËÖ¡ÎªÏÖ³¡µÚËÄÂëÁ÷
}DD_FRAME_ATTRIB;

//°´Î»±£´æ¡£×î¶à²»ÄÜ³¬¹ý32¸ö
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

//°´Î»±£´æ£¬×î¶àÖ»ÄÜÎª32¸ö¡£
typedef enum _dd_video_encode_mode_
{
	DD_VIDEO_ENCODE_MODE_VBR	=	0x01,	//±äÂëÁ÷
	DD_VIDEO_ENCODE_MODE_CBR	=	0x02	//¹Ì¶¨ÂëÁ÷
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

//VGA·Ö±æÂÊ£¬¼È¿ÉÒÔÓÃÓÚ±£´æÒ²¿ÉÒÔÓÃÓÚÖ§³Ö¹¦ÄÜ²ÎÊý,'
//×¢Òâ£ºÒª°´Î»±íÊ¾
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

//ÏÔÊ¾ÄêÔÂÈÕµÄÄ£Ê½
typedef enum _dd_date_mode_
{
	DD_DATE_MODE_YMD	= 0x01,		//ÄêÔÂÈÕÄ£Ê½
	DD_DATE_MODE_MDY	= 0x02,		//ÔÂÈÕÄêÄ£Ê½
	DD_DATE_MODE_DMY	= 0x03		//ÈÕÔÂÄêÄ£Ê½
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

//Èý¼¶ÓÃ»§È¨ÏÞ£¬Ã¿¼¶ÓÃ»§¾ßÓÐÄ¬ÈÏÈ¨ÏÞ£¬µ«ÊÇ¿ÉÒÔÏòÏÂµ÷½Ú¾ßÌåÈ¨ÏÞ£¨²»ÄÜÏòÉÏµ÷½Ú£©¡£
typedef enum _dd_user_group_
{
	DD_USER_GROUP_NONE		= 0x00,	//
	DD_USER_GROUP_ADMIN		= 0x01,	//¹ÜÀíÔ±£¬ÓµÓÐËùÓÐµÄÈ¨ÏÞ
	DD_USER_GROUP_ADVANCE	= 0x02,	//¸ß¼¶ÓÃ»§£¬Ä¬ÈÏ¾ßÓÐ£º»ù±¾¡¢Â¼Ïñ¡¢ÅäÖÃ¡¢»Ø·Å¡¢±¸·Ý¡¢Êý¾Ý¹ÜÀí¡¢´ÅÅÌ¹ÜÀí£¬ÔÆÌ¨¿ØÖÆ£¬Ô¶³ÌµÇÂ¼£¬¼°È«Í¨µÀÈ¨ÏÞ
	DD_USER_GROUP_NORMAL	= 0x04	//Ò»°ãÓÃ»§£¬Ä¬ÈÏ¾ßÓÐ£º»ù±¾¡¢Â¼Ïñ¡¢»Ø·Å¡¢±¸·Ý¡¢ÔÆÌ¨¿ØÖÆ¡¢Ô¶³ÌµÇÂ¼£¬¼°È«Í¨µÀÈ¨ÏÞ
}DD_USER_GROUP;

typedef enum _dd_record_type_
{
	DD_RECORD_TYPE_NONE		= 0x0000,			//ÎÞÂ¼ÏñÀàÐÍ

	DD_RECORD_TYPE_MANUAL	= 0x0001,			//ÊÖ¶¯Â¼Ïñ
	DD_RECORD_TYPE_SCHEDULE	= 0x0002,			//¶¨Ê±Â¼Ïñ
	DD_RECORD_TYPE_MOTION	= 0x0004,			//ÒÆ¶¯Õì²âÂ¼Ïñ
	DD_RECORD_TYPE_SENSOR	= 0x0008,			//´«¸ÐÆ÷±¨¾¯Â¼Ïñ

	DD_RECORD_TYPE_BEHAVIOR = 0x0010,			//ÐÐÎª·ÖÎö±¨¾¯Â¼Ïñ
    DD_RECORD_TYPE_SHELTER     = 0x20,		//ÕÚµ²±¨¾¯
    DD_RECORD_TYPE_OVERSPEED   = 0x40,		//³¬ËÙ
    DD_RECORD_TYPE_OVERBOUND   = 0x80,		//Ô½½ç
    DD_RECORD_TYPE_OSC         = 0x0100,     //ÎïÆ·¿´»¤Õì²âÂ¼Ïñ
    DD_RECORD_TYPE_AVD         = 0x0200,     //Òì³£Õì²â
    DD_RECORD_TYPE_TRIPWIRE    = 0x0400,     //Ô½½çÕì²â
    DD_RECORD_TYPE_PERIMETER   = 0x0800,     //ÇøÓòÈëÇÖÕì²â
    DD_RECORD_TYPE_VFD         = 0x1000,     //ÈËÁ³Ê¶±ð
    DD_RECORD_TYPE_POS         = 0x2000,     //POS
	DD_RECORD_TYPE_PIR         = 0x4000,	 //C12 IPCµÄpir±¨¾¯Â¼Ïñ
    DD_RECORD_TYPE_INTELLIGENT = DD_RECORD_TYPE_OSC | DD_RECORD_TYPE_AVD | DD_RECORD_TYPE_TRIPWIRE | DD_RECORD_TYPE_PERIMETER | DD_RECORD_TYPE_VFD,
    DD_RECORD_TYPE_ALL         = 0xFFFFFFFF, //ËùÓÐµÄÂ¼ÏñÀàÐÍ
}DD_RECORD_TYPE;
typedef enum _dd_record_status_
{
	DD_RECORD_STATUS_OFF = 0,     //Í£Ö¹Â¼Ïñ
	DD_RECORD_STATUS_ON,		  //Â¼ÏñÖÐ				
	DD_RECORD_STATUS_ABNORMAL 	  //Â¼ÏñÒì³£
}DD_RECORD_STATUS;

typedef enum _dd_event_type_
{
	DD_EVENT_TYPE_MOTION    = 0x00000001,		//ÒÆ¶¯Õì²â
	DD_EVENT_TYPE_SENSOR    = 0x00000002,		//´«¸ÐÆ÷±¨¾¯
	DD_EVENT_TYPE_V_LOSS    = 0x00000004,		//ÊÓÆµ¶ªÊ§
	DD_EVENT_TYPE_V_COVER   = 0x00000008,		//ÊÓÆµÕÚµ²
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
//ÒÔÏÂÎªN9000Ïà¹ØÀàÐÍ
typedef enum _n9000_log_type
{
	//È«²¿ÀàÐÍ
	//	LOG_ALL,

	//±¨¾¯ÈÕÖ¾
	//	LOG_ALARM_ALL,
	LOG_ALARM_MOTION = 0x100,			//ÒÆ¶¯Õì²â±¨¾¯
	LOG_ALARM_SENSOR,					//´«¸ÐÆ÷±¨¾¯
	LOG_ALARM_ALARMOUTPUT,				//±¨¾¯Êä³ö	

	//²Ù×÷ÈÕÖ¾
	//	LOG_OPERATE_ALL,
	LOG_OPERATE_RECORD_SPB,				//Â¼Ïñ¼ìË÷/»Ø·Å/±¸·Ý
	LOG_OPERATE_MANUAL_RECORD,			//ÊÖ¶¯Â¼Ïñ
	LOG_OPERATE_MANUAL_ALARM,			//ÊÖ¶¯±¨¾¯
	LOG_OPERATE_SYSTEM_MAINTENANCE,		//ÏµÍ³Î¬»¤
	LOG_OPERATE_PTZ_CONTROL,			//ÔÆÌ¨¿ØÖÆ
	LOG_OPERATE_AUDIO_TALK,				//ÓïÒô¶Ô½²
	LOG_OPERATE_SYSTEM_SCR,				//¿ª¹Ø»ú
	LOG_OPERATE_LOGIN_LOGOUT,			//µÇÂ¼/µÇ³ö
	LOG_OPERATE_SNAPSHOT_MSPB,			//Í¼Æ¬
	LOG_OPERATE_FORMAT_HD,				//¸ñÊ½»¯´ÅÅÌ

	//ÉèÖÃÈÕÖ¾
	//	LOG_CONFIG_ALL,
	LOG_CONFIG_CHANNEL,					//Í¨µÀ²ÎÊý
	LOG_CONFIG_RECORD,					//Â¼Ïñ²ÎÊý
	LOG_CONFIG_ALARM,					//±¨¾¯²ÎÊý
	LOG_CONFIG_DISK,					//´ÅÅÌ²ÎÊý
	LOG_CONFIG_NETWORK,					//ÍøÂç²ÎÊý
	LOG_CONFIG_SCHEDULE,				//ÅÅ³Ì²ÎÊý
	LOG_CONFIG_USER,					//ÓÃ»§²ÎÊý
	LOG_CONFIG_BASIC,					//»ù±¾ÅäÖÃ

	//Òì³£ÈÕÖ¾
	//	LOG_EXCEPTION_ALL,
	LOG_EXCEPTION_UNLAWFUL_ACCESS,		//·Ç·¨·ÃÎÊ
	LOG_EXCEPTION_DISK_FULL,			//´ÅÅÌÂú
	LOG_EXCEPTION_DISK_IO_ERROR,		//´ÅÅÌ¶ÁÐ´³ö´í
	LOG_EXCEPTION_IP_COLLISION,			//IPµØÖ·³åÍ»
	LOG_EXCEPTION_INTERNET_DISCONNECT,	//ÍøÂç¶Ï¿ª
	LOG_EXCEPTION_IPC_DISCONNECT,		//Ç°¶ËµôÏß
	LOG_EXCEPTION_ABNORMAL_SHUTDOWN,	//ÏµÍ³Òì³£¹Ø»ú
	LOG_EXCEPTION_NO_DISK,				//ÎÞ´ÅÅÌ
	LOG_EXCEPTION_VIDEO_LOSS,			//ÊÓÆµ¶ªÊ§
}N9000_LOG_TYPE;

typedef enum _n9000_log_major_type
{
	LOG_ALL		= 0x01,//È«²¿ÀàÐÍ
	LOG_ALARM_ALL,		//±¨¾¯ÈÕÖ¾
	LOG_OPERATE_ALL,	//²Ù×÷ÈÕÖ¾
	LOG_CONFIG_ALL,		//ÉèÖÃÈÕÖ¾
	LOG_EXCEPTION_ALL,	//Òì³£ÈÕÖ¾
	LOG_INFOR_ALL,		//ÆäËüÈÕÖ¾
	LOG_MAJOR_TYPE_END,
}N9000_LOG_MAJOR_TYPE;

//°´Î»±£´æ¡£×î¶à²»ÄÜ³¬¹ý32¸ö
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
