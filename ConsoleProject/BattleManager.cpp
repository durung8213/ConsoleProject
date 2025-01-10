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
    monster = new Monster(540, "����");
}

void BattleManager::BattleStartInfo()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    IsAttack = false;
    cout << endl;
    cout << "��Ʋ ����!" << endl;
    cout << endl;
    cout << monster->GetName() << "�� ��Ÿ�����ϴ�!" << endl;
    cout << "-----------------------------" << endl;
    cout << monster->GetName() << " �� ü�� : " << monster->GetHP() << endl;
    cout << m_player->GetName() << " �� ü�� : " << m_player->GetHP() << endl;
    cout << m_player->GetName() << " �� ���� : " << m_player->GetMP() << endl;

}


void BattleManager::DrawMenu(const vector<string>& options, int selectedIndex)
{
    cout << "========= �޴� =========" << endl;;
    for (size_t i = 0; i < options.size(); ++i) {
        if (static_cast<int>(i) == selectedIndex) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // ���õ� �׸�: ���� �Ķ�
            std::cout << "> " << options[i] << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // �⺻ �������� ����
        }
        else {
            std::cout << "  " << options[i] << endl;
        }
    }

}

void BattleManager::SelectMenu()
{
    DrawMenu(mainOptions, selectedIndex);

    int key = _getch(); // Ű �Է� ���
    if (key != NULL)
    {
        if (key == 224) { // Ư�� Ű (ȭ��ǥ ��)
            key = _getch(); // ���� Ű �� �б�
            if (key == 72) { // ���� ȭ��ǥ
                selectedIndex = (selectedIndex - 1 + mainOptions.size()) % mainOptions.size();
            }
            else if (key == 80) { // �Ʒ��� ȭ��ǥ
                selectedIndex = (selectedIndex + 1) % mainOptions.size();
            }
        }
        else if (key == 13)
        { // ���� Ű
            if (mainOptions[selectedIndex] == "����")
            {
                AttackToMonster();
                IsAttack = true;
            }
            else if (mainOptions[selectedIndex] == "��ų")
            {
                SetSkillMenu();
                return;
            }
            else if (mainOptions[selectedIndex] == "������")
            {
                UseInvenItem();
                return;
            }
            else if (mainOptions[selectedIndex] == "��������")
            {
                Exit();
                return;
            }
        }
        
    }

}

void BattleManager::SetSkillMenu()
{

    cout << "--- ������ ��ų�� �Է��ϼ��� ---" << endl;
    for (const auto& pair : m_player->GetSkill())
    {
        cout << " �� " << pair.first << "     �Һ� MP : "<<pair.second<<" ";
        cout << endl;
    }
    cout<<endl;
    cout << "---------------------------" << endl;
    cout << "                     9 : �ڷ� ����" << endl;
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
        cout << "�߸��� �Է°��Դϴ�." << endl;
        Sleep(500);
    }
}

void BattleManager::SetUseItemMenu()
{
}

void BattleManager::UpdateBattle()
{
	//while������ �ݺ��ؾ��� ����.
    system("cls");
    //��Ʋ �̹��� ���
    PrintBattleScene();
    //���Ϳ� �÷��̾� ���� ���
    BattleStartInfo();

    //��Ʋ �޴�
    SelectMenu();

    //�÷��̾� & ���� �� �� �ϳ��� �״´ٸ�
    CheckHP();

    //������ ������ �ʾҰ�, �÷��̾ ���� �����ߴٸ�, ���� �÷��̾ �����Ѵ�.
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
        cout << "ü���� ��� ���ϼ̽��ϴ�.." << endl;
        //Ÿ��Ʋ ������ ���ư��� �ڵ�
        BattleOver = true;
    }
    else if (mob <= 0)
    {
        // �����߸� ���� + �� ȹ�� ������ monster �Լ��� ����
        monster->Dead();
        //�� ȹ��
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
    //��ų�� ������� ��, ��ų�� ���������� �����ߴٸ�
    if (result)
    {  
        IsAttack = true;
    }
    //������ ���ų�, �ڷΰ��� ���
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
    cout << "������� ������ Ĩ�ϴ�..." << endl;
    Sleep(1000); 
    BattleOver = true;
}

//��Ʋ ȭ�� ��� �̹��� (�밡��..)
void BattleManager::PrintBattleScene()
{
    //1-3
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "���������������������������������������������" << endl;
    cout << "���������������������������������������������" << endl;
    cout << "���������������������������������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "�����"<<endl;
    
    //4
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�������������������������������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //��ο� ���
    cout << "��"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);   //���
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�����"<<endl;

    //5
    cout << "������������������������������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //��ο� ���
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);   //���
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //��ο� ���
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�����" << endl;

    //6
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "������������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //��ο� ���
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);   //���
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //��ο� ���
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "������"<< endl;

    //7
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�����������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "�������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "������" << endl;

    //8
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "����" ;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�������" << endl;

    //9
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "��������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "������" << endl;

    //10
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "����������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�����������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "������" << endl;

    //11
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�����" << endl;

    //12
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�����������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "����" << endl;

    //13
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "���";    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "����������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "������"<<endl;

    //14
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�����" << endl;

    //15
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�����" << endl;

    //16
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�����" << endl;

    //17
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "��"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "������" << endl;

    //18
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "����������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�����" << endl;

    //19
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "����������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "�����" << endl;

    //20
    cout << "������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "��������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "�����" << endl;


    //21
    cout << "������������������������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
    cout << "����" << endl;

    //22
    cout << "������������������������������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "�����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "���";







}
