#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

map<string, int>score_list;
vector<pair<pair<string, string>, string>>QList;
string s;
int c;

void GetQuestionList(string n)
{
    string q, ansrs, ans;
    c=0;s="";
    ifstream myfile;

    if(n=="1")
        myfile.open("Sports.txt");
    else if(n=="2")
        myfile.open("Biology.txt");
    else if(n=="3")
        myfile.open("History.txt");
    else if(n=="4")
        myfile.open("Mental Abilities.txt");
    else if(n=="5")
        myfile.open("Arts.txt");


    if(myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline(myfile, s);
            if(c==0)q=s;
            else if(c==1)ansrs=s;
            else
            {
                ans=s;
                QList.push_back({{q, ansrs}, ans});
                c=-1;
            }
            c++;
        }
        myfile.close();
    }
}

void TakingScoreList()
{
    c=0;s="";
    string user;
    int HighScore;
    ifstream myfile("ScoreList.txt");
    if(myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline(myfile, s);
            if(c==0)
                user=s;
            else
            {
                HighScore=0;
                for(unsigned int i=0;i<s.size();i++)
                    HighScore = HighScore*10+(s[i]-'0');
                score_list[user]=HighScore;

                c=-1;
            }
            c++;
        }
        myfile.close();
    }
}

void FillingScoreList()
{
    ofstream myfile("ScoreList.txt");
    if(myfile.is_open())
    {
        for(auto it=score_list.rbegin();it!=score_list.rend();it++)
            myfile << it->first<<endl<<it->second<<endl;


        myfile.close();
    }
}

void round(bool AskedQ[30], int &current_score)
{
    int r;string user_input;
    for(unsigned int QNum=1;QNum<=6;QNum++)
    {
        r = rand()%QList.size();
        while(AskedQ[r])
            r = rand()%QList.size();
        AskedQ[r]=1;

        cout<<"Q"<<QNum<<": "<<QList[r].first.first<<endl<<QList[r].first.second<<endl;
        cin>>user_input;
        while(user_input.size()>1 || (user_input>"4" || user_input<"1"))
        {
            cout<<"Entered number is not valid please enter a valid number"<<endl;
            cin>>user_input;
        }


        if(user_input!=QList[r].second)
        {
            cout<<"Wrong Answer"<<endl;
            break;
        }
        else
        {
            cout<<"Good Job"<<endl;
            current_score++;
        }
    }
}



int main()
{
    TakingScoreList();

    string username, user_input;int  current_score=0;
    cout<<"Enter user name: "<<flush;
    cin>>username;
    cout<<endl<<username<<"'s highest score is: "<<score_list[username]<<"\nReady To Break It?!"<<endl<<endl;


    cout<<"Choose QuIzGaMe field:"<<endl<<"1-SPORTS \n2-BIOLOGY \n3-HISTORY \n4-Mental Abilities \n5-Arts"<<endl;
    cin>>user_input;
    while(user_input.size()>1 || (user_input>"5" || user_input<"1"))
    {
        cout<<"Entered number is not valid please enter a valid number"<<endl;
        cin>>user_input;
    }


    GetQuestionList(user_input);
    bool AskedQ[30]={};
    round(AskedQ, current_score);


    if(current_score==6)
    {
        cout<<"Well done!!! You passed the first round"<<endl;
        cout<<"Do you want to move to the final round?"<<endl<<"1-)YES 2-)any other number than 1 will be considered no"<<endl;
        cin>>user_input;
        if(user_input=="1")
        {
            QList.clear();
            cout<<"Choose QuIzGaMe field for this round:"<<endl<<"1-SPORTS \n2-BIOLOGY \n3-HISTORY \n4-Math \n5-Geography"<<endl;
            cin>>user_input;
            while( user_input.size()>1 ||  (user_input>"5" || user_input<"1"))
            {
                cout<<"Entered number is not valid please enter a valid number"<<endl;
                cin>>user_input;
            }
            GetQuestionList(user_input);

            cout<<"Let's GOOO"<<endl;
            round(AskedQ, current_score);
        }
    }

    cout<<"Your score: "<<current_score<<endl;
    if(current_score>score_list[username])
        score_list[username]=current_score;
    if(current_score==12)
        cout<<"CONGRATULATIONS!!! YOU WON"<<endl;
    else
        cout<<"Your highest score: "<<score_list[username]<<endl;


    FillingScoreList();

//*/
    return 0;
}
