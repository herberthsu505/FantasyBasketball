//Herbert Hsu
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;
class Player  //build stats for players
{
	private:
		ifstream in1, in2; //two input files
		vector<double> weights; //weights
		vector<vector<double> > playerStats; //2d array of player stats
   		vector<double> playerStatsLine; //each players stats in playerStats
		vector<string> playerList; //player names
		vector<double> offStats; //player offensive stats
		vector<double> defStats; //player defensive stats
		vector<double> shootStats; //player shooting stats
		vector<double> playerScores; //player score based on weight
		int numPlayers;
	public:
		Player(string, string);
		void InputWeight();
		void BuildStats();
		void BuildList();
		void BuildOffStats();
		void BuildDefStats();
		void BuildShootStats();
		void PlayerScores();
		vector<double> GetOffStats() const;
		vector<double> GetDefStats() const;
		vector<double> GetShootStats() const;
		vector<double> GetPlayerScore() const;
		vector<string> GetPlayerList() const;
};
Player::Player(string playerFile, string weightFile) //constructor, run functions that build the vectors
{
	in1.open(playerFile.c_str());
    in2.open(weightFile.c_str());
    InputWeight();
    BuildStats();
    BuildOffStats();
	BuildDefStats();
	BuildShootStats();
	PlayerScores();
}
void Player::InputWeight() //store weghts into vector from cvs
{
    string line;
    while (getline(in2, line, ',')) //read from cvs 
    {
        weights.push_back(atof(line.c_str()));
    }
}
void Player::BuildStats() //build stats needed from large stats file, and store player names
{
	vector<vector<double> > tempValues;
    vector<double> tempValueLine;
    vector<vector<string> > tempValues2;
    vector<string> tempValueLine2;
    string item;
    for (string line; getline(in1, line); ) //get all stats from cvs file
    {
        istringstream in(line);
        numPlayers++;
        while (getline(in, item, ','))
        {
            tempValueLine.push_back(atof(item.c_str()));
            tempValueLine2.push_back(item);
        }
        tempValues.push_back(tempValueLine);
        tempValues2.push_back(tempValueLine2);
        tempValueLine.clear();
        tempValueLine2.clear();
    }
    for(unsigned int i = 0; i<tempValues.size(); i++) //only extract stats we need
    {
        playerStatsLine.push_back(tempValues.at(i).at(8)); //FG 0
        playerStatsLine.push_back(tempValues.at(i).at(9)); //FGA 1
        playerStatsLine.push_back(tempValues.at(i).at(11)); //3P 2
        playerStatsLine.push_back(tempValues.at(i).at(18)); //FT 3 
        playerStatsLine.push_back(tempValues.at(i).at(19)); //FTA 4
        playerStatsLine.push_back(tempValues.at(i).at(23)); //TRB 5
        playerStatsLine.push_back(tempValues.at(i).at(24)); //AST 6
        playerStatsLine.push_back(tempValues.at(i).at(25)); //STL 7
        playerStatsLine.push_back(tempValues.at(i).at(26)); //BLK 8
        playerStatsLine.push_back(tempValues.at(i).at(27)); //TOV 9
        playerStatsLine.push_back(tempValues.at(i).at(29)); //PTS 10

        playerStats.push_back(playerStatsLine); //store into 2d arrau
        playerStatsLine.clear();
    }
    for(unsigned int i = 0; i<tempValues2.size(); i++)
    {
        playerList.push_back(tempValues2.at(i).at(1)); //name
    }
    playerStats.erase(playerStats.begin());
    playerList.erase(playerList.begin());
}
void Player::BuildOffStats() //build offensive stats
{
	for(unsigned int i = 0; i <playerStats.size(); i++)
	{
		offStats.push_back(playerStats.at(i).at(6) + playerStats.at(i).at(10));
	}
}
void Player::BuildDefStats() //build defensive stats
{
	for(unsigned int i = 0; i <playerStats.size(); i++)
	{
		defStats.push_back(playerStats.at(i).at(5) + 
		playerStats.at(i).at(7) + playerStats.at(i).at(8));
	}
}
void Player::BuildShootStats() //build shooting stats
{
	for(unsigned int i = 0; i <playerStats.size(); i++)
	{
		shootStats.push_back(playerStats.at(i).at(2) + playerStats.at(i).at(3));
	}
}
void Player::PlayerScores() //player score based on weight
{
	for(unsigned int i = 0; i <playerStats.size(); i++)
	{
		double score = weights.at(0)*playerStats.at(i).at(0) + weights.at(1)*playerStats.at(i).at(1) 
		+ weights.at(2)*playerStats.at(i).at(4) + weights.at(3)*playerStats.at(i).at(3) 
		+ weights.at(4)*playerStats.at(i).at(2) + weights.at(5)*playerStats.at(i).at(10) 
		+ weights.at(6)*playerStats.at(i).at(5) + weights.at(7)*playerStats.at(i).at(6) 
		+ weights.at(8)*playerStats.at(i).at(7) + weights.at(9)*playerStats.at(i).at(8) 
		+ weights.at(10)*playerStats.at(i).at(9);

		playerScores.push_back(score);
	}
}
vector<double> Player::GetOffStats() const //accessor
{
	return offStats;
}
vector<double> Player::GetDefStats() const//accessor
{
	return defStats;
}
vector<double> Player::GetShootStats() const//accessor
{
	return shootStats;
}
vector<double> Player::GetPlayerScore() const//accessor
{
	return playerScores;
}
vector<string> Player::GetPlayerList() const//accessor
{
	return playerList;
}
class Team //build team in league
{
	private:
		int numTeam, numPlayer, randomSeed;
		vector<int> players;
		vector<vector<int> > team; //2d vector of teams
		vector<double> offStatsTeam;
		vector<double> defStatsTeam;
		vector<double> shootStatsTeam;
		vector<double> offStatsTeamConst;
		vector<double> defStatsTeamConst;
		vector<double> shootStatsTeamConst;
		vector<double> playerScore;
		vector<string> playerNames;
		vector<double> winningTeamPlayer;
		vector<vector<double> > winningTeam;


	public:
		Team(int ,int, int, vector<double>, vector<double>, vector<double>, vector<double>, vector<string>);
		void BuildTeamStrat();
		void BuildTeam();
		int ReturnMaxIndex(const vector<double>&);
		double GetTeamScore(int);
		void Trade();
		void PrintOutput();
		int FindWinningTeam();
		vector<double> ReturnTeamStats(const vector<int>&, int);
		string ReturnStrat(const vector<int>&);
		void SortWinningTeam(int);
		bool operator >(const Team&);

};
Team::Team(int a, int b, int c, vector<double> oStat, vector<double> dStat, vector<double> sStat, vector<double> pScore, vector<string> pName)
{
	numTeam = a;
	numPlayer = b;		
	randomSeed = c;
	srand(randomSeed);
	offStatsTeam = oStat;
	defStatsTeam = dStat;
	shootStatsTeam = sStat;
	offStatsTeamConst = oStat;
	defStatsTeamConst = dStat;
	shootStatsTeamConst = sStat;
	playerScore = pScore;
	playerNames = pName;
}

void Team::BuildTeamStrat() //decide team strategy
{
	for(int i = 0; i< numTeam; i++)
	{
		if(i%3==0)
		{
			players.push_back(0);
		}
		else if(i%3==1)
		{
			players.push_back(1);
		}
		else
		{
			players.push_back(2);
		}
		team.push_back(players); //first number in each vector is the strategy
		players.clear();
	}	
}
bool Team::operator >(const Team& t)
{
	if(GetTeamScore(0)>GetTeamScore(1))
		return true;
	return false;
}
void Team::BuildTeam() //draft players based on strategy
{	
	unsigned int pick;
	unsigned int count = 0;

	while(count < numTeam*numPlayer && count <  playerNames.size())
	{
		pick = rand()%numTeam; //random number 
		int in = 0;
		//draft based on strategy
		if(team.at(pick).at(0)==0 && team.at(pick).size()<=numPlayer)
		{
			in = ReturnMaxIndex(offStatsTeam); //get highest score in list for the strategy
			team.at(pick).push_back(in); //add player
			offStatsTeam.at(in) = -1; //delete player from list
			defStatsTeam.at(in) = -1; //delete player from list
			shootStatsTeam.at(in) = -1; //delete player from list
			count++;
		}
		else if(team.at(pick).at(0)==1 && team.at(pick).size()<=numPlayer)
		{
			in = ReturnMaxIndex(defStatsTeam);
			team.at(pick).push_back(in);
			offStatsTeam.at(in) = -1;
			defStatsTeam.at(in) = -1;
			shootStatsTeam.at(in) = -1;
			count++;

		}
		else if(team.at(pick).at(0)==2 && team.at(pick).size()<=numPlayer)
		{
			in = ReturnMaxIndex(shootStatsTeam);
			team.at(pick).push_back(in);
			offStatsTeam.at(in) = -1;
			defStatsTeam.at(in) = -1;
			shootStatsTeam.at(in) = -1;
			count++;
		}
	}
}
int Team::ReturnMaxIndex(const vector<double>& v) //find max in vector
{
	double max = v.at(0);
    int pos = 0;

    for (unsigned int i = 0; i<v.size(); i++)
    {
        if(max<v.at(i))
        {
            max = v.at(i);
            pos = i;
        }
    }
    return pos;
}
void Team::Trade() //trading
{
	if(numTeam%2 == 0 && numTeam>1) //if number of teams is even
	{
		for(int i = 0; i<numTeam-1; i+=2)
		{
			if(team.at(i).size()>1 && team.at(i+1).size()>1)
			{
				vector<int> temp = team.at(i);
				int inTrade1, inTrade2, valTrade1, valTrade2;
				inTrade1 = ReturnMaxIndex(ReturnTeamStats(team.at(i+1), team.at(i).at(0))) + 1; //find index of player to trade 
				valTrade1 = team.at(i+1).at(inTrade1); //player to trade
				inTrade2 = ReturnMaxIndex(ReturnTeamStats(team.at(i), team.at(i+1).at(0))) + 1; //find index of player to trade
				valTrade2 = team.at(i).at(inTrade2); //player to trade
				team.at(i).at(inTrade2) = valTrade1;
				team.at(i+1).at(inTrade1) = valTrade2;

			}
		}
	}
	else if(numTeam%2 == 1 && numTeam>1) //if number of team is odd
	{
		for(int i = 0; i<numTeam-2; i+=2)
		{
			if(team.at(i).size()>1)
			{
				vector<int> temp = team.at(i);
				int inTrade1, inTrade2, valTrade1, valTrade2;
				inTrade1 = ReturnMaxIndex(ReturnTeamStats(team.at(i+1), team.at(i).at(0))) + 1;
				valTrade1 = team.at(i+1).at(inTrade1);
				inTrade2 = ReturnMaxIndex(ReturnTeamStats(team.at(i), team.at(i+1).at(0))) + 1;
				valTrade2 = team.at(i).at(inTrade2);
				team.at(i).at(inTrade2) = valTrade1;
				team.at(i+1).at(inTrade1) = valTrade2;
			}
		}
	}

}
vector<double> Team::ReturnTeamStats(const vector<int>& playerInTeam, int strat) //retrun off/def/shoot stats of team
{
	vector<double> TeamStats;
	if(strat == 0)
	{
		for(unsigned int i = 1; i<playerInTeam.size(); i++)
		{
			TeamStats.push_back(offStatsTeamConst.at(playerInTeam.at(i)));
		}
	}
	else if(strat == 1)
	{
		for(unsigned int i = 1; i<playerInTeam.size(); i++)
		{
			TeamStats.push_back(defStatsTeamConst.at(playerInTeam.at(i)));
		}
	}
	else
	{
		for(unsigned int i = 1; i<playerInTeam.size(); i++)
		{
			TeamStats.push_back(shootStatsTeamConst.at(playerInTeam.at(i)));
		}
	}

	return TeamStats;
}

int Team::FindWinningTeam() //find winning team
{
	double max = GetTeamScore(0);
    int maxIn = 0;
	for(unsigned int i = 0; i<team.size(); i++) //find max score
	{
		if(max<GetTeamScore(i))
        {
            max = GetTeamScore(i);
            maxIn = i;
        }
	}
	return maxIn;
}

double Team::GetTeamScore(int pos) //get total team score
{
	double score = 0;
	for(unsigned int i = 1; i<team.at(pos).size(); i++)
	{
		score = score + playerScore.at(team.at(pos).at(i));
	}

	return score;
}

void Team::SortWinningTeam(int winIndex) //sort the winning team from highest to lowest
{

	for(unsigned int i = 1; i<team.at(winIndex).size(); i++)
	{
		winningTeamPlayer.push_back(team.at(winIndex).at(i));
		winningTeamPlayer.push_back(playerScore.at(team.at(winIndex).at(i)));

		winningTeam.push_back(winningTeamPlayer);
		winningTeamPlayer.clear();
	}
   	
   	int length = winningTeam.size();
   	//sort 
    for (int i = 0; i < length; ++i)
    {
        int min = i;
        for (int j = i+1; j < length; ++j)
        {
            if (winningTeam.at(j).at(1) > winningTeam.at(min).at(1))
            {
                min = j;
            }
        }

        if (min != i)
        {
            //swap
            double tmp = winningTeam.at(i).at(1);
		    winningTeam.at(i).at(1) = winningTeam.at(min).at(1);
		    winningTeam.at(min).at(1) = tmp;
		    int tmp2 = winningTeam.at(i).at(0);
		    winningTeam.at(i).at(0) = winningTeam.at(min).at(0);
		    winningTeam.at(min).at(0) = tmp2;
        }
    }

}
void Team::PrintOutput() //print based on format given
{	
	cout<< "Fantasy Basketball Winner is: "<< endl;
	cout<< "Team "<< FindWinningTeam()<< endl;
	cout<< "Strategy: "<< ReturnStrat(team.at(FindWinningTeam()))<< endl;
	SortWinningTeam(FindWinningTeam());
	for(unsigned int i = 0; i<winningTeam.size(); i++)
	{
		cout << fixed;
		cout << setprecision(3);
		cout<< "Player: "<< playerNames.at(winningTeam.at(i).at(0))<< " (Score: "<<winningTeam.at(i).at(1)<<")"<<endl;
	}
	cout << fixed;
	cout << setprecision(3);
	cout<< "Total score: "<< GetTeamScore(FindWinningTeam())<< endl;
}
string Team::ReturnStrat(const vector<int>& vec) //return strategy in string
{
	if(vec.at(0)==0)
	{
		return "OFF";
	}
	if(vec.at(0)==1)
	{
		return "DEF";
	}
	else
	{
		return "SHOOT";
	}
}
int main()
{
	string playerFName, weightFName, line;
	int numTeams, numPlayers, randSeed;
	getline(cin, line);
	istringstream inSS(line);  
	inSS >> playerFName;
    inSS >> weightFName;
    inSS >> numTeams;
    inSS >> numPlayers;
    inSS >> randSeed;
    playerFName = playerFName+".csv"; //add cvs to filename
    weightFName = weightFName+".csv";
    Player p1(playerFName, weightFName);
    Team t1(numTeams, numPlayers, randSeed, p1.GetOffStats(), p1.GetDefStats(), p1.GetShootStats(), p1.GetPlayerScore(), p1.GetPlayerList());
    t1.BuildTeamStrat();
    t1.BuildTeam();
    t1.Trade();
    t1.PrintOutput();
}