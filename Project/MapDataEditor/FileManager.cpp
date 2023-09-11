#include <GameEngineContents/PreCompile.h>
#include "FileManager.h"

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

void FileManager::FileLoad(int MaxX, int MaxY, std::vector<unsigned int>& IndexData)
{
    GameEngineWindow MainWindow;
    std::string FilePath = "";

    OPENFILENAME OFN;

    TCHAR filePathName[200] = L"";
    TCHAR lpstrFile[200] = L"";
    static TCHAR filter[] = L"��� ����\0*.*\0";

    memset(&OFN, 0, sizeof(OPENFILENAME));
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = MainWindow.GetHWND();
    OFN.lpstrFilter = filter;
    OFN.lpstrFile = lpstrFile;
    OFN.nMaxFile = 100;
    OFN.lpstrInitialDir = L".";


    while (GetOpenFileName(&OFN) != 0)
    {
        wsprintf(filePathName, L"%s ������ ���ڽ��ϱ�?", OFN.lpstrFile);
        if (MessageBox(MainWindow.GetHWND(), filePathName, L"���� ����", MB_YESNO) == IDYES)
        {
            FilePath = GameEngineString::UnicodeToAnsi(OFN.lpstrFile);

            FILE* File;
            fopen_s(&File, FilePath.c_str(), "rb");

            for (int i = 0; i < MaxY * MaxX; i++)
            {
                fread(&IndexData[i], sizeof(unsigned int), 1, File);
            }

            fclose(File);

            break;
        }
    }
}

void FileManager::FileSave(int MaxX, int MaxY, std::vector<unsigned int>& IndexData)
{
    GameEngineWindow MainWindow;
    std::string FilePath = "";

    OPENFILENAME OFN;
    TCHAR filePathName[200] = L"";
    TCHAR lpstrFile[200] = L"";
    static TCHAR filter[] = L"��� ����\0*.*\0";

    memset(&OFN, 0, sizeof(OPENFILENAME));
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = MainWindow.GetHWND();
    OFN.lpstrFilter = filter;
    OFN.lpstrFile = lpstrFile;
    OFN.nMaxFile = 100;
    OFN.lpstrInitialDir = L".";


    while (GetSaveFileName(&OFN) != 0)
    {
        wsprintf(filePathName, L"%s �� ���Ͽ� �����Ͻðڽ��ϱ�?", OFN.lpstrFile);
        if (MessageBox(MainWindow.GetHWND(), filePathName, L"����", MB_YESNO) == IDYES)
        {
            FilePath = GameEngineString::UnicodeToAnsi(OFN.lpstrFile);

            FILE* File;
            fopen_s(&File, FilePath.c_str(), "wb");

            for (int i = 0; i < MaxY * MaxX; i++)
            {
                fwrite(&IndexData[i], sizeof(unsigned int), 1, File);
            }

            fclose(File);

            break;
        }
    }
}