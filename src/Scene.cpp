#include "Stdafx.h"
#include "Manager.h"
#include "Scene.h"
#include "Node.h"

namespace Fbx
{
    Scene^ Scene::Create(Manager^ manager)
    {
        Scene^ scene = gcnew Scene;

        scene->scene = ::FbxScene::Create(manager->manager, "MyScene");

        return scene;
    }

    Node^ Scene::GetRootNode()
    {
        return Node::FromInternalPointer(scene->GetRootNode());
    }
}
