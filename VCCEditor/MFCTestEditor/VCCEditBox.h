#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace MFCTestEditor {

	/// <summary>
	/// Resumen de VCCEditBox
	/// </summary>
	public ref class VCCEditBox : public System::Windows::Forms::UserControl
	{
	public:
		VCCEditBox(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			editBox->Grammar =  (gcnew T3000::T3000Grammar());
			//editTextBox.Grammar = new T3000Grammar();
			editBox->SetParser( gcnew Irony::Parsing::LanguageData(editBox->Grammar));
            //editTextBox.SetParser(new LanguageData(editTextBox.Grammar));
			
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén utilizando.
		/// </summary>
		~VCCEditBox()
		{
			if (components)
			{
				delete components;
			}
		}
	private: FastColoredTextBoxNS::IronyFCTB^  editBox;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(VCCEditBox::typeid));
			this->editBox = (gcnew FastColoredTextBoxNS::IronyFCTB());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->editBox))->BeginInit();
			this->SuspendLayout();
			// 
			// editBox
			// 
			this->editBox->AutoCompleteBracketsList = gcnew cli::array< System::Char >(10) {'(', ')', '{', '}', '[', ']', '\"', '\"', '\'', 
				'\''};
			this->editBox->AutoScrollMinSize = System::Drawing::Size(27, 14);
			this->editBox->BackBrush = nullptr;
			this->editBox->CharHeight = 14;
			this->editBox->CharWidth = 8;
			this->editBox->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->editBox->DisabledColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(180)), 
				static_cast<System::Int32>(static_cast<System::Byte>(180)), static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->editBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->editBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F));
			this->editBox->InputsColor = System::Drawing::Color::Empty;
			this->editBox->IsReplaceMode = false;
			this->editBox->Location = System::Drawing::Point(0, 0);
			this->editBox->Name = L"editBox";
			this->editBox->OutputsColor = System::Drawing::Color::Empty;
			this->editBox->Paddings = System::Windows::Forms::Padding(0);
			this->editBox->SelectionColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->editBox->ServiceColors = (cli::safe_cast<FastColoredTextBoxNS::ServiceColors^  >(resources->GetObject(L"editBox.ServiceColors")));
			this->editBox->Size = System::Drawing::Size(331, 239);
			this->editBox->TabIndex = 0;
			this->editBox->Zoom = 100;
			// 
			// VCCEditBox
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->editBox);
			this->Name = L"VCCEditBox";
			this->Size = System::Drawing::Size(331, 239);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->editBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
