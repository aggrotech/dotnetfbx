#pragma once

namespace Fbx
{
    ref class Manager;
    ref class IoSettings;
    ref class Scene;

    public ref class Importer
    {
    public:

        static Importer^ Create(Manager^ manager);

        void Initialize(System::String^ filename, IoSettings^ ioSettings);

        void Import(Scene^ scene);

    private:

        ::FbxImporter* importer;
    };
}