#pragma once

#include "animation.h"

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//���ҽ��κ��� ����
		LOAD_FILE,			//���Ϸκ��� ����
		LOAD_EMPTY,			//�� ����
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;
		HDC		hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float	x;
		float	y;
		int		width;
		int		height;

		int currentFrameX;	//���� ������ X
		int currentFrameY;	//���� ������ Y
		int maxFrameX;		//�ִ� ������ X
		int maxFrameY;		//�ִ� ������ Y
		int frameWidth;		//�����Ӵ� ���� ������
		int frameHeight;	//�����Ӵ� ���� ������
		
		BYTE	loadType;
		RECT boundingBox;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
			boundingBox = {0, 0, 0, 0};
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	//������ ���ÿ� ����̴ϼ� ������� �ʱ�ȭ ���ִ� ������
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	CHAR*			_fileName;		//�̹��� �̸� ���

	BOOL			_trans;			//�������� ������ �ֳ�?
	COLORREF		_transColor;	//�����÷�Ű

	BLENDFUNCTION	_blendFunc;		//���� �����带 ���� ����
	LPIMAGE_INFO	_blendImage;	//���� �����带 ����ϱ� ���� �̹���

public:
	image();
	~image();

	//�� ��Ʈ�� �̹��� �����
	HRESULT init( int width, int height );

	//���ҽ��κ��� �о�´�
	HRESULT init( const DWORD resID, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE );

	//�̹��� ���� (���Ϸ� �о��)
	HRESULT init( const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE );

	HRESULT init( const char* fileName, float x, float y, int width, int height,
		BOOL trans, COLORREF transColor );

	//���Ϸ� �о���µ� ������ �̹���
	HRESULT init( const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor );

	HRESULT init( const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans, COLORREF transColor );

	void alphaInit();

	//����
	void release();

	//���� Ű��(RGB��) ���� == Ư�� ������ �׸��� �ʴ´�
	void setTransColor( BOOL trans, COLORREF transColor );

	//����
	void render( HDC hdc);
	void render( HDC hdc, int destX, int destY );
	void render( HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight );
	void render( HDC hdc, int destX, int destY, int sourX, int sourY, int orgWidth, int orgHeight, int sourWidth, int sourHeight );

	//������ ����
	void frameRender( HDC hdc, int destX, int destY );
	void frameRender( HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY );

	//���� ����
	void alphaRender( HDC hdc, int destX, int destY, BYTE alpha );
	void alphaRender( HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha );

	//�ִ� ����
	void aniRender( HDC hdc, int destX, int destY, animation* ani );

	//���� ����
	void loopRender( HDC hdc, const LPRECT drawArea, int offsetX, int offsetY );

	//DC ������
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//��ǥ X
	inline void setX( float x ) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	//��ǥ Y
	inline void setY( float y ) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	//��ǥ ����
	inline void setCenter( float x, float y )
	{
		_imageInfo->x = x - ( _imageInfo->width / 2 );
		_imageInfo->y = y - ( _imageInfo->height / 2 );
	}

	//���� X
	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + ( _imageInfo->width / 2 ) :
			_imageInfo->x + ( _imageInfo->frameWidth / 2 );
	}

	//���� Y
	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + ( _imageInfo->height / 2 ) :
			_imageInfo->y + ( _imageInfo->frameHeight / 2 );
	}

	//���� �ػ�
	inline int getWidth() { return _imageInfo->width; }

	//���� �ػ�
	inline int getHeight() { return _imageInfo->height; }

	//�ٿ�� �ڽ�
	inline RECT boundingBox()
	{
		RECT rc = {int(_imageInfo->x),
		int(_imageInfo->y),
		int(_imageInfo->x + _imageInfo->frameWidth),
		int(_imageInfo->y + _imageInfo->frameHeight)};

		return rc;
	}

	//������
	inline void setFrameX( int frameX )
	{
		_imageInfo->currentFrameX = frameX;
		if ( frameX > _imageInfo->maxFrameX ) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void setFrameY( unsigned int frameY )
	{
		_imageInfo->currentFrameY = frameY;
		if ( frameY > _imageInfo->maxFrameY ) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }
};
