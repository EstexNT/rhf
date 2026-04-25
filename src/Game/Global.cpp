#include "GameManager.hpp"
#include "FileManager.hpp"
#include "GraphicManager.hpp"
#include "Controller.hpp"
#include "LayoutManager.hpp"
#include "CellAnimManager.hpp"
#include "HBMManager.hpp"
#include "MessageManager.hpp"
#include "Sound.hpp"
#include "TickFlowManager.hpp"
#include "InputCheckManager.hpp"
#include "CheckPointManager.hpp"
#include "SceneManager.hpp"
#include "SaveData.hpp"
#include "BackupManager.hpp"
#include "SDManager.hpp"
#include "VarParam.hpp"
#include "DebugPrint.hpp"
#include "MyCanvas.hpp"
#include "DummyManager.hpp"
// #include "DebugFont.hpp"
// #include "PlayHistory.hpp"
// #include "RFLManager.hpp"
// #include "CafeTopic.hpp"

/*
 * The following global instances are located elsewhere:
 *  - gDebugConsole, in main.cpp
 *  - gDebugFont, in main.cpp
 *  - gPlayHistory, in main.cpp
 *  - gRFLManager, in main.cpp
 *  - gCafeTopic, in GameSelect/MyLayout.cpp
 */

CMyCanvasManager *gMyCanvasManager = NULL;
CMessageManager *gMessageManager = NULL;
CBackupManager *gBackupManager = NULL;
CSaveData *gSaveData = NULL;
CHBMManager *gHBMManager = NULL;
CSceneManager *gSceneManager = NULL;
CDebugPrint *gDebugPrint = NULL;
CVarParamManager *gVarParamManager = NULL;
CSDManager *gSDManager = NULL;
CCheckPointManager *gCheckPointManager = NULL;
CInputCheckManager *gInputCheckManager = NULL;
CTickFlowManager *gTickFlowManager = NULL;
CCellAnimManager *gCellAnimManager = NULL;
CDummyManager *gDummyManager = NULL;
CGameManager *gGameManager = NULL;
CSoundManager *gSoundManager = NULL;
CLayoutManager *gLayoutManager = NULL;
CControllerManager *gControllerManager = NULL;
CGraphicManager *gGraphicManager = NULL;
CFileManager *gFileManager = NULL;
