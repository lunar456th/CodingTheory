#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <locale.h>

char chr_table[64];

uint8_t table_conv(const char);
wchar_t bit15_to_unicode(const wchar_t);
wchar_t unicode_to_bit15(const wchar_t);

int e(int, const char*, const char*);
int e0(const char*, const char*);
int e1(const char*, const char*);
int e2(const char*, const char*);
int e3(const char*, const char*);
int e4(const char*, const char*);

int d(int, const char*, const char*);
int d0(const char*, const char*);
int d1(const char*, const char*);
int d2(const char*, const char*);
int d3(const char*, const char*);
int d4(const char*, const char*);

#endif /* __UTILITY_H__ */
