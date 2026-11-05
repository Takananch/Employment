#pragma once
#include "StageBase.h"

class Stage2 : public StageBase
{
public:
    Stage2();
    ~Stage2() override;
public:
    void Init() override;
    void Load() override;
    void Start() override;
    void Draw() override;
    void Fin() override;

private:
    int m_Stage2Handle; // Stage2ƒ‚ƒfƒ‹‚Ìƒnƒ“ƒhƒ‹
};