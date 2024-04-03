#include <bits/stdc++.h>
using namespace std;

class Branches
{
public:
    int BTechICT{0};
    int BTechMNC{0};
    int BTechEVD{0};
    int MTechICT{0};
};
class Candidate
{
public:
    string info[12];
};
int Round_data(ifstream &file)
{
    string s;
    getline(file, s, ',');
    if ((s[s.length() - 1]) >= 48 && (s[s.length() - 1]) <= 57)
    {
        return (s[s.length() - 1]) - '0';
    }
    else
    {
        if (s.find("HR") != string::npos)
        {
            return 4;
        }
        else
        {
            return 5;
        }
    }
}
class Final : public Branches
{
public:
    string EndDate;
    string StartDate;
    vector<Candidate> v;
    vector<string> CR;
};
class HR : public Branches
{
public:
    string EndDate;
    string StartDate;
    vector<Candidate> v;
    vector<string> CR;
};
class Round3 : public Branches
{
public:
    string EndDate;
    string StartDate;
    vector<Candidate> v;
    vector<string> CR;
    void display()
    {
        for (auto it : v)
        {
            for (int i = 0; i < 12; i++)
            {
                cout << it.info[i] << " ";
            }
            cout << endl;
        }
    }
};

class Round2 : public Branches
{
public:
    string EndDate;
    string StartDate;
    vector<Candidate> v;
    vector<string> CR;
    void display()
    {
        for (auto it : v)
        {
            for (int i = 0; i < 12; i++)
            {
                cout << it.info[i] << " ";
            }
            cout << endl;
        }
    }
};
class Round1 : public Branches
{
public:
    string EndDate;
    string StartDate;
    vector<Candidate> v;
    vector<string> CR;
    void display()
    {
        for (auto it : v)
        {
            for (int i = 0; i < 12; i++)
            {
                cout << it.info[i] << " ";
            }
            cout << endl;
        }
    }
};

map<string, Candidate> mpround1;
map<string, Candidate> mpround2;
map<string, Candidate> mpround3;
map<string, Candidate> mpround4;
map<string, Candidate> mpround5;
class Company
{
public:
    string cname;
    Round1 r1;
    Round2 r2;
    Round3 r3;
    HR r4;
    Final r5;

    int TotalNoOfCandidates(int n)
    {
        switch (n)
        {
        case 1:
            return r1.v.size();
        case 2:
            return r2.v.size();
        case 3:
            return r3.v.size();
        case 4:
            return r4.v.size();
        case 5:
            return r5.v.size();
        }
    }
    int Selected_From_Round(int n)
    {
        switch (n)
        {
        case 1:
            return r2.v.size();
        case 2:
            return r3.v.size();
        case 3:
            return r4.v.size();
        case 4:
            return r5.v.size();
        }
    }
    double successRate(int n)
    {
        switch (n)
        {
        case 1:
            return r2.v.size() * 100.0 / r1.v.size();
        case 2:
            return r3.v.size() * 100.0 / r2.v.size();
        case 3:
            return r4.v.size() * 100.0 / r3.v.size();
        case 4:
            return r5.v.size() * 100.0 / r4.v.size();
        }
    }
    double TotalSuccessRate()
    {
        return r5.v.size() * 100.0 / r1.v.size();
    }
};
vector<Company> total;
void reading(ifstream &file)
{

    int Round_no = Round_data(file);
    string s;
    string tempp;

    file.seekg(0);
    for (int i = 0; i < 3; i++)
    {
        getline(file, s);
    }
    for (int i = 0; i < 5; i++)
    {
        tempp = s.substr(0, s.find(","));
        s.erase(0, s.find(",") + 1);
    }
    for (auto &it : total)
    {
        if (it.cname == tempp)
        {
            file.seekg(0);
            for (int i = 0; i < 2; i++)
            {
                getline(file, s);
            }
            getline(file, s);
            int pos = s.find("START DATE");
            string startDate = s.substr(pos + 11, 10);
            switch (Round_no)
            {
            case 1:
                it.r1.StartDate = startDate;
                break;
            case 2:
                it.r2.StartDate = startDate;
                break;
            case 3:
                it.r3.StartDate = startDate;
                break;
            case 4:
                it.r4.StartDate = startDate;
                break;
            case 5:
                it.r5.StartDate = startDate;
                break;
            }
            file.seekg(0);
            for (int i = 0; i < 3; i++)
            {
                getline(file, s);
            }
            getline(file, s);
            pos = s.find("END DATE");
            string endDate = s.substr(pos + 9, 10);
            switch (Round_no)
            {
            case 1:
                it.r1.EndDate = endDate;
                break;
            case 2:
                it.r2.EndDate = endDate;
                break;
            case 3:
                it.r3.EndDate = endDate;
                break;
            case 4:
                it.r4.EndDate = endDate;
                break;
            case 5:
                it.r5.EndDate = endDate;
                break;
            }
            file.seekg(0);
            for (int i = 0; i < 4; i++)
            {
                getline(file, s);
            }
            for (int i = 0; i < 5; i++)
            {
                tempp = s.substr(0, s.find(","));
                s.erase(0, s.find(",") + 1);
            }
            while (tempp[tempp.length() - 1] >= '0' && tempp[tempp.length() - 1] <= '9')
            {
                switch (Round_no)
                {
                case 1:
                    it.r1.CR.emplace_back(tempp);
                    break;
                case 2:
                    it.r2.CR.emplace_back(tempp);
                    break;
                case 3:
                    it.r3.CR.emplace_back(tempp);
                    break;
                case 4:
                    it.r4.CR.emplace_back(tempp);
                    break;
                case 5:
                    it.r5.CR.emplace_back(tempp);
                    break;
                }
                getline(file, s);
                for (int i = 0; i < 5; i++)
                {
                    tempp = s.substr(0, s.find(","));
                    s.erase(0, s.find(",") + 1);
                }
            }
            while (getline(file, s))
            {
                Candidate c;
                size_t ind = 0;
                string token;
                int no = -1;
                while (no <= 11 && ((ind = s.find(",")) != string::npos))
                {
                    token = s.substr(0, ind);
                    if (no == -1 && (s[0] < 48 || s[0] > 57))
                    {
                        return;
                    }
                    if (no >= 0)
                    {
                        c.info[no] = token;
                        if (no == 5)
                        {
                            if (c.info[no][4] == '0')
                            {
                                switch (Round_no)
                                {
                                case 1:
                                    switch (c.info[no][5])
                                    {
                                    case '1':
                                        it.r1.BTechICT++;
                                        break;
                                    case '2':
                                        it.r1.BTechEVD++;
                                        break;
                                    case '3':
                                        it.r1.BTechMNC++;
                                        break;
                                    }
                                    break;
                                case 2:
                                    switch (c.info[no][5])
                                    {
                                    case '1':
                                        it.r2.BTechICT++;
                                        break;
                                    case '2':
                                        it.r2.BTechEVD++;
                                        break;
                                    case '3':
                                        it.r2.BTechMNC++;
                                        break;
                                    }
                                    break;
                                case 3:
                                    switch (c.info[no][5])
                                    {
                                    case '1':
                                        it.r3.BTechICT++;
                                        break;
                                    case '2':
                                        it.r3.BTechEVD++;
                                        break;
                                    case '3':
                                        it.r3.BTechMNC++;
                                        break;
                                    }
                                    break;
                                case 4:
                                    switch (c.info[no][5])
                                    {
                                    case '1':
                                        it.r4.BTechICT++;
                                        break;
                                    case '2':
                                        it.r4.BTechEVD++;
                                        break;
                                    case '3':
                                        it.r4.BTechMNC++;
                                        break;
                                    }
                                    break;
                                case 5:
                                    switch (c.info[no][5])
                                    {
                                    case '1':
                                        it.r5.BTechICT++;
                                        break;
                                    case '2':
                                        it.r5.BTechEVD++;
                                        break;
                                    case '3':
                                        it.r5.BTechMNC++;
                                        break;
                                    }
                                    break;
                                }
                            }
                            else
                            {
                                switch (Round_no)
                                {
                                case 1:
                                    it.r1.MTechICT++;
                                    break;
                                case 2:
                                    it.r2.MTechICT++;
                                    break;
                                case 3:
                                    it.r3.MTechICT++;
                                    break;
                                case 4:
                                    it.r4.MTechICT++;
                                    break;
                                case 5:
                                    it.r5.MTechICT++;
                                    break;
                                }
                            }
                        }
                    }
                    s.erase(0, ind + 1);
                    no++;
                }
                switch (Round_no)
                {
                case 1:
                    mpround1[c.info[5] + "-" + it.cname] = c;
                    it.r1.v.emplace_back(c);
                    break;
                case 2:
                    mpround2[c.info[5] + "-" + it.cname] = c;
                    it.r2.v.emplace_back(c);
                    break;
                case 3:
                    mpround3[c.info[5] + "-" + it.cname] = c;
                    it.r3.v.emplace_back(c);
                    break;
                case 4:
                    mpround4[c.info[5] + "-" + it.cname] = c;
                    it.r4.v.emplace_back(c);
                    break;
                case 5:
                    mpround5[c.info[5] + "-" + it.cname] = c;
                    it.r5.v.emplace_back(c);
                    break;
                }
            }
        }
    }
    Company newcompany;
    newcompany.cname = tempp;

    file.seekg(0);
    for (int i = 0; i < 2; i++)
    {
        getline(file, s);
    }
    getline(file, s);
    int pos = s.find("START DATE");
    string startDate = s.substr(pos + 11, 10);
    switch (Round_no)
    {
    case 1:
        newcompany.r1.StartDate = startDate;
        break;
    case 2:
        newcompany.r2.StartDate = startDate;
        break;
    case 3:
        newcompany.r3.StartDate = startDate;
        break;
    case 4:
        newcompany.r4.StartDate = startDate;
        break;
    case 5:
        newcompany.r5.StartDate = startDate;
        break;
    }

    file.seekg(0);
    for (int i = 0; i < 3; i++)
    {
        getline(file, s);
    }
    getline(file, s);
    pos = s.find("END DATE");
    string endDate = s.substr(pos + 9, 10);
    switch (Round_no)
    {
    case 1:
        newcompany.r1.EndDate = endDate;
        break;
    case 2:
        newcompany.r2.EndDate = endDate;
        break;
    case 3:
        newcompany.r3.EndDate = endDate;
        break;
    case 4:
        newcompany.r4.EndDate = endDate;
        break;
    case 5:
        newcompany.r5.EndDate = endDate;
        break;
    }

    file.seekg(0);
    for (int i = 0; i < 4; i++)
    {
        getline(file, s);
    }
    for (int i = 0; i < 5; i++)
    {
        tempp = s.substr(0, s.find(","));
        s.erase(0, s.find(",") + 1);
    }
    while (tempp[tempp.length() - 1] >= '0' && tempp[tempp.length() - 1] <= '9')
    {
        switch (Round_no)
        {
        case 1:
            newcompany.r1.CR.emplace_back(tempp);
            break;
        case 2:
            newcompany.r2.CR.emplace_back(tempp);
            break;
        case 3:
            newcompany.r3.CR.emplace_back(tempp);
            break;
        case 4:
            newcompany.r4.CR.emplace_back(tempp);
            break;
        case 5:
            newcompany.r5.CR.emplace_back(tempp);
            break;
        }
        getline(file, s);
        for (int i = 0; i < 5; i++)
        {
            tempp = s.substr(0, s.find(","));
            s.erase(0, s.find(",") + 1);
        }
    }

    while (getline(file, s))
    {
        Candidate c;
        size_t ind = 0;
        string token;
        int no = -1;
        while (no <= 11 && ((ind = s.find(",")) != string::npos))
        {
            token = s.substr(0, ind);
            if (no == -1 && (s[0] < 48 || s[0] > 57))
            {
                total.emplace_back(newcompany);
                return;
            }
            if (no >= 0)
            {
                c.info[no] = token;
                if (no == 5)
                {
                    if (c.info[no][4] == '0')
                    {
                        switch (Round_no)
                        {
                        case 1:
                            switch (c.info[no][5])
                            {
                            case '1':
                                newcompany.r1.BTechICT++;
                                break;
                            case '2':
                                newcompany.r1.BTechEVD++;
                                break;
                            case '3':
                                newcompany.r1.BTechMNC++;
                                break;
                            }
                            break;
                        case 2:
                            switch (c.info[no][5])
                            {
                            case '1':
                                newcompany.r2.BTechICT++;
                                break;
                            case '2':
                                newcompany.r2.BTechEVD++;
                                break;
                            case '3':
                                newcompany.r2.BTechMNC++;
                                break;
                            }
                            break;
                        case 3:
                            switch (c.info[no][5])
                            {
                            case '1':
                                newcompany.r3.BTechICT++;
                                break;
                            case '2':
                                newcompany.r3.BTechEVD++;
                                break;
                            case '3':
                                newcompany.r3.BTechMNC++;
                                break;
                            }
                            break;
                        case 4:
                            switch (c.info[no][5])
                            {
                            case '1':
                                newcompany.r4.BTechICT++;
                                break;
                            case '2':
                                newcompany.r4.BTechEVD++;
                                break;
                            case '3':
                                newcompany.r4.BTechMNC++;
                                break;
                            }
                            break;
                        case 5:
                            switch (c.info[no][5])
                            {
                            case '1':
                                newcompany.r5.BTechICT++;
                                break;
                            case '2':
                                newcompany.r5.BTechEVD++;
                                break;
                            case '3':
                                newcompany.r5.BTechMNC++;
                                break;
                            }
                            break;
                        }
                    }
                    else
                    {
                        switch (Round_no)
                        {
                        case 1:
                            newcompany.r1.MTechICT++;
                            break;
                        case 2:
                            newcompany.r2.MTechICT++;
                            break;
                        case 3:
                            newcompany.r3.MTechICT++;
                            break;
                        case 4:
                            newcompany.r4.MTechICT++;
                            break;
                        case 5:
                            newcompany.r5.MTechICT++;
                            break;
                        }
                    }
                }
            }
            s.erase(0, ind + 1);
            no++;
        }
        switch (Round_no)
        {
        case 1:
            mpround1[c.info[5] + "-" + newcompany.cname] = c;
            newcompany.r1.v.emplace_back(c);
            break;
        case 2:
            mpround2[c.info[5] + "-" + newcompany.cname] = c;
            newcompany.r2.v.emplace_back(c);
            break;
        case 3:
            mpround3[c.info[5] + "-" + newcompany.cname] = c;
            newcompany.r3.v.emplace_back(c);
            break;
        case 4:
            mpround4[c.info[5] + "-" + newcompany.cname] = c;
            newcompany.r4.v.emplace_back(c);
            break;
        case 5:
            mpround5[c.info[5] + "-" + newcompany.cname] = c;
            newcompany.r5.v.emplace_back(c);
            break;
        }
    }
}
void GetData(string s)
{
    cout << "Details: " << endl;
    cout << "Student name: " << mpround1[s].info[0] << endl;
    cout << "Interview date: " << mpround1[s].info[1] << endl;
    cout << "Interview status: " << mpround1[s].info[2] << endl;
    cout << "Interview Start Time: " << mpround1[s].info[3] << endl;
    cout << "Interview End Time: " << mpround1[s].info[4] << endl;
    cout << "Student ID: " << mpround1[s].info[5] << endl;
    cout << "Email: " << mpround1[s].info[6] << endl;
    cout << "Program: " << mpround1[s].info[7] << endl;
    cout << "Contact No.: " << mpround1[s].info[8] << endl;
    cout << "WhatsApp No.: " << mpround1[s].info[9] << endl;
    cout << "Alternate No.: " << mpround1[s].info[10] << endl;
    cout << "Skype ID: " << mpround1[s].info[11] << endl;
}

void Selection_data_of_candidate(string s)
{
    if (mpround1[s].info[0] == "")
    {
        GetData(s);
        cout << "The name of the person with provided ID number is not found in the list of the candidates\n";
        return;
    }
    if (mpround5[s].info[0] != "")
    {
        cout << "This candidates selected for the placement.\n";
        return;
    }
    if (mpround4[s].info[0] != "")
    {
        cout << "This candidate is eliminated in HR round.\n";
        return;
    }
    if (mpround3[s].info[0] != "")
    {
        cout << "This candidate is eliminated in 3rd round.\n";
        return;
    }
    if (mpround2[s].info[0] != "")
    {
        cout << "This candidate is eliminated in 2nd round.\n";
        return;
    }
    if (mpround1[s].info[0] != "")
    {
        cout << "This candidate is eliminated in 1st round.\n";
        return;
    }
}

void PlacementChances()
{
    vector<pair<double, string>> v;
    for (auto it : total)
    {
        v.emplace_back(it.TotalSuccessRate(), it.cname);
    }
    sort(v.rbegin(), v.rend());
    for (auto it : v)
    {
        cout << it.first;
        cout << it.second << endl;
    }
}

int main()
{
    ifstream file1("Finalround1.csv");
    reading(file1);
    ifstream file2("Finalselection.csv");
    reading(file2);

    ifstream google("Googler1.csv");
    reading(google);
    ifstream googlefinal("Googlefinal.csv");
    reading(googlefinal);
    // for(auto it: total){
    //     cout << it.cname;
    //     it.r1.display();
    //     cout << it.r1.BTechICT<<endl;
    //     cout << it.r1.MTechICT<<endl;
    //     cout << it.r1.StartDate<<endl;
    //     cout << it.r1.EndDate<<endl;
    // }
    // for(auto it: total){
    //     cout << it.cname;
    //     it.r2.display();
    //     cout << it.r2.BTechICT<<endl;
    //     cout << it.r2.MTechICT<<endl;
    //     cout << it.r2.StartDate<<endl;
    //     cout << it.r2.EndDate<<endl;
    // }

    // if(mpround1["234235345-[asdhflhds]"].info[0]==""){cout << "Yes bro!!!!";}
    Selection_data_of_candidate("202001008-[Microsoft]");

    PlacementChances();
    return 0;
}
