CC=g++-6
all: picture rgbpixel cmykpixel hslpixel histogram tfh runs
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

runs:
	$(CC) -c run_1_1_a_cropping.cpp
	$(CC) -c run_1_1_a_resizing.cpp
	$(CC) -c run_1_1_b_cmyk.cpp
	$(CC) -c run_1_1_b_hsl.cpp
	$(CC) -c run_1_2_a_histogram_equalization.cpp
	$(CC) -c run_1_2_b_histcolor_equalization.cpp

clean:
	rm *.o