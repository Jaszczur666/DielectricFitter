#include "Parser.h"
#include "Fitowanie.h"
#include <complex>
#include <intrin.h>
#include "About.h"
#include "Dense"
using Eigen::MatrixXd;
vector<double> Dataf;
vector<double> Dataep;
vector<double> Dataeb;
struct curve{
vector<double> Dataf;
vector<double> Dataep;
vector<double> Dataeb;
double temperature;
double en,de1,fp1,a1,de2,fp2,a2;
bool fitted;
bool twofunctions;
};
vector <curve> CurveSet;
int Position;
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
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::ToolStripMenuItem^  loadFileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::TextBox^  textBox9;

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
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
			this->loadFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->abooutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
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
			this->chart1->BorderlineWidth = 0;
			this->chart1->BorderSkin->BorderColor = System::Drawing::Color::DimGray;
			this->chart1->BorderSkin->BorderWidth = 0;
			chartArea1->AxisX->IsMarginVisible = false;
			chartArea1->AxisX->IsStartedFromZero = false;
			chartArea1->AxisX->LabelStyle->Interval = 0;
			chartArea1->AxisX->MajorGrid->Enabled = false;
			chartArea1->AxisX->MaximumAutoSize = 85;
			chartArea1->AxisX->Title = L"log (frequency)";
			chartArea1->AxisX2->MajorGrid->Enabled = false;
			chartArea1->AxisY->IsStartedFromZero = false;
			chartArea1->AxisY->MajorGrid->Enabled = false;
			chartArea1->AxisY2->IsStartedFromZero = false;
			chartArea1->AxisY2->MajorGrid->Enabled = false;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart1->Location = System::Drawing::Point(3, 3);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series1->Color = System::Drawing::Color::Black;
			series1->Name = L"Series1";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series2->Color = System::Drawing::Color::Red;
			series2->Name = L"Series2";
			series2->YAxisType = System::Windows::Forms::DataVisualization::Charting::AxisType::Secondary;
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series3->Color = System::Drawing::Color::Black;
			series3->Name = L"Series3";
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series4->Color = System::Drawing::Color::Red;
			series4->Name = L"Series4";
			series4->YAxisType = System::Windows::Forms::DataVisualization::Charting::AxisType::Secondary;
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Series->Add(series3);
			this->chart1->Series->Add(series4);
			this->chart1->Size = System::Drawing::Size(1420, 748);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &Form1::chart1_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(0, 23);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Load";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Filter = L"Dat file|*.dat|txt file|*.txt";
			this->openFileDialog1->FilterIndex = 2;
			this->openFileDialog1->Multiselect = true;
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(208, 23);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(68, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"0,4108e-12";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(282, 20);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(39, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Fit";
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
			this->tabControl1->Size = System::Drawing::Size(1434, 780);
			this->tabControl1->TabIndex = 4;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->chart1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1426, 754);
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
			this->tabPage2->Size = System::Drawing::Size(1604, 754);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Cole-Cole";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// chart2
			// 
			chartArea2->AxisX->MajorGrid->Enabled = false;
			chartArea2->AxisY->MajorGrid->Enabled = false;
			chartArea2->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea2);
			this->chart2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart2->Location = System::Drawing::Point(3, 3);
			this->chart2->Name = L"chart2";
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series5->Name = L"Series1";
			series6->ChartArea = L"ChartArea1";
			series6->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series6->Name = L"Series2";
			this->chart2->Series->Add(series5);
			this->chart2->Series->Add(series6);
			this->chart2->Size = System::Drawing::Size(1598, 748);
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
			this->menuStrip1->Size = System::Drawing::Size(1453, 24);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Form1::menuStrip1_ItemClicked);
			// 
			// FileToolStripMenuItem
			// 
			this->FileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->loadFileToolStripMenuItem, 
				this->exitToolStripMenuItem});
			this->FileToolStripMenuItem->Name = L"FileToolStripMenuItem";
			this->FileToolStripMenuItem->Size = System::Drawing::Size(35, 20);
			this->FileToolStripMenuItem->Text = L"File";
			this->FileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::plikToolStripMenuItem_Click);
			// 
			// loadFileToolStripMenuItem
			// 
			this->loadFileToolStripMenuItem->Name = L"loadFileToolStripMenuItem";
			this->loadFileToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->loadFileToolStripMenuItem->Text = L"Load file";
			this->loadFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::loadFileToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
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
			this->abooutToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->abooutToolStripMenuItem->Text = L"About";
			this->abooutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::abooutToolStripMenuItem_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(499, 22);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(78, 20);
			this->textBox2->TabIndex = 6;
			this->textBox2->Text = L"1";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(583, 22);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(78, 20);
			this->textBox3->TabIndex = 7;
			this->textBox3->Text = L"1";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(667, 22);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(78, 20);
			this->textBox4->TabIndex = 8;
			this->textBox4->Text = L"1";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(751, 22);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(78, 20);
			this->textBox5->TabIndex = 9;
			this->textBox5->Text = L"1";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(1159, 23);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 10;
			this->button3->Text = L"Chi2";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(85, 23);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(24, 23);
			this->button4->TabIndex = 11;
			this->button4->Text = L"<";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(115, 23);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(24, 23);
			this->button5->TabIndex = 12;
			this->button5->Text = L">";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(155, 30);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(13, 13);
			this->label1->TabIndex = 13;
			this->label1->Text = L"1";
			// 
			// button6
			// 
			this->button6->FlatAppearance->BorderSize = 0;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Location = System::Drawing::Point(327, 19);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(39, 23);
			this->button6->TabIndex = 14;
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(835, 22);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(100, 20);
			this->textBox6->TabIndex = 15;
			this->textBox6->Text = L"1";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(941, 21);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(100, 20);
			this->textBox7->TabIndex = 16;
			this->textBox7->Text = L"1";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(1047, 21);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(100, 20);
			this->textBox8->TabIndex = 17;
			this->textBox8->Text = L"1";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(384, 26);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(100, 17);
			this->checkBox1->TabIndex = 18;
			this->checkBox1->Text = L"Use 2 functions";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(327, 19);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(42, 23);
			this->button7->TabIndex = 19;
			this->button7->Text = L"Store";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(1240, 12);
			this->textBox9->Multiline = true;
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(203, 57);
			this->textBox9->TabIndex = 20;
			this->textBox9->WordWrap = false;
			this->textBox9->TextChanged += gcnew System::EventHandler(this, &Form1::textBox9_TextChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1453, 836);
			this->Controls->Add(this->textBox9);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
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
				 double c0,temperature;//,ep,eb;
				 curve  SingleCurve;
				 MatrixXd parameters(4,1);
				 temperature=0.0;
				 if (openFileDialog1->ShowDialog() == ::System::Windows::Forms::DialogResult::OK )
				 {
					 string name;
					 CurveSet.clear();
					 c0=(Convert::ToDouble(textBox1->Text));
					 complex<double> d;
					 cout<<"Number of files to load "<<openFileDialog1->FileNames->Length<<endl;
					 for (i=0;i<openFileDialog1->FileNames->Length;i++)
					 {
						 LoadDielectric(openFileDialog1->FileNames[i],SingleCurve.Dataf,SingleCurve.Dataep,SingleCurve.Dataeb,SingleCurve.temperature);
						 size=SingleCurve.Dataf.size();
						 Normalize(SingleCurve.Dataep,SingleCurve.Dataeb,c0);
						 SingleCurve.fitted=false;
						 CurveSet.push_back(SingleCurve);
					 }
					 label1->Text="1/"+CurveSet.size().ToString();
					 Position=1;
					 chart1->Series["Series1"]->Points->Clear();
					 chart2->Series["Series1"]->Points->Clear();
					 chart1->Series["Series2"]->Points->Clear();
					 chart2->Series["Series2"]->Points->Clear();
					 chart1->Series["Series3"]->Points->Clear();
					 chart1->Series["Series4"]->Points->Clear();
					 size=CurveSet[Position-1].Dataf.size();
					 for (i=0;i<=size-1;i++)
					 {
						 chart1->Series["Series1"]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),CurveSet[Position-1].Dataep[i]);
						 chart1->Series["Series2"]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),-CurveSet[Position-1].Dataeb[i]);
						 chart2->Series["Series1"]->Points->AddXY(CurveSet[Position-1].Dataep[i],-CurveSet[Position-1].Dataeb[i]);

					 }
				 }
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 double ep,eb,es,en,fp,a;
				 int i,size;
				 MatrixXd parameters(4,1);
				 complex<double> d;
				 if (!checkBox1->Checked){
				 chart1->Series["Series3"]->Points->Clear();
				 chart1->Series["Series4"]->Points->Clear();
				 chart2->Series["Series2"]->Points->Clear();
				 size=CurveSet[Position-1].Dataf.size();
				 es=(Convert::ToDouble(textBox2->Text));
				 en=(Convert::ToDouble(textBox3->Text));
				 fp=(Convert::ToDouble(textBox4->Text));
				 a=(Convert::ToDouble(textBox5->Text));
				 parameters<<es,en,fp,a;
				 FitLM(CurveSet[Position-1].Dataf,CurveSet[Position-1].Dataep,CurveSet[Position-1].Dataeb,parameters);
				 es=parameters(0,0);
				 textBox2->Text=es.ToString();
				 en=parameters(1,0);
				 textBox3->Text=en.ToString();
				 fp=parameters(2,0);
				 textBox4->Text=fp.ToString();
				 a=parameters(3,0);
				 textBox5->Text=a.ToString();
				 CurveSet[Position-1].en=en;
				 CurveSet[Position-1].de1=es-en;
				 CurveSet[Position-1].fp1=fp;
				 CurveSet[Position-1].a1=a;
				 CurveSet[Position-1].fitted=true;
				 CurveSet[Position-1].de2=0;
				 CurveSet[Position-1].fp2=1;
				 CurveSet[Position-1].a2=0;
				 CurveSet[Position-1].twofunctions=false;
				 //					 cout << es <<" "<<en<<" "<<fp<<" "<<a<<std::endl;
				 for (i=0;i<=size-1;i++)
				 {
					 d=en+(es-en)/(1.0+pow(ii*CurveSet[Position-1].Dataf[i]/fp,1-a));
					 ep= std::real(d);
					 eb=-std::imag(d);
					 chart1->Series["Series3"]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),ep);
					 chart1->Series["Series4"]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),eb);
					 chart2->Series["Series2"]->Points->AddXY(ep,eb);
				 }}
				 else button6->PerformClick();
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
		Form^ rgForm = gcnew About();
		rgForm->Show();			 
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			  double ep,eb,es,en,fp,f,a,maxf,minf,df,de2,fp2,a2;
				 int i,size;
				 MatrixXd parameters(4,1);
				 complex<double> d;
				 chart1->Series["Series3"]->Points->Clear();
				 chart1->Series["Series4"]->Points->Clear();
				 chart2->Series["Series2"]->Points->Clear();
				 size=CurveSet[Position-1].Dataf.size();
				 minf=CurveSet[Position-1].Dataf[size-1];
				 maxf=CurveSet[Position-1].Dataf[0];
				 df=log10(maxf)-log10(minf);
				 es=(Convert::ToDouble(textBox2->Text));
				 en=(Convert::ToDouble(textBox3->Text));
				 fp=(Convert::ToDouble(textBox4->Text));
				 a=(Convert::ToDouble(textBox5->Text));
				 de2=(Convert::ToDouble(textBox6->Text));
				 fp2=(Convert::ToDouble(textBox7->Text));
				 a2=(Convert::ToDouble(textBox8->Text));
				 for (i=0;i<=300;i++)
				 {
					 f=log10(minf)+(i/300.0)*df;
					 if (!checkBox1->Checked) 
					 {
						 d=en+(es-en)/(1.0+pow(ii*pow(10,f)/fp,1-a));
					 }
					 else d=es+en/(1.0+pow(ii*pow(10,f)/fp,1-a))+de2/(1.0+pow(ii*pow(10,f)/fp2,1-a2));
					 ep= std::real(d);
					 eb=-std::imag(d);
					 //cout <<i<<" "<<f <<endl;
					 chart1->Series["Series3"]->Points->AddXY(f,ep);
					 chart1->Series["Series4"]->Points->AddXY(f,eb);
					 chart2->Series["Series2"]->Points->AddXY(ep,eb);
				 }
		 }
private: System::Void loadFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 button1->PerformClick();
		 }
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 exit(0);
		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 int i,size;
			 if (Position<CurveSet.size()) Position++;
			 label1->Text=Position.ToString()+"/"+CurveSet.size();
			 chart1->Series["Series1"]->Points->Clear();
			 chart2->Series["Series1"]->Points->Clear();
			 chart1->Series["Series2"]->Points->Clear();
			 chart2->Series["Series2"]->Points->Clear();
			 chart1->Series["Series3"]->Points->Clear();
			 chart1->Series["Series4"]->Points->Clear();
			 if (CurveSet[Position-1].fitted){
				 textBox2->Text=CurveSet[Position-1].en.ToString();
				 textBox3->Text=CurveSet[Position-1].de1.ToString();
				 textBox4->Text=CurveSet[Position-1].fp1.ToString();
				 textBox5->Text=CurveSet[Position-1].a1.ToString();
				 textBox6->Text=CurveSet[Position-1].de2.ToString();
				 textBox7->Text=CurveSet[Position-1].fp2.ToString();
				 textBox8->Text=CurveSet[Position-1].a2.ToString();
				 button3->PerformClick();
			 }
			 size=CurveSet[Position-1].Dataf.size();
			 for (i=0;i<=size-1;i++)
			 {
				 chart1->Series["Series1"]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),CurveSet[Position-1].Dataep[i]);
				 chart1->Series["Series2"]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),-CurveSet[Position-1].Dataeb[i]);
				 chart2->Series["Series1"]->Points->AddXY(CurveSet[Position-1].Dataep[i],-CurveSet[Position-1].Dataeb[i]);

			 }
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 		 int i,size;
			 if (Position>1) Position--;
			 label1->Text=Position.ToString()+"/"+CurveSet.size();
			 chart1->Series["Series1"]->Points->Clear();
			 chart2->Series["Series1"]->Points->Clear();
			 chart1->Series["Series2"]->Points->Clear();
			 chart2->Series["Series2"]->Points->Clear();
			 chart1->Series["Series3"]->Points->Clear();
			 chart1->Series["Series4"]->Points->Clear();
			 if (CurveSet[Position-1].fitted){
				 textBox2->Text=CurveSet[Position-1].en.ToString();
				 textBox3->Text=CurveSet[Position-1].de1.ToString();
				 textBox4->Text=CurveSet[Position-1].fp1.ToString();
				 textBox5->Text=CurveSet[Position-1].a1.ToString();
				 textBox6->Text=CurveSet[Position-1].de2.ToString();
				 textBox7->Text=CurveSet[Position-1].fp2.ToString();
				 textBox8->Text=CurveSet[Position-1].a2.ToString();
				 button3->PerformClick();
			 }
			 size=CurveSet[Position-1].Dataf.size();
					  for (i=0;i<=size-1;i++)
					 {
						 chart1->Series["Series1"]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),CurveSet[Position-1].Dataep[i]);
						 chart1->Series["Series2"]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),-CurveSet[Position-1].Dataeb[i]);
						 chart2->Series["Series1"]->Points->AddXY(CurveSet[Position-1].Dataep[i],-CurveSet[Position-1].Dataeb[i]);

					 }

		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			 double es,de1,fp1,a1,de2,fp2,a2,ep,eb;
			 int i,size;
			 complex<double> d;
			 MatrixXd parameters(7,1);
			 chart1->Series["Series3"]->Points->Clear();
			 chart1->Series["Series4"]->Points->Clear();
			 chart2->Series["Series2"]->Points->Clear();
			 es=(Convert::ToDouble(textBox2->Text));
			 de1=(Convert::ToDouble(textBox3->Text));
			 fp1=(Convert::ToDouble(textBox4->Text));
			 a1=(Convert::ToDouble(textBox5->Text));
			 de2=(Convert::ToDouble(textBox6->Text));
			 fp2=(Convert::ToDouble(textBox7->Text));
			 a2=(Convert::ToDouble(textBox8->Text));
			 parameters<<es,de1,fp1,a1,de2,fp2,a2;
			 FitLM2(CurveSet[Position-1].Dataf,CurveSet[Position-1].Dataep,CurveSet[Position-1].Dataeb,parameters);
			 es=parameters(0,0);
			 textBox2->Text=es.ToString();
			 de1=parameters(1,0);
			 textBox3->Text=de1.ToString();
			 fp1=parameters(2,0);
			 textBox4->Text=fp1.ToString();
			 a1=parameters(3,0);
			 textBox5->Text=a1.ToString();
			 de2=parameters(4,0);
			 textBox6->Text=de2.ToString();
			 fp2=parameters(5,0);
			 textBox7->Text=fp2.ToString();
			 a2=parameters(6,0);
			 textBox8->Text=a2.ToString();
			 size=CurveSet[Position-1].Dataf.size();
			 CurveSet[Position-1].en=es;
			 CurveSet[Position-1].de1=de1;
			 CurveSet[Position-1].fp1=fp1;
			 CurveSet[Position-1].a1=a1;
			 CurveSet[Position-1].fitted=true;
			 CurveSet[Position-1].de2=de2;
			 CurveSet[Position-1].fp2=fp2;
			 CurveSet[Position-1].a2=a2;
			 CurveSet[Position-1].twofunctions=true;
			 for (i=0;i<=size-1;i++)
			 {
					 d=es+de1/(1.0+pow(ii*CurveSet[Position-1].Dataf[i]/fp1,1-a1))+de2/(1.0+pow(ii*CurveSet[Position-1].Dataf[i]/fp2,1-a2));
					 ep= std::real(d);
					 eb=-std::imag(d);
					 chart1->Series["Series3"]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),ep);
					 chart1->Series["Series4"]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),eb);
					 chart2->Series["Series2"]->Points->AddXY(ep,eb);
				 }
		 }
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
			 double temperature;
			 int i,size;
			 size=CurveSet.size();
			 //temperature=CurveSet[Position-1].temperature;
			 //cout << temperature;
			 //textBox9->Text+=temperature.ToString()+" "+textBox2->Text+" "+textBox3->Text+" "+textBox4->Text+" "+textBox5->Text+" "+textBox6->Text+" "+textBox7->Text+" "+textBox8->Text+System::Environment::NewLine;
			 for (i=0;i<size;i++){
				if(CurveSet[i].fitted) textBox9->Text+=CurveSet[i].temperature+" "+CurveSet[i].en+" "+CurveSet[i].de1+" "+CurveSet[i].fp1+" "+CurveSet[i].a1+" "+CurveSet[i].de2+" "+CurveSet[i].fp2+" "+CurveSet[i].a2+System::Environment::NewLine;
			 }

		 }
private: System::Void textBox9_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

