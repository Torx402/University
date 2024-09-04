#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"

extern int32_t turtle(
	uint8_t *dest_bitmap,
	uint8_t *commands,
	size_t commands_size
);

uint8_t* create_bitmap(int w, int h);

char* default_tpl = "template.bmp";
char* default_bin = "program.bin";
char* default_bmp = "result.bmp";

int main(int argc, char** argv)
{
	FILE* hFile = NULL;
	char* path_tpl = default_tpl;
	char* path_bin = default_bin;
	char* path_bmp = default_bmp;
	
	if (argc == 4) {
		path_tpl = argv[1];
		path_bin = argv[2];
		path_bmp = argv[3];
	} 
	else if (argc != 1) {
		printf("Usage: %s [template.bmp] [program.bin] [result.bmp]\n");
		return 0;
	}
	
	uint8_t* bitmap = NULL;
	size_t bitmap_size = 0;	
	
	uint8_t* pixels = NULL;
			
	hFile = fopen(path_tpl, "rb");
	if (hFile != NULL) {
		fseek(hFile, 0, SEEK_END);
		bitmap_size = ftell(hFile);
		rewind(hFile);
		bitmap = (uint8_t*)malloc(bitmap_size);
		fread(bitmap, bitmap_size, 1, hFile);
		fclose(hFile);
		printf("Read template (%u bytes)\n", bitmap_size);
		
		size_t offset = (*(size_t*)(bitmap+0x0A));
		pixels = bitmap + offset + 2;
	} 
	else {
		printf("Error reading template\n");
	}
	
	uint8_t* commands = NULL;
	size_t commands_size = 0;
	
	hFile = fopen(path_bin, "rb");
	if (hFile != NULL) {
		fseek(hFile, 0, SEEK_END);
		commands_size = ftell(hFile);
		rewind(hFile);
		commands = (uint8_t*)malloc(commands_size);
		fread(commands, commands_size, 1, hFile);
		fclose(hFile);
		printf("Read program binary (%u bytes)\n", commands_size);
	} 
	else {
		printf("Error reading program binary\n");
	}
		
	printf("Executing program...\n");
	int32_t result = turtle(pixels, commands, commands_size);	
	switch (result)
	{
		case 0:
			printf("Done!\n");
			break;
		default:
			printf("Unknown error: %i\n", result);
			break;
	}
		
	hFile = fopen(path_bmp, "wb");
	if (hFile != NULL) {
		fwrite(bitmap, bitmap_size, 1, hFile);
		fclose(hFile);
		printf("Wrote result (%u bytes)\n", bitmap_size);
	} 
	else {
		printf("Error writing bitmap\n");
	}
	return 0;
}

void debug_pen(uint32_t pen)
{
	printf("[0] Pen: %u\n", pen);
}
void debug_mov(uint32_t mvamt)
{
	printf("[1] Move: %u\n", mvamt);
}
void debug_dir(int32_t dx, int32_t dy)
{
	printf("[2] Dir: DX=%i, DY=%i\n", dx, dy);
}
void debug_pos(uint32_t px, uint32_t py)
{
	printf("[3] Pos: PX=%u, PY=%u\n", px, py);
}
