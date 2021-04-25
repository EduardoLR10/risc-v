#include "forward/forward_tb.hpp"

void forward_tb::aciona() {
	ID_EX_rs1 = 0;	ID_EX_rs2 = 0;	EX_MEM_rd = 0;	MEM_WB_rd = 0;
	EX_MEM_write = 0;	MEM_WB_write = 0;
	wait(1, SC_NS);
	std::cout << "ID/EX.rs1 = " << ID_EX_rs1.read() << "\tID/EX.rs2 = " << ID_EX_rs2.read() <<
		"\tEX/MEM.rd = " << EX_MEM_rd.read() << "\tMEM/WB.rd = " << MEM_WB_rd.read() <<
		"\nEX/MEM.write = " << EX_MEM_write.read() << "\tMEM/WB.write = " << MEM_WB_write.read() << std::endl;
	std::cout << "Forward A = " << forwardA.read() << "\tForward B = " << forwardB.read() << std::endl << std::endl;

	ID_EX_rs1 = 5;	ID_EX_rs2 = 0;	EX_MEM_rd = 0;	MEM_WB_rd = 0;
	EX_MEM_write = 1;	MEM_WB_write = 0;
	wait(1, SC_NS);
	std::cout << "ID/EX.rs1 = " << ID_EX_rs1.read() << "\tID/EX.rs2 = " << ID_EX_rs2.read() <<
		"\tEX/MEM.rd = " << EX_MEM_rd.read() << "\tMEM/WB.rd = " << MEM_WB_rd.read() <<
		"\nEX/MEM.write = " << EX_MEM_write.read() << "\tMEM/WB.write = " << MEM_WB_write.read() << std::endl;
	std::cout << "Forward A = " << forwardA.read() << "\tForward B = " << forwardB.read() << std::endl << std::endl;

	ID_EX_rs1 = 5;	ID_EX_rs2 = 0;	EX_MEM_rd = 5;	MEM_WB_rd = 0;
	EX_MEM_write = 1;	MEM_WB_write = 0;
	wait(1, SC_NS);
	std::cout << "ID/EX.rs1 = " << ID_EX_rs1.read() << "\tID/EX.rs2 = " << ID_EX_rs2.read() <<
		"\tEX/MEM.rd = " << EX_MEM_rd.read() << "\tMEM/WB.rd = " << MEM_WB_rd.read() <<
		"\nEX/MEM.write = " << EX_MEM_write.read() << "\tMEM/WB.write = " << MEM_WB_write.read() << std::endl;
	std::cout << "Forward A = " << forwardA.read() << "\tForward B = " << forwardB.read() << std::endl << std::endl;

	ID_EX_rs1 = 5;	ID_EX_rs2 = 5;	EX_MEM_rd = 5;	MEM_WB_rd = 0;
	EX_MEM_write = 1;	MEM_WB_write = 0;
	wait(1, SC_NS);
	std::cout << "ID/EX.rs1 = " << ID_EX_rs1.read() << "\tID/EX.rs2 = " << ID_EX_rs2.read() <<
		"\tEX/MEM.rd = " << EX_MEM_rd.read() << "\tMEM/WB.rd = " << MEM_WB_rd.read() <<
		"\nEX/MEM.write = " << EX_MEM_write.read() << "\tMEM/WB.write = " << MEM_WB_write.read() << std::endl;
	std::cout << "Forward A = " << forwardA.read() << "\tForward B = " << forwardB.read() << std::endl << std::endl;

	ID_EX_rs1 = 5;	ID_EX_rs2 = 7;	EX_MEM_rd = 5;	MEM_WB_rd = 0;
	EX_MEM_write = 1;	MEM_WB_write = 1;
	wait(1, SC_NS);
	std::cout << "ID/EX.rs1 = " << ID_EX_rs1.read() << "\tID/EX.rs2 = " << ID_EX_rs2.read() <<
		"\tEX/MEM.rd = " << EX_MEM_rd.read() << "\tMEM/WB.rd = " << MEM_WB_rd.read() <<
		"\nEX/MEM.write = " << EX_MEM_write.read() << "\tMEM/WB.write = " << MEM_WB_write.read() << std::endl;
	std::cout << "Forward A = " << forwardA.read() << "\tForward B = " << forwardB.read() << std::endl << std::endl;

	ID_EX_rs1 = 5;	ID_EX_rs2 = 7;	EX_MEM_rd = 5;	MEM_WB_rd = 3;
	EX_MEM_write = 1;	MEM_WB_write = 1;
	wait(1, SC_NS);
	std::cout << "ID/EX.rs1 = " << ID_EX_rs1.read() << "\tID/EX.rs2 = " << ID_EX_rs2.read() <<
		"\tEX/MEM.rd = " << EX_MEM_rd.read() << "\tMEM/WB.rd = " << MEM_WB_rd.read() <<
		"\nEX/MEM.write = " << EX_MEM_write.read() << "\tMEM/WB.write = " << MEM_WB_write.read() << std::endl;
	std::cout << "Forward A = " << forwardA.read() << "\tForward B = " << forwardB.read() << std::endl << std::endl;

	ID_EX_rs1 = 5;	ID_EX_rs2 = 7;	EX_MEM_rd = 6;	MEM_WB_rd = 3;
	EX_MEM_write = 0;	MEM_WB_write = 1;
	wait(1, SC_NS);
	std::cout << "ID/EX.rs1 = " << ID_EX_rs1.read() << "\tID/EX.rs2 = " << ID_EX_rs2.read() <<
		"\tEX/MEM.rd = " << EX_MEM_rd.read() << "\tMEM/WB.rd = " << MEM_WB_rd.read() <<
		"\nEX/MEM.write = " << EX_MEM_write.read() << "\tMEM/WB.write = " << MEM_WB_write.read() << std::endl;
	std::cout << "Forward A = " << forwardA.read() << "\tForward B = " << forwardB.read() << std::endl << std::endl;

	ID_EX_rs1 = 3;	ID_EX_rs2 = 7;	EX_MEM_rd = 6;	MEM_WB_rd = 3;
	EX_MEM_write = 0;	MEM_WB_write = 1;
	wait(1, SC_NS);
	std::cout << "ID/EX.rs1 = " << ID_EX_rs1.read() << "\tID/EX.rs2 = " << ID_EX_rs2.read() <<
		"\tEX/MEM.rd = " << EX_MEM_rd.read() << "\tMEM/WB.rd = " << MEM_WB_rd.read() <<
		"\nEX/MEM.write = " << EX_MEM_write.read() << "\tMEM/WB.write = " << MEM_WB_write.read() << std::endl;
	std::cout << "Forward A = " << forwardA.read() << "\tForward B = " << forwardB.read() << std::endl << std::endl;

	ID_EX_rs1 = 5;	ID_EX_rs2 = 3;	EX_MEM_rd = 6;	MEM_WB_rd = 3;
	EX_MEM_write = 0;	MEM_WB_write = 1;
	wait(1, SC_NS);
	std::cout << "ID/EX.rs1 = " << ID_EX_rs1.read() << "\tID/EX.rs2 = " << ID_EX_rs2.read() <<
		"\tEX/MEM.rd = " << EX_MEM_rd.read() << "\tMEM/WB.rd = " << MEM_WB_rd.read() <<
		"\nEX/MEM.write = " << EX_MEM_write.read() << "\tMEM/WB.write = " << MEM_WB_write.read() << std::endl;
	std::cout << "Forward A = " << forwardA.read() << "\tForward B = " << forwardB.read() << std::endl << std::endl;

	ID_EX_rs1 = 3;	ID_EX_rs2 = 3;	EX_MEM_rd = 6;	MEM_WB_rd = 3;
	EX_MEM_write = 0;	MEM_WB_write = 1;
	wait(1, SC_NS);
	std::cout << "ID/EX.rs1 = " << ID_EX_rs1.read() << "\tID/EX.rs2 = " << ID_EX_rs2.read() <<
		"\tEX/MEM.rd = " << EX_MEM_rd.read() << "\tMEM/WB.rd = " << MEM_WB_rd.read() <<
		"\nEX/MEM.write = " << EX_MEM_write.read() << "\tMEM/WB.write = " << MEM_WB_write.read() << std::endl;
	std::cout << "Forward A = " << forwardA.read() << "\tForward B = " << forwardB.read() << std::endl << std::endl;

	ID_EX_rs1 = 5;	ID_EX_rs2 = 7;	EX_MEM_rd = 6;	MEM_WB_rd = 3;
	EX_MEM_write = 1;	MEM_WB_write = 1;
	wait(1, SC_NS);
	std::cout << "ID/EX.rs1 = " << ID_EX_rs1.read() << "\tID/EX.rs2 = " << ID_EX_rs2.read() <<
		"\tEX/MEM.rd = " << EX_MEM_rd.read() << "\tMEM/WB.rd = " << MEM_WB_rd.read() <<
		"\nEX/MEM.write = " << EX_MEM_write.read() << "\tMEM/WB.write = " << MEM_WB_write.read() << std::endl;
	std::cout << "Forward A = " << forwardA.read() << "\tForward B = " << forwardB.read() << std::endl << std::endl;
}