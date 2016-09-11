# ./main crop "../images/P1/Anna.raw" 250 300 1 "../images/tests/Anna_cropped.raw" 55 85 184 214
# ./main resize "../images/P1/Anna.raw" 250 300 1 "../images/tests/Anna_resized.raw" 400 400
# ./main rgb2cmy "../images/P1/Clownfish.raw" 600 400 1 "../images/tests/Clownfish.raw"
# ./main rgb2hsl "../images/P1/Turtle.raw" 400 250 1 "../images/tests/Turtle.raw"
# ./main hist_equalize_linear "../images/P2/Beach_dark.raw" 500 375 0 "../images/tests/Beach_dark_linear_equalized.raw"
# ./main hist_equalize_cdf "../images/P2/Beach_dark.raw" 500 375 0 "../images/tests/Beach_dark_cdf_equalized.raw"
# ./main hist_equalize_linear "../images/P2/Skyline.raw" 600 400 1 "../images/tests/Skyline_linear_equalized.raw"
# ./main hist_equalize_cdf "../images/P2/Skyline.raw" 600 400 1 "../images/tests/Skyline_cdf_equalized.raw"
./main sfx "../images/P2/Trojan.raw" 450 300 "../images/P2/Skyline.raw" 600 400 "../images/tests/Trojan.raw"
./main hist_match "../images/P2/Student_2.raw" 500 375 0 "../images/tests/Student_2.raw" 125 40