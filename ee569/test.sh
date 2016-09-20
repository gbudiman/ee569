# P1A
./main crop "../images/P1/Anna.raw" 250 300 1 "../images/tests/Anna_cropped_square.raw" 55 85 184 214
./main crop "../images/P1/Anna.raw" 250 300 1 "../images/tests/Anna_cropped_rect.raw" 55 30 184 239
./main crop "../images/P1/Rebel.raw" 250 300 1 "../images/tests/Rebel_cropped_rect.raw" 35 20 164 199
./main crop "../images/P1/Rebel.raw" 250 300 1 "../images/tests/Rebel_cropped_square.raw" 25 25 174 174

./main resize "../images/tests/Anna_cropped_square.raw" 130 130 1 "../images/tests/Anna_resized_1.raw" 100 100
./main resize "../images/tests/Anna_cropped_square.raw" 130 130 1 "../images/tests/Anna_resized_2.raw" 200 200
./main resize "../images/tests/Anna_cropped_square.raw" 130 130 1 "../images/tests/Anna_resized_3.raw" 300 300
./main resize "../images/tests/Rebel_cropped_square.raw" 150 150 1 "../images/tests/Rebel_resized_1.raw" 100 100
./main resize "../images/tests/Rebel_cropped_square.raw" 150 150 1 "../images/tests/Rebel_resized_2.raw" 200 200
./main resize "../images/tests/Rebel_cropped_square.raw" 150 150 1 "../images/tests/Rebel_resized_3.raw" 300 300

# P1B
./main rgb2cmy "../images/P1/Clownfish.raw" 600 400 1 "../images/tests/Clownfish.raw"
./main rgb2cmy "../images/P1/Octopus.raw" 500 374 1 "../images/tests/Octopus.raw"
./main rgb2hsl "../images/P1/Turtle.raw" 400 250 1 "../images/tests/Turtle.raw"
./main rgb2hsl "../images/P1/Jellyfish.raw" 500 333 1 "../images/tests/Jellyfish.raw"

# P2A
./main hist_equalize_linear "../images/P2/Beach_dark.raw" 500 375 0 "../images/tests/Beach_dark_linear_equalized.raw"
./main hist_equalize_cdf "../images/P2/Beach_dark.raw" 500 375 0 "../images/tests/Beach_dark_cdf_equalized.raw"

# P2B
./main hist_equalize_linear "../images/P2/Skyline.raw" 600 400 1 "../images/tests/Skyline_linear_equalized.raw"
./main hist_equalize_cdf "../images/P2/Skyline.raw" 600 400 1 "../images/tests/Skyline_cdf_equalized.raw"

# P2C
./main sfx "../images/P2/Trojan.raw" 450 300 "../images/P2/Skyline.raw" 600 400 "../images/tests/Trojan.raw"
./main sfx "../images/P2/Park.raw" 259 194 "../images/P2/Skyline.raw" 600 400 "../images/tests/Park.raw"

# P2D
./main hist_match "../images/P2/Student_1.raw" 500 332 0 "../images/tests/Student_2.raw" 125 40
./main hist_match "../images/P2/Student_2.raw" 500 375 0 "../images/tests/Student_2.raw" 125 40

# P3A
./main denoise mean "../images/P3/Lena_noisy.raw" 512 512 1 "../images/tests/Lena_mean_3.raw" 3
./main denoise median "../images/P3/Lena_noisy.raw" 512 512 1 "../images/tests/Lena_median_3.raw" 3

# to cascade filter, simply call another denoising command on output as follows
./main denoise mean "../images/tests/Lena_median_3.raw" 512 512 1 "../images/tests/Lena_median_3_mean_3.raw" 3
./main denoise gaussian "../images/P3/Lena_noisy.raw" 512 512 1 "../images/tests/Lena_gaussian_2_1.raw" 2 1
./main psnr "../images/P3/Lena_noisy.raw" "../images/P3/Lena.raw" 512 512 1
./main psnr "../images/P3/Lena.raw" "../images/tests/Lena_mean_3.raw" 512 512 1
./main psnr "../images/P3/Lena.raw" "../images/tests/Lena_median_3.raw" 512 512 1
./main psnr "../images/P3/Lena.raw" "../images/tests/Lena_median_3_mean_3.raw" 512 512 1
./main psnr "../images/P3/Lena.raw" "../images/tests/Lena_gaussian_2_1.raw" 512 512 1

# P3B
# !!! WARNING !!!
# NLM is expensive algorithm. Depending input parameters, it may take between minutes to hours
./main denoise nlm "../images/P3/Buildings.raw" 512 512 1 "../images/tests/Buildings_7_3_1000.raw" 7 3 1000
./main psnr "../images/P3/Buildings.raw" "../images/tests/Buildings_7_3_1000.raw" 512 512 1