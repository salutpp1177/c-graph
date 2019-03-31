#include "Parse.h"


/** The default constructor
 */
CParse::CParse()
{
	pcGraph = nullptr;
	cPARFilename = nullptr;
}

/** The defined constructor
 * @param uiNum the number of this sommet
 */
CParse::CParse(const char * Filename)
{
	//pcGraph = nullptr;
	pcGraph = new CGraph();
	cPARFilename = _strdup(Filename);
}

/** The destructor
 */
CParse::~CParse()
{
	if (pcGraph != nullptr)
	{
		delete pcGraph;
	}
}


/** Get the number of sommets 
 * @return the number of sommets
 */
unsigned int CParse::PARGetnbrSommets()
{
	return uiPARnbrSommets;
}

/** Get the number of arcs
 * @return the number of arcs
 */
unsigned int CParse::PARGetnbrArcs()
{
	return uiPARnbrArcs;
}

/** Read the file
 */
void CParse::PARReadFile()
{
	ifstream file;
	file.open(cPARFilename);
	if (!file.is_open())
	{
		throw Exception(FailOpenFile);
	}

	string str;
	if (!file.eof())
	{
		getline(file, str);
		size_t len = str.length();
		//Check the file is vide
		if (len < 1)
		{
			throw Exception(FileVide);
		}

		//Get the number of sommet
		size_t find = str.find("NBSommets=");
		if (find != -1)
		{
			find = str.find("=");
			int bufnbrSom = 0;
			for (size_t i = find + 1; i < len; i++)
			{
				if (!isdigit(str[i]))
				{
					throw Exception(FileContentError);
				}

				bufnbrSom = bufnbrSom * 10 + str[i] - '0';
			}
			uiPARnbrSommets = bufnbrSom; 

		}
		else throw Exception(FileContentError);

		getline(file, str);
		len = str.length();

		//Get the number of arc
		find = str.find("NBArcs=");
		if (find != -1)
		{
			find = str.find("=");
			int bufnbrarc = 0;
			for (size_t i = find + 1; i < len; i++)
			{
				if (!isdigit(str[i]))
				{
					throw Exception(FileContentError);
				}
				bufnbrarc = bufnbrarc * 10 + str[i] - '0';
			}
			uiPARnbrArcs = bufnbrarc;
		}
		else throw Exception(FileContentError);

		getline(file, str);
		len = str.length();

		//Get the content of sonmmets' number
		if (str.find("Sommets=[") == -1)
		{
			throw Exception(FileContentError);
		}

		for (size_t i = 0; i < uiPARnbrSommets; i++)
		{
			getline(file, str);
			len = str.length();
			//Add the new sommet
			find = str.find("Numero=");
			if (find != -1)
			{
				find = str.find("=");
				int bufnumsommet = 0;
				for (size_t i = find + 1; i < len; i++)
				{
					if (!isdigit(str[i]))
					{
						throw Exception(FileContentError);
					}
					bufnumsommet = bufnumsommet * 10 + str[i] - '0';
				}
				pcGraph->GRAAddSommet(bufnumsommet); 
			}
		}

		getline(file, str);
		len = str.length();

		if (str.find("]") == -1)
		{
			throw Exception(FileContentError);
		}

		getline(file, str);
		len = str.length();

		//Get the content of arcs' number
		if (str.find("Arcs=[") == -1)
		{
			throw Exception(FileContentError);
		}

		for (unsigned int i = 0; i < uiPARnbrSommets; i++)
		{
			int numDebut;
			int numFin;

			getline(file, str);
			len = str.length();

			//Get the beginning of the arc
			find = str.find("Debut=");
			size_t findComa = str.find(",");
			if (find != -1)
			{
				find += 5;
				int bufnumdebut = 0;
				for (size_t i = find + 1; i < findComa; i++)
				{
					if (!isdigit(str[i]))
					{
						throw Exception(FileContentError);
					}
					bufnumdebut = bufnumdebut * 10 + str[i] - '0';
				}
				numDebut = bufnumdebut;
			}
			else
			{
				throw Exception(FileContentError);
			}

			//Get the end of the arc
			find = str.find("Fin=");
			if (find != -1)
			{
				find += 3;
				int bufnumfin = 0;
				for (size_t i = find + 1; i < len; i++)
				{
					if (!isdigit(str[i]))
					{
						throw Exception(FileContentError);
					}
					bufnumfin = bufnumfin * 10 + str[i] - '0';
				}
				numFin = bufnumfin;
			}
			else
			{
				throw Exception(FileContentError);
			}

			pcGraph->GRAAddArc(numDebut, numFin);
		}

	}
}

/** Remove the blank space in a string
 * @param str the string
 */
void CParse::PARRemoveBlanks(string & str)
{
	str.erase(remove_if(str.begin(), str.end(),isspace));
}
	 