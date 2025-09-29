#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <memory>

using namespace std; 
class TimeLog {             

public:
    static TimeLog& getInstance() {         //"Create a static method that returns a reference to a static member"
        static TimeLog instance;
        return instance;
    }

    void addLog(const string& activity) {
        string currentTime = getCurrentTime();
        string logEntry = currentTime + " - " + activity;
        logs.push_back(logEntry);
        cout << "Log added: " << logEntry << endl;
    }

    void saveLogs() {           //Discussed in Advanced C++ Text file
        string filename = generateFilename();
        ofstream outFile(filename, ios::app);
        if (outFile.is_open()) {
            for (const auto& log : logs) {
                outFile << log << endl;
            }
            outFile.close();
            cout << "Logs saved to " << filename << endl;       
        } else {
            cerr << "Unable to open file: " << filename << endl;        //Flags if saving is unsuccessful
        }
        logs.clear();
    }

private:
    /*With the constructor private and deleting the copy constructor and assignment operator, 
    the code ensures that no other part of the program can create additional instances of TimeLog
    Refers to the following segment of the note: "Want to prevent anyone creating additional copies"
    */

    vector<string> logs;
    string current_date;

    TimeLog() {                                         //private
        current_date = getCurrentDate();
    }

    ~TimeLog() = default;           
    TimeLog(const TimeLog&) = delete;                   //delete
    TimeLog& operator=(const TimeLog&) = delete;        //delete

    string getCurrentDate() {                           //Had to research derivation of current date and current time
        time_t now = time(0);                           //and how to make it appear in the code
        tm* localtm = localtime(&now);
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d", localtm);      //Observe implementation of Year/Month/Day
        return string(buffer);
    }

    string getCurrentTime() {
        time_t now = time(0);
        tm* localtm = localtime(&now);
        char buffer[80];
        strftime(buffer, 80, "%H:%M:%S", localtm);      //and Hour/Minutes/Seconds
        return string(buffer);
    }

    string generateFilename() {
        return "TimeLog_" + current_date + ".txt";      //EDIT FILE NAME HERE
    }
};

int main() {
    TimeLog& log = TimeLog::getInstance();
    /*"A Singleton is a component instantiated only once"
    TimeLog is created only when getInstance is called for the first time*/ 

    /*getInstance method is called to get a reference to the single TimeLog instance */

    string activity;
    while (true) {                              //continues unless break condition is met
        cout << "Enter activity (or 'exit' to quit and save logs): ";
        getline(cin, activity);                 //activity is the user input that will the log content
        if (activity == "exit") {
            break;
        }
        log.addLog(activity);                   //called on the Singleton instance to add a log entry
    }

    log.saveLogs();                             //saving mechanism

    return 0;
}
