// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <d3d12.h>
#include "graphics/BufferResource.h"

namespace ouzel
{
    namespace graphics
    {
        class BufferResourceD3D12: public BufferResource
        {
        public:
            BufferResourceD3D12();
            virtual ~BufferResourceD3D12();

        protected:
            virtual bool upload() override;
        };
    } // namespace graphics
} // namespace ouzel
