#include "Stdafx.h"
#include "Mesh.h"

namespace Fbx
{
    bool Mesh::IsTriangleMesh::get()
    {
        return InternalPointer->IsTriangleMesh();
    }
}
