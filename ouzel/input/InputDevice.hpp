// Copyright (C) 2018 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

namespace ouzel
{
    namespace input
    {
        class InputDevice
        {
        public:
            enum Type
            {
                KEYBOARD,
                MOUSE,
                TOUCHPAD,
                GAMEPAD
            };

            explicit InputDevice(Type initType): type(initType) {}
            virtual ~InputDevice() {}

            Type getType() const { return type; }

        private:
            Type type;
        };
    }
}
