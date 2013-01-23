#include "Parser.h"
#include "Fitowanie.h"
#include <complex>
#include <intrin.h>
#include "Dense"
using Eigen::MatrixXd;
namespace DielectricFitter {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  FileToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  abooutToolStripMenuItem;

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series10 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series11 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series12 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->FileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->abooutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart2))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea3->AxisX->IsMarginVisible = false;
			chartArea3->AxisX->IsStartedFromZero = false;
			chartArea3->AxisX->LabelStyle->Interval = 0;
			chartArea3->AxisX->MajorGrid->Enabled = false;
			chartArea3->AxisX->MaximumAutoSize = 85;
			chartArea3->AxisX->Title = L"log (Czêstotliwoœæ)";
			chartArea3->AxisX2->MajorGrid->Enabled = false;
			chartArea3->AxisY->IsStartedFromZero = false;
			chartArea3->AxisY->MajorGrid->Enabled = false;
			chartArea3->AxisY2->IsStartedFromZero = false;
			chartArea3->AxisY2->MajorGrid->Enabled = false;
			chartArea3->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea3);
			this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart1->Location = System::Drawing::Point(3, 3);
			this->chart1->Name = L"chart1";
			series7->ChartArea = L"ChartArea1";
			series7->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series7->Color = System::Drawing::Color::Black;
			series7->Name = L"Series1";
			series8->ChartArea = L"ChartArea1";
			series8->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series8->Color = System::Drawing::Color::Red;
			series8->Name = L"Series2";
			series8->YAxisType = System::Windows::Forms::DataVisualization::Charting::AxisType::Secondary;
			series9->ChartArea = L"ChartArea1";
			series9->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series9->Color = System::Drawing::Color::Black;
			series9->Name = L"Series3";
			series10->ChartArea = L"ChartArea1";
			series10->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series10->Color = System::Drawing::Color::Red;
			series10->Name = L"Series4";
			series10->YAxisType = System::Windows::Forms::DataVisualization::Charting::AxisType::Secondary;
			this->chart1->Series->Add(series7);
			this->chart1->Series->Add(series8);
			this->chart1->Series->Add(series9);
			this->chart1->Series->Add(series10);
			this->chart1->Size = System::Drawing::Size(759, 501);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &Form1::chart1_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(4, 27);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 21);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Load and fit";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"Dat file|*.dat|txt file|*.txt";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(115, 27);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(106, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"0,4108e-12";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(227, 27);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(0, 50);
			this->tabControl1->Margin = System::Windows::Forms::Padding(10);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(773, 533);
			this->tabControl1->TabIndex = 4;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->chart1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(765, 507);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Bode Plot";
			this->tabPage1->UseVisualStyleBackColor = true;
			this->tabPage1->Click += gcnew System::EventHandler(this, &Form1::tabPage1_Click);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->chart2);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(765, 507);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Cole-Cole";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// chart2
			// 
			chartArea4->AxisX->MajorGrid->Enabled = false;
			chartArea4->AxisY->MajorGrid->Enabled = false;
			chartArea4->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea4);
			this->chart2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart2->Location = System::Drawing::Point(3, 3);
			this->chart2->Name = L"chart2";
			series11->ChartArea = L"ChartArea1";
			series11->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series11->Name = L"Series1";
			series12->ChartArea = L"ChartArea1";
			series12->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series12->Name = L"Series2";
			this->chart2->Series->Add(series11);
			this->chart2->Series->Add(series12);
			this->chart2->Size = System::Drawing::Size(759, 501);
			this->chart2->TabIndex = 0;
			this->chart2->Text = L"chart2";
			this->chart2->Resize += gcnew System::EventHandler(this, &Form1::chart2_Resize);
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::Control;
			this->menuStrip1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->FileToolStripMenuItem, 
				this->helpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(792, 24);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Form1::menuStrip1_ItemClicked);
			// 
			// FileToolStripMenuItem
			// 
			this->FileToolStripMenuItem->Name = L"FileToolStripMenuItem";
			this->FileToolStripMenuItem->Size = System::Drawing::Size(35, 20);
			this->FileToolStripMenuItem->Text = L"File";
			this->FileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::plikToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->abooutToolStripMenuItem});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->helpToolStripMenuItem->Text = L"About";
			// 
			// abooutToolStripMenuItem
			// 
			this->abooutToolStripMenuItem->Name = L"abooutToolStripMenuItem";
			this->abooutToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->abooutToolStripMenuItem->Text = L"About";
			this->abooutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::abooutToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(792, 589);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Dielectric Fitter";
			this->ResizeEnd += gcnew System::EventHandler(this, &Form1::Form1_ResizeEnd);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart2))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 int i;
				 int size;
				 double c0,ep,eb;
				 MatrixXd parameters(4,1);

				 if (openFileDialog1->ShowDialog() == ::System::Windows::Forms::DialogResult::OK )
				 {
					 chart1->Series["Series1"]->Points->Clear();
					 chart2->Series["Series1"]->Points->Clear();
					 chart1->Series["Series2"]->Points->Clear();
					 chart2->Series["Series2"]->Points->Clear();
					 chart1->Series["Series3"]->Points->Clear();
					 chart1->Series["Series4"]->Points->Clear();
					 c0=(Convert::ToDouble(textBox1->Text));
					 double es,en,fp,a;
					 complex<double> d;
					 vector<double> Dataf;
					 vector<double> Dataep;
					 vector<double> Dataeb;
					 LoadDielectric(openFileDialog1->FileName,Dataf,Dataep,Dataeb);
					 //LoadDielectric("e:\\Data1.txt",Dataf,Dataep,Dataeb);
					 size=Dataf.size();
					 Normalize(Dataep,Dataeb,c0);
					 //cout<<"Rozmiar = "<<size<<endl;
					 for (i=1;i<=size-2;i++)
					 {
						 chart1->Series["Series1"]->Points->AddXY(log10(Dataf[i]),Dataep[i]);
						 chart1->Series["Series2"]->Points->AddXY(log10(Dataf[i]),-Dataeb[i]);
						 chart2->Series["Series1"]->Points->AddXY(Dataep[i],-Dataeb[i]);

					 }

					 es=123;//80; //25.49947;
					 en=45;//1.33;
					 fp=12345;
					 a=0.35;
					 parameters<<es,en,fp,a;
					 CalculateHessian(Dataf,Dataep,Dataeb,parameters);
//					 Fit( Dataf,Dataep,Dataeb,es,en,fp,a);
//					 FitA(Dataf,Dataep,Dataeb,es,en,fp,a);
//					 Fit( Dataf,Dataep,Dataeb,es,en,fp,a);
//					 FitA(Dataf,Dataep,Dataeb,es,en,fp,a);
//					 Fit( Dataf,Dataep,Dataeb,es,en,fp,a);
					 for (i=1;i<=size-2;i++)
					 {
						 d=en+(es-en)/(1.0+pow(ii*Dataf[i]/fp,1-a));
						 ep= std::real(d);
						 eb=-std::imag(d);
						 chart1->Series["Series3"]->Points->AddXY(log10(Dataf[i]),ep);
						 chart1->Series["Series4"]->Points->AddXY(log10(Dataf[i]),eb);
						 chart2->Series["Series2"]->Points->AddXY(ep,eb);
					 }
				 }
			  }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 vector<double> Dataf;
				 vector<double> Dataep;
				 vector<double> Dataeb;
				 double es,en,fp;
				 es=123;
				 en=45;
				 fp=12345;
				 LoadDielectric("e:\\Sheet1.dat",Dataf,Dataep,Dataeb);
				// TestFitA(Dataf,Dataep,Dataeb,es,en,fp,a);
			 }
private: System::Void chart1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void tabPage1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void plikToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void menuStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
		 }
private: System::Void chart2_Resize(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Form1_ResizeEnd(System::Object^  sender, System::EventArgs^  e) {
		
		 }
private: System::Void abooutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
};
}

