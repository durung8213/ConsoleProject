#include "BattleManager.h"
#include <Windows.h>
#include <conio.h>

BattleManager::BattleManager()
{
    
}

BattleManager::~BattleManager()
{
}

void BattleManager::BattleInit()
{
    monster = new Monster(540, "봄봄");
}

void BattleManager::BattleStartInfo()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    IsAttack = false;
    cout << endl;
    cout << "배틀 시작!" << endl;
    cout << endl;
    cout << monster->GetName() << "이 나타났습니다!" << endl;
    cout << "-----------------------------" << endl;
    cout << monster->GetName() << " 의 체력 : " << monster->GetHP() << endl;
    cout << m_player->GetName() << " 의 체력 : " << m_player->GetHP() << endl;
    cout << m_player->GetName() << " 의 마력 : " << m_player->GetMP() << endl;

}


void BattleManager::DrawMenu(const vector<string>& options, int selectedIndex)
{
    cout << "========= 메뉴 =========" << endl;;
    for (size_t i = 0; i < options.size(); ++i) {
        if (static_cast<int>(i) == selectedIndex) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // 선택된 항목: 밝은 파랑
            std::cout << "> " << options[i] << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 기본 색상으로 복원
        }
        else {
            std::cout << "  " << options[i] << endl;
        }
    }

}

void BattleManager::SelectMenu()
{
    DrawMenu(mainOptions, selectedIndex);

    int key = _getch(); // 키 입력 대기
    if (key != NULL)
    {
        if (key == 224) { // 특수 키 (화살표 등)
            key = _getch(); // 실제 키 값 읽기
            if (key == 72) { // 위쪽 화살표
                selectedIndex = (selectedIndex - 1 + mainOptions.size()) % mainOptions.size();
            }
            else if (key == 80) { // 아래쪽 화살표
                selectedIndex = (selectedIndex + 1) % mainOptions.size();
            }
        }
        else if (key == 13)
        { // 엔터 키
            if (mainOptions[selectedIndex] == "공격")
            {
                AttackToMonster();
                IsAttack = true;
            }
            else if (mainOptions[selectedIndex] == "스킬")
            {
                SetSkillMenu();
                return;
            }
            else if (mainOptions[selectedIndex] == "아이템")
            {
                UseInvenItem();
                return;
            }
            else if (mainOptions[selectedIndex] == "도망가기")
            {
                Exit();
                return;
            }
        }
        
    }

}

void BattleManager::SetSkillMenu()
{

    cout << "--- 시전할 스킬을 입력하세요 ---" << endl;
    for (const auto& pair : m_player->GetSkill())
    {
        cout << " ▶ " << pair.first << "     소비 MP : "<<pair.second<<" ";
        cout << endl;
    }
    cout<<endl;
    cout << "---------------------------" << endl;
    cout << "                     9 : 뒤로 가기" << endl;
    string skill;
    cin >> skill;
    bool IsSkilled = false;

    for (const auto& pair : m_player->GetSkill())
    {
        if (skill == "9")
        {
            return;
        }
        else if(pair.first == skill)
        {
            SkillToMonster(skill);
            IsSkilled = true;
        }
    }
    if (!IsSkilled)
    {
        cout << "잘못된 입력값입니다." << endl;
        Sleep(500);
    }
}

void BattleManager::SetUseItemMenu()
{
}

void BattleManager::UpdateBattle()
{
	//while문에서 반복해야할 내용.
    system("cls");
    //배틀 이미지 출력
    PrintBattleScene();
    //몬스터와 플레이어 정보 출력
    BattleStartInfo();

    //배틀 메뉴
    SelectMenu();

    //플레이어 & 몬스터 둘 중 하나라도 죽는다면
    CheckHP();

    //게임이 끝나지 않았고, 플레이어가 적을 공격했다면, 적도 플레이어를 공격한다.
    if (IsAttack && !BattleOver)
    {
        AttackToPlayer();
    }

}


void BattleManager::AttackToPlayer()
{
	monster->Attack(*m_player);
}

void BattleManager::CheckHP()
{
    int player = m_player->GetHP();
    int mob = monster->GetHP();

    if (player <= 0)
    {
        cout << "체력이 모두 다하셨습니다.." << endl;
        //타이틀 씬으로 돌아가는 코드
        BattleOver = true;
    }
    else if (mob <= 0)
    {
        // 쓰러뜨린 내역 + 돈 획득 내용을 monster 함수에 정의
        monster->Dead();
        //돈 획득
        m_player->m_Inven.SetGill(m_player->m_Inven.GetGill() + monster->GetGill());
        delete monster;
        BattleOver = true;
    }
}


void BattleManager::AttackToMonster()
{
	m_player->Attack(monster);
}

void BattleManager::SkillToMonster(const string& skill)
{
    bool result = m_player->Skill(monster, skill);
    //스킬을 사용했을 때, 스킬을 성공적으로 시전했다면
    if (result)
    {  
        IsAttack = true;
    }
    //마나가 없거나, 뒤로갔을 경우
    else
    {
        IsAttack = false;
    }
}

void BattleManager::UseInvenItem()
{
    m_player->UseItem();
}

void BattleManager::Exit()
{
    cout << "재빠르게 도망을 칩니다..." << endl;
    Sleep(1000); 
    BattleOver = true;
}

//배틀 화면 배경 이미지 (노가다..)
void BattleManager::PrintBattleScene()
{
    //1-3
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
    cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
    cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■■■"<<endl;
    
    //4
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //어두운 노랑
    cout << "■"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);   //노랑
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■"<<endl;

    //5
    cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //어두운 노랑
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);   //노랑
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //어두운 노랑
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■" << endl;

    //6
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //어두운 노랑
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);   //노랑
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //어두운 노랑
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■"<< endl;

    //7
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■" << endl;

    //8
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■" ;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■" << endl;

    //9
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■" << endl;

    //10
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■■■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■" << endl;

    //11
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■" << endl;

    //12
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■" << endl;

    //13
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■";    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■"<<endl;

    //14
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■" << endl;

    //15
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■" << endl;

    //16
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■" << endl;

    //17
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■" << endl;

    //18
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■" << endl;

    //19
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■" << endl;

    //20
    cout << "■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "■■■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "■■■■" << endl;


    //21
    cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
    cout << "■■■" << endl;

    //22
    cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
    cout << "■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "■■■■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "■";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "■■";







}
