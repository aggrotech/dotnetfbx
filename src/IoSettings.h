#pragma once

namespace Fbx
{
    ref class Manager;

    public ref class IoSettings
    {
    public:

        static IoSettings^ Create(Manager^ manager);

    internal:

        ::FbxIOSettings* settings;
    };
}
