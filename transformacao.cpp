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
	Form3->Color = clWhite;
	ComboBox1->Items->Add("VERTICAL");
	ComboBox1->Items->Add("HORIZONTAL");
	ComboBox1->Enabled = false;
	SpeedButton2->Enabled = false;
	SpeedButton3->Enabled = false;

	SpeedButton5->Enabled = false;
	SpeedButton8->Enabled = false;
	SpeedButton9->Enabled = false;
	Edit1->Enabled = false;
	Edit2->Enabled = false;
	Edit3->Enabled = false;
	Edit4->Enabled = false;
	Edit5->Enabled = false;
	Edit6->Enabled = false;
	Edit7->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton1Click(TObject *Sender)
{
	Image1->Picture->LoadFromFile("cg.bmp"); // Carregando imagem
	Image1->Stretch = true; //redimensiona
	Image1->Refresh(); //atualiza
	SpeedButton2->Enabled = true;
	SpeedButton3->Enabled = true;
	SpeedButton5->Enabled = true;
	SpeedButton8->Enabled = true;
	SpeedButton9->Enabled = true;
	Edit1->Enabled = true;
	Edit2->Enabled = true;
	Edit3->Enabled = true;
	Edit4->Enabled = true;
	Edit5->Enabled = true;
	Edit6->Enabled = true;
	Edit7->Enabled = true;
	ComboBox1->Enabled = true;

}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton6Click(TObject *Sender)
{
	Form3->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton2Click(TObject *Sender)
{
	float angle;
	float newx, newy, x, y;

	//encontrar a largura e a altura do ret�ngulo delimitador que correspondem � largura e altura
	//do bitmap de destino
	newx = x * cos(angle) - y * sin(angle);
	newy = y * cos(angle) + x * sin(angle);

	angle = Edit1->Text.ToDouble();

	Graphics::TBitmap *rota=new Graphics::TBitmap;
	Graphics::TBitmap *recebe=new Graphics::TBitmap;
	rota->LoadFromFile("cg.bmp");

	//Converter graus para radianos
	float radians=(2*3.1416*angle)/360;

	float cosine=(float)cos(radians);
	float sine=(float)sin(radians);
	//Defini��es do pontos corresponde ao ret�ngulo da imagem, que s�o 4 pontos, por�m o primeiro � (0,0)
	float Point1x=(-rota->Height*sine);
	float Point1y=(rota->Height*cosine);
	float Point2x=(rota->Width*cosine-rota->Height*sine);
	float Point2y=(rota->Height*cosine+rota->Width*sine);
	float Point3x=(rota->Width*cosine);
	float Point3y=(rota->Width*sine);

	//Definindo o tamanho m�ximo e m�nimo
	float minx = min(0,min(Point1x,min(Point2x,Point3x)));
	float miny = min(0,min(Point1y,min(Point2y,Point3y)));
	float maxx = max(Point1x,max(Point2x,Point3x));
	float maxy = max(Point1y,max(Point2y,Point3y));


	int valorWidth=(int)ceil(fabs(maxx)-minx);
	int valorpHeight=(int)ceil(fabs(maxy)-miny);

	recebe->Height = valorpHeight;
	recebe->Width = valorWidth;

	//toma cada pixel no bitmap de destino e obtem seu valor no bitmap de origem usando as mesmas f�rmulas
	for(int x=0; x < valorWidth; x++)
	{
	  for(int y=0; y < valorpHeight; y++)
	  {
		int rx=(int)((x+minx)*cosine+(y+miny)*sine);
		int ry=(int)((y+miny)*cosine-(x+minx)*sine);
		if(rx >= 0 && rx < rota->Width && ry >= 0 && ry < rota->Height)
		{
		  recebe->Canvas->Pixels[x][y]= rota->Canvas->Pixels[rx][ry];
		}
	  }
	}
	//Mostrar o bitmap girado
	Image1->Picture->Bitmap=recebe;
	delete recebe;
	delete rota;
	Edit1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::SpeedButton3Click(TObject *Sender)
{
	double fator1, fator2;
	fator1 = Edit2->Text.ToDouble();
	fator2 = Edit3->Text.ToDouble();

	Graphics::TBitmap *SrcBitmap = new Graphics::TBitmap;
	Graphics::TBitmap *DestBitmap = new Graphics::TBitmap;
	SrcBitmap->LoadFromFile("cg.bmp");


	float Point1x=(SrcBitmap->Width);
	float Point1y=(SrcBitmap->Height);
	float Point2x=(SrcBitmap->Width);
	float Point2y=(SrcBitmap->Height);
	float Point3x=(SrcBitmap->Width);
	float Point3y=(SrcBitmap->Height);

	float minx = min(0,min(Point1x,min(Point2x,Point3x)));
	float miny = min(0,min(Point1y,min(Point2y,Point3y)));
	float maxx = max(Point1x,max(Point2x,Point3x));
	float maxy = max(Point1y,max(Point2y,Point3y));

	int DestBitmapWidth=(int)ceil(fabs(maxx)-minx);
	int DestBitmapHeight=(int)ceil(fabs(maxy)-miny);

	DestBitmap->Height=DestBitmapHeight;
	DestBitmap->Width=DestBitmapWidth;

	for(int x=0; x < DestBitmap->Width; x++)
	{
	  for(int y=0;y<DestBitmap->Height;y++)
	  {
		double fx = (fator1*x);
		double	fy = (fator2*y);
		if(fx >= 0 && fx < SrcBitmap->Width && fy >= 0 && fy < SrcBitmap->Height)
		{
			DestBitmap->Canvas->Pixels[x][y]= SrcBitmap->Canvas->Pixels[(int)fx][(int)fy];
		}
	  }
	}
	//Mostrar o bitmap girado

	Image1->Picture->Bitmap=DestBitmap;
	delete DestBitmap;
	delete SrcBitmap;
	Edit2->Clear();
	Edit3->Clear();
	//***********************************************************************
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton5Click(TObject *Sender)
{
	double tx, ty;
	int fx;
	int fy;
	tx = Edit4->Text.ToDouble();
	ty = Edit5->Text.ToDouble();


	Graphics::TBitmap *SrcBitmap=new Graphics::TBitmap;
	Graphics::TBitmap *DestBitmap=new Graphics::TBitmap;
	SrcBitmap->LoadFromFile("cg.bmp");

	float Point1x=(Image1->Width+tx);
	float Point1y=(Image1->Height+ty);
	float Point2x=(Image1->Width+tx);
	float Point2y=(Image1->Height+ty);
	float Point3x=(Image1->Width+tx);
	float Point3y=(Image1->Height+ty);

	float minx = min(0,min(Point1x,min(Point2x,Point3x)));
	float miny = min(0,min(Point1y,min(Point2y,Point3y)));
	float maxx = max(Point1x,max(Point2x,Point3x));
	float maxy = max(Point1y,max(Point2y,Point3y));

	int DestBitmapWidth=(int)ceil(fabs(maxx)-minx);
	int DestBitmapHeight=(int)ceil(fabs(maxy)-miny);

	DestBitmap->Height=DestBitmapHeight;
	DestBitmap->Width=DestBitmapWidth;

	for(int x=0;x<DestBitmapWidth;x++)
	{
	  for(int y=0;y<DestBitmapHeight;y++)
	  {
		fx = (int)(tx+x);
		fy = (int)(ty+y);

		if(fx >= 0 && fx < SrcBitmap->Width && fy >= 0 && fy < SrcBitmap->Height)
		{
		  DestBitmap->Canvas->Pixels[x][y]= SrcBitmap->Canvas->Pixels[fx][fy];
		}
	  }
	}
	//Mostrar o bitmap transladado */
	Image1->Picture->Bitmap=DestBitmap;
	delete DestBitmap;
	delete SrcBitmap;
	Edit4->Clear();
	Edit5->Clear();
}
//---------------------------------------------------------------------------



void __fastcall TForm3::SpeedButton8Click(TObject *Sender)
{
	double fDes;
	fDes = Edit6->Text.ToDouble();
	int fx, fy;
	Graphics::TBitmap *SrcBitmap=new Graphics::TBitmap;
	Graphics::TBitmap *DestBitmap=new Graphics::TBitmap;
	SrcBitmap->LoadFromFile("cg.bmp");

	float Point1x=(Image1->Width+fDes);
	float Point1y=(Image1->Height);
	float Point2x=(Image1->Width+fDes);
	float Point2y=(Image1->Height);
	float Point3x=(Image1->Width+fDes);
	float Point3y=(Image1->Height);

	float minx = min(0,min(Point1x,min(Point2x,Point3x)));
	float miny = min(0,min(Point1y,min(Point2y,Point3y)));
	float maxx = max(Point1x,max(Point2x,Point3x));
	float maxy = max(Point1y,max(Point2y,Point3y));

	int DestBitmapWidth=(int)ceil(fabs(maxx)-minx);
	int DestBitmapHeight=(int)ceil(fabs(maxy)-miny);

	DestBitmap->Height=DestBitmapHeight;
	DestBitmap->Width=DestBitmapWidth;

	for(int x=0;x<DestBitmapWidth;x++)
	{
	  for(int y=0;y<DestBitmapHeight;y++)
	  {
		fx = (int)(x+fDes*y);
		fy = (int)(y);

		if(fx >= 0 && fx < SrcBitmap->Width && fy >= 0 && fy < SrcBitmap->Height)
		{
		  DestBitmap->Canvas->Pixels[x][y]= SrcBitmap->Canvas->Pixels[fx][fy];
		}
	  }
	}
	//Mostrar o bitmap girado
	Image1->Picture->Bitmap=DestBitmap;
	delete DestBitmap;
	delete SrcBitmap;
	Edit6->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::SpeedButton9Click(TObject *Sender)
{
	double fDes;
	fDes = Edit7->Text.ToDouble();
	int fx, fy;
	Graphics::TBitmap *SrcBitmap=new Graphics::TBitmap;
	Graphics::TBitmap *DestBitmap=new Graphics::TBitmap;
	SrcBitmap->LoadFromFile("cg.bmp");

	float Point1x=(Image1->Width+fDes);
	float Point1y=(Image1->Height);
	float Point2x=(Image1->Width+fDes);
	float Point2y=(Image1->Height);
	float Point3x=(Image1->Width+fDes);
	float Point3y=(Image1->Height);

	float minx = min(0,min(Point1x,min(Point2x,Point3x)));
	float miny = min(0,min(Point1y,min(Point2y,Point3y)));
	float maxx = max(Point1x,max(Point2x,Point3x));
	float maxy = max(Point1y,max(Point2y,Point3y));

	int DestBitmapWidth=(int)ceil(fabs(maxx)-minx);
	int DestBitmapHeight=(int)ceil(fabs(maxy)-miny);

	DestBitmap->Height=DestBitmapHeight;
	DestBitmap->Width=DestBitmapWidth;

	for(int x=0;x<DestBitmapWidth;x++)
	{
	  for(int y=0;y<DestBitmapHeight;y++)
	  {
		fx = (int)(x);
		fy = (int)(y+fDes*x);

		if(fx >= 0 && fx < SrcBitmap->Width && fy >= 0 && fy < SrcBitmap->Height)
		{
		  DestBitmap->Canvas->Pixels[x][y]= SrcBitmap->Canvas->Pixels[fx][fy];
		}
	  }
	}
	//Mostrar o bitmap girado
	Image1->Picture->Bitmap=DestBitmap;
	delete DestBitmap;
	delete SrcBitmap;
	Edit7->Clear();
}
//---------------------------------------------------------------------------



void __fastcall TForm3::ComboBox1Change(TObject *Sender)
{
	AnsiString teste;
	teste = ComboBox1->Text;
	if(teste == "VERTICAL"){
		/*
		for(int x = 0; x < IntToStr(Image1->Width); x++){
			int fx = (int)(x);
			for(int y = 0;  y < IntToStr(Image1->Height); y++){
				int  fy = (int)((-1)*y);
				Image1->Canvas->Pixels[x][y] = Image1->Canvas->Pixels[fx][fy];
			}
		}

		Graphics::TBitmap *SrcBitmap=new Graphics::TBitmap;
		Graphics::TBitmap *DestBitmap=new Graphics::TBitmap;
		SrcBitmap->LoadFromFile("cg.bmp");
		float Point1x=(Image1->Width);
		float Point1y=(Image1->Height);
		float Point2x=(Image1->Width);
		float Point2y=(Image1->Height);
		float Point3x=(Image1->Width);
		float Point3y=(Image1->Height);

		float minx = min(0,min(Point1x,min(Point2x,Point3x)));
		float miny = min(0,min(Point1y,min(Point2y,Point3y)));
		float maxx = max(Point1x,max(Point2x,Point3x));
		float maxy = max(Point1y,max(Point2y,Point3y));

		int DestBitmapWidth=(int)ceil(fabs(maxx)-minx);
		int DestBitmapHeight=(int)ceil(fabs(maxy)-miny);

		DestBitmap->Height=DestBitmapHeight;
		DestBitmap->Width=DestBitmapWidth;
		for(int x=0;x<DestBitmapWidth;x++)
		{
		  for(int y=0;y<DestBitmapHeight;y++)
		  {
			int	fx = (int)1*(x);
			int fy = (int)((-1)*(y));

			if(fx >= 0 && fx < SrcBitmap->Width && fy >= 0 && fy < SrcBitmap->Height)
			{
			  DestBitmap->Canvas->Pixels[x][y]= SrcBitmap->Canvas->Pixels[fx][fy];
			}
		  }
		}
	//Mostrar o bitmap girado
	Image1->Picture->Bitmap=DestBitmap;
	delete DestBitmap;
	delete SrcBitmap; */

	Graphics::TBitmap *copia = new Graphics::TBitmap;
	copia->LoadFromFile("cg.bmp");
	copia->Height += copia->Height;
	copia->Width += copia->Width;

	  for (int y = 0; y < Image1->Height; y++) {
		for (int x = 0; x < Image1->Width; x++) {
			copia->Canvas->Pixels [Image1->Width-x][y+Image1->Height] = Image1->Canvas->Pixels[Image1->Width-x][Image1->Height-y];
		}
	 }
	 Image1->Picture->Bitmap = copia;
	 delete copia;

	}
	else{
		if(teste == "HORIZONTAL"){
			/*int fx, fy;

			Graphics::TBitmap *SrcBitmap=new Graphics::TBitmap;
			Graphics::TBitmap *DestBitmap=new Graphics::TBitmap;
			SrcBitmap->LoadFromFile("cg.bmp");

			float Point1x=(Image1->Width);
			float Point1y=(Image1->Height);
			float Point2x=(Image1->Width);
			float Point2y=(Image1->Height);
			float Point3x=(Image1->Width);
			float Point3y=(Image1->Height);

			float minx = min(0,min(Point1x,min(Point2x,Point3x)));
			float miny = min(0,min(Point1y,min(Point2y,Point3y)));
			float maxx = max(Point1x,max(Point2x,Point3x));
			float maxy = max(Point1y,max(Point2y,Point3y));

			int DestBitmapWidth=(int)ceil(fabs(maxx)-minx);
			int DestBitmapHeight=(int)ceil(fabs(maxy)-miny);

			DestBitmap->Height=DestBitmapHeight;
			DestBitmap->Width=DestBitmapWidth;

			for(int x=0;x<DestBitmapWidth;x++)
			{
			  for(int y=0;y<DestBitmapHeight;y++)
			  {
				fx = (int)((-1)*x);
				fy = (int)(1*y);

				if(fx >= 0 && fx < SrcBitmap->Width && fy >= 0 && fy < SrcBitmap->Height)
				{
				  DestBitmap->Canvas->Pixels[x][y]= SrcBitmap->Canvas->Pixels[fx][fy];
				}
			  }
			}
			//Mostrar o bitmap girado
			Image1->Picture->Bitmap=DestBitmap;
			delete DestBitmap;
			delete SrcBitmap;
		} */
		}
		Graphics::TBitmap *copia = new Graphics::TBitmap;
		copia->LoadFromFile("cg.bmp");
		copia->Height += copia->Height;
		copia->Width += copia->Width;

		  for (int y = 0; y < Image1->Height; y++) {
			for (int x = 0; x < Image1->Width; x++) {
				copia->Canvas->Pixels[x+Image1->Width][Image1->Height-y] = Image1->Canvas->Pixels[Image1->Width-x][Image1->Height-y];
			}
		 }
		 Image1->Picture->Bitmap = copia;
		 delete copia;

	}
}
//---------------------------------------------------------------------------


