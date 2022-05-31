#include "Expand.h"
#include <iostream>
#include <map>
#include <vector>
//разбить функцию на логические части
std::string ExpandTemplate(std::string const &tpl, const Dictionary &params)
{
    std::string result = tpl;
    std::vector<bool> wasChanged(tpl.length(), false);
    std::vector<EntryPointAndSubstring> entryPoints;
    FindAllPos(tpl, entryPoints);
    int delta = 0;
    for (int i = 0; i < entryPoints.size(); i++)
    {
        //делаем проверку, меняем ли мы уже изменённые символы
        int start = entryPoints[i].first;
        bool reModification = false;
        for (int j = 0; j < entryPoints[i].second.length(); j++)
        {
            if ((j < wasChanged.size() - start) && (wasChanged[j + start] == true))
            {
                reModification = true;
                break;
            }
        }
        if (reModification)
        {
            continue;
        }
        for (int j = 0; j < entryPoints[i].second.length(); j++)
        {
            if (j < wasChanged.size() - start)
            {
                wasChanged[j + start] = true;
            }
        }
        start = entryPoints[i].first + delta;
        result.erase(result.begin() + start, result.begin() + start + entryPoints[i].second.length());
        Dictionary::const_iterator iter = params.find(entryPoints[i].second);
        if (iter != params.end())
        {
            result.insert(start, iter->second);
            delta += iter->second.length() - entryPoints[i].second.length();
        }
    }
    return result;
}
