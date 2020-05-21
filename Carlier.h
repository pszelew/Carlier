#pragma once

#include <limits>
#include "result_shrage.h"
#include <vector>
#include <algorithm>
#include <iostream>

class Carlier
{
	public:
		Carlier();
		zadanie best[2000];
		zadanie schrage[2000];
		int UB;
		int LB;
		int U;
		int a;
		int b;
		int c;
		int n;
		long long flag;
		int r_k;
		int p_k;
		int q_k;

		//int r_backup;
		//int q_backup;
		//int num_backup_r;
		//int num_backup_q;

		int schrage_inter();
		int schrage_normal();
		int do_carlier();
		int check_time();
		int h(int a, int b, int c);
		int check_time_stop_working(int k);



};
