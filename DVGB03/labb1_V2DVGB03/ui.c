#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>

//
// Private
//
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i=0; i<num_options; i++) {
		printf("    %c) %s\n", 'a'+i, options[i]);
	}
}

// Prints the results of the tests.
void printres(result_t *result)
{
	for(int i=0;i<RESULT_ROWS;i++)
	{
		printf("Size: %d  ", result[i].size);
		printf("Time: %e  ", result[i].time);
		printf("T/n: %e  ", result[i].time/result[i].size);
		printf("T/n^2 %e  ", result[i].time/pow(result[i].size,2));
		printf("T/n^3 %e  ", result[i].time/pow(result[i].size,3));
		printf("T/log(n) %e  ", result[i].time/log(result[i].size));
		printf("T/nlog(n) %e\n\n", result[i].time/(result[i].size*log(result[i].size)));

	}
}

// Menu funktion that prints out options.
static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort avarege case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort avarege case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort avarege case\n",
		"Linear search best case",
		"Linear search worst case",
		"Linear search avarege case\n",
		"Binary search best case",
		"Binary search worst case",
		"Binary search avarege case",


	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

//
// Public
//
//Funktion that runs the UI.
void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];

	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
			// House keeping
			case 'a':
				show_menu = true;
				break;
			case 'b':
				running = false;
				break;


			// Bubble sort best
			case 'c':

				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
				printres(result);

				break;

				//bubble worst
			case 'd':
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);

				printres(result);
				break;

				//bubble average
			case 'e':

				benchmark(bubble_sort_t,average_t, result, RESULT_ROWS);

				printres(result);

				break;


				//insertion best
			case 'f':
				benchmark(insertion_sort_t,best_t,result, RESULT_ROWS);

				printres(result);
				break;

				//insertion worst
			case 'g':
				benchmark(insertion_sort_t,worst_t,result, RESULT_ROWS);

				printres(result);
				break;

				//insertion average
			case 'h':
				benchmark(insertion_sort_t,average_t,result, RESULT_ROWS);

				printres(result);
				break;


				//quick best
			case 'i':
				benchmark(quick_sort_t,best_t,result, RESULT_ROWS);

				printres(result);
				break;

				//quick worst
			case 'j':
				benchmark(quick_sort_t,worst_t,result, RESULT_ROWS);

				printres(result);

				break;

				//quick average
			case 'k':

				benchmark(quick_sort_t,average_t,result, RESULT_ROWS);
				printres(result);


				break;



				//linear best
			case 'l':
				benchmark(linear_search_t,best_t,result, RESULT_ROWS);

				printres(result);
				break;

				//linear worst
			case 'm':
				benchmark(linear_search_t,worst_t,result, RESULT_ROWS);

				printres(result);
				break;

				//linear average
			case 'n':
				benchmark(linear_search_t,average_t,result, RESULT_ROWS);

				printres(result);
				break;



				//binary best
			case 'o':
				benchmark(binary_search_t,best_t,result, RESULT_ROWS);

				printres(result);
				break;

				//binary worst
			case 'p':
				benchmark(binary_search_t,worst_t,result, RESULT_ROWS);

				printres(result);
				break;

				//binary average
			case 'q':
				benchmark(binary_search_t,average_t,result, RESULT_ROWS);

				printres(result);

				break;


			// Invalid input
			default:
				show_menu = false;
				ui_invalid_input();
				break;


		}
	}
	ui_exit();
}
