/*
 * SpiderpigOS
 * Copyright (C) 2009 - 2010 Davide Gessa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * \file driver/video/vesa.h
 * \author Davide Gessa
 * \date 12-27-09
 */
#ifndef VIDEO_VESA_H
#define VIDEO_VESA_H

#include <types.h>
#include <driver.h>


extern driver_t driver_vesa;

/**
 * Struttura per le informazioni generali del vbe
 */
typedef struct
{
    char signature[4];
    uint16_t version;
    uint32_t oem_string_ptr;
    uint32_t capabilities;
    uint32_t video_mode_ptr;
    uint16_t total_memory;
	
	// Vesa 2.0
	uint32_t oem_software_rev;
	char *oem_vendor_name;
	char *oem_product_name;
	char *oem_product_rev;
} vesa_info_t;

 


/**
 * Struttura per le informazioni della modalita' del vbe
 */
typedef struct
{
    uint16_t mode_attributes;
    uint8_t wina_attributes;
    uint8_t winb_attributes;
    uint16_t win_granularity;
    uint16_t win_size;
    uint16_t wina_segment;
    uint16_t winb_segment;
    uint32_t win_pos_func_ptr;
    uint16_t bytes_per_scan_line;
    uint16_t width;
    uint16_t height;
    uint8_t char_width;
    uint8_t char_height;
    uint8_t num_planes;
    uint8_t bits_per_pixel;
    uint8_t num_banks;
    uint8_t memory_model_type;
    uint8_t bank_size;
    uint8_t num_image_pages;
    uint8_t reserved1;
    uint8_t red_mask_size;
    uint8_t red_field_position;
    uint8_t green_mask_size;
    uint8_t green_field_position;
    uint8_t blue_mask_size;
    uint8_t blue_field_position;
    uint8_t reserved_mask_size;
    uint8_t reserved_mask_position;
    uint8_t direct_color_mode_info;
    uint32_t phys_base_ptr;
    uint32_t offscreen_mem_ptr;
    uint16_t offscreen_mem_size;
    uint16_t lin_bytes_per_scan_line;
    uint8_t bnk_num_image_pages;
    uint8_t lin_num_image_pages;
    uint8_t lin_red_mask_size;
    uint8_t lin_red_field_position;
    uint8_t lin_green_mask_size;
    uint8_t lin_green_field_position;
    uint8_t lin_blue_mask_size;
    uint8_t lin_blue_field_position;
    uint8_t lin_rsvd_mask_size;
    uint8_t lin_rsvd_field_position;
    uint32_t max_pixel_clock;
    uint8_t reserved4[190];
} vesa_mode_info_t;


vesa_mode_info_t *vesa_get_mode_info();

void vesa_draw_pixel(uint32_t, uint32_t, uint32_t);
uint32_t vesa_get_pixel(uint32_t, uint32_t);
uint32_t vesa_set_mode(uint32_t, uint32_t, uint32_t);

#endif
