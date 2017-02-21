#include "d3dUtil.h"
#include "d3dApp.h"
#include "GfxStats.h"
#include <tchar.h>


GfxStats::GfxStats()
: mFont(0), mFPS(0.0f), mMilliSecPerFrame(0.0f)
{
	D3DXFONT_DESC fontDesc;
	fontDesc.Height = 18;
	fontDesc.Width = 0;
	fontDesc.Weight = 0;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = false;
	fontDesc.CharSet = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	_tcscpy(fontDesc.FaceName, _T("Times New Roman"));

	HR(D3DXCreateFontIndirect(gd3dDevice, &fontDesc, &mFont));
}


GfxStats::~GfxStats()
{
	ReleaseCOM(mFont);
}

void GfxStats::onLostDevice()
{
	HR(mFont->OnLostDevice());
}

void GfxStats::onResetDevice()
{
	HR(mFont->OnResetDevice());
}

void GfxStats::addVertices(DWORD n)
{
	mNumVertices += n;
}

void GfxStats::subVertices(DWORD n)
{
	mNumVertices -= n;
}

void GfxStats::addTriangles(DWORD n)
{
	mNumTris += n;
}

void GfxStats::subTriangles(DWORD n)
{
	mNumTris -= n;
}

void GfxStats::setTriCount(DWORD n)
{
	mNumTris = n;
}

void GfxStats::setVertexCount(DWORD n)
{
	mNumVertices = n;
}


void GfxStats::update(float dt)
{
	static float numFrames = 0.0f;
	static float timeElapsed = 0.0f;
	
	numFrames += 1.0f;
	timeElapsed += dt;

	//ÿ�����һ��FPS
	if (timeElapsed >= 1.0f)
	{
		mFPS = numFrames; //����
		mMilliSecPerFrame = 1000.0f / mFPS;

		//reset
		timeElapsed = 0.0f;
		numFrames = 0.0f;
	}

	
}

void GfxStats::display()
{
	// Make static so memory is not allocated every frame.
	static char buffer[256];

	sprintf(buffer, "Frames Per Second = %.2f\n"
		"Milliseconds Per Frame = %.4f\n"
		/*"Triangle Count = %d\n"
		"Vertex Count = %d"*/, mFPS, mMilliSecPerFrame/*, mNumTris, mNumVertices*/);

	RECT R = { 5, 5, 0, 0 };
	HR(mFont->DrawText(0, buffer, -1, &R, DT_NOCLIP, D3DCOLOR_XRGB(0, 0, 0)));

}
