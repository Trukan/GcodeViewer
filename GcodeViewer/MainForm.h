#pragma once
#include "GcodeData.h"
namespace GcodeViewer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace OpenTK;
	using namespace OpenTK::Platform::Windows;
	using namespace OpenTK::Graphics::OpenGL;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:

		MainForm(void)
		{
			InitializeComponent();
			this->gdata = gcnew GcodeData();
			this->bindingSrc1 = gcnew System::Windows::Forms::BindingSource;
			this->table = gcnew DataTable;
			//
			//TODO: добавьте код конструктора
			//
		}
		cli::array<String^>^ getText(String^);
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: OpenTK::GLControl^  glControl1;
	protected:
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripDropDownButton^  toolStripDropDownButton1;
	private: System::Windows::Forms::ToolStripMenuItem^  открытьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  сохранитьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  сохранитьКакToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  закрытьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  выходToolStripMenuItem1;

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::TextBox^  textUnderMenu;


	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		//имя открываемого файла
		String^ opndfileName = "";
		String^ editCellText = "";
		cli::array<String^>^ tText;
		GcodeData^ gdata;
		DataTable^ table;
		System::Windows::Forms::BindingSource^ bindingSrc1;
		System::Windows::Forms::DataGridView^  dataGridView1;
		System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->glControl1 = (gcnew OpenTK::GLControl());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripDropDownButton1 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->открытьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьКакToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->закрытьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выходToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textUnderMenu = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->toolStrip1->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// glControl1
			// 
			this->glControl1->BackColor = System::Drawing::Color::Black;
			this->glControl1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->glControl1->Location = System::Drawing::Point(360, 28);
			this->glControl1->Name = L"glControl1";
			this->glControl1->Size = System::Drawing::Size(643, 547);
			this->glControl1->TabIndex = 0;
			this->glControl1->VSync = true;
			this->glControl1->AutoSizeChanged += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
			// 
			// toolStrip1
			// 
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripDropDownButton1 });
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(1008, 25);
			this->toolStrip1->TabIndex = 1;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripDropDownButton1
			// 
			this->toolStripDropDownButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripDropDownButton1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->открытьToolStripMenuItem,
					this->сохранитьToolStripMenuItem, this->сохранитьКакToolStripMenuItem, this->закрытьToolStripMenuItem, this->выходToolStripMenuItem1
			});
			this->toolStripDropDownButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripDropDownButton1.Image")));
			this->toolStripDropDownButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripDropDownButton1->Name = L"toolStripDropDownButton1";
			this->toolStripDropDownButton1->Size = System::Drawing::Size(29, 22);
			this->toolStripDropDownButton1->Text = L"toolStripDropDownButton1";
			// 
			// открытьToolStripMenuItem
			// 
			this->открытьToolStripMenuItem->Name = L"открытьToolStripMenuItem";
			this->открытьToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->открытьToolStripMenuItem->Text = L"Открыть";
			this->открытьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::открытьToolStripMenuItem_Click);
			// 
			// сохранитьToolStripMenuItem
			// 
			this->сохранитьToolStripMenuItem->Name = L"сохранитьToolStripMenuItem";
			this->сохранитьToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->сохранитьToolStripMenuItem->Text = L"Сохранить";
			// 
			// сохранитьКакToolStripMenuItem
			// 
			this->сохранитьКакToolStripMenuItem->Name = L"сохранитьКакToolStripMenuItem";
			this->сохранитьКакToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->сохранитьКакToolStripMenuItem->Text = L"Сохранить как";
			this->сохранитьКакToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::сохранитьКакToolStripMenuItem_Click);
			// 
			// закрытьToolStripMenuItem
			// 
			this->закрытьToolStripMenuItem->Name = L"закрытьToolStripMenuItem";
			this->закрытьToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->закрытьToolStripMenuItem->Text = L"Закрыть";
			// 
			// выходToolStripMenuItem1
			// 
			this->выходToolStripMenuItem1->Name = L"выходToolStripMenuItem1";
			this->выходToolStripMenuItem1->Size = System::Drawing::Size(153, 22);
			this->выходToolStripMenuItem1->Text = L"Выход";
			this->выходToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::выходToolStripMenuItem1_Click);
			// 
			// textUnderMenu
			// 
			this->textUnderMenu->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textUnderMenu->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textUnderMenu->Location = System::Drawing::Point(3, 28);
			this->textUnderMenu->Name = L"textUnderMenu";
			this->textUnderMenu->ShortcutsEnabled = false;
			this->textUnderMenu->Size = System::Drawing::Size(343, 13);
			this->textUnderMenu->TabIndex = 0;
			this->textUnderMenu->TabStop = false;
			this->textUnderMenu->Text = L"Test Text Maxlength char [undef]";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"G-code arcs Files (*.tap)|*.tap|All Files (*.*)|*.*";
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 578);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(1008, 22);
			this->statusStrip1->TabIndex = 3;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->AutoSize = false;
			this->toolStripStatusLabel1->Margin = System::Windows::Forms::Padding(3, 2, 0, 2);
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Overflow = System::Windows::Forms::ToolStripItemOverflow::Never;
			this->toolStripStatusLabel1->Size = System::Drawing::Size(440, 18);
			this->toolStripStatusLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToResizeColumns = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::ColumnHeader;
			this->dataGridView1->BackgroundColor = System::Drawing::Color::Lavender;
			this->dataGridView1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->dataGridView1->ClipboardCopyMode = System::Windows::Forms::DataGridViewClipboardCopyMode::EnableWithoutHeaderText;
			this->dataGridView1->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->Column1 });
			this->dataGridView1->Cursor = System::Windows::Forms::Cursors::Arrow;
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::GradientActiveCaption;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridView1->EditMode = System::Windows::Forms::DataGridViewEditMode::EditOnKeystroke;
			this->dataGridView1->EnableHeadersVisualStyles = false;
			this->dataGridView1->GridColor = System::Drawing::SystemColors::ButtonShadow;
			this->dataGridView1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->dataGridView1->Location = System::Drawing::Point(3, 45);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(1, 1, 1, 0);
			this->dataGridView1->MinimumSize = System::Drawing::Size(0, 100);
			this->dataGridView1->Name = L"dataGridView1";
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::ScrollBar;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle3->Format = L"N0";
			dataGridViewCellStyle3->NullValue = nullptr;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::GradientActiveCaption;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::Desktop;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
			this->dataGridView1->RowHeadersWidth = 75;
			this->dataGridView1->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle4->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dataGridView1->RowsDefaultCellStyle = dataGridViewCellStyle4;
			this->dataGridView1->RowTemplate->DefaultCellStyle->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->dataGridView1->RowTemplate->ErrorText = L"00000";
			this->dataGridView1->RowTemplate->Height = 17;
			this->dataGridView1->RowTemplate->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGridView1->Size = System::Drawing::Size(356, 530);
			this->dataGridView1->TabIndex = 1;
			this->dataGridView1->CellBeginEdit += gcnew System::Windows::Forms::DataGridViewCellCancelEventHandler(this, &MainForm::dataGridView1_CellBeginEdit);
			this->dataGridView1->CellEnter += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::dataGridView1_CellEnter);
			this->dataGridView1->CellLeave += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::dataGridView1_CellLeave);
			this->dataGridView1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
			this->dataGridView1->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &MainForm::dataGridView1_PreviewKeyDown);
		//		 this->dataGridView1->AutoGenerateColumns = true;
				 // 
				 // Column1
				 // 
			this->Column1->DataPropertyName = "commands";
			this->Column1->DividerWidth = 2;
			this->Column1->FillWeight = 256;
			this->Column1->Frozen = true;
			this->Column1->HeaderText = "Команды";
			this->Column1->MinimumWidth = 256;
			this->Column1->Name = L"Column1";
			this->Column1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Column1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column1->Width = 256;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1008, 600);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->textUnderMenu);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->glControl1);
			this->MinimumSize = System::Drawing::Size(585, 300);
			this->Name = L"MainForm";
			this->Text = L"GcodeViewer";
			this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
		//обработка нажатия кнопки меню "Сохранить как"
	private: System::Void сохранитьКакToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		this->saveFileDialog1->FileName = opndfileName;
		if (System::Windows::Forms::DialogResult::OK == this->saveFileDialog1->ShowDialog())
			this->textUnderMenu->Text = this->saveFileDialog1->FileName + " сохранен";
		else
			this->Text = L"GcodeViewer";
	}

			 //обработка нажатия кнопки меню "открыть"
	private: System::Void открытьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (System::Windows::Forms::DialogResult::OK == this->openFileDialog1->ShowDialog()) {
			opndfileName = this->openFileDialog1->FileName;
			if (gdata->loadFile(opndfileName)) {
				this->textUnderMenu->Text = " открыт:" + opndfileName;
				this->dataGridView1->Rows->Clear();
		//		this->table->
		//		this->dataGridView1->DataSource = gdata->commands;
				
						this->dataGridView1->RowCount = gdata->commands->Count;
				//		this->dataGridView1->Rows-> = gdata->commands;
						int rowNumber = 1;
						System::Collections::IEnumerator^ myEnum = safe_cast<System::Collections::IEnumerable^>(dataGridView1->Rows)->GetEnumerator();
						myEnum->Reset();
						while (myEnum->MoveNext())
						{
							DataGridViewRow^ row = safe_cast<DataGridViewRow^>(myEnum->Current);
							row->HeaderCell->Value = String::Format(L"{0}", rowNumber);
							row->SetValues(gdata->commands[rowNumber - 1]);
							if (rowNumber >= gdata->commands->Count)
								break;
							rowNumber = rowNumber + 1;
						}
			
			}
			else {
				this->textUnderMenu->Text = "не открытся" + opndfileName;
			}
		}
	}
			 //обработка нажатия кнопки меню "выход"
	private: System::Void выходToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
			 //обработка изменения размеров окна
	private: System::Void MainForm_Resize(System::Object^  sender, System::EventArgs^  e) {
		this->glControl1->Size = System::Drawing::Size(this->Width - 380, this->Height - 92);
		this->dataGridView1->Size = System::Drawing::Size(356, this->Height - 109);
		this->toolStrip1->Size = System::Drawing::Size(this->Width - 4, 25);

	}

			 //обработка события CellBeginEdit
	private: System::Void dataGridView1_CellBeginEdit(System::Object^  sender, System::Windows::Forms::DataGridViewCellCancelEventArgs^  e) {
	}

			 //обработка события CellEnter
	private: System::Void dataGridView1_CellEnter(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		this->toolStripStatusLabel1->Text = "" + this->dataGridView1->CurrentCell->RowIndex + ":" +
			this->dataGridView1->CurrentCell->ColumnIndex +
			"BeginEdit:" + this->dataGridView1->BeginEdit(true);
	}
			 //обработка события CellLeave
	private: System::Void dataGridView1_CellLeave(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		this->dataGridView1->EndEdit();
	}
	private: System::Void dataGridView1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {

	}

	private: System::Void dataGridView1_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
		if (this->dataGridView1->SelectedCells->Count != 0) {
			switch (e->KeyCode) {
				//		case Keys::Delete:
				//			if(this->dataGridView1->EditingControl!=nullptr)
				//				this->dataGridView1->Rows->RemoveAt(this->dataGridView1->CurrentCell->RowIndex);
				//			break;
			case Keys::Escape:
				this->dataGridView1->CurrentCell = nullptr;
				break;
			case Keys::Enter:
				if (this->dataGridView1->CurrentCell->RowIndex + 1 < this->dataGridView1->Rows->Count)
					this->dataGridView1->Rows->Insert(this->dataGridView1->CurrentCell->RowIndex + 1, 1);
				this->toolStripStatusLabel1->Text = "" + this->dataGridView1->CurrentCell->RowIndex + ":" +
					this->dataGridView1->CurrentCell->ColumnIndex + "rowCount" + this->dataGridView1->Rows->Count;
				break;
			}
		}
	}
	};
}
