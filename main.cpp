#include<iostream>
using namespace std;
#include "service.h"
void menu(){
    string choice;
    do{
    cout<<"\n\n\t =======================================================================================";
    cout<<"\n\n\t  *  HELP MENU                                                                         *";
    cout<<"\n\n\t =======================================================================================";
    cout<<"\n\n\t   add <Location>                             : Add a new Location";
    cout<<"\n\t   delete <Location>                          : Delete an existing Location";
    cout<<"\n\t   record <Location> <disease> <case>         : Record a disease and its case";
    cout<<"\n\t   list locations                             :List existing location ";
    cout<<"\n\t   list diseases                              :List all existing diseses in locations ";
    cout<<"\n\t   where <disease>                            :Find where disease exists ";
    cout<<"\n\t   case <Location> <disease>                  :Find cases of a disease in a location ";
    cout<<"\n\t   cases <disease>                            :Find total cases of a given disease ";
    cout<<"\n\t   help                                       :Prints user manual ";
    cout<<"\n\t   exit                                       :Exit the program ";
    cout<<"\n\n\t ======================================================================================="<<endl;

    cout<<"\n\n\t  . Type Your Command"<<endl;

    getline(cin, choice);
    if(choice == "add"){
        string locationName;
        cin>>locationName;
        saveLocation(locationName);
    }else if(choice == "list locations"){
        listLocationsAlphabetically();
    }else if(choice =="record"){
        string diseaseName, locationName;
        int cases;
        cin>>locationName>>diseaseName>>cases;
        saveDisease(locationName, diseaseName,cases);
    }
    else if(choice =="list diseases"){
        listDiseasesAlphabetically();
    }
    else if(choice =="where"){
        string disease;
        cin>>disease;
        getLocationByDiseaseName(disease);
        if(!getLocationByDiseaseName(disease)){
            cout<<"\n\t No location with this disease!"<<endl;
        }
        
    }
     else if(choice =="case"){
        string location;
        string disease;
        cin>>location>>disease;
        getCasesReport(location, disease);
    
    }
    else if(choice =="cases"){
        string disease;
        cin>>disease;
        totalCasesOfDisease(disease);
        if(!totalCasesOfDisease( disease)){
            cout<<"\n\t No cases of "<< disease <<" Found in " <<endl;

        }
        
    }
    else if(choice=="delete"){
         string location;
         cin>>location;
         deleteLocation(location);
    }
    else if(choice=="help"){
        menu();
    }
    else if(choice=="exit"){
        return;
    }
    else{
        cout<<"\n\n\n INVALID COMMAND"<<endl;
    }
    }while (choice!="exit");
    


}
void intro(){
    string helpCommand;
    cout<<"\n\n\t =======================================================================";
    cout<<"\n\t  * Welcome to Disease cases Reporting System! ";
    cout<<"\n\t  *  \t\t\t                                               *";
    cout<<"\n\t  * It is developed  by Best Verie as practical * ";
    cout<<"\n\t  *  \t\t\t                                               *";
    cout<<"\n\t  * Evaluation for the end year 3 ";
    cout<<"\n\n\t =======================================================================";
    cout<<"\n\t  * Starting time: Thu Apr 5 CAT 2022 * ";
    cout<<"\n\t  * Need a help? Type help then press enter * "<<endl;
    getline(cin, helpCommand);
    if(helpCommand == "help"){
        menu();
    }



}
int main(){
    intro();
 return 0;
}