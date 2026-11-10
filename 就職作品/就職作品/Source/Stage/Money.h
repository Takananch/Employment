#pragma once

class Player;

class Money
{
public:
    Money();
    ~Money();

    void Init();

    // •óÎ‚ğ”[•i‚µ‚Ä‹àŠz‚ğ‰ÁZ
    int Deposit(Player* player);

    // —İŒv‹àŠz‚ğæ“¾
    int GetTotalMoney() const { return m_TotalMoney; }

private:
    int m_TotalMoney;   // —İŒv”[•i‹àŠz
};