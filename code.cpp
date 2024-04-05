#include <bits/stdc++.h> // Include necessary header file
using namespace std;


// Class to store information about a candidate
class Candidate
{
public:
    string info[12];
};

// Class to store information about the number of candidates selected from different branches
// and start and end date of the round, CR and candidate information
class Round_info
{
public:
    int BTechICT{0};
    int BTechMNC{0};
    int BTechEVD{0};
    int MTechICT{0};
    string EndDate;
    string StartDate;
    vector<Candidate> v;  // Vector to store candidate information
    vector<string> CR; // Vector to store CR names with number
};
// Function to determine the round number based on the input file
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

// Class to store information about the final round of interviews
class Round : public Round_info{};


// Maps to store candidate information for different rounds
unordered_map<string, Candidate> mpround[5];

// Class to store company-wise interview data
class Company
{
public:
    string cname; // Company name
    Round Rounds[5];

    // Function to get total number of candidates for a specific round
    int TotalNoOfCandidates(int rno){
            return Rounds[rno-1].v.size();
        }
    // Function to get number of candidates selected from previous round
    int Selected_From_Round(int rno){
            return Rounds[rno].v.size();
    }
    // Function to calculate success rate for each round
    double successRate(int rno){
            return Rounds[rno].v.size() * 100.0 / Rounds[rno-1].v.size();
    }
    double TotalSuccessRate(){
        return Rounds[4].v.size() * 100.0/Rounds[0].v.size();
    }
};
vector<Company> total; // Vector to store company-wise interview data

// Function to read data from input file
void reading(ifstream &file)
{

    int Round_no = Round_data(file); // Determine round number
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
            it.Rounds[Round_no-1].StartDate = startDate;
            file.seekg(0);
            for (int i = 0; i < 3; i++)
            {
                getline(file, s);
            }
            getline(file, s);
            pos = s.find("END DATE");
            string endDate = s.substr(pos + 9, 10);
           it.Rounds[Round_no-1].EndDate = endDate;
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
                it.Rounds[Round_no-1].CR.emplace_back(tempp);
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
                                switch (c.info[no][5])
                                {
                                case '1':
                                    it.Rounds[Round_no-1].BTechICT++;
                                    break;
                                case '2':
                                    it.Rounds[Round_no-1].BTechEVD++;
                                    break;
                                case '3':
                                    it.Rounds[Round_no-1].BTechMNC++;
                                    break;
                                }
                            }
                            else
                            {
                                it.Rounds[Round_no-1].MTechICT++;
                            }
                        }
                    }
                    s.erase(0, ind + 1);
                    no++;
                }
                    mpround[Round_no-1][c.info[5]+"-"+it.cname] = c;
                    it.Rounds[Round_no-1].v.emplace_back(c);
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
    newcompany.Rounds[Round_no-1].StartDate = startDate;
    
    
    file.seekg(0);
    for (int i = 0; i < 3; i++)
    {
        getline(file, s);
    }
    getline(file, s);
    pos = s.find("END DATE");
    string endDate = s.substr(pos + 9, 10);
    newcompany.Rounds[Round_no-1].EndDate = endDate;
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
        newcompany.Rounds[Round_no-1].CR.emplace_back(tempp);
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
                            switch (c.info[no][5])
                            {
                            case '1':
                                newcompany.Rounds[Round_no-1].BTechICT++;
                                break;
                            case '2':
                                newcompany.Rounds[Round_no-1].BTechEVD++;
                                break;
                            case '3':
                                newcompany.Rounds[Round_no-1].BTechMNC++;
                                break;
                            }
                    }
                    else
                    {
                        newcompany.Rounds[Round_no-1].MTechICT++;
                    }
                }
            }
            s.erase(0, ind + 1);
            no++;
        }
        mpround[Round_no-1][c.info[5]+"-"+newcompany.cname] = c;
        newcompany.Rounds[Round_no-1].v.emplace_back(c);
    }
}

// Class that have all additional functions to solve problems.
class Functionality{
    public:

    // Function to get all information of candidate if ID and company name is provided.
    static void GetData(string s){
                        cout << "Details: " << endl;
                        cout << "Student name: " <<mpround[0][s].info[0] << endl;
                        cout << "Student ID: " <<mpround[0][s].info[5] << endl;
                        cout << "Email: " <<mpround[0][s].info[6] << endl;
                        cout << "Program: " << mpround[0][s].info[7]<< endl;
                        cout << "Contact No.: " << mpround[0][s].info[8]<< endl;
                        cout << "WhatsApp No.: " << mpround[0][s].info[9]<< endl;
                        cout << "Alternate No.: " << mpround[0][s].info[10] << endl;
                        cout << "Skype ID: " << mpround[0][s].info[11] << endl;
    }

    // Function to get all information about candidates round wise (candidate ID company name and round number should be provided)
    static void GetData_cname_Round(string s, int rno){
        cout << "Details: " << endl;
        cout << "Student name: " <<mpround[rno-1][s].info[0] << endl;
        cout << "Student ID: " <<mpround[rno-1][s].info[5] << endl;
        cout << "Email: " <<mpround[rno-1][s].info[6] << endl;
        cout << "Program: " << mpround[rno-1][s].info[7]<< endl;
        cout << "Contact No.: " << mpround[rno-1][s].info[8]<< endl;
        cout << "WhatsApp No.: " << mpround[rno-1][s].info[9]<< endl;
        cout << "Alternate No.: " << mpround[rno-1][s].info[10] << endl;
        cout << "Skype ID: " << mpround[rno-1][s].info[11] << endl;
        cout << "Date of the interview is " << mpround[rno-1][s].info[1] << endl;
        cout << "Start time of the interview is " << mpround[rno-1][s].info[3] << endl;
        cout << "end time of the interview is " << mpround[rno-1][s].info[4] << endl;
    }


    //Function to know status of the candidates interview.
    static void StatusOf(string s, int rno){
            if(rno==4){
                cout << "Status of the candidate's interview in " << s << " HR round is "<< mpround[3][s].info[2] << endl;
            }
            else{
                cout << "Status of the candidate's interview in " << s << " round "<< rno << " is "<< mpround[rno-1][s].info[2] << endl;
            }
    }
    
    // Function to know how many rounds cleared by a specific candidate.
    static void Selection_data_of_candidate(string s){
    if(mpround[0][s].info[0]==""){
        cout << "The name of the person with provided ID number is not found in the list of the candidates\n";
        return;
    }
    if(mpround[4][s].info[0]!=""){
        cout << "This candidates selected for the placement.\n";
        return;
    }
    if(mpround[3][s].info[0]!=""){
        cout << "This candidate is eliminated in HR round.\n";
        return;
    }
    if(mpround[2][s].info[0]!=""){
        cout << "This candidate is eliminated in 3rd round.\n";
        return;
    }
    if(mpround[1][s].info[0]!=""){
        cout << "This candidate is eliminated in 2nd round.\n";
        return;
    }
    if(mpround[0][s].info[0]!=""){
        cout << "This candidate is eliminated in 1st round.\n";
        return;
    }
    }

    // Function to get the chances of placement in company, it gives sorted order of companies on basis of % chances.
    static void PlacementChances(){
    vector<pair<double, string>> v;
    for(auto it: total){
        v.emplace_back(it.TotalSuccessRate(), it.cname);
    }
    sort(v.rbegin(), v.rend());
    for(auto it: v){
        cout << it.first ;
        cout << it.second << endl;
    }
    }

    // Function to get average time of interview of particular company's round
    static double avgtime(string s, int rno){
        string temp;
        long long minutes=0;
        for(auto it: total){
            if(it.cname==s){
                for(auto pt: it.Rounds[rno-1].v){
                    temp = pt.info[4].substr(0, pt.info[4].find(":"));
                    minutes += (stoi(temp)*60);
                    temp = pt.info[4].substr(pt.info[4].find(":")+1, pt.info[4].find(","));
                    minutes += stoi(temp);

                    temp = pt.info[3].substr(0, pt.info[3].find(":"));
                    minutes -= (stoi(temp)*60);
                    temp = pt.info[3].substr(pt.info[3].find(":")+1, pt.info[3].find(","));
                    minutes -= stoi(temp);
                }
                return float(minutes)/it.TotalNoOfCandidates(rno);
            }
        }
    }

    // Function to calculate maximum time of interview of particular company's round.
    static int maxtime(string s, int rno){
        int minutes = 0;
        string temp;
        for(auto it: total){
            if(it.cname==s){
                for(auto pt: it.Rounds[rno-1].v){
                    int tempint = 0;
                    temp = pt.info[4].substr(0, pt.info[4].find(":"));
                    tempint += (stoi(temp)*60);
                    temp = pt.info[4].substr(pt.info[4].find(":")+1, pt.info[4].find(","));
                    tempint += stoi(temp);

                    temp = pt.info[3].substr(0, pt.info[3].find(":"));
                    tempint -= (stoi(temp)*60);
                    temp = pt.info[3].substr(pt.info[3].find(":")+1, pt.info[3].find(","));
                    tempint -= stoi(temp);
                    if(minutes<tempint){
                        minutes = tempint;
                    }
                }
            }
        }
        return minutes;
    }

    // Function to calculate minimum time of interview of particular company's round.
    static int mintime(string s, int rno){
        int minutes = INT_MAX;
        string temp;
        for(auto it: total){
            if(it.cname==s){
                for(auto pt: it.Rounds[rno-1].v){
                    int tempint = 0;
                    temp = pt.info[4].substr(0, pt.info[4].find(":"));
                    tempint += (stoi(temp)*60);
                    temp = pt.info[4].substr(pt.info[4].find(":")+1, pt.info[4].find(","));
                    tempint += stoi(temp);

                    temp = pt.info[3].substr(0, pt.info[3].find(":"));
                    tempint -= (stoi(temp)*60);
                    temp = pt.info[3].substr(pt.info[3].find(":")+1, pt.info[3].find(","));
                    tempint -= stoi(temp);
                    if(minutes>tempint){
                        minutes = tempint;
                    }
                }
            }
        }
        return minutes;
    }
};
int main()
{
    #ifndef Om
        auto starttime = chrono::high_resolution_clock::now();
    #endif
    for(int i=1;i>-1;i++){
        int count = 1;
        for(int j=1;j<=5;j++){
            string filename = "company" + to_string(i) + "round" + to_string(j) + ".csv";
            string path = "D:/C++/Capstone/Programs/filetoberead/" + filename;
            ifstream file12(path);
            if(file12.is_open()){
                reading(file12);
            }
            else {
                count = 0;
                break;
            }
        }
        if(count==0){break;}
    }

    ifstream google("D:/C++/Capstone/Programs/filetoberead/Googler1.csv");
    reading(google);
    ifstream googlefinal("D:/C++/Capstone/Programs/filetoberead/Googlefinal.csv");
    reading(googlefinal);

    Functionality::GetData("202001096-[Microsoft]");
    Functionality::GetData_cname_Round("202001019-[Microsoft]", 3);
    Functionality::Selection_data_of_candidate("202001008-[Microsoft]");
    Functionality::StatusOf("202001019-[Microsoft]", 3);
    Functionality::Selection_data_of_candidate("202001096-[Microsoft]");
    Functionality::PlacementChances();
    cout << Functionality::avgtime("[Microsoft]", 4);
    cout << Functionality::maxtime("[Microsoft]", 1) << " Minutes\n";
    cout << Functionality::mintime("[Microsoft]", 3) << " Minutes\n";
    
    #ifndef Om
        auto endtime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endtime-starttime).count();
        cout << duration << "ms";
    #endif
    return 0;
}
