#pragma once

namespace Fbx
{
    /// <summary>
    /// Geometry made out of polygons.
    /// </summary>
    public ref class Mesh
    {
    public:

        /// <summary>
        /// Returns true if the mesh is composed entirely of triangles.
        /// </summary>
        property bool IsTriangleMesh
        {
            bool get();
        }

    internal:

        ::FbxMesh* InternalPointer;
    };
}
