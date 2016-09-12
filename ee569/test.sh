./main crop "../images/P1/Anna.raw" 250 300 1 "../images/tests/Anna_cropped.raw" 55 85 184 214
./main resize "../images/P1/Anna.raw" 250 300 1 "../images/tests/Anna_resized.raw" 400 400
./main rgb2cmy "../images/P1/Clownfish.raw" 600 400 1 "../images/tests/Clownfish.raw"
./main rgb2hsl "../images/P1/Turtle.raw" 400 250 1 "../images/tests/Turtle.raw"
./main hist_equalize_linear "../images/P2/Beach_dark.raw" 500 375 0 "../images/tests/Beach_dark_linear_equalized.raw"
./main hist_equalize_cdf "../images/P2/Beach_dark.raw" 500 375 0 "../images/tests/Beach_dark_cdf_equalized.raw"
./main hist_equalize_linear "../images/P2/Skyline.raw" 600 400 1 "../images/tests/Skyline_linear_equalized.raw"
./main hist_equalize_cdf "../images/P2/Skyline.raw" 600 400 1 "../images/tests/Skyline_cdf_equalized.raw"
./main sfx "../images/P2/Trojan.raw" 450 300 "../images/P2/Skyline.raw" 600 400 "../images/tests/Trojan.raw"
./main hist_match "../images/P2/Student_2.raw" 500 375 0 "../images/tests/Student_2.raw" 125 40
./main denoise mean "../images/P3/Lena_noisy.raw" 512 512 1 "../images/tests/Lena_mean_3.raw" 3
./main denoise median "../images/P3/Lena_noisy.raw" 512 512 1 "../images/tests/Lena_median_3.raw" 3
./main denoise mean "../images/tests/Lena_median_3.raw" 512 512 1 "../images/tests/Lena_median_3_mean_3.raw" 3
./main denoise gaussian "../images/P3/Lena_noisy.raw" 512 512 1 "../images/tests/Lena_gaussian_2_1.raw" 2 1
./main psnr "../images/P3/Lena_noisy.raw" "../images/P3/Lena.raw" 512 512 1
./main psnr "../images/P3/Lena.raw" "../images/tests/Lena_mean_3.raw" 512 512 1
./main psnr "../images/P3/Lena.raw" "../images/tests/Lena_median_3.raw" 512 512 1
./main psnr "../images/P3/Lena.raw" "../images/tests/Lena_median_3_mean_3.raw" 512 512 1
./main psnr "../images/P3/Lena.raw" "../images/tests/Lena_gaussian_2_1.raw" 512 512 1
./main denoise nlm "../images/P3/Buildings.raw" 512 512 1 "../images/tests/Buildings_7_3_1000.raw" 7 3 1000
./main psnr "../images/P3/Buildings.raw" "../images/tests/Buildings_7_3_1000.raw" 512 512 1