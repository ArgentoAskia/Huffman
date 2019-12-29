#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct HuffmanNode;
typedef struct HuffmanNode HuffmanTree, *PHuffmanTree;
typedef char *HuffmanCode;

PHuffmanTree CreateHuffmanTree(int *WeightArray, int Arrayzise);
bool CreateHuffmanCode(PHuffmanTree HT, const char *keyfile, HuffmanCode *&_code, int Arrayzise);
bool CountByte(const char *file, int *weightarray, int arraysize);
bool WriteCompressFile(HuffmanCode *_code, const char *file, const char *dust);
void DeleteHuffmanTree(PHuffmanTree &HT);
void DeleteHuffmanCode(HuffmanCode *&_code, int Arraysize);

bool WriteDecompressFile(PHuffmanTree HT, const char *Compressfile, const char *dust);
bool CreateHTWithKey(const char *keyfile, PHuffmanTree &HT);

bool HaveRenameFile(const char *file);

#include "HuffmanTree.cpp"
#include "Decompress.cpp"
#include "Compress.cpp"
#include "SE.cpp"
/*
  	 Compressfile == 加压完成后加压文件所在位置
         keyfile == 秘钥文件
	 dust == 生成的目标文件所在位置
	 file ==要加压的文件所在位置
*/
#ifdef _DEBUG_
bool DecompressBinaryFile(const char *Compressfile, const char *keyfile, const char *dust, const char *file)
#else
bool DecompressBinaryFile(const char *Compressfile, const char *keyfile, const char *dust)	// 解压函数
#endif
{
	PHuffmanTree HT;
# ifdef _DEBUG_
	SetDebugMode(Compressfile,0);
# endif
	if(CreateHTWithKey(keyfile, HT))
	{
# ifdef _DEBUG_
		Debug_HuffmanTree(HT);
# endif
		if(WriteDecompressFile(HT, Compressfile, dust))
		{
			DeleteHuffmanTree(HT);
# ifdef _DEBUG_
  	       	TestFile(file,dust);
			EndDebugMode();
# endif
			return true;
		}
		else
		{
# ifdef _DEBUG_

			EndDebugMode();
# endif
			return false;
		}
	}
	else
	{
# ifdef _DEBUG_
		EndDebugMode();
# endif
		return false;
	}
}
bool CompressBinaryFile(const char *file, const char *Keyfile, const char *dust)		// 加压函数
{
	int Weightarray[256];
	PHuffmanTree Tree;
	HuffmanCode *code;
# ifdef _DEBUG_
	SetDebugMode(file,1);
# endif
	if(CountByte(file, Weightarray, 256))
	{
# ifdef _DEBUG_
		Debug_ArrayCount(Weightarray, 256, file);
# endif

		Tree = CreateHuffmanTree(Weightarray, 256);
# ifdef _DEBUG_
		Debug_HuffmanTree(Tree);
# endif

		if(Tree!=NULL)
		{
			CreateHuffmanCode(Tree, Keyfile, code, 256);
# ifdef _DEBUG_
			Debug_HuffmanCode(code, 256);
# endif
			WriteCompressFile(code, file, dust);
			DeleteHuffmanTree(Tree);
			DeleteHuffmanCode(code, 256);
		}
		else
		{
			printf("Create HuffmanTree fail\n");
# ifdef _DEBUG_
			EndDebugMode();
# endif
			return false;
		}
	}
	else
	{
		printf("can't not Count byte of file, please set _DEBUG_ mode\n");
# ifdef _DEBUG_
		EndDebugMode();
# endif
		return false;
	}
# ifdef _DEBUG_
	EndDebugMode();
# endif
	return true;
}


