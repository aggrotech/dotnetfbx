#pragma once

using namespace System;

namespace Fbx
{
    ref class NodeAttribute;
    ref class Mesh;

    public ref class Node
    {
    public:

        // Basic Properties

        property String^ Name
        {
            String^ get();
            void set(String^ name);
        }
        

        // Child Nodes

        property int ChildCount
        {
            int get();
        }

        Node^ GetChild(int index);


        // Node Attributes

        property int NodeAttributeCount
        {
            int get();
        }

        property NodeAttribute^ Attribute
        {
            NodeAttribute^ get();
        }

        NodeAttribute^ GetNodeAttributeByIndex(int index);

    internal:

        static Node^ FromInternalPointer(::FbxNode* node);

        ::FbxNode* InternalPointer;
    };
}
