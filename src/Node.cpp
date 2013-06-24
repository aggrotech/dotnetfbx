#include "Stdafx.h"
#include "Node.h"
#include "NodeAttribute.h"
#include "Mesh.h"

using namespace System::Runtime::InteropServices;

namespace Fbx
{
    // Basic Properties

    String^ Node::Name::get()
    {
        return Marshal::PtrToStringAnsi((IntPtr)const_cast<char *>(InternalPointer->GetName()));
    }

    void Node::Name::set(String^ name)
    {
        char *charName = (char *)(void *)Marshal::StringToHGlobalAnsi(name);
        InternalPointer->SetName(charName);
    }

    // Child Nodes

    int Node::ChildCount::get()
    {
        return InternalPointer->GetChildCount();
    }

    Node^ Node::GetChild(int index)
    {
        return Node::FromInternalPointer(InternalPointer->GetChild(index));
    }


    // Node Attributes

    int Node::NodeAttributeCount::get()
    {
        return InternalPointer->GetNodeAttributeCount();
    }

    NodeAttribute^ Node::Attribute::get()
    {
        return NodeAttribute::FromInternalPointer(InternalPointer->GetNodeAttribute());
    }

    NodeAttribute^ Node::GetNodeAttributeByIndex(int index)
    {
        return NodeAttribute::FromInternalPointer(InternalPointer->GetNodeAttributeByIndex(index));
    }

    Node^ Node::FromInternalPointer(::FbxNode* node)
    {
        Node^ n = gcnew Node;

        n->InternalPointer = node;

        return n;
    }

    Mesh^ Node::MeshAttribute::get()
    {
        return Mesh::FromInternalPointer(InternalPointer->GetMesh());
    }
}
