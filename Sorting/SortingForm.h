#pragma once

namespace Sort {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Sorting
	/// </summary>
	public ref class Sorting : public System::Windows::Forms::Form
	{
	public:
		Sorting(void)
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
		~Sorting()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:

	protected:

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Button^ buttonSortStep;
	private: System::Windows::Forms::Label^ labelIndex;
	private: System::Windows::Forms::Timer^ MoveTimer;
	private: System::ComponentModel::IContainer^ components;


	protected:

	protected:

	protected:







	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->buttonSortStep = (gcnew System::Windows::Forms::Button());
			this->labelIndex = (gcnew System::Windows::Forms::Label());
			this->MoveTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 460);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(478, 196);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Generate numbers";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Sorting::button1_Click);
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(97, 92);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(958, 362);
			this->panel1->TabIndex = 2;
			// 
			// buttonSortStep
			// 
			this->buttonSortStep->Location = System::Drawing::Point(795, 460);
			this->buttonSortStep->Name = L"buttonSortStep";
			this->buttonSortStep->Size = System::Drawing::Size(350, 190);
			this->buttonSortStep->TabIndex = 3;
			this->buttonSortStep->Text = L"Sort (one step)";
			this->buttonSortStep->UseVisualStyleBackColor = true;
			this->buttonSortStep->Click += gcnew System::EventHandler(this, &Sorting::buttonSortStep_Click);
			// 
			// labelIndex
			// 
			this->labelIndex->AutoSize = true;
			this->labelIndex->Location = System::Drawing::Point(364, 40);
			this->labelIndex->Name = L"labelIndex";
			this->labelIndex->Size = System::Drawing::Size(35, 13);
			this->labelIndex->TabIndex = 4;
			this->labelIndex->Text = L"label1";
			// 
			// MoveTimer
			// 
			this->MoveTimer->Enabled = true;
			this->MoveTimer->Interval = 10;
			this->MoveTimer->Tick += gcnew System::EventHandler(this, &Sorting::MoveTimer_Tick);
			// 
			// Sorting
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1264, 681);
			this->Controls->Add(this->labelIndex);
			this->Controls->Add(this->buttonSortStep);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button1);
			this->Name = L"Sorting";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sorting numbers and stuff";
			this->Load += gcnew System::EventHandler(this, &Sorting::Sorting_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		ref class NumberThing
		{
		public:
			static enum class AnimationState
			{
				Idle,
				Swapping,
				DroppingDown,
				RisingUp
			};

			int Value;
			Label^ label;
			AnimationState CurrentState;
		private:
			NumberThing^ SwapTarget;
			int targetX;
			int targetY;
		public:
			NumberThing(int value)
			{
				Value = value;
				label = gcnew Label;
				Setup();
			}

			NumberThing(int value, Label^ lbl)
			{
				Value = value;
				label = lbl;
				Setup();
			}

			void StartSwapAnimation(int newX, int y, NumberThing^ swapTarget)
			{
				targetX = newX;
				targetY = y;
				SwapTarget = swapTarget;
				CurrentState = AnimationState::DroppingDown;
			}

			void Update()
			{
				switch (CurrentState)
				{
				case AnimationState::Idle:
					break;
				case AnimationState::Swapping:
					if (SwapTarget->CurrentState == AnimationState::DroppingDown)
						break;
					if (label->Location.X < targetX)
						label->Location = Point(label->Location.X + 5, label->Location.Y);
					else if (label->Location.X > targetX)
						label->Location = Point(label->Location.X - 5, label->Location.Y);
					else
						CurrentState = AnimationState::RisingUp;
					break;
				case AnimationState::DroppingDown:
					label->Location = Point(label->Location.X, label->Location.Y + 5);
					if (label->Location.Y >= targetY)
						CurrentState = AnimationState::Swapping;
					break;
				case AnimationState::RisingUp:
					label->Location = Point(label->Location.X, label->Location.Y - 5);
					if (label->Location.Y <= 10)
						CurrentState = AnimationState::Idle;
					break;
				}
			}
		private:
			void Setup()
			{
				label->Text = Value.ToString();
				label->Size = System::Drawing::Size(labelSizeX, labelSizeY);
				label->Font = gcnew System::Drawing::Font("Arial", 20);
				label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				CurrentState = AnimationState::Idle;
			}
		};

		array<NumberThing^>^ numbers;
		array<Label^>^ GeneratedLabels;
		const static int labelSizeX = 70;
		const static int labelSizeY = 50;
		enum class SortType
		{
			BubbleSort,
			SelectionSort,
			InsertionSort
		};

		void GenerateNumbers(int count)
		{
			Random^ rnd = gcnew Random;
			numbers = gcnew array<NumberThing^>(count);
			for (int i = 0; i < count; i++)
			{
				if (GeneratedLabels[i] != nullptr)
					numbers[i] = gcnew NumberThing(rnd->Next(0, 100), GeneratedLabels[i]);
				else
				{
					numbers[i] = gcnew NumberThing(rnd->Next(0, 100));
					GeneratedLabels[i] = numbers[i]->label;
					this->panel1->Controls->Add(numbers[i]->label);
				}
				numbers[i]->label->Location = System::Drawing::Point(i * (labelSizeX + 5), 10);
			}
			ColorAllNumbers(Color::White);
		}

		void Sorting_Load(System::Object^ sender, System::EventArgs^ e) 
		{
			GeneratedLabels = gcnew array<Label^>(100);
		}

		void button1_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			GenerateNumbers(10);
			isSorted = false;
		}

		int index = 0;
		bool isSorted = false;
		/*
		void swapNumbers(NumberThing^& N1, NumberThing^& N2)
		{
			NumberThing^ temp = N1;
			Point tempLocation = N1->label->Location;
			N1->label->Location = N2->label->Location;
			N2->label->Location = tempLocation;
			N1 = N2;
			N2 = temp;
		}
		*/

		void MoveTimer_Tick(System::Object^ sender, System::EventArgs^ e) 
		{
			bool AllIdle = true;
			if (numbers == nullptr)
				return;
			for (int i = 0; i < numbers->Length; i++)
			{
				numbers[i]->Update();
				if (numbers[i]->CurrentState != NumberThing::AnimationState::Idle)
					AllIdle = false;
			}
			if (AllIdle)
				buttonSortStep->Enabled = true;
			else
				buttonSortStep->Enabled = false;
		}

		void ColorAllNumbers(Color color)
		{
			for (int i = 0; i < numbers->Length; i++)
				numbers[i]->label->BackColor = color;
		}

		void StartSwap(NumberThing^ N1, NumberThing^ N2)
		{
			buttonSortStep->Enabled = false;
			N1->StartSwapAnimation(N2->label->Location.X, 50, N2);
			N2->StartSwapAnimation(N1->label->Location.X, 100, N1);
		}

		void BubbleSortStep()
		{
			if (isSorted)
				return;
			ColorAllNumbers(Color::White);
			isSorted = true;
			for (int i = index; i < numbers->Length - 1; i++)
			{
				if (numbers[i]->Value > numbers[i + 1]->Value)
				{
					NumberThing^ temp = numbers[i];
					//Point tempLocation = numbers[i]->label->Location;
					//numbers[i]->label->Location = numbers[i+1]->label->Location;
					//numbers[i+1]->label->Location = tempLocation;
					numbers[i] = numbers[i+1];
					numbers[i+1] = temp;
					numbers[i]->label->BackColor = System::Drawing::Color::Red;
					numbers[i + 1]->label->BackColor = System::Drawing::Color::Red;
					StartSwap(numbers[i], numbers[i + 1]);
					isSorted = false;
					index = i + 1;
					return;
				}
			}
			for (int i = 0; i < index; i++)
			{
				if (numbers[i]->Value > numbers[i + 1]->Value)
				{
					NumberThing^ temp = numbers[i];
					//Point tempLocation = numbers[i]->label->Location;
					//numbers[i]->label->Location = numbers[i + 1]->label->Location;
					//numbers[i + 1]->label->Location = tempLocation;
					numbers[i] = numbers[i + 1];
					numbers[i + 1] = temp;
					numbers[i]->label->BackColor = System::Drawing::Color::Red;
					numbers[i + 1]->label->BackColor = System::Drawing::Color::Red;
					StartSwap(numbers[i], numbers[i + 1]);
					isSorted = false;
					index = i + 1;
					return;
				}
			}
			ColorAllNumbers(Color::Green);
		}
		void buttonSortStep_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			BubbleSortStep();
			labelIndex->Text = "Current index: " + index.ToString();
		}

};
}
