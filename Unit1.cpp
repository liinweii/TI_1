//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TForm1::getStolbKey()
{
	keyStolb = stolbKey->Text;
}

void TForm1::getVigenerKey()
{
	keyVigener = vigenerKey->Text;
}

void TForm1::getStolbInp()
{
	inpStolb = stolbInput->Text;
}

void TForm1::getVigenerInp()
{
	inpVig = vigInput->Text;
}

void TForm1::showStolbOut()
{
	stolbOutput->Text = outStolb;
}

void TForm1::showVigenerOut()
{
	vigOutput->Text = outVig;
}

void TForm1::clearStolb()
{
	stolbInput->Text = "";
	stolbKey->Text = "";
	stolbOutput->Text = "";
}

void TForm1::clearVigener()
{
	vigInput->Text = "";
	vigenerKey->Text = "";
	vigOutput->Text = "";
}
void __fastcall TForm1::stolbClearClick(TObject *Sender)
{
    clearStolb();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::vigenerClearClick(TObject *Sender)
{
    clearVigener();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::stolbShiphClick(TObject *Sender)
{
	encodeStolb();
}

void TForm1::encodeStolb()
{
	getStolbKey();

	getStolbInp();


	UnicodeString text = inpStolb.UpperCase();
	UnicodeString key = keyStolb.UpperCase();

	UnicodeString cleanText = L"";
	for(int i = 1; i <= text.Length(); i++)
	{
		if((text[i] >= L'А' && text[i] <= L'Я') || text[i] == L'Ё')
			cleanText += text[i];
	}
	if (cleanText == L"")
	{
		ShowMessage(L"Исходный текст не содержит корректных символов");
		return;
	}

	UnicodeString cleanKey = L"";
	for(int i = 1; i <= key.Length(); i++)
	{
		if((key[i] >= L'А' && key[i] <= L'Я') || key[i] == L'Ё')
			cleanKey += key[i];
	}
    	if (cleanKey == L"")
	{
		ShowMessage(L"Ключ не содержит корректных символов");
		return;
	}

	int cols = cleanKey.Length();
	int rows = (cleanText.Length() + cols - 1) / cols;

	struct KeyItem
	{
		wchar_t ch;
		int originalPos;
		int order;
	};

	KeyItem* keyItems = new KeyItem[cols + 1];

	for(int j = 1; j <= cols; j++)
	{
		keyItems[j].ch = cleanKey[j];
		keyItems[j].originalPos = j;
		keyItems[j].order = 0;
	}

   /*	for(int i = 1; i <= cols; i++)
	{
		for(int j = i + 1; j <= cols; j++)
		{
			if(keyItems[i].ch > keyItems[j].ch)
			{
				KeyItem temp = keyItems[i];
				keyItems[i] = keyItems[j];
				keyItems[j] = temp;
			}
		}
	}      */

    for(int i = 2; i <= cols; i++) {
		KeyItem key = keyItems[i];
		int j = i - 1;
		while(j >= 1 && keyItems[j].ch > key.ch) {
			keyItems[j + 1] = keyItems[j];
			j--;
		}
		keyItems[j + 1] = key;
	}

	for(int i = 1; i <= cols; i++)
	{
		keyItems[i].order = i;
	}

	for(int i = 1; i <= cols; i++)
	{
		for(int j = i + 1; j <= cols; j++)
		{
			if(keyItems[i].originalPos > keyItems[j].originalPos)
			{
				KeyItem temp = keyItems[i];
				keyItems[i] = keyItems[j];
				keyItems[j] = temp;
			}
		}
	}

	int* readOrder = new int[cols + 1];
	for(int j = 1; j <= cols; j++)
	{
		readOrder[keyItems[j].order] = j;
	}

	UnicodeString result = L"";
	int countBlank = 5;
	for(int order = 1; order <= cols; order++)
	{
		int col = readOrder[order];

		for(int row = 0; row < rows; row++)
		{
			int pos = row * cols + (col - 1);


			if(pos < cleanText.Length())
			{
				result += cleanText[pos + 1];

				if(result.Length() % countBlank == 0 && pos < cleanText.Length() - 1)
				{
					result += L' ';
					countBlank+=6;
				}
			}
		}
	}

	outStolb = result;
	showStolbOut();

	delete[] keyItems;
	delete[] readOrder;

}

void TForm1::encodeVigener()
{
	getVigenerKey();

	getVigenerInp();

	UnicodeString alphabet = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";


	UnicodeString text = inpVig.UpperCase();
	UnicodeString key = keyVigener.UpperCase();

	UnicodeString cleanText = L"";
	for(int i = 1; i <= text.Length(); i++)
	{
		if((text[i] >= L'А' && text[i] <= L'Я') || text[i] == L'Ё')
		{
			cleanText += text[i];
		}
	}

	if (cleanText == L"")
	{
		ShowMessage(L"Исходный текст не содержит корректных символов");
		return;
	}

	UnicodeString cleanKey = L"";
	for(int i = 1; i <= key.Length(); i++)
	{
		if((key[i] >= L'А' && key[i] <= L'Я') || key[i] == L'Ё')
		{
			cleanKey += key[i];
		}
	}
	if (cleanKey == L"")
	{
		ShowMessage(L"Ключ не содержит корректных символов");
		return;
	}

	UnicodeString generatedKey = cleanKey;

	int keyPos = 1;
	while(generatedKey.Length() < cleanText.Length())
	{
		generatedKey += cleanText[keyPos];
		keyPos++;
	}

	UnicodeString result = L"";
	for(int i = 1; i <= cleanText.Length(); i++)
	{

		int textPos = 0;
		for(int j = 1; j <= alphabet.Length(); j++)
		{
			if(cleanText[i] == alphabet[j])
			{
				textPos = j;
				break;
			}
		}

		int keyPos = 0;
		for(int j = 1; j <= alphabet.Length(); j++)
		{
			if(generatedKey[i] == alphabet[j])
			{
				keyPos = j;
				break;
			}
		}

		int cipherPos = textPos + keyPos - 1;
		if(cipherPos > alphabet.Length())
		{
			cipherPos -= alphabet.Length();
		}

		result += alphabet[cipherPos];

		if(i % 5 == 0 && i < cleanText.Length())
		{
			result += L' ';
		}
	}

	outVig = result;
	showVigenerOut();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::vigenerShiphClick(TObject *Sender)
{
    encodeVigener();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::stolbDeshiphClick(TObject *Sender)
{
	decodeStolb();
}
//---------------------------------------------------------------------------

void TForm1::decodeStolb()
{
	getStolbKey();
	getStolbInp();


	UnicodeString cipherText = inpStolb.UpperCase();
	UnicodeString key = keyStolb.UpperCase();

	UnicodeString cleanCipher = L"";
	for(int i = 1; i <= cipherText.Length(); i++)
	{
		if((cipherText[i] >= L'А' && cipherText[i] <= L'Я') || cipherText[i] == L'Ё')
		{
			cleanCipher += cipherText[i];
		}
	}
    if (cleanCipher == L"")
	{
		ShowMessage(L"Исходный текст не содержит корректных символов");
		return;
	}

	UnicodeString cleanKey = L"";
	for(int i = 1; i <= key.Length(); i++)
	{
		if((key[i] >= L'А' && key[i] <= L'Я') || key[i] == L'Ё')
		{
			cleanKey += key[i];
		}
	}
	if (cleanKey == L"")
	{
		ShowMessage(L"Ключ не содержит корректных символов");
		return;
	}

	int cols = cleanKey.Length();
	int totalChars = cleanCipher.Length();
	int rows = (totalChars + cols - 1) / cols;
	int lastRowFilled = totalChars % cols;
	if(lastRowFilled == 0) lastRowFilled = cols;

	struct KeyItem
	{
		wchar_t ch;
		int originalPos;
		int order;
	};

	KeyItem* keyItems = new KeyItem[cols + 1];

	for(int j = 1; j <= cols; j++)
	{
		keyItems[j].ch = cleanKey[j];
		keyItems[j].originalPos = j;
		keyItems[j].order = 0;
	}

   /*	for(int i = 1; i <= cols; i++)
	{
		for(int j = i + 1; j <= cols; j++)
		{
			if(keyItems[i].ch > keyItems[j].ch)
			{
				KeyItem temp = keyItems[i];
				keyItems[i] = keyItems[j];
				keyItems[j] = temp;
			}
		}
	}      */

    for(int i = 2; i <= cols; i++) {
		KeyItem key = keyItems[i];
		int j = i - 1;

		// Двигаем элементы, которые БОЛЬШЕ текущего
		while(j >= 1 && keyItems[j].ch > key.ch) {
			keyItems[j + 1] = keyItems[j];
			j--;
		}
		keyItems[j + 1] = key;
	}

	for(int i = 1; i <= cols; i++)
	{
		keyItems[i].order = i;
	}

	for(int i = 1; i <= cols; i++)
	{
		for(int j = i + 1; j <= cols; j++)
		{
			if(keyItems[i].originalPos > keyItems[j].originalPos)
			{
				KeyItem temp = keyItems[i];
				keyItems[i] = keyItems[j];
				keyItems[j] = temp;
			}
		}
	}

	int* colOrder = new int[cols + 1];
	for(int j = 1; j <= cols; j++)
	{
		colOrder[j] = keyItems[j].order;
	}

	int* readOrder = new int[cols + 1];
	for(int j = 1; j <= cols; j++)
	{
		readOrder[colOrder[j]] = j;
	}

	int* colLengths = new int[cols + 1];
	for(int j = 1; j <= cols; j++)
	{
		if(j <= lastRowFilled)
		{
			colLengths[j] = rows;
		} else
		{
			colLengths[j] = rows - 1;
		}
	}

	int* colStartPos = new int[cols + 1];
	int* colCurrentPos = new int[cols + 1];

	int currentPos = 1;
	for(int order = 1; order <= cols; order++)
	{
		int col = readOrder[order];
		colStartPos[col] = currentPos;
		colCurrentPos[col] = currentPos;
		currentPos += colLengths[col];
	}

	UnicodeString result = L"";
	int* colReadCount = new int[cols + 1];
	for(int j = 1; j <= cols; j++)
	{
		colReadCount[j] = 0;
	}

	for(int row = 1; row <= rows; row++)
	{
		for(int col = 1; col <= cols; col++)
		{
			if(row <= colLengths[col])
			{
				int pos = colStartPos[col] + colReadCount[col];
				result += cleanCipher[pos];
				colReadCount[col]++;
			}
		}

	}

	outStolb = result;
	showStolbOut();

	delete[] keyItems;
	delete[] colOrder;
	delete[] readOrder;
	delete[] colLengths;
	delete[] colStartPos;
	delete[] colCurrentPos;
	delete[] colReadCount;
}
void __fastcall TForm1::vigenerDeshiphClick(TObject *Sender)
{
	decodeVigener();
}
//---------------------------------------------------------------------------

void TForm1::decodeVigener()
{
	getVigenerKey();
	getVigenerInp();

	UnicodeString alphabet = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	int alphabetSize = alphabet.Length();

	UnicodeString cipherText = vigInput->Text.UpperCase();
	UnicodeString key = keyVigener.UpperCase();

	UnicodeString cleanCipher = L"";
	for(int i = 1; i <= cipherText.Length(); i++)
	{
		if((cipherText[i] >= L'А' && cipherText[i] <= L'Я') || cipherText[i] == L'Ё')
		{
			cleanCipher += cipherText[i];
		}
	}

	if (cleanCipher == L"")
	{
		ShowMessage(L"Исходный текст не содержит корректных символов");
		return;
	}

	UnicodeString cleanKey = L"";
	for(int i = 1; i <= key.Length(); i++)
	{
		if((key[i] >= L'А' && key[i] <= L'Я') || key[i] == L'Ё')
		{
			cleanKey += key[i];
		}
	}

	if (cleanKey == L"")
	{
		ShowMessage(L"Ключ не содержит корректных символов");
		return;
	}

	UnicodeString result = L"";
	UnicodeString generatedKey = cleanKey;

	for(int i = 1; i <= cleanCipher.Length(); i++)
	{
		int cipherIdx = 0;
		for(int j = 1; j <= alphabetSize; j++)
		{
			if(cleanCipher[i] == alphabet[j])
			{
				cipherIdx = j - 1;
				break;
			}
		}

		int keyIdx = 0;
		for(int j = 1; j <= alphabetSize; j++)
		{
			if(generatedKey[i] == alphabet[j])
			{
				keyIdx = j - 1;
				break;
			}
		}

		int textIdx = (cipherIdx - keyIdx + alphabetSize) % alphabetSize;

		wchar_t plainChar = alphabet[textIdx + 1];
		result += plainChar;
		if(generatedKey.Length() < cleanCipher.Length())
		{
			generatedKey += plainChar;
		}
	}

	outVig = result;
	showVigenerOut();
}


void __fastcall TForm1::stolbFileClick(TObject *Sender)
{
	TOpenDialog* OpenDialog = new TOpenDialog(this);
	OpenDialog->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
	OpenDialog->DefaultExt = "txt";

	if(OpenDialog->Execute())
	{
		try {
			TStringList* SL = new TStringList();
			SL->LoadFromFile(OpenDialog->FileName, TEncoding::UTF8);

			if(SL->Count >= 2)
			{
				stolbKey->Text = SL->Strings[0].Trim();
				stolbInput->Text = SL->Strings[1].Trim();

				ShowMessage(L"Данные загружены");
			} else
			{
				ShowMessage(L"Файл должен содержать 2 строки: ключ и текст");
			}

			delete SL;
		}
		catch(Exception &e)
		{
			ShowMessage(L"Ошибка: " + e.Message);
		}
	}

	delete OpenDialog;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::vigenerFileClick(TObject *Sender)
{
	TOpenDialog* OpenDialog = new TOpenDialog(this);
	OpenDialog->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
	OpenDialog->DefaultExt = "txt";

	if(OpenDialog->Execute())
	{
		try
		{
			TStringList* SL = new TStringList();
			SL->LoadFromFile(OpenDialog->FileName, TEncoding::UTF8);

			if(SL->Count >= 2)
			{
				vigenerKey->Text = SL->Strings[0].Trim();
				vigInput->Text = SL->Strings[1].Trim();

				ShowMessage(L"Данные загружены");
			} else
			{
				ShowMessage(L"Файл должен содержать 2 строки: ключ и текст");
			}

			delete SL;
		}
		catch(Exception &e)
		{
			ShowMessage(L"Ошибка: " + e.Message);
		}
	}

	delete OpenDialog;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::stolbSaveClick(TObject *Sender)
{
	if(stolbOutput->Text.IsEmpty())
	{
		ShowMessage(L"Нет данных для сохранения.");
		return;
	}

	TSaveDialog* SaveDialog = new TSaveDialog(this);
	SaveDialog->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
	SaveDialog->DefaultExt = "txt";

	if(SaveDialog->Execute())
	{
		TStringList* SL = new TStringList();

		try
		{
			SL->Add(L"СТОЛБЦОВЫЙ МЕТОД");
			SL->Add(L"");
			SL->Add(L"Ключ: " + stolbKey->Text);
			SL->Add(L"Исходный текст: " + stolbInput->Text);
			SL->Add(L"Результат: " + stolbOutput->Text);

			SL->SaveToFile(SaveDialog->FileName, TEncoding::UTF8);
			ShowMessage(L"Результат сохранен");
        }
		catch(Exception &e)
		{
			ShowMessage(L"Ошибка сохранения: " + e.Message);
        }

		delete SL;
	}

	delete SaveDialog;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::vigSaveClick(TObject *Sender)
{
	if(vigOutput->Text.IsEmpty())
	{
		ShowMessage(L"Нет данных для сохранения.");
		return;
	}

    TSaveDialog* SaveDialog = new TSaveDialog(this);
	SaveDialog->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
	SaveDialog->DefaultExt = "txt";

	if(SaveDialog->Execute())
	{
		TStringList* SL = new TStringList();

		try
		{
			SL->Add(L"МЕТОД ВИЖЕНЕРА (САМОГЕНЕРИРУЮЩИЙСЯ КЛЮЧ)");
			SL->Add(L"");
			SL->Add(L"Ключ: " + vigenerKey->Text);
			SL->Add(L"Исходный текст: " + vigInput->Text);
			SL->Add(L"Результат: " + vigOutput->Text);

			SL->SaveToFile(SaveDialog->FileName, TEncoding::UTF8);
			ShowMessage(L"Результат сохранен");
        }
		catch(Exception &e)
		{
			ShowMessage(L"Ошибка сохранения: " + e.Message);
        }

		delete SL;
	}

	delete SaveDialog;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::saveButtonClick(TObject *Sender)
{
	if(stolbOutput->Text.IsEmpty() || vigOutput->Text.IsEmpty())
	{
		ShowMessage(L"Недостаточно данных для сохранения.");
		return;
	}

    TSaveDialog* SaveDialog = new TSaveDialog(this);
	SaveDialog->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
	SaveDialog->DefaultExt = "txt";

	if(SaveDialog->Execute())
	{
		TStringList* SL = new TStringList();

		try
		{
			SL->Add(L"СТОЛБЦОВЫЙ МЕТОД");
			SL->Add(L"");
			SL->Add(L"Ключ: " + stolbKey->Text);
			SL->Add(L"Исходный текст: " + stolbInput->Text);
			SL->Add(L"Результат: " + stolbOutput->Text);
            SL->Add(L"");
			SL->Add(L"МЕТОД ВИЖЕНЕРА (САМОГЕНЕРИРУЮЩИЙСЯ КЛЮЧ)");
			SL->Add(L"");
			SL->Add(L"Ключ: " + vigenerKey->Text);
			SL->Add(L"Исходный текст: " + vigInput->Text);
			SL->Add(L"Результат: " + vigOutput->Text);

			SL->SaveToFile(SaveDialog->FileName, TEncoding::UTF8);
			ShowMessage(L"Результат сохранен");
        }
		catch(Exception &e)
		{
			ShowMessage(L"Ошибка сохранения: " + e.Message);
        }

		delete SL;
	}

	delete SaveDialog;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    TOpenDialog* OpenDialog = new TOpenDialog(this);
	OpenDialog->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
	OpenDialog->DefaultExt = "txt";

	if(OpenDialog->Execute())
	{
		try
		{
			TStringList* SL = new TStringList();
			SL->LoadFromFile(OpenDialog->FileName, TEncoding::UTF8);

			if(SL->Count >= 4)
			{
				stolbKey->Text = SL->Strings[0].Trim();
				stolbInput->Text = SL->Strings[1].Trim();
				vigenerKey->Text = SL->Strings[2].Trim();
				vigInput->Text = SL->Strings[3].Trim();

				ShowMessage(L"Данные загружены");
			} else
			{
				ShowMessage(L"Файл должен содержать 4 строки: ключ и текст для каждого из методов");
			}

			delete SL;
		}
		catch(Exception &e)
		{
			ShowMessage(L"Ошибка: " + e.Message);
		}
	}

	delete OpenDialog;
}
//---------------------------------------------------------------------------

