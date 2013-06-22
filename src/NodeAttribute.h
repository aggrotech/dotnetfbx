#pragma once

namespace Fbx
{
    public enum class NodeAttributeTypes
    {
        Unknown,
        Null,
        Marker,
        Skeleton,
        Mesh,
        Nurbs,
        Patch,
        Camera,
        CameraStereo,
        CameraSwitcher,
        Light,
        OpticalReference,
        OpticalMarker,
        NurbsCurve,
        TrimNurbsSurface,
        Boundary,
        NurbsSurface,
        Shape,
        LodGroup,
        SubDiv,
        CachedEffect,
        Line
    };

    public ref class NodeAttribute
    {
    public:

        NodeAttributeTypes AttributeType;

    internal:

        static NodeAttribute^ FromInternalPointer(::FbxNodeAttribute* ptr);

        ::FbxNodeAttribute* InternalPointer;
    };
}
