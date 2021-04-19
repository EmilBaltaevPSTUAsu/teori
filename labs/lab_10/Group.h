#pragma once
#include "Finance.h"
#include <vector>
#include <map>
#include <set>
#include <algorithm>

class Group
{
private:
	vector<Finance> fins;
	int fin_AI;
	int last_delete;

public:
	Group();
	~Group();

	// Finance
	bool fin_contains(Finance& fin);
	void fin_select();
	void fin_select_by_department();
	void fin_insert();
	void fin_update();
	void fin_delete();
	void fin_cancel_delete();
	void fin_save();
	void fin_read();
	void query1();
	void query2();
};

