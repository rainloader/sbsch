/*
 * FileRecord.h
 *
 *  Created on: 2013. 4. 11.
 *      Author: ÇÃ·§Æû¿î¿µÆÀ
 */

#ifndef FILERECORD_H_
#define FILERECORD_H_

#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 8
#endif
#ifndef MAX_FILE_NAME_LENGTH
#define MAX_FILE_NAME_LENGTH 500
#endif

#include <string>

typedef struct _FileTime{
	short year;
	short month;
	short date;
	short hour;
	short minute;
}FileTime;

typedef struct _AdditionalInfo{
	char fileType[10];
	char programming[10];
	char dbUsage[5];
	char uploadUsage[5];
}AdditionalInfo;

class FileRecord{
public:
	FileRecord();
	~FileRecord();

protected:
	char mtFileMode[10];
	int mtNumberOfLinks;
	char mtOwnerName[MAX_NAME_LENGTH];
	char mtGroupName[MAX_NAME_LENGTH];
	int mtNumberOfBytesInTheFile;
	FileTime mtFileTime;
/*	short mtMonth;
	short mtDate;
	short mtYear;
	short mtHour;
	short mtMinute;*/
	char mtPathName[MAX_FILE_NAME_LENGTH];
	AdditionalInfo mtAdditionalInfo;

private:

};



#endif /* FILERECORD_H_ */
