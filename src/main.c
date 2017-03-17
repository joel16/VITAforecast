#include "clock.h"
#include "fs.h"
#include "ime_dialog.h"
#include "main.h"
#include "net.h"
#include "utils.h"
#include "weather.h"

extern unsigned char _binary_res_background_png_start;
extern unsigned char _binary_res_gekihen_png_start;
extern unsigned char _binary_res_wifi_png_start;

int mainMenu()
{	
	while (1) 
	{	
		vita2d_start_drawing();
		vita2d_clear_screen();
		
		downloadWeatherData(); //Constatly download and replace data in the background.
		vita2d_draw_texture(background, 0, 0);
		
		if(netAccess == true)
			vita2d_draw_texture(wifi, 0, 0);
		
		//vita2d_pvf_draw_text(font, 360, 80, RGBA8(255, 255, 255, 255), 2.0f, "Current Weather");
		digitaltime(840, 22, RGBA8(255, 255, 255, 255), 1.3f, 0);
		
		if (fileExists("ux0:data/VITAforecast/weather.txt"))
			displayWeatherContent();
		
		controls();
		
		if (pressed & SCE_CTRL_SQUARE)
		{
			strcpy(zip, keyboard_vita_get("Enter zip-code and country ID. Example: 07001,US", 10));
			WriteFile("ux0:data/VITAforecast/zipCode.txt", zip, 10);
		}
		
		if (pressed & SCE_CTRL_START)
			sceKernelExitProcess(0);
		
		endDrawing();
	}	
	
	return 0;
}

int controls()
{
	memset(&pad, 0, sizeof(SceCtrlData));
	sceCtrlPeekBufferPositive(0, &pad, 1);

	pressed = pad.buttons & ~old_pad.buttons;
	
	old_pad = pad;
	return 0;
}

int main(int argc, char *argv[]) 
{
	vita2d_init();
	
	vita2d_set_clear_color(RGBA8(0, 0, 0, 255));
	
	background = loadPngWithFilter(&_binary_res_background_png_start);
	gekihen = loadPngWithFilter(&_binary_res_gekihen_png_start);
	wifi = loadPngWithFilter(&_binary_res_wifi_png_start);
	mist = loadPngWithFilter(&_binary_res_mist_png_start);
	
	dClearSky = loadPngWithFilter(&_binary_res_day_dClearSky_png_start);
	dClouds = loadPngWithFilter(&_binary_res_day_dClouds_png_start);
	dRain = loadPngWithFilter(&_binary_res_day_dRain_png_start);
	dThunderstorm = loadPngWithFilter(&_binary_res_day_dThunderstorm_png_start);
	dSnow = loadPngWithFilter(&_binary_res_day_dSnow_png_start);
	
	nClearSky = loadPngWithFilter(&_binary_res_night_nClearSky_png_start);
	nClouds = loadPngWithFilter(&_binary_res_night_nClouds_png_start);
	nRain = loadPngWithFilter(&_binary_res_night_nRain_png_start);
	nThunderstorm = loadPngWithFilter(&_binary_res_night_nThunderstorm_png_start);
	nSnow = loadPngWithFilter(&_binary_res_night_nSnow_png_start);
	
	font = vita2d_load_default_pvf();
	
	int ret = initNet();
	if(ret != 0) 
		netAccess = true;
	httpInit();
	
	createWeatherDir();
	

	vita2d_start_drawing();
	vita2d_clear_screen();
	vita2d_draw_texture(gekihen, 0, 0);
	endDrawing();
	sceKernelDelayThread(4 * 1000 * 1000);//delay 4 seconds
	vita2d_clear_screen();
	
	
	if (fileExists("ux0:data/VITAforecast/zipCode.txt"))
		readFile("ux0:data/VITAforecast/zipCode.txt", zip, 10);
	else
	{
		strcpy(zip, keyboard_vita_get("Enter zip-code and country ID. Example: 07001,US", 10));
		WriteFile("ux0:data/VITAforecast/zipCode.txt", zip, 10);
	}
	
	char buffer[1024];
	if (fileExists("ux0:data/VITAforecast/weather.txt"))
		readFile("ux0:data/VITAforecast/weather.txt", buffer, 1024);
	
	if ((strcmp(getWeatherContent(buffer, "country\":\"", "\",\"sunr"), "US") == 0) || (strcmp(getWeatherContent(buffer, "country\":\"", "\",\"sunr"), "us") == 0))
		CorF = 0;
	else
		CorF = 1;
	
	while(1)
	{
		mainMenu();
	}
	
	httpTerm();
	termNet();
	
	vita2d_fini();
	vita2d_free_texture(background);
	vita2d_free_pvf(font);
	sceKernelExitProcess(0);
	
	return 0;
}
