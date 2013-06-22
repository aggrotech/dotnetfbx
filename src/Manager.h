#pragma once
#include "IoSettings.h"

namespace Fbx
{
    public ref class Manager
    {
    public:
        static Manager^ Create();

        IoSettings^ Settings;

        ~Manager();

    internal:

        ::FbxManager* manager;

    private:

        bool disposed;
    };
}
