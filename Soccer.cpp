#include "Soccer.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
using namespace std;

Soccer::Soccer() {
    bool yes = true;
}

Soccer::Soccer(string filename) {
    readfile(filename);

    int item;


    do {
        cout << "Choose your gamemode" << endl << endl;
        cout << "0. Team Output" << endl;
        cout << "1. One game simulation" << endl;
        cout << "2. Win Prediction calulator" << endl;
        cout << "3. Type 9 to quit, or 3 to clear the terminal" << endl;

        cin >> item;

        string team1;
        string team2;

        cout << "Team one name: ";  
        cin >> team1;
        cout << "Team two name: ";
        cin >> team2;

        switch(item) {
            case 0: 
                printTeam(team1);
                printTeam(team2);
                break;
            
            case 1:
                runMatch(team1, team2);
                break;

            case 2:
                matchupTest(team1, team2);
                break;


        }
    } while (item != 9);





}
void Soccer::readfile(string filename) {
    std::ifstream file;
    file.open(filename);
    string line;
    while (getline(file, line)) {
        std::istringstream stream = istringstream(line);
        getline(stream, line, ',');
        string team = line;
        Team add;
        add.teamName = line;
        Player fs;
        getline(stream, line, ',');
        fs.name = line;
        getline(stream, line, ',');
        fs.overall = stoi(line);
        fs.position = "Striker";
        add.playerList.push_back(fs);

        Player ss;
        getline(stream, line, ',');
        ss.name = line;
        getline(stream, line, ',');
        ss.overall = stoi(line);
        ss.position = "Striker";
        add.playerList.push_back(ss);

        Player ts;
        getline(stream, line, ',');
        ts.name = line;
        getline(stream, line, ',');
        ts.overall = stoi(line);
        ts.position = "Striker";
        add.playerList.push_back(ts);

        Player gk;
        getline(stream, line, ',');
        gk.name = line;
        getline(stream, line, ',');
        gk.overall = stoi(line);
        gk.position = "Goal Keeper";
        add.playerList.push_back(gk);

        teamList.push_back(add);
    }
}

void Soccer::printAll() {
    for (auto it : teamList) {
        cout << it.teamName << endl;
        for (auto ite : it.playerList) {
            cout << setw(20) << ite.name << setw(5) << ite.overall << setw(25) << ite.position << endl;
        }
        cout << endl;
    }
}

void Soccer::printTeam(string teamName) {
    Team current = locateTeam(teamName);
    cout << current.teamName << endl;
    for (auto ite : current.playerList) {
        cout << setw(20) << ite.name << setw(5) << ite.overall << setw(25) << ite.position << endl;
    }
    cout << endl;
    
}

int Soccer::testMatch(int attack, int defense, int iterations) {
    int scoreCount = 0;
    int missCount = 0;
    for (int i = 0; i < iterations; i++) {
        bool j = shotAttempt(attack, defense);
        if (j) {
            scoreCount++;
        } else {
            missCount++;
        }
    }
    // cout << (scoreCount*1.0)/(scoreCount + missCount) << endl;
    return scoreCount;

}

Soccer::Team Soccer::runMatch(string country1, string country2) {
    Team team1 = locateTeam(country1);
    Team team2 = locateTeam(country2);

    Player team1Keep = team1.playerList[3];
    Player team2Keep = team2.playerList[3];

    int score_1 = 0;
    int score_2 = 0;

    for (int j = 0; j < 5; ++j) {
        int i = j%3;
        score_1 += shotAttempt(team1.playerList[i], team2Keep, true);
        score_2 += shotAttempt(team2.playerList[i], team1Keep, true);

        cout << "SCORE: " << endl;
        cout << team1.teamName << ": " << score_1 << "  " << score_2 << " :" << team2.teamName << endl;

    }
    if (score_1 > score_2) {
        cout << country1 << " WINS" << endl;
        return team1;
    } else if (score_2 > score_1) {
        cout << country2 << " WINS" << endl;
        return team2;
    }
    Team null;
    null.teamName = "null";
    cout << "TIED" <<endl;
    return null;
}

Soccer::Team Soccer::runMatchNoPrint(string country1, string country2) {
    Team team1 = locateTeam(country1);
    Team team2 = locateTeam(country2);

    Player team1Keep = team1.playerList[3];
    Player team2Keep = team2.playerList[3];

    int score_1 = 0;
    int score_2 = 0;

    for (int j = 0; j < 5; ++j) {
        int i = j%3;
        score_1 += shotAttempt(team1.playerList[i], team2Keep, false);
        score_2 += shotAttempt(team2.playerList[i], team1Keep, false);

    }

    if (score_1 > score_2) {
        return team1;
    } else if (score_2 > score_1) {
        return team2;
    }

    Team null;
    null.teamName = "null";
    return null;
}

void Soccer::matchupTest(string country1, string country2) {
    int iteration = 10000;
    int team1Count = 0;
    int team2Count = 0;
    int tieCount = 0;
    for (int i = 0; i < iteration; i++) {
        Soccer::Team newa = runMatchNoPrint(country1, country2);
        if (newa.teamName == country1) {
            team1Count++;
        } else if (newa.teamName == country2) {
            team2Count++;
        } else {
            tieCount++;
        }
        
    }

    

    float progress = 0.0;
    cout << team1Count << " " << tieCount << " " << team2Count << endl;
    while (progress < 1.0) {
        int barWidth = 70;

        std::cout << int((team1Count * 100.0)/iteration) << "% [";
        int pos = int(barWidth*(team1Count *1.0)/iteration);
        int pos2 = int(barWidth*((team1Count + tieCount)*1.0)/iteration);
        for (int i = 0; i < barWidth; ++i) {
            system("Color 0C");
            if (i < pos) std::cout << "=";
            else if (i < pos2) std::cout << '/';
            else std::cout << ";";
        }
        std::cout << "] " << int((team2Count * 100.0)/iteration) << " %\r";
        std::cout.flush();

        progress += 0.16; // for demonstration only
    }
    std::cout << std::endl;
}