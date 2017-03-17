#include "main.h"
#include "net.h"
#include "utils.h"

int initNet()
{
	sysmoduleLoadModule(SCE_SYSMODULE_NET);
	
	static char memory[16 * 1024];

	SceNetInitParam param;
	param.memory = memory;
	param.size = sizeof(memory);
	param.flags = 0;

	sceNetInit(&param);
	sceNetCtlInit();
	
	return 1;
}

void termNet()
{
	sceNetCtlTerm();
	sceNetTerm();
}

void httpInit() 
{
	sysmoduleLoadModule(SCE_SYSMODULE_HTTP);
	sceHttpInit(1 * 1024 * 1024);
}

void httpTerm() 
{
	sceHttpTerm();
	sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTP);
}

void download(const char *url, const char *dest) 
{
	vita2d_pvf_draw_textf(font, 40, 120, RGBA8(255, 255, 255, 255), 1.0f, "\n\nDownloading %s to %s\n", url, dest);
	
	int tpl = sceHttpCreateTemplate("Weather Data", 1, 1);
	
	vita2d_pvf_draw_textf(font, 40, 140, RGBA8(255, 255, 255, 255), 1.0f, "0x%08X sceHttpCreateTemplate\n", tpl);

	// set url on the template
	int conn = sceHttpCreateConnectionWithURL(tpl, url, 0);
	vita2d_pvf_draw_textf(font, 40, 160, RGBA8(255, 255, 255, 255), 1.0f, "0x%08X sceHttpCreateConnectionWithURL\n", conn);

	// create the request with the correct method
	int request = sceHttpCreateRequestWithURL(conn, SCE_HTTP_METHOD_GET, url, 0);
	vita2d_pvf_draw_textf(font, 40, 180, RGBA8(255, 255, 255, 255), 1.0f, "0x%08X sceHttpCreateRequestWithURL\n", request);

	// send the actual request. Second parameter would be POST data, third would be length of it.
	int handle = sceHttpSendRequest(request, NULL, 0);
	vita2d_pvf_draw_textf(font, 40, 200, RGBA8(255, 255, 255, 255), 1.0f, "0x%08X sceHttpSendRequest\n", handle);

	// open destination file
	int fh = sceIoOpen(dest, SCE_O_WRONLY | SCE_O_CREAT, 0777);
	vita2d_pvf_draw_textf(font, 40, 220, RGBA8(255, 255, 255, 255), 1.0f, "0x%08X sceIoOpen\n", fh);

	// create buffer and counter for read bytes.
	unsigned char data[16*1024];
	int read = 0;

	// read data until finished
	while ((read = sceHttpReadData(request, &data, sizeof(data))) > 0) {
		vita2d_pvf_draw_textf(font, 240, 120, RGBA8(255, 255, 255, 255), 1.0f, "read %d bytes\n", read);

		// writing the count of read bytes from the data buffer to the file
		int write = sceIoWrite(fh, data, read);
		vita2d_pvf_draw_textf(font, 260, 120, RGBA8(255, 255, 255, 255), 1.0f, "wrote %d bytes\n", write);
	}

	// close file
	sceIoClose(fh);
	vita2d_pvf_draw_textf(font, 40, 280, RGBA8(255, 255, 255, 255), 1.0f, "sceIoClose\n");
}

char * getIP() //local ip
{
	static char address[16];

	SceNetCtlInfo info;
	if (sceNetCtlInetGetInfo(SCE_NETCTL_INFO_GET_IP_ADDRESS, &info) < 0) 
	{
		strcpy(address, "-");
	}
	else 
	{
		strcpy(address, info.ip_address);
	}
	
	return address;
}