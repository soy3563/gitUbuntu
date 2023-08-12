#include <stdio.h>

//비트맵 헤더를 한 묶음으로 다시 구조체로 묶었어요. 함수처리를 편하게 하려구요.
typedef struct tagBITMAPHEADER {
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	RGBQUAD hRGB[256];
}BITMAPHEADER;

int main() {

	BITMAPHEADER originalHeader;	//비트맵의 헤더부분을 파일에서 읽어 저장할 구조체
	BITMAPHEADER outputHeader;	//변형을 가한 헤더부분을 저장할 구조체
	int imgSize;			//이미지의 크기를 저장할 변수
	BYTE* image = LoadBitmapFile(&originalHeader,&imgSize, "lenna.bmp"); //비트맵파일을 읽어 화소정보를 저장
	if (image == NULL) return 0;        //파일 읽기에 실패하면 프로그램 종료
	BYTE* output = (BYTE*)malloc(sizeof(BYTE) * imgSize);	//결과값을 저장할 포인터 선언 및 메모리 할당
	outputHeader = originalHeader;				//헤더정보를 출력헤더정보에 할당

	/*요기에다가 영상을 처리할 코드가 들어가면 됩니다.*/
       //여기부터 밝기를 50만큼 증가시킨 파일 생성
	ChangeRGB(originalHeader.hRGB,outputHeader.hRGB, 50, 50, 50);
	WriteBitmapFile(outputHeader, output, imgSize, "output1.bmp");

	//여기부터 밝기를 50만큼 감소시킨 파일 생성
	ChangeRGB(originalHeader.hRGB, outputHeader.hRGB, -50, -50, -50);
	WriteBitmapFile(outputHeader, output, imgSize, "output2.bmp");
	//화소정보 복사
	for (int i = 0; i < imgSize; i++)
	{
		output[i] = image[i];
	}

	free(image);
	free(output);

	return 0;
}


BYTE* LoadBitmapFile(BITMAPHEADER* bitmapHeader, int* imgSize, char* filename)
{
	FILE* fp = fopen(filename, "rb");	//파일을 이진읽기모드로 열기
	if (fp == NULL)
	{
		printf("파일로딩에 실패했습니다.\n");	//fopen에 실패하면 NULL값을 리턴
		return NULL;
	}
	else
	{
		fread(&bitmapHeader->bf, sizeof(BITMAPFILEHEADER), 1, fp);	//비트맵파일헤더 읽기
		fread(&bitmapHeader->bi, sizeof(BITMAPINFOHEADER), 1, fp);	//비트맵인포헤더 읽기
		fread(&bitmapHeader->hRGB, sizeof(RGBQUAD), 256, fp);	//색상팔렛트 읽기

		int imgSizeTemp = bitmapHeader->bi.biWidth * bitmapHeader->bi.biHeight;	//이미지 사이즈 계산
		*imgSize = imgSizeTemp;	// 이미지 사이즈를 상위 변수에 할당

		BYTE* image = (BYTE*)malloc(sizeof(BYTE) * imgSizeTemp);	//이미지크기만큼 메모리할당
		fread(image, sizeof(BYTE), imgSizeTemp, fp);//이미지 크기만큼 파일에서 읽어오기
		fclose(fp);
		return image;
	}

}

void WriteBitmapFile(BITMAPHEADER outputHeader, BYTE* output, int imgSize, char* filename)
{
	FILE* fp = fopen(filename, "wb");//파일을 이진쓰기모드로 열기

	fwrite(&outputHeader.bf, sizeof(BITMAPFILEHEADER), 1, fp);//비트맵파일헤더쓰기
	fwrite(&outputHeader.bi, sizeof(BITMAPINFOHEADER), 1, fp);//비트맵인포헤더쓰기
	fwrite(&outputHeader.hRGB, sizeof(RGBQUAD), 256, fp);//색상팔렛트 쓰기
	fwrite(output, sizeof(BYTE), imgSize, fp);//이미지인덱스정보 쓰기
	fclose(fp);
}

void ChangeRGB(RGBQUAD* originalhRGB, RGBQUAD* outputhRGB, int maniplRed, int maniplBlue, int maniplGreen)
{
	//클리핑 처리후 outputhRGB에 그 값을 할당
	for (int i = 0; i < 256; i++)
	{
		if (originalhRGB[i].rgbRed + maniplRed > 255)//만약 255보다 크면
			outputhRGB[i].rgbRed = 255;//255할당
		else if (originalhRGB[i].rgbRed + maniplRed < 0)//만약 0보다 작으면
			outputhRGB[i].rgbRed = 0;//0할당
		else    //0~255범위 안에 있으면 그 값을 그냥 할당
			outputhRGB[i].rgbRed = originalhRGB[i].rgbRed + maniplRed;

		if (originalhRGB[i].rgbBlue + maniplBlue > 255)
			outputhRGB[i].rgbBlue = 255;
		else if (originalhRGB[i].rgbBlue + maniplBlue < 0)
			outputhRGB[i].rgbBlue = 0;
		else
			outputhRGB[i].rgbBlue = originalhRGB[i].rgbBlue + maniplBlue;

		if (originalhRGB[i].rgbGreen + maniplGreen > 255)
			outputhRGB[i].rgbGreen = 255;
		else if (originalhRGB[i].rgbGreen + maniplGreen < 0)
			outputhRGB[i].rgbGreen = 0;
		else
			outputhRGB[i].rgbGreen = originalhRGB[i].rgbGreen + maniplGreen;
	}

}

//https://m.blog.naver.com/liveforu/221935778106