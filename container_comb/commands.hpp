#ifndef COMMANDS_H
#define COMMANDS_H

using namespace std;

void CHANGE(string region, string newCenter, map<string, string>& regions);
void RENAME(string old_region, string new_region, map<string, string>& regions);
void ABOUT(string region, map<string, string>& regions);
void ALL(map<string, string>& regions);

#endif