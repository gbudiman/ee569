CC=g++-6
CFLAGS=-Ofast
all: picture rgbpixel cmykpixel hslpixel histogram tfh psnr kernel patch_map nlm_weight runs
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
	$(CC) $(CFLAGS) -c run_1_3_b_nlm.cpp

clean:
	rm *.o main