#ifndef _VITAIDENT_MAIN_H_
#define _VITAIDENT_MAIN_H_

#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/io/fcntl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/location.h>
#include <psp2/sysmodule.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <vita2d.h>

#define selector_xDistance 0 //The distance between the X axis of the two selections
#define selector_yDistance 40 //The distance between the Y axis of the two selections

vita2d_texture *background, *gekihen, *wifi;
vita2d_pvf *font;

SceLocationHandle locHandle;
bool netAccess;

int sceLocationInit();
int sceLocationTerm();

SceCtrlData pad, old_pad;
unsigned int pressed;

void getLocation();
int controls();
int mainMenu();

#endif