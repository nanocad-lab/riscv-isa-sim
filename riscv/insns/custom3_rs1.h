reg_t msg;
reg_t cl[8];
reg_t blockpos;

//Read CSRs
msg = p->get_csr(CSR_PENALTY_BOX_MSG);
cl[0] = p->get_csr(CSR_PENALTY_BOX_CACHELINE_BLK0);
cl[1] = p->get_csr(CSR_PENALTY_BOX_CACHELINE_BLK1);
cl[2] = p->get_csr(CSR_PENALTY_BOX_CACHELINE_BLK2);
cl[3] = p->get_csr(CSR_PENALTY_BOX_CACHELINE_BLK3);
cl[4] = p->get_csr(CSR_PENALTY_BOX_CACHELINE_BLK4);
cl[5] = p->get_csr(CSR_PENALTY_BOX_CACHELINE_BLK5);
cl[6] = p->get_csr(CSR_PENALTY_BOX_CACHELINE_BLK6);
cl[7] = p->get_csr(CSR_PENALTY_BOX_CACHELINE_BLK7);
blockpos = p->get_csr(CSR_PENALTY_BOX_CACHELINE_BLKPOS);

//Convert values to lumps of bytes
uint8_t* victim_message = reinterpret_cast<uint8_t*>(&msg);
uint8_t cacheline[64];
//memcpy(victim_message, &msg, 8);
memcpy(cacheline, cl, 64);

//Run external command
std::string script_filename = "/home/mgottscho/Git/eccgrp-ecc-ctrl/data_recovery_spike_wrapper.sh";
std::string cmd = construct_sdecc_recovery_cmd(script_filename, victim_message, 8, cacheline, (unsigned)(blockpos));
std::string output = myexec(cmd);
const char* output_cstr = output.c_str();

MMU.store_slow_path(RS1, output.length(), (const uint8_t*)output_cstr, 0);

std::cout << " Original message: ";
for (size_t i = 0; i < 8; i++)
  std::cout << std::bitset<8>(victim_message[i]);
std::cout << std::endl;
std::cout << "Recovered message: " << output; //output has newline built in
