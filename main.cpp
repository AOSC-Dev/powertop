#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "cpu/cpu.h"
#include "process/process.h"
#include "perf/perf.h"
#include "perf/perf_bundle.h"
#include "lib.h"

#include "devices/device.h"
#include "devices/backlight.h"
#include "measurement/measurement.h"
#include "parameters/parameters.h"

int main(int argc, char **argv)
{
	int i;

	system("/sbin/modprobe cpufreq_stats > /dev/null 2>&1");


	enumerate_cpus();
	create_all_backlights();
	detect_power_meters();



	for (i = 0; i < 1; i++) {
		start_power_measurement();
		devices_start_measurement();
		start_process_measurement();
		start_cpu_measurement();


		cout << "measuring\n";
		sleep(2);


		end_cpu_measurement();
		end_process_measurement();
		devices_end_measurement();
		end_power_measurement();

		cout << "doing math \n";

		process_cpu_data();
		process_process_data();
		store_results();
	}


//	display_cpu_cstates();
//	cout << "\n\n\n";

//	display_cpu_pstates();

//	display_cpu_cstates("<table>\n", "</table>\n", "<tr><td>","</td><td>", "</td></tr>\n");
//	display_cpu_pstates("<table>\n", "</table>\n", "<tr><td>","</td><td>", "</td></tr>\n");

	i = 0;
	while (i++ < 20) {
		start_power_measurement();
		devices_start_measurement();
		start_process_measurement();
		start_cpu_measurement();


		cout << "measuring\n";
		sleep(10);


		end_cpu_measurement();
		end_process_measurement();
		devices_end_measurement();
		end_power_measurement();

		cout << "doing math \n";

		process_cpu_data();
		process_process_data();
		

		report_devices();
		store_results();
		printf("\n\nPower estimated: %5.1f\n", global_joules_consumed());
	}

	end_process_data();
	end_cpu_data();

	register_parameter("base power", 8.4);

	learn_parameters();

	return 0;
}
