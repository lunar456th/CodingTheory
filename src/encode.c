#include "utility.h"

int e(int sel, const char *from, const char *to)
{
	switch(sel)
	{
	case 0:
		return e0(from, to);
		break;
	case 1:
		return e1(from, to);
		break;
	case 2:
		return e2(from, to);
		break;
	case 3:
		return e3(from, to);
		break;
	case 4:
		return e4(from, to);
		break;
	default:
		break;
	}
	return 0;
}

int e0(const char *from, const char *to)
{
	int buf;
	FILE *fin = fopen(from, "rb");
	FILE *fout = fopen(to, "w+");
	while(!feof(fin))
	{
		fread(&buf, sizeof(int), 1, fin);
		fprintf(fout, "%x ", buf);
	}
	return 0;
}

int e1(const char *from, const char *to)
{
	uint64_t buf;
	FILE *fin = fopen(from, "rb");
	FILE *fout = fopen(to, "w+");
	while(!feof(fin))
	{
		fread(&buf, sizeof(uint64_t), 1, fin);
		fprintf(fout, "%016llx ", buf);
	}
	return 0;
}

int e2(const char *from, const char *to)
{
	uint8_t buf;
	FILE *fin = fopen(from, "rb");
	FILE *fout = fopen(to, "w+");
	while(!feof(fin))
	{
		fread(&buf, sizeof(uint8_t), 1, fin);
		fprintf(fout, "%x", (buf & 0xf0) >> 4);
		fprintf(fout, "%x", (buf & 0xf));
	}
	return 0;
}

int e3(const char *from, const char *to)
{
	FILE *fin = fopen(from, "rb");
	FILE *fout = fopen(to, "w+");
	uint8_t buf[3];
	uint8_t chr[4];

	while(!feof(fin))
	{
		fread(buf, sizeof(uint8_t), 3, fin);
		chr[0] = (buf[0] & 0xfc) >> 2;
		chr[1] = ((buf[0] & 0x3) << 4) | ((buf[1] & 0xf0) >> 4);
		chr[2] = ((buf[1] & 0xf) << 2) | ((buf[2] & 0xc0) >> 6);
		chr[3] = buf[2] & 0x3f;
		fprintf(fout, "%c%c%c%c", chr_table[chr[0]], chr_table[chr[1]], chr_table[chr[2]], chr_table[chr[3]]);
		chr[0] = chr[1] = chr[2] = 0;
	}
	return 0;
}

int e4(const char *from, const char *to)
{
	FILE *fin = fopen(from, "rb");
	FILE *fout = fopen(to, "wb+");
	wchar_t src[15];
	wchar_t dest[16];
	int i;
	setlocale(LC_ALL, ".OCP");
	wchar_t mark = 0xfeff;
	fwrite(&mark, sizeof(wchar_t), 1, fout);
	while(!feof(fin))
	{
		fread(src, sizeof(wchar_t), 15, fin);
		dest[0]  =  (src[0]  & 0xfffe)  >> 1;
		dest[1]  = ((src[0]  & 0x1)    << 14) | ((src[1]  & 0xfffc) >>  2);
		dest[2]  = ((src[1]  & 0x3)    << 13) | ((src[2]  & 0xfff8) >>  3);
		dest[3]  = ((src[2]  & 0x7)    << 12) | ((src[3]  & 0xfff0) >>  4);
		dest[4]  = ((src[3]  & 0xf)    << 11) | ((src[4]  & 0xffe0) >>  5);
		dest[5]  = ((src[4]  & 0x1f)   << 10) | ((src[5]  & 0xffc0) >>  6);
		dest[6]  = ((src[5]  & 0x3f)   <<  9) | ((src[6]  & 0xff80) >>  7);
		dest[7]  = ((src[6]  & 0x7f)   <<  8) | ((src[7]  & 0xff00) >>  8);
		dest[8]  = ((src[7]  & 0xff)   <<  7) | ((src[8]  & 0xfe00) >>  9);
		dest[9]  = ((src[8]  & 0x1ff)  <<  6) | ((src[9]  & 0xfc00) >> 10);
		dest[10] = ((src[9]  & 0x3ff)  <<  5) | ((src[10] & 0xf800) >> 11);
		dest[11] = ((src[10] & 0x7ff)  <<  4) | ((src[11] & 0xf000) >> 12);
		dest[12] = ((src[11] & 0xfff)  <<  3) | ((src[12] & 0xe000) >> 13);
		dest[13] = ((src[12] & 0x1fff) <<  2) | ((src[13] & 0xc000) >> 14);
		dest[14] = ((src[13] & 0x3fff) <<  1) | ((src[14] & 0x8000) >> 15);
		dest[15] =   src[14] & 0x7fff;
		for(i = 0; i < 16; i++)
		{
			dest[i] = bit15_to_unicode(dest[i]);
			fwprintf(fout, L"%c", dest[i]);
		}
		dest[0] = dest[1] = dest[2]  = dest[3]  = dest[4]  = dest[5]  = dest[6]  = dest[7]  = 0;
		dest[8] = dest[9] = dest[10] = dest[11] = dest[12] = dest[13] = dest[14] = dest[15] = 0;
	}
	return 0;
}
