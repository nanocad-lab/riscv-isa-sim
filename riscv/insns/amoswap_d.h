require_extension('A');
require_rv64;
reg_t v = MMU.load_uint64(RS1, false); //MWG
MMU.store_uint64(RS1, RS2, false); //MWG
WRITE_RD(v);
