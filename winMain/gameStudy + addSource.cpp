#include "stdafx.h"
#include "gameStudy.h"

void gameStudy::addSource()
{
	//키 움직이고 선택 취소 사운드
	SOUNDMANAGER->addSound("select_ok", "titleScene/select_ok_snd.mp3", false, false); //OK 소리1
	SOUNDMANAGER->addSound("stage_ok", "titleScene/stage_ok.mp3", false, false); //OK 소리2
	SOUNDMANAGER->addSound("select_cancel", "titleScene/select_cancel_snd.mp3", false, false); //취소
	SOUNDMANAGER->addSound("select_move", "titleScene/select_move_snd.mp3", false, false); //선택 움직 일 때
	SOUNDMANAGER->addSound("ctl_move", "titleScene/ctl_move.mp3", false, false); //마왕, 곡괭이 움직 일 때 2
	SOUNDMANAGER->addSound("volume_se", "titleScene/volume_se.mp3", false, false); //se 사운드 크기 조절 시
	SOUNDMANAGER->addSound("appearScene", "hero/appearScene.mp3", false, false); //hero 등장 씬 노래
	SOUNDMANAGER->addSound("hero_in", "hero/hero_in.mp3", false, false); //hero 등장 씬 노래
	SOUNDMANAGER->addSound("hero_arrest", "hero/hero_arrest.mp3", true, true); //hero maou 잡고나서 노래
	SOUNDMANAGER->addSound("hero_in_play", "hero/hero_in_play.mp3", true, true); //hero 마왕 던전 진입 후 노래
	//곡괭이용
	//SOUNDMANAGER->addSound("pickax_move", "play/pickax_move_snd.mp3", false, false); //se 사운드 크기 조절 시
	//talk_box 용
	//IMAGEMANAGER->addImage("t_box", "textbox/talk_box.bmp", 900, 102, true, TRANSCOLOR);
	//IMAGEMANAGER->addImage("end_point", "textbox/talk_point.bmp", 29, 15, true, TRANSCOLOR);
	//IMAGEMANAGER->addImage("maou_idle", "textbox/maou_idle.bmp", 125, 94, false, false);
	//IMAGEMANAGER->addImage("maou_excit", "textbox/maou_excited.bmp", 125, 94, false, false);
	//IMAGEMANAGER->addImage("maou_omg", "textbox/maou_omg.bmp", 125, 94, false, false);
	//IMAGEMANAGER->addImage("maou_otl", "textbox/maou_otl.bmp", 125, 94, false, false);
	//IMAGEMANAGER->addImage("maou_sad", "textbox/maou_sad.bmp", 125, 94, false, false);
	//worldScene
	/*IMAGEMANAGER->addImage("stage_board", "worldScene/stage_board2.bmp", 320, 114, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("world_bg", "worldScene/worldmap.bmp", WINSIZEX, WINSIZEY, false, false);
	IMAGEMANAGER->addImage("world_alpha", "worldScene/world_alpha.bmp", WINSIZEX, WINSIZEY, false, false);
	SOUNDMANAGER->addSound("worldScene_bgm", "worldScene/worldScene_bgm.mp3", true, true);*/
	//titleScene
	//IMAGEMANAGER->addImage("title_bg", "titleScene/title(956x516).bmp", 956, 516, false, false); // 배경
	//SOUNDMANAGER->addSound("titleScene_bgm", "titleScene/titleScene_bgm.mp3", true, true); //배경음
	//
	//stage
	IMAGEMANAGER->addImage("block_1", "stage_1/block_1.bmp", 36, 36, false, false);
	//slime
	SOUNDMANAGER->addSound("slime_appear", "monster/slime/slime_appear.mp3", false, false);
	SOUNDMANAGER->addSound("slime_move", "monster/slime/slime_move.mp3", false, false);
	EFFECTMANAGER->addEffect("slime_damage_effect", "monster/slime/slime_damage_effect.bmp", 180, 33, 36, 33, 5, 0.02, 15);
	EFFECTMANAGER->addEffect("hero_damage_effect", "hero/hero_damage_effect.bmp", 200, 37, 40, 37, 5, 0.02, 15);
}