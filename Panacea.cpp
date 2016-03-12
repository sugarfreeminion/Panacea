/**************************************************************************
 * Author:          sugarfreeoh
 * Date:            10 March 2016
 * Description:     Each input line includes a test case with virus
 *                  components in hex and antivirus components in binary
 *                  Virus and antivirus are separated by a '|'.
 *                  Calculate the sum of all virus components and compare
 *                  it with the sum of the antivirus components. If the
 *                  numbers are the same or the sum of antivirus
 *                  components is greater than the sum of virus components
 *                  that means the virus was stopped.
 *************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <locale>
#include <math.h>

using namespace std;

int BaseConverter(const string baseValue, const int base);
int HexAlphaToDec(const string hexValue);

int main(int argc, char *argv[])
{
    ifstream inputFile;

    inputFile.open(argv[1]);

    if(inputFile.is_open())
    {
        string input;

        while(getline(inputFile,input))
        {
            size_t delLoc;
            string virus;
            string antiVirus;

            int virusValue = 0;
            int antiVirusValue = 0;

            delLoc = input.find('|');

            if(delLoc != string::npos)
            {
                virus = input.substr(0,delLoc-1);
                antiVirus = input.substr(delLoc+2,input.size()-delLoc-2);

                //cout << "Virus: " << virus << "." << endl;
                //cout << "AntiVirus: " << antiVirus << "." << endl;

                virusValue = BaseConverter(virus,16);
                antiVirusValue = BaseConverter(antiVirus,2);

                //cout << "Virus Sum: " << virusValue << endl;
                //cout << "AntiVirus Sum: " << antiVirusValue << endl;

                if(antiVirusValue >= virusValue)
                {
                    cout << "True" << endl;
                }
                else
                {
                    cout << "False" << endl;
                }
            }
        }

        inputFile.close();
    }
    else
    {
        cout << "Error opening input file" << endl;
    }

    return 0;
}

int BaseConverter(const string baseValue,const int base)
{
    stringstream ss;
    stringstream baseValueStream;

    string temp;

    int sum = 0;
    int value;

    baseValueStream << baseValue;

    while(getline(baseValueStream,temp,' '))
    {
        unsigned int index = 0;

        //cout << "    Converting: " << temp << "." << endl;

        while(index < temp.size())
        {
            ss.str("");
            ss.clear();
            //cout << "        Character: " << temp[index] << endl;

            if(isdigit(temp[index]))
            {
                //cout << "        Found a digit" << endl;
                ss << temp[index];
                ss >> value;
            }
            else
            {
                ss << temp[index];
                value = HexAlphaToDec(ss.str());
            }
        
            //cout << "        Digit: " << hex << endl;
            //cout << "        Power: " << temp.size()-index-1 << endl;
            sum = sum + (value * pow(base,temp.size()-index-1));
            //cout << "        Sum: " << sum << endl;

            ++index;
        }
    }    

    return sum;
}

int HexAlphaToDec(const string hexValue)
{
    int decValue = 0;

    if(strncmp(hexValue.c_str(),"a",1) == 0)
    {
        decValue = 10;
    }
    else if(strncmp(hexValue.c_str(),"b",1) == 0)
    {
        decValue = 11;
    }
    else if(strncmp(hexValue.c_str(),"c",1) == 0)
    {
        decValue = 12;
    }
    else if(strncmp(hexValue.c_str(),"d",1) == 0)
    {
        decValue = 13;
    }
    else if(strncmp(hexValue.c_str(),"e",1) == 0)
    {
        decValue = 14;
    }
    else if(strncmp(hexValue.c_str(),"f",1) == 0)
    {
        decValue = 15;
    }

    return decValue;
}
