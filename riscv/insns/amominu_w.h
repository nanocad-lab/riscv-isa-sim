require_extension('A');
uint32_t v = MMU.load_int32(RS1, false); //MWG
MMU.store_uint32(RS1, std::min(uint32_t(RS2),v), false); //MWG
WRITE_RD((int32_t)v);
