// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "core/CompileConfig.h"

#if OUZEL_SUPPORTS_VULKAN

#include "graphics/MeshBufferResource.h"

namespace ouzel
{
    namespace graphics
    {
        class BufferResourceVk;

        class MeshBufferResourceVk: public MeshBufferResource
        {
        public:
            MeshBufferResourceVk();
            virtual ~MeshBufferResourceVk();

            BufferResourceVk* getIndexBufferD3D11() const { return indexBufferD3D11; }
            BufferResourceVk* getVertexBufferD3D11() const { return vertexBufferD3D11; }

        protected:
            virtual bool upload() override;

            BufferResourceVk* indexBufferVk = nullptr;
            BufferResourceVk* vertexBufferVk = nullptr;
        };
    } // namespace graphics
} // namespace ouzel

#endif
