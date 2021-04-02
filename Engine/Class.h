#pragma once

#include "Class.g.h"

namespace winrt::Engine::implementation
{
    struct Class : ClassT<Class>
    {
        Class() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);

    public:
        static const wchar_t* GetEngineName()
        {
            return L"WhiteFlint";
        }
    };
}

namespace winrt::Engine::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
