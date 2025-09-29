#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stack>
#include <memory>
#include <vector>

using namespace std;

// Forward declaration of Logger
class Logger;

// GameCommand interface
class GameCommand {
public:
    virtual ~GameCommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Memento class
class Memento {
private:
    bool hasKey;

public:
    Memento(bool keyState) : hasKey(keyState) {}

    bool getState() const {
        return hasKey;
    }
};

// Originator class
class GameState {
private:
    bool hasKey;

public:
    GameState() : hasKey(false) {}

    void setKey(bool keyState) {
        hasKey = keyState;
    }

    bool getKey() const {
        return hasKey;
    }

    Memento save() const {
        return Memento(hasKey);
    }

    void restore(const Memento& memento) {
        hasKey = memento.getState();
    }
};

class CommandInvoker;

// Concrete commands
class ForwardCommand : public GameCommand {
private:
    GameState& gameState;
    CommandInvoker& invoker;

public:
    ForwardCommand(GameState& gameState, CommandInvoker& invoker) : gameState(gameState), invoker(invoker) {}

    void execute() override {
        if (gameState.getKey()) {
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

class SearchCommand : public GameCommand {
private:
    GameState& gameState;

public:
    SearchCommand(GameState& gameState) : gameState(gameState) {}

    void execute() override {
        cout << "You found a key!" << endl;
        gameState.setKey(true);
    }

    void undo() override {
        gameState.setKey(false);
        cout << "You lost the key!" << endl;
    }
};

class QuitCommand : public GameCommand {
public:
    void execute() override {
        cout << "Thanks for playing the game!" << endl;
        exit(0);
    }

    void undo() override {
        // No undo action needed for quitting
    }
};

// Logging feature; also used for the undo action
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
    stack<unique_ptr<GameCommand>> redoStack;
    stack<Memento> undoHistory;
    stack<Memento> redoHistory;
    GameState& gameState;

public:
    CommandInvoker(GameState& gameState) : gameState(gameState) {}

    void executeCommand(unique_ptr<GameCommand> command) {
        undoHistory.push(gameState.save());
        command->execute();
        Logger::log("Executed command.");
        history.push(move(command));

        // Clear the redo stack whenever a new command is executed
        while (!redoStack.empty()) redoStack.pop();
        while (!redoHistory.empty()) redoHistory.pop();
    }

    void undoLastCommand() {
        if (!history.empty()) {
            auto lastCommand = move(history.top());
            history.pop();
            lastCommand->undo();
            gameState.restore(undoHistory.top());
            undoHistory.pop();
            Logger::log("Undid last command.");
            redoStack.push(move(lastCommand));
            redoHistory.push(gameState.save());
        } else {
            Logger::log("Nothing to undo.");
        }
    }

    void redoLastCommand() {
        if (!redoStack.empty()) {
            auto redoCommand = move(redoStack.top());
            redoStack.pop();
            gameState.restore(redoHistory.top());
            redoHistory.pop();
            redoCommand->execute();
            Logger::log("Redid last command.");
            history.push(move(redoCommand));
            undoHistory.push(gameState.save());
        } else {
            Logger::log("Nothing to redo.");
        }
    }

    void startCombat() {
        Logger::log("Starting combat phase...");
        battle();
    }
};

bool battle() {
    cout << "You encounter an enemy!" << endl;
    // Combat logic would go here
}

// Main function
int main() {
    srand(time(0));

    cout << "Welcome to discount Elden Ring!" << endl;

    int choice;
    GameState gameState;
    CommandInvoker invoker(gameState);

    while (true) {
        cout << "You are in a room. What would you like to do?" << endl;
        cout << "1. Go forward" << endl;
        cout << "2. Search for treasure" << endl;
        cout << "3. Quit" << endl;
        cout << "4. Undo last action" << endl;
        cout << "5. Redo last undone action" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                unique_ptr<GameCommand> forwardCommand = make_unique<ForwardCommand>(gameState, invoker);
                invoker.executeCommand(move(forwardCommand));
                break;
            }
            case 2: {
                unique_ptr<GameCommand> searchCommand = make_unique<SearchCommand>(gameState);
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
            case 5:
                invoker.redoLastCommand();
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
