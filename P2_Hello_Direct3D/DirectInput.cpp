#include "d3dUtil.h"
#include "DirectInput.h"
#include "d3dApp.h"

DirectInput* gDInput = NULL;

DirectInput::DirectInput(DWORD keyboardCoopFlags, DWORD mouseCoopFlags)
{
	ZeroMemory(mKeyboardState, sizeof(mKeyboardState));
	ZeroMemory(&mMouseState, sizeof(mMouseState));
	HR(DirectInput8Create(gd3dApp->getAppInst(), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&mDInput, 0));

	//Step 1: Create the Device
	HR(mDInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, 0));
	HR(mDInput->CreateDevice(GUID_SysMouse, &mMouse, 0));
	//Step 2: Set the Data Format
	HR(mKeyboard->SetDataFormat(&c_dfDIKeyboard));
	HR(mMouse->SetDataFormat(&c_dfDIMouse2));
	//Step 3: Set the Cooperative Level
	HR(mKeyboard->SetCooperativeLevel(gd3dApp->getMainWnd(),
		keyboardCoopFlags));
	HR(mMouse->SetCooperativeLevel(gd3dApp->getMainWnd(),
		mouseCoopFlags));
	//Step 4: Acquire the Device
	HR(mKeyboard->Acquire());
	HR(mMouse->Acquire());


}


DirectInput::~DirectInput()
{
	ReleaseCOM(mDInput);
	mKeyboard->Unacquire();
	mMouse->Unacquire();
	ReleaseCOM(mKeyboard);
	ReleaseCOM(mMouse);
}

void DirectInput::poll()
{
	// Poll keyboard.
	HRESULT hr = mKeyboard->GetDeviceState(sizeof(mKeyboardState),
		(void**)&mKeyboardState);
	if (FAILED(hr))
	{
		// Keyboard lost, zero out keyboard data structure.
		ZeroMemory(mKeyboardState, sizeof(mKeyboardState));
		// Try to acquire for next time we poll.
		hr = mKeyboard->Acquire();
	}
	// Poll mouse.
	hr = mMouse->GetDeviceState(sizeof(DIMOUSESTATE2),
		(void**)&mMouseState);
	if (FAILED(hr))
	{
		// Mouse lost, zero out mouse data structure.
		ZeroMemory(&mMouseState, sizeof(mMouseState));
		// Try to acquire for next time we poll.
		hr = mMouse->Acquire();
	}
}

bool DirectInput::keyDown(char key)
{
	return (mKeyboardState[key] & 0x80) != 0;
}

bool DirectInput::mouseButtonDown(int button)
{
	return (mMouseState.rgbButtons[button] & 0x80) != 0;
}

float DirectInput::mouseDX()
{
	return (float)mMouseState.lX;
}
float DirectInput::mouseDY()
{
	return (float)mMouseState.lY;
}
float DirectInput::mouseDZ()
{
	return (float)mMouseState.lZ;
}