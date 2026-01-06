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
	private: System::Windows::Forms::ListBox^ listBox1;
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
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
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
			this->panel1->Location = System::Drawing::Point(146, 92);
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
			// listBox1
			// 
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 31;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Bubble", L"Insertion", L"Selection" });
			this->listBox1->Location = System::Drawing::Point(12, 31);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(120, 128);
			this->listBox1->TabIndex = 5;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Sorting::listBox1_SelectedIndexChanged);
			// 
			// Sorting
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1264, 681);
			this->Controls->Add(this->listBox1);
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
				RisingUp,
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

			void StartSwapAnimation(int newX, int y, NumberThing^ swapTarget) // if swapTarget is self it won't wait when swapping
			{
				targetX = newX;
				targetY = y;
				SwapTarget = swapTarget;
				CurrentState = AnimationState::DroppingDown;
			}

			void StartInsertionSwapAnimation(int newX, NumberThing^ swapTarget)
			{
				targetX = newX;
				CurrentState = AnimationState::Swapping;
			}

			void ColorNumber(Color color)
			{
				label->BackColor = color;
			}

			void Update()
			{
				switch (CurrentState)
				{
				case AnimationState::Idle:
					break;
				case AnimationState::Swapping:
					if (SwapTarget->CurrentState == AnimationState::DroppingDown)
						return;
					if (label->Location.X < targetX)
						label->Location = Point(label->Location.X + 5, label->Location.Y);
					else if (label->Location.X > targetX)
						label->Location = Point(label->Location.X - 5, label->Location.Y);
					else
						CurrentState = AnimationState::RisingUp;
					break;
				case AnimationState::DroppingDown:
					if (label->Location.Y >= targetY)
					{
						CurrentState = AnimationState::Swapping;
						return;
					}
					label->Location = Point(label->Location.X, label->Location.Y + 5);
					break;
				case AnimationState::RisingUp:
					if (label->Location.Y <= 10)
					{
						CurrentState = AnimationState::Idle;
						return;
					}
					label->Location = Point(label->Location.X, label->Location.Y - 5);
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

		enum class SortState
		{
			Unsorted,
			Sorting,
			Sorted
		};

		static SortType CurrentSortType;
		static SortState CurrentSortState;
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
			CurrentSortState = SortState::Unsorted;
		}

		int index = 0;
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
				numbers[i]->ColorNumber(color);
		}

		void StartSwap(NumberThing^ N1, NumberThing^ N2)
		{
			buttonSortStep->Enabled = false;
			N1->StartSwapAnimation(N2->label->Location.X, 70, N2);
			N2->StartSwapAnimation(N1->label->Location.X, 120, N1);
		}

		void BubbleSortStep()
		{
			ColorAllNumbers(Color::White);
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
					numbers[i]->ColorNumber(Color::Red);
					numbers[i + 1]->ColorNumber(Color::Red);
					StartSwap(numbers[i], numbers[i + 1]);
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
					numbers[i]->ColorNumber(Color::Red);
					numbers[i + 1]->ColorNumber(Color::Red);
					StartSwap(numbers[i], numbers[i + 1]);
					index = i + 1;
					return;
				}
			}
			ColorAllNumbers(Color::Green);
			CurrentSortState = SortState::Sorted;
		}

		void InsertionSortStep()
		{
			//however the heck insertion sort works
		}

		void SelectionSortStep()
		{
			for (int i = 0; i < numbers->Length; i++)
				if (i < index)
					numbers[i]->ColorNumber(Color::White);
				else
					numbers[i]->ColorNumber(Color::Lime);
			int maxNumIndex = 0;
			for (int i = 1; i < index; i++)
				if (numbers[i]->Value >= numbers[maxNumIndex]->Value)
					maxNumIndex = i;
			if (maxNumIndex == index - 1)
				numbers[maxNumIndex]->ColorNumber(Color::Lime);
			else
			{
				NumberThing^ temp = numbers[maxNumIndex];
				numbers[maxNumIndex] = numbers[index - 1];
				numbers[index - 1] = temp;
				numbers[maxNumIndex]->ColorNumber(Color::Red);
				numbers[index - 1]->ColorNumber(Color::Lime);
				StartSwap(numbers[maxNumIndex], numbers[index - 1]);
			}
			index--;
			if (index == 0)
			{
				ColorAllNumbers(Color::Green);
				CurrentSortState = SortState::Sorted;
			}
		}
		void buttonSortStep_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			switch (CurrentSortState)
			{
				case SortState::Unsorted:
					switch (CurrentSortType)
					{
						case SortType::BubbleSort:
							index = 0;
							BubbleSortStep();
							break;
						case SortType::InsertionSort:
							index = numbers->Length;
							InsertionSortStep();
							break;
						case SortType::SelectionSort:
							index = numbers->Length;
							SelectionSortStep();
							break;
					}
					CurrentSortState = SortState::Sorting;
					break;
				case SortState::Sorting:
					switch (CurrentSortType)
					{
						case SortType::BubbleSort:
							BubbleSortStep();
							break;
						case SortType::InsertionSort:
							InsertionSortStep();
							break;
						case SortType::SelectionSort:
							SelectionSortStep();
							break;
					}
					break;
			}
			labelIndex->Text = "Current index: " + index.ToString();
		}

		void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			switch (listBox1->SelectedIndex)
			{
			case 0:
				CurrentSortType = SortType::BubbleSort;
				break;
			case 1:
				CurrentSortType = SortType::InsertionSort;
				break;
			case 2:
				CurrentSortType = SortType::SelectionSort;
				break;
			}
			CurrentSortState = SortState::Unsorted;
		}
};
}
