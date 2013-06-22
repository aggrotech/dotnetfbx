#pragma once

namespace Fbx
{
    ref class NodeAttribute;
    ref class Mesh;

    public ref class Node
    {
    public:

        System::String^ Name;

        int GetChildCount();

        Node^ GetChild(int i);

        int GetNodeAttributeCount();

        NodeAttribute^ GetNodeAttribute();

        NodeAttribute^ GetNodeAttributeByIndex(int index);

    internal:

        static Node^ FromInternalPointer(::FbxNode* node);

        ::FbxNode* InternalPointer;
    };
}
