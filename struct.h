#ifndef STRUCT
#define STRUCT


#pragma pack(push, 1)
typedef struct {
    uint16_t a;
    uint16_t b;
    uint16_t c;
    uint16_t d;
    uint16_t e;
    uint16_t f;
    uint16_t g;
} data;

typedef struct {
    uint16_t ip_digit_1;
    uint16_t ip_digit_2;
    uint16_t ip_digit_3;
    uint16_t ip_digit_4;
} ip;

typedef struct {
    uint8_t ser_no;
    ip ip_addr;
    data data_values[8];
} data_2;

typedef struct {
    data_2 sub_struct[4];
} main_struct;
#pragma pack(pop)



#endif // STRUCT

