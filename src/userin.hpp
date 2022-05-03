#pragma once

class UserInput {
    public:
        UserInput();
        ~UserInput();
		int FetchP1();
		int FetchP2();
		int FetchP3();

	private:
		int p1_inState;
		int p2_inState;
		int p3_inState;
};