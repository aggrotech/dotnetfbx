#include "Stdafx.h"
#include "fbxsdk.h"
#include "NodeAttribute.h"

namespace Fbx
{
    NodeAttribute^ NodeAttribute::FromInternalPointer(::FbxNodeAttribute* ptr)
    {
        if(ptr == NULL)
        {
            return nullptr;
        }

        NodeAttribute^ attr = gcnew NodeAttribute;

        attr->InternalPointer = ptr;
        
        attr->AttributeType = (NodeAttributeTypes)ptr->GetAttributeType();

        return attr;
    }
}
