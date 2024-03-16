// Function to update the scoreboard based on the current ball
void updateScoreboard(struct score *board, struct inner *values) {
	// Update runs, overs, and wickets
	debug_log(1,"entered into update scoreboard function");
	debug_log(2 ,"In this function updating total runs , total overs , total wickets ,extra balls ,required runs,run rate");
	board->runs = board->runs + values->runs_scored + values->wide_ball;  // Total runs
	board->overs = values->overs_bowled;                                 // Total overs
	board->wickets += values->wickets_taken;                             // Total wickets
	board->extra_balls += values->extra_ball;                            // Extra balls bowled
									     // Calculate required runs and run rate for the second innings
	if (values->innings == 2) {
		board->req_runs = board->target - board->runs;                   // Required runs
		board->req_run_rate = board->req_runs / (values->total_overs - board->overs); // Required run rate
	} else {
		// Reset values for the first innings
		board->req_runs = 0;
		board->req_run_rate = 0;
	}
	// Calculate the current run rate
	board->run_rate = board->runs / board->overs;
	debug_log(1,"exiting from update scoreboard function");
}
// Function to update the current bowler's name with an extra character
void bowlerCurrent(struct players *details, int *index, int startIndex, int stopIndex, struct inner *values) {
	int length;
	char extraChar;
        debug_log(2 , "Entered into the bowler current function");
	// Check if the current over is completed
	if (values->balls % MAX_BALLS_PER_OVER == 0) {
		// Remove the last character from the current bowler's name
		length = strlen(details->names[*index]);
		if (length > 0) {
			details->names[*index][length - 1] = '\0';
		}
		extraChar = '*'; // Extra character to mark the current bowler
		++*index; // Move to the next bowler
		length = strlen(details->names[*index]);
		// Add the extra character at the end of the new bowler's name
		details->names[*index][length] = extraChar;
		details->names[*index][length + 1] = '\0';
		// If all bowlers have bowled their overs, mark the first bowler with the extra character too
		if (*index == stopIndex) {
			*index = startIndex;
			length = strlen(details->names[*index]);
			details->names[*index][length] = extraChar;
			details->names[*index][length + 1] = '\0';
		}
	}
	debug_log(2 , "Leaving bowlercurrent function");
}

// Function to update bowler statistics after each ball
void updateBowlerStats(struct inner *values, struct bowler *updates) {
	// If it's a regular ball (not wide or extra)
	debug_log(1, "Entered into the update bowlerstats function");
	debug_log(2 ,"In this function updating bowlers statistics  overs bowled, wickets taken,economy");
	if (values->wide_ball == 0 && values->extra_ball == 0) {
		// Update balls, runs, over runs, overs, and economy
		updates->bowler_balls[updates->bowler_change] += 1;
		updates->bowler_runs[updates->bowler_change] += values->runs_scored;
		updates->bowler_over_runs[updates->bowler_change] += values->runs_scored;
		updates->bowler_over1[updates->bowler_change] = updates->bowler_balls[updates->bowler_change] / MAX_BALLS_PER_OVER;
		updates->bowler_over2[updates->bowler_change] = updates->bowler_balls[updates->bowler_change] % MAX_BALLS_PER_OVER;
		// If a wicket is taken, update wickets
		if (values->wickets_taken) {
			(updates->bowler_wickets[updates->bowler_change]) += 1;
		}
		// If the over is completed
		if (updates->bowler_balls[updates->bowler_change] % MAX_BALLS_PER_OVER == 0) {
			// If it's a maiden over (no runs scored)
			if (updates->bowler_over_runs[updates->bowler_change] == 0) {
				(updates->bowler_maiden[updates->bowler_change]) += 1;
				(updates->bowler_over_runs[updates->bowler_change]) = 0;
			}
			// Update overs bowled and economy
			updates->overs_bowled[updates->bowler_change] += 1;
			updates->economy[updates->bowler_change] = updates->bowler_runs[updates->bowler_change] / updates->overs_bowled[updates->bowler_change];
			updates->bowler_change += 1;  // Increment bowler_change when the over is completed
		}
	}
	// If it's a wide ball, only update runs
	else if (values->wide_ball) {
		(updates->bowler_runs[updates->bowler_change]) += 1;
		(updates->bowler_over_runs[updates->bowler_change]) += 1;
	}
	// If it's an extra ball, update runs and wickets if taken
	else if (values->extra_ball) {
		(updates->bowler_runs[updates->bowler_change]) += values->runs_scored;
		(updates->bowler_over_runs[updates->bowler_change]) += values->runs_scored;
		if (values->wickets_taken) {
			(updates->bowler_wickets[updates->bowler_change]) += 1;
		}
	}
	// Reset bowler_change when all bowlers have bowled their overs
	if (updates->bowler_change == 5) {
		updates->bowler_change = 0;
	}
	debug_log(1, "Leaving update bowlerstats function");
}

// Function to update scores of a particular batter for each innings
void batterUpdatesInnings(struct batter *scores, struct inner *values, char batter[], struct players *details) {
	int index = 0, current = 0;
	debug_log(1 , "Entered into batterupdatesInnings function");
	if (values->innings == 1) {
		index = 4; // Starting index for the first innings
		current = 0; // Current batter index
	} else if (values->innings == 2) { // Check if it's the second innings
		index = 16; // Starting index for the second innings
		current = 0; // Current batter index
	}
	while (1) {
		if (!strcmp(batter, details->names[index])) {
			scores->batter_balls[current] += 1;
			scores->batter_runs[current] += values->runs_scored;
			scores->batter_strike[current] = (scores->batter_runs[current] * 100) / scores->batter_balls[current];
			if (values->runs_scored == 4) {
				scores->batter_fours[current] += 1; // Increment the number of fours
				debug_log(2 ," incrementing 4's");
			}
		        else if (values->runs_scored == MAX_BALLS_PER_OVER) { // Check if the runs scored by the batter is a six
				scores->batter_sixes[current] += 1; // Increment the number of sixes
				debug_log(2 ," incrementing 6's");
			}
			break; // Exit the loop
		} else {
			index++; // Move to the next batter
			current++; // Move to the next index for tracking current batter
		}
	}
	debug_log(2,"In this function updating batter statistics  runs scored, strike rate, total 4's and 6's");
	debug_log(1, "Leaving from batterupdatesInnings function");
}

