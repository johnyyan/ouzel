// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "BufferResourceD3D12.h"
#include "RendererD3D12.h"
#include "core/Engine.h"
#include "utils/Log.h"

namespace ouzel
{
    namespace graphics
    {
        BufferResourceD3D12::BufferResourceD3D12()
        {
        }

        BufferResourceD3D12::~BufferResourceD3D12()
        {
        }

        bool BufferResourceD3D12::upload()
        {
            std::lock_guard<std::mutex> lock(uploadMutex);

            if (dirty)
            {
                dirty = 0;
            }

            return true;
        }
    } // namespace graphics
} // namespace ouzel
