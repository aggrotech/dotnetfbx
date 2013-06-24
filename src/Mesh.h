#pragma once
#include "Vector4.h"

namespace Fbx
{
    ref class GeometryElementMaterial;

    public ref class Mesh
    {
    public:

        // Edge Management

        property bool IsTriangleMesh
        {
            bool get();
        }

        // Polygon Management

        property array<Vector4>^ ControlPoints
        {
            array<Vector4>^ get();
        }

        property int PolygonCount
        {
            int get();
        }

        property int NormalCount
        {
            int get();
        }

        property int UvCount
        {
            int get();
        }

        property GeometryElementMaterial^ ElementMaterial
        {
            GeometryElementMaterial^ get();
        }

        int GetPolygonVertex(int polygonIndex, int vertexIndex);

    internal:

        static Mesh^ FromInternalPointer(::FbxMesh* mesh);

        ::FbxMesh* InternalPointer;
    };
}
