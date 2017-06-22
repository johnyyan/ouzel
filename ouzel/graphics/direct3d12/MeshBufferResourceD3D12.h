// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "core/CompileConfig.h"

#if OUZEL_SUPPORTS_DIRECT3D12

#include <d3d12.h>
#include "graphics/MeshBufferResource.h"

namespace ouzel
{
    namespace graphics
    {
        class BufferResourceD3D12;

        class MeshBufferResourceD3D12: public MeshBufferResource
        {
        public:
            MeshBufferResourceD3D12();
            virtual ~MeshBufferResourceD3D12();

            BufferResourceD3D12* getIndexBufferD3D11() const { return indexBufferD3D11; }
            BufferResourceD3D12* getVertexBufferD3D11() const { return vertexBufferD3D11; }

        protected:
            virtual bool upload() override;

            BufferResourceD3D12* indexBufferD3D11 = nullptr;
            BufferResourceD3D12* vertexBufferD3D11 = nullptr;
        };
    } // namespace graphics
} // namespace ouzel

#endif
