set terminal gif size 1520, 1024
set multiplot layout 3,3
set xrange [0:255]
#set y2range [0:255]
#set y2tics
set key off

set boxwidth 0

#set xlabel "Brightness"
#set ylabel "PDF (pixels)"
#set y2label "CDF (pixels)"

set tics out

set title "Lena - Red"
plot "images/P3/Lena_hist_red_pdf.txt" smooth freq with boxes lt rgb "#FF0000" axes x1y1

set title "Lena Noisy - Red"
plot "images/P3/Lena_noisy_hist_red_pdf.txt" smooth freq with boxes lt rgb "#FF0000" axes x1y1

set title "Lena Median - Red"
plot "images/P3/Lena_median_denoised_hist_red_pdf.txt" smooth freq with boxes lt rgb "#FF0000" axes x1y1

set title "Lena - Green"
plot "images/P3/Lena_hist_green_pdf.txt" smooth freq with boxes lt rgb "#00FF00" axes x1y1

set title "Lena Noisy - Green"
plot "images/P3/Lena_noisy_hist_green_pdf.txt" smooth freq with boxes lt rgb "#00FF00" axes x1y1

set title "Lena Median - Green"
plot "images/P3/Lena_median_denoised_hist_green_pdf.txt" smooth freq with boxes lt rgb "#00FF00" axes x1y1

set title "Lena - Blue"
plot "images/P3/Lena_hist_blue_pdf.txt" smooth freq with boxes lt rgb "#0000FF" axes x1y1

set title "Lena Noisy - Blue"
plot "images/P3/Lena_noisy_hist_blue_pdf.txt" smooth freq with boxes lt rgb "#0000FF" axes x1y1

set title "Lena Median - Blue"
plot "images/P3/Lena_median_denoised_hist_blue_pdf.txt" smooth freq with boxes lt rgb "#0000FF" axes x1y1