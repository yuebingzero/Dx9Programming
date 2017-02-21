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

	void addVertices(DWORD n);
	void subVertices(DWORD n);
	void addTriangles(DWORD n);
	void subTriangles(DWORD n);

	void setTriCount(DWORD n);
	void setVertexCount(DWORD n);
protected:
	float mFPS;
	float mMilliSecPerFrame;
	DWORD mNumTris;
	DWORD mNumVertices;
	ID3DXFont* mFont;
};

