#include "Stdafx.h"
#include "Mesh.h"
#include "Vector4.h"
#include "GeometryElementMaterial.h"

namespace Fbx
{
    bool Mesh::IsTriangleMesh::get()
    {
        return InternalPointer->IsTriangleMesh();
    }

    array<Vector4>^ Mesh::ControlPoints::get()
    {
        int count = InternalPointer->GetControlPointsCount();
        ::FbxVector4* pts = InternalPointer->GetControlPoints();

        array<Vector4>^ output = gcnew array<Vector4>(count);

        for(int i = 0; i < count; i++)
        {
            Vector4 v;

            v.x = pts[i][0];
            v.y = pts[i][1];
            v.z = pts[i][2];
            v.w = pts[i][3];

            output[i] = v;
        }

        return output;
    }

    int Mesh::PolygonCount::get()
    {
        return InternalPointer->GetPolygonCount();
    }

    int Mesh::NormalCount::get()
    {
        return InternalPointer->GetElementNormalCount();
    }

    int Mesh::UvCount::get()
    {
        return InternalPointer->GetElementUVCount();
    }

    Mesh^ Mesh::FromInternalPointer(::FbxMesh* mesh)
    {
        Mesh^ m = gcnew Mesh;

        m->InternalPointer = mesh;

        return m;
    }

    GeometryElementMaterial^ Mesh::ElementMaterial::get()
    {
        ::FbxGeometryElementMaterial* mat = InternalPointer->GetElementMaterial();

        if (mat == NULL)
        {
            return nullptr;
        }
        
        GeometryElementMaterial^ material = gcnew GeometryElementMaterial;
        material->InternalPointer = mat;
        return material;
    }

    int Mesh::GetPolygonVertex(int polygonIndex, int vertexIndex)
    {
        return InternalPointer->GetPolygonVertex(polygonIndex, vertexIndex);
    }
}
