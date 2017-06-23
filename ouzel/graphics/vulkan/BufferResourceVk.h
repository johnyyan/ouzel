// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "core/CompileConfig.h"

#if OUZEL_SUPPORTS_VULKAN

#include "graphics/BufferResource.h"

namespace ouzel
{
    namespace graphics
    {
        class BufferResourceVk: public BufferResource
        {
        public:
            BufferResourceVk();
            virtual ~BufferResourceVk();

        protected:
            virtual bool upload() override;
        };
    } // namespace graphics
} // namespace ouzel

#endif
