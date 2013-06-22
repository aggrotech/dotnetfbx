#include "Stdafx.h"
#include "Importer.h"
#include "Manager.h"
#include "Scene.h"

namespace Fbx
{
    Importer^ Importer::Create(Manager^ manager)
    {
        Importer^ imp = gcnew Importer;

        imp->importer = ::FbxImporter::Create(manager->manager, "");

        return imp;
    }

    void Importer::Initialize(System::String^ filename, IoSettings^ settings)
    {
        char *n = (char *)(void *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(filename);

        if (!importer->Initialize(n, -1, settings->settings))
        {
            throw gcnew System::Exception("Error initializing importer");
        }
    }

    void Importer::Import(Scene^ scene)
    {
        if(!importer->Import(scene->scene))
        {
            throw gcnew System::Exception("Error importing scene");
        }
    }
}
