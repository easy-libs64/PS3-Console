#include "ttf_render.h"
#include "printF.h"


#define MaxLineCount 10
#define MaxLineLen 41
#define HFONT 24
#define WFONT 20
#define XSTART 100
#define YSTART 100
#define YOFFSET 6

#define WHITE (255 << 24) | (255 << 16) | (255 << 8) | 255
#define BLACK 0

#define MAX_INT_CHAR_LEN 12

static u16 activeLine = 0;

typedef struct {
	u16 lineX;
	u16 lineY;
	char* text;
} Line;

static Line lineBuffer[MaxLineCount];

static void inc_activeLine(){
	++activeLine;
	if(activeLine >= MaxLineCount){
		activeLine = 0;
	}
}
///Check for memory leaks!!!

void Console_INIT()
{
	TTFUnloadFont();
	TTFLoadFont(0,"/dev_flash/data/font/SCE-PS3-SR-R-LATIN2.TTF", NULL, 0);
	for(u16 i = 0; i<MaxLineCount; ++i){
		Line line;
		line.lineX = XSTART;
		line.lineY = YSTART + (HFONT + YOFFSET) * i;
		line.text = (char*)malloc(MaxLineLen);
		lineBuffer[i] = line;
	}
}



void Console_print(const char* msg)
{
	strncpy(lineBuffer[activeLine].text, msg, MaxLineLen);
	inc_activeLine();
}
void Console_printInt(const char* msg, u32 msgSize, u32 num)
{
	char str[msgSize + MAX_INT_CHAR_LEN];
	strcpy(str, msg);
	
	u32 i = msgSize; // at 0-terminal
	
	if(!num) {str[i] = '0'; ++i;}
	while (num){
		str[i] = '0' + num%10;
		num/=10;
		++i;
	}
	str[i] = 0;
	char *st = str + msgSize;
	char *en = str + (i-1);
	
	while(en >= st){
		char t = *en;
		*en = *st;
		*st = t;
		++st;
		--en;
	}
	
	print(str);
}

void Console_SHOW()
{
	//reset_ttf_frame();
	for(u16 i = 0; i<MaxLineCount; ++i){
		Line cur = lineBuffer[i];
		display_ttf_string(cur.lineX, cur.lineY, cur.text, WHITE, BLACK, WFONT, HFONT);
	}
}

void Console_DeINIT()
{
	for(u16 i = 0; i<MaxLineCount; ++i){
		free(lineBuffer[i].text);
	}
}

