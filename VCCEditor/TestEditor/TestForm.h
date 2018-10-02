#pragma once

namespace TestEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace T3000;
	using namespace Irony;

	/// <summary>
	/// Resumen de TestForm
	/// </summary>
	public ref class TestForm : public System::Windows::Forms::Form
	{
	public:
		TestForm(void)
		{
			InitializeComponent();
			//
			//TODO: inicializar nuevo parser para que funcione el highlighting
			//


			editorFCTB->Grammar =  (gcnew T3000::T3000Grammar());
			//editTextBox.Grammar = new T3000Grammar();
			editorFCTB->SetParser( gcnew Irony::Parsing::LanguageData(editorFCTB->Grammar));
            //editTextBox.SetParser(new LanguageData(editTextBox.Grammar));

			
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén utilizando.
		/// </summary>
		~TestForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: FastColoredTextBoxNS::IronyFCTB^  editorFCTB;
	protected: 
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Variable del diseñador requerida.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido del método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TestForm::typeid));
			this->editorFCTB = (gcnew FastColoredTextBoxNS::IronyFCTB());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->editorFCTB))->BeginInit();
			this->SuspendLayout();
			// 
			// editorFCTB
			// 
			this->editorFCTB->AutoCompleteBracketsList = gcnew cli::array< System::Char >(10) {'(', ')', '{', '}', '[', ']', '\"', '\"', '\'', 
				'\''};
			this->editorFCTB->AutoScrollMinSize = System::Drawing::Size(27, 14);
			this->editorFCTB->BackBrush = nullptr;
			this->editorFCTB->CharHeight = 14;
			this->editorFCTB->CharWidth = 8;
			this->editorFCTB->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->editorFCTB->DisabledColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(180)), 
				static_cast<System::Int32>(static_cast<System::Byte>(180)), static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->editorFCTB->Dock = System::Windows::Forms::DockStyle::Fill;
			this->editorFCTB->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F));
			this->editorFCTB->InputsColor = System::Drawing::Color::Empty;
			this->editorFCTB->IsReplaceMode = false;
			this->editorFCTB->Location = System::Drawing::Point(0, 0);
			this->editorFCTB->Name = L"editorFCTB";
			this->editorFCTB->OutputsColor = System::Drawing::Color::Empty;
			this->editorFCTB->Paddings = System::Windows::Forms::Padding(0);
			this->editorFCTB->SelectionColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->editorFCTB->ServiceColors = (cli::safe_cast<FastColoredTextBoxNS::ServiceColors^  >(resources->GetObject(L"editorFCTB.ServiceColors")));
			this->editorFCTB->Size = System::Drawing::Size(633, 360);
			this->editorFCTB->TabIndex = 0;
			this->editorFCTB->Zoom = 100;
			// 
			// TestForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(633, 360);
			this->Controls->Add(this->editorFCTB);
			this->Name = L"TestForm";
			this->Text = L"TestForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->editorFCTB))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}

