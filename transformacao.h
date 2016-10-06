//---------------------------------------------------------------------------

#ifndef transformacaoH
#define transformacaoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton5;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TSpeedButton *SpeedButton6;
	TSplitter *Splitter1;
	TSplitter *Splitter2;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TLabel *Label8;
	TLabel *Label9;
	TSplitter *Splitter3;
	TSpeedButton *SpeedButton8;
	TLabel *Label10;
	TEdit *Edit6;
	TLabel *Label11;
	TLabel *Label12;
	TEdit *Edit7;
	TSplitter *Splitter4;
	TSpeedButton *SpeedButton9;
	TImage *Image2;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TComboBox *ComboBox1;
	TLabel *Label13;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton6Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton5Click(TObject *Sender);
	void __fastcall SpeedButton8Click(TObject *Sender);
	void __fastcall SpeedButton9Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
