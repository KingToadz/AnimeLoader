// UsingIO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Downloader.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>

int _tmain(int argc, _TCHAR* argv[])
{
	Downloader downloader;

	if(!downloader.Load())
	{
		std::cout << "Error Downloading" << std::endl;
		return -1;
	}

	// open calendar.vcs
	std::ifstream fileToRead("calendar");

	// Is er een error tijdens het openen.
	if(!fileToRead.is_open())
	{
		std::cout << "Error opening file!" << std::endl;
		system("pause");
		return 1;
	}

	// melding dat die leest
	std::cout << "Reading Calendar file..." << std::endl;
	
	// buffer om in op te slaan
	char buffer[128];

	// Moet de eerst volgende summary tag worden laten zien
	bool Summary = false;

	// prefix van de dag gister vandaag morgen
	enum prefix
	{
		Yesterday,
		Today,
		Tomarrow
	};

	std::string prefixNames[] = { "Yesterday", "Today", "Tommorow"};

	prefix curFix;
	
	// Lees zolang de End Of File niet gelezen is
	while(!fileToRead.eof())
	{
		// Lees de volgende line in het bestand
		fileToRead.getline(buffer, 128);

		// stringstream word
		std::stringstream words;
		
		// Lees eerste 7 tekens
		for(int i = 0; i < 7; i++)
			words << buffer[i];

		// eerste 7 tekens DTSTART
		if(words.str() == "DTSTART")
		{
			std::stringstream date;

			// Lees de datum (altijd tussen de 8 en 16)
			for(int i = 8; i < 16; i++)
				date << buffer[i];

			// tijd
			time_t secs=time(0);
			tm *t=localtime(&secs);

			for (int i = -1; i < 2; i++)
			{
			
				std::stringstream curDate;

				//			jaar
				curDate << t->tm_year+1900;

				// als de maand onder de 10 is voeg er een 0 aan toe dus 1 word 01
				if(t->tm_mon + 1 < 10)
					curDate << "0";
				curDate << t->tm_mon + 1;

				// als de dag onder de 10 is voeg er een 0 aan toe dus 1 word 01
				if(t->tm_mday < 10)
					curDate << "0";
				curDate << t->tm_mday + i;

				// Datum van vandaag de zelfde als in de file
				if(curDate.str() == date.str())
				{
					switch (i)
					{
						case -1:
							curFix = Yesterday;
							break;
						case 0:
							curFix = Today;
							break;
						case 1:
							curFix = Tomarrow;
							break;
					}
					// Laat de eerst volgende summary zien
					Summary = true;
					break;
				}
			}
		}
		// Eerste 7 tekens SUMMARY en Summary is true
		else if (words.str() == "SUMMARY" && Summary)
		{
			words << " ";

			for(int i = 8; i < 64; i++)
				words << buffer[i];

			std::cout << prefixNames[curFix] << ": " << words.str().substr(8,64)<< std::endl;

			Summary = false;
		}

		memset(buffer, 0, 128);
	}

	// End of program
	std::cout << "Done with reading" << std::endl;
	system("pause");
	return 0;
}