/*
 * LsParser.h
 *
 *  Created on: 2013. 4. 12.
 *      Author: ÇÃ·§Æû¿î¿µÆÀ
 */

#ifndef LSPARSER_H_
#define LSPARSER_H_

#include <string>
#include <fstream>

using namespace std;


class LsParser {
public:
	LsParser();
	~LsParser();

	void parseEcho();

	void openFiles(const char *rFileName, const char *wFileName);
	void parse();
	void analyze();
	void closeFiles();

protected:
	ifstream fin;
	ofstream fout;
	char logDel;
};

#endif /* LSPARSER_H_ */
