#include "Stdafx.h"
#include "Manager.h"

namespace Fbx
{
    Manager^ Manager::Create()
    {
        Manager^ mgr = gcnew Manager;

        mgr->manager = ::FbxManager::Create();

        return mgr;
    }
}
