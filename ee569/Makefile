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
CVLIBS=-I/usr/local/opt/opencv3/include -L/usr/local/opt/opencv3/lib
CVFLAGS=-lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_video -lopencv_videoio -lopencv_videostab -lopencv_xfeatures2d -lopencv_ximgproc -lopencv_xobjdetect -lopencv_ccalib -lopencv_saliency -lopencv_surface_matching -lopencv_xphoto
all: picture rgbpixel cmykpixel hslpixel histogram tfh psnr kernel patch_map nlm_weight matrix binary_matrix grain_categorizer morph_matrix mark_pattern_matrix coordinate bitstream_matrix tracer bounding_box spatial_data boundary_tracer mpeg7_classifier kcluster laws_filter statistics filter_energy f_measure runs
	$(CC) $(CFLAGS) $(CVLIBS) $(CVFLAGS) *.o main.cpp -o main

picture:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c Picture.cpp

rgbpixel:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c RgbPixel.cpp

cmykpixel:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c CmykPixel.cpp

hslpixel:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c HslPixel.cpp

histogram:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c Histogram.cpp

tfh:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c TransferFunction.cpp

psnr:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c Psnr.cpp

kernel:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c Kernel.cpp

patch_map:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c PatchMap.cpp

nlm_weight:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c NlmWeight.cpp

binary_matrix:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c BinaryMatrix.cpp

matrix:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c Matrix.cpp

grain_categorizer:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c GrainCategorizer.cpp

coordinate:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c Coordinate.cpp

morph_matrix:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c MorphMatrix.cpp

mark_pattern_matrix:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c MarkPatternMatrix.cpp

bitstream_matrix:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c BitStreamMatrix.cpp

tracer:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c Tracer.cpp

bounding_box:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c BoundingBox.cpp

spatial_data:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c SpatialData.cpp

boundary_tracer:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c BoundaryTracer.cpp

mpeg7_classifier:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c Mpeg7Classifier.cpp

kcluster:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c KCluster.cpp

laws_filter:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c LawsFilter.cpp

statistics:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c Statistics.cpp

filter_energy:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c FilterEnergy.cpp

f_measure:
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c FMeasure.cpp

runs:
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_1_a_cropping.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_1_a_resizing.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_1_b_cmyk.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_1_b_hsl.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_2_a_histogram_equalization.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_2_b_histcolor_equalization.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_2_c_sfx.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_2_d_histogram_transform.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_3_a_median_filtering.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_3_a_cascaded_filter.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_3_b_nlm.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_3_b_cascaded_filter.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_1_3_psnr_calculator.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_2_1_a_diamond_warp.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_2_1_c_homography.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_f_2_1_b_puzzle_matching.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_2_2_a_dithering.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_2_3_a_rice_grain.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_2_3_b_mpeg7.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_3_1_texture.cpp
	$(CC) $(CVLIBS) $(CFLAGS) -c run_3_1_segmentation.cpp
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c run_3_2_salient_points.cpp
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c run_3_2_bag_of_words.cpp
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c run_3_3_canny.cpp
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c run_3_3_structured_edge.cpp
	$(CC) $(CVLIBS) $(CFLAGS) $(CVFLAGS) -c run_3_3_ground_truth.cpp

clean:
	rm *.o main