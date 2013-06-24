#pragma once

namespace Fbx
{
    ref class Node;
    ref class Manager;

    public ref class GeometryConverter
    {
    public:

        GeometryConverter(Manager^ manager);

        // Triangulation

        void TriangulateInPlace(Node^ node);

    internal:

        ::FbxGeometryConverter* InternalPointer;
    };
}
