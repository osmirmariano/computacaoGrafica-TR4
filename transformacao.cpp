//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.hpp>
#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

#include "transformacao.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton6Click(TObject *Sender)
{
	Form3->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton1Click(TObject *Sender)
{
	Image1->Picture->LoadFromFile("cg.bmp"); // Carregando imagem
	Image1->Stretch = true; //redimensiona
	Image1->Refresh(); //atualiza
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton2Click(TObject *Sender)
{
	float angle;
	float newx, newy, x, y;

	//encontrar a largura e a altura do retângulo delimitador que correspondem à largura e altura do bitmap de destino
	newx = x * cos(angle) - y * sin(angle);
	newy = y * cos(angle) + x * sin(angle);

	angle = Edit1->Text.ToDouble();
	Graphics::TBitmap *SrcBitmap=new Graphics::TBitmap;
	Graphics::TBitmap *DestBitmap=new Graphics::TBitmap;
	SrcBitmap->LoadFromFile("cg.bmp");

	//Converter graus para radianos
	float radians=(2*3.1416*angle)/360;

	float cosine=(float)cos(radians);
	float sine=(float)sin(radians);

	float Point1x=(-SrcBitmap->Height*sine);  //O ponto 1 é o ponto(0, bitmap->Width),
	float Point1y=(SrcBitmap->Height*cosine); //O ponto 1 é o ponto(0, bitmap->Width),
	float Point2x=(SrcBitmap->Width*cosine-SrcBitmap->Height*sine);  //o ponto 2 é o ponto(bitmap->Height, 0)
	float Point2y=(SrcBitmap->Height*cosine+SrcBitmap->Width*sine);  //o ponto 2 é o ponto(bitmap->Height, 0)
	float Point3x=(SrcBitmap->Width*cosine); //o ponto 3 é o ponto(bitmap->Width, bitmap->Height).
	float Point3y=(SrcBitmap->Width*sine);   //o ponto 3 é o ponto(bitmap->Width, bitmap->Height).

	float minx = min(0,min(Point1x,min(Point2x,Point3x)));
	float miny = min(0,min(Point1y,min(Point2y,Point3y)));
	float maxx = max(Point1x,max(Point2x,Point3x));
	float maxy = max(Point1y,max(Point2y,Point3y));


	int DestBitmapWidth=(int)ceil(fabs(maxx)-minx);
	int DestBitmapHeight=(int)ceil(fabs(maxy)-miny);

	DestBitmap->Height=DestBitmapHeight;
	DestBitmap->Width=DestBitmapWidth;

	//toma cada pixel no bitmap de destino e obtem seu valor no bitmap de origem usando as mesmas fórmulas
	for(int x=0;x<DestBitmapWidth;x++)
	{
	  for(int y=0;y<DestBitmapHeight;y++)
	  {
		int SrcBitmapx=(int)((x+minx)*cosine+(y+miny)*sine);
		int SrcBitmapy=(int)((y+miny)*cosine-(x+minx)*sine);
		if(SrcBitmapx >=0 && SrcBitmapx < SrcBitmap->Width && SrcBitmapy >=0 && SrcBitmapy < SrcBitmap->Height)
		{
		  DestBitmap->Canvas->Pixels[x][y]= SrcBitmap->Canvas->Pixels[SrcBitmapx][SrcBitmapy];
		}
	  }
	}
	//Mostrar o bitmap girado
	Image1->Picture->Bitmap=DestBitmap;
	delete DestBitmap;
	delete SrcBitmap;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton3Click(TObject *Sender)
{
	double fator1, fator2;
	int SrcBitmapx;
	int SrcBitmapy;

	Graphics::TBitmap *SrcBitmap = new Graphics::TBitmap;
	Graphics::TBitmap *DestBitmap = new Graphics::TBitmap;
	SrcBitmap->LoadFromFile("cg.bmp");

	fator1 = Edit2->Text.ToDouble();
	fator2 = Edit3->Text.ToDouble();

	//toma cada pixel no bitmap de destino e obtem seu valor no bitmap de origem usando as mesmas fórmulas
	for(int x = 0; x < IntToStr(Image1->Width); x++)
	{
	  for(int y = 0; y < IntToStr(Image1->Height); y++)
	  {
			SrcBitmapx=(int)(fator1*x);
			SrcBitmapy=(int)(fator2*y);
			DestBitmap->Canvas->Pixels[SrcBitmapx][SrcBitmapx] = SrcBitmap->Canvas->Pixels[SrcBitmapx][SrcBitmapy];
		//ShowMessage(DestBitmap->Canvas->Pixels[x][y]);
	  }
	}
	ShowMessage(SrcBitmapx);
	//Mostrar o bitmap escalonado
	Image1->Picture->Bitmap = DestBitmap;
	delete DestBitmap;
	delete SrcBitmap;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton5Click(TObject *Sender)
{
	   ShowMessage("TRANSLAÇÃO");
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton4Click(TObject *Sender)
{
	 ShowMessage("REFLEXÃO");
}
//---------------------------------------------------------------------------
