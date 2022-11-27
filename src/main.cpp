#include <iostream>
#include <vector> 
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "dikstra.h"
#include "glfw3.h"


const int ROWSIZE = 15;


void loadData(std::vector<std::string> &loadMapData);

struct mapData
{
    std::string name;
    int vertex;
    std::vector<int> nodes;
    std::vector<double> weights;
};

void loadData(std::vector<std::string> &loadMapData)
{
    std::ifstream file;
    std::string line;
    std::string temp;
    std::string word;
    file.open("../data/Final_4_data.csv");

    while (std::getline(file, line))
    {

        std::stringstream s(line);

        while(getline(s, word, ','))
        {
            loadMapData.push_back(word);
        }
    }

    file.close();
}

void parseData(std::vector<std::string> loadMapData, std::map<int, mapData> &anchorageMapData )
{
    mapData temp;
    int currKey = -1;
    for (int i = 0; i < loadMapData.size(); ++i)
    {
        if(i % ROWSIZE == 0)
        {
            ++currKey;
        }
        else if(i % ROWSIZE == 1)
        {
            temp.name = loadMapData.at(i);
        }
        else if(i % ROWSIZE == 2)
        {

            int x = std::stoi(loadMapData.at(i));
            temp.vertex = x;
        }
        else if(i % 2 == 1)
        {
           
            int x = std::stoi(loadMapData.at(i));
            temp.nodes.push_back(x);


        }
        else
        {

            double x = std::stod(loadMapData.at(i));
            temp.weights.push_back(x);

        }

        if(i % ROWSIZE == 14)
        {
            anchorageMapData[currKey] = temp;
            temp.nodes.clear();
            temp.weights.clear();
        }
    }


}





int main()
{
//loads the data into a vector line by line
std::vector<std::string> loadMapData;
loadData(loadMapData);

//parses the data into useable chunks to be used to create nodes
std::map<int, mapData> anchorageMapData;


//std::cout << "parsed data" <<std::endl;
parseData(loadMapData,anchorageMapData);

std::cout << anchorageMapData[14].name << std::endl;
}
