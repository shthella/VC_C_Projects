#include "include_structure.h"

void receivePlayerDetails(int serverSocket, struct players *details) {
	// Receive the entire struct players from the server
	debug_log(2, "Receiving Player Details");
	size_t size = sizeof(struct players);
	debuglog(2, "Receiving Player details size is ", size);
	char *ptr = (char *)details;
	size_t bytesReceived = 0;
	while (bytesReceived < size) {
		ssize_t ret = recv(serverSocket, ptr + bytesReceived, size - bytesReceived, 0);
		if (ret == -1) {
			perror("Error receiving player details");
			break;
		} else if (ret == 0) {
			// Connection closed by peer
			break;
		} else {
			bytesReceived += ret;
		}
	}
	debuglog(2, "Received Player details size is ", bytesReceived);
	debug_log(2, "Completed Receiving player details");
}

void receiveScoreboard(int serverSocket, struct score *board) {
	// printing debug
	// Receive the entire struct score from the server
	debug_log(2, "Receiving score board");
	size_t size = sizeof(struct score);
	debuglog(2, "Receiving Score board size is ", size);
	char *ptr = (char *)board;
	size_t bytesReceived = 0;
	while (bytesReceived < size) {
		ssize_t ret = recv(serverSocket, ptr + bytesReceived, size - bytesReceived, 0);
		if (ret == -1) {
			perror("Error receiving scoreboard");
			break;
		} else if (ret == 0) {
			// Connection closed by peer
			break;
		} else {
			bytesReceived += ret;
		}
	}
	debuglog(2, "Received score board size is ", bytesReceived);
	debug_log(2, "Completed Receiving score board");
}

void receiveInnerValues(int serverSocket, struct inner *values) {
	// Receive the entire struct players from the server
	debug_log(2, "Receiving Inner values");
	size_t size = sizeof(struct inner);
	debuglog(2, "Receiving Inner values size is ", size);
	char *ptr = (char *)values;
	size_t bytesReceived = 0;
	while (bytesReceived < size) {
		ssize_t ret = recv(serverSocket, ptr + bytesReceived, size - bytesReceived, 0);
		if (ret == -1) {
			perror("Error receiving inner values");
			break;
		} else if (ret == 0) {
			// Connection closed by peer
			break;
		} else {
			bytesReceived += ret;
		}
	}
	debuglog(2, "Received inner values size is ", bytesReceived);
	debug_log(2, "Completed Receiving Inner values");
}

void receiveBatterScores(int serverSocket, struct batter *scores) {
	// Receive the entire struct score from the server
	debug_log(2, "Receiving batter scores");
	size_t size = sizeof(struct batter);
	debuglog(2, "Receiving batter scores size is ", size);
	char *ptr = (char *)scores;
	size_t bytesReceived = 0;
	while (bytesReceived < size) {
		ssize_t ret = recv(serverSocket, ptr + bytesReceived, size - bytesReceived, 0);
		if (ret == -1) {
			perror("Error receiving batter scores");
			break;
		} else if (ret == 0) {
			// Connection closed by peer
			break;
		} else {
			bytesReceived += ret;
		}
	}
	debuglog(2, "Received batter scores size is ", bytesReceived);
	debug_log(2, "Completed receiving batter scores");
}

void receiveBowlerUpdates(int serverSocket, struct bowler *updates) {
	// Receive the entire struct score from the server
	debug_log(2, "Receiving bowler updates");
	size_t size = sizeof(struct bowler);
	debuglog(2, "Receiving bowler updates size is ", size);
	char *ptr = (char *)updates;
	size_t bytesReceived = 0;
	while (bytesReceived < size) {
		ssize_t ret = recv(serverSocket, ptr + bytesReceived, size - bytesReceived, 0);
		if (ret == -1) {
			perror("Error receiving bowler updates");
			break;
		} else if (ret == 0) {
			// Connection closed by peer
			break;
		} else {
			bytesReceived += ret;
		}
	}
	debuglog(2, "Received Bowler updates size is ", bytesReceived);
	debug_log(2, "Completed receiving bowler updates");
}



void sendClientDetails(int clientSocket, struct Client *client_info) {
	// Calculate the size of the struct players
	debug_log(2, "Sending client details ");
	size_t size = sizeof(struct Client);
        debuglog(2, "Sending client details size is ", size);
	// Send the struct players to the client
	if (send(clientSocket, client_info, size, 0) == -1) {
		perror("Error sending client details");
	}
	debug_log(2, "completed Sending client details ");
}

char ip_addr[20];
void setDebugLevel(int argc, char *argv[]) {
    if (argc <= 4) {
        if (argc == 1) {  // Changed this condition from argc == 1 to argc == 2
            printf("\n");
            strcpy(ip_addr, "192.168.29.240");
        } else if (argc == 2) {
            //strcpy(ip_addr, "192.168.29.46");
            if(strcmp(argv[1], "--help") == 0){
                printf("Usage: ./program [IP_ADDRESS] [-v VERBOSE_LEVEL]\n");
                printf("./program            --Executable file name/compiled file name\n");
                printf("IP_ADDRESS           --IP address of a device on the network/IP of the server\n");
                printf("                     --Example format: 196.168.29.46\n");
                printf("                     --Not mandatory beacause a predefined IP is already present\n");
                printf("                     --Use only if you want to specify the certain system IP\n");
                printf("[-v VERBOSE_LEVEL]   --optional flag to enable verbose output, with VERBOSE_LEVEL indicating the level of verbosity\n");
                printf("                     --Not mandatory use if you want print the debug logs to debug the code\n");
                exit(1);
            } else {
                strcpy(ip_addr, argv[1]);
            }
        } else if (argc == 3) {
            if (!strcmp(argv[2], "-v") == 0) {
                printf("Invalid input! Enter -v\n");
                exit(1);
            } else {
                strcpy(ip_addr, argv[1]);
            }
        } else if (argc == 4) {
            if (!strcmp(argv[2], "-v") && (strcmp(argv[3], "1") == 0 || strcmp(argv[3], "2") == 0 || strcmp(argv[3], "3") == 0)) {
                DEBUG_LEVEL = atoi(argv[3]);
                strcpy(ip_addr, argv[1]);
                printf("Debug level set to: %d\n", DEBUG_LEVEL);
            } else {
                printf("Invalid input!\n Input format is -v 1 or -v 2 or -v 3 only\n");
                exit(1);
            }
        } else {
            DEBUG_LEVEL = 2;
            printf("Debug level set to: %d\n", DEBUG_LEVEL);
        }
    }
}

int main(int argc, char *argv[]) {
    int clientSocket;
    struct sockaddr_in serverAddr;
    setDebugLevel(argc, argv); // Set debug level based on command-line arguments
    debug_log(2, "The program has been started");
    int balance = 20000;
    struct Client client_info;

    // Create socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address struct
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip_addr); // Server IP address (localhost)
    serverAddr.sin_port = htons(8080); // Server port

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server.\n");
     printf("Enter your name: ");
     scanf("%s", client_info.name);

    while (1) {
     S:   char ackn[] = "ack";
        debug_log(2, "Started sending ack");
        send(clientSocket, ackn, sizeof(ackn), 0);
        debug_log(2, "Completed sending ack");
        // Inside your main function after receiving other data from the server
        recv(clientSocket,striker,sizeof(striker),0);
        receiveScoreboard(clientSocket, &board);
        receiveInnerValues(clientSocket, &values);
        receivePlayerDetails(clientSocket, &details);
        receiveBatterScores(clientSocket, &scores);
        receiveBowlerUpdates(clientSocket, &updates);
        // Display the received scoreboard
        displayScoreboard(&board, &updates, &scores, &values, &details);

        while (1) {
            printf("\n-------------TOTAL BALANCE--------------------\n");
            printf("total balance in your account:\x1b[1;32m%d\x1b[0m\n", balance);
            printf("----------------------------------------------\n\n");
            printf("do you want to bet(y|n)\n");
            scanf(" %c", &client_info.option);
            if (client_info.option == 'y' || client_info.option == 'Y' || client_info.option == 'n' || client_info.option == 'N'||client_info.option == 't' || client_info.option == 'T') {
                break;
            } else {
                printf("Invalid input!");
            }
            while (getchar() != '\n');
        }
    
        if (client_info.option == 'y') {
            while(1)
            {
            printf("enter your choice for betting \n");
            printf("1.Enter (r|R) for runs scored\n2.Enter (A|a|b|B) for wicket\n3.Enter (w|W) for wide ball\n");
            scanf(" %c",&client_info.choice);
            if(client_info.choice=='r'||client_info.choice=='R'||client_info.choice=='a'||client_info.choice=='A'||client_info.choice=='b'||client_info.choice=='B'||client_info.choice=='w'||client_info.choice=='W')
            {
            break;
            }
            else
            {
            printf("please enter valid input\n");
            }
             while (getchar() != '\n');
             }
            switch(client_info.choice)
            { 
              case 'R' :
              case 'r' : printf("you choosed runs scored \n");
              
              while (1) {
                printf("Enter runs to bet for this ball\n");
                printf("1. 1 run\n2. 2 runs\n3. 3 runs\n4. 4 runs\n6. 6 runs\n");
                scanf("%d", &client_info.bet_runs);
                if (client_info.bet_runs == 1 || client_info.bet_runs == 2 || client_info.bet_runs == 3 ||
                    client_info.bet_runs == 4  || client_info.bet_runs == 6) {
                    break;
                } else {
                    printf("Invalid input!");
                }
                while (getchar() != '\n');
            }
              break;
              case 'A' :
              case 'a' : 
              case 'B' :
              case 'b' :printf("you choosen wicket\n");
                        client_info.bet_runs=0;
                         break;
              case 'W' :
              case 'w' : printf("you choosen wide ball\n");
                        client_info.bet_runs=0;
                         break;
                         }
              

            while (1) {
                char s;
                int add_amount;
            L:
                printf("Enter the betting amount: ");
                scanf("%d", &client_info.amount);
                if (client_info.amount > balance) {
                    printf("you don't have %d in your account\n", client_info.amount);
                    printf("do you want add money to your account (y|n)\n");
                    scanf("  %c", &s);
                    if (s == 'y') {
                        printf("enter how much amount you want to add to your account\n");
                        scanf("%d", &add_amount);
                        balance = balance + add_amount;
                    } else {
                        printf("enter the betting amount less than your account balance\n");
                        goto L;
                    }
                } else {
                    if (client_info.amount) {
                        break;
                    } else {
                        printf("Invalid input!");
                    }
                    while (getchar() != '\n');
                }
            }
            balance = balance - client_info.amount;
            // Send client details to the server
            sendClientDetails(clientSocket, &client_info);

            while (1) {
                int win_amount;
                char arr[20];
                recv(clientSocket, &arr, sizeof(arr), 0);
                if (strcmp(arr, "acknowledge") == 0) {
                    int bytes_received = recv(clientSocket, &win_amount, sizeof(win_amount), 0);
                    if (bytes_received < 0) {
                        perror("Error receiving betting amount from server");
                        break; // Exit the loop if there's an error
                    } else if (bytes_received == 0) {
                        printf("Server disconnected.\n");
                        close(clientSocket);
                        break; // Exit the loop if the server disconnects
                    } else {
                           if(win_amount!=0)
                            {
                              int cas=win_amount-client_info.amount;
                              printf("\n---------win amount----------\n");
                              printf("You won: \x1b[1;32m%d\x1b[0m\n",cas);
                              printf("------------------------------\n");
                            }
                           else
                            {
                              printf("\n---------lost amount---------\n");
                              printf("you lost : \x1b[1;32m%d\x1b[0m\n",client_info.amount);
                              printf("------------------------------\n");
                              
                             }
                        balance = balance + win_amount;
                        break;
                    }
                }
            }
        }
      else if(client_info.option=='t')
        {
          break;
        }
      else
      {
        // Send client details to the server
        sendClientDetails(clientSocket, &client_info);
        char arr[20];
        int winners_count;
        recv(clientSocket, &arr, sizeof(arr), 0);
         if (strcmp(arr, "acknowledge") == 0)
         {
         recv(clientSocket,&winners_count,sizeof(winners_count),0);
         //printf("winners_count:%d\n",winners_count);
         }
        
      }
        sleep(5);
    }

    // Close the client socket
    close(clientSocket);

    return 0;
}

