#pragma once
#include "stdafx.h"

namespace MandelbrotSet_boost {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
    using namespace System::Data;
	using namespace System::Drawing;

   
    int MaxIters = 100;
	int save = -1;
	

	public value class PointD
	{ public:
		double X; double Y; 
	};
	
	

	/// <summary>
	/// Сводка для Form1
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:
		double Xmin; double Xmax; double Ymin; double Ymax;
		//centre of the picture
		double Xcentre, Ycentre;
    
	private:
		//to colour the edge of the set or not
		int valColoured;
		//distance from the centre
		double dist;
		//is the centre on the axis-X
		bool isSymmetric;
		Graphics ^G;
		//for painting the panel with white
		SolidBrush ^B;
		double HeightMin1;
		//array of 128 shades
		array<Color> ^shades128;
		//array of 256 shades
		array<Color> ^shades256;
		//array of 512 shades
		array<Color> ^shades512;
		//array of 1024 shades
		array<Color> ^shades1024;
		//array of 2048 shades
		array<Color> ^shades2048;
		//array of 4096 shades
		array<Color> ^shades4096;


	private: System::Windows::Forms::Button^  butPrint;
	private: System::Windows::Forms::Label^  label1;


	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;

	private: System::Windows::Forms::NumericUpDown^  numIters;
			 System::Drawing::Bitmap ^bmp;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Label^  labelCentre;

	private: System::Windows::Forms::NumericUpDown^  NumCentreY;

	private: System::Windows::Forms::NumericUpDown^  NumCentreX;
	private: System::Windows::Forms::Label^  labelDist;
	private: System::Windows::Forms::NumericUpDown^  numericDist;
	private: System::Windows::Forms::ComboBox^  comboBox1;


	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;

	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			Xmin = -2; Xmax = 2; Ymin = -2; Ymax = 2;
			Xcentre = Ycentre = 0.0;
			dist = 2.0;
			
			//white edge
			valColoured = 0;
			isSymmetric = true;
			B = gcnew SolidBrush(Color::White);
			HeightMin1 = panel1->Height - 1;
			
			shades1024 = setShades(1);
			shades512 = setShades(2);
			shades256 = setShades(4);
			shades128 = setShades(8);

			shades2048 = doubleCopyOf(shades1024);
			shades4096 = doubleCopyOf(shades2048);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	 
	private: array<Color>^ setShades(int step){
				array<Color> ^shades = gcnew array<Color>(1024/step);
				int r = 0; 
				int g; 
				int b = 255;
				int i = 0;

				for(g = 0; g < 256; g+=step) { //from blue to light blue
					shades[i] = Color::FromArgb(r, g, b);
					i++;
				}
				r = g = 255;
				for(b = 255; b >=0; b-=step) { //from white to yellow
					shades[i] = Color::FromArgb(r, g, b);
					i++;
				}
				b = 0;
				for(g = 254; g >= 127; g-=step) { //from yellow to orange
					shades[i] = Color::FromArgb(r, g, b);
					i++;
				}
				for(r = 255, g = 127; r >= 128; r-=step, g-=step) { //from orange to brown?
					shades[i] = Color::FromArgb(r, g, b);
					i++;
				}
				r = 128; g = 0;
				for(b = 0; b < 256; b+=step) { //from brown to dark violet?
					shades[i] = Color::FromArgb(r, g, b);
					i++;
				}

				return shades;
			 }

	private: array<Color>^ doubleCopyOf(array<Color>^ shades2) {
				int k = shades2->Length*2;
				array<Color> ^shades = gcnew array<Color>(k);
				for(int i = 0, j = 0; j < k/2; i+=2, j++)
					shades[i] = shades[i+1] = shades2[j];

				return shades;
			 }
	/*
	 private: array<Color>^ halfCopyOf(array<Color>^ shades2) {
				int k = shades2->Length/2;
				array<Color> ^shades = gcnew array<Color>(k);
				for(int i = 0, j=0; i < k; i++, j+=2)
					shades[i] = shades2[j];

				return shades;
	 }*/

	private: System::Windows::Forms::Panel^  panel1;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->butPrint = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->numIters = (gcnew System::Windows::Forms::NumericUpDown());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->labelDist = (gcnew System::Windows::Forms::Label());
			this->numericDist = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumCentreY = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumCentreX = (gcnew System::Windows::Forms::NumericUpDown());
			this->labelCentre = (gcnew System::Windows::Forms::Label());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numIters))->BeginInit();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericDist))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NumCentreY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NumCentreX))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->panel1->Location = System::Drawing::Point(12, 27);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(800, 800);
			this->panel1->TabIndex = 1;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel1_Paint);
			// 
			// butPrint
			// 
			this->butPrint->Location = System::Drawing::Point(19, 242);
			this->butPrint->Name = L"butPrint";
			this->butPrint->Size = System::Drawing::Size(71, 19);
			this->butPrint->TabIndex = 2;
			this->butPrint->Text = L"Print!";
			this->butPrint->UseVisualStyleBackColor = true;
			this->butPrint->Click += gcnew System::EventHandler(this, &Form1::butPrint_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(81, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Number of iter-s";
			// 
			// numIters
			// 
			this->numIters->Location = System::Drawing::Point(19, 30);
			this->numIters->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {40000, 0, 0, 0});
			this->numIters->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->numIters->Name = L"numIters";
			this->numIters->Size = System::Drawing::Size(100, 20);
			this->numIters->TabIndex = 0;
			this->numIters->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->numIters->ValueChanged += gcnew System::EventHandler(this, &Form1::numIters_ValueChanged);
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->comboBox1);
			this->panel2->Controls->Add(this->labelDist);
			this->panel2->Controls->Add(this->numericDist);
			this->panel2->Controls->Add(this->NumCentreY);
			this->panel2->Controls->Add(this->NumCentreX);
			this->panel2->Controls->Add(this->labelCentre);
			this->panel2->Controls->Add(this->numIters);
			this->panel2->Controls->Add(this->label1);
			this->panel2->Controls->Add(this->butPrint);
			this->panel2->Location = System::Drawing::Point(818, 27);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(287, 797);
			this->panel2->TabIndex = 2;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"No colours", L"7-coloured", L"128 shades", L"Complex shades"});
			this->comboBox1->Location = System::Drawing::Point(19, 184);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(111, 21);
			this->comboBox1->TabIndex = 9;
			this->comboBox1->Text = L"No colours";
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox1_SelectedIndexChanged);
			// 
			// labelDist
			// 
			this->labelDist->AutoSize = true;
			this->labelDist->Location = System::Drawing::Point(16, 120);
			this->labelDist->Name = L"labelDist";
			this->labelDist->Size = System::Drawing::Size(49, 13);
			this->labelDist->TabIndex = 8;
			this->labelDist->Text = L"Distance";
			this->labelDist->Click += gcnew System::EventHandler(this, &Form1::labelDist_Click);
			// 
			// numericDist
			// 
			this->numericDist->DecimalPlaces = 15;
			this->numericDist->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 983040});
			this->numericDist->Location = System::Drawing::Point(19, 145);
			this->numericDist->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			this->numericDist->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 983040});
			this->numericDist->Name = L"numericDist";
			this->numericDist->Size = System::Drawing::Size(125, 20);
			this->numericDist->TabIndex = 7;
			this->numericDist->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, 0});
			this->numericDist->ValueChanged += gcnew System::EventHandler(this, &Form1::numericDist_ValueChanged);
			// 
			// NumCentreY
			// 
			this->NumCentreY->DecimalPlaces = 15;
			this->NumCentreY->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 917504});
			this->NumCentreY->Location = System::Drawing::Point(152, 81);
			this->NumCentreY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, 0});
			this->NumCentreY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, System::Int32::MinValue});
			this->NumCentreY->Name = L"NumCentreY";
			this->NumCentreY->Size = System::Drawing::Size(125, 20);
			this->NumCentreY->TabIndex = 6;
			this->NumCentreY->ValueChanged += gcnew System::EventHandler(this, &Form1::NumCentreY_ValueChanged);
			// 
			// NumCentreX
			// 
			this->NumCentreX->DecimalPlaces = 15;
			this->NumCentreX->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 917504});
			this->NumCentreX->Location = System::Drawing::Point(19, 81);
			this->NumCentreX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, 0});
			this->NumCentreX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, System::Int32::MinValue});
			this->NumCentreX->Name = L"NumCentreX";
			this->NumCentreX->Size = System::Drawing::Size(125, 20);
			this->NumCentreX->TabIndex = 5;
			this->NumCentreX->ValueChanged += gcnew System::EventHandler(this, &Form1::NumCentreX_ValueChanged);
			// 
			// labelCentre
			// 
			this->labelCentre->AutoSize = true;
			this->labelCentre->Location = System::Drawing::Point(20, 60);
			this->labelCentre->Name = L"labelCentre";
			this->labelCentre->Size = System::Drawing::Size(64, 13);
			this->labelCentre->TabIndex = 3;
			this->labelCentre->Text = L"Centre(X, Y)";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripMenuItem1, 
				this->saveToolStripMenuItem, this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(95, 6);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(98, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(98, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->aboutToolStripMenuItem});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(116, 22);
			this->aboutToolStripMenuItem->Text = L"About...";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutToolStripMenuItem_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
				this->helpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1105, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Form1::menuStrip1_ItemClicked);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->DefaultExt = L"png";
			this->saveFileDialog1->Filter = L"PNG images|*.png|BMP images|*.bmp|All files|*.*";
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::saveFileDialog1_FileOk);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1105, 830);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"MandelbrotSet_boost";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numIters))->EndInit();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericDist))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NumCentreY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NumCentreX))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: 
  System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
  { this->Close(); }
  
  System::Void ToScreen(PointD W, Point &S) { 
	  S.X = panel1->Width*(W.X  - Xmin)/(Xmax-Xmin);
      S.Y = panel1->Height*(Ymax - W.Y)/(Ymax-Ymin);
  }

  System::Void ToWorld(Point S, PointD &W) {
		W.X = S.X*(Xmax-Xmin)/panel1->Width + Xmin;
		W.Y = S.Y*(Ymin-Ymax)/panel1->Height + Ymax;
  }

private: System::Void numIters_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			MaxIters = Decimal::ToInt32(numIters->Value);
	     }

private: System::Void butPrint_Click(System::Object^  sender, System::EventArgs^  e) {
		    save = 1;
			this->Refresh();
		 }

private: bool isInsideMainCardioid(PointD W) {
			 //determine distance and angle of the point
			double wXrepl = W.X - 0.25;
			double roW = pow(wXrepl*wXrepl + W.Y*W.Y, 0.5);
			double theta = atan2(W.Y, wXrepl);
			//cardioid in polar coordinate system
			double roCard = 0.5 - 0.5*cos(theta);

			return (roW > roCard ? false : true);
		 }

private: System::Drawing::Color setColorOfOuterPixel(int k) {
			 int num = k%7;
			
			 Color c;
			 //colors for outer points of Mandelbrot Set
			 switch(num) {
				case 0:
					c = Color::Red;
					break;
                case 1:
					c = Color::Orange;
					break;
				case 2:
					c = Color::Yellow;
					break;
				case 3:
					c = Color::Green;
					break;
				case 4:
					c = Color::LightBlue;
					break;
				case 5:
					c = Color::Blue;
					break;
				case 6:
					c = Color::Purple;
					break;
				default:
					c = Color::White;
					break;
			 }
							
			 return c;
		 }

private: System::Drawing::Color setShade(int k) {
			Color c;
			
			if(k < 128)
				c = shades128[k%128];
			else if(k < 384) {
				k -= 128;
				c = shades256[k%256];
			}
			else if(k < 896) {
				k -= 384;
				c = shades512[k%512];
			}
			else if(k < 1920){
				k -= 896;
				c = shades1024[k%1024];
			}
			else if(k < 3968) {
				k -= 1920;
				c = shades2048[k%2048];
			}
			else if(k < 8064) {
				k -= 3968;
				c = shades4096[k%4096];
			}
			else{
				k -= 8064;
				c = shades4096[k%4096];
			}
				
			return c;
		 }

private: System::Void buildMandelbrotSet(){
			 bmp = gcnew Bitmap(panel1->Width, panel1->Height);

			 int height = panel1->Height;
			 if(isSymmetric)
				 height *= 0.5;

			 int width = panel1->Width;
			 Point S;
			 PointD W;
			
			 //real and imaginary parts of complex number z'n'
			 double xCur, yCur;
			 //real and imaginary parts of complex number z'n+1'
			 double xNext, yNext;
			
			 //pixel is owned by the Mandelbrot Set
			 bool isInside = true;
			 double sqrModZnext;

			 for(int i = 0; i < width; i++) {
				 for(int j = 0; j < height; j++) {
					S.X = i; S.Y = j;
					ToWorld(S, W);
					
					//complex number c (with |c|>2) isn't owned by the Mandelbrot Set
					double sqrModC = W.X*W.X + W.Y*W.Y;
					//it's better not to take the square root
					if(sqrModC > 4.0)
						continue;
					
					xCur = 0.0; 
					yCur = 0.0;
					
					Color co;

					//it's faster to determine if the pixel is inside of the main cardioid
					if(!this->isInsideMainCardioid(W)){
						for(int k = 0; k < MaxIters; k++) {
							xNext = xCur*xCur - yCur*yCur + W.X;
							yNext = 2*xCur*yCur + W.Y;
							
							//in this case the set of zn doesn't remain bounded
							sqrModZnext = xNext*xNext + yNext*yNext;
							if(sqrModZnext > 4.0){
								isInside = false;
								if(valColoured != 0) { 
									//colouring the outer pixels
									if(valColoured == 1)
										co = setColorOfOuterPixel(k); //with 7 colours
									else if(valColoured == 2) //with 128 shades
										co = shades128[k%(shades128->Length)];
									else if(valColoured == 3) //with complex shades
										co = setShade(k);

									bmp->SetPixel(i, j, co);

									if(isSymmetric)
										bmp->SetPixel(i, this->HeightMin1 - j, co);
								}
								break;
							}

							xCur = xNext;
							yCur = yNext;
						}
					}

					if(isInside){
						bmp->SetPixel(i, j, Color::Black);
						if(isSymmetric)
							bmp->SetPixel(i, this->HeightMin1 - j, Color::Black);
					}
						
					isInside = true;
				 }
			  }
		 }

private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			G = e->Graphics;

	        G->FillRectangle(B, 0, 0, panel1->Width, panel1->Height);
			buildMandelbrotSet();
			G->DrawImage(bmp, 0, 0);
		 }

private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			MessageBox::Show("This program was created by Ivanov Artyom.", "About program");
		 }

private: System::Void menuStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
		 }

private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(save == 1)
			     saveFileDialog1->ShowDialog();
		 }
private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 bmp->Save(saveFileDialog1->FileName);
		 }

private: System::Void setArea() {
			 Xmin = Xcentre-dist;
			 Xmax = Xcentre+dist;
			 Ymin = Ycentre-dist;
			 Ymax = Ycentre+dist;
		 }

private: System::Void NumCentreX_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 Xcentre = Decimal::ToDouble(NumCentreX->Value);
			 this->setArea();
		 }
private: System::Void NumCentreY_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 Ycentre = Decimal::ToDouble(NumCentreY->Value);
			 
			 isSymmetric = ((Ycentre == 0.0) ? true : false);
			
		     this->setArea();
		 }
private: System::Void numericDist_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 dist = Decimal::ToDouble(numericDist->Value);
			 this->setArea();
		 }
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			  String^ text = comboBox1->Text;
			 if(text->Contains("No colours")){
				valColoured = 0;
			 } else if(text->Contains("7-coloured")){
				valColoured = 1;
			 }else if(text->Contains("128 shades")){
				valColoured = 2;
			 } else if(text->Contains("Complex shades")){
				valColoured = 3;
			 } 
		 }
private: System::Void labelDist_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};

}


