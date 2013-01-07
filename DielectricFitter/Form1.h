#include "Parser.h"
#include "Fitowanie.h"
#include <complex>

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
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea1->AxisX->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea1->AxisX->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea1->AxisX->IsMarginVisible = false;
			chartArea1->AxisX->IsStartedFromZero = false;
			chartArea1->AxisX->LabelStyle->Interval = 0;
			chartArea1->AxisX->LabelStyle->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Auto;
			chartArea1->AxisX->MajorGrid->Enabled = false;
			chartArea1->AxisX->MaximumAutoSize = 85;
			chartArea1->AxisX->Title = L"log (Czêstotliwoœæ)";
			chartArea1->AxisX2->MajorGrid->Enabled = false;
			chartArea1->AxisY->IsStartedFromZero = false;
			chartArea1->AxisY->MajorGrid->Enabled = false;
			chartArea1->AxisY2->IsStartedFromZero = false;
			chartArea1->AxisY2->MajorGrid->Enabled = false;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->Location = System::Drawing::Point(7, 63);
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
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Color = System::Drawing::Color::Black;
			series3->Name = L"Series3";
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Color = System::Drawing::Color::Red;
			series4->Name = L"Series4";
			series4->YAxisType = System::Windows::Forms::DataVisualization::Charting::AxisType::Secondary;
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Series->Add(series3);
			this->chart1->Series->Add(series4);
			this->chart1->Size = System::Drawing::Size(770, 496);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &Form1::chart1_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(7, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(53, 21);
			this->button1->TabIndex = 1;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(83, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(106, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"0,4108e-12";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(281, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(792, 573);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->chart1);
			this->Name = L"Form1";
			this->Text = L"Dielectric Fitter";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
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

				  /* if (openFileDialog1->ShowDialog() == ::System::Windows::Forms::DialogResult::OK )
      {*/
	chart1->Series["Series1"]->Points->Clear();
	chart1->Series["Series2"]->Points->Clear();
	chart1->Series["Series3"]->Points->Clear();
	chart1->Series["Series4"]->Points->Clear();
	c0=(Convert::ToDouble(textBox1->Text));
	double es,en,fp,a;
	complex<double> d;
	vector<double> Dataf;
	vector<double> Dataep;
	vector<double> Dataeb;
    /*LoadDielectric(openFileDialog1->FileName,Dataf,Dataep,Dataeb);
	*/
	LoadDielectric("e:\\Data1.txt",Dataf,Dataep,Dataeb);
	size=Dataf.size();
	Normalize(Dataep,Dataeb,c0);
	//cout<<"Rozmiar = "<<size<<endl;
	for (i=1;i<=size-2;i++)
	{
		//cout << i <<";"<<Dataep[i]<<endl;
	chart1->Series["Series1"]->Points->AddXY(log10(Dataf[i]),Dataep[i]);
	chart1->Series["Series2"]->Points->AddXY(log10(Dataf[i]),-Dataeb[i]);
	
	}
	//Fit( Dataf,Dataep,Dataeb,25.61584,24.89592,710729.67865,0.34906 );
	es=80;//80; //25.49947;
	en=1.33;//1.33;
	fp=45e3;
	a=0;
//	a=0;
	TestFitF( Dataf,Dataep,Dataeb,es,en,fp,a);
		for (i=1;i<=size-2;i++)
	{
	d=en+(es-en)/(1.0+pow(ii*Dataf[i]/fp,1-a));
//	d=en+(es-en)/(1.0+pow(std::complex <double>(0.0,1.0)*Dataf[i]/fp,1-a));
	ep= std::real(d);
	eb=-std::imag(d);
	chart1->Series["Series3"]->Points->AddXY(log10(Dataf[i]),ep);
	chart1->Series["Series4"]->Points->AddXY(log10(Dataf[i]),eb);
	  }
				  // }
				   

			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void chart1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

