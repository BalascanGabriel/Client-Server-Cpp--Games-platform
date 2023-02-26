#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "Com.h"
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include <string>



// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "9000"

using namespace std;


int __cdecl main(int argc, char** argv)
{
  
    // Validate the parameters
    /*if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }*/


    // Initialize Winsock
    
    Com com;

    /*com.send_message("op_login");
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    com.send_message("bob");
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    com.send_message("1234");*/
   

    // --------------- testare start game poker -----------------------

    // 
  com.send_message("op_start_game_poker");
    bool continue_playing = true;
    while (continue_playing) {

        std::vector<std::string> options;
        options.push_back("tie");
        options.push_back("banker");
        options.push_back("player");
        options.push_back("banker_pair");
        options.push_back("player_pair");

        std::cout << "Your choice: " << std::endl;
        for (int i = 0; i < options.size(); i++) {
            std::cout << "\t\t" << i << ". " << options[i] << std::endl;
        }
        int choice;
        cin >> choice;

        com.send_message(options[choice]);

        std::string server_message = com.get_message();
        std::cout << "SERVER MESSAGE: " << server_message << std::endl;

        cout << "Do you want to continue 0. no 1. yes" << endl;
        int end;
        cin >> end;
        continue_playing = (end == 0) ? false : true;
        if (continue_playing) {
            com.send_message("continue");
        }
        else {
            com.send_message("end");
        }

    }
    
    // --------------- testare start game blackjack -----------------------
    /*
    com.send_message("op_start_game_black_jack");
    bool continue_playing = true;
    while (continue_playing) {
        std::string server_message = com.get_message();
        cout << "YOUR CARDS (2)/ DEALER CARD (1): " << server_message << endl;

        std::string action;
        cout << "Action? 1. stand 2. hit" << endl;
        int choice;
        cin >> choice;

        bool game_over = false;
        while (choice != 1 && !game_over) {
            switch (choice) {
            case 1:
                action = "stand";
                break;
            case 2:
                action = "hit";
                break;
            }
            com.send_message(action);
            std::string sm = com.get_message();

            // 
            if (sm.find("GAME OVER") != std::string::npos) {
                std::cout << "GAME OVER ---" << endl;
                game_over = true;
            }
            cout << "YOUR CARDS: " << sm << endl;
            if (game_over) {
                break;
            }
           
            cout << "Action? 1. stand 2. hit" << endl;
            cin >> choice;
        }


        if (!game_over) {
            com.send_message("stand");
            std::string sm = com.get_message();
            cout << "***DUPA STAND**: " << endl;

            cout << sm << endl;
        }
        cout << "Do you want to continue 0. no 1. yes" << endl;
        int end;
        cin >> end;
        continue_playing = (end == 0) ? false : true;
        if (continue_playing) {
            com.send_message("continue");
        }
        else {
            com.send_message("end");
        }
        // game over 
    }
   
    
    */
    //cout << "Baga username: ";
    // --------------- testare login -----------------------
    //string username;
    //string password;

    //com.send_message("op_login");
    //cout << "Baga username: ";

    //cin >> username;
    //com.send_message(username);

    //cout << "Baga parola: ";
    //cin >> password;
    //com.send_message(password);


    //int id_user = atoi(com.get_message().c_str());

    //if (id_user == 0) {
    //    // register failed
    //    cout << "Logare esuata" << endl;
    //}
    //else {
    //    // register succeded
    //    cout << "Te-ai logat cu user-ul: " << id_user << endl;
    //}

    // --------------- testare register -----------------------
    //string username;
    //string password;

    //com.send_message("op_register");
    //cout << "Baga username: ";

    //cin >> username;
    //com.send_message(username);
    //
    //cout << "Baga parola: ";
    //cin >> password;
    //com.send_message(password);


    //int id_user = atoi(com.get_message().c_str());

    //if (id_user == 0) {
    //    // register failed
    //    cout << "Inregistrare esuata" << endl;
    //}
    //else {
    //    // register succeded
    //    cout << "Te-ai inregistrat cu user-ul: " << id_user << endl;
    //}
    //
    // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    // com.send_message("bob@gmail.com");
//    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    

    //com.send_message("op_register");
    //com.send_message("op_start_game_poker");
    system("pause");
    return 0;
}