#include <stdio.h>
#include <stdint.h>
#include <string.h>

const uint8_t licensee_codes[] = {0x00,0x01,0x08,0x09,0x0A,0x0B,0x0C,0x13,0x18,0x19,0x1A,0x1D,0x1F,0x24,0x25,0x28,0x29,0x30,0x31,0x32,0x33,0x34,0x35,0x38,0x39,0x3C,0x3E,0x41,0x42,0x44,0x46,0x47,0x49,0x4A,0x4D,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x59,0x5A,0x5B,0x5C,0x5D,0x60,0x61,0x67,0x69,0x6E,0x6F,0x70,0x71,0x72,0x73,0x75,0x78,0x79,0x7A,0x7C,0x7F,0x80,0x83,0x86,0x8B,0x8C,0x8E,0x8F,0x91,0x92,0x93,0x95,0x96,0x97,0x99,0x9A,0x9B,0x9C,0x9D,0x9F,0xA1,0xA2,0xA4,0xA6,0xA7,0xA9,0xAA,0xAC,0xAD,0xAF,0xB0,0xB1,0xB2,0xB4,0xB6,0xB7,0xB9,0xBA,0xBB,0xBD,0xBF,0xC0,0xC2,0xC3,0xC4,0xC5,0xC6,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,0xD0,0xD1,0xD2,0xD3,0xD4,0xD6,0xD7,0xD9,0xDA,0xDB,0xDD,0xDE,0xDF,0xE0,0xE1,0xE2,0xE3,0xE5,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xEE,0xF0,0xF3,0xFF};

const char* licensee_names[] = {"None/Not found","Nintendo","Capcom","HOT-B","Jaleco","Coconuts Japan","Elite Systems","EA (Electronic Arts)","Hudson Soft","ITC Entertainment","Yanoman","Japan Clary","Virgin Games Ltd.3","PCM Complete","San-X","Kemco","SETA Corporation","Infogrames5","Nintendo","Bandai","Indicates that the New licensee code should be used instead","Konami","HectorSoft","Capcom","Banpresto","Entertainment I","Gremlin","Ubi Soft1","Atlus","Malibu Interactive","Angel","Spectrum Holoby","Irem","Virgin Games Ltd.3","Malibu Interactive","U.S. Gold","Absolute","Acclaim Entertainment","Activision","Sammy USA Corporation","GameTek","Park Place","LJN","Matchbox","Milton Bradley Company","Mindscape","Romstar","Naxat Soft13","Tradewest","Titus Interactive","Virgin Games Ltd.3","Ocean Software","EA (Electronic Arts)","Elite Systems","Electro Brain","Infogrames5","Interplay Entertainment","Broderbund","Sculptured Software6","The Sales Curve Limited7","THQ","Accolade","Triffix Entertainment","Microprose","Kemco","Misawa Entertainment","Lozc","Tokuma Shoten","Bullet-Proof Software2","Vic Tokai","Ape","I’Max","Chunsoft Co.8","Video System","Tsubaraya Productions","Varie","Yonezawa/S’Pal","Kemco","Arc","Nihon Bussan","Tecmo","Imagineer","Banpresto","Nova","Hori Electric","Bandai","Konami","Kawada","Takara","Technos Japan","Broderbund","Toei Animation","Toho","Namco","Acclaim Entertainment","ASCII Corporation or Nexsoft","Bandai","Square Enix","HAL Laboratory","SNK","Pony Canyon","Culture Brain","Sunsoft","Sony Imagesoft","Sammy Corporation","Taito","Kemco","Square","Tokuma Shoten","Data East","Tonkinhouse","Koei","UFL","Ultra","Vap","Use Corporation","Meldac","Pony Canyon","Angel","Taito","Sofel","Quest","Sigma Enterprises","ASK Kodansha Co.","Naxat Soft13","Copya System","Banpresto","Tomy","LJN","NCS","Human","Altron","Jaleco","Towa Chiki","Yutaka","Varie","Epcoh","Athena","Asmik Ace Entertainment","Natsume","King Records","Atlus","Epic/Sony Records","IGS","A Wave","Extreme Entertainment","LJN"};

const char* cartridge_types[] = {"ROM ONLY","MBC1","MBC1+RAM","MBC1+RAM+BATTERY","MBC2","MBC2+BATTERY","ROM+RAM 9","ROM+RAM+BATTERY 9","MMM01","MMM01+RAM","MMM01+RAM+BATTERY","MBC3+TIMER+BATTERY","MBC3+TIMER+RAM+BATTERY 10","MBC3","MBC3+RAM 10","MBC3+RAM+BATTERY 10","MBC5","MBC5+RAM","MBC5+RAM+BATTERY","MBC5+RUMBLE","MBC5+RUMBLE+RAM","MBC5+RUMBLE+RAM+BATTERY","MBC6","MBC7+SENSOR+RUMBLE+RAM+BATTERY","POCKET CAMERA","BANDAI TAMA5","HuC3","HuC1+RAM+BATTERY"};

const uint8_t cartridge_type_codes[] = {0x00,0x01,0x02,0x03,0x05,0x06,0x08,0x09,0x0B,0x0C,0x0D,0x0F,0x10,0x11,0x12,0x13,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x20,0x22,0xFC,0xFD,0xFE,0xFF};

const char* RAM_sizes[] = {"0 (No RAM)", "2 KiB (I don't know how)", "8 KiB (1 bank)", "32 KiB (4 banks)", "128 KiB (16 banks)", "64 KiB (8 banks)"};


uint8_t get_licensee_name(uint8_t code)
{
    for(int i=0;i<147;i++)
    {
        if(licensee_codes[i]==code) return i;
    }
    return 0;
}

uint8_t get_cartridge_type_name(uint8_t code)
{
    for(int i=0;i<28;i++)
    {
        if(cartridge_type_codes[i]==code) return i;
    }
    return 0;
}

void read_offset(FILE* f, char* buf, size_t offset, size_t size)
{
    fseek(f, offset, SEEK_SET);
    fread(buf, size, 1, f);
}

int main(int argc, char *argv[])
{
    FILE* f = fopen(argv[1], "r");

    char title[17];
    uint8_t SGB_Flag;
    uint8_t cartridge_type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t dest_code;
    uint8_t old_licensee_code;
    uint8_t version;

    read_offset(f, title, 0x134, 16);   title[16]=0;
    read_offset(f, (char*)&SGB_Flag, 0x146, 1);
    read_offset(f, (char*)&cartridge_type, 0x147, 1);
    read_offset(f, (char*)&rom_size, 0x148, 1);
    read_offset(f, (char*)&ram_size, 0x149, 1);
    read_offset(f, (char*)&dest_code, 0x14A, 1);
    read_offset(f, (char*)&old_licensee_code, 0x14B, 1);
    read_offset(f, (char*)&version, 0x14C, 1);

    fclose(f);

    const char* licensee = licensee_names[get_licensee_name(old_licensee_code)];
    const char* cartridge_type_s = cartridge_types[get_cartridge_type_name(cartridge_type)];


    printf("Title: %s\n", title);
    (SGB_Flag == 0x03) ? printf("SGB Function Support: Yes\n") : printf("SGB Function Support: No\n");
    printf("Cartridge type: %s\n", cartridge_type_s);
    printf("ROM Size: %d KiB (%d ROM banks)\n", 32<<(int)rom_size, 2<<(int)rom_size);
    printf("RAM Size: %s\n", RAM_sizes[ram_size]);
    (dest_code == 0x00) ? printf("Destination Code: Japan (and possibly overseas)\n") : printf("Destination Code: Overseas only\n");
    printf("Licensee: %s\n", licensee);
    printf("Version: %d", (int)version);

    getchar();
}