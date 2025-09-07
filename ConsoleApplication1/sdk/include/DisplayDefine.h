#ifndef _DISPLAY_DEFINE_H_
#define _DISPLAY_DEFINE_H_
//#include "dvrdvstypedef.h"

//��ƹ̶���������׼�ָ�㡢���л���
enum LAYOUT_LAYER
{
	LAYOUT_LAYER_0,
	LAYOUT_LAYER_1,
};

enum STREAM_TYPE
{
	STREAM_TYPE_NONE,
	STREAM_TYPE_LIVE,
	STREAM_TYPE_PLAYBACK = 100,
};

enum LAYOUT_PIP_POSITION
{
	LAYOUT_PIP_LEFT_TOP,
	LAYOUT_PIP_RIGHT_TOP,
	LAYOUT_PIP_LEFT_BOTTOM,
	LAYOUT_PIP_RIGHT_BOTTOM,
	LAYOUT_PIP_NUM,
};

enum CH_STATUS
{
	CH_STATUS_FREE		= 0,
	CH_STATUS_VLOSS		= 1,
	CH_STATUS_DISCONNECT= 2, 
	CH_STATUS_NO_AUTH	= 3,
	CH_STATUS_RECORD	= 4
};

const unsigned int MAX_NORMAL_PORT_NUM = 128;
const unsigned int	MAX_DISPLAY_PORT_NUM = MAX_NORMAL_PORT_NUM + LAYOUT_PIP_NUM;
const unsigned int PIP_SIZE_PERCENT = 20;

const unsigned int PORT_STATUS_BAR_HEIGHT = 16;

#ifdef _WINDOWS_
typedef long                POINTERHANDLE;
#endif

typedef void (CALLBACK *DRAW_FUN_CALLBACK)(POINTERHANDLE lLiveHandle, HDC hDC, void *pUser);

typedef struct _display_port
{
	unsigned short index;	//������
	unsigned short zOrder;	//Z����ʾ˳��LAYOUT_LAYER

	unsigned short xPos;	//���ϽǺ�����
	unsigned short yPos;	//���Ͻ�������
	unsigned short cx;		//��ʾ�����ȣ����أ�
	unsigned short cy;		//��ʾ����߶ȣ����أ�

	unsigned short channel;
	unsigned short streamType;//STREAM_TYPE
	unsigned int deviceID;
	unsigned int liveHandle;
	DRAW_FUN_CALLBACK	drawCallBackFunc;
	void *				cbParam;
}DISPLAY_PORT;

typedef enum
{
    FISHEYE_ORIGNAL = 0,		//ԭʼģʽ,����/��/��װģʽ�µ�����ͼ,�൱���˳�����У��ģʽ

    FISHEYE_ROOF = 0x0100,		//��װ(����)
    FISHEYE_ROOF_360,			//��װ֮360�����չ��ȫ�� + �����ӻ���;�ӻ���;���չ��ȫ���е��ӿ��֧�ֱ䱶���ƶ�����������չ��ȫ����֧��������ʼ���ƶ�����
    FISHEYE_ROOF_2x180,			//��װ֮2��������180�����չ�����棬�κ�ʱ�����Ӵ��ھ����360��ȫ�����ֽС�˫ȫ��������������չ�������֧�������ƶ���ʼ����������໥����;
    FISHEYE_ROOF_FISH_3PTZ,		//��װ֮ԭʼͼ�� + 3�������ӻ��棬�ӻ����ԭʼͼ���е��ӿ��֧�ֱ䱶���ƶ�������ԭʼͼ��֧����ת�ı���ʼ�����;
    FISHEYE_ROOF_FISH_4PTZ,		//��װ֮ԭʼͼ�� + 4�������ӻ��棬�ӻ����ԭʼͼ���е��ӿ��֧�ֱ䱶���ƶ�������ԭʼͼ��֧����ת�ı���ʼ�����
    FISHEYE_ROOF_360_6PTZ,		//��װ֮360�����չ��ȫ�� + 6�������ӻ��棬�ӻ���;���չ��ȫ���е��ӿ��֧�ֱ䱶���ƶ�����������չ��ȫ����֧��������ʼ���ƶ�����;				
    FISHEYE_ROOF_FISH_8PTZ,		//��װ֮ԭʼͼ�� + 8�������ӻ��棬�ӻ����ԭʼͼ���е��ӿ��֧�ֱ䱶���ƶ�������ԭʼͼ��֧����ת�ı���ʼ�����;

    FISHEYE_WALL = 0x0200,		//��װ
    FISHEYE_WALL_180,			//��װ֮180ȫ��ͼ��������180�����չ��ȫ����180�����չ��ȫ��֧�������ƶ��������ı䴹ֱ�ӽ�;
    FISHEYE_WALL_180_3PTZ,		//��װ֮180�����չ��ȫ�� + 3�������ӻ��棬�ӻ���;���չ��ȫ���е��ӿ��֧�ֱ䱶���ƶ�����������չ��ȫ��֧�������ƶ��������ı䴹ֱ�ӽ� 
    FISHEYE_WALL_180_4PTZ,		//��װ֮180�����չ��ȫ�� + 4�������ӻ��棬�ӻ���;���չ��ȫ���е��ӿ��֧�ֱ䱶���ƶ�����������չ��ȫ��֧�������ƶ��������ı䴹ֱ�ӽ� 
    FISHEYE_WALL_180_8PTZ,		//��װ֮180�����չ��ȫ�� + 8�������ӻ��棬�ӻ���;���չ��ȫ���е��ӿ��֧�ֱ䱶���ƶ�����������չ��ȫ��֧�������ƶ��������ı䴹ֱ�ӽ� 

    FISHEYE_DESKTOP = 0x0300,	//��װ(����)
    FISHEYE_DESKTOP_360,		//��װ֮360�����չ��ȫ�� + �����ӻ���;�ӻ���;���չ��ȫ���е��ӿ��֧�ֱ䱶���ƶ�����������չ��ȫ����֧��������ʼ���ƶ�����
    FISHEYE_DESKTOP_2x180,		//��װ֮2��������180�����չ�����棬�κ�ʱ�����Ӵ��ھ����360��ȫ�����ֽС�˫ȫ��������������չ�������֧�������ƶ���ʼ����������໥����;
    FISHEYE_DESKTOP_FISH_3PTZ,	//��װ֮ԭʼͼ�� + 3�������ӻ��棬�ӻ����ԭʼͼ���е��ӿ��֧�ֱ䱶���ƶ�������ԭʼͼ��֧����ת�ı���ʼ�����;
    FISHEYE_DESKTOP_FISH_4PTZ,	//��װ֮ԭʼͼ�� + 4�������ӻ��棬�ӻ����ԭʼͼ���е��ӿ��֧�ֱ䱶���ƶ�������ԭʼͼ��֧����ת�ı���ʼ�����
    FISHEYE_DESKTOP_360_6PTZ,	//��װ֮360�����չ��ȫ�� + 6�������ӻ��棬�ӻ���;���չ��ȫ���е��ӿ��֧�ֱ䱶���ƶ�����������չ��ȫ����֧��������ʼ���ƶ�����;				
    FISHEYE_DESKTOP_FISH_8PTZ,	//��װ֮ԭʼͼ�� + 8�������ӻ��棬�ӻ����ԭʼͼ���е��ӿ��֧�ֱ䱶���ƶ�������ԭʼͼ��֧����ת�ı���ʼ�����;

}FISHEYE_MODE;

//��Ⱦ����
typedef enum tagRENDER_TYPE
{
    MP_RENDER_NOTSET = 0,				// δ����
    MP_RENDER_DDRAW,					// ddraw��Ⱦ
    MP_RENDER_D3D,						// d3d��Ⱦ
    MP_RENDER_OPENGL,		            // ��windowsƽ̨opengl��Ⱦ
    MP_RENDER_SDL2,                    // SDL_AUTO
    MP_RENDER_SDL2_SOFTWARE,           // SDL_RENDERER_SOFTWARE
    MP_RENDER_SDL2_OCX = MP_RENDER_SDL2_SOFTWARE,                    // OCX use
    MP_RENDER_SDL2_FORLIBVA,
    MP_RENDER_CALLER                   //���ſ�ֻ���룬�ص�YUV���ݸ�caller�Լ���Ⱦ
}RENDER_TYPE;

#endif
