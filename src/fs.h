#ifndef _VITAIDENT_FS_H_
#define _VITAIDENT_FS_H_

#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/devctl.h>

#include <string.h>

typedef struct {
	uint64_t max_size;
	uint64_t free_size;
	uint32_t cluster_size;
	void *unk;
} SceIoDevInfo;

int fileExists(const char *path);
int dirExists(const char *path);
int readFile(char *file, void *buf, int size);
int writeFile(char *file, void *buf, int size);
int removeFile(char *file);
int getFileSize(const char *file);

#endif