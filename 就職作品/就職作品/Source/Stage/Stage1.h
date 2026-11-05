#pragma once
#include "StageBase.h"

class Stage1 : public StageBase
{
public:
    Stage1();
    ~Stage1() override;

public:
    void Init() override;
    void Load() override;
    void Start() override;
    void Draw() override;
    void Fin() override;

private:
    int m_Stage1Handle; // Stage1ƒ‚ƒfƒ‹‚Ìƒnƒ“ƒhƒ‹
};