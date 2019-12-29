/*
  ѹ��ģ�飺
  1. �ȼ����ļ��ֽ���
  2. �����ֽ�������huffmanTree
  3. ����huffmantree����HuffmanCode
  4. ����huffmancode��д�ļ�(ѹ���ļ�)
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
bool WriteCompressFile(HuffmanCode *_code, const char *file, const char *dust)  	// ���ݹ���������дѹ���ļ�
{
	long long fileBit;
	FILE *fp = NULL;
	FILE *_dust = NULL;
	FILE *length = NULL;
	fileBit = 0;				// ͳ��λ����ȥ�����Ĳ�λ
	int pos = 0;
	char str = 0;				// ��λ��־
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
		ch = fgetc(fp);		// ȡ�ֽ�����

		int k=0;

		while(!feof(fp))
		{

			int strlenth = strlen(_code[ch+128]);	// �����ֽ�ȡ����ĳ���
			HuffmanCode code = _code[ch+128]; 		// �����ֽ�ȡ����
			// printf("��%d���ֽڣ�����%s ���볤��:%d\n", j, _code[ch+128],strlen(_code[ch+128]));
			// ��ʼ������ֽ�λ
			int i;
			for(i=0; i<strlenth; i++)
			{
				str <<= 1;			// ����һλ
				str |= (code[i] - '0');		// ��λ
				fileBit++;			// �ֽ��ۼ�
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
		if(pos!=0)  		// ����8λ����λ
		{
			int t = 8 - pos;
			str <<= t;			// ��λ
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
		// printf("��д��:%d�ΰ�λ\n",k);
		return true;
	}
}
