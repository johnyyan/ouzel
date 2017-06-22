// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "core/CompileConfig.h"

#if OUZEL_SUPPORTS_DIRECT3D12

#include "MeshBufferResourceD3D12.h"
#include "BufferResourceD3D12.h"
#include "utils/Log.h"

namespace ouzel
{
    namespace graphics
    {
        MeshBufferResourceD3D12::MeshBufferResourceD3D12()
        {
        }

        MeshBufferResourceD3D12::~MeshBufferResourceD3D12()
        {
        }

        bool MeshBufferResourceD3D12::upload()
        {
            std::lock_guard<std::mutex> lock(uploadMutex);

            if (dirty)
            {
                indexBufferD3D11 = static_cast<BufferResourceD3D12*>(indexBuffer);
                vertexBufferD3D11 = static_cast<BufferResourceD3D12*>(vertexBuffer);

                dirty = 0;
            }

            return true;
        }
    } // namespace graphics
} // namespace ouzel

#endif
