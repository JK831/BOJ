#include <string>
#include <vector>
#include <map>

#include <sstream>

using namespace std;

enum StringType
{
    NONE = 0,
    ENTER,
    LEAVE,
    CHANGE,
};

vector<string> Split(string input, char delimiter)
{
    vector<string> ret;
    stringstream ss(input);
    string tmp;
    
    while(getline(ss, tmp, delimiter))
        ret.push_back(tmp);
    
    return ret;  
}

void ParseRecord(string record, StringType& stringType, string& uid, string& nickName)
{
    const vector<string>& parsed = Split(record, ' ');
    
    if (parsed[0] == "Enter")
    {
        stringType = ENTER;
        uid = parsed[1];
        nickName = parsed[2];
    }
    else if (parsed[0] == "Leave")
    {
        stringType = LEAVE;
        uid = parsed[1];
    }
    else if (parsed[0] == "Change")
    {
        stringType = CHANGE;
        uid = parsed[1];
        nickName = parsed[2];
    }
}

vector<string> solution(vector<string> record) {
    vector<string> answer;
    map<string, string> idMap;
    vector<pair<string, StringType>> record2;
    
    for (const string& rec : record)
    {
        StringType stringType = NONE;
        string uid, nickName;
        ParseRecord(rec, stringType, uid, nickName);
        
        if (stringType == NONE)
            continue;
        
        switch (stringType)
        {
            case ENTER:
                idMap[uid] = nickName;
                record2.push_back(make_pair(uid, stringType));
                break;
            case LEAVE:
                record2.push_back(make_pair(uid, stringType));
                break;
            case CHANGE:
                idMap[uid] = nickName;
                break;
            
        }
    }
    
    for(const pair<string, StringType>& rec : record2)
    {
        string pta = idMap[rec.first] + "님이 ";
        pta += (rec.second == ENTER) ? "들어왔습니다." : "나갔습니다.";
        answer.push_back(pta);
    }
    return answer;
}