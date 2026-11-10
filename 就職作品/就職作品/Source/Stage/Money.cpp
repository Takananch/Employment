#include "Money.h"
#include "../Player/Player.h"
#include "../StoneGem/Gem.h"
#include <vector>

Money::Money()
{
    m_TotalMoney = 0;
}

Money::~Money()
{
}

void Money::Init()
{
    // 新しいラン開始時に金額を初期化
    m_TotalMoney = 0;
}

int Money::Deposit(Player* player)
{
    if (player == nullptr)
    {
        return 0;
    }

    // プレイヤーが所持している宝石をすべて取り出す
    std::vector<Gem*> gems = player->TakeAllGems();

    int depositAmount = 0;

    // 宝石の価値を合計して解放
    for (Gem* gem : gems)
    {
        if (gem != nullptr)
        {
            depositAmount += gem->GetValue();
            delete gem;
        }
    }

    // 累計金額に加算
    m_TotalMoney += depositAmount;

    return depositAmount;
}