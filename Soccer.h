#ifndef SOCCER_H
#define SOCCER_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <ctime>
#include <cmath>
using namespace std;



class Soccer {
    private:

    struct Player {
        string name;
        int overall;
        string position;
    };

    struct Team {
        string teamName;
        vector<Player> playerList;
    };

    vector<Team> teamList;

    int totalPeople;

    Team locateTeam(string country) {
        size_t index = 0;
        while (teamList[index].teamName != country) {
            index++;
        }
        return teamList[index];
    }

    bool shotAttempt(int attacker, int defender) {
        random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, 999);
        int randomInt = distribution(gen);

        // To level the field for non goalie specialized teams

        double probability = 10*(50 - ((defender*1.0)/1.2 - (attacker*1.0)/1.2) * 1.5*sqrt(abs(attacker - defender)));
        // cout << "PROBABILITY: " << probability << endl;
        if (probability)

        if (randomInt > probability) {
            return false;
        }
        return true;
        // Thought process
        // Good keeper will stop bad shooter with fairly high accuracy Lets say 90 keeper, 70 striker, should be 95 percent save
        // Good striker will score on bad keeper with fairly high accuracy. Lets say 90 striker, 70 keeper, should be 95 percent score.
        // As the overalls get closer the probability should shift greatly, the difference in probability from 70-71 should be
        // far less than the difference between 89-90, however the 89-90 difference should also be minimal.
        // An idea is to say sqrt(abs(a - d)), this penalizes smaller differences more, than larger ones.
        // As larger values square root doesn't change by as much
    }

    bool shotAttempt(Player attacker, Player defender, bool print) {
        int attackStat = attacker.overall;
        int defenseStat = defender.overall;
        if (print) {
            cout << attacker.name << " shoots ";
        }
        
        bool temp = shotAttempt(attackStat, defenseStat);
        if (print) {
            if (temp) {
                cout << "and SCORES" << endl;
                return temp;
            } else {
                cout << "and MISSES" << endl;
                return temp;
            }
        }

    }

    public:

    Soccer(); //default constructor
    Soccer(string filename); // default constructor
    void readfile(string filename);
    void printAll();
    void printTeam(string teamName);
    int testMatch(int attack, int defense, int iterations);
    Team runMatch(string country1, string country2);
    Team runMatchNoPrint(string country1, string country2);
    void matchupTest(string country1, string country2);
    


};
#endif