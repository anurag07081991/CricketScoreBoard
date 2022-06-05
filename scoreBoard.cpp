
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>

using namespace std;

int first_team_score = 0;
int first_inning_finished = 0;

class Player
{
public:
    char name_of_player[26];
    int no_of_runs_scored;
    int no_of_balls_played;
    int no_of_fours_scored, no_of_sixes_scored;

    Player()
    {
        strcpy(name_of_player, "");
        no_of_runs_scored = 0;
        no_of_balls_played = 0;
        no_of_fours_scored = 0;
        no_of_sixes_scored = 0;
    }
    void setname()
    {
        cout << "enter the player name ";
        cin >> name_of_player;
    }
};

class Team
{
public:
    char teamName[10];
    Player p[5];
    int over_played_by_team;
    int over_balls;
    int total_runs_scored_by_team;
    int fall_of_wickets; 

    int on_strike_batsman;
    int far_end_batsman;

    Team()
    {
        strcpy(teamName, "");
        over_played_by_team = 0;
        total_runs_scored_by_team = 0;
        on_strike_batsman = 0;
        far_end_batsman = 1;

        fall_of_wickets = 0;
        
    }
    void setTeamname()
    {
        cout << "Enter the Team name ";
        cin >> teamName;
    }

    bool strike_changed(int runs)
    {
        switch (runs)
        {

        case 1:
        case 5:
        case 3:
            return true;
        case 0:
        case 2:
        case 4:
        case 6:
            return false;
        default:
            cout << "Invalid Run";
        }
        return NULL;
    }

    void inningsStarted(int over)
    {

        char result;
        for (int i = 1; i <= 6*over; i++)
        {
            cout << "enter the result(0 to 6 )(w for wickets and e for extras)\t:";
            cin >> result; // Change the w to lower
            
            over_balls = i%6; // over updated

            // if ball is wide or no ball
            if(result == 'd' || result == 'n')
            {
                total_runs_scored_by_team++;
                i--;
                over_balls = i%6;
            }
           
           //wicket taken by bowling team
            if (result == 'w' || result == 'W')
            {
                p[on_strike_batsman].no_of_balls_played++;
                // first display the player details after fall of his wickets
                fall_of_wickets++;
                on_strike_batsman = (on_strike_batsman > far_end_batsman) ? on_strike_batsman + 1 : far_end_batsman + 1;
            }
            if(fall_of_wickets >= 4)
            {
                first_inning_finished = 1;
                first_team_score = total_runs_scored_by_team;
                return;
            }
            if (result >= 48 && result <= 57)
            {
                p[on_strike_batsman].no_of_runs_scored += result - 48;

                /* no_of_runs_scored=0;
                    no_of_balls_played=0;
                    */
                p[on_strike_batsman].no_of_balls_played++;

                if(result == 52)
                {
                    p[on_strike_batsman].no_of_fours_scored++;
                }

                if(result == 54)
                {
                    p[on_strike_batsman].no_of_sixes_scored++;
                }
            

                /*
                  total_runs_scored_by_team = 0;
                  on_strike_batsman = 0;
                  far_end_batsman=1;
                  fall_of_wickets;
                  */
                total_runs_scored_by_team += (result - 48);

                
                if (strike_changed(result - 48) == true)
                {
                    // to check strike change then increment run and wickets stats for team and player
                    // to swap the batsmen
                    on_strike_batsman = on_strike_batsman + far_end_batsman;
                    far_end_batsman = on_strike_batsman - far_end_batsman;
                    on_strike_batsman = on_strike_batsman - far_end_batsman;
                }
            }
            if (i % 6 == 0)
            {
                over_played_by_team++;
                over_balls = 0;
                on_strike_batsman = on_strike_batsman + far_end_batsman;
                far_end_batsman = on_strike_batsman - far_end_batsman;
                on_strike_batsman = on_strike_batsman - far_end_batsman;
            }
            if (first_inning_finished && total_runs_scored_by_team > first_team_score)
            {
                return;
            }
            // to do 18 times loop if 3over match
            // at each ball update batsmen on strikes run and bowlers runs given also the TEAMS RUNS ,OVERS PLAYED,
            // if run scored is 1,3 strike changed else(0,4,6,2) strike unchanged
            // if wickets fall update bowlers wicket stats bring new batsmen on strike
        }

        first_inning_finished = 1;
        first_team_score = total_runs_scored_by_team;
    }

    void scoreBoard()
    {
        cout<<"Player name"<<"  Scored"<<"  4s"<<"   6s"<<"  Balls played"<<endl;
        for(int i = 0; i < 5; i++)
        {
            cout<<p[i].name_of_player<<"    "<<p[i].no_of_runs_scored<<"        "
            <<p[i].no_of_fours_scored<<"    "<<p[i].no_of_sixes_scored<<"   "<<
            p[i].no_of_balls_played<<endl;
        }
    }

    void totalScore()
    {
        cout<<"Total:"<<total_runs_scored_by_team<<"/"<<fall_of_wickets<<endl;
        cout<<"Overs:"<<over_played_by_team<<"."<<over_balls<<endl;
    }
};

int main()
{
    Team t[2];
    int over;
    
    cout << "Enter the team format(Number of over the game should be played)\t:";
    cin >> over;
    t[0].setTeamname();
    t[1].setTeamname();
    cout << "please!Enter the playing 5 for team:" << t[0].teamName << endl;
    for (int i = 0; i < 5; i++)
    {
        cin >> t[0].p[i].name_of_player;
    }
    cout << "Please!Enter the playing 5 for team:" << t[1].teamName << endl;
    for (int i = 0; i < 5; i++)
    {
        cin >> t[1].p[i].name_of_player;
    }

    t[0].inningsStarted(over);

    t[0].scoreBoard();
    t[0].totalScore();

    // else
    // {
    //     innings_1_batting_team = toss_lost_by_team;
    //     t0.inningsStarted(&t[toss_lost_by_team], &t[toss_won_by_team], over);
    // }
    // Innings 1 stores the 0 or 1 which mean we can get the no. of runs scored in innings 1
    cout << "Total runs required to win the match \t:" << t[0].total_runs_scored_by_team + 1 << endl;

    t[1].inningsStarted(over);

    t[1].scoreBoard();
    t[1].totalScore();

    if(t[1].total_runs_scored_by_team > t[0].total_runs_scored_by_team)
    {
        cout<<t[1].teamName<<" won the match by "<<5-t[1].fall_of_wickets<<" wickets"<<endl;
    }
    else if(t[0].total_runs_scored_by_team > t[1].total_runs_scored_by_team)
    {
        cout<<t[0].teamName<<" won the match by "<<t[0].total_runs_scored_by_team-t[1].total_runs_scored_by_team<<" runs"<<endl;
    }
    else if(t[0].total_runs_scored_by_team == t[1].total_runs_scored_by_team)
    {
        cout<<"Score level and match tied"<<endl;
    }


    return 0;
}