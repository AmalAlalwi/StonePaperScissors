#include <iostream>
#include<string>
#include<cstdlib>
using namespace std;
enum enTypePlay { Stone = 1, Paper = 2, Scissors = 3 };
enum enTheWinner { Player1 = 1, Computer = 2, Equals = 3 };

int RandomNum(int From, int To) {
    int random = rand() % (To - From + 1) + From;
    return random;
}
struct  stFinalResults
{
    short GameRounds;
    int UserGoals = 0;
    int ComputerGoals = 0;
    int EqualGoals = 0;
    enTheWinner WinnerGame;
    string WinnerName;

};
struct stRoundInfo {
    short RoundNumber;
    enTypePlay Choiceplayer1;
    enTypePlay ChoiceComputer;
    enTheWinner WinnerRound;
    string WinnerName;
};
string ReadText() {
    string Text;
    cout << "Enter Your Text Please:??" << endl;
    getline(cin, Text);
    return Text;
}
string Tabs(int num) {
    string Tab = "";
    while (num--) { Tab += "\t"; }return Tab;
}
enTheWinner TheWinner(int GoalsPlay1, int GoalsComputer) {
    if (GoalsPlay1 > GoalsComputer)return enTheWinner::Player1;
    else if (GoalsPlay1 < GoalsComputer)return enTheWinner::Computer;
    else return enTheWinner::Equals;
}
string WinnerName(enTheWinner Winner) {
    string arrWinner[3] = { "Player 1","Computer","No Winner" };
    return arrWinner[Winner - 1];
}
string ChoiceName(enTypePlay Choice) {
    string arrChoiceName[3] = { "Stone","Paper","Scissors" };
    return arrChoiceName[Choice - 1];
}
int ReadPositiveNumber(string Message) {
    int Num = -1;
    while (Num < 0) {
        cout << Message << endl;
        cin >> Num;
    }
    return Num;
}
int RandomNum(int From, int To);
enTypePlay ReadWhatYouWantToPlay() {
    int Choice;
    cout << "Your Choice: [1] Stone,[2]Paper,[3] Scissors ";
    cin >> Choice;
    return (enTypePlay)Choice;
}
short ReadHowManyRounds() {

    short Num = 0;
    cout << "Enter How Many Rounds You Want Play? From 1 to 10" << endl;
    cin >> Num;
    while (Num < 1 || Num>10) {
        cout << "Enter How Many Rounds You Want Play? From 1 to 10" << endl;
        cin >> Num;
    }
    return Num;
}
enTheWinner WinnerRound(stRoundInfo RoundInfo) {

    if (RoundInfo.Choiceplayer1 == RoundInfo.ChoiceComputer)
    {
        return enTheWinner::Equals;
    }
    switch (RoundInfo.Choiceplayer1)
    {
    case enTypePlay::Stone: {
        if (RoundInfo.ChoiceComputer == enTypePlay::Scissors)
            return enTheWinner::Player1;
        break;
    }
    case enTypePlay::Paper: {
        if (RoundInfo.ChoiceComputer == enTypePlay::Stone)
            return enTheWinner::Player1;
        break;
    }
    case enTypePlay::Scissors: {
        if (RoundInfo.ChoiceComputer == enTypePlay::Paper)
            return enTheWinner::Player1;
        break;
    }
    }
    return enTheWinner::Computer;

}
void ResetToConsel() {
    system("cls");
    system("color 0F");
}
void ShowGameOverSecreen() {
    cout << "\t\t\t" << "_________________________________________________" << endl;
    cout << "\t\t\t\t" << "+++ G A M E   O V E R +++" << endl;
}
stFinalResults FillGameResults(short NumRound, short PlayerTimes, short ComputerTimes, short Draw) {
    stFinalResults ListOfREsult;
    ListOfREsult.GameRounds = NumRound;
    ListOfREsult.ComputerGoals = ComputerTimes;
    ListOfREsult.UserGoals = PlayerTimes;
    ListOfREsult.EqualGoals = Draw;
    ListOfREsult.WinnerGame = TheWinner(PlayerTimes, ComputerTimes);
    ListOfREsult.WinnerName = WinnerName(ListOfREsult.WinnerGame);
    return ListOfREsult;
}
void SetColorSecreen(enTheWinner Winner) {
    switch (Winner)
    {
    case Player1: {
        system("color 2F");
        break;
    }
    case Computer: {
        system("color 4F");
        break;
    }
    case Equals: {
        system("color 6F");
    }
    }
}

void PrintFinalResult(stFinalResults Results) {

    cout << Tabs(3) << "__________________[Game Result:]_________________" << endl;
    cout << Tabs(3) << "Game Rounds\t: " << Results.GameRounds << endl;
    cout << Tabs(3) << "Player 1 win times: " << Results.UserGoals << endl;
    cout << Tabs(3) << "Computer Win times: " << Results.ComputerGoals << endl;
    cout << Tabs(3) << "Equals times: " << Results.EqualGoals << endl;
    cout << Tabs(3) << "The Winner\t: " << Results.WinnerName << endl;
    SetColorSecreen(Results.WinnerGame);
}
void PrintRoundResult(stRoundInfo ResultRound) {
    cout << "Player 1 Choice: " << ChoiceName(ResultRound.Choiceplayer1) << endl;
    cout << "Computer Choice: " << ChoiceName(ResultRound.ChoiceComputer) << endl;
    cout << "Round Winnrer :" << ResultRound.WinnerName << endl;
    cout << "-----------------------------------------------------------------------"<<endl;
    SetColorSecreen(ResultRound.WinnerRound);

}
stFinalResults PlayGame(short Num) {
    stRoundInfo RoundInfo;
    short playerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
    for (int i = 1; i <= Num; i++) {
        cout << "-----------------Round " << i << " ------------------" << endl;
        RoundInfo.RoundNumber = i;
        RoundInfo.Choiceplayer1 = ReadWhatYouWantToPlay();
        RoundInfo.ChoiceComputer = (enTypePlay)RandomNum(1, 3);
        RoundInfo.WinnerRound = WinnerRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.WinnerRound);

        if (RoundInfo.WinnerRound == enTheWinner::Player1)playerWinTimes++;
        else if (RoundInfo.WinnerRound == enTheWinner::Computer)ComputerWinTimes++;
        else DrawTimes++;

        PrintRoundResult(RoundInfo);
    }
    return FillGameResults(Num, playerWinTimes, ComputerWinTimes, DrawTimes);
}
void StartPlay() {
    bool ContinuePlay = 1;
    do {
        ResetToConsel();
        stFinalResults ListOfResult = PlayGame(ReadHowManyRounds());
        ShowGameOverSecreen();
        PrintFinalResult(ListOfResult);
        cout << Tabs(3) << "Do you want play again: [0] No,[1] Yes";
        cin >> ContinuePlay;
    } while (ContinuePlay);
}


int main()
{
    srand((unsigned)time(NULL));

    StartPlay();





}
