#pragma once

#include "singletonBase.h"

#include <map>
#include <string>

//fmod.hpp �߰�
#include "inc/fmod.hpp"

//lib ��ũ
#pragma comment (lib, "lib/fmodex_vc.lib")

//�������� ä�� ���� ����(����)
#define EXTRA_SOUND_CHANNEL 50
#define SOUNDBUFFER 50

//�� ���� ����
#define TOTAL_SOUND_CHANNEL SOUNDBUFFER + EXTRA_SOUND_CHANNEL

using namespace FMOD;

class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;

private:
	System* _system;
	Sound** _sound;

	Channel** _channel;

	arrSounds _mTotalSounds;

public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();

	//���� �߰�
	void addSound( string keyName, string soundName, bool background = false, bool loop = false );

	//���
	void play( string keyName, float volume );
	
	//����
	void stop( string keyName );
	
	//����
	void pause( string keyName );
	
	//�ٽ� ���
	void resume( string keyName );
	
	//�����ִ�?
	bool isPauseSound( string keyName );
	
	//������̴�?
	bool isPlaySound( string keyName );

	//��� �ð�
	unsigned int getLength( string keyName );

	//���� ����
	void volume();

	//Fmod �ý��� ����
	void update();

};
