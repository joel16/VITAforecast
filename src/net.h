#ifndef _VITAIDENT_NET_H_
#define _VITAIDENT_NET_H_

#include <psp2/io/fcntl.h>

#include <psp2/net/http.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>

#include <stdio.h>
#include <string.h>

int initNet();
void termNet();
void httpInit();
void httpTerm();
void download(const char *url, const char *dest);
char * getIP();

#endif