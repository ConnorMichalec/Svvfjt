/**
 * Manage GPIO input data and make them available for audio/visual
 * 
 */

#include "userin.hpp"

UserInput::UserInput() {

}

UserInput::~UserInput() {
	
}

int UserInput::FetchP1()
{
	return(p1_inState);
}

int UserInput::FetchP2()
{
	return(p2_inState);	
}

int UserInput::FetchP3()
{
	return(p3_inState);	
}
