#include "Expand.h"
#include <iostream>
#include <map>
#include <vector>

const int ALPHABET_SIZE = 95; // 26

const char START_ALPHABET_SYMBOL = ' '; //'a'

struct BohrVertex
{
    int nextVertex[ALPHABET_SIZE], patternNumber, suffixLink, autoMove[ALPHABET_SIZE], parrent, suffixFineLink;
    bool flag;
    char symbol;
};

std::vector<BohrVertex> bohr;
std::vector<std::string> pattern;

void AddParamsToBohr(Dictionary params)
{
    for (auto it = params.begin(); it != params.end(); it++)
    {
        AddStringToBohr(it->first);
    }
}

//������������� ���������
BohrVertex MakeBohrVertex(int parent, char symbol)
{ //�������� ����� ���� � ������ �� ����� � ����
    BohrVertex vertex;
    //(255)=(2^8-1)=(��� ������� � ������ ����� ������)=(-1 � �������������� ���� ������ 4-�������� ����� int)
    //������ memset, ������ �������� ����������
    memset(vertex.nextVertex, 255, sizeof(vertex.nextVertex));
    memset(vertex.autoMove, 255, sizeof(vertex.autoMove));
    vertex.flag = false;
    vertex.suffixLink = -1;
    vertex.parrent = parent;
    vertex.symbol = symbol;
    vertex.suffixFineLink = -1;
    return vertex;
}

void InitBohr()
{
    //��������� ������������ ������� - ������
    bohr.clear();
    bohr.push_back(MakeBohrVertex(0, '$'));
}

void AddStringToBohr(const std::string &s)
{
    int num = 0; //�������� � �����
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i] - START_ALPHABET_SYMBOL; //�������� ����� � ��������
        if (bohr[num].nextVertex[ch] == -1)
        { //-1 - ������� ���������� �����
            bohr.push_back(MakeBohrVertex(num, ch));
            bohr[num].nextVertex[ch] = bohr.size() - 1;
        }
        num = bohr[num].nextVertex[ch];
    }
    bohr[num].flag = true;
    pattern.push_back(s);
    bohr[num].patternNumber = pattern.size() - 1;
}

bool IsStringInBohr(const std::string &s)
{
    int num = 0;
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i] - START_ALPHABET_SYMBOL;
        if (bohr[num].nextVertex[ch] == -1)
        {
            return false;
        }
        num = bohr[num].nextVertex[ch];
    }
    return true;
}
//������� � ����� ����
int GetAutoMove(int v, char ch);
//������������� �������
int GetSuffLink(int v)
{
    //������������� ������� if
    if (bohr[v].suffixLink == -1)           //���� ��� �� �������
        if (v == 0 || bohr[v].parrent == 0) //���� v - ������ ��� ������ v - ������
            bohr[v].suffixLink = 0;
        else
            bohr[v].suffixLink = GetAutoMove(GetSuffLink(bohr[v].parrent), bohr[v].symbol);
    return bohr[v].suffixLink;
}
//�������� �������� ������
int GetAutoMove(int v, char ch)
{
    //������������� ������� if
    if (bohr[v].autoMove[ch] == -1)
        if (bohr[v].nextVertex[ch] != -1)
            bohr[v].autoMove[ch] = bohr[v].nextVertex[ch];
        else if (v == 0)
            bohr[v].autoMove[ch] = 0;
        else
            bohr[v].autoMove[ch] = GetAutoMove(GetSuffLink(v), ch);
    return bohr[v].autoMove[ch];
}

//������: ��� ���������� Fine Suff Link
int GetSuffFlink(int v)
{
    if (bohr[v].suffixFineLink == -1)
    {
        int u = GetSuffLink(v);
        if (u == 0) //���� v - ������, ���� ���. ������ v ��������� �� ������
        {
            bohr[v].suffixFineLink = 0;
        }
        else
        {
            bohr[v].suffixFineLink = (bohr[u].flag) ? u : GetSuffFlink(u);
        }
    }
    return bohr[v].suffixFineLink;
}
//�������� �������� �������, ����� ������, ��� �� ���������
void Check(int v, int i, std::vector<EntryPointAndSubstring> &result)
{
    for (int u = v; u != 0; u = GetSuffFlink(u))
    {
        //�������� ������� �����������
        if (!bohr[u].flag)
        {
            continue;
        }
        if (!result.empty())
        {
            auto point = result[result.size() - 1];
            if (point.first == i - pattern[bohr[u].patternNumber].length() )
            {
                result.pop_back();
            }
        }
        result.push_back(
            std::make_pair(i - pattern[bohr[u].patternNumber].length(), pattern[bohr[u].patternNumber]));
    }
}

void FindAllPos(const std::string &s, std::vector<EntryPointAndSubstring> &result)
{
    int u = 0;
    for (int i = 0; i < s.length(); i++)
    {
        u = GetAutoMove(u, s[i] - START_ALPHABET_SYMBOL);
        Check(u, i + 1, result);
    }
}
