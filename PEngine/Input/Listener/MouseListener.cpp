/**
 * @file MouseListener.cpp
 * @brief Implementation of the MouseListener class.
 */

#include <PEngine/Input/Listener/MouseListener.h>

namespace Picasso::Engine::Input::Listener
{
    /**
     * @brief Process a mouse button event.
     *
     * This function updates the state of a mouse button and dispatches a corresponding event.
     *
     * @param button The button that was pressed or released.
     * @param pressed True if the button was pressed, false if it was released.
     * @param inputState The current input state.
     */
    void MouseListener::ProcessButton(BUTTONS button, bool pressed, pInputState &inputState)
    {
        // Check if the button state has changed
        if (inputState.mouseCurrent.buttons[button] == pressed)
        {
            return;
        }

        // Update the button state
        inputState.mouseCurrent.buttons[button] = pressed;

        // Create event data
        PEventData eData;
        eData.data.u16[0] = button;

        // Dispatch the event
        PicassoRegistry::Dispatch(pressed ? PEvent::BUTTON_PRESSED : PEvent::BUTTON_RELEASED, eData);
    }

    /**
     * @brief Process a mouse move event.
     *
     * This function updates the current mouse position and dispatches a mouse moved event.
     *
     * @param x The new x-coordinate of the mouse position.
     * @param y The new y-coordinate of the mouse position.
     * @param inputState The current input state.
     */
    void MouseListener::ProcessMouseMove(float x, float y, pInputState &inputState)
    {
        // Check if the mouse position has changed
        if (inputState.mouseCurrent.x == x && inputState.mouseCurrent.y == y)
        {
            return;
        }

        // Update the mouse position
        inputState.mouseCurrent.x = x;
        inputState.mouseCurrent.y = y;

        // Create event data
        PEventData eData;
        eData.data.u16[0] = x;
        eData.data.u16[1] = y;

        // Dispatch the event
        PicassoRegistry::Dispatch(PEvent::MOUSE_MOVED, eData);
    }

    /**
     * @brief Get the current mouse position.
     *
     * This function retrieves the current x and y coordinates of the mouse position.
     *
     * @param x Pointer to store the x-coordinate of the mouse position.
     * @param y Pointer to store the y-coordinate of the mouse position.
     * @param inputState The current input state.
     */
    void MouseListener::GetMousePosition(float *x, float *y, pInputState &inputState)
    {
        // Check if the pointers are valid
        if (x == nullptr)
        {
            *x = 0;
            return;
        }

        if (y == nullptr)
        {
            *y = 0;
            return;
        }

        // Get the current mouse position
        *x = inputState.mouseCurrent.x;
        *y = inputState.mouseCurrent.y;
    }

    /**
     * @brief Get the previous mouse position.
     *
     * This function retrieves the previous x and y coordinates of the mouse position.
     *
     * @param x Pointer to store the previous x-coordinate of the mouse position.
     * @param y Pointer to store the previous y-coordinate of the mouse position.
     * @param inputState The current input state.
     */
    void MouseListener::GetPrevMousePosition(float *x, float *y, pInputState &inputState)
    {
        // Check if the pointers are valid
        if (x == nullptr)
        {
            *x = 0;
            return;
        }

        if (y == nullptr)
        {
            *y = 0;
            return;
        }

        // Get the previous mouse position
        *x = inputState.mousePrev.x;
        *y = inputState.mousePrev.y;
    }

    /**
     * @brief Process a mouse wheel event.
     *
     * This function dispatches a mouse wheel event.
     *
     * @param zDelta The delta value of the mouse wheel.
     */
    void MouseListener::ProcessMouseWheels(int zDelta)
    {
        // Create event data
        PEventData eData;
        eData.data.u8[0] = zDelta;

        // Dispatch the event
        PicassoRegistry::Dispatch(PEvent::MOUSE_WHEEL, eData);
    }

    /**
     * @brief Check if a mouse button is currently pressed.
     *
     * This function checks if a specific mouse button is currently pressed.
     *
     * @param button The button to check.
     * @param inputState The current input state.
     * @return True if the button is currently pressed, false otherwise.
     */
    bool MouseListener::IsButtonDown(BUTTONS button, pInputState &inputState)
    {
        return inputState.mouseCurrent.buttons[button] == true;
    }

    /**
     * @brief Check if a mouse button is currently released.
     *
     * This function checks if a specific mouse button is currently released.
     *
     * @param button The button to check.
     * @param inputState The current input state.
     * @return True if the button is currently released, false otherwise.
     */
    bool MouseListener::IsButtonUp(BUTTONS button, pInputState &inputState)
    {
        return inputState.mouseCurrent.buttons[button] == false;
    }

    /**
     * @brief Check if a mouse button was previously pressed.
     *
     * This function checks if a specific mouse button was previously pressed.
     *
     * @param button The button to check.
     * @param inputState The current input state.
     * @return True if the button was previously pressed, false otherwise.
     */
    bool MouseListener::WasButtonDown(BUTTONS button, pInputState &inputState)
    {
        return inputState.mousePrev.buttons[button] == true;
    }

    /**
     * @brief Check if a mouse button was previously released.
     *
     * This function checks if a specific mouse button was previously released.
     *
     * @param button The button to check.
     * @param inputState The current input state.
     * @return True if the button was previously released, false otherwise.
     */
    bool MouseListener::WasButtonUp(BUTTONS button, pInputState &inputState)
    {
        return inputState.mousePrev.buttons[button] == false;
    }
}