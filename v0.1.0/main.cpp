#include <iostream>
#include <string>
#include <vector>
#include <locale.h>
#include <conio.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <nlohmann/json.hpp>

using json = nlohmann::json;

//ConsoleClear class
class ConsoleClear {
    public:
        static void clear() {
            #ifdef _WIN32
                std::system("cls");
            #else
                std::system("clear");
            #endif
        }
};

//coloring class
class Colors {
    public:
        // Foreground colors
        static const std::string fgReset;
        static const std::string fgRed;
        static const std::string fgGreen;
        static const std::string fgBlue;
        static const std::string fgYellow;
        static const std::string fgCyan;
        static const std::string fgMagenta;
        static const std::string fgWhite;
        static const std::string fgBlack;
    
        // Background colors
        static const std::string bgReset;
        static const std::string bgRed;
        static const std::string bgGreen;
        static const std::string bgBlue;
        static const std::string bgYellow;
        static const std::string bgCyan;
        static const std::string bgMagenta;
        static const std::string bgWhite;
        static const std::string bgBlack;
};

// Foreground colors
const std::string Colors::fgReset = "\033[0m";
const std::string Colors::fgRed = "\033[31m";
const std::string Colors::fgGreen = "\033[32m";
const std::string Colors::fgBlue = "\033[34m";
const std::string Colors::fgYellow = "\033[33m";
const std::string Colors::fgCyan = "\033[36m";
const std::string Colors::fgMagenta = "\033[35m";
const std::string Colors::fgWhite = "\033[37m";
const std::string Colors::fgBlack = "\033[30m";

// Background colors
const std::string Colors::bgReset = "\033[0m";
const std::string Colors::bgRed = "\033[41m";
const std::string Colors::bgGreen = "\033[42m";
const std::string Colors::bgBlue = "\033[44m";
const std::string Colors::bgYellow = "\033[43m";
const std::string Colors::bgCyan = "\033[46m";
const std::string Colors::bgMagenta = "\033[45m";
const std::string Colors::bgWhite = "\033[47m";
const std::string Colors::bgBlack = "\033[40m";

//Menu class
class Menu {
    public:
        Menu() = default;

        void addOption(const std::string& option) {
            options.push_back(option);
        }

        void printMenu() const {
            printHeader("Main Menu");
            for (size_t i = 0; i < options.size(); ++i) {
                printOption(i + 1, options[i]);
            }
            printFooter();
        }

        void printHeader(const std::string& header) const {
            std::cout << Colors::fgCyan << "┌───────────────────────────┐" << Colors::fgReset << std::endl;
            std::cout << Colors::fgCyan << "│ " << Colors::fgYellow << header << Colors::fgCyan << " │" << Colors::fgReset << std::endl;
            std::cout << Colors::fgCyan << "├───────────────────────────┤" << Colors::fgReset << std::endl;
        }

        void printOption(int index, const std::string& option) const {
            std::cout << Colors::fgCyan << "│ " << Colors::fgGreen << index << ". " << option << Colors::fgCyan << " │" << Colors::fgReset << std::endl;
        }

        void printFooter() const {
            std::cout << Colors::fgCyan << "└───────────────────────────┘" << Colors::fgReset << std::endl;
        }

    private:
        std::vector<std::string> options;
};

//Chat class
class Chat {
    public:
        Chat() = default;
    
        void addMessage(const std::string& message) {
            messages.push_back(message);
        }
    
        void printChat() const {
            ConsoleClear::clear();
            std::cout << Colors::fgYellow << "Chat History:" << Colors::fgReset << std::endl;
            for (const auto& message : messages) {
                std::cout << Colors::fgCyan << "You: " << Colors::fgReset << message << std::endl;
            }
            std::cout << Colors::fgYellow << "Type your message below (Press ESC to exit):" << Colors::fgReset << std::endl;
        }
    
    private:
        std::vector<std::string> messages;
    };
    
    void startChat(Chat& chat) {
        std::string message;
    
        while (true) {
            chat.printChat();
    
            // Check if the Escape key is pressed
            if (_kbhit()) { // Windows-specific; use termios for Linux
                char key = _getch();
                if (key == 27) { // ASCII code for Escape key
                    std::cout << Colors::fgRed << "Exiting chat..." << Colors::fgReset << std::endl;
                    break;
                }
            }
    
            // Check if there is input available in std::cin
            if (std::cin.peek() != EOF) {
                std::cout << Colors::fgGreen << "You: " << Colors::fgReset;
                if (std::getline(std::cin, message)) {
                    if (!message.empty()) {
                        chat.addMessage(message);
                    }
                } else {
                    // Handle input failure (e.g., Ctrl+D or EOF)
                    std::cin.clear(); // Clear the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                }
            }
        }
    };

int main(){
    setlocale(LC_ALL, "");

    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Set console output to UTF-8
    #endif

    Menu menu;

    menu.addOption("Start Chat");
    menu.addOption("View Chat History");
    menu.addOption("Settings");
    menu.addOption("Exit");

    Chat chat;

    while (true){
        menu.printMenu();

        int choice = 0;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        switch (choice){

            //start chat
            case 1:
                std::cout << "Starting chat..." << std::endl;
                startChat(chat);
                break;

            //view chat history
            case 2:
                std::cout << "Viewing chat history..." << std::endl;
                chat.printChat();
                break;

            //settings
            case 3:
                ConsoleClear::clear();
                std::cout << "Opening settings..." << std::endl;
                break;
            
            //exit
            case 4:
                ConsoleClear::clear();
                std::cout << "Exiting..." << std::endl;
                return 0;

            //default case
            default:
                ConsoleClear::clear();
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
    return 0;
}