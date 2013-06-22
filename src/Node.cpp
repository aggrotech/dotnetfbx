#include "Stdafx.h"
#include "Node.h"
#include "NodeAttribute.h"
#include "Mesh.h"

namespace Fbx
{
    int Node::GetChildCount()
    {
        return InternalPointer->GetChildCount();
    }

    Node^ Node::GetChild(int index)
    {
        return Node::FromInternalPointer(InternalPointer->GetChild(index));
    }

    int Node::GetNodeAttributeCount()
    {
        return InternalPointer->GetNodeAttributeCount();
    }

    NodeAttribute^ Node::GetNodeAttribute()
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

        char *name = const_cast<char *>(node->GetName());

        n->Name = System::Runtime::InteropServices::Marshal::PtrToStringAnsi(static_cast<System::IntPtr>(name));
        n->InternalPointer = node;

        return n;
    }


}
