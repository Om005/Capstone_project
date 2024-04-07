#include<iostream>
#include<fstream>
#include<chrono>
#include<vector>
#include<string>
#include<climits>
#include<algorithm>
#include<unordered_map>
#include <cstdlib>
#include <cstdlib>
#include <ctime> 
using namespace std;


// Class to store information about a candidate
class Candidate
{
public:
    //*************************
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
    string year;
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
    //
    file.seekg(0);
            for (int i = 0; i < 2; i++)
            {
                getline(file, s);
            }
            getline(file, s);
            int lose = s.find("START DATE");
            string startYear = s.substr(lose + 17, 4);
    //
    
    for (auto &it : total)
    {
        if (it.cname == tempp)
        {

            string yr = it.year;
            if(startYear!=yr){
                continue;
            }
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
                    mpround[Round_no-1][c.info[5]+"-"+it.cname+"-"+startYear] = c;
                    it.Rounds[Round_no-1].v.emplace_back(c);
            }
            
        }
    }
    Company newcompany;
    newcompany.cname = tempp;
    newcompany.year = startYear;
    
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
        mpround[Round_no-1][c.info[5]+"-"+newcompany.cname+"-"+startYear] = c;
        newcompany.Rounds[Round_no-1].v.emplace_back(c);
    }
}

// Class that have all additional functions to solve problems.
class Functionality{
    public:

    // Function to get all information of candidate if ID and company name is provided.
    static void GetData(string s){
                        if(mpround[0][s].info[0]==""){
                            cerr << "Something is wrong! Maybe file not found or you have provided wrong details!\n";
                            return;
                        }
                        cout << "Details: " << endl;
                        cout << "Student name: " <<mpround[0][s].info[0] << endl;
                        cout << "Student ID: " <<mpround[0][s].info[5] << endl;
                        cout << "Email: " <<mpround[0][s].info[6] << endl;
                        cout << "Program: " << mpround[0][s].info[7]<< endl;
                        cout << "Contact No.: " << mpround[0][s].info[8]<< endl;
                        cout << "WhatsApp No.: " << mpround[0][s].info[9]<< endl;
                        cout << "Alternate No.: " << mpround[0][s].info[10] << endl;
                        cout << "Skype ID: " << mpround[0][s].info[11] << endl;
                        cout << "-------------------------------\n";
    }

    // Function to get all information about candidates round wise (candidate ID company name and round number should be provided)
    static void GetData_cname_Round(string s, int rno){
        if(mpround[rno-1][s].info[0]==""){
            cerr << "Something is wrong! Maybe file not found or you have provided wrong details!\n";
            return;
        }
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
        cout << "-------------------------------\n";
    }


    //Function to know status of the candidates interview.
    static void StatusOf(string s, int rno){
            if(mpround[rno-1][s].info[0]==""){
                cerr << "Something is wrong! Maybe file not found or you have provided wrong details!\n";
                return;
            }
            if(rno==4){
                cout << "Status of the candidate's interview in " << s.substr(10, s.length()-1) << " HR round is "<< mpround[3][s].info[2] << endl;
            }
            else{
                cout << "Status of the candidate's interview in " << s.substr(10, s.length()-1) << " round "<< rno << " is "<< mpround[rno-1][s].info[2] << endl;
            }
            cout << "-------------------------------\n";
    }
    
    // Function to know how many rounds cleared by a specific candidate.
    static void Selection_data_of_candidate(string s){
    if(mpround[0][s].info[0]==""){
        cout << "The name of the person with provided ID number is not found in the list of the candidates!!\n";
    }
    else if(mpround[4][s].info[0]!=""){
        cout << "This candidates selected for the placement.\n";
    }
    else if(mpround[3][s].info[0]!=""){
        cout << "This candidate is eliminated in HR round.\n";
    }
    else if(mpround[2][s].info[0]!=""){
        cout << "This candidate is eliminated in 3rd round.\n";
    }
    else if(mpround[1][s].info[0]!=""){
        cout << "This candidate is eliminated in 2nd round.\n";
    }
    else if(mpround[0][s].info[0]!=""){
        cout << "This candidate is eliminated in 1st round.\n";
    }
    cout << "-------------------------------\n";
    }

    // Function to get the chances of placement in company, it gives sorted order of companies on basis of % chances.
    static void PlacementChances(int yr){
        vector<pair<double, string>> v;
        for(auto it: total){
            string y = it.year;
            if(y==to_string(yr)){ 
                v.emplace_back(it.TotalSuccessRate(), it.cname);
            }
        }
        sort(v.rbegin(), v.rend());
        for(auto it: v){
            cout << it.first << "% " ;
            cout << it.second << endl;
        }
        cout << "-------------------------------\n";
    }

    // Function to get average time of interview of particular company's round
    static void avgtime(string s, int rno, int yr){
        string temp;
        long long minutes=0;
        for(auto it: total){
            string y = it.year;
            if(it.cname==s && y==to_string(yr)){
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
                cout << "Average time of interview for " << " company " << s  << ", Round " <<  rno << " and year " << yr << " is " << float(minutes)/it.TotalNoOfCandidates(rno)  << " minutes."<< endl; 
                cout << "-------------------------------\n";
            }
        }
    }

    // Function to calculate maximum time of interview of particular company's round.
    static void maxtime(string s, int rno, int yr){
        int minutes = 0;
        string temp;
        for(auto it: total){
            string y = it.year;
            if(it.cname==s && y==to_string(yr)){
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
        cout << "Maximum time of interview for " << " company " << s  << ", Round " <<  rno << " and year " << yr << " is " << minutes  << " minutes."<< endl; 
        cout << "-------------------------------\n";
    }

    // Function to calculate minimum time of interview of particular company's round.
    static void mintime(string s, int rno, int yr){
        int minutes = INT_MAX;
        string temp;
        for(auto it: total){
            string y = it.year;
            if(it.cname==s && y==to_string(yr)){
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
        cout << "Minimum time of interview for " << " company " << s  << ", Round " <<  rno << " and year " << yr << " is " << minutes  << " minutes."<< endl; 
        cout << "-------------------------------\n";
    }

    // Function that takes student ID and finds the names of all companies in which that student has participated.
    static void findCompany(string s, int yr){
        string temp;
        for(auto it: total){
            if(it.year==to_string(yr)){
                temp = s + "-" + it.cname + "-" + to_string(yr);
                if(mpround[0][temp].info[0] != ""){
                    cout << it.cname << endl;
                }
            }
        }
        cout << "-------------------------------\n";
    }

    // Function that gives % of placement rate of the college for a particular year.
    static void PlacementRate(int year){
        int entered{0};
        int selected{0};
        int count = 0;
        for(auto it: total){
            if(it.year==to_string(year)){
                entered += it.Rounds[0].v.size();
                selected += it.Rounds[4].v.size();
                count = 1;
            }
        }
        if(count==1){
            cout << "Placement rate of " << year << " is " << selected*100.0/entered << "%.\n";
            cout << "-------------------------------\n";
        }
        else{
            cout << "This year's data is not available.\n";
        }
    }
    /*Finding trend of placement of the given company by using previous years data. (This trend will be program-wise and branch-wise also. If a user enters from year & to year, we will give the trend of that particular company for that time period.)*/
    static void trend_of(string cn, int y1, int y2){
        
        double temp;
        double Bt_succ1,Mt_succ1,Bt_succ2,Mt_succ2;
        vector<pair<double, string>> b(3);
        int x,y=0;
        double b1,b2,b3,b4,b5,b6;
        for(auto it: total){
            for(int i=y1;i<=y2;i++){
                if(it.cname==cn && it.year==to_string(i)){
                    if(i==y1){
                        cout << "Total analysis: " << endl;
                        cout << "Year: " << i << endl;
                        cout << "Company: " << cn << endl;
                        cout << "Total no. of candidates participated: " << it.TotalNoOfCandidates(1) << endl;
                        cout << "Total no. of selected candidates: " << it.TotalNoOfCandidates(5) << endl;
                        temp=it.TotalSuccessRate();
                        cout << "Total success rate: " << temp << "%" << endl << endl;
                        //***************
                        cout << "Program-wise analysis: " << endl;
                        x=it.Rounds[0].BTechEVD + it.Rounds[0].BTechICT + it.Rounds[0].BTechMNC;
                        cout << "No. of BTech candidates: " << x << endl;
                        y=it.Rounds[4].BTechEVD + it.Rounds[4].BTechICT + it.Rounds[4].BTechMNC;
                        cout << "No. of selected BTech candidates: " << y << endl;
                        Bt_succ1 = y*100.0/x;
                        cout << "BTech success rate: " << Bt_succ1 << "%" << endl;
                        x=it.Rounds[0].MTechICT;
                        cout << "No. of MTech candidates: " << x << endl;
                        y=it.Rounds[4].MTechICT;
                        cout << "No. of selected MTech candidates: " << y << endl;
                        Mt_succ1=y*100.0/x;
                        cout << "MTech success rate: " << Mt_succ1 << "%" << endl;
                        cout << "In BTech vs MTech, this year" << ((Bt_succ1>Mt_succ1)?" BTech " : " MTech ") << "was more successful." << endl << endl;  
                        //**************
                        cout << "Branch-wise analysis: " << endl;
                        cout << "BTech ICT: " << endl;
                        cout << "No. of BTech ICT candidates: " << it.Rounds[0].BTechICT << endl;
                        cout << "No. of BTech ICT candidates selected: " << it.Rounds[4].BTechICT << endl;
                        
                        b1=(it.Rounds[4].BTechICT*100.0)/(it.Rounds[0].BTechICT);
                        cout << "BTech ICT success rate: " << b1 << "%" << endl;

                        cout << "BTech MnC: " << endl;
                        cout << "No. of BTech MnC candidates: " << it.Rounds[0].BTechMNC << endl;
                        cout << "No. of BTech MnC candidates selected: " << it.Rounds[4].BTechMNC << endl;
                        b2=(it.Rounds[4].BTechMNC*100.0)/(it.Rounds[0].BTechMNC);
                        cout << "BTech MnC success rate: " << b2 << "%" << endl;

                        cout << "BTech EVD: " << endl;
                        cout << "No. of BTech EVD candidates: " << it.Rounds[0].BTechEVD << endl;
                        cout << "No. of BTech EVD candidates selected: " << it.Rounds[4].BTechEVD << endl;
                        b3=(it.Rounds[4].BTechEVD*100.0)/(it.Rounds[0].BTechEVD);
                        cout << "BTech EVD success rate: " << b3 << "%" << endl;
                        b[0] = {b1, "BTech ICT"};
                        b[1] = {b2, "BTech MnC"};
                        b[2] = {b3, "BTech EVD"};
                        sort(b.rbegin(), b.rend());
                        cout << "BTech ICT vs MnC vs EVD, this year: " << endl;
                        cout << "1. " << b[0].second << endl << "2. " << b[1].second << endl << "3. " << b[2].second << endl << endl;
                    }
                    else {
                        cout << "Total analysis: " << endl;
                        cout << "Year: " << i << endl;
                        cout << "Company: " << cn << endl;
                        cout << "Total no. of candidates participated: " << it.TotalNoOfCandidates(1) << endl;
                        cout << "Total no. of selected candidates: " << it.TotalNoOfCandidates(5) << endl;
                        cout << "Total success rate: " << it.TotalSuccessRate() << "%" << endl;
                        cout << "Increament in total success rate: " << it.TotalSuccessRate()-temp << "%" << endl << endl;
                        //***************
                        cout << "Program-wise analysis: " << endl;
                        x=it.Rounds[0].BTechEVD + it.Rounds[0].BTechICT + it.Rounds[0].BTechMNC;
                        cout << "No. of BTech candidates: " << x << endl;
                        y=it.Rounds[4].BTechEVD + it.Rounds[4].BTechICT + it.Rounds[4].BTechMNC;
                        cout << "No. of selected BTech candidates: " << y << endl;
                        Bt_succ2 = y*100.0/x;
                        cout << "BTech success rate: " << Bt_succ2 << "%" << endl;
                        cout << "Increament in BTech success rate: " << Bt_succ2-Bt_succ1 << endl;
                        x=it.Rounds[0].MTechICT;
                        cout << "No. of MTech candidates: " << x << endl;
                        y=it.Rounds[4].MTechICT;
                        cout << "No. of selected MTech candidates: " << y << endl;
                        Mt_succ2 = y*100.0/x;
                        cout << "MTech success rate: " << Mt_succ2 << "%" << endl;
                        cout << "Increament in MTech success rate: " << Mt_succ2-Mt_succ1 << "%" << endl;
                        cout << "In BTech vs MTech, this year" << ((Bt_succ2>Mt_succ2)?" BTech " : " MTech ") << "was more successful." << endl << endl;  
                        //**************
                        cout << "Branch-wise analysis: " << endl;
                        cout << "BTech ICT: " << endl;
                        cout << "No. of BTech ICT candidates: " << it.Rounds[0].BTechICT << endl;
                        cout << "No. of BTech ICT candidates selected: " << it.Rounds[4].BTechICT << endl;
                        
                        b4=(it.Rounds[4].BTechICT*100.0)/(it.Rounds[0].BTechICT);
                        cout << "BTech ICT success rate: " << b4 << "%" << endl;
                        cout << "Increament in BTech ICT success rate: " << b4-b1 << "%" << endl;
                        cout << "BTech MnC: " << endl;
                        cout << "No. of BTech MnC candidates: " << it.Rounds[0].BTechMNC << endl;
                        cout << "No. of BTech MnC candidates selected: " << it.Rounds[4].BTechMNC << endl;
                        b5=(it.Rounds[4].BTechMNC*100.0)/(it.Rounds[0].BTechMNC);
                        cout << "BTech MnC success rate: " << b5 << "%" << endl;
                        cout << "Increament in BTech MnC success rate: " << b5-b2 << "%" << endl;
                        cout << "BTech EVD: " << endl;
                        cout << "No. of BTech EVD candidates: " << it.Rounds[0].BTechEVD << endl;
                        cout << "No. of BTech EVD candidates selected: " << it.Rounds[4].BTechEVD << endl;
                        b6=(it.Rounds[4].BTechEVD*100.0)/(it.Rounds[0].BTechEVD);
                        cout << "BTech EVD success rate: " << b6 << "%" << endl;
                        cout << "Increament in BTech EVD success rate: " << b6-b3 << "%" << endl;
                        b[0] = {b4, "BTech ICT"};
                        b[1] = {b5, "BTech MnC"};
                        b[2] = {b6, "BTech EVD"};
                        sort(b.rbegin(), b.rend());
                        cout << "BTech ICT vs MnC vs EVD, this year: " << endl;
                        cout << "1. " << b[0].second << endl << "2. " << b[1].second << endl << "3. " << b[2].second << endl << endl;
                    }
                    
                }
            }
        }
        cout << "-------------------------------\n";
    }

     // Getting total no. of BTech ICT candidates from given year, company and round mo.
    static void GetICT(string s, int yr, int rno){
        for(auto it: total){
            if(it.cname==s && it.year==to_string(yr)){
                cout << "Total number of BTech ICT candidates in " << s << " company Round " << rno << " year " << yr << " is " << it.Rounds[rno-1].BTechICT << endl;
                cout << "-------------------------------\n";
            }
        }
    }
    // Getting total no. of BTech EVD candidates from given year, company and round mo.
    static void GetEVD(string s, int yr, int rno){
        for(auto it: total){
            if(it.cname==s && it.year==to_string(yr)){
                cout << "Total number of BTech EVD candidates in " << s << " company Round " << rno << " year " << yr << " is " << it.Rounds[rno-1].BTechEVD << endl;
                cout << "-------------------------------\n";
            }
        }
    }
};
int main()
{   
    system("python new.py");
    #ifndef Om
        auto starttime = chrono::high_resolution_clock::now();
    #endif
    ifstream inputfile("fnames.txt");
    string ffname;
    while(getline(inputfile, ffname)){
        ifstream file("D:/C++/Capstone/Programs/filetoberead/selfmadefiles/"+ffname);
        reading(file);
    }

    Functionality::findCompany("202001001", 2024);
    Functionality::GetData("202001096-[Microsoft]-2024");
    Functionality::GetData_cname_Round("202003017-[Microsoft]-2024", 5);
    Functionality::Selection_data_of_candidate("202001008-[Microsoft]-2024");
    Functionality::StatusOf("202001019-[Microsoft]-2024", 3);
    Functionality::Selection_data_of_candidate("202001096-[Microsoft]-2024");
    Functionality::PlacementChances(2024);
    Functionality::GetICT("[Microsoft]", 2024, 3);
    Functionality::GetEVD("[Microsoft]", 2024, 3);
    Functionality::avgtime("[Microsoft]", 2, 2024);
    Functionality::maxtime("[Microsoft]", 2, 2024);
    Functionality::mintime("[Microsoft]", 2, 2024);
    Functionality::trend_of("[Microsoft]",2024,2024);
    Functionality::trend_of("[Google]",2024,2024);
    Functionality::PlacementRate(2024);

    cout << "Total time of the program is: ";
    #ifndef Om
        auto endtime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endtime-starttime).count();
        cout << duration << "ms";
    #endif
    return 0;
}
