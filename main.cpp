#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void readData(const string &, vector<double> &, vector<double> &);
double interpolation(double, const vector<double> &, const vector<double> &);
bool isOrdered(const vector<double> &);
void reorder(vector<double> &, vector<double> &);

int main(int argc, char* argv[])
{
    string fileName;

    #define CHECK_ARG

    #ifdef CHECK_ARG
      if (argc < 2) {
         cout << "Please enter a file on the command line" << endl; 
         return 1;
      }
      if (argc > 2) {
         cout << "Too many arguements! Only 1 file is expected" << endl;
         return 1;
      }
      fileName = argv[1];
   #endif
   #ifndef CHECK_ARG
      cin >> fileName; 
   #endif

    vector<double> fpAngles;
    vector<double> corCoe;

    int userVal = 0;

    string continu = "Yes";

    readData(fileName, fpAngles, corCoe);

    if(fpAngles.size() > 1)
    {

         reorder(fpAngles, corCoe);

    }
    else
    {

        return 1;

    }

    while(continu == "Yes")
    {

        cin >> userVal;

        cout << interpolation(userVal, fpAngles, corCoe);
        cin >> continu;

    }

    return 0;

}

void readData(const string& fileName, vector<double>& fpAngles, vector<double>& corCoe)
{

    ifstream inFS;

    double temp;

    inFS.open(fileName);

   if(!inFS.is_open())
   {

      cout << "Error opening " << fileName << endl;
      return;

   }

   while(inFS >> temp)
   {

        fpAngles.push_back(temp);

        inFS >> temp;
        corCoe.push_back(temp);

   }

    inFS.close();
}

bool isOrdered(const vector<double> &fpAngles)
{

    bool ans = true;

    for(unsigned int i = 0; i + 1 < fpAngles.size(); i++)
    {

        if(fpAngles.at(i) > fpAngles.at(i+1))
        {

            ans = false;

        }

    }

    return ans;

}

void reorder(vector<double>& fpAngles, vector<double>& corCoe)
{
    
    for(unsigned int i = 0; i < fpAngles.size(); i++)
    {
        int smIn = i; // Smallest index
        for(unsigned int j = i + 1; j < fpAngles.size(); j++)
        {
            if(fpAngles.at(j) < fpAngles.at(smIn))
            {
                smIn = j;
            }

        }
        double tempAngles = fpAngles.at(i);
        double tempCoe = corCoe.at(i);
        
        fpAngles.at(i) = fpAngles.at(smIn);
        corCoe.at(i) = corCoe.at(smIn);

        fpAngles.at(smIn) = tempAngles;
        corCoe.at(smIn) = tempCoe;

    }

}

double interpolation(double userVal, const vector<double>& fpAngles, const vector<double>& corCoe)
{

    double a;
    //  b = userVal;
    double c;

    double ans;

    for(unsigned int i = 1; i < fpAngles.size(); i++)
    {
        if(userVal == fpAngles.at(i))
        {

            ans = corCoe.at(i);

        }
        else if(userVal < fpAngles.at(i))
        {

            c = i;
            a = i - 1;

            i = fpAngles.size();

            ans = corCoe.at(a) + ((userVal - fpAngles.at(a)) / (fpAngles.at(c) - fpAngles.at(a)) * (corCoe.at(c) - corCoe.at(a)));
        }

    }

    return ans;

}