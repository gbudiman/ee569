CC=g++-6
all: picture rgbpixel cmykpixel hslpixel histogram tfh psnr kernel runs
	$(CC) *.o main.cpp -o main

picture:
	$(CC) -c Picture.cpp

rgbpixel:
	$(CC) -c RgbPixel.cpp

cmykpixel:
	$(CC) -c CmykPixel.cpp

hslpixel:
	$(CC) -c HslPixel.cpp

histogram:
	$(CC) -c Histogram.cpp

tfh:
	$(CC) -c TransferFunction.cpp

psnr:
	$(CC) -c Psnr.cpp

kernel:
	$(CC) -c Kernel.cpp

runs:
	$(CC) -c run_1_1_a_cropping.cpp
	$(CC) -c run_1_1_a_resizing.cpp
	$(CC) -c run_1_1_b_cmyk.cpp
	$(CC) -c run_1_1_b_hsl.cpp
	$(CC) -c run_1_2_a_histogram_equalization.cpp
	$(CC) -c run_1_2_b_histcolor_equalization.cpp
	$(CC) -c run_1_2_c_sfx.cpp
	$(CC) -c run_1_2_d_histogram_transform.cpp
	$(CC) -c run_1_3_a_median_filtering.cpp

clean:
	rm *.o main