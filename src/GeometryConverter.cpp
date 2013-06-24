#include "Stdafx.h"
#include "GeometryConverter.h"
#include "Node.h"
#include "Manager.h"

namespace Fbx
{
    GeometryConverter::GeometryConverter(Manager^ manager)
    {
        InternalPointer = new ::FbxGeometryConverter(manager->manager);
    }

    void GeometryConverter::TriangulateInPlace(Node^ node)
    {
        InternalPointer->TriangulateInPlace(node->InternalPointer);
    }
}
