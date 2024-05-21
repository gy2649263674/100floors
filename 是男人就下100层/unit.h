#pragma once
#include <ctime>
#include<iostream>
#include<windows.h>
#include<easyx.h>
#include<graphics.h>
#include<deque>
#include<iostream>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iterator>
#include <streambuf>
#include <vector>
#include<deque>
#include<functional>
#define MAINW 1000
#define LENGTH 1000
#define MAINH 750
#define WIDTH 750
#define MAINX 256
#define MAINY 0
#define BTW 50
#define BTH 50
#define BTPOSX 250
#define BTPOSY 20
#define BTGAP 2000
#define MAPNUM 5
#define WORDX ((MAINW)/2)
#define _10PER 30
#define WORDY (MAINH-_10PER)
#define KLEFT 37
#define KRIGHT 39
#define KUP 38
#define KDOWN 40
#define WINW 860
#define WINH 1024
#define ROOTDIR "picture"
#define MAPDIR "map"
#define BTDIR "button"
#define PICDIR "picture"
#define MASK "_mask"
#define ROLEH 60
#define ROLEW 60

#define BOARD_GAP 50
#define CLICKED 0 
#define HANGON 2
#define UNIN 1
#define	 LEFT -1
#define	 RIGHT 1
#define BOARDW 40
#define BOARDH 40
#define FPS 60
#define FRAME 1000/60
enum entertain
{
	normal,
	jump_jump,
	fake_world,
	run_run,
};