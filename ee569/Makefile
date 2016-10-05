# EE569 HW1
# Date: 9/12/2016
# Name: Gloria Budiman
# ID: 6528-1836-50
# email: gbudiman@usc.edu
#
# Compiled on Mac El Capitan using g++-6 version 6.1.0
# C++14 is required. C++11 will not work

CC=g++-6
CFLAGS=-Ofast
all: picture rgbpixel cmykpixel hslpixel histogram tfh psnr kernel patch_map nlm_weight matrix binary_matrix grain_categorizer morph_matrix mark_pattern_matrix coordinate bitstream_matrix tracer bounding_box spatial_data boundary_tracer mpeg7_classifier runs
	$(CC) $(CFLAGS) *.o main.cpp -o main

picture:
	$(CC) $(CFLAGS) -c Picture.cpp

rgbpixel:
	$(CC) $(CFLAGS) -c RgbPixel.cpp

cmykpixel:
	$(CC) $(CFLAGS) -c CmykPixel.cpp

hslpixel:
	$(CC) $(CFLAGS) -c HslPixel.cpp

histogram:
	$(CC) $(CFLAGS) -c Histogram.cpp

tfh:
	$(CC) $(CFLAGS) -c TransferFunction.cpp

psnr:
	$(CC) $(CFLAGS) -c Psnr.cpp

kernel:
	$(CC) $(CFLAGS) -c Kernel.cpp

patch_map:
	$(CC) $(CFLAGS) -c PatchMap.cpp

nlm_weight:
	$(CC) $(CFLAGS) -c NlmWeight.cpp

binary_matrix:
	$(CC) $(CFLAGS) -c BinaryMatrix.cpp

matrix:
	$(CC) $(CFLAGS) -c Matrix.cpp

grain_categorizer:
	$(CC) $(CFLAGS) -c GrainCategorizer.cpp

coordinate:
	$(CC) $(CFLAGS) -c Coordinate.cpp

morph_matrix:
	$(CC) $(CFLAGS) -c MorphMatrix.cpp

mark_pattern_matrix:
	$(CC) $(CFLAGS) -c MarkPatternMatrix.cpp

bitstream_matrix:
	$(CC) $(CFLAGS) -c BitStreamMatrix.cpp

tracer:
	$(CC) $(CFLAGS) -c Tracer.cpp

bounding_box:
	$(CC) $(CFLAGS) -c BoundingBox.cpp

spatial_data:
	$(CC) $(CFLAGS) -c SpatialData.cpp

boundary_tracer:
	$(CC) $(CFLAGS) -c BoundaryTracer.cpp

mpeg7_classifier:
	$(CC) $(CFLAGS) -c Mpeg7Classifier.cpp

runs:
	$(CC) $(CFLAGS) -c run_1_1_a_cropping.cpp
	$(CC) $(CFLAGS) -c run_1_1_a_resizing.cpp
	$(CC) $(CFLAGS) -c run_1_1_b_cmyk.cpp
	$(CC) $(CFLAGS) -c run_1_1_b_hsl.cpp
	$(CC) $(CFLAGS) -c run_1_2_a_histogram_equalization.cpp
	$(CC) $(CFLAGS) -c run_1_2_b_histcolor_equalization.cpp
	$(CC) $(CFLAGS) -c run_1_2_c_sfx.cpp
	$(CC) $(CFLAGS) -c run_1_2_d_histogram_transform.cpp
	$(CC) $(CFLAGS) -c run_1_3_a_median_filtering.cpp
	$(CC) $(CFLAGS) -c run_1_3_a_cascaded_filter.cpp
	$(CC) $(CFLAGS) -c run_1_3_b_nlm.cpp
	$(CC) $(CFLAGS) -c run_1_3_b_cascaded_filter.cpp
	$(CC) $(CFLAGS) -c run_1_3_psnr_calculator.cpp
	$(CC) $(CFLAGS) -c run_2_1_a_diamond_warp.cpp
	$(CC) $(CFLAGS) -c run_2_1_c_homography.cpp
	$(CC) $(CFLAGS) -c run_f_2_1_b_puzzle_matching.cpp
	$(CC) $(CFLAGS) -c run_2_2_a_dithering.cpp
	$(CC) $(CFLAGS) -c run_2_3_a_rice_grain.cpp
	$(CC) $(CFLAGS) -c run_2_3_b_mpeg7.cpp

clean:
	rm *.o main