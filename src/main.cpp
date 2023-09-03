#include <iostream>
#include <cstdlib>
#include <cstring>
#include "algo_extractor.h"

int main()
{
    static AlgoExtractor extractor;
    static FlashIface::program_target_t target = {0};
    static FlashIface::target_cfg_t cfg;

    extractor.extract("./STM32H7x_2048.FLM", target, cfg);

    for (int i = 0; i < cfg.sector_info.size(); i++)
    {
        int sec_num = (i != (cfg.sector_info.size() - 1)) ? ((cfg.sector_info[i + 1].start - cfg.sector_info[i].start) / cfg.sector_info[i].size) : ((cfg.flash_regions[0].end - cfg.sector_info[i].start) / cfg.sector_info[i].size);
        printf("Sector info %d  start addr: 0x%x, secrot size: 0x%x * %d\n", i, cfg.sector_info[i].start, cfg.sector_info[i].size, sec_num);
    }

    for (int i = 0; i < cfg.flash_regions.size(); i++)
    {
        if (cfg.flash_regions[i].start == 0 && cfg.flash_regions[i].end == 0)
            break;

        std::cout << "Flash region " << i << " addr:0x" << std::hex << cfg.flash_regions[i].start << ", end:0x" << cfg.flash_regions[i].end << std::endl;
    }

    for (int i = 0; i < cfg.ram_regions.size(); i++)
    {
        if (cfg.ram_regions[i].start == 0 && cfg.ram_regions[i].end == 0)
            break;

        std::cout << "RAM region " << i << " addr:0x" << std::hex << cfg.ram_regions[i].start << ", end:0x" << cfg.ram_regions[i].end << std::endl;
    }

    if (target.algo_blob)
        delete[] target.algo_blob;
}