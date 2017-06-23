// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "core/CompileConfig.h"

#if OUZEL_SUPPORTS_VULKAN

#include "BufferResourceVk.h"
#include "RendererVk.h"
#include "core/Engine.h"
#include "utils/Log.h"

namespace ouzel
{
    namespace graphics
    {
        BufferResourceVk::BufferResourceVk()
        {
        }

        BufferResourceVk::~BufferResourceVk()
        {
        }

        bool BufferResourceVk::upload()
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

#endif