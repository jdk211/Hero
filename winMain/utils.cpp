#include "stdafx.h"
#include "utils.h"

namespace MY_UTIL
{
	//     int nHeight,             // 높이
	//     int nWidth,              // 폭. 0을 넣어주면 높이에 비례함
	//     int nEscapement,         // 글자 전체 기울기
	//     int nOrientation,        // 기준선이 정해져 있고 기우는 기울기
	//     int fnWeight,            // 폰트의 두께 0~1000
	//     DWORD fdwItalic,         // 이탤릭
	//     DWORD fdwUnderline,      // 밑줄
	//     DWORD fdwStrikeOut,      // 취소선
	//     DWORD fdwCharSet,        // 캐릭터 셋
	//     DWORD fdwOutputPrecision,  // 정밀도
	//     DWORD fdwClipPrecision,  // 정밀도
	//     DWORD fdwQuality,        // 정밀도
	//     DWORD fdwPitchAndFamily,  // 정밀도
	//     LPCTSTR lpszFace         // 글꼴이름

	void TextOutPlus(HDC hdc, int x, int y, LPCSTR lpString, int size, COLORREF color, int weight, LPCSTR ttf)
	{
		HFONT myFont = CreateFont(size, 0, 0, 0, weight, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, ttf);
		HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
		//글자 색상
		SetTextColor(hdc, color);
		TextOut(hdc, x, y, lpString, strlen(lpString));
		SelectObject(hdc, oldFont);
		DeleteObject(myFont);
	}

	void DrawTextPlus(HDC hdc, int x, int y, int width, int height, LPCSTR lpString, int size, COLORREF color, int weight, LPCSTR ttf, bool bg, UINT format)
	{
		RECT rc = RectMake(x, y, width, height);
		HFONT myFont = CreateFont(size, 0, 0, 0, weight, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, ttf);
		HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
		if (bg)
		{
			HBRUSH my, old;
			my = CreateSolidBrush(0x000000);
			old	= (HBRUSH)SelectObject(hdc, my);
			Rectangle(hdc, rc.left, rc.top - 10, rc.right, rc.bottom);
			DeleteObject(old);
		}
		//글자 색상
		SetTextColor(hdc, color);
		DrawText(hdc, lpString, strlen(lpString), &rc, format);
		SelectObject(hdc, oldFont);
		DeleteObject(myFont);
	}

	void TestText(HDC hdc, int x, int y, int value)
	{
		//테스트 확인용
		char str2[32];
		sprintf_s(str2, "%d", value);
		TextOut(hdc, x, y, str2, strlen(str2));
	}

	bool inScreen(float x, float y)
	{
		if ((CAMERA->getUnitViewX(x) > 0 && CAMERA->getUnitViewX(x) < WINSIZEX)
			&& (CAMERA->getUnitViewY(y) > 0 && CAMERA->getUnitViewY(y) < WINSIZEY))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	float getDistance( float startX, float startY, float endX, float endY )
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf( x*x + y*y );
	}

	float getAngle( float startX, float startY, float endX, float endY )
	{
		float x = endX - startX;
		float y = endY - startY;

		float dist = sqrtf( x*x + y*y );
		float angle = acosf( x / dist );

		if ( y > 0 ) angle = PI2 - angle;

		return angle;
	}

	bool checkPointInRect( const RECT & rc, const POINT & pt )
	{
		if ( (rc.left <= pt.x && pt.x <= rc.right) && (rc.top <= pt.y && pt.y <= rc.bottom) ) return true;
		else return false;
	}
	
	bool checkPointInRect( const RECT & rc, int x, int y )
	{
		if ( ( rc.left <= x && x <= rc.right ) && ( rc.top <= y && y <= rc.bottom ) ) return true;
		else return false;
	}
	
	bool checkPointInRect( const MYRECT & rc, float x, float y )
	{
		if ( ( rc.left <= x && x <= rc.right ) && ( rc.top <= y && y <= rc.bottom ) ) return true;
		else return false;
	}
	
	bool checkPointInRect( const MYRECT & rc, const MYPOINT & pt )
	{
		if ( ( rc.left <= pt.x && pt.x <= rc.right ) && ( rc.top <= pt.y && pt.y <= rc.bottom ) ) return true;
		else return false;
	}
	
	bool checkPointInCircle( float cX, float cY, float cR, const MYPOINT & pt )
	{
		//x, y 거리
		float deltaX = pt.x - cX;
		float deltaY = pt.y - cY;

		//거리 제곱
		float distSquare = deltaX * deltaX + deltaY * deltaY;

		//반지름 제곱
		float radiusSquare = cR * cR;

		if ( radiusSquare < distSquare ) return false;

		return true;
	}
	
	bool checkPointInCircle( float cX, float cY, float cR, float x, float y )
	{
		//x, y 거리
		float deltaX = x - cX;
		float deltaY = y - cY;

		//거리 제곱
		float distSquare = deltaX * deltaX + deltaY * deltaY;

		//반지름 제곱
		float radiusSquare = cR * cR;

		if ( radiusSquare < distSquare ) return false;

		return true;
	}
	
	bool checkPointInCircle( const MYCIRCLE & rc, float x, float y )
	{
		//x, y 거리
		float deltaX = x - rc.x;
		float deltaY = y - rc.y;

		//거리 제곱
		float distSquare = deltaX * deltaX + deltaY * deltaY;

		//반지름 제곱
		float radiusSquare = rc.r * rc.r;

		if ( radiusSquare < distSquare ) return false;

		return true;
	}
	
	bool checkPointInCircle( const MYCIRCLE & rc, const MYPOINT & pt )
	{
		//x, y 거리
		float deltaX = pt.x - rc.x;
		float deltaY = pt.y - rc.y;

		//거리 제곱
		float distSquare = deltaX * deltaX + deltaY * deltaY;

		//반지름 제곱
		float radiusSquare = rc.r * rc.r;

		if ( radiusSquare < distSquare ) return false;

		return true;
	}
	
	bool isCollision( const MYRECT & rc1, const MYRECT & rc2 )
	{
		if ( ( rc1.left <= rc2.right && rc1.right >= rc2.left ) &&
			( rc1.top <= rc2.bottom && rc1.bottom >= rc2.top ) ) return true;
		return false;
	}
	
	bool isCollision( const RECT & rc1, const RECT & rc2 )
	{
		if ( ( rc1.left <= rc2.right && rc1.right >= rc2.left ) &&
			( rc1.top <= rc2.bottom && rc1.bottom >= rc2.top ) ) return true;
		return false;
	}
	
	bool isCollision( const MYCIRCLE & cir1, const MYCIRCLE & cir2 )
	{
		float deltaX = cir2.x - cir1.x;
		float deltaY = cir2.y - cir1.y;

		float distSquare = deltaX * deltaX + deltaY * deltaY;

		float radius = cir1.r + cir2.r;
		float radiusSquare = radius * radius;

		if ( distSquare > radiusSquare )
		{
			return false;
		}

		return true;
	}
	
	//원 사각형 충돌
	bool isCollision( const MYCIRCLE & cir, const RECT & rc )
	{
		int centerX = FLOAT_TO_INT( cir.x );
		int centerY = FLOAT_TO_INT( cir.y );
		int radius = FLOAT_TO_INT( cir.r );

		if ( ( rc.left <= centerX && centerX <= rc.right ) ||
			( rc.top <= centerY && centerY <= rc.bottom ) )
		{
			RECT exRect;
			exRect.left = rc.left - radius;
			exRect.right = rc.right + radius;
			exRect.top = rc.top - radius;
			exRect.bottom = rc.bottom + radius;

			if ( ( exRect.left <= centerX && centerX <= exRect.right ) &&
				( exRect.top <= centerY && centerY <= exRect.bottom ) )
			{
				return true;
			}
		}
		else
		{
			//좌상단
			if ( checkPointInCircle( cir, (float) rc.left, (float) rc.top ) ) return true;
			
			//우상단
			if ( checkPointInCircle( cir, (float) rc.right, (float) rc.top ) ) return true;

			//좌하단
			if ( checkPointInCircle( cir, (float) rc.left, (float) rc.bottom ) ) return true;

			//우하단
			if ( checkPointInCircle( cir, (float) rc.right, (float) rc.bottom ) ) return true;
		}
	}
	
	bool isCollision( const MYCIRCLE & cir, const MYRECT & rc )
	{
		if ( ( rc.left <= cir.x && cir.x <= rc.right ) ||
			( rc.top <= cir.y && cir.y <= rc.bottom ) )
		{
			RECT exRect;
			exRect.left = rc.left - cir.r;
			exRect.right = rc.right + cir.r;
			exRect.top = rc.top - cir.r;
			exRect.bottom = rc.bottom + cir.r;

			if ( ( exRect.left <= cir.x && cir.x <= exRect.right ) &&
				( exRect.top <= cir.y && cir.y <= exRect.bottom ) )
			{
				return true;
			}
		}
		else
		{
			//좌상단
			if ( checkPointInCircle( cir, (float) rc.left, (float) rc.top ) ) return true;

			//우상단
			if ( checkPointInCircle( cir, (float) rc.right, (float) rc.top ) ) return true;

			//좌하단
			if ( checkPointInCircle( cir, (float) rc.left, (float) rc.bottom ) ) return true;

			//우하단
			if ( checkPointInCircle( cir, (float) rc.right, (float) rc.bottom ) ) return true;
		}
	}
	
	bool isCollisionReaction( const RECT & rcHold, RECT & rcMove )
	{
		RECT rcInter;

		if ( !IntersectRect( &rcInter, &rcHold, &rcMove ) ) return false;

		//여기 내려왔다는 것은 충돌했다는 거
		int interW = rcInter.right - rcInter.left;
		int interH = rcInter.bottom - rcInter.top;

		//수직충돌
		if ( interH < interW )
		{
			//위
			if ( rcHold.top == rcInter.top )
			{
				OffsetRect( &rcMove, 0, -interH );
			}
			//아래
			else if ( rcHold.bottom == rcInter.bottom )
			{
				OffsetRect( &rcMove, 0, interH );
			}
		}
		else
		{
			//좌
			if ( rcHold.left == rcInter.left )
			{
				OffsetRect( &rcMove, -interW, 0 );
			}
			//우
			if ( rcHold.right == rcInter.right )
			{
				OffsetRect( &rcMove, interW, 0 );
			}
		}

		return true;
	}
	
	bool isCollisionReaction( const MYRECT & mrcHold, MYRECT & mrcMove )
	{
		RECT rcHold;
		rcHold.left = FLOAT_TO_INT( mrcHold.left );
		rcHold.top = FLOAT_TO_INT( mrcHold.top );
		rcHold.right = FLOAT_TO_INT( mrcHold.right );
		rcHold.bottom = FLOAT_TO_INT( mrcHold.bottom );

		RECT rcMove;
		rcMove.left = FLOAT_TO_INT( mrcMove.left );
		rcMove.top = FLOAT_TO_INT( mrcMove.top );
		rcMove.right = FLOAT_TO_INT( mrcMove.right );
		rcMove.bottom = FLOAT_TO_INT( mrcMove.bottom );

		RECT rcInter;
		if ( !IntersectRect( &rcInter, &rcHold, &rcMove ) ) return false;

		//여기 내려왔다는 것은 충돌했다는 거
		int interW = rcInter.right - rcInter.left;
		int interH = rcInter.bottom - rcInter.top;

		//수직충돌
		if ( interH < interW )
		{
			//위
			if ( rcHold.top == rcInter.top )
			{
				OffsetRect( &rcMove, 0, -interH );
			}
			//아래
			else if ( rcHold.bottom == rcInter.bottom )
			{
				OffsetRect( &rcMove, 0, interH );
			}
		}
		else
		{
			//좌
			if ( rcHold.left == rcInter.left )
			{
				OffsetRect( &rcMove, -interW, 0 );
			}
			//우
			if ( rcHold.right == rcInter.right )
			{
				OffsetRect( &rcMove, interW, 0 );
			}
		}

		mrcMove.left = static_cast<float>(rcMove.left);
		mrcMove.top = static_cast<float>(rcMove.top);
		mrcMove.right = static_cast<float>(rcMove.right);
		mrcMove.bottom = static_cast<float>(rcMove.bottom);

		return true;
	}
	
	bool isCollisionReaction( const MYCIRCLE & cirHold, MYCIRCLE & cirMove )
	{
		float deltaX = cirMove.x - cirHold.x;
		float deltaY = cirMove.y - cirHold.y;

		float distance = sqrtf( deltaX * deltaX + deltaY * deltaY );

		float radius = cirHold.r + cirMove.r;

		if ( distance < radius )
		{
			float angle = getAngle( cirHold.x, cirHold.y, cirMove.x, cirMove.y );

			float moveDelta = radius - distance;

			float moveX = cosf( angle ) * moveDelta;
			float moveY = -sinf( angle ) * moveDelta;

			cirMove.move( moveX, moveY );

			return true;
		}

		return false;
	}
}

