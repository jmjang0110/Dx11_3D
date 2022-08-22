#include "pch.h"
#include "CTestScene.h"

#include <Engine/CResMgr.h>
#include <Engine/CCollisionMgr.h>

#include <Engine/CSceneMgr.h>
#include <Engine/CScene.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>

#include <Engine/CTransform.h>
#include <Engine/CMeshRender.h>
#include <Engine/CCollider2D.h>
#include <Engine/CParticleSystem.h>
#include <Engine/CCamera.h>
#include <Engine/CLight2D.h>
#include <Engine/CLight3D.h>

#include <Engine/CSceneFile.h>
#include <Engine/CSound.h>

#include <Script/CPlayerScript.h>
#include <Script/CCameraMoveScript.h>
#include <Script/CMissileScript.h>

#include <Script\CSceneSaveLoad.h>


void CTestScene::CreateTestScene()
{
	CScene* pCurScene = new CScene;
	CSceneMgr::GetInst()->ChangeScene(pCurScene);		

	pCurScene->SetLayerName(0, L"Tile");
	pCurScene->SetLayerName(1, L"Default");
	pCurScene->SetLayerName(2, L"Player");
	pCurScene->SetLayerName(3, L"Monster");

	// Texture 한장 로딩해보기
	CResMgr::GetInst()->Load<CTexture>(L"texture\\Player.bmp", L"texture\\Player.bmp");
	CResMgr::GetInst()->Load<CTexture>(L"texture\\MagicCircle.png", L"texture\\MagicCircle.png");

	Ptr<CTexture> pTileTex = CResMgr::GetInst()->Load<CTexture>(L"texture\\tile\\TILE_01.tga", L"texture\\tile\\TILE_01.tga");
	Ptr<CTexture> pTileNTex = CResMgr::GetInst()->Load<CTexture>(L"texture\\tile\\TILE_01_N.tga", L"texture\\tile\\TILE_01_N.tga");





	// Camera Object 추가
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pCamObj->Camera()->SetCameraAsMain();
	pCamObj->Camera()->CheckLayerMaskAll();

	pCurScene->AddObject(pCamObj, L"Default");

	// Directional Light
	CGameObject* pLight3D = new CGameObject;
	pLight3D->SetName(L"Directional Light");

	pLight3D->AddComponent(new CTransform);
	pLight3D->AddComponent(new CLight3D);

	pLight3D->Transform()->SetRelativePos(Vec3(-500.f, 0.f, 500.f));

	pLight3D->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight3D->Light3D()->SetLightDir(Vec3(1.f, -1.f, 1.f));
	pLight3D->Light3D()->SetRange(1000.f);

	pLight3D->Light3D()->SetDiffuse(Vec3(1.f, 1.f, 1.f));
	pLight3D->Light3D()->SetSpecular(Vec3(0.3f, 0.3f, 0.3f));
	pLight3D->Light3D()->SetAmbient(Vec3(0.15f, 0.15f, 0.15f));

	pCurScene->AddObject(pLight3D, L"Default");	



	//// 광원1 오브젝트 추가
	//CGameObject* pLight3D = new CGameObject;
	//pLight3D->SetName(L"Point Light 1");

	//pLight3D->AddComponent(new CTransform);
	//pLight3D->AddComponent(new CLight3D);

	//pLight3D->Transform()->SetRelativePos(Vec3(-500.f, 0.f, 500.f));

	//pLight3D->Light3D()->SetLightType(LIGHT_TYPE::POINT);
	//pLight3D->Light3D()->SetLightDir(Vec3(1.f, -1.f, 1.f));
	//pLight3D->Light3D()->SetRange(1000.f);

	//pLight3D->Light3D()->SetDiffuse(Vec3(1.f, 1.f, 1.f));
	//pLight3D->Light3D()->SetSpecular(Vec3(0.15f, 0.15f, 0.15f));
	//pLight3D->Light3D()->SetAmbient(Vec3(0.f, 0.f, 0.f));

	//pCurScene->AddObject(pLight3D, L"Default");	

	//// 광원2 오브젝트 추가
	//pLight3D = pLight3D->Clone();
	//pLight3D->SetName(L"Point Light 2");
	//pLight3D->Transform()->SetRelativePos(Vec3(500.f, 0.f, 500.f));

	//pCurScene->AddObject(pLight3D, L"Default");

	// Object
	CGameObject* pObject = new CGameObject;
	pObject->SetName(L"Object");

	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);	

	pObject->Transform()->SetRelativePos(0.f, -500.f, 500.f);
	pObject->Transform()->SetRelativeScale(4000.f, 4000.f, 1.f);
	pObject->Transform()->SetRelativeRotation(XM_PI / 2.f, 0.f, 0.f);

	pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObject->MeshRender()->SetSharedMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"material\\Std3DMtrl.mtrl"));
	pObject->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTileTex);
	pObject->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_1, pTileNTex);

	pCurScene->AddObject(pObject, L"Default");

	
	// 충돌 레이어 설정
	pCurScene->SetResKey(L"scene\\TestScene.scene");
	wstring strSceneFilePath = CPathMgr::GetInst()->GetContentPath();	
	CSceneSaveLoad::SaveScene(pCurScene, strSceneFilePath + L"scene\\TestScene.scene");
	
	//pCurScene->start();	
	pCurScene->SetSceneState(SCENE_STATE::STOP);
}
