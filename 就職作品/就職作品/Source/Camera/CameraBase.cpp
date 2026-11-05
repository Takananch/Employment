#include "CameraBase.h"

CameraBase::CameraBase()
{
    m_Pos = VGet(0, 0, 0);
    m_Target = VGet(0, 0, 0);
    m_UpVec = VGet(0, 1, 0);

    m_Yaw = 0.0f;
    m_Pitch = 0.0f;
}

CameraBase::~CameraBase()
{
}