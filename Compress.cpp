/*
  压缩模块：
  1. 先计算文件字节数
  2. 根据字节数生成huffmanTree
  3. 根据huffmantree生成HuffmanCode
  4. 根据huffmancode来写文件(压缩文件)
*/
bool CountByte(const char *file, int *weightarray, int arraysize)
{
	int i;
	for(i=0; i<arraysize; i++)
	{
		weightarray[i] = 0;
	}
	FILE *fp;
	fp = fopen(file, "rb");
	if(fp!=NULL)
	{
		int ch;
		ch = fgetc(fp);
		while(!feof(fp))
		{
			weightarray[ch+128]++;
			ch = fgetc(fp);
		}

		fclose(fp);
		return true;
	}
	else
	{
		return false;
	}
}
bool WriteCompressFile(HuffmanCode *_code, const char *file, const char *dust)  	// 根据哈夫曼编码写压缩文件
{
	long long fileBit;
	FILE *fp = NULL;
	FILE *_dust = NULL;
	FILE *length = NULL;
	fileBit = 0;				// 统计位数，去掉最后的补位
	int pos = 0;
	char str = 0;				// 八位标志
	fp = fopen(file, "rb");
	length = fopen("length.log","a+");
	_dust = fopen(dust,"wb");
	if(fp==NULL || length == NULL || _dust==NULL )
	{
		return false;
	}

	if(fp!=NULL)
	{
		int ch;
		ch = fgetc(fp);		// 取字节数据

		int k=0;

		while(!feof(fp))
		{

			int strlenth = strlen(_code[ch+128]);	// 根据字节取编码的长度
			HuffmanCode code = _code[ch+128]; 		// 根据字节取编码
			// printf("第%d个字节：编码%s 编码长度:%d\n", j, _code[ch+128],strlen(_code[ch+128]));
			// 初始化填充字节位
			int i;
			for(i=0; i<strlenth; i++)
			{
				str <<= 1;			// 左移一位
				str |= (code[i] - '0');		// 填位
				fileBit++;			// 字节累加
				pos++;
				if(pos==8)      // 8bit write to file
				{
					k++;
					fputc(str,_dust);
					// printf("%d\n",str);
					pos = 0;
					str = 0;
				}
			}
			ch = fgetc(fp);
		}
		if(pos!=0)  		// 不够8位，补位
		{
			int t = 8 - pos;
			str <<= t;			// 补位
			fputc(str,_dust);
			k++;

		}
		fclose(fp);
		fclose(_dust);
		long long tmp;
		int filelength = 0;
		char path[256];
		int flags=0;

		while(!feof(length))
		{

			fscanf(length,"%s %ld\n",path, &tmp);
			if(!strcmp(path,dust))
			{
				fclose(length);
				length = fopen("length.log","w+");
				fseek(length, (long)filelength, SEEK_CUR);
				flags=1;
				break;
			}
			filelength = ftell(length);
		}
		if(flags==0 || filelength==0)
		{
			fprintf(length,"%s %ld\n", dust, fileBit);
		}
		else
		{
			fprintf(length,"\n%s %ld\n", dust, fileBit);

		}

		fclose(length);
		// printf("共写了:%d次八位\n",k);
		return true;
	}
}
