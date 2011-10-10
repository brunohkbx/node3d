#include "UIIcon.h"
#include "RenderSystem.h"
#include "UIDialog.h"
#include "Graphics.h"
#include "SkeletonNode.h"
#include "RPGSkyUIGraph.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//void* s_pTexture = NULL;

CUIIcon::CUIIcon()
	:m_nIconID(-1)
	,s_pTexture(NULL)
{
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CUIIcon::~CUIIcon()
{
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CUIIcon::OnFrameMove(double fTime, float fElapsedTime)
{
	CUIButton::OnFrameMove(fTime, fElapsedTime);
	if (s_pTexture==NULL)
	{
		s_pTexture = UIGraph::getInstance().createTexture("data\\ui\\icon.tga");
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CUIIcon::OnFrameRender(const Matrix & mTransform, double fTime, float fElapsedTime)
{
	CUIButton::OnFrameRender(mTransform, fTime, fElapsedTime);
	RECT rcDest={0,0,32,32};
	if (s_pTexture && m_nIconID>-1)
	{
		RECT rcSrc={(m_nIconID%16)*32,(m_nIconID/16)*32,(m_nIconID%16)*32+32,(m_nIconID/16)*32+32};
		UIGraph::getInstance().drawSprite(rcDest, s_pTexture, 0xFFFFFFFF, &rcSrc);
	}
	//Node3DUIGraph::getInstance().drawText(L"2", 3, rcDest, ALIGN_TYPE_CENTER);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CUIIcon::OnMouseMove(POINT point)
{
	CUIButton::OnMouseMove(point);
	// ----
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CUIIcon::OnMouseWheel(POINT point,short wheelDelta)
{
	CUIButton::OnMouseWheel(point, wheelDelta);
	// ----
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CUIIcon::OnLButtonDown(POINT point)
{
	CUIButton::OnLButtonDown(point);
	// ----
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CUIIcon::OnLButtonUp(POINT point)
{
	CUIButton::OnLButtonUp(point);
	// ----
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CUIIcon::OnRButtonDown(POINT point)
{
	CUIButton::OnRButtonDown(point);
	// ----
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CUIIcon::OnRButtonUp(POINT point)
{
	CUIButton::OnRButtonUp(point);
	// ----
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CUIIcon::OnMButtonDown(POINT point)
{
	CUIButton::OnMButtonDown(point);
	// ----
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CUIIcon::OnMButtonUp(POINT point)
{
	CUIButton::OnMButtonUp(point);
	// ----
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CUIIcon::OnSize(const CRect<int>& rc)
{
	CUIButton::OnSize(rc);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "CsvFile.h"
#define ITEM_CVS_PATCH		"Data\\CSV\\Item.csv"
void CUIIcon::setItemData(const ItemData itemData)
{
	m_ItemData = itemData;
	// ----
	m_nIconID = m_ItemData.cType*16+m_ItemData.cIndex;
	// ----
	CCsvFile csv;
	// ----
	csv.open(ITEM_CVS_PATCH);
	// ----
	csv.seek(0, m_ItemData.cType);
	csv.seek(1, m_ItemData.cIndex);
	// ----
	std::string strTip;
	strTip.append( "[align=center]" );
	// name
	if (m_ItemData.level>6)
	{
		strTip.append( "[color=255,255,0]" );
	}
	else if (m_ItemData.level>4)
	{
		strTip.append( "[color=128,128,255]" );
	}
	else
	{
		strTip.append( "[color=255,255,255]" );
	}
	strTip.append( csv.getStr("Name","NULL") );
	if (m_ItemData.level>0)
	{
		strTip.append( " +" );
		char szTemp[256];
		strTip.append( itoa(m_ItemData.level,szTemp,10) );
	}
	strTip.append( "[/color][br]" );
	// DamMin-DamMax
	strTip.append( "攻击力: " );
	strTip.append( csv.getStr("DamMin","NULL") );
	strTip.append( "-" );
	strTip.append( csv.getStr("DamMax","NULL") );
	strTip.append( "[br]" );
	// Speed
	strTip.append( "攻击速度: " );
	strTip.append( csv.getStr("Speed","NULL") );
	strTip.append( "[br]" );
	// Dur
	strTip.append( "耐久度: 0\\" );
	strTip.append( csv.getStr("Dur","NULL") );
	strTip.append( "[br]" );
	// Str
	strTip.append( "所需力量: " );
	strTip.append( csv.getStr("Str","NULL") );
	strTip.append( "[br]" );
	//
	strTip.append( "[/align]" );
	// ----
	SetTip(s2ws(strTip));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------