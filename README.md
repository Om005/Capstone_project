# Capstone_Project

Information:<br>
This README file contains: <br>
-> Problem details<br>
-> Team details<br>
-> What problems we have solved <br>
-> Type of input and output file <br>
-> Addition harder problems that we have designed and solved in good way<br>
-> Contributions<br>
-> Pseudocode and algorithmic point of view of code, time and space complexity details<br>
So please go through this file or documentation file which we have uploaded.<br>

Problem: <br>
P2. DA-IICT Placement Manager:
Develop a comprehensive Placement Manager system to streamline the
placement process for the university. This system will record and manage all
placement-related activities for each batch and program, including written tests,
interviews, shortlisting, and job offers. Also, it can search for students placed in a
specific company, batch, location, etc.<br>

Team Name: Code Crafters<br>
Section: A<br>
Members:<br>
Dhruvil Mehta (202301061)<br>
Chavda Om (202301177)<br>
Jay Rathod (202301006)<br>
Sanyam Shah (202301137)<br>

Here we are listing some of the problems which we have solved for the question and we have added some harder extra questions which can be useful and we have also solved those:<br>
Q. Storing all the data of all companies' all rounds efficiently. <br>
Q. Getting start date and end date of any round of any company. <br>
Q. Getting information of any candidate participated in given company by his/hers ID. <br>
Q. Getting information of CR (Company Representatives) for any given company. <br>
Q. Getting total number of candidates in given round of given company. <br>
Q. Finding success rate of passing the particular rounds. <br>
Q. Finding that given candidate has reached till what round by his ID and company. <br>
Q. Counting the number of people belonging to different branches in given round of given company. <br>
Q. Get round-wise information of candidate when ID and company name is given. <br>
Q. Find candidate's interview status when company name, ID and round no. are given.<br>
Q. Knowing how many rounds did candidate pass from his ID and company name.<br>
Q. Finding chances of placement in company by giving sorted order of company on basis of % chances. <br>
Q. Calculating average time of interview of particular company's round. <br>
Q. Finding the maximum time of interview for given company's round. <br>
Q. Finding the minimum time of interview for given company's round. <br>
Q. Finding list of the companies in which a given student has participated. <br>
Q. Finding % placement rate of the college for a particular given year. <br>
Q. Finding trend of placement of the given company by using previous years data. (This trend will be program-wise and branch-wise also. If a user enters from year & to year, we will give the trend of that particular company for that time period.)<br>
Q. Finding the trajectory for a student to get placed. (Finding the best possible way from previous years data, i.e. if the student follows that path, he must be placed. Students will be suggested some path to follow for placement. For example how many Average (LeetCode questions (Easy, Medium, Hard), How many projects, CPI, Hackathons) should a student do to get placed in particular company, we’ll also suggest in what projects and in which hackathon student should participate, from additional given data of previously placed students.)<br>


Input and Output files:<br>
We will take input from CSV files. There should be different CSV files of all companies, all years, all rounds in the same format. We have removed the constraint of the name of the file by Python. For the Trajectory question, we will take input from a CSV file which contains information about previously placed students. All excel files can be converted into CSV files easily. <br>
We will output and store the data which we have received from our program in the TXT file. <br>

Contributions:<br>
→ Here are contributions of different members for different functions. We have mostly discussed the code together as a team and written it down:<br>
→ Round_info: Dhruvil<br>
→  Reading: All<br>
→  GetData: Jay<br>
→ GetData_cname_Round: Om<br>
→ Status_of: Sanyam<br>
→ Selection_data_of_candidates: Jay<br>
→ Placement chances: Om, Dhruvil<br>
→ Avgtime: All<br>
→ Maxtime: All<br>
→ Mintime: All<br>
→ Findcompany:  Dhruvil<br>
→ Placementrate: Om<br>
→ Trend: Om, Dhruvil, Sanyam<br>
→ Trajectory: Om, Dhruvil, Jay<br>
→ GetICT:  Dhruvil<br>
→ GetEVD:  Om<br>
→ GetMnC:  Jay<br>
→ GetMTech: Sanyam<br>


Pseudocode: <br>
// Include necessary headers<br>
// Define Candidate class<br>
    // Public array to store candidate information<br>
// Define Round_info class<br>
    // Public integer variables for candidate count in each branch<br>
    // Public strings for EndDate and StartDate<br>
    // Public vector of Candidates to store candidate information<br>
    // Public vector of strings to store CR names with number<br>
// Define Round_data function<br>
    // Accepts a reference to an ifstream object<br>
    // Reads the round number from the input file<br>
    // Returns the round number as an integer<br>
// Define Round class as a subclass of Round_info<br>
// Create a global array of unordered_maps to store candidate information for different rounds<br>
// Define Company class<br>
    // Public string variables for year and company name<br>
    // Public array of Rounds<br>
    // Public methods for calculating total number of candidates, selected candidates, success rates, and total success rate<br>
// Define a global vector to store company-wise interview data<br>
// Define reading function<br>
    // Accepts a reference to an ifstream object<br>
    // Reads data from the input file and populates the total vector and the maps for rounds<br>
// Define Functionality class with static methods<br>
    // Methods for retrieving candidate data, status, selection data, placement chances, average/maximum/minimum interview times, company finding, placement rate, trend analysis, trajectory for placement, and getting total number of candidates by program and branch <br>
// Main function starts <br>
    // System call to run a Python script<br>
    // Define starttime for performance measurement (if not in Om mode)<br>
    // Open a file containing filenames and read filenames<br>
    // Loop through each filename<br>
        // Open the file to read<br>
        // Call the reading function with the opened file<br>
    // End loop<br>
    // Call various methods from Functionality class to perform different operations<br>
    // Print total time of the program (if not in Om mode)<br>
// Main function ends<br>

Algorithm: <br>
 1. Define necessary classes and global variables:<br>
   - Candidate: Class to store information about a candidate. <br>
   - Round_info: Class to store information about the number of candidates selected from different branches, and start and end date of the round, CR, and candidate information.<br>
   - Round: Class to store information about the final round of interviews, inherits from Round_info.<br>
   - Company: Class to store company-wise interview data.<br>
   - Functionality: Class to provide additional functions to solve problems.<br>
   - mpround: Global array of unordered maps to store candidate information for different rounds.<br>
   - total: Global vector to store company-wise interview data.<br>
 2. Define the Round_data function to determine the round number based on the input file.<br>
 3. Define the reading function to read data from the input file:<br>
   - Determine the round number using Round_data.<br>
   - Read and ignore the first few lines to reach the relevant data.<br>
   - Extract the company name and start year from the file.<br>
   - If the company already exists in 'total' and the year matches, update its Round_info.<br>
   - Otherwise, create a new Company instance and add it to 'total'.<br>
   - For each candidate entry in the file, parse the data and:<br>
 	- Update the candidate's information in the appropriate mpround map.<br>
 	- Update the candidate count for their program (BTechICT, BTechMNC, etc.) in Round_info.<br>
 	- Add the candidate to the vector of candidates in Round_info.<br>
 4. Define static functions within the Functionality class to perform various operations:<br>
   - GetData: Retrieve and display general information of a candidate based on ID.<br>
   - GetData_cname_Round: Retrieve and display information of a candidate for a specific round.<br>
   - StatusOf: Retrieve and display the interview status of a candidate for a specific round.<br>
   - Selection_data_of_candidate: Determine how many rounds a candidate has cleared and display the result.<br>
   - PlacementChances: Calculate and display the placement chances for each company for a specific year.<br>
   - avgtime: Calculate and return the average interview time for a specific company and round.<br>
   - maxtime: Calculate and return the maximum interview time for a specific company and round.<br>
   - mintime: Calculate and return the minimum interview time for a specific company and round.<br>
   - findCompany: Display the names of all companies where the candidate has participated.<br>
   - PlacementRate: Calculate and return the placement rate for the college for a specific year.<br>
   - trend_of: Display the trend of placements for a company over a range of years.<br>
   - Trajectory: Suggest a trajectory for a student to get placed based on historical data.<br>
 5. Start the main function:<br>
   - Execute an external Python script using a system call.<br>
   - Open the file 'fnames.txt' containing the list of filenames to be processed.<br>
   - For each filename in the list:<br>
 	- Open the file and call the reading function to process the data.<br>
   - Demonstrate the use of Functionality class methods by calling them with sample data.<br>
   - If in debugging mode, measure and display the execution time.<br>
 6. End the main function.<br>
 
Postconditions:<br>
- The recruitment data is processed, and various statistics and information are displayed.<br>
- If in debugging mode, the total execution time of the program is printed.<br>

Time & Space complexity view:<br>
→ Time Complexity:<br>
1. Reading Data (reading function):<br>
  -In this function we are processing each line of the input files. So if there are n lines in the file, the time complexity is O(n), because we are processing all lines once.<br>
2. Updating Data in total vector and mpround maps variable and searching a company of particular year:<br>
  -  Searching for a company in the “total” vector takes O(n) time, where n is the total number of members in company in the vector, and it’s O(n) because we may require to traverse the entire vector in the worst case scenario.<br>
  - Inserting candidates into the “mpround” maps take O(1) average time for each candidate because of the nature of the unordered_map, it’s true that the worst case time complexity of the unorderd_map is O(n) but is very rare.<br>
3. Functions of the class Functionality:<br>
  - Most of the functions of the class functionality are O(n) where n is the no of the companies (according to the year) or the no of the candidates. For example avgtime, maxtime and mintime iterate over all candidates in a round, so it’s O(n). In PlacementChances sorting is there so it will be around O(nlogn)<br>

The overall time complexity is hard to point out, but it’s mostly linear with respect to the number of the lines or candidates or the number of the companies (according to year) and somewhere around O(nlogn) due to sorting operations.<br>

→ Space complexity:<br>
1.	Total vector stores all companies (according to the year) so it’s O(n) , where n is the total number of the companies(according to the year).<br>
2.	Mpround stores the data of each candidate from all rounds so we can say that it’s O(n), where n is the total number of the candidates (total means candidates of all rounds of all companies.)<br>

Data Structures used & why that data structure: <br>
Maps:<br>
→ Here we have used Unordered Maps, by which we are storing the data for searching purposes only. Here Unordered maps help us to reduce time complexity. It will store all the things for searching in O(1) {Constant} time. In the worst case it can be O(n) but that is rare to happen.<br>
→ Here we could have also used maps but that would work in O(n) time, so we are using Unordered maps instead of maps.<br>
Vectors:<br>
→ Here we have used vectors for storing all the data of different companies for each year. Vectors are dynamic, so we can vary its size accordingly. If we do not know how many inputs are coming then a vector is the most suitable data structure for storing them, i.e. in our problem we do not know how many companies are coming this year, so we are using vectors to store their information.<br>
→ Vectors can also sort their elements in O(nlogn) time so it is also useful in that way also. In traversal it will take O(n) time.<br>
Arrays:<br>
→ We have used arrays for storing purposes. We have created arrays of strings and array of maps in our code. Arrays of strings were useful in storing all long information and fetching them in O(1) time and for traversal it would take O(n) time.<br>
→ In our problem, instead of creating 5 different objects of maps we have used an array of maps, so we can avoid a lot of switch cases. This reduced many lines from our code and increased readability of our program. <br>

Screenshots of output file, video of output, Documentation file, output file, input files are also uploaded in this repository. <br>

→ Here tasks.json is for writing whole output in output.txt instead of console (Note that, here when we use this method we have to set command prompt as default terminal).<br>
