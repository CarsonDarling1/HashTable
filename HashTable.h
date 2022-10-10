#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

using namespace std;


struct Project
{
    int cost;
    string projectName;
    string projectRegion;
    Project* nextProject;
    Project* head;
    Project(string newProjectName, string newProjectRegion, int newCost);
    Project();
};

struct HashTable
{
    int arrSize;
    int arrFilled;
    int currentSize;
    Project** projectList;
    HashTable();
    void create(int n);
    void hash_display();
    void hash_insert(string newProjectname, string newProjectRegion, int newCost);
    void hash_search(string projectName);
    void hash_delete(string projectName);
    void max_cost();
};



#endif // HASHTABLE_H_INCLUDED
