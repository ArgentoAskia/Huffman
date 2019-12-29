/*
	Name: Extra HuffmanCompressor Interface
	Copyright:
	Author:
	Date: 23/12/19 13:24
	Description:
*/
// debug console for HuffmanCompressor

bool PrintHuffmanCode(const char *keyfile)
{
	FILE *fp = NULL;
	fp = fopen(keyfile, "r");
	if(fp==NULL)
        return false;
	char code[50];
	int data;
	fscanf(fp,"%d %s\n", &data, code);
	while(!feof(fp))
	{
		printf("%d %s\n", data, code);
		fscanf(fp,"%d %s\n", &data, code);
	}
	return true;
}
int PrintCompressFileBit(const char *Compressfile)
{
	FILE *fp, *length;
	char filename[50];
	int fileBit;
	fp = fopen(Compressfile, "rb");
	length = fopen("length.log", "r");
	fscanf(length,"%s %ld\n",filename, &fileBit);
	while(!feof(length))
	{
		if(strcmp(filename, Compressfile))
		{
			fscanf(length,"%s %ld\n",filename, &fileBit);
		}
		else
			break;
	}
	if(feof(length))
	{
		return false;
	}
	int ch;
	ch = fgetc(fp);
	while(!feof(fp))
	{
		int count = 7;
		while(count>=0)
		{
			int i = ch;
			i>>=count;
			i &=1;
			printf("%d", i);
			fileBit--;
			if(fileBit==0)
			{
				putchar('\n');
				return true;
			}
			count--;
		}
		ch = fgetc(fp);
	}
	fclose(fp);
}
int CountFileByte(const char *Compressfile)
{
	FILE *fp;
	fp = fopen(Compressfile, "rb");
	char byte;
	int total=0;
	byte = fgetc(fp);
	while(!feof(fp))
	{
		total++;
		byte = fgetc(fp);
	}
	fclose(fp);
	return  total;

}



