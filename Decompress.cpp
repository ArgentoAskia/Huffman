bool WriteDecompressFile(PHuffmanTree HT, const char *Compressfile, const char *dust)
{
	FILE *fp = NULL;
	FILE *_dust = NULL;
	int filebit = 0;
	char filename[256];
	FILE *length = NULL;
	int flag=0;
	length = fopen("length.log","a+");
	flag = fscanf(length,"%s %ld",filename, &filebit);

	_dust = fopen(dust, "wb");
	fp = fopen(Compressfile, "rb");
	while(flag!=-1)
	{
		if(strcmp(filename, Compressfile))
		{
			flag = fscanf(length,"%s %ld",filename, &filebit);
		}
		else
			break;
	}
	if(flag==-1)
	{
		printf("Can't not find the compress file\n");
		fclose(length);
		fclose(fp);
		fclose(_dust);
		return false;
	}
	fclose(length);
#       ifdef _DEBUG_
	printf("now compress file name is: %s, byte is: %d\n", filename, filebit);
#       endif
	PHuffmanNode traveler = HT;
	if(fp!=NULL)
	{
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
				if(i == 0)
				{
					traveler = traveler->lchild;
					if(IsLeaves(traveler))   // Pop
					{
						fputc(traveler->byte,_dust);
						traveler = HT;
					}
				}
				else if(i == 1)
				{
					traveler = traveler->rchild;
					if(IsLeaves(traveler))   // Pop
					{
						fputc(traveler->byte,_dust);
						traveler = HT;
					}
				}
				filebit--;
				if(filebit==0)
				{
					return true;
				}
				count--;
			}
			ch = fgetc(fp);
		}
	}
	fclose(fp);
	fclose(_dust);
}
bool CreateHTWithKey(const char *keyfile, PHuffmanTree &HT)
{
	FILE *fp = NULL;
	fp = fopen(keyfile, "r");
	if(fp==NULL)
	{
#       ifdef _DEBUG_
		printf("In function CreateHTWithKey：can't not open file: %s", keyfile);
#       endif
		return false;
	}

	char ch;
	char str[50];
	int count;

	// 新建一颗空树
	HT = (PHuffmanTree) malloc(sizeof(HuffmanTree));
	PHuffmanNode traveler = HT;
	HT->lchild = NULL;
	HT->rchild = NULL;

	PHuffmanNode NewNode;

	int i;

	// 先读入一个字符串，根据字符串遍历树来创建树
	// 判断是不是叶子，只要判断字符的下一位是不是'\0'即可
	// 官方BUG：切记先读字符再判断feof()，并且不能用fseek()！！！
	fscanf(fp, "%d %s\n", &ch, str);
	while(!feof(fp))
	{
		i = 0;
		while(str[i]!='\0')
		{
			if(str[i+1]!='\0')
			{
				if(str[i]=='0')
				{
					if(traveler->lchild!=NULL)
					{
						traveler = traveler->lchild;
					}
					else
					{
						NewNode = (PHuffmanNode) malloc(sizeof(HuffmanNode));
						NewNode->lchild = NULL;
						NewNode->rchild = NULL;
						traveler->lchild = NewNode;
						traveler = traveler->lchild;
					}
				}
				else if(str[i]=='1')
				{
					if(traveler->rchild!=NULL)
					{
						traveler = traveler->rchild;
					}
					else
					{
						NewNode= (PHuffmanNode) malloc(sizeof(HuffmanNode));
						NewNode->lchild = NULL;
						NewNode->rchild = NULL;
						traveler->rchild = NewNode;
						traveler = traveler->rchild;
					}
				}
			}
			else if(str[i+1]=='\0')
			{
				if(str[i]=='0')
				{
					NewNode = (PHuffmanNode) malloc(sizeof(HuffmanNode));
					NewNode->lchild = NULL;
					NewNode->rchild = NULL;
					NewNode->byte = ch;
					traveler->lchild = NewNode;
				}
				else
				{
					NewNode = (PHuffmanNode) malloc(sizeof(HuffmanNode));
					NewNode->lchild = NULL;
					NewNode->rchild = NULL;
					NewNode->byte = ch;
					traveler->rchild = NewNode;
				}
			}
			i++;
		}
		traveler = HT;
#           ifdef _DEBUG_
		int flag;
		flag = fscanf(fp, "%d %s", &ch, str);
		if(flag==-1&&!feof(fp))
			printf("In function CreateHTWithKey：can't not read ch and str\n");
#           else
		fscanf(fp, "%d %s", &ch, str);
#           endif
	}
	fclose(fp);
	return true;
}



