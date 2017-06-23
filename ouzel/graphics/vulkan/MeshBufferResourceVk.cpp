// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "core/CompileConfig.h"

#if OUZEL_SUPPORTS_VULKAN

#include "MeshBufferResourceVk.h"
#include "BufferResourceVk.h"
#include "utils/Log.h"

namespace ouzel
{
    namespace graphics
    {
        MeshBufferResourceVk::MeshBufferResourceVk()
        {
        }

        MeshBufferResourceVk::~MeshBufferResourceVk()
        {
        }

        bool MeshBufferResourceVk::upload()
        {
            std::lock_guard<std::mutex> lock(uploadMutex);

            if (dirty)
            {
                indexBufferVk = static_cast<BufferResourceVk*>(indexBuffer);
                vertexBufferVk = static_cast<BufferResourceVk*>(vertexBuffer);

                dirty = 0;
            }

            return true;
        }
    } // namespace graphics
} // namespace ouzel

#endif
