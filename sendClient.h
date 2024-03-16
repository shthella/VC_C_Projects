void sendPlayerDetails(int clientSocket, struct players *details) {
	// Calculate the size of the struct players
	debug_log(2, "sending player details started....");
	size_t size = sizeof(struct players);
	debuglog(2, "sending player details size is",size);
	//printf("client socket:%d\n",clientSocket);
	// Send the struct players to the client
	if (send(clientSocket, details, size, 0) == -1) {
		perror("Error sending player details");
	}
	 debug_log(2, "sending player details completed....");
}

void sendInnerValues(int clientSocket, struct inner *values) {
	// Calculate the size of the struct inner
	debug_log(1, "sending innier values started....");
	size_t size = sizeof(struct inner);
	debuglog(2, "sending innervalues size is",size);
        //printf("client socket:%d\n",clientSocket);
	// Send the struct inner to the client
	if (send(clientSocket, values, size, 0) == -1) {
		perror("Error sending inner values");
	}
	  debug_log(1, "sending innier values completed....");
}

void sendScoreBoard(int clientSocket, struct score *board) {
	// Calculate the size of the struct score
	debug_log(1, "sending scoreboard started....");
	size_t size = sizeof(struct score);
	debuglog(2, "sending score board size is",size);
         //printf("client socket:%d\n",clientSocket);
	// Send the struct players to the client
	if (send(clientSocket, board, size, 0) == -1) {
		perror("Error sending score board");
	}
	debug_log(1, "sending scoreboard completed....");
}

void sendBowlerUpdates(int clientSocket, struct bowler *updates) {
	// Calculate the size of the struct players
	debug_log(1, "sending bowler updates started....");
	size_t size = sizeof(struct bowler);
	debuglog(2, "sending bowler updates size is",size);
        //printf("client socket:%d\n",clientSocket);
	// Send the struct players to the client
	if (send(clientSocket, updates, size, 0) == -1) {
		perror("Error sending bowler updates");
	}
	 debug_log(1, "sending bowler updates completed....");
}

void sendBatterScores(int clientSocket, struct batter *scores) {
	// Calculate the size of the struct players
	debug_log(1, "sending batter scores started....");
	size_t size = sizeof(struct batter);
	debuglog(2, "sending batterscores size is",size);
        //printf("client socket:%d\n",clientSocket);
	// Send the struct players to the client
	if (send(clientSocket, scores, size, 0) == -1) {
		perror("Error sending batter scores");
	}
	debug_log(1, "sending batter scores updated....");
}
void split_amount(void)
{       
        debug_log(1, "Entered into split amount function");
	int winnings=0,winners_count=0,split_amount,profit,split_amount1;
	char ack[20]="acknowledge";
	//printf("runs scored %d\n",values.runs_scored);
	for (int j = 0; j < client_num; j++) 
	  {
	    if(clients[j].option=='y')
	      {
	        if(user == 'g' ||user == 'G'||user == 'n' ||user == 'N')
	        {
			if(clients[j].choice=='r' || clients[j].choice=='R')
			{
				if (clients[j].bet_runs == values.runs_scored)
				{
					clients[j].status = 1; // Set status to indicate a win
					winners_count++; // Increase the count of winners
			        }
				else {
					// Client's bet does not match the runs scored
					clients[j].status = 0; // Set status to indicate a loss
					winnings += clients[j].amount; // Update total winnings
				}
			}
			else
		                {
	                         // Client's bet does not match the runs scored
			         clients[j].status = 0; // Set status to indicate a loss
			         winnings += clients[j].amount; // Update total winnings
		                }
			
		}
		
	      else if(user == 'a' || user== 'A' || user== 'b' ||user == 'B')
			{
			      if(clients[j].choice == 'a'||clients[j].choice == 'A' ||clients[j].choice == 'b' ||clients[j].choice == 'B')
                               {
			         clients[j].status = 1; // Set status to indicate a win
				 winners_count++;
			       }
			      else
		                {
	                         // Client's bet does not match the runs scored
			         clients[j].status = 0; // Set status to indicate a loss
			         winnings += clients[j].amount; // Update total winnings
		                }
			}
	      else if(user=='w' || user =='W')
			{
			    if(clients[j].choice == 'w' ||clients[j].choice == 'W')
			       {
			          clients[j].status = 1; // Set status to indicate a win
				  winners_count++;
			       }
			    else
		              {
	                          // Client's bet does not match the runs scored
			         clients[j].status = 0; // Set status to indicate a loss
			         winnings += clients[j].amount; // Update total winnings
		              }
			}
		}
         }
	//gain is for profit of 10%
	profit=winnings/10;
	winnings=winnings-profit;
	// Calculate and distribute winnings
	if (winners_count > 0) {
		// Calculate split amount for each winner
		int split_amount = winnings / winners_count;
		int zero=0;
		// Send winnings to each winner
		for (int j = 0; j < client_num; j++) {
			char arr[20]="acknowledge";
		  if(clients[j].option=='y')
		    {
			send(clients[j].fd,&arr,sizeof(arr),0);
			 debug_log(2, "sending acknowledgement to client amount splitting completed");
			if (clients[j].status == 1) 
			{
				split_amount1=clients[j].amount+split_amount;

				if(send(clients[j].fd, &split_amount1, sizeof(split_amount), 0)<0)
				{
					printf("error sending\n");
				}
				else
				{
				         debug_log(2, "sent win amount to winner client");
				         clients[j].amount=0;
					//printf("Sent split amount %d to winner client %s\n", split_amount1, clients[j].name);
				}
			}
			else if(clients[j].status==0)
			{
				if(send(clients[j].fd,&zero,sizeof(zero),0)<0)
				{
					printf("error sending");
				}
				else
				{
				         debug_log(2, "sent zero to looser client");
				           clients[j].amount=0;
					//printf("sent 0 to the looser client\n");
				}
			}
		 }
		 else if(clients[j].option =='n')
		 {
		      debug_log(1, " sending winners count to client because client don't want to bet have to wait until betting process completed to get scoreboard");
		     send(clients[j].fd,&winners_count,sizeof(winners_count),0);
		 }
		}
		//printf("winners for this ball is %d\n", winners_count);
	}
	else {
		int zero=0;
		debug_log(2, "no winners this time");
		for (int j = 0; j < client_num; j++)
		{
		         debug_log(1, "no winners this time so sending zeros to betted clients");
			send(clients[j].fd,&ack,sizeof(ack),0);
			send(clients[j].fd,&zero,sizeof(zero),0);
			  clients[j].amount=0;
		}

	   }
	debug_log(1, "Leaving the split amount function");	
	strcpy(buf,"hello");
}
