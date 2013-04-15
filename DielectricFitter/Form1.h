#include "Parser.h"
#include "Fitowanie.h"
#include <complex>
#include <intrin.h>
#include "About.h"
#include "Dense"
using  System::IO::StreamWriter;
using namespace System::Globalization;
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
size_t  Position,Positionfreq;
double vacuumcapacity=1.0;
const double pi  =3.1415926535897932384626433;
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
	private: System::Windows::Forms::Button^  LoadButton;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  FitButton;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  FileToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  abooutToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  tbeps;
	private: System::Windows::Forms::TextBox^  tbde1;
	private: System::Windows::Forms::TextBox^  tbf1;
	private: System::Windows::Forms::TextBox^  tba1;
	private: System::Windows::Forms::Button^  ChiSqrButton;
	private: System::Windows::Forms::ToolStripMenuItem^  loadFileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::Button^  PrevCurveButton;
	private: System::Windows::Forms::Button^  NextCurveButton;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  Fit2Button;
	private: System::Windows::Forms::TextBox^  tbde2;
	private: System::Windows::Forms::TextBox^  tbfp2;
	private: System::Windows::Forms::TextBox^  tba2;
	private: System::Windows::Forms::CheckBox^  TwoFunCheckBox;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart3;
	private: System::Windows::Forms::Button^  PlotButton;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart4;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ToolStripMenuItem^  writeTemperatureDependenciesToolStripMenuItem;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::ToolStripMenuItem^  impedanceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveTempImpedanceToolStripMenuItem;
	private: System::Windows::Forms::TabPage^  tabPage5;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart5;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TextBox^  textBox12;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TabPage^  tabPage6;
	private: System::Windows::Forms::TextBox^  textBoxheigth;

	private: System::Windows::Forms::TextBox^  textBoxradius;
	private: System::Windows::Forms::Button^  CalcGeomCap;
	private: System::Windows::Forms::Label^  CapacityLabel1;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  corgraphmax;
	private: System::Windows::Forms::TextBox^  corgraphmin;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Button^  toepsbutton;
	private: System::Windows::Forms::TextBox^  textBoxheight2;

	private: System::Windows::Forms::TextBox^  textBoxsurface;

	private: System::Windows::Forms::Button^  GeomButton2;
private: System::Windows::Forms::Label^  CapacityLabel2;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
private: System::Windows::Forms::Panel^  panel2;






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
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series10 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series11 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series12 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series13 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series14 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series15 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea5 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series16 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series17 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series18 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->LoadButton = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->FitButton = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tbeps = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->TwoFunCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tbde1 = (gcnew System::Windows::Forms::TextBox());
			this->tbf1 = (gcnew System::Windows::Forms::TextBox());
			this->tba1 = (gcnew System::Windows::Forms::TextBox());
			this->tbde2 = (gcnew System::Windows::Forms::TextBox());
			this->ChiSqrButton = (gcnew System::Windows::Forms::Button());
			this->tbfp2 = (gcnew System::Windows::Forms::TextBox());
			this->tba2 = (gcnew System::Windows::Forms::TextBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->chart3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->chart4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->chart5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->corgraphmax = (gcnew System::Windows::Forms::TextBox());
			this->corgraphmin = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->tabPage6 = (gcnew System::Windows::Forms::TabPage());
			this->CapacityLabel2 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->toepsbutton = (gcnew System::Windows::Forms::Button());
			this->textBoxheight2 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxsurface = (gcnew System::Windows::Forms::TextBox());
			this->GeomButton2 = (gcnew System::Windows::Forms::Button());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->CapacityLabel1 = (gcnew System::Windows::Forms::Label());
			this->CalcGeomCap = (gcnew System::Windows::Forms::Button());
			this->textBoxheigth = (gcnew System::Windows::Forms::TextBox());
			this->textBoxradius = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->FileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->writeTemperatureDependenciesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveTempImpedanceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->impedanceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->abooutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PrevCurveButton = (gcnew System::Windows::Forms::Button());
			this->NextCurveButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Fit2Button = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->PlotButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->panel2->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart2))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart3))->BeginInit();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart4))->BeginInit();
			this->tabPage5->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart5))->BeginInit();
			this->panel1->SuspendLayout();
			this->tabPage6->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// chart1
			// 
			this->chart1->BorderlineWidth = 0;
			this->chart1->BorderSkin->BorderColor = System::Drawing::Color::DimGray;
			this->chart1->BorderSkin->BorderWidth = 0;
			chartArea1->AxisX->Interval = 0.2;
			chartArea1->AxisX->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea1->AxisX->IntervalOffsetType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea1->AxisX->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea1->AxisX->IsMarginVisible = false;
			chartArea1->AxisX->IsStartedFromZero = false;
			chartArea1->AxisX->LabelStyle->Interval = 0;
			chartArea1->AxisX->MajorGrid->Enabled = false;
			chartArea1->AxisX->MajorTickMark->Interval = 0;
			chartArea1->AxisX->MajorTickMark->TickMarkStyle = System::Windows::Forms::DataVisualization::Charting::TickMarkStyle::AcrossAxis;
			chartArea1->AxisX->MaximumAutoSize = 90;
			chartArea1->AxisX->Title = L"log (frequency)";
			chartArea1->AxisX2->MajorGrid->Enabled = false;
			chartArea1->AxisY->IsStartedFromZero = false;
			chartArea1->AxisY->MajorGrid->Enabled = false;
			chartArea1->AxisY2->IsStartedFromZero = false;
			chartArea1->AxisY2->MajorGrid->Enabled = false;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			legend1->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Top;
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(3, 3);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series1->Color = System::Drawing::Color::Black;
			series1->Legend = L"Legend1";
			series1->Name = L"Eps\' experimental";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series2->Color = System::Drawing::Color::Red;
			series2->Legend = L"Legend1";
			series2->Name = L"Eps\'\' experimental";
			series2->YAxisType = System::Windows::Forms::DataVisualization::Charting::AxisType::Secondary;
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series3->Color = System::Drawing::Color::Black;
			series3->Legend = L"Legend1";
			series3->Name = L"Eps\' fit";
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series4->Color = System::Drawing::Color::Red;
			series4->Legend = L"Legend1";
			series4->Name = L"Eps\'\' fit";
			series4->YAxisType = System::Windows::Forms::DataVisualization::Charting::AxisType::Secondary;
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series5->Color = System::Drawing::Color::Red;
			series5->Legend = L"Legend1";
			series5->Name = L"Eps\'\' function 1";
			series5->YAxisType = System::Windows::Forms::DataVisualization::Charting::AxisType::Secondary;
			series6->ChartArea = L"ChartArea1";
			series6->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series6->Color = System::Drawing::Color::Red;
			series6->Legend = L"Legend1";
			series6->Name = L"Eps\'\' Function 2";
			series6->YAxisType = System::Windows::Forms::DataVisualization::Charting::AxisType::Secondary;
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Series->Add(series3);
			this->chart1->Series->Add(series4);
			this->chart1->Series->Add(series5);
			this->chart1->Series->Add(series6);
			this->chart1->Size = System::Drawing::Size(1086, 682);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			// 
			// LoadButton
			// 
			this->LoadButton->Location = System::Drawing::Point(4, 31);
			this->LoadButton->Name = L"LoadButton";
			this->LoadButton->Size = System::Drawing::Size(75, 23);
			this->LoadButton->TabIndex = 1;
			this->LoadButton->Text = L"Load";
			this->LoadButton->UseVisualStyleBackColor = true;
			this->LoadButton->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
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
			this->textBox1->Location = System::Drawing::Point(255, 32);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(25, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"1";
			// 
			// FitButton
			// 
			this->FitButton->Location = System::Drawing::Point(17, 240);
			this->FitButton->Name = L"FitButton";
			this->FitButton->Size = System::Drawing::Size(39, 23);
			this->FitButton->TabIndex = 3;
			this->FitButton->Text = L"Fit";
			this->FitButton->UseVisualStyleBackColor = true;
			this->FitButton->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->tabPage6);
			this->tabControl1->Location = System::Drawing::Point(0, 67);
			this->tabControl1->Margin = System::Windows::Forms::Padding(10);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1246, 720);
			this->tabControl1->TabIndex = 4;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->tableLayoutPanel2);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1238, 694);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Bode Plot";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				88.67172F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				11.32828F)));
			this->tableLayoutPanel2->Controls->Add(this->chart1, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->panel2, 1, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(1232, 688);
			this->tableLayoutPanel2->TabIndex = 1;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->button13);
			this->panel2->Controls->Add(this->label3);
			this->panel2->Controls->Add(this->tbeps);
			this->panel2->Controls->Add(this->label5);
			this->panel2->Controls->Add(this->label6);
			this->panel2->Controls->Add(this->label8);
			this->panel2->Controls->Add(this->Fit2Button);
			this->panel2->Controls->Add(this->label9);
			this->panel2->Controls->Add(this->label7);
			this->panel2->Controls->Add(this->TwoFunCheckBox);
			this->panel2->Controls->Add(this->label4);
			this->panel2->Controls->Add(this->tbde1);
			this->panel2->Controls->Add(this->tbf1);
			this->panel2->Controls->Add(this->tba1);
			this->panel2->Controls->Add(this->tbde2);
			this->panel2->Controls->Add(this->ChiSqrButton);
			this->panel2->Controls->Add(this->FitButton);
			this->panel2->Controls->Add(this->tbfp2);
			this->panel2->Controls->Add(this->tba2);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel2->Location = System::Drawing::Point(1095, 3);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(134, 682);
			this->panel2->TabIndex = 1;
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(17, 269);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(32, 23);
			this->button13->TabIndex = 30;
			this->button13->Text = L">>";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &Form1::button13_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(17, 26);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(20, 13);
			this->label3->TabIndex = 23;
			this->label3->Text = L"En";
			// 
			// tbeps
			// 
			this->tbeps->Location = System::Drawing::Point(56, 12);
			this->tbeps->Name = L"tbeps";
			this->tbeps->Size = System::Drawing::Size(78, 20);
			this->tbeps->TabIndex = 6;
			this->tbeps->Text = L"1";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(14, 75);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(22, 13);
			this->label5->TabIndex = 25;
			this->label5->Text = L"fp1";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(14, 101);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(19, 13);
			this->label6->TabIndex = 26;
			this->label6->Text = L"a1";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(14, 127);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(25, 13);
			this->label8->TabIndex = 27;
			this->label8->Text = L"de2";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(14, 175);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(19, 13);
			this->label9->TabIndex = 28;
			this->label9->Text = L"a2";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(14, 153);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(22, 13);
			this->label7->TabIndex = 27;
			this->label7->Text = L"fp2";
			// 
			// TwoFunCheckBox
			// 
			this->TwoFunCheckBox->AutoSize = true;
			this->TwoFunCheckBox->Location = System::Drawing::Point(17, 203);
			this->TwoFunCheckBox->Name = L"TwoFunCheckBox";
			this->TwoFunCheckBox->Size = System::Drawing::Size(100, 17);
			this->TwoFunCheckBox->TabIndex = 18;
			this->TwoFunCheckBox->Text = L"Use 2 functions";
			this->TwoFunCheckBox->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(14, 49);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(25, 13);
			this->label4->TabIndex = 24;
			this->label4->Text = L"de1";
			// 
			// tbde1
			// 
			this->tbde1->Location = System::Drawing::Point(56, 38);
			this->tbde1->Name = L"tbde1";
			this->tbde1->Size = System::Drawing::Size(78, 20);
			this->tbde1->TabIndex = 7;
			this->tbde1->Text = L"1";
			// 
			// tbf1
			// 
			this->tbf1->Location = System::Drawing::Point(56, 64);
			this->tbf1->Name = L"tbf1";
			this->tbf1->Size = System::Drawing::Size(78, 20);
			this->tbf1->TabIndex = 8;
			this->tbf1->Text = L"1";
			// 
			// tba1
			// 
			this->tba1->Location = System::Drawing::Point(56, 90);
			this->tba1->Name = L"tba1";
			this->tba1->Size = System::Drawing::Size(78, 20);
			this->tba1->TabIndex = 9;
			this->tba1->Text = L"1";
			// 
			// tbde2
			// 
			this->tbde2->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->tbde2->Location = System::Drawing::Point(56, 116);
			this->tbde2->Name = L"tbde2";
			this->tbde2->Size = System::Drawing::Size(78, 20);
			this->tbde2->TabIndex = 10;
			this->tbde2->Text = L"1";
			// 
			// ChiSqrButton
			// 
			this->ChiSqrButton->Location = System::Drawing::Point(59, 241);
			this->ChiSqrButton->Name = L"ChiSqrButton";
			this->ChiSqrButton->Size = System::Drawing::Size(75, 23);
			this->ChiSqrButton->TabIndex = 13;
			this->ChiSqrButton->Text = L"Chi2";
			this->ChiSqrButton->UseVisualStyleBackColor = true;
			this->ChiSqrButton->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// tbfp2
			// 
			this->tbfp2->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->tbfp2->Location = System::Drawing::Point(56, 142);
			this->tbfp2->Name = L"tbfp2";
			this->tbfp2->Size = System::Drawing::Size(78, 20);
			this->tbfp2->TabIndex = 11;
			this->tbfp2->Text = L"1";
			// 
			// tba2
			// 
			this->tba2->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->tba2->Location = System::Drawing::Point(56, 168);
			this->tba2->Name = L"tba2";
			this->tba2->Size = System::Drawing::Size(78, 20);
			this->tba2->TabIndex = 12;
			this->tba2->Text = L"1";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->chart2);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(1238, 694);
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
			series7->ChartArea = L"ChartArea1";
			series7->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series7->Color = System::Drawing::Color::Black;
			series7->Name = L"Series1";
			series8->ChartArea = L"ChartArea1";
			series8->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series8->Color = System::Drawing::Color::Red;
			series8->Name = L"Series2";
			series9->ChartArea = L"ChartArea1";
			series9->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series9->Color = System::Drawing::Color::Red;
			series9->Name = L"Series3";
			series10->ChartArea = L"ChartArea1";
			series10->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series10->Color = System::Drawing::Color::Red;
			series10->Name = L"Series4";
			this->chart2->Series->Add(series7);
			this->chart2->Series->Add(series8);
			this->chart2->Series->Add(series9);
			this->chart2->Series->Add(series10);
			this->chart2->Size = System::Drawing::Size(1232, 688);
			this->chart2->TabIndex = 0;
			this->chart2->Text = L"chart2";
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->chart3);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(1238, 694);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Parameters";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// chart3
			// 
			chartArea3->AxisX->MajorGrid->Enabled = false;
			chartArea3->AxisY->MajorGrid->Enabled = false;
			chartArea3->Name = L"ChartArea1";
			this->chart3->ChartAreas->Add(chartArea3);
			this->chart3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart3->Location = System::Drawing::Point(3, 3);
			this->chart3->Name = L"chart3";
			series11->ChartArea = L"ChartArea1";
			series11->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastPoint;
			series11->Color = System::Drawing::Color::Black;
			series11->Name = L"Series1";
			series11->YValuesPerPoint = 4;
			series12->ChartArea = L"ChartArea1";
			series12->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastPoint;
			series12->Color = System::Drawing::Color::Red;
			series12->Name = L"Series2";
			series13->ChartArea = L"ChartArea1";
			series13->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastPoint;
			series13->Color = System::Drawing::Color::ForestGreen;
			series13->Name = L"Series3";
			series13->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			this->chart3->Series->Add(series11);
			this->chart3->Series->Add(series12);
			this->chart3->Series->Add(series13);
			this->chart3->Size = System::Drawing::Size(1232, 688);
			this->chart3->TabIndex = 0;
			this->chart3->Text = L"chart3";
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->chart4);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(1238, 694);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Arrhenius";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// chart4
			// 
			chartArea4->AxisX->IsMarginVisible = false;
			chartArea4->AxisX->IsStartedFromZero = false;
			chartArea4->AxisX->MajorGrid->Enabled = false;
			chartArea4->AxisY->IsMarginVisible = false;
			chartArea4->AxisY->IsStartedFromZero = false;
			chartArea4->AxisY->MajorGrid->Enabled = false;
			chartArea4->AxisY2->IsMarginVisible = false;
			chartArea4->AxisY2->IsStartedFromZero = false;
			chartArea4->AxisY2->MajorGrid->Enabled = false;
			chartArea4->Name = L"ChartArea1";
			this->chart4->ChartAreas->Add(chartArea4);
			this->chart4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart4->Location = System::Drawing::Point(3, 3);
			this->chart4->Name = L"chart4";
			series14->ChartArea = L"ChartArea1";
			series14->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series14->Color = System::Drawing::Color::Red;
			series14->Name = L"Series1";
			series14->YValuesPerPoint = 2;
			series15->ChartArea = L"ChartArea1";
			series15->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series15->Color = System::Drawing::Color::ForestGreen;
			series15->Name = L"Series2";
			this->chart4->Series->Add(series14);
			this->chart4->Series->Add(series15);
			this->chart4->Size = System::Drawing::Size(1232, 688);
			this->chart4->TabIndex = 0;
			this->chart4->Text = L"chart4";
			// 
			// tabPage5
			// 
			this->tabPage5->Controls->Add(this->tableLayoutPanel1);
			this->tabPage5->Location = System::Drawing::Point(4, 22);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(1238, 694);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"Correction";
			this->tabPage5->UseVisualStyleBackColor = true;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->AutoSize = true;
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				100)));
			this->tableLayoutPanel1->Controls->Add(this->chart5, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->panel1, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1232, 688);
			this->tableLayoutPanel1->TabIndex = 2;
			// 
			// chart5
			// 
			chartArea5->AxisX->MajorGrid->Enabled = false;
			chartArea5->AxisY->IsStartedFromZero = false;
			chartArea5->AxisY->MajorGrid->Enabled = false;
			chartArea5->AxisY2->MajorGrid->Enabled = false;
			chartArea5->Name = L"ChartArea1";
			this->chart5->ChartAreas->Add(chartArea5);
			this->chart5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart5->Location = System::Drawing::Point(3, 33);
			this->chart5->Name = L"chart5";
			series16->ChartArea = L"ChartArea1";
			series16->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series16->Name = L"Series1";
			series17->ChartArea = L"ChartArea1";
			series17->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series17->Name = L"Series2";
			series18->ChartArea = L"ChartArea1";
			series18->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series18->Name = L"Series3";
			series18->YAxisType = System::Windows::Forms::DataVisualization::Charting::AxisType::Secondary;
			this->chart5->Series->Add(series16);
			this->chart5->Series->Add(series17);
			this->chart5->Series->Add(series18);
			this->chart5->Size = System::Drawing::Size(1226, 652);
			this->chart5->TabIndex = 1;
			this->chart5->Text = L"chart5";
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::Control;
			this->panel1->Controls->Add(this->corgraphmax);
			this->panel1->Controls->Add(this->corgraphmin);
			this->panel1->Controls->Add(this->label10);
			this->panel1->Controls->Add(this->button12);
			this->panel1->Controls->Add(this->button11);
			this->panel1->Controls->Add(this->button10);
			this->panel1->Controls->Add(this->textBox12);
			this->panel1->Controls->Add(this->button9);
			this->panel1->Controls->Add(this->textBox11);
			this->panel1->Controls->Add(this->textBox10);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(3, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1226, 24);
			this->panel1->TabIndex = 2;
			// 
			// corgraphmax
			// 
			this->corgraphmax->Location = System::Drawing::Point(835, 1);
			this->corgraphmax->Name = L"corgraphmax";
			this->corgraphmax->Size = System::Drawing::Size(100, 20);
			this->corgraphmax->TabIndex = 9;
			this->corgraphmax->Text = L"-10";
			// 
			// corgraphmin
			// 
			this->corgraphmin->Location = System::Drawing::Point(698, 0);
			this->corgraphmin->Name = L"corgraphmin";
			this->corgraphmin->Size = System::Drawing::Size(100, 20);
			this->corgraphmin->TabIndex = 8;
			this->corgraphmin->Text = L"-60";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(242, 5);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(24, 13);
			this->label10->TabIndex = 7;
			this->label10->Text = L"1/2";
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(116, 0);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(24, 23);
			this->button12->TabIndex = 6;
			this->button12->Text = L">";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &Form1::button12_Click);
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(85, 0);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(24, 23);
			this->button11->TabIndex = 5;
			this->button11->Text = L"<";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &Form1::button11_Click);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(147, 0);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(75, 23);
			this->button10->TabIndex = 4;
			this->button10->Text = L"Apply";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &Form1::button10_Click);
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(514, 1);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(100, 20);
			this->textBox12->TabIndex = 3;
			this->textBox12->Text = L"0,8";
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(3, 0);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(75, 23);
			this->button9->TabIndex = 2;
			this->button9->Text = L"Show";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &Form1::button9_Click);
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(408, 1);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(100, 20);
			this->textBox11->TabIndex = 1;
			this->textBox11->Text = L"0,3";
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(302, 1);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(100, 20);
			this->textBox10->TabIndex = 0;
			this->textBox10->Text = L"-52";
			// 
			// tabPage6
			// 
			this->tabPage6->Controls->Add(this->CapacityLabel2);
			this->tabPage6->Controls->Add(this->label14);
			this->tabPage6->Controls->Add(this->label13);
			this->tabPage6->Controls->Add(this->toepsbutton);
			this->tabPage6->Controls->Add(this->textBoxheight2);
			this->tabPage6->Controls->Add(this->textBoxsurface);
			this->tabPage6->Controls->Add(this->GeomButton2);
			this->tabPage6->Controls->Add(this->label12);
			this->tabPage6->Controls->Add(this->label11);
			this->tabPage6->Controls->Add(this->CapacityLabel1);
			this->tabPage6->Controls->Add(this->CalcGeomCap);
			this->tabPage6->Controls->Add(this->textBoxheigth);
			this->tabPage6->Controls->Add(this->textBoxradius);
			this->tabPage6->Location = System::Drawing::Point(4, 22);
			this->tabPage6->Name = L"tabPage6";
			this->tabPage6->Padding = System::Windows::Forms::Padding(3);
			this->tabPage6->Size = System::Drawing::Size(1238, 694);
			this->tabPage6->TabIndex = 5;
			this->tabPage6->Text = L"Sample Geometry";
			this->tabPage6->UseVisualStyleBackColor = true;
			// 
			// CapacityLabel2
			// 
			this->CapacityLabel2->AutoSize = true;
			this->CapacityLabel2->Location = System::Drawing::Point(315, 150);
			this->CapacityLabel2->Name = L"CapacityLabel2";
			this->CapacityLabel2->Size = System::Drawing::Size(41, 13);
			this->CapacityLabel2->TabIndex = 12;
			this->CapacityLabel2->Text = L"C0=-pF";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(37, 147);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(20, 13);
			this->label14->TabIndex = 11;
			this->label14->Text = L"S=";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(174, 147);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(19, 13);
			this->label13->TabIndex = 10;
			this->label13->Text = L"h=";
			// 
			// toepsbutton
			// 
			this->toepsbutton->Location = System::Drawing::Point(64, 201);
			this->toepsbutton->Name = L"toepsbutton";
			this->toepsbutton->Size = System::Drawing::Size(75, 23);
			this->toepsbutton->TabIndex = 9;
			this->toepsbutton->Text = L"Transform data";
			this->toepsbutton->UseVisualStyleBackColor = true;
			this->toepsbutton->Click += gcnew System::EventHandler(this, &Form1::toepsbutton_Click);
			// 
			// textBoxheight2
			// 
			this->textBoxheight2->Location = System::Drawing::Point(199, 143);
			this->textBoxheight2->Name = L"textBoxheight2";
			this->textBoxheight2->Size = System::Drawing::Size(100, 20);
			this->textBoxheight2->TabIndex = 8;
			this->textBoxheight2->Text = L"0,9";
			// 
			// textBoxsurface
			// 
			this->textBoxsurface->Location = System::Drawing::Point(64, 143);
			this->textBoxsurface->Name = L"textBoxsurface";
			this->textBoxsurface->Size = System::Drawing::Size(100, 20);
			this->textBoxsurface->TabIndex = 7;
			this->textBoxsurface->Text = L"32,5";
			// 
			// GeomButton2
			// 
			this->GeomButton2->Location = System::Drawing::Point(64, 88);
			this->GeomButton2->Name = L"GeomButton2";
			this->GeomButton2->Size = System::Drawing::Size(75, 23);
			this->GeomButton2->TabIndex = 6;
			this->GeomButton2->Text = L"Calculate";
			this->GeomButton2->UseVisualStyleBackColor = true;
			this->GeomButton2->Click += gcnew System::EventHandler(this, &Form1::GeomButton2_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(172, 44);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(19, 13);
			this->label12->TabIndex = 5;
			this->label12->Text = L"h=";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(40, 44);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(16, 13);
			this->label11->TabIndex = 4;
			this->label11->Text = L"r=";
			// 
			// CapacityLabel1
			// 
			this->CapacityLabel1->AutoSize = true;
			this->CapacityLabel1->Location = System::Drawing::Point(305, 44);
			this->CapacityLabel1->Name = L"CapacityLabel1";
			this->CapacityLabel1->Size = System::Drawing::Size(41, 13);
			this->CapacityLabel1->TabIndex = 3;
			this->CapacityLabel1->Text = L"C0=-pF";
			// 
			// CalcGeomCap
			// 
			this->CalcGeomCap->Location = System::Drawing::Point(64, 3);
			this->CalcGeomCap->Name = L"CalcGeomCap";
			this->CalcGeomCap->Size = System::Drawing::Size(75, 23);
			this->CalcGeomCap->TabIndex = 2;
			this->CalcGeomCap->Text = L"Calculate";
			this->CalcGeomCap->UseVisualStyleBackColor = true;
			this->CalcGeomCap->Click += gcnew System::EventHandler(this, &Form1::CalcGeomCap_Click);
			// 
			// textBoxheigth
			// 
			this->textBoxheigth->Location = System::Drawing::Point(199, 40);
			this->textBoxheigth->Name = L"textBoxheigth";
			this->textBoxheigth->Size = System::Drawing::Size(100, 20);
			this->textBoxheigth->TabIndex = 1;
			this->textBoxheigth->Text = L"0,8";
			// 
			// textBoxradius
			// 
			this->textBoxradius->Location = System::Drawing::Point(64, 40);
			this->textBoxradius->Name = L"textBoxradius";
			this->textBoxradius->Size = System::Drawing::Size(100, 20);
			this->textBoxradius->TabIndex = 0;
			this->textBoxradius->Text = L"3";
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::Control;
			this->menuStrip1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->FileToolStripMenuItem, 
				this->helpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1246, 24);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// FileToolStripMenuItem
			// 
			this->FileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->loadFileToolStripMenuItem, 
				this->writeTemperatureDependenciesToolStripMenuItem, this->saveToolStripMenuItem, this->saveTempImpedanceToolStripMenuItem, this->impedanceToolStripMenuItem, 
				this->exitToolStripMenuItem});
			this->FileToolStripMenuItem->Name = L"FileToolStripMenuItem";
			this->FileToolStripMenuItem->Size = System::Drawing::Size(35, 20);
			this->FileToolStripMenuItem->Text = L"File";
			// 
			// loadFileToolStripMenuItem
			// 
			this->loadFileToolStripMenuItem->Name = L"loadFileToolStripMenuItem";
			this->loadFileToolStripMenuItem->Size = System::Drawing::Size(244, 22);
			this->loadFileToolStripMenuItem->Text = L"Load file";
			this->loadFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::loadFileToolStripMenuItem_Click);
			// 
			// writeTemperatureDependenciesToolStripMenuItem
			// 
			this->writeTemperatureDependenciesToolStripMenuItem->Name = L"writeTemperatureDependenciesToolStripMenuItem";
			this->writeTemperatureDependenciesToolStripMenuItem->Size = System::Drawing::Size(244, 22);
			this->writeTemperatureDependenciesToolStripMenuItem->Text = L"Save Temperature Dependencies";
			this->writeTemperatureDependenciesToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::writeTemperatureDependenciesToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(244, 22);
			this->saveToolStripMenuItem->Text = L"Save Fit Parameters";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveToolStripMenuItem_Click);
			// 
			// saveTempImpedanceToolStripMenuItem
			// 
			this->saveTempImpedanceToolStripMenuItem->Name = L"saveTempImpedanceToolStripMenuItem";
			this->saveTempImpedanceToolStripMenuItem->Size = System::Drawing::Size(244, 22);
			this->saveTempImpedanceToolStripMenuItem->Text = L"Save temp. impedance";
			this->saveTempImpedanceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveTempImpedanceToolStripMenuItem_Click);
			// 
			// impedanceToolStripMenuItem
			// 
			this->impedanceToolStripMenuItem->Name = L"impedanceToolStripMenuItem";
			this->impedanceToolStripMenuItem->Size = System::Drawing::Size(244, 22);
			this->impedanceToolStripMenuItem->Text = L"Impedance";
			this->impedanceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::impedanceToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(244, 22);
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
			// PrevCurveButton
			// 
			this->PrevCurveButton->Location = System::Drawing::Point(89, 31);
			this->PrevCurveButton->Name = L"PrevCurveButton";
			this->PrevCurveButton->Size = System::Drawing::Size(24, 23);
			this->PrevCurveButton->TabIndex = 15;
			this->PrevCurveButton->Text = L"<";
			this->PrevCurveButton->UseVisualStyleBackColor = true;
			this->PrevCurveButton->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// NextCurveButton
			// 
			this->NextCurveButton->Location = System::Drawing::Point(119, 31);
			this->NextCurveButton->Name = L"NextCurveButton";
			this->NextCurveButton->Size = System::Drawing::Size(24, 23);
			this->NextCurveButton->TabIndex = 12;
			this->NextCurveButton->Text = L">";
			this->NextCurveButton->UseVisualStyleBackColor = true;
			this->NextCurveButton->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(149, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(13, 13);
			this->label1->TabIndex = 14;
			this->label1->Text = L"1";
			// 
			// Fit2Button
			// 
			this->Fit2Button->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Fit2Button->FlatAppearance->BorderSize = 0;
			this->Fit2Button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Fit2Button->Location = System::Drawing::Point(20, 361);
			this->Fit2Button->Name = L"Fit2Button";
			this->Fit2Button->Size = System::Drawing::Size(39, 23);
			this->Fit2Button->TabIndex = 14;
			this->Fit2Button->UseVisualStyleBackColor = false;
			this->Fit2Button->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(484, 55);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(42, 23);
			this->button7->TabIndex = 19;
			this->button7->Text = L"Store";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// textBox9
			// 
			this->textBox9->BackColor = System::Drawing::SystemColors::Control;
			this->textBox9->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox9->Location = System::Drawing::Point(1240, 12);
			this->textBox9->Multiline = true;
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(10, 13);
			this->textBox9->TabIndex = 20;
			this->textBox9->WordWrap = false;
			// 
			// PlotButton
			// 
			this->PlotButton->Location = System::Drawing::Point(422, 55);
			this->PlotButton->Name = L"PlotButton";
			this->PlotButton->Size = System::Drawing::Size(46, 23);
			this->PlotButton->TabIndex = 21;
			this->PlotButton->Text = L"Plot";
			this->PlotButton->UseVisualStyleBackColor = true;
			this->PlotButton->Click += gcnew System::EventHandler(this, &Form1::button8_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(214, 36);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(10, 13);
			this->label2->TabIndex = 22;
			this->label2->Text = L"-";
			// 
			// progressBar1
			// 
			this->progressBar1->Enabled = false;
			this->progressBar1->Location = System::Drawing::Point(119, 2);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(378, 23);
			this->progressBar1->Step = 1;
			this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->progressBar1->TabIndex = 29;
			this->progressBar1->Visible = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1246, 785);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->PlotButton);
			this->Controls->Add(this->textBox9);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->NextCurveButton);
			this->Controls->Add(this->PrevCurveButton);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->LoadButton);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Dielectric Fitter";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart2))->EndInit();
			this->tabPage3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart3))->EndInit();
			this->tabPage4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart4))->EndInit();
			this->tabPage5->ResumeLayout(false);
			this->tabPage5->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart5))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->tabPage6->ResumeLayout(false);
			this->tabPage6->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 
				 curve  SingleCurve;
				 MatrixXd parameters(4,1);
				 if (openFileDialog1->ShowDialog() == ::System::Windows::Forms::DialogResult::OK )
				 {
				 double c0;//,ep,eb;
				 int i,numload;
				 int size;
					 CurveSet.clear();
					 c0=(Convert::ToDouble(textBox1->Text));
					 complex<double> d;
					 numload=openFileDialog1->FileNames->Length;
					 //cout<<"Number of files to load "<<numload<<endl;
					 progressBar1->Value=0;
					 progressBar1->Visible=true;
					 for (i=0;i<numload;i++)
					 {
						 LoadDielectric(openFileDialog1->FileNames[i],SingleCurve.Dataf,SingleCurve.Dataep,SingleCurve.Dataeb,SingleCurve.temperature);
						 size=SingleCurve.Dataf.size();
						 Normalize(SingleCurve.Dataep,SingleCurve.Dataeb,c0);
						 SingleCurve.fitted=false;
						 CurveSet.push_back(SingleCurve);
						 cout << 100*i/numload<<"%"<<endl;
						 progressBar1->Value=100*(i+1)/numload;
					 }
					 label1->Text="1/"+CurveSet.size().ToString();
					 Position=1;
					 Positionfreq=1;
					 chart1->Series[0]->Points->Clear();
					 chart2->Series["Series1"]->Points->Clear();
					 chart1->Series[1]->Points->Clear();
					 chart2->Series["Series2"]->Points->Clear();
					 chart1->Series[2]->Points->Clear();
					 chart1->Series[3]->Points->Clear();
					 size=CurveSet[Position-1].Dataf.size();
					 label1->Text=Position.ToString()+"/"+CurveSet.size();
					 label2->Text=CurveSet[0].temperature.ToString();
					 progressBar1->Visible=false;
					 for (i=0;i<=size-1;i++)
					 {
						 chart1->Series[0]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),CurveSet[Position-1].Dataep[i]);
						 chart1->Series[1]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),-CurveSet[Position-1].Dataeb[i]);
						 chart2->Series[0]->Points->AddXY(CurveSet[Position-1].Dataep[i],-CurveSet[Position-1].Dataeb[i]);

					 }
				 }
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 MatrixXd parameters(4,1);
				 complex<double> d;
				 if (!TwoFunCheckBox->Checked){
				 chart1->Series[2]->Points->Clear();
				 chart1->Series[3]->Points->Clear();
				 chart2->Series["Series2"]->Points->Clear();
				 double es,en,fp,a,pom;
				 en=(Convert::ToDouble(tbeps->Text));
				 es=(Convert::ToDouble(tbde1->Text));
				 fp=(Convert::ToDouble(tbf1->Text));
				 a=(Convert::ToDouble(tba1->Text));
				 pom=en;
				 en=es+en;
				 es=pom;
				 parameters<<es,en,fp,a;
				 FitLM(CurveSet[Position-1].Dataf,CurveSet[Position-1].Dataep,CurveSet[Position-1].Dataeb,parameters);
				 es=parameters(0,0);
				 en=parameters(1,0);
				 fp=parameters(2,0);
				 a=parameters(3,0);
				 es=es-en;
				 tbeps->Text=en.ToString();
				 tbde1->Text=es.ToString();
				 tbf1->Text=fp.ToString();
				 tba1->Text=a.ToString();
				 CurveSet[Position-1].en=en;
				 CurveSet[Position-1].de1=es;
				 CurveSet[Position-1].fp1=fp;
				 CurveSet[Position-1].a1=a;
				 CurveSet[Position-1].fitted=true;
				 CurveSet[Position-1].de2=0;
				 CurveSet[Position-1].fp2=1;
				 CurveSet[Position-1].a2=0;
				 CurveSet[Position-1].twofunctions=false;
				 //					 cout << es <<" "<<en<<" "<<fp<<" "<<a<<std::endl;
				 /*for (i=0;i<=size-1;i++)
				 {
					 d=en+(es-en)/(1.0+pow(ii*CurveSet[Position-1].Dataf[i]/fp,1-a));
					 ep= std::real(d);
					 eb=-std::imag(d);
					 chart1->Series[2]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),ep);
					 chart1->Series[3]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),eb);
					 chart2->Series["Series2"]->Points->AddXY(ep,eb);
				 }*/
				 ChiSqrButton->PerformClick();
				 //PlotButton->PerformClick();
				 }
				 else Fit2Button->PerformClick();
			 }

private: System::Void abooutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		Form^ rgForm = gcnew About();
		rgForm->Show();			 
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			  double ep,ep1,ep2,eb,eb1,eb2,es,en,fp,f,a,maxf,minf,df,de2,fp2,a2;
				 int i,size;
				 MatrixXd parameters(4,1);
				 complex<double> d;
				 complex<double> d2;
				 complex<double> d1;
				 chart1->Series[2]->Points->Clear();
				 chart1->Series[3]->Points->Clear();
				 chart1->Series[4]->Points->Clear();
				 chart1->Series[5]->Points->Clear();
				 chart2->Series["Series2"]->Points->Clear();
				 chart2->Series["Series3"]->Points->Clear();
				 chart2->Series["Series4"]->Points->Clear();
				 size=CurveSet[Position-1].Dataf.size();
				 minf=CurveSet[Position-1].Dataf[size-1];
				 maxf=CurveSet[Position-1].Dataf[0];
				 df=log10(maxf)-log10(minf);
				 es=(Convert::ToDouble(tbeps->Text));
				 en=(Convert::ToDouble(tbde1->Text));
				 fp=(Convert::ToDouble(tbf1->Text));
				 a=(Convert::ToDouble(tba1->Text));
				 de2=(Convert::ToDouble(tbde2->Text));
				 fp2=(Convert::ToDouble(tbfp2->Text));
				 a2=(Convert::ToDouble(tba2->Text));
				 for (i=0;i<=100;i++)
				 {
					 f=log10(minf)+(i/100.0)*df;
					 if (!TwoFunCheckBox->Checked) 
					 {
						 d=es+en/(1.0+pow(ii*pow(10,f)/fp,1-a));
					 }
					 else d=es+en/(1.0+pow(ii*pow(10,f)/fp,1-a))+de2/(1.0+pow(ii*pow(10,f)/fp2,1-a2));
						 d1=en/(1.0+pow(ii*pow(10,f)/fp,1-a));
						 d2=de2/(1.0+pow(ii*pow(10,f)/fp2,1-a2));
					 ep= std::real(d);
					 eb=-std::imag(d);
					 eb1=-std::imag(d1);
					 eb2=-std::imag(d2);
					 ep1=std::real(d1)+es+de2;
					 ep2=std::real(d2)+es;
					 //cout <<i<<" "<<f <<endl;
					 chart1->Series[2]->Points->AddXY(f,ep);
					 chart1->Series[3]->Points->AddXY(f,eb);
					 chart1->Series[4]->Points->AddXY(f,eb1);
					 if (CurveSet[Position-1].twofunctions) chart1->Series[5]->Points->AddXY(f,eb2);
					 chart2->Series["Series2"]->Points->AddXY(ep,eb);
					 if (CurveSet[Position-1].twofunctions) chart2->Series["Series3"]->Points->AddXY(ep1,eb1);
					 if (CurveSet[Position-1].twofunctions) chart2->Series["Series4"]->Points->AddXY(ep2,eb2);
				 }
		 }
private: System::Void loadFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 LoadButton->PerformClick();
		 }
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 exit(0);
		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 int i,size;
			 if (Position<CurveSet.size()) Position++;
			 label1->Text=Position.ToString()+"/"+CurveSet.size();
			 this->Text=openFileDialog1->FileNames[Position-1];
			 chart1->Series[0]->Points->Clear();
			 chart2->Series["Series1"]->Points->Clear();
			 chart1->Series[1]->Points->Clear();
			 chart2->Series["Series2"]->Points->Clear();
			 chart2->Series["Series3"]->Points->Clear();
			 chart2->Series["Series4"]->Points->Clear();
			 chart1->Series[4]->Points->Clear();
			 chart1->Series[5]->Points->Clear();
			 chart1->Series[2]->Points->Clear();
			 chart1->Series[3]->Points->Clear();
			 label2->Text=CurveSet[Position-1].temperature.ToString();
			 if (CurveSet[Position-1].fitted){
				 tbeps->Text=CurveSet[Position-1].en.ToString();
				 tbde1->Text=CurveSet[Position-1].de1.ToString();
				 tbf1->Text=CurveSet[Position-1].fp1.ToString();
				 tba1->Text=CurveSet[Position-1].a1.ToString();
				 tbde2->Text=CurveSet[Position-1].de2.ToString();
				 tbfp2->Text=CurveSet[Position-1].fp2.ToString();
				 tba2->Text=CurveSet[Position-1].a2.ToString();
				 ChiSqrButton->PerformClick();
			 }
			 size=CurveSet[Position-1].Dataf.size();
			 for (i=0;i<=size-1;i++)
			 {
				 chart1->Series[0]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),CurveSet[Position-1].Dataep[i]);
				 chart1->Series[1]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),-CurveSet[Position-1].Dataeb[i]);
				 chart2->Series["Series1"]->Points->AddXY(CurveSet[Position-1].Dataep[i],-CurveSet[Position-1].Dataeb[i]);

			 }
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 		 int i,size;
			 if (Position>1) Position--;
			 this->Text=openFileDialog1->FileNames[Position-1];
			 label1->Text=Position.ToString()+"/"+CurveSet.size();
			  label2->Text=CurveSet[Position-1].temperature.ToString();
			 chart1->Series[0]->Points->Clear();
			  chart1->Series[4]->Points->Clear();
				 chart1->Series[5]->Points->Clear();
			 chart2->Series["Series1"]->Points->Clear();
			 chart1->Series[1]->Points->Clear();
			 chart2->Series["Series2"]->Points->Clear();
			 chart1->Series[2]->Points->Clear();
			 chart1->Series[3]->Points->Clear();
			 if (CurveSet[Position-1].fitted){
				 tbeps->Text=CurveSet[Position-1].en.ToString();
				 tbde1->Text=CurveSet[Position-1].de1.ToString();
				 tbf1->Text=CurveSet[Position-1].fp1.ToString();
				 tba1->Text=CurveSet[Position-1].a1.ToString();
				 tbde2->Text=CurveSet[Position-1].de2.ToString();
				 tbfp2->Text=CurveSet[Position-1].fp2.ToString();
				 tba2->Text=CurveSet[Position-1].a2.ToString();
				 ChiSqrButton->PerformClick();
			 }
			 size=CurveSet[Position-1].Dataf.size();
					  for (i=0;i<=size-1;i++)
					 {
						 chart1->Series[0]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),CurveSet[Position-1].Dataep[i]);
						 chart1->Series[1]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),-CurveSet[Position-1].Dataeb[i]);
						 chart2->Series["Series1"]->Points->AddXY(CurveSet[Position-1].Dataep[i],-CurveSet[Position-1].Dataeb[i]);

					 }

		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			 double es,de1,fp1,a1,de2,fp2,a2;
			 complex<double> d;
			 MatrixXd parameters(7,1);
			 chart1->Series[2]->Points->Clear();
			 chart1->Series[3]->Points->Clear();
			 chart2->Series["Series2"]->Points->Clear();
			 es=(Convert::ToDouble(tbeps->Text));
			 de1=(Convert::ToDouble(tbde1->Text));
			 fp1=(Convert::ToDouble(tbf1->Text));
			 a1=(Convert::ToDouble(tba1->Text));
			 de2=(Convert::ToDouble(tbde2->Text));
			 fp2=(Convert::ToDouble(tbfp2->Text));
			 a2=(Convert::ToDouble(tba2->Text));
			 parameters<<es,de1,fp1,a1,de2,fp2,a2;
			 FitLM2(CurveSet[Position-1].Dataf,CurveSet[Position-1].Dataep,CurveSet[Position-1].Dataeb,parameters);
			 es=parameters(0,0);
			 tbeps->Text=es.ToString();
			 de1=parameters(1,0);
			 tbde1->Text=de1.ToString();
			 fp1=parameters(2,0);
			 tbf1->Text=fp1.ToString();
			 a1=parameters(3,0);
			 tba1->Text=a1.ToString();
			 de2=parameters(4,0);
			 tbde2->Text=de2.ToString();
			 fp2=parameters(5,0);
			 tbfp2->Text=fp2.ToString();
			 a2=parameters(6,0);
			 tba2->Text=a2.ToString();
			 CurveSet[Position-1].en=es;
			 CurveSet[Position-1].de1=de1;
			 CurveSet[Position-1].fp1=fp1;
			 CurveSet[Position-1].a1=a1;
			 CurveSet[Position-1].fitted=true;
			 CurveSet[Position-1].de2=de2;
			 CurveSet[Position-1].fp2=fp2;
			 CurveSet[Position-1].a2=a2;
			 CurveSet[Position-1].twofunctions=true;
		/*	 for (i=0;i<=size-1;i++)
			 {
					 d=es+de1/(1.0+pow(ii*CurveSet[Position-1].Dataf[i]/fp1,1-a1))+de2/(1.0+pow(ii*CurveSet[Position-1].Dataf[i]/fp2,1-a2));
					 ep= std::real(d);
					 eb=-std::imag(d);
					 chart1->Series[2]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),ep);
					 chart1->Series[3]->Points->AddXY(log10(CurveSet[Position-1].Dataf[i]),eb);
					 chart2->Series["Series2"]->Points->AddXY(ep,eb);
				 }*/
			 ChiSqrButton->PerformClick();
			 //PlotButton->PerformClick();
		 }
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
			 int i,size;
			 size=CurveSet.size();
			 //temperature=CurveSet[Position-1].temperature;
			 //cout << temperature;
			 //textBox9->Text+=temperature.ToString()+" "+tbeps->Text+" "+tbde1->Text+" "+tbf1->Text+" "+tba1->Text+" "+tbde2->Text+" "+tbfp2->Text+" "+tba2->Text+System::Environment::NewLine;
			 textBox9->Text="";
			 for (i=0;i<size;i++){
				if(CurveSet[i].fitted) textBox9->Text+=CurveSet[i].temperature+" "+CurveSet[i].en+" "+CurveSet[i].de1+" "+CurveSet[i].fp1+" "+CurveSet[i].a1+" "+CurveSet[i].de2+" "+CurveSet[i].fp2+" "+CurveSet[i].a2+System::Environment::NewLine;
			 }

		 }
private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			button7->PerformClick();
			 if (saveFileDialog1->ShowDialog() == ::System::Windows::Forms::DialogResult::OK ){
				 StreamWriter^ sw = gcnew StreamWriter(saveFileDialog1->FileName);
				 sw->WriteLine(textBox9->Text);
				 sw->Close();
				 cout <<"Fit parameters saved";
			 }
		 }
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
			 chart3->Series["Series1"]->Points->Clear();
			 chart3->Series["Series2"]->Points->Clear();
			 chart4->Series["Series1"]->Points->Clear();
			 chart4->Series["Series2"]->Points->Clear();
			 chart3->Series["Series3"]->Points->Clear();
			 int i,size;
			 double temperature;
			 size=CurveSet.size();
			 //cout << temperature;
			 //textBox9->Text+=temperature.ToString()+" "+tbeps->Text+" "+tbde1->Text+" "+tbf1->Text+" "+tba1->Text+" "+tbde2->Text+" "+tbfp2->Text+" "+tba2->Text+System::Environment::NewLine;
			 for (i=0;i<size;i++){
				 if(CurveSet[i].fitted){
					 temperature=CurveSet[i].temperature;
					 chart3->Series["Series1"]->Points->AddXY(temperature,CurveSet[i].en);
					 chart3->Series["Series2"]->Points->AddXY(temperature,CurveSet[i].de1);
					 chart3->Series["Series3"]->Points->AddXY(temperature,CurveSet[i].de2);
					 chart4->Series["Series1"]->Points->AddXY(1.0/(temperature+273.15),log(CurveSet[i].fp1));
					 chart4->Series["Series2"]->Points->AddXY(1.0/(temperature+273.15),log(CurveSet[i].fp2));
				 }
			 }
		 }
private: System::Void writeTemperatureDependenciesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (saveFileDialog1->ShowDialog() == ::System::Windows::Forms::DialogResult::OK ){
			 			 size_t  i,j;
				 for (i=0;i<CurveSet[0].Dataf.size();i++)
				 {
					 StreamWriter^ sw = gcnew StreamWriter(saveFileDialog1->FileName+i.ToString()+".dat");
					 sw->WriteLine("Frequency = "+ CurveSet[0].Dataf[i]);
					 for (j=0;j<CurveSet.size();j++){
						 sw->WriteLine(CurveSet[j].temperature+" "+ CurveSet[j].Dataep[i]+" "+-CurveSet[j].Dataeb[i]);
					 }
					 sw->Close();
				 }
			 }
		 }
private: System::Void impedanceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 CultureInfo^ MyCI = gcnew CultureInfo( "en-US",false );
			 NumberFormatInfo^ nfi = MyCI->NumberFormat;
			 nfi->NumberDecimalSeparator = ".";
			 complex<double> eps;
			 complex<double> zs;
			 if (saveFileDialog1->ShowDialog() == ::System::Windows::Forms::DialogResult::OK ){
			size_t  i,j,size,size2;
			 double ep,eb;
			 size=CurveSet[0].Dataf.size();
			 size2=CurveSet.size();
			 for (j=0;j<size2;j++){
				 //cout << CurveSet[j].temperature <<" "<<  Correction(CurveSet[j].temperature) <<endl;
			 StreamWriter^ sw = gcnew StreamWriter(saveFileDialog1->FileName+j.ToString()+".dat");
			 sw->WriteLine("Temperature = "+ CurveSet[j].temperature);
			 sw->WriteLine("Freq. [Hz]\tZs' [Ohms]\tZs'' [Ohms]");
			 for (i=0;i<size;i++){
			 ep=CurveSet[j].Dataep[i];
			 eb=CurveSet[j].Dataeb[i];
			 eps=ep+ii*eb;
			 zs=(-ii*1.0/eps)/(vacuumcapacity*2.0*pi*CurveSet[j].Dataf[i]);
			 sw->WriteLine(CurveSet[j].Dataf[i].ToString("e6",nfi)+"\t"+real(zs).ToString("g6",nfi)+"\t"+imag(zs).ToString("g6",nfi)+"\t"+ep.ToString("g6",nfi)+"\t"+eb.ToString("g6",nfi));
			 //cout <<CurveSet[j].Dataf[i]<<" " <<real(zs)<< " "<<imag(zs)<<endl;
			 }
			 sw->Close();
			 }
			 
			 }
		 }
private: System::Void saveTempImpedanceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 complex<double> eps;
			 complex<double> zs;
			 			 CultureInfo^ MyCI = gcnew CultureInfo( "en-US",false );
			 NumberFormatInfo^ nfi = MyCI->NumberFormat;
			 nfi->NumberDecimalSeparator = ".";
			 if (saveFileDialog1->ShowDialog() == ::System::Windows::Forms::DialogResult::OK ){
			 size_t  i,j;
			 double ep,eb;
				 for (i=0;i<CurveSet[0].Dataf.size();i++)
				 {
					 StreamWriter^ sw = gcnew StreamWriter(saveFileDialog1->FileName+i.ToString()+".dat");
					 sw->WriteLine("Frequency = "+ CurveSet[0].Dataf[i]);
					 for (j=0;j<CurveSet.size();j++){
						 ep=CurveSet[j].Dataep[i];
						 eb=CurveSet[j].Dataeb[i];
						 eps=ep+ii*eb;
						 zs=(-ii*1.0/eps)/(vacuumcapacity*2.0*pi*CurveSet[j].Dataf[i]);
						 sw->WriteLine(CurveSet[j].temperature.ToString("g5",nfi)+" "+ real(zs).ToString("g6",nfi)+" "+imag(zs).ToString("g6",nfi)+" "+ep.ToString("g6",nfi)+" "+eb.ToString("g6",nfi));
					 }
					 sw->Close();
				 }
			 }
		 }
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
			 int i,size;
			 double temperature,midt,jump,scale,maxx,minx;
			 	 size=CurveSet.size();
				 label10->Text=Positionfreq.ToString();
				 chart5->Series["Series1"]->Points->Clear();
				 chart5->Series["Series2"]->Points->Clear();
				 chart5->Series["Series3"]->Points->Clear();
				 midt=(Convert::ToDouble(textBox10->Text));
				 scale=(Convert::ToDouble(textBox11->Text));
				 jump=(Convert::ToDouble(textBox12->Text));
				 minx=(Convert::ToDouble(corgraphmin->Text));
				 maxx=(Convert::ToDouble(corgraphmax->Text));
			 for (i=0;i<size;i++){
				 temperature=CurveSet[i].temperature;
				 if ((temperature > minx)&&(temperature<maxx)){
				 chart5->Series["Series1"]->Points->AddXY(temperature,CurveSet[i].Dataep[Positionfreq-1]);
				 chart5->Series["Series2"]->Points->AddXY(temperature,CurveSet[i].Dataep[Positionfreq-1]-Correction(temperature,midt,scale,jump));
				 chart5->Series["Series3"]->Points->AddXY(temperature,Correction(temperature,midt,scale,jump));
				 }
			 }
		 }
private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
			 int i,j,size,size2;
			 double temperature,midt,jump,scale;
			 size=CurveSet.size();
			 size2=CurveSet[0].Dataf.size();
			 midt=(Convert::ToDouble(textBox10->Text));
			 scale=(Convert::ToDouble(textBox11->Text));
			 jump=(Convert::ToDouble(textBox12->Text));
			 for (i=0;i<size;i++){
				 temperature=CurveSet[i].temperature;
				 for (j=0;j<size2;j++) CurveSet[i].Dataep[j]-=Correction(temperature,midt,scale,jump);
			 }
		 }
private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
			  if (Positionfreq>1) Positionfreq--;
			  button9->PerformClick();
		 }
private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) {
			   if (Positionfreq<CurveSet[0].Dataf.size()) Positionfreq++;
			   button9->PerformClick();
		 }
private: System::Void CalcGeomCap_Click(System::Object^  sender, System::EventArgs^  e) {
			 double r,d,c0;
			 r=(Convert::ToDouble(textBoxradius->Text));
			 d=(Convert::ToDouble(textBoxheigth->Text));
			 c0=8.85e-12*pi*r*1e-6*r/(d*1.0e-3);
			 vacuumcapacity=c0;
			 CapacityLabel1->Text="C0= "+(c0/1.0e-12).ToString("G5") + " pF";
		 }
private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
			 int i;
			 for (i=1;i<=20;i++){
				 NextCurveButton->PerformClick();
				 FitButton->PerformClick();
			 }
		 }

private: System::Void GeomButton2_Click(System::Object^  sender, System::EventArgs^  e) {
			  double r,d,c0;
			 r=(Convert::ToDouble(textBoxsurface->Text));
			 d=(Convert::ToDouble(textBoxheight2->Text));
			 c0=8.85e-12*r*1e-6/(d*1.0e-3);
			 vacuumcapacity=c0;
			 CapacityLabel2->Text="C0= "+(c0/1.0e-12).ToString("G5") + " pF";
		 }
private: System::Void toepsbutton_Click(System::Object^  sender, System::EventArgs^  e) {
			 size_t size,i;
			 size=CurveSet.size();
			 for (i=0;i<size;i++){
			 Normalize(CurveSet[i].Dataep,CurveSet[i].Dataeb,vacuumcapacity);
			 }
		 }
};
}

