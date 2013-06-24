#pragma once

namespace Fbx
{
    public ref class GeometryElementMaterial
    {
    public:

        property array<int>^ IndexArray
        {
            array<int>^ get();
        }

    internal:

        ::FbxGeometryElementMaterial* InternalPointer;
    };
}
