// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <d3d12.h>
#include "graphics/BlendStateResource.h"

namespace ouzel
{
    namespace graphics
    {
        class BlendStateResourceD3D12: public BlendStateResource
        {
        public:
            BlendStateResourceD3D12();
            virtual ~BlendStateResourceD3D12();

        protected:
            virtual bool upload() override;
        };
    } // namespace graphics
} // namespace ouzel
