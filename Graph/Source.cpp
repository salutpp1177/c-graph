#include "Arc.h"
#include "Sommet.h"
#include "Graph.h"
#include "Exception.h"
#include "Parse.h"
#include "OperationForGraph.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>

#pragma once
using namespace std;

void ChoiceForExecution(int &i)
{
    cout <<"******************************************************************"<<endl;
    cout <<"*                PLEASE CHOOSE YOUR EXECUTION                    *"<<endl;
    cout <<"*                1 : Add an arc                                  *"<<endl;
    cout <<"*                2 : Modify an arc                               *"<<endl;
    cout <<"*                3 : Delete an arc                               *"<<endl;
    cout <<"*                4 : ADD a sommet                                *"<<endl;
    cout <<"*                5 : Modify a sommet                             *"<<endl;
    cout <<"*                6 : Delete a sommet                             *"<<endl;
    cout <<"*                7 : Reverse a graph                             *"<<endl;
    cout <<"******************************************************************"<<endl; 
    i = 0 ;
    cout <<"Please input your choice for execution : "<< endl;
    cin >>i;
}

int main(int argc, char *argv[])
{
	try
	{
		//char * filename = "test.txt";
		//CParse CParse(filename);
		//CParse.PARReadFile();
		//CGraph * CGraph;
		//CGraph = CParse.PARGetGraph();
		//CGraph->GRADispalyGraph();

		 // Input a graph from the file
		cout <<"******************************************************************"<<endl;
		cout << "Please input your filename : " << endl;
		char * filename = new char[32];
		cin >> filename;
		cout <<"******************************************************************"<<endl;
		cout << "Here is your graph : " << endl;
		CParse CParse(filename);
		CParse.PARReadFile();
		CGraph *CGraph;
		CGraph = CParse.PARGetGraph();
		CGraph->GRADispalyGraph();
		cout <<"******************************************************************"<<endl;

		//Choice the execution and then execute it
		int i;
		while(1)
		{
			ChoiceForExecution(i);
			switch(i)
			{
				//Add an arc
				case 1 :
					cout << "Input the departure (Début) of the arc :" << endl;
					unsigned int uiArcDeptA;
					cin >> uiArcDeptA;
					cout << "Input the destination (Fin) of the arc :" << endl;
					unsigned int uiArcDestA;
					cin >> uiArcDestA;
					CGraph->GRAAddArc(uiArcDeptA, uiArcDestA);
					cout <<"*********Here is your new graph after adding an arc **************"<<endl;
					CGraph->GRADispalyGraph();
				break;

				//Modify an arc
				case 2 :
					cout << "Input the departure (Début) of the old-arc :" << endl;
					unsigned int uiOldDept;
					cin >> uiOldDept;
					cout << "Input the departure (Début) of the new-arc :" << endl;
					unsigned int uiNewDept;
					cin >> uiNewDept;
					cout << "Input the destination (Fin) of the old-arc :" << endl;
					unsigned int uiOldDest;
					cin >> uiOldDest;
					cout << "Input the destination (Début) of the new-arc :" << endl;
					unsigned int uiNewDest;
					cin >> uiNewDest;
					CGraph->GRAModifyArc(uiOldDept, uiOldDest, uiNewDept, uiNewDest);
					cout <<"*********Here is your new graph after modifying an arc ***********"<<endl;
					CGraph->GRADispalyGraph();
				break;

				//Delete an arc
				case 3 :
					cout << "Input the departure (Début) of the arc :" << endl;
					unsigned int uiArcDeptD;
					cin >> uiArcDeptD;
					cout << "Input the destination (Fin) of the arc :" << endl;
					unsigned int uiArcDestD;
					cin >> uiArcDestD;
					CGraph->GRADeleteArc(uiArcDeptD, uiArcDestD);
					cout <<"*********Here is your new graph after deleting an arc ************"<<endl;
					CGraph->GRADispalyGraph();
				break;

				//Add a sommet
				case 4 :
					cout << "Input the number of sommet :" << endl;
					unsigned int uiNumSomA;
					cin >> uiNumSomA;
					CGraph->GRAAddSommet(uiNumSomA);
					cout <<"*********Here is your new graph after add an sommet **************"<<endl;
					CGraph->GRADispalyGraph();
				break;

				//Modify a sommet
				case 5 :
					cout << "Input the number of sommet which you want to modify:" << endl;
					unsigned int uiNumSomOld;
					cin >> uiNumSomOld;
					cout << "Input the new number of this sommet :" << endl;
					unsigned int uiNumSomNew;
					cin >> uiNumSomNew;
					CGraph->GRAModifySommet(uiNumSomOld, uiNumSomNew);
					cout <<"*********Here is your new graph after modifying a sommet**********"<<endl;
					CGraph->GRADispalyGraph();
				break;

				//Delete a sommet
				case 6 :
					cout << "Input the number of sommet :" << endl;
					unsigned int uiNumSomD;
					cin >> uiNumSomD;
					CGraph->GRADeleteSommet(uiNumSomD);
					cout <<"*********Here is your new graph after deleting an arc ************"<<endl;
					CGraph->GRADispalyGraph();
				break;

				//Reverse a graph
				case 7 :
					{
					COperationForGraph COperationForGraph;
					COperationForGraph.OPRReverseGraph(*CGraph);
					cout <<"*********Here is your new graph after reversion ******************"<<endl;
					CGraph->GRADispalyGraph();
					}
				break;

				default : 
					cout << "Your choice is [ "<<i<<" ] "<<endl;
				break;
			}
		}
	}
	catch (Exception & e)
	{
		e.EXCPrintStackTrace();
		system("pause");
		exit(0);
	}

	system("pause");
	return 0;
	
}


