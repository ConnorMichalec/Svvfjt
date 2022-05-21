#pragma once

class UserInput {
	public:
		UserInput();
		~UserInput();
		void Update();
		float FetchP1();
		float FetchP2();
		float FetchP3();

	private:
		// Each parameter state can be used for various purposes, just represents general input
		float p1_state;
		float p2_state;
		float p3_state;
};
