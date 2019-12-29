#define _DEBUG_
#include "HuffmanCompressor.hpp"
#include "ExtraHuffmanCompressor.hpp"
int main() 
{
	printf("********** ���ڹ��������㷨���ļ�ѹ����ʾ **********\n");
	printf("Target: TestFile\\test.txt\n");
	printf("Size of File: %d\n",CountFileByte("TestFile\\ReserveMe.dat"));
	printf("Compressed target: TestFile\\CompressFile1.dat\n");
	printf("Compressing...\n");
	CompressBinaryFile("TestFile\\test.txt", "TestFile\\Key.key", "TestFile\\CompressFile1.dat");
	printf("Size of Compressed File: %d\n",CountFileByte("TestFile\\CompressFile1.dat"));
	// CompressBinaryFile(Ҫ��ѹ���ļ�, ��Կ�洢λ��, ��ѹ���ļ��洢λ��);
	printf("Decompressed target: TestFile\\DecompressFile2.dat\n");
	printf("Decompressing...\n");
	DecompressBinaryFile("TestFile\\CompressFile1.dat", "TestFile\\Key.key","TestFile\\DecompressFile2.dat","TestFile\\ReserveMe.dat");
	// DecompressBinaryFile(��ѹ�ļ�����λ��, ��Կ�洢λ��, ��ѹ�ļ����ļ��洢λ��);
	return 0;
}
