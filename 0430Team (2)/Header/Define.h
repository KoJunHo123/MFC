#pragma once

#define		WINCX		800
#define		WINCY		600

#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1

#define		VK_MAX			0xff

#define		TILECX			24//130
#define		TILECY			24//68

#define		TILEX			50
#define		TILEY			50

#pragma region 타입(비트 연산용)
#define		NORMAL			0x0001
#define		FIRE			0x0002
#define		WATER			0x0004
#define		GRASS			0x0008
#define		ELECTRIC		0x0010
#define		ICE				0x0020
#define		FIGHT			0x0040
#define		POISON			0x0080
#define		GROUND			0x0100
#define		FLYING			0x0200
#define		PSYCHIC			0x0400
#define		BUG				0x0800
#define		ROCK			0x1000
#define		GHOST			0x2000
#define		DRAGON			0x4000
#define		DARK			0x8000
#define		STEEL			0x10000
#define		FAIRY			0x20000
#pragma endregion

#define		MIN_STR			64
#define		MAX_STR			256

#define		RUBY			0x01		// -> 0001
#define		DIAMOND			0x02		// -> 0010
#define		SAPPHIRE		0x04		// -> 0100


#pragma region 방향
#define		LEFT			0x01
#define		TOP				0x02
#define		RIGHT			0x04
#define		BOTTOM			0x08
#pragma endregion


extern HWND		g_hWnd;

#define ERR_MSG(message)								\
::MessageBox(nullptr, message, L"error", MB_OK)

#define NO_COPY(ClassName)								\
ClassName(const ClassName&) = delete;					\
ClassName& operator=(const ClassName&) = delete;

#define DECLARE_SINGLETON(ClassName)					\
		NO_COPY(ClassName)								\
public :												\
	static ClassName* Get_Instance();					\
	static void		  Destroy_Instance();				\
private:												\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)					\
ClassName* ClassName::m_pInstance = nullptr;			\
ClassName* ClassName::Get_Instance()					\
{														\
	if (nullptr == m_pInstance)							\
		m_pInstance = new ClassName;					\
	return m_pInstance;									\
}														\
void ClassName::Destroy_Instance()						\
{														\
	if(nullptr != m_pInstance)							\
	{													\
		delete m_pInstance;								\
		m_pInstance = nullptr;							\
	}													\
}




// 선언과 동시에 초기화 불가능, 먼저 선언된 전역변수와 자료형, 변수명까지 일치하는 상태에서만 사용 가능