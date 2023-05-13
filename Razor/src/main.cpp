#include "rzr_pch.h"
#include "Razor.h"

int main(int argc, char** argv)
{
    Razor::Log::Init();
    RZR_INFO("Engine starting...");

    auto app = Razor::CreateApplication();
    app->Run();
    delete app;

    return 0;
}