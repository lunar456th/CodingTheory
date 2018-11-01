#include "utility.h"

char chr_table[64] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
		'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
		'y', 'z', '-', '+',
};

uint8_t table_conv(const char buf)
{
	if(buf == 43)
		return buf - 43 + 63;
	else if(buf == 45)
		return buf - 45 + 62;
	else if(48 <= buf && buf <= 57)
		return buf - 48;
	else if(65 <= buf && buf <= 90)
		return buf - 65 + 10;
	else if(97 <= buf && buf <= 122)
		return buf - 97 + 10 + 26;
	else
		return 0;
}

wchar_t bit15_to_unicode(const wchar_t src)
{
	if(0 <= src && src <= 11183)
		return src + 0xac00;
	else if(11184 <= src && src <= 32175)
		return src - 11184 + 0x4E00;
	else if(32176 <= src && src <= 32767)
		return src - 32176 + 0x3400;
	else
		return 0;
}

wchar_t unicode_to_bit15(const wchar_t src)
{
	if(0xAC00 <= src && src <= 0xD7AF)
		return src - 0xac00;
	else if(0x4E00 <= src && src <= 0x9FFF)
		return src - 0x4E00 + 11184;
	else if(0x3400 <= src && src <= 0x3650)
		return src - 0x3400 + 32176;
	else
		return 0;
}
