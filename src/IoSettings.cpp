#include "Stdafx.h"
#include "IoSettings.h"
#include "Manager.h"

namespace Fbx
{
    IoSettings^ IoSettings::Create(Manager^ manager)
    {
        IoSettings^ settings = gcnew IoSettings;

        settings->settings = ::FbxIOSettings::Create(manager->manager, "");

        return settings;
    }
}
