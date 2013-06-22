#pragma once

namespace Fbx
{
    ref class Manager;
    ref class Node;

    public ref class Scene
    {
    public:

        static Scene^ Create(Manager^ manager);

        Node^ GetRootNode();

    internal:

        ::FbxScene* scene;
    };
}
