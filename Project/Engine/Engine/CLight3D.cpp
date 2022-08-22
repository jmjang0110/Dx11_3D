#include "pch.h"
#include "CLight3D.h"

#include "CRenderMgr.h"
#include "CTransform.h"

CLight3D::CLight3D()
	: CComponent(COMPONENT_TYPE::LIGHT3D)
	, m_LightInfo{}
	, m_iLightIdx(-1)
{
}

CLight3D::~CLight3D()
{

}

void CLight3D::update()
{
}

void CLight3D::finalupdate()
{
	m_LightInfo.vWorldPos = Transform()->GetWorldPos();
	//m_LightInfo.vLightDir = Transform()->GetWorldDir(DIR_TYPE::RIGHT);

	m_iLightIdx = CRenderMgr::GetInst()->RegisterLight3D(this);
}

void CLight3D::SaveToScene(FILE* _pFile)
{
	CComponent::SaveToScene(_pFile);

	fwrite(&m_LightInfo, sizeof(tLightInfo), 1, _pFile);
}

void CLight3D::LoadFromScene(FILE* _pFile)
{
	CComponent::LoadFromScene(_pFile);

	fread(&m_LightInfo, sizeof(tLightInfo), 1, _pFile);
}