#pragma once

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include "MainWindow.g.h"

#pragma pop_macro("GetCurrentTime")

namespace winrt::Client::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void colorPicker_ColorChanged(Microsoft::UI::Xaml::Controls::ColorPicker const& sender, Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const& args);

    private:
        Engine::Core core;
        bool isRendering;
    };
}

namespace winrt::Client::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
