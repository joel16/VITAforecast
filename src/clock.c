#include "clock.h"
#include "main.h"

void digitaltime(int x, int y, int color, float size, int hr)
{					
	SceDateTime time;
	sceRtcGetCurrentClockLocalTime(&time);
		
	if (hr == 0)
	{
		if(time.hour >= 12) 
			vita2d_pvf_draw_text(font, x + 70, y, RGBA8(255, 255, 255, 255), 1.0f, "PM"); 
		else 
			vita2d_pvf_draw_text(font, x + 70, y, RGBA8(255, 255, 255, 255), 1.0f, "AM");   
		
		if (time.hour > 12)
			time.hour -= 12;
	
		if (time.hour == 00)
			time.hour = 12;
			
		vita2d_pvf_draw_textf(font, x, y, RGBA8(255, 255, 255, 255), size, "%2d:%02d", time.hour, time.minute);
	}
	
	else if (hr == 1)
	{
		vita2d_pvf_draw_textf(font, x + 40, y, RGBA8(255, 255, 255, 255), size, "%2d:%02d", time.hour, time.minute);
	}
}

void getDayOfWeek(int x, int y, int style, float size)
{
	SceDateTime time;
	sceRtcGetCurrentClockLocalTime(&time);

	int day = sceRtcGetDayOfWeek(time.year, time.month, time.day);

    static const char days[7][16] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    
    char buffer[16];
	sprintf(buffer, "%s", days[day]);
    
    if(style == 1)
        buffer[3] = 0;
        
    vita2d_pvf_draw_textf(font, x, y, RGBA8(255, 255, 255, 255), size, "%s", buffer);
}
	
void getMonthOfYear(int x, int y, float size)
{
	static const char months[12][16] =
	{
		"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
	};
       
    SceDateTime time;
	sceRtcGetCurrentClockLocalTime(&time);
    vita2d_pvf_draw_textf(font, x, y, RGBA8(255, 255, 255, 255), size, "%d %s", time.day, months[time.month - 1]);
}