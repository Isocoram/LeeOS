%define BIOS_start_address              0x7c00
%define BIOS_disk_reset_service         0x00
%define BIOS_disk_read_service          0x02
%define BIOS_video_service_interrupt    0x10
%define BIOS_disk_access_interrupt      0x13
%define BIOS_teletype_output_function   0x0e

;   0x0d: carriage return, 0x0a: line feed - cursor control characters
%define newline                         0x0d, 0x0a
%define backspace                       0x08

%define sector_count                    4
%define cylinder                        0
%define head                            0
%define sector                          2
%define stage2_load_address             0x8000
%define kernel_load_address             0x100000
%define kernel_sector_count             2