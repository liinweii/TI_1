//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *stolbKey;
	TEdit *vigenerKey;
	TLabel *stolbName;
	TLabel *viginerName;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *stolbInput;
	TEdit *stolbOutput;
	TEdit *vigInput;
	TEdit *vigOutput;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TButton *stolbFile;
	TButton *vigenerFile;
	TButton *stolbShiph;
	TButton *stolbDeshiph;
	TButton *vigenerDeshiph;
	TButton *vigenerShiph;
	TButton *stolbClear;
	TButton *vigenerClear;
	TButton *vigSave;
	TButton *stolbSave;
	TButton *saveButton;
	TButton *Button1;
	TPanel *Panel1;
	TPanel *Panel2;
	void __fastcall stolbClearClick(TObject *Sender);
	void __fastcall vigenerClearClick(TObject *Sender);
	void __fastcall stolbShiphClick(TObject *Sender);
	void __fastcall vigenerShiphClick(TObject *Sender);
	void __fastcall stolbDeshiphClick(TObject *Sender);
	void __fastcall vigenerDeshiphClick(TObject *Sender);
	void __fastcall stolbFileClick(TObject *Sender);
	void __fastcall vigenerFileClick(TObject *Sender);
	void __fastcall stolbSaveClick(TObject *Sender);
	void __fastcall vigSaveClick(TObject *Sender);
	void __fastcall saveButtonClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void getStolbKey();
	void getVigenerKey();
	void getVigenerInp();
	void showVigenerOut();
	void getStolbInp();
	void showStolbOut();
	void clearStolb();
	void clearVigener();
	void encodeStolb();
	void encodeVigener();
	void decodeStolb();
    void decodeVigener();
	UnicodeString keyStolb, keyVigener, inpStolb, inpVig, outStolb, outVig;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
