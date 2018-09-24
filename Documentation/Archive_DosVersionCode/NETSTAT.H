#ifndef _NETSTAT_H
#define _NETSTAT_H				/* avoid recompilation */

#define MAX_SLAVE_ADDRESS_TABLE 32
typedef struct {
 char state;
 char serialno[9];
 int  panel;
 char description[21];
 char label[9];
} SLAVEADDRESSTable;

#endif