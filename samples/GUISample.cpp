// Copyright (C) 2018 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "GUISample.hpp"
#include "MainMenu.hpp"

using namespace std;
using namespace ouzel;

GUISample::GUISample():
    button("button.png", "button_selected.png", "button_down.png", "", "Button", "arial.fnt", 1.0F, Color::RED, Color::RED, Color::BLACK),
    fullscreenButton("button.png", "button_selected.png", "button_down.png", "", "Fullscreen", "arial.fnt", 1.0F, Color::BLACK, Color::BLACK, Color::BLACK),
    checkBox("checkbox.png", "", "", "", "tick.png"),
    label1("checkbox test", "AmosisTechnik.ttf", 24.0F, Color::WHITE, Vector2(0.0F, 0.5F)),
    label2(engine->getLocalization()->getString("Ouzel"), "ArialBlack.fnt"),
    label3("UTF-8 ĀāČč\nNew line", "ArialBlack.fnt", 1.0F, Color::WHITE, Vector2(0.0F, 0.5F)),
    backButton("button.png", "button_selected.png", "button_down.png", "", "Back", "arial.fnt", 1.0F, Color::BLACK, Color::BLACK, Color::BLACK)
{
    handler.gamepadHandler = bind(&GUISample::handleGamepad, this, placeholders::_1, placeholders::_2);
    handler.uiHandler = bind(&GUISample::handleUI, this, placeholders::_1, placeholders::_2);
    handler.keyboardHandler = bind(&GUISample::handleKeyboard, this, placeholders::_1, placeholders::_2);
    engine->getEventDispatcher()->addEventHandler(&handler);

    guiCamera.setScaleMode(scene::Camera::ScaleMode::SHOW_ALL);
    guiCamera.setTargetContentSize(Size2(800.0F, 600.0F));
    guiCameraActor.addComponent(&guiCamera);
    guiLayer.addChild(&guiCameraActor);
    addLayer(&guiLayer);

    guiLayer.addChild(&menu);

    button.setPosition(Vector2(-200.0F, 100.0F));
    menu.addWidget(&button);

    checkBox.setPosition(Vector2(-100.0F, 100.0F));
    guiLayer.addChild(&checkBox);

    fullscreenButton.setPosition(Vector2(-200.0F, 40.0F));
    menu.addWidget(&fullscreenButton);

    label1.getLabelDrawable()->setColor(Color::CYAN);
    label1.setPosition(Vector2(-88.0F, 108.0F));
    guiLayer.addChild(&label1);

    engine->getLocalization()->addLanguage("latvian", "lv.mo");
    engine->getLocalization()->setLanguage("latvian");

    label2.setPosition(Vector2(10.0F, 0.0F));
    guiLayer.addChild(&label2);

    label3.getLabelDrawable()->setColor(Color::BLUE);
    label3.setPosition(Vector2(-100.0F, -100.0F));
    label3.setScale(Vector3(0.5F, 0.5F, 1.0F));
    guiLayer.addChild(&label3);

    backButton.setPosition(Vector2(-200.0F, -200.0F));
    menu.addWidget(&backButton);
}

bool GUISample::handleGamepad(Event::Type type, const GamepadEvent& event)
{
    if (type == Event::Type::GAMEPAD_BUTTON_CHANGE)
    {
        if (event.pressed &&
            event.button == input::GamepadButton::FACE_RIGHT)
        {
            engine->getSceneManager()->setScene(std::unique_ptr<scene::Scene>(new MainMenu()));
        }
    }

    return true;
}

bool GUISample::handleUI(Event::Type type, const UIEvent& event)
{
    if (type == Event::Type::ACTOR_CLICK)
    {
        if (event.actor == &backButton)
        {
            engine->getSceneManager()->setScene(std::unique_ptr<scene::Scene>(new MainMenu()));
        }
        else if (event.actor == &button)
        {
            checkBox.setChecked(!checkBox.isChecked());
        }
        else if (event.actor == &fullscreenButton)
        {
            bool fullscreen = engine->getWindow()->isFullscreen();
            engine->getWindow()->setFullscreen(!fullscreen);
        }
    }

    return true;
}

bool GUISample::handleKeyboard(Event::Type type, const KeyboardEvent& event) const
{
    if (type == Event::Type::KEY_PRESS)
    {
        switch (event.key)
        {
            case input::KeyboardKey::ESCAPE:
            case input::KeyboardKey::MENU:
                engine->getSceneManager()->setScene(std::unique_ptr<scene::Scene>(new MainMenu()));
                break;
            default:
                break;
        }
    }

    return true;
}
