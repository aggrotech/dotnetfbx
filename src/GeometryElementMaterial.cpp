#include "Stdafx.h"
#include "GeometryElementMaterial.h"

namespace Fbx
{
    array<int>^ GeometryElementMaterial::IndexArray::get()
    {
        ::FbxLayerElementArrayTemplate<int> &indices = InternalPointer->GetIndexArray();
        int count = indices.GetCount();

        array<int>^ output = gcnew array<int>(count);

        for(int i = 0; i < count; i++)
        {
            output[i] = indices[i];
        }

        return output;
    }
}
