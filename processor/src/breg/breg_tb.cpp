#include "breg/breg_tb.hpp"

void breg_tb::drive() {
	wait();
	wren = 1;
	for (int i=0; i<32; i++) {
		rd = i; 
		rs1 = i;
		d_in.write(i*10);
		wait();
	}
	wren = 0;
	for (int i=0; i<32; i++) {
		rs1 = i; 
		rs2 = i;
		wait();
	}
}

void breg_tb::monitor() {
	cout	<< std::setw(10) << "Time" << std::setw(5) << "rs1" << std::setw(5) << "rs2" 
			<< std::setw(5) << "rd" << std::setw(5) << "wren" 
			<< std::setw(5) << "d_in" << std::setw(5)
			<< "ra" << std::setw(5) << "rb" << endl;
	cout << std::setw(10) << sc_time_stamp()
	<< std::setw(5) << rs1.read()  << std::setw(5) << rs2.read()  << std::setw(5)
	<< rd.read()  << std::setw(5) << wren.read()  << std::setw(5) << d_in.read()  << std::setw(5)
	<< ra.read()  << std::setw(5) << rb.read()  << endl;
}