#include "cpu/exec/template-start.h"

#define instr adc

static void do_execute () {
	DATA_TYPE result = op_dest->val + op_src->val + cpu.eflags.CF;
	OPERAND_W(op_dest, result);

	/* TODO: Update EFLAGS. */
	update_eflags_pf_zf_sf((DATA_TYPE_S)result);
	cpu.eflags.CF = result < op_dest->val;
	cpu.eflags.OF = MSB(~(op_dest->val ^ op_src->val) & (op_dest->val ^ result));

	print_asm_template2();
}

make_instr_helper(r2rm)
make_instr_helper(i2rm)
make_instr_helper(rm2r)

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
#include "cpu/exec/template-end.h"
