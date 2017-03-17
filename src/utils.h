#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <psp2/display.h>
#include <psp2/io/fcntl.h>
#include <psp2/sysmodule.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vita2d.h>

int sysmoduleLoadModule(SceUInt16 id);
vita2d_texture * loadPngWithFilter(const void *buffer);
void endDrawing();

#endif