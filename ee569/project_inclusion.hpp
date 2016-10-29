//
//  project_inclusion.hpp
//  ee569
//
//  Created by Gloria Budiman on 8/27/16.
//  Finalized on 10/6/16
//  gbudiman@usc.edu 6528-1836-50
//  Copyright © 2016 gbudiman. All rights reserved.
//

#ifndef project_inclusion_h
#define project_inclusion_h

void f_1_1_a_cropping();
void f_crop(char*, int, int, int, char*, int, int, int, int);
void f_1_1_a_resizing();
void f_resize(char*, int, int, int, char*, int, int);
void f_1_1_b_cmyk();
void f_cmyk(char*, int, int, int, char*);
void f_1_1_b_hsl();
void f_hsl(char*, int, int, int, char*);
void f_1_2_a_histogram_equalization();
void f_histogram_equalization(char*, int, int, int, char*, int);
void f_1_2_b_histcolor_equalization();
void f_1_2_c_sfx();
void f_sfx(char*, int, int, char*, int, int, char*);
void f_1_2_d_histogram_transform();
void f_hist_match(char*, int, int, int, char*, int, int);
void f_1_3_a_median_filtering();
void f_1_3_a_cascaded_filter();
void f_denoise_mean(char*, int, int, int, char*, int);
void f_denoise_median(char*, int, int, int, char*, int);
void f_denoise_gaussian(char*, int, int, int, char*, int, float);
void f_denoise_nlm(char*, int, int, int, char*, int, int, float);
void f_psnr(char*, char*, int, int, int);
void f_1_3_b_nlm();
void f_1_3_b_cascaded_filter();
void f_1_3_psnr_calculator();

void f_2_1_a_diamond_warp();
void f_2_1_b_puzzle_matching();
void f_2_1_c_homography();
void f_2_2_a_dithering();
void f_2_3_a_rice_grain();
void f_2_3_b_mpeg7();

void f_diamond_warp(char*, char*, int, int, int);
void f_puzzle_match(char*, int, int, char*, int, int, char*, int, int, char*, char*, int);
void f_homography(char*, int, int, char*, int, int, char*, int);
void f_dither(char*, int, int, int, char*);
void f_dither_multi(char*, int, int, int, char*, int);
void f_rice(char*, int, int, int);
void f_mpeg7(char*, int, int, char*, int, int, char*, int, int);

void f_3_1_texture();
void f_3_1_segmentation();
void f_3_1_segmentation_with_bypass();
void f_3_2_salient_points();
void f_3_2_bag_of_words();
void f_3_3_canny();
void f_3_3_structured_edge();
void f_3_3_ground_truth();

#endif /* project_inclusion_h */

