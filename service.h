#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<sstream>
#include <cmath>

using namespace std;

class Location{
    public:
    int locationId;
    string locationName;
    Location(){}

};


class Disease{
    public:
    int diseaseId;
    string locationName;
    string diseaseName;
    int cases;
};



bool is_empty_file(std::ifstream &lFile)
{
    return lFile.peek() == std::ifstream::traits_type::eof();
}

vector<Location> getAllLocations()
{
    ifstream file("locations.txt", ios::in);
    vector<Location> Locations;
    string line;
    while (getline(file, line))
    {
        stringstream stringstream1(line);
        vector<string> fields;
        string field;
        while (getline(stringstream1, field, ' '))
        {
            fields.push_back(field);
        }

        Location location;
        location.locationId= stoi(fields[0]);
        location.locationName= fields[1];
        Locations.push_back(location);
    }

    file.close();
    return Locations;
}

int getCurrentId()
{
    vector<Location> locations = getAllLocations();
    return locations.back().locationId;
}

bool locationExistsbyName(string locName){
    vector <Location> locations = getAllLocations();
    for(int i=0; i<locations.size(); i++){
        if(locations[i].locationName == locName){
            return true;
        }
    }
    return false;
}


void saveLocation(string locationName){
  if(locationExistsbyName(locationName)){
    cout<<"\n\t LOCATION already registered!"<<endl;
    return;
  }
  Location location;
  ofstream locationFile("locations.txt", ios::out | ios::app);

  location.locationId = getCurrentId()+1;
  location.locationName = locationName;
   
  locationFile<<location.locationId<<" "<<location.locationName<<" "<<endl;
  
  locationFile.close();

  cout<<"\n\n\t location " <<location.locationName<<" is successfully added!";

}


vector<Disease> getAllDiseases()
{
    ifstream file("diseases.txt", ios::in);
    vector<Disease> Diseases;
    string line;
    while (getline(file, line))
    {
        stringstream stringstream1(line);
        vector<string> fields;
        string field;
        while (getline(stringstream1, field, ' '))
        {
            fields.push_back(field);
        }

        Disease disease;
        disease.diseaseId= stoi(fields[0]);
        disease.locationName= fields[1];
        disease.diseaseName= fields[2];
        disease.cases=stoi(fields[3]);
        Diseases.push_back(disease);
    }

    file.close();
    return Diseases;
}


int getCurrentDiseaseId()
{
    vector<Disease> diseases = getAllDiseases();
    return diseases.back().diseaseId;
}


bool diseaseExistsbyName(string disName){
    vector <Disease> diseases = getAllDiseases();
    for(int i=0; i<diseases.size(); i++){
        if(diseases[i].diseaseName == disName){
            return true;
        }
    }
    return false;
}

void updateDiseasesFile(vector<Disease> Diseases)
{

    ofstream temp_file("temp.txt", ios::out | ios::app);
    for (int i = 0; i < Diseases.size(); i++)
    {
        Disease disease = Diseases[i];
        cout<<"diseses in temp: "<<disease.cases<<endl;
        temp_file << disease.diseaseId<<" "<<disease.locationName<<" "<<disease.diseaseName<<" "<<disease.cases<<" "<<endl;
    }
    remove("diseases.txt");
    rename("temp.txt", "diseases.txt");
    temp_file.close();

}


bool locationAndDiseaseNameAlreadyExists(string location, string disease){
     vector <Disease> diseases = getAllDiseases();
    for(int i=0; i<diseases.size(); i++){
        if(diseases[i].locationName == location && diseases[i].diseaseName == disease){
            return true;
        }
    }
    return false;
}


void updateDisease(string location, string diseaseName, int myCases){
     vector<Disease> Diseases = getAllDiseases();
     int newCases;
    for (int i = 0; i < Diseases.size(); i++)
    {
        if (Diseases[i].locationName == location && Diseases[i].diseaseName == diseaseName)
        {
            Diseases[i].cases += myCases;
        }
    }


    updateDiseasesFile(Diseases);
}


void saveDisease(string locationName, string diseaseName, int cases){
  Disease disease;
  ofstream diseaseFile("diseases.txt", ios::out | ios::app);
  

  if(!locationExistsbyName(locationName)){
        cout<<"\n\t LOCATION not registered!"<<endl;
        return;
  }
  else if(locationAndDiseaseNameAlreadyExists(locationName, diseaseName)){
    updateDisease(locationName, diseaseName,cases);    
  }
  
  else{
  disease.diseaseId = getCurrentDiseaseId()+1;
  disease.locationName = locationName;
  disease.diseaseName = diseaseName;
  disease.cases = cases;

    diseaseFile<<disease.diseaseId<<" "<<disease.locationName<<" "<<disease.diseaseName<<" "<<disease.cases<<" "<<endl;
  
  diseaseFile.close();
  
  }
}


bool getLocationByDiseaseName(string diseaseName){
    vector<Disease> diseases = getAllDiseases();
    for (int i = 0; i < diseases.size(); i++)
    {
        if(diseases[i].diseaseName == diseaseName){
            cout<<"\n\t ["<<diseases[i].locationName<<"]"<<endl;
        }
        return true;
    }
    return false;
}

bool getCasesReport(string locationName, string diseaseName){
vector<Disease> diseases = getAllDiseases();
    for (int i = 0; i < diseases.size(); i++)
    {
        if(diseases[i].locationName == locationName && diseases[i].diseaseName ==diseaseName){
            cout<<"\n\t cases of " <<diseases[i].diseaseName<<" at "<<diseases[i].locationName<<" are: "<<diseases[i].cases<<endl;
        }
        return true;
    }
    return false;
}


bool totalCasesOfDisease(string disease){
    vector<Disease> diseases = getAllDiseases();
    int totalCases =0;
    for (int i = 0; i < diseases.size(); i++)
    {
        if(diseases[i].diseaseName == disease){
            totalCases += diseases[i].cases; 
            cout<<"\n\t Total cases of " <<diseases[i].diseaseName<<" is: "<<totalCases<<endl;
        }
        return true;
    }
    return false;
}






void updateLocationFile(vector<Location> Locations, string locName)
{
    ofstream temp_file("temp.txt", ios::out | ios::app);
    for (int i = 0; i < Locations.size(); i++)
    {
        Location location = Locations[i];
        temp_file << location.locationId << " " << location.locationName << endl;
    }
    temp_file.close();
    remove("locations.txt");
    rename("temp.txt", "locations.txt");


    vector<Disease> Diseases = getAllDiseases();
    for (int i = 0; i < Diseases.size(); i++)
    {
        Disease diseases = Diseases[i];
        if (diseases.locationName == locName)
        {
            Diseases.erase(Diseases.begin() + i);
        }
    }

    updateDiseasesFile(Diseases);

}

void deleteLocation(string locationName)
{
    vector<Location> Locations = getAllLocations();
    for (int i = 0; i < Locations.size(); i++)
    {
        Location locations = Locations[i];
        if (locations.locationName == locationName)
        {
            Locations.erase(Locations.begin() + i);
        }
    }
    updateLocationFile(Locations, locationName);
}


void listDiseases(vector<Disease> diseases)
{
    for (int i = 0; i < diseases.size(); i++)
    {
        cout<<"\n\t "<<diseases[i].diseaseName<<endl;
    }
}



void listDiseasesAlphabetically()
{
    vector<Disease> diseases = getAllDiseases();

    for (int i = 0; i < (diseases.size()); i++)
    {

        int swapped = 0;

        for (int j = 0; j < (diseases.size()); j++)
        {

            if (diseases[j].diseaseName <= diseases[j + 1].diseaseName)
            {

                Disease temp = diseases[j];
                diseases[j] = diseases[j+1];
                diseases[j+1] = temp;

                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }

    listDiseases(diseases);
}


void listAllLocations(vector<Location> locations){
    for(int i=0; i<locations.size(); i++){
        cout<<"\n\t "<<locations[i].locationName<<endl;
    }
}




void listLocationsAlphabetically()
{
    vector<Location> locations = getAllLocations();

    for (int i = 0; i < (locations.size()); i++)
    {

        int swapped = 0;

        for (int j = 0; j < (locations.size()); j++)
        {

            if (locations[j].locationName <= locations[j + 1].locationName)
            {

                Location temp = locations[j];
                locations[j] = locations[j+1];
                locations[j+1] = temp;

                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }

    listAllLocations(locations);
}
