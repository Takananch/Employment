#pragma once

class StageBase;

class StageManager
{
public:
    StageManager();
    ~StageManager();

public:
    static void CreateInstance() { if (!m_Instance)m_Instance = new StageManager; }
    static StageManager* GetInstance() { return m_Instance; }
    static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

public:
    void Init();
    void Load();
    void Start();
    void Step();
    void Update();
    void Draw();
    void Fin();

    bool ChangeStage(int stageNumber);                                  // ステージを切り替える
	StageBase* GetStage() const { return m_Stage; }                     // 現在のステージを取得
	int GetCurrentStageNumber() const { return m_CurrentStageNumber; }  // 現在のステージ番号を取得

private:
	static StageManager* m_Instance;    // シングルトンインスタンス

    StageBase* m_Stage;                 // 現在のステージ
    int m_CurrentStageNumber;           // 現在のステージ番号
};