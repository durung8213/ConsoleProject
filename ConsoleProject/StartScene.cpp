#include "StartScene.h"

void StartScene::ShowMainScreen()
{
}


void StartScene::SetMenu(const vector<string>& options, int selectedIndex)
{
    cout << "\t\t\t\t\t=== �޴� ===\t\t\t\t\t" << endl;;
    for (size_t i = 0; i < options.size(); ++i) {
        if (static_cast<int>(i) == selectedIndex) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // ���õ� �׸�: ���� �Ķ�
            std::cout << "\t\t\t\t\t> " << options[i] << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // �⺻ �������� ����
        }
        else {
            std::cout << "\t\t\t\t\t" << options[i] << endl;
        }
    }
}

void StartScene::SelectMenu()
{
    ShowGameInfo();
    SetMenu(startMenu, selectedIndex);

    int key = _getch(); // Ű �Է� ���
    if (key != NULL)
    {
        if (key == 224) { // Ư�� Ű (ȭ��ǥ ��)
            key = _getch(); // ���� Ű �� �б�
            if (key == 72) { // ���� ȭ��ǥ
                selectedIndex = static_cast<int>(selectedIndex - 1 + startMenu.size()) % startMenu.size();
            }
            else if (key == 80) { // �Ʒ��� ȭ��ǥ
                selectedIndex = (selectedIndex + 1) % startMenu.size();
            }
        }
        else if (key == 13)
        { // ���� Ű
            if (startMenu[selectedIndex] == "���� ����")
            {
                GameStart = true;
            }
            else if (startMenu[selectedIndex] == "���� ����")
            {
                GameOver = true;
                return;
            }
        }
        system("cls");
    }
}

//Ÿ��Ʋ ȭ��...
void StartScene::ShowGameInfo()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���������������������������������������������" << endl;
    cout << "���������������������������������������������" << endl;
    cout << "���������������������������������������������" << endl;
    cout << "���������������������������������������������" << endl;
    cout << "���������������������������������������������" << endl;

    //6
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����������"<<endl;

    //7
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "������������" << endl;

    //8
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����������" << endl;

    //14
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "������������"<<endl;

    //14
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����������"<<endl;

    //11 12
    cout << "���������������������������������������������" << endl;
    cout << "���������������������������������������������" << endl;


    //13
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����������" << endl;

    //14
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����������" << endl;

    //1
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����������" << endl;

    //16
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "�����������"<<endl;

    //17
    cout << "���������";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "����";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "���";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "�����������" << endl;

    cout << "���������������������������������������������" << endl;
    cout << "���������������������������������������������" << endl;
    cout << "���������������������������������������������" << endl;
    cout << "���������������������������������������������" << endl;
    cout << "���������������������������������������������" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

}