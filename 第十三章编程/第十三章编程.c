#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* s_gets(char* st, int n);//1
void one(void);//1
void two(char* file1, char* file2);//
void five_review(char* ch, char* file);//five_review
void three(void);//3

int main(int argc,char* argv[])
{
	//one();
	//two(argv[1], argv[2]);
	//five_review(argv[1], argv[2]);
	three();
	return 0;
}

void one(void)
{
	char ch;
	FILE* fp;
	char name[40];
	unsigned long count = 0;
	printf("请输入打开文件名称");
	scanf("%s", name);
	//s_gets(name, 40);
	if ((fp = fopen(name, "r")) == NULL)
	{
		printf("%s文件打开失败", name);
		exit(EXIT_FAILURE);
	}
	while((ch = getc(fp)) != EOF)
	{
		putc(ch, stdout);
		count++;
	}
	fclose(fp);
	printf("%s有%lu个字符", name, count);
}

//2****************************************************************************************
void two(char *file1,char* file2)
{
	size_t bytes;
	FILE* ptr1; FILE* ptr2;
	char temp[4096];
	if((ptr1 = fopen(file1, "rb"))==NULL)
	{
		fprintf(stderr, "无法打开文件%s", file1);
		exit(EXIT_FAILURE);
	}
	if(setvbuf(ptr1,NULL,_IOFBF,4096)!=0)
	{
		fputs("file1申请缓冲失败", stderr);
		exit(EXIT_FAILURE);
	}
	if (strcmp(file1, file2) == 0)
	{
		fputs("无法对相同文件进行操作",stderr);
	}
	if ((ptr2 = fopen(file2, "wb")) == NULL)
	{
		fprintf(stderr, "打开文件%s失败", file2);
		exit(EXIT_FAILURE);
	}
	if (setvbuf(ptr2, NULL, _IOFBF, 4096)!=0)
	{
		fputs("file2申请缓冲失败", stderr);
		exit(EXIT_FAILURE);
	}
	while((bytes = fread(temp, sizeof(char), 4096, ptr1)) > 0)
		fwrite(temp, sizeof(char), bytes, ptr2);
	if(ferror(ptr1)!=0)
		fputs("file读取失败", stderr);
	if (ferror(ptr2) != 0)
		fputs("file输入失败", stderr);
	fclose(ptr1);
	fclose(ptr2);
}

//复习题5*************************************************************************************
void five_review(char *ch,char* file)
{
	char line[256];
	FILE* ptr1;
	if ((ptr1 = fopen(file, "r")) == NULL)
	{
		fprintf(stderr, "failed to open,\"%s\"", file);
		exit(EXIT_FAILURE);
	}
	
	while ((fgets(line, 256, ptr1)) != NULL)
	{
		if (strchr(line, *ch) != NULL)
			puts(line);
	}
}

//3*************************************************************************
void three(void)

{
	size_t bytes;
	FILE* ptr; 
	char name[40];
	char copy[256];
	printf("输入文件名");
	//s_gets(name, 40);
	//fgets(name, 40, stdin);
	scanf("%s", name);
	if ((ptr = fopen(name, "r+")) == NULL)
	{
		fprintf(stderr, "failed to open,%s", name);
		exit(EXIT_FAILURE);
	}
	setvbuf(ptr, NULL, _IOFBF, 256);
	while ((bytes = fread(copy,1, 256, ptr)) > 0)
	{
		char* s = copy;
		while (*s)
		{
			*s = toupper(*s);
			s++;
		}
		rewind(ptr);
		fwrite(copy, 1, bytes, ptr);
	}
	fclose(ptr);
}

//12************************************************************************************************
void twelve(void)
{

}

//*************************************************************************************************
char* s_gets(char* st, int n)
{
	char* ret_val;
	char* find;
	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '/n');
		if (find)
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}