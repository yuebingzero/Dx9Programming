#pragma once
class GfxStats
{
public:
	GfxStats();
	~GfxStats();

	void update(float dt);
	void display();
	void onLostDevice();
	void onResetDevice();

protected:
	float mFPS;
	float mMilliSecPerFrame;
	ID3DXFont* mFont;
};

