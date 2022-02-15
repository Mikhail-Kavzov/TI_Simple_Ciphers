#pragma once
#include <string>
#include <msclr\marshal_cppstd.h>
#include<vector>
#include<fstream>
#include<codecvt>
#include<math.h>
#include "LabCode.h"
#define BOMend 3
namespace ShiphrLab {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Shiphr
	/// </summary>
	public ref class Shiphr : public System::Windows::Forms::Form
	{
	public:
		Shiphr(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Shiphr()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ StrKey;
	protected:

	private: System::Windows::Forms::Button^ RunBtn;
	private: System::Windows::Forms::RadioButton^ GridRBut;

	private: System::Windows::Forms::RadioButton^ RailRBut;

	private: System::Windows::Forms::RadioButton^ VizhenerRBut;
	private: System::Windows::Forms::RadioButton^ EncryptRBut;
	private: System::Windows::Forms::RadioButton^ DecryptRBut;
	private: System::Windows::Forms::GroupBox^ EncAlgorithms;
	private: System::Windows::Forms::GroupBox^ EncDec;
	private: System::Windows::Forms::OpenFileDialog^ OpenFileDlg;










	protected:


	protected:

	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->StrKey = (gcnew System::Windows::Forms::TextBox());
			this->RunBtn = (gcnew System::Windows::Forms::Button());
			this->GridRBut = (gcnew System::Windows::Forms::RadioButton());
			this->RailRBut = (gcnew System::Windows::Forms::RadioButton());
			this->VizhenerRBut = (gcnew System::Windows::Forms::RadioButton());
			this->EncryptRBut = (gcnew System::Windows::Forms::RadioButton());
			this->DecryptRBut = (gcnew System::Windows::Forms::RadioButton());
			this->EncAlgorithms = (gcnew System::Windows::Forms::GroupBox());
			this->EncDec = (gcnew System::Windows::Forms::GroupBox());
			this->OpenFileDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->EncAlgorithms->SuspendLayout();
			this->EncDec->SuspendLayout();
			this->SuspendLayout();
			// 
			// StrKey
			// 
			this->StrKey->Location = System::Drawing::Point(413, 315);
			this->StrKey->Name = L"StrKey";
			this->StrKey->Size = System::Drawing::Size(510, 22);
			this->StrKey->TabIndex = 0;
			this->StrKey->TextChanged += gcnew System::EventHandler(this, &Shiphr::StrKey_TextChanged);
			// 
			// RunBtn
			// 
			this->RunBtn->Enabled = false;
			this->RunBtn->Location = System::Drawing::Point(954, 315);
			this->RunBtn->Name = L"RunBtn";
			this->RunBtn->Size = System::Drawing::Size(75, 23);
			this->RunBtn->TabIndex = 1;
			this->RunBtn->Text = L"Run";
			this->RunBtn->UseVisualStyleBackColor = true;
			this->RunBtn->Click += gcnew System::EventHandler(this, &Shiphr::RunBtn_Click);
			// 
			// GridRBut
			// 
			this->GridRBut->AutoSize = true;
			this->GridRBut->Location = System::Drawing::Point(6, 73);
			this->GridRBut->Name = L"GridRBut";
			this->GridRBut->Size = System::Drawing::Size(222, 21);
			this->GridRBut->TabIndex = 2;
			this->GridRBut->Text = L"Поворачивающаяся решетка";
			this->GridRBut->UseVisualStyleBackColor = true;
			this->GridRBut->CheckedChanged += gcnew System::EventHandler(this, &Shiphr::GridRBut_CheckedChanged);
			// 
			// RailRBut
			// 
			this->RailRBut->AutoSize = true;
			this->RailRBut->Location = System::Drawing::Point(6, 48);
			this->RailRBut->Name = L"RailRBut";
			this->RailRBut->Size = System::Drawing::Size(217, 21);
			this->RailRBut->TabIndex = 3;
			this->RailRBut->Text = L"Железнодорожная изгородь";
			this->RailRBut->UseVisualStyleBackColor = true;
			this->RailRBut->CheckedChanged += gcnew System::EventHandler(this, &Shiphr::RailRBut_CheckedChanged);
			// 
			// VizhenerRBut
			// 
			this->VizhenerRBut->AutoSize = true;
			this->VizhenerRBut->Checked = true;
			this->VizhenerRBut->Location = System::Drawing::Point(6, 21);
			this->VizhenerRBut->Name = L"VizhenerRBut";
			this->VizhenerRBut->Size = System::Drawing::Size(87, 21);
			this->VizhenerRBut->TabIndex = 4;
			this->VizhenerRBut->TabStop = true;
			this->VizhenerRBut->Text = L"Виженер";
			this->VizhenerRBut->UseVisualStyleBackColor = true;
			this->VizhenerRBut->CheckedChanged += gcnew System::EventHandler(this, &Shiphr::VizhenerRBut_CheckedChanged);
			// 
			// EncryptRBut
			// 
			this->EncryptRBut->AutoSize = true;
			this->EncryptRBut->Checked = true;
			this->EncryptRBut->Location = System::Drawing::Point(6, 21);
			this->EncryptRBut->Name = L"EncryptRBut";
			this->EncryptRBut->Size = System::Drawing::Size(104, 21);
			this->EncryptRBut->TabIndex = 5;
			this->EncryptRBut->TabStop = true;
			this->EncryptRBut->Text = L"Шифровать";
			this->EncryptRBut->UseVisualStyleBackColor = true;
			// 
			// DecryptRBut
			// 
			this->DecryptRBut->AutoSize = true;
			this->DecryptRBut->Location = System::Drawing::Point(6, 48);
			this->DecryptRBut->Name = L"DecryptRBut";
			this->DecryptRBut->Size = System::Drawing::Size(123, 21);
			this->DecryptRBut->TabIndex = 6;
			this->DecryptRBut->Text = L"Дешифровать";
			this->DecryptRBut->UseVisualStyleBackColor = true;
			// 
			// EncAlgorithms
			// 
			this->EncAlgorithms->Controls->Add(this->VizhenerRBut);
			this->EncAlgorithms->Controls->Add(this->RailRBut);
			this->EncAlgorithms->Controls->Add(this->GridRBut);
			this->EncAlgorithms->Location = System::Drawing::Point(413, 150);
			this->EncAlgorithms->Name = L"EncAlgorithms";
			this->EncAlgorithms->Size = System::Drawing::Size(261, 100);
			this->EncAlgorithms->TabIndex = 7;
			this->EncAlgorithms->TabStop = false;
			// 
			// EncDec
			// 
			this->EncDec->Controls->Add(this->EncryptRBut);
			this->EncDec->Controls->Add(this->DecryptRBut);
			this->EncDec->Location = System::Drawing::Point(740, 150);
			this->EncDec->Name = L"EncDec";
			this->EncDec->Size = System::Drawing::Size(200, 100);
			this->EncDec->TabIndex = 8;
			this->EncDec->TabStop = false;
			// 
			// OpenFileDlg
			// 
			this->OpenFileDlg->Filter = L"\"Text files(*.txt)|*.txt";
			// 
			// Shiphr
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1324, 458);
			this->Controls->Add(this->EncDec);
			this->Controls->Add(this->EncAlgorithms);
			this->Controls->Add(this->RunBtn);
			this->Controls->Add(this->StrKey);
			this->Name = L"Shiphr";
			this->Text = L"Shiphr";
			this->EncAlgorithms->ResumeLayout(false);
			this->EncAlgorithms->PerformLayout();
			this->EncDec->ResumeLayout(false);
			this->EncDec->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	
	
	private: System::Void RunBtn_Click(System::Object^ sender, System::EventArgs^ e) {





		System::IO::Stream^ MyStream;
		OpenFileDialog^ OpenF = gcnew OpenFileDialog;
		OpenF->InitialDirectory = "C:\\Users\\User\\source\\repos\\ShiphrLab";
		OpenF->FilterIndex = 1;
		OpenF->RestoreDirectory = true;
		if (OpenF->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			MyStream = OpenF->OpenFile();
			if (MyStream != nullptr)
			{
				



					std::string Fname = msclr::interop::marshal_as<std::string>(OpenF->FileName);
					
					 std::wstring key = msclr::interop::marshal_as<std::wstring>(this->StrKey->Text);
					
					int p = Fname.length() - 1;
					std::string NewName = Fname;

					while (NewName[p] != '.')
					{
						p--;
					}
					
					NewName.insert(p, "_Res");
					
					
					std::wifstream in;
					std::wofstream out;

					in.open(Fname);
					out.open(NewName);
					in.imbue(std::locale(in.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff>));
					out.imbue(std::locale(out.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff>));
					
					try {
						in.seekg(0, ios::end);
						if ((in.tellg()==0)||(in.tellg()==BOMend))
							throw gcnew System::String(L"File is empty");
						in.seekg(ios::beg);
						

						if (VizhenerRBut->Checked == true && EncryptRBut->Checked == true)
						{


							VizhenerEncrypt(key, in, out);
						}
						else if (RailRBut->Checked == true && EncryptRBut->Checked == true)
						{
							RailwayEncrypt(key, in, out);
						}
						else if (GridRBut->Checked == true && EncryptRBut->Checked == true)
						{
							GridEncrypt(in, out);
						}
						else if (VizhenerRBut->Checked == true && DecryptRBut->Checked == true)
						{
							VizhenerDecrypt(key, in, out);
						}
						else if (RailRBut->Checked == true && DecryptRBut->Checked == true)
						{
							RailwayDecrypt(key, in, out);
						}
						else {
							GridDecrypt(in, out);
						}
					}
					catch(String^ ex){

					
						MessageBox::Show(ex,gcnew System::String(L"Error"), MessageBoxButtons::OK, MessageBoxIcon::Error);

					
					}
					
				
				in.close();
				out.close();
				MyStream->Close();
			}
		}
	

	}


private: System::Void VizhenerRBut_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	this->StrKey->Enabled = true;
	this->StrKey->Text = "";
	this->RunBtn->Enabled = false;
}
private: System::Void RailRBut_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	this->StrKey->Enabled = true;
	this->StrKey->Text = "";
	this->RunBtn->Enabled = false;
}
private: System::Void GridRBut_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	this->StrKey->Text = "";
	this->StrKey->Enabled = false;
	this->RunBtn->Enabled = true;
}
private: System::Void StrKey_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (this->StrKey->Text == "")
	{
		this->RunBtn->Enabled = false;
	}
	else this->RunBtn->Enabled = true;
}
};
}
