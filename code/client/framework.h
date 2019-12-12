#pragma once

enum class key_state_t
{
	none = 0,
	clear,
	enter,
	cancel,
	exit
};

class framework
{
public:
	framework();
	~framework();

	bool initialize();
	
	bool input();
	void process_arrow_key();
	void process_enter_key();
	void process_cancel_key();
	void process_exit_key();

	void update();
	void draw();

private:
	key_state_t state = key_state_t::none;
};
