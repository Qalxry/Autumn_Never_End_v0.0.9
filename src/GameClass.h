#pragma once
#ifndef GAMECLASS_H
#define GAMECLASS_H

//-----------------------------------------------------------------------------------------------

struct COLOR;
struct PDTIME;

//-----------------------------------------------------------------------------------------------

struct COLOR {
	unsigned short br;
	unsigned short bg;
	unsigned short bb;
};

struct PDTIME {
	short print_time;
	short delete_time;
};

//-----------------------------------------------------------------------------------------------

#endif
