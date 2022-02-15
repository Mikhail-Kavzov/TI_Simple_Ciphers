#include "Shiphr.h"
#include <Windows.h>

using namespace ShiphrLab;
[STAThread]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew Shiphr);
    return 0;
}
