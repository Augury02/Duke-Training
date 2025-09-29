#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stack>
#include <memory>

using namespace std;

// Forward declaration of Logger
class Logger;

// GameCommand interface
class GameCommand {
/*
interface that defines two methods
execute() which is responsible for executing the command
undo() which is for undoing reversible logged actions
*/
public:
    virtual ~GameCommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class CommandInvoker;

/*
Concrete commands
    ForwardCommand which represents the action of moving in the game (1)
    SearchCommand represents the search action (for getting key; 2)
    QuitCommand; quit (3)
    undo; undo last logged action (4)
*/

    // 
class ForwardCommand : public GameCommand {
private:
    bool& hasKey;
    CommandInvoker& invoker;

public:
    ForwardCommand(bool& hasKey, CommandInvoker& invoker) : hasKey(hasKey), invoker(invoker) {}

    void execute() override {
        if (hasKey) {
            cout << "You unlocked the door and moved forward." << endl;
            invoker.startCombat();
        } else {
            cout << "You need a key to proceed!" << endl;
        }
    }

    void undo() override {
        // No undo action needed for moving forward
    }
};

// SearchCommand
class SearchCommand : public GameCommand {
private:
    bool& hasKey;

public:
    SearchCommand(bool& hasKey) : hasKey(hasKey) {}

    void execute() override {
        cout << "You found a key!" << endl;
        hasKey = true;
    }

    void undo() override {
        hasKey = false;
        cout << "You lost the key!" << endl;
    }
};

class QuitCommand : public GameCommand {
public:
    void execute() override {
        cout << "Thanks for playing daGame!" << endl;
        exit(0);
    }

    void undo() override {
        // No undo action needed for quitting
    }
};

//Logging feature; also used for the undo action
class Logger {
public:
    static void log(const string& message) {
        cout << "[LOG] " << message << endl;
    }
};

// CommandInvoker class
class CommandInvoker {
private:
    stack<unique_ptr<GameCommand>> history;

public:
    void executeCommand(unique_ptr<GameCommand> command) {
        command->execute();
        Logger::log("Executed command.");
        history.push(move(command));
    }

    void undoLastCommand() {
        if (!history.empty()) {
            auto lastCommand = move(history.top());
            lastCommand->undo();
            Logger::log("Undid last command.");
            history.pop();
        } else {
            Logger::log("Nothing to undo.");
        }
    }

    void startCombat() {
        Logger::log("Starting combat phase...");
        battle(); 
    }
};

//THIS IS WHERE COMBAT ENCOUNTER WOULD USUALLY BEGIN; REMOVED TO SAVE TIME AND FOCUS ON TOPIC
bool battle() {
    cout << "You encounter an enemy!" << endl;

}

// Main function
int main() {
    srand(time(0));

    cout << "Welcome to discount Elden Ring!" << endl;

    int choice;
    bool hasKey = false;
    CommandInvoker invoker;

    while (true) {
        cout << "You are in a room. What would you like to do?" << endl;
        cout << "1. Go forward" << endl;
        cout << "2. Search for treasure" << endl;
        cout << "3. Quit" << endl;
        cout << "4. Undo last action" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                unique_ptr<GameCommand> forwardCommand = make_unique<ForwardCommand>(hasKey, invoker);
                invoker.executeCommand(move(forwardCommand));
                break;
            }
            case 2: {
                unique_ptr<GameCommand> searchCommand = make_unique<SearchCommand>(hasKey);
                invoker.executeCommand(move(searchCommand));
                break;
            }
            case 3: {
                unique_ptr<GameCommand> quitCommand = make_unique<QuitCommand>();
                invoker.executeCommand(move(quitCommand));
                break;
            }
            case 4:
                invoker.undoLastCommand();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                cout << endl;
                break;
        }

        cout << endl;
    }

    return 0;
}
