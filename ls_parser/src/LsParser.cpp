/*
 * LsParser.cpp
 *
 *  Created on: 2013. 4. 12.
 *      Author: ÇÃ·§Æû¿î¿µÆÀ
 */

#include "LsParser.h"
#include "trim.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <string>

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 1024
#endif
#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 8
#endif
#ifndef MAX_FILE_NAME_LENGTH
#define MAX_FILE_NAME_LENGTH 500
#endif


LsParser::LsParser() {
	logDel = '*';
}


LsParser::~LsParser() {
	closeFiles();
}

void LsParser::parseEcho() {
	cout << "echo" << endl;
}

void LsParser::openFiles(const char *rFileName, const char *wFileName){
	this->fin.open(rFileName);
	this->fout.open(wFileName);
}

void LsParser::parse(){
	char line[MAX_LINE_LENGTH+1] = {0};
	char directory[MAX_LINE_LENGTH+1] = {0};
	char fileMode[11] = {0};
	int numberOfLinks = 0;
	char ownerName[MAX_NAME_LENGTH+1] = {0};
	char groupName[MAX_NAME_LENGTH+1] = {0};
	int numberOfBytesInTheFile = 0;
	char month[6] = {0};
	int date = 0;
	char year[6] = {0};
	char pathName[MAX_FILE_NAME_LENGTH] = {0};
	char fileExtension[MAX_FILE_NAME_LENGTH+1] = {0};

	char* token = 0; // token

	for(int i=0; !fin.eof(); i++) {

		fin.getline(line, MAX_LINE_LENGTH);

		/* ===Analyze line.=== */

		/* if the line is empty, pass the line */
		if(strlen(line) <= 0)
		{
			continue;
		}
		/* if the line starts with "./", it must be directory. */
		else if(strncmp(line, "./", 2) == 0){
			strcpy(directory, line);
			/* eliminate the last colon */
			for(int i=strlen(directory)-1; i>=0; i--){
				if(directory[i] == ':'){
					directory[i] = 0;
					break;
				}
			}
			continue;
		}
		/* if the line starts with "total" or "ÇÕ°è", pass the line. */
		else if(strncmp(line, "total", 5) == 0 || strncmp(line, "ÇÕ°è", 4) == 0){
			continue;
		}
		/* identify filetype. if there is wrong first character which not starts with file type, it must be an error.
		 * 'D' is for Door in the Sun Solaris operating system*/
		else if(line[0] != '-' && line[0] != 'd' && line[0] != 'c' &&
				line[0] != 'b' && line[0] != 'p' && line[0] != 'l' &&
				line[0] != 's' && line[0] != 'D'){
			cout << "[ERROR] Wrong line" << endl;
		}



		/* ===Parse line.=== */

		/* Read Filemode */
		token = strtok(line, " ");
		strncpy(fileMode, token, strlen(token));
		fileMode[10] = 0;

		/* Read the number of links. */
		token = strtok(NULL, " ");
		numberOfLinks = atoi(token);

		/* Read Owner Name */
		token = strtok(NULL, " ");
		strncpy(ownerName, token, strlen(token));
		ownerName[strlen(token)] = 0;

		/* Read Group Name */
		token = strtok(NULL, " ");
		strncpy(groupName, token, strlen(token));
		groupName[strlen(token)] = 0;

		/* Read the number of bytes in the file */
		token = strtok(NULL, " ");
		numberOfBytesInTheFile = atoi(token);

		/* Read month */
		token = strtok(NULL, " ");
		strncpy(month, token, strlen(token));
		month[strlen(token)] = 0;

		/* Read date */
		token = strtok(NULL, " ");
		date = atoi(token);

		/* Read Year */
		token = strtok(NULL, " ");
		strncpy(year, token, strlen(token));
		year[strlen(token)] = 0;

		/* Read path name */
		token = strtok(NULL, "");
		token = trim(token);	/* trim blanks from back and forth */
		strncpy(pathName, token, strlen(token));
		pathName[strlen(token)] = 0;

		/* Get the file extension from path name */
		int i_pathName = 0;
		for(i_pathName=strlen(pathName)-1; i_pathName>=0 && pathName[i_pathName] != '.' ; i_pathName--); /* Get position of the last dot */
		/* If there`s no dot, there`s no extension */
		if(i_pathName < 0) {
			strncpy(fileExtension, "Non_EXT", 8);
		}
		/* Else, copy the extension. */
		else {
			char* extensionPtr = pathName+i_pathName+1;
			strncpy(fileExtension, extensionPtr, strlen(extensionPtr));
			fileExtension[strlen(extensionPtr)] = 0;
		}




		/* ===Write to file=== */

		/* if the number of links isn`t 1, it must be directory, so ignore it. */
		if(numberOfLinks != 1)
			continue;

		fout 	<< directory << logDel
				<< numberOfLinks << logDel
				<< ownerName << logDel
				<< groupName << logDel
				<< numberOfBytesInTheFile << logDel
				<< month << logDel
				<< date << logDel
				<< year << logDel
				<< pathName << logDel
				<< fileExtension << endl;
		if(i%10000 == 0){
			cout << i << " line completed." << endl;
		}
	}


	cout << "parse over!" << endl;
}

void LsParser::analyze() {
	map<string , int> directoryJspCountMap;


	char line[MAX_LINE_LENGTH+1] = {0};
	char directory[MAX_LINE_LENGTH+1] = {0};
	char secondLayer[MAX_LINE_LENGTH+1] = {0};
	char fileMode[11] = {0};
	int numberOfLinks = 0;
	char ownerName[MAX_NAME_LENGTH+1] = {0};
	char groupName[MAX_NAME_LENGTH+1] = {0};
	int numberOfBytesInTheFile = 0;
	char month[6] = {0};
	int date = 0;
	char year[6] = {0};
	char pathName[MAX_FILE_NAME_LENGTH] = {0};
	char fileExtension[MAX_FILE_NAME_LENGTH+1] = {0};
	int jspCounter = 0;

	char* token = 0; // token

	for(int i=0; !fin.eof(); i++) {

		fin.getline(line, MAX_LINE_LENGTH);

		/* ===Analyze line.=== */

		/* if the line is empty, pass the line */
		if(strlen(line) <= 0)
		{
			continue;
		}
		/* if the line starts with "./", it must be directory. */
		else if(strncmp(line, "./", 2) == 0){
			strcpy(directory, line);
			/* eliminate the last colon */
			for(int i=strlen(directory)-1; i>=0; i--){
				if(directory[i] == ':'){
					directory[i] = 0;
					line[i] = 0;
					break;
				}
			}

			/* identify directory of second layer */
			strtok(line, "/");
			strtok(NULL, "/");
			char* newSecondLayer = strtok(NULL, "/");
			if(secondLayer[0] == 0)
			{
				strcpy(secondLayer, newSecondLayer);
			}
			/* if there`s new second layer appears */
			else if(strcmp(secondLayer, newSecondLayer) != 0){
				string secondLayerString = secondLayer;
				directoryJspCountMap[secondLayerString] = jspCounter;
				fout << secondLayer << logDel << jspCounter << endl;
				strcpy(secondLayer, newSecondLayer);
				jspCounter = 0;
			}


			continue;
		}
		/* if the line starts with "total" or "ÇÕ°è", pass the line. */
		else if(strncmp(line, "total", 5) == 0 || strncmp(line, "ÇÕ°è", 4) == 0){
			continue;
		}
		/* identify filetype. if there is wrong first character which not starts with file type, it must be an error.
		 * 'D' is for Door in the Sun Solaris operating system*/
		else if(line[0] != '-' && line[0] != 'd' && line[0] != 'c' &&
				line[0] != 'b' && line[0] != 'p' && line[0] != 'l' &&
				line[0] != 's' && line[0] != 'D'){
			cout << "[ERROR] Wrong line" << endl;
		}



		/* ===Parse line.=== */

		/* Read Filemode */
		token = strtok(line, " ");
		strncpy(fileMode, token, strlen(token));
		fileMode[10] = 0;

		/* Read the number of links. */
		token = strtok(NULL, " ");
		numberOfLinks = atoi(token);

		/* Read Owner Name */
		token = strtok(NULL, " ");
		strncpy(ownerName, token, strlen(token));
		ownerName[strlen(token)] = 0;

		/* Read Group Name */
		token = strtok(NULL, " ");
		strncpy(groupName, token, strlen(token));
		groupName[strlen(token)] = 0;

		/* Read the number of bytes in the file */
		token = strtok(NULL, " ");
		numberOfBytesInTheFile = atoi(token);

		/* Read month */
		token = strtok(NULL, " ");
		strncpy(month, token, strlen(token));
		month[strlen(token)] = 0;

		/* Read date */
		token = strtok(NULL, " ");
		date = atoi(token);

		/* Read Year */
		token = strtok(NULL, " ");
		strncpy(year, token, strlen(token));
		year[strlen(token)] = 0;

		/* Read path name */
		token = strtok(NULL, "");
		token = trim(token);	/* trim blanks from back and forth */
		strncpy(pathName, token, strlen(token));
		pathName[strlen(token)] = 0;

		/* figure out pathname has ".jsp" if it does, increase jsp counter */
		char lowerCasePathName[MAX_LINE_LENGTH+1] = {0};
		strcpy(lowerCasePathName, pathName);
		lowerCasePathName[strlen(pathName)] = 0;
		strlwr(lowerCasePathName);
		int pathNameLength = strlen(lowerCasePathName) - 3;

		for(int j=0; j<pathNameLength; j++){
			if(strncmp(lowerCasePathName+j, ".jsp", 4) == 0){
				jspCounter++;
				break;
			}
		}

		/* Get the file extension from path name */
		int i_pathName = 0;
		for(i_pathName=strlen(pathName)-1; i_pathName>=0 && pathName[i_pathName] != '.' ; i_pathName--); /* Get position of the last dot */
		/* If there`s no dot, there`s no extension */
		if(i_pathName < 0) {
			strncpy(fileExtension, "Non_EXT", 8);
		}
		/* Else, copy the extension. */
		else {
			char* extensionPtr = pathName+i_pathName+1;
			strncpy(fileExtension, extensionPtr, strlen(extensionPtr));
			fileExtension[strlen(extensionPtr)] = 0;
		}




		/* ===Write to file=== */

		/* if the number of links isn`t 1, it must be directory, so ignore it. */
		if(numberOfLinks != 1)
			continue;

/*		cout 	<< directory << logDel
				<< numberOfLinks << logDel
				<< ownerName << logDel
				<< groupName << logDel
				<< numberOfBytesInTheFile << logDel
				<< month << logDel
				<< date << logDel
				<< year << logDel
				<< pathName << logDel
				<< fileExtension << endl;*/
		if(i%10000 == 0){
			cout << i << " line completed." << endl;
		}
	}

	string secondLayerString = secondLayer;
	directoryJspCountMap[secondLayerString] = jspCounter;
	fout << secondLayer << logDel << jspCounter << endl;
/*

	 write statistics
	map<string, int>::iterator it;
	for(it = directoryJspCountMap.begin(); it != directoryJspCountMap.end(); it++){
		cout << ;
	}
*/


	cout << "parse over!" << endl;

}

void LsParser::closeFiles() {
	this->fin.close();
	this->fout.close();
}
