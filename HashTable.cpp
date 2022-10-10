#include <iostream>
#include <list>
#include "HashTable.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    string theProjectName, theProjectRegion, line, newProj;
    int theProjectCost, theProjectSize, newProj2;
    int count = 1;
    HashTable theHash;
    ifstream readFile("sampleinput.txt");
    istringstream iss(line);
    getline(readFile, line);
    theProjectSize = stoi(line);
    theHash.create(theProjectSize);
    while(getline(readFile,line) && line != "EndOfInsertion")
    {
        stringstream iss(line);
        cout << line << endl;
        if(line != "EndOfInsertion")
        {
            getline(iss,theProjectName, ',');
            getline(iss,theProjectRegion,',');
            getline(iss,newProj, ',');
            theProjectCost = stoi(newProj);
            theHash.hash_insert(theProjectName,theProjectRegion, theProjectCost);
            count += 1;
        }
    }
    while(getline(readFile,line))
    {
        string command, projectName;
        stringstream iss(line);
        getline(iss, command, '/');
        getline(iss, projectName);
        if(command == "hash_display")
        {
            theHash.hash_display();
        }
        else if(command == "hash_search")
        {
            theHash.hash_search(projectName);
        }
        else if(command == "hash_delete")
        {
            theHash.hash_delete(projectName);
        }
        else if(command == "hash_max_cost")
        {
            theHash.max_cost();
        }
        else
            "Invalid ";
    }
    readFile.close();
    theHash.hash_display();
}

HashTable::HashTable()
{
    arrSize = 0;
    currentSize = 0;
    arrFilled = 0;
    projectList = new Project*();
}

Project::Project()
{
    cost = 0;
    projectName = "";
    projectRegion = "";
    nextProject = NULL;
}

Project::Project(string newProjectName, string newProjectRegion, int newCost)
{
    this->projectName = newProjectName;
    this->projectRegion = newProjectRegion;
    this->cost = newCost;
}

void HashTable::create(int n)
{
    arrSize = n;
    arrFilled = 0;
    for(int i = 0; i <= n; i++)
    {
        projectList[i] = NULL;
    }
}

void HashTable::hash_display()
{
    int counter;
    Project* currProject;
    for(int i = 0; i < arrSize; i++)
    {
        currProject = projectList[i];
        counter = 1;
        if(currProject == NULL)
        {
            cout << "The list is empty. " << "\n";
            cout << "\n";
        }
        else
        {
            while(currProject != NULL)
            {
                cout << "index : " << i << ", linked list size: ", cout << counter  << "\n";
                cout << "Project Name: " << currProject->projectName << "\n";
                cout << "Region: " << currProject->projectRegion << "\n";
                cout << "Cost: " << currProject->cost << "\n";
                cout << "\n";
                if(currProject != NULL)
                {
                    currProject = currProject->nextProject;
                    counter++;
                }
            }
        }
    }
}

void HashTable::hash_insert(string newProjectname, string newProjectRegion, int newCost)
{
    int key;
    bool projectAdded = false;
    if(newProjectname.length() > 2)
    {
        key = ((newProjectname.at(0)*(128^2) % this->arrSize) + (newProjectname.at(1)*(128) & this->arrSize) + newProjectname.at(2) % (this->arrSize)) % this->arrSize;
    }
    else if (newProjectname.length() == 2)
    {
        key = (newProjectname.at(0) * (37) + newProjectname.at(1) * (37) % this->arrSize);
    }
    else if(newProjectname.length() == 1)
    {
        key = (newProjectname.at(0) * (37) % this->arrSize);
    }
    else
    {
        cout << "Project name not entered. ";
    }
    currentSize += 1;
    Project* currProject = projectList[key];
    Project* prevProject = NULL;
    while(currProject != NULL)
    {
        prevProject = currProject;
        currProject = currProject->nextProject;
    }
    if(currProject == NULL)
    {
        currProject = new Project(newProjectname,newProjectRegion,newCost);
        if(prevProject == NULL)
        {
            projectList[key] = currProject;
            currProject->nextProject = NULL;
        }
        else
        {
            prevProject->nextProject = currProject;
            currProject->nextProject = NULL;
        }
    }
}

void HashTable::hash_search(string searchProjectName)
{
    Project *tempPointer;
    bool projectFound = false;
    for(int i = 0; i <= arrSize; i++)
    {
        tempPointer = projectList[i];
        while(tempPointer != NULL)
        {
            if(tempPointer->projectName == searchProjectName)
            {
                cout << "The Project: " << tempPointer->projectName << " with cost " << tempPointer->cost << " is found. " << "\n";
                projectFound = true;
            }
            tempPointer = tempPointer->nextProject;
        }
    }
    if(projectFound == false)
    {
        cout << "Project not found. " << "\n";
    }
}

void HashTable::hash_delete(string delProjectName)
{
    Project* currProject;
    Project* prevProject;
    bool projectFound = false;
    for(int i = 0; i <= arrSize; i++)
    {
        currProject = projectList[i];
        while(currProject != NULL)
        {
            if(currProject->projectName == delProjectName)
            {
                cout << "The Project: " << currProject->projectName << " with Cost " << currProject->cost << " is removed" << "\n";
                if(currProject->nextProject == NULL)
                {
                    prevProject->nextProject = NULL;
                    currProject = NULL;
                    projectFound = true;
                }
                else if(prevProject != NULL)
                {
                    prevProject->nextProject = currProject->nextProject;
                    projectList[i] = prevProject;
                    currProject->nextProject = NULL;
                    delete currProject;
                    projectFound = true;
                }
                else
                {
                    projectList[i] = currProject->nextProject;
                    currProject->nextProject = NULL;
                    currProject = NULL;
                    projectFound = true;
                }
            }
            else
            {
                prevProject = currProject;
                currProject = currProject->nextProject;
            }
        }
    }
    if(projectFound == false)
    {
        cout << "The Project: " << delProjectName << " was not found \n";
    }

}

void HashTable:: max_cost()
{
    Project* currPointer;
    int largest = 0;
    string largestName;
    if(currentSize == 0)
    {
        cout << "The list is empty " << endl;
    }
    for(int i = 0; i <= arrSize; i++)
    {
        currPointer = projectList[i];
        while(currPointer != NULL)
        {
            if(currPointer->cost > largest)
            {
                largest = currPointer->cost;
                largestName = currPointer->projectName;
            }
            currPointer = currPointer->nextProject;
        }
    }
    if(currentSize != 0)
    {
        cout << "The Project: " << largestName << " has the highest cost of " << largest << endl;
    }
}


