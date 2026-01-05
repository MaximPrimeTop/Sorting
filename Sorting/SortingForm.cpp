#include "SortingForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Sort;

[STAThread]
int main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Sorting);
	return 0;
}
