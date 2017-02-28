#include<stdlib.h>

typedef unsigned char byte;

static byte* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static byte indexof(byte c){  // return the index of a byteacter in the base64 alphabet
	if(c == '/')
		return 63;
	else if(c == '+')
		return 62;
	else if('0' <= c && c <= '9')
		return 52 + (c - '0');
	else if('a' <= c && c <= 'z')
		return 26 + (c - 'a');
	else if('A' <= c && c <= 'Z')
		return c - 'A';
	else
		return 64;
}

// 一次通过不需要调试666666666666

__declspec(dllexport) byte* encode(const byte* p){
	int i = 0, length = 0, padding = 0;
	// get length and padding in the original string
	while(p[i++] != '\0')
		length += 1;
	if((length + 1) % 3 == 0)
		padding = 1;
	if((length + 2) % 3 == 0)
		padding = 2;

	// allocate space for return string
	byte* c = (byte*)malloc(((length+padding)*4/3) * sizeof(byte) + 1);

	// start encode
	byte m2 = 0x03, m4 = 0x0F, m6 = 0x3F;
	int j = 0; // index of the return byteacter
	for(i = 0; i < length; i += 3){
		if(i + 3 > length){  // considering padding
			c[j++] = alphabet[(p[i] >> 2) & m6];
			if(padding == 1){
				c[j++] = alphabet[((p[i] & m2) << 4) ^ ((p[i+1] >> 4) & m4)];
				c[j++] = alphabet[(p[i+1] & m4) << 2];
			}
			if(padding == 2){
				c[j++] = alphabet[(p[i] & m2) << 4];
				c[j++] = '=';
			}
			c[j++] = '=';
		}
		else{
			c[j++] = alphabet[(p[i] >> 2) & m6];
			c[j++] = alphabet[((p[i] & m2) << 4) ^ ((p[i+1] >> 4) & m4)];
			c[j++] = alphabet[((p[i+1] & m4) << 2) ^ ((p[i+2] >> 6) & m2)];
			c[j++] = alphabet[p[i+2] & m6];
		}
	}

	c[j] = '\0';
	return c;
}

__declspec(dllexport) byte* decode(const byte* c){
	int i = 0, length = 0, padding = 0;
	while(c[i] != '\0'){
		length += 1;
		if(c[i++] == '=')
			padding += 1;
	}

	byte* p = (byte*)malloc((length*3/4-padding) * sizeof(byte) + 1);

	byte m2 = 0x03, m4 = 0x0F;
	int j = 0;
	for(i = 0; i < length; i += 4){
		if(i + 4 >= length){
			p[j++] = (indexof(c[i]) << 2) ^ ((indexof(c[i+1]) >> 4) & m2);
			if(padding == 1)
				p[j++] = ((indexof(c[i+1]) & m4) << 4) ^ ((indexof(c[i+2]) >> 2) & m4);
		}
		else{
			p[j++] = (indexof(c[i]) << 2) ^ ((indexof(c[i+1]) >> 4) & m2);
			p[j++] = ((indexof(c[i+1]) & m4) << 4) ^ ((indexof(c[i+2]) >> 2) & m4);
			p[j++] = ((indexof(c[i+2]) & m2) << 6) ^ indexof(c[i+3]);
		}
	}

	p[j] = '\0';
	return p;
}

/*
int main(){
	//byte* plain = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
	//byte* cipher = encode(plain);
	
	byte* cipher = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
	byte* plain = decode(cipher);
	
	printf(plain);

	getbyte();
	return 0;
}
*/