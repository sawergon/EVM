//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "avlTree.h"
#include "Analyzer.h"
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

void init_StringGrid(TStringGrid* str_gr){
	str_gr->RowCount = NUM_ROWS;
	str_gr->Cells[0][0] = "��������";
	str_gr->Cells[1][0] = "���";
}

const char *convert_code(int code) {
	switch (code) {
		case ID_NUM: return "ID_NUM\0";
		case ID_SET: return "ID_SET\0";
		case ID_NOT_EQ: return "ID_NOT_EQ\0";
		case ID_SUM: return "ID_SUM\0";
		case ID_DIF: return "ID_DIF\0";
		case ID_MUL: return "ID_MUL\0";
		case ID_DIV: return "ID_DIV\0";
		case ID_VAR: return "ID_VAR\0";
		case ID_IF: return "ID_IF\0";
		case ID_ELSE: return "ID_ELSE\0";
		case ID_REPEAT: return "ID_REPEAT\0";
		case ID_UNTIL: return "ID_UNTIL\0";
		case ID_LEFT: return "ID_LEFT\0";
		case ID_RIGHT: return "ID_RIGHT\0";
		case ID_BREAK: return "ID_BREAK\0";
		case ID_LESS: return "ID_LESS\0";
		case ID_MORE: return "ID_MORE\0";
		case ID_EQ: return "ID_EQ\0";
	}
	return "TYPE_TRASH";
}

void refresh_StringGrid(TStringGrid* str_gr, node* table, int *start){
	if (table->left) {
		refresh_StringGrid(str_gr, table->left, start);

	}
	(*start)++;
	str_gr->Cells[0][*start] = table->key.name;
	str_gr->Cells[1][*start] = convert_code(table->key.key);
	if (table->right) {
		refresh_StringGrid(str_gr, table->right, start);
	}
}

void clear_StringGrid(TStringGrid* str_gr){
	for(int i = 1; i < NUM_ROWS; i++){
		str_gr->Cells[0][i] = "";
		str_gr->Cells[1][i] = "";
	}
}

void __fastcall TForm1::Create(TObject *Sender)
{
	init_StringGrid(StringGrid1);
	init_StringGrid(StringGrid2);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
	UnicodeString s = Memo1->Text;
	int len = strlen(AnsiString(s).c_str()), pos = 0;
	char * source = (char *) malloc(len);
	strcpy(source, AnsiString(s).c_str());
	node *lexeme_table = nullptr;
	node *id_table = nullptr;
	while (pos < len) {
		lexeme k;
		if (get_lexeme(source, pos, k) == CODE_ER) {
			pos++;
		} else {
			lexeme_table = insert(lexeme_table, k);
			if (((k.key == ID_NUM) || (k.key == ID_VAR)) && (!id_table || !find_name(id_table, k.name))) {
				lexeme d;
				d.name = (char *) malloc(strlen(k.name) + 1);
				strcpy(d.name, k.name);
				d.key = k.key;
				id_table = insert(id_table, d);
			}
		}
	}
	int start = 0;
	clear_StringGrid(StringGrid1);
	clear_StringGrid(StringGrid2);
	refresh_StringGrid(StringGrid1, lexeme_table, &start);
	start = 0;
	refresh_StringGrid(StringGrid2, id_table, &start);
	free(source);
}
//---------------------------------------------------------------------------


