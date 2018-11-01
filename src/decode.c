#include "utility.h"

int d(int sel, const char *from, const char *to)
{
	switch(sel)
	{
	case 0:
		return d0(from, to);
		break;
	case 1:
		return d1(from, to);
		break;
	case 2:
		return d2(from, to);
		break;
	case 3:
		return d3(from, to);
		break;
	case 4:
		return d4(from, to);
		break;
	default:
		break;
	}
	return 0;
}

int d0(const char *from, const char *to)
{
	FILE *fin = fopen(from, "r");
	FILE *fout = fopen(to, "wb+");
	int buf;
	while(!feof(fin))
	{
		fscanf(fin, "%x", &buf);
		fwrite(&buf, sizeof(int), 1, fout);
	}
	return 0;
}

int d1(const char *from, const char *to)
{
	FILE *fin = fopen(from, "r");
	FILE *fout = fopen(to, "wb+");
	uint64_t buf;
	while(!feof(fin))
	{
		fscanf(fin, "%llx", &buf);
		fwrite(&buf, sizeof(uint64_t), 1, fout);
	}
	return 0;
}

int d2(const char *from, const char *to)
{
	FILE *fin = fopen(from, "r");
	FILE *fout = fopen(to, "wb+");
	int i;
	char ch[2];
	uint8_t buf;
	while(!feof(fin))
	{
		for(i = 0; i < 2; i++)
		{
			fscanf(fin, "%c", &ch[i]);
			if(ch[i] >= 'a' && ch[i] <= 'z')
				ch[i] -= 87;
			else
				ch[i] -= 48;
		}
		buf = (ch[0] << 4) | ch[1];
		fwrite(&buf, sizeof(uint8_t), 1, fout);
	}
	return 0;
}

int d3(const char *from, const char *to)
{
	FILE *fin = fopen(from, "r");
	FILE *fout = fopen(to, "wb+");
	uint8_t bin[3];
	uint8_t chr[4];
	char buf[4];


	while(!feof(fin))
	{
		fscanf(fin, "%c%c%c%c", &buf[0], &buf[1], &buf[2], &buf[3]);
		chr[0] = table_conv(buf[0]);
		chr[1] = table_conv(buf[1]);
		chr[2] = table_conv(buf[2]);
		chr[3] = table_conv(buf[3]);
		bin[0] = ((chr[0] & 0x3f) << 2) | ((chr[1] & 0x30) >> 4);
		bin[1] = ((chr[1] & 0x0f) << 4) | ((chr[2] & 0x3c) >> 2);
		bin[2] = ((chr[2] & 0x03) << 6) | (chr[3] & 0x3f);
		fwrite(bin, sizeof(uint8_t), 3, fout);
		bin[0] = bin[1] = bin[2] = 0;
	}
	return 0;
}

int d4(const char *from, const char *to)
{
	FILE *fin = fopen(from, "rb");
	FILE *fout = fopen(to, "wb+");
	wchar_t src[16];
	wchar_t dest[15];
	int i;
	fseek(fin, sizeof(wchar_t), SEEK_SET);
	setlocale(LC_ALL, ".OCP");
	while(!feof(fin))
	{
		for(i = 0; i < 16; i++)
		{
			fwscanf(fin, L"%lc", &src[i]);
			src[i] = unicode_to_bit15(src[i]);
		}
		dest[0]   = (src[0]  <<  1) | ((src[1]  & 0x4000) >> 14);
		dest[1]   = (src[1]  <<  2) | ((src[2]  & 0x6000) >> 13);
		dest[2]   = (src[2]  <<  3) | ((src[3]  & 0x7000) >> 12);
		dest[3]   = (src[3]  <<  4) | ((src[4]  & 0x7800) >> 11);
		dest[4]   = (src[4]  <<  5) | ((src[5]  & 0x7c00) >> 10);
		dest[5]   = (src[5]  <<  6) | ((src[6]  & 0x7e00) >>  9);
		dest[6]   = (src[6]  <<  7) | ((src[7]  & 0x7f00) >>  8);
		dest[7]   = (src[7]  <<  8) | ((src[8]  & 0x7f80) >>  7);
		dest[8]   = (src[8]  <<  9) | ((src[9]  & 0x7fc0) >>  6);
		dest[9]   = (src[9]  << 10) | ((src[10] & 0x7fe0) >>  5);
		dest[10]  = (src[10] << 11) | ((src[11] & 0x7ff0) >>  4);
		dest[11]  = (src[11] << 12) | ((src[12] & 0x7ff8) >>  3);
		dest[12]  = (src[12] << 13) | ((src[13] & 0x7ffc) >>  2);
		dest[13]  = (src[13] << 14) | ((src[14] & 0x7ffe) >>  1);
		dest[14]  = (src[14] << 15) |  (src[15] & 0x7fff);
		fwrite(dest, sizeof(wchar_t), 15, fout);
		dest[0] = dest[1] = dest[2]  = dest[3]  = dest[4]  = dest[5]  = dest[6]  = dest[7]  = 0;
		dest[8] = dest[9] = dest[10] = dest[11] = dest[12] = dest[13] = dest[14] = 0;
	}
	return 0;
}
//dest[0]  = (src[0]  <<  1) | ((src[1]  & 0x8000) >> 15);
//dest[1]  = (src[1]  <<  2) | ((src[2]  & 0xc000) >> 14);
//dest[2]  = (src[2]  <<  3) | ((src[3]  & 0xe000) >> 13);
//dest[3]  = (src[3]  <<  4) | ((src[4]  & 0xf000) >> 12);
//dest[4]  = (src[4]  <<  5) | ((src[5]  & 0xf800) >> 11);
//dest[5]  = (src[5]  <<  6) | ((src[6]  & 0xfc00) >> 10);
//dest[6]  = (src[6]  <<  7) | ((src[7]  & 0xfe00) >>  9);
//dest[7]  = (src[7]  <<  8) | ((src[8]  & 0xff00) >>  8);
//dest[8]  = (src[8]  <<  9) | ((src[9]  & 0xff80) >>  7);
//dest[9]  = (src[9]  << 10) | ((src[10] & 0xffc0) >>  6);
//dest[10] = (src[10] << 11) | ((src[11] & 0xffe0) >>  5);
//dest[11] = (src[11] << 12) | ((src[12] & 0xfff0) >>  4);
//dest[12] = (src[12] << 13) | ((src[13] & 0xfff8) >>  3);
//dest[13] = (src[13] << 14) | ((src[14] & 0xfffc) >>  2);
//dest[14] = (src[14] << 15) | ((src[15] & 0xfffe) >>  1);
