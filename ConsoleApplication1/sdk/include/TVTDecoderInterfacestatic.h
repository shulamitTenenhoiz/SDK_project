/*********************************************************************
* 版权所有 (C)2017, 深圳市同为视频技术有限公司。
* 
* 文件名称： // TVTDecoderInterface.h
* 内容摘要： // Defines the exported functions for the DLL application.
* 当前版本： // 1.0.0.1
* 完成日期： // 2017年6月13日
* 与对应lib使用
**********************************************************************/
#ifndef _TVTDECODER_INTERFACE_H_
#define _TVTDECODER_INTERFACE_H_

#include "TVTDecoderHeader.h"

TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_Init();
TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_Cleanup();

TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_CreateDecoder(tint32 &iHandle, tint32 iCodec);
TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_DestroyDecoder(tint32 iHandle);

// TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_SetHWMode(HARDWARE_ACCEL_ENUM enumHWAccel);
TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_DecodeVideo(tint32 iHandle, BYTE *pInData, tint32 iInLen, BYTE *pOutData, tint32 &iOutLen);
TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_GetVideoFormat(tint32 iHandle, VIDEOFORMAT &stSrcVFmt, VIDEOFORMAT &stDstVFmt);
TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_SetVideoFormat(tint32 iHandle, VIDEOFORMAT &stSrcVFmt, VIDEOFORMAT &stDstVFmt);

TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_Capture(tint32 iHandle, const char *sFileName);

//输出的图片为RGB格式，iOutLen = width*height*3
TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_DecodeVideoToImage(tint32 iHandle, BYTE *pInData, tint32 iInLen, BYTE *pOutData, tint32 &iOutLen, tint32 &width, tint32 &height); 

TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_SetRenderInfo(tint32 iHandle, RENDERINFO &stRenderInfo);
TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_RenderFrame(tint32 iHandle, tint8 *pFrameBuf, tuint32 uFrameLen, tuint64 ullTimeStamp = 0);


TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_SetSDLReander(tint32 iHandle);

// TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_SetTexture(tint32 iHandle,TextureType type, void* param);

TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_Resize(tint32 iHandle,int h,int w);
#endif  // _TVTDECODER_INTERFACE_H_
