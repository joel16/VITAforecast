TARGET 		:= VITAforecast
PROJECT_TITLE := VITA Forecast
TITLE_ID 	:= VITACAST0
SOURCES 	:= src

OBJS = clock.o fs.o ime_dialog.o main.o net.o utils.o weather.o \
	   res/background.o res/gekihen.o res/mist.o res/wifi.o \
	   res/day/dClearSky.o res/day/dClouds.o res/day/dRain.o res/day/dSnow.o res/day/dThunderstorm.o \
	   res/night/nClearSky.o res/night/nClouds.o res/night/nRain.o res/night/nSnow.o res/night/nThunderstorm.o \

PREFIX   = arm-vita-eabi
CC       = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
CFLAGS   = -Wl,-q -Wall -Werror -O3 -fno-lto
CXXFLAGS = $(CFLAGS) -std=c++11 -fno-rtti -fno-exceptions
ASFLAGS  = $(CFLAGS)

LIBDIR = 
LDFLAGS = 
LIBS := -lvita2d -lSceDisplay_stub -lSceGxm_stub \
		-lSceSysmodule_stub -lSceCtrl_stub -lScePvf_stub \
		-lSceCommonDialog_stub -lfreetype -lpng -ljpeg -lz -lm -lc \
		-lSceAppUtil_stub -lSceNet_stub -lSceNetCtl_stub -lSceHttp_stub \

all: $(TARGET).vpk

%.vpk: eboot.bin
	vita-mksfoex -d PARENTAL_LEVEL=1 -s APP_VER=01.00 -s TITLE_ID=$(TITLE_ID) "$(PROJECT_TITLE)" param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin \
		--add ../sce_sys/icon0.png=sce_sys/icon0.png \
		--add ../sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png \
		--add ../sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png \
		--add ../sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml \
	$(TARGET).vpk
	
eboot.bin: $(TARGET).velf
	vita-make-fself -s -c $< $@

%.velf: %.elf
	$(PREFIX)-strip -g $<
	vita-elf-create $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

%.o: %.png
	$(PREFIX)-ld -r -b binary -o $@ $^

clean:
	@rm -rf $(TARGET).vpk $(TARGET).velf $(TARGET).elf $(TARGET).unstripped.elf $(OBJS) \
		eboot.bin param.sfo
