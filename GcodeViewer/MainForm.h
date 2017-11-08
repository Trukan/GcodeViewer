#pragma once

namespace GcodeViewer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

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
	private: System::Windows::Forms::Panel^  panelUnderMenu;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::TextBox^  textUnderMenu;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		 String^ opndfileName = "";

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
			this->glControl1 = (gcnew OpenTK::GLControl());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripDropDownButton1 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->открытьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьКакToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->закрытьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выходToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->panelUnderMenu = (gcnew System::Windows::Forms::Panel());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->textUnderMenu = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->toolStrip1->SuspendLayout();
			this->panelUnderMenu->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// glControl1
			// 
			this->glControl1->BackColor = System::Drawing::Color::Black;
			this->glControl1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->glControl1->Location = System::Drawing::Point(212, 28);
			this->glControl1->Name = L"glControl1";
			this->glControl1->Size = System::Drawing::Size(793, 698);
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
			// 
			// panelUnderMenu
			// 
			this->panelUnderMenu->Controls->Add(this->dataGridView1);
			this->panelUnderMenu->Location = System::Drawing::Point(0, 47);
			this->panelUnderMenu->Name = L"panelUnderMenu";
			this->panelUnderMenu->Size = System::Drawing::Size(206, 682);
			this->panelUnderMenu->TabIndex = 2;
			// 
			// dataGridView1
			// 
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::ColumnHeader;
			this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->dataGridView1->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SunkenVertical;
			this->dataGridView1->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->Column1 });
			this->dataGridView1->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->dataGridView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dataGridView1->EditMode = System::Windows::Forms::DataGridViewEditMode::EditOnEnter;
			this->dataGridView1->EnableHeadersVisualStyles = false;
			this->dataGridView1->Location = System::Drawing::Point(0, 0);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(1);
			this->dataGridView1->MinimumSize = System::Drawing::Size(0, 100);
			this->dataGridView1->Name = L"dataGridView1";
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->Format = L"N0";
			dataGridViewCellStyle1->NullValue = nullptr;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::MenuHighlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::Desktop;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dataGridView1->RowsDefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridView1->RowTemplate->DefaultCellStyle->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->dataGridView1->RowTemplate->ErrorText = L"00000";
			this->dataGridView1->RowTemplate->Height = 17;
			this->dataGridView1->RowTemplate->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGridView1->Size = System::Drawing::Size(206, 682);
			this->dataGridView1->TabIndex = 1;
			this->dataGridView1->RowCount = 100;
			// 
			// textUnderMenu
			// 
			this->textUnderMenu->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textUnderMenu->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textUnderMenu->Location = System::Drawing::Point(3, 28);
			this->textUnderMenu->Name = L"textUnderMenu";
			this->textUnderMenu->ReadOnly = true;
			this->textUnderMenu->ShortcutsEnabled = false;
			this->textUnderMenu->Size = System::Drawing::Size(203, 13);
			this->textUnderMenu->TabIndex = 0;
			this->textUnderMenu->TabStop = false;
			this->textUnderMenu->Text = L"Test Text Maxlength char [37]";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"G-code arcs Files (*.tap)|*.tap|All Files (*.*)|*.*";
			// 
			// Column1
			// 
			this->Column1->DividerWidth = 2;
			this->Column1->FillWeight = 160;
			this->Column1->Frozen = true;
			this->Column1->HeaderText = L"Команды";
			this->Column1->MinimumWidth = 160;
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Column1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column1->Width = 160;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1008, 729);
			this->Controls->Add(this->panelUnderMenu);
			this->Controls->Add(this->textUnderMenu);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->glControl1);
			this->Name = L"MainForm";
			this->Text = L"GcodeViewer";
			this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->panelUnderMenu->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	//обработка нажатия кнопки меню "Сохранить как"
	private: System::Void сохранитьКакToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		this->saveFileDialog1->FileName = opndfileName;
		if(System::Windows::Forms::DialogResult::OK == this->saveFileDialog1->ShowDialog())
			this->Text = "GcodeViewer -  файл " + this->saveFileDialog1->FileName + " сохранен";
		else 
			this->Text = L"GcodeViewer";
	}

	//обработка нажатия кнопки меню "открыть"
	private: System::Void открытьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		this->openFileDialog1->ShowDialog();
		opndfileName = this->openFileDialog1->FileName;
		this->Text = "GcodeViewer -  файл " + opndfileName + " открыт";
	}
	
	//обработка изменения размеров окна
	private: System::Void MainForm_Resize(System::Object^  sender, System::EventArgs^  e) {
		this->glControl1->Size = System::Drawing::Size(this->Width - 232, this->Height - 72);
	}

};
}
