#ifndef _VITAIDENT_WEATHER_H_
#define _VITAIDENT_WEATHER_H_

#include <psp2/ctrl.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vita2d.h>

vita2d_texture *dClearSky, *dClouds, *dRain, *dSnow, *dThunderstorm;
vita2d_texture *nClearSky, *nClouds, *nRain, *nSnow, *nThunderstorm;
vita2d_texture *mist;

char zip[10];

/*
	Day icons
*/
extern unsigned char _binary_res_day_dClearSky_png_start;
extern unsigned char _binary_res_day_dClouds_png_start;
extern unsigned char _binary_res_day_dRain_png_start;
extern unsigned char _binary_res_day_dThunderstorm_png_start;
extern unsigned char _binary_res_day_dSnow_png_start;

/*
	Night icons
*/
extern unsigned char _binary_res_night_nClearSky_png_start;
extern unsigned char _binary_res_night_nClouds_png_start;
extern unsigned char _binary_res_night_nRain_png_start;
extern unsigned char _binary_res_night_nThunderstorm_png_start;
extern unsigned char _binary_res_night_nSnow_png_start;

extern unsigned char _binary_res_mist_png_start;

int CorF;

void initWeatherData();
int getWeatherZip();
int downloadWeatherData();
char * getWeatherContent(char * string, char * str1, char * str2);
double strToDouble(char * str);
double kelvinToC(double temp);
double kelvinToF(double temp);
double mToKm(double m);
double mToMph(double m);
void displayWeatherContent();
void displayWeatherIcon(char * desc, bool day);

#endif