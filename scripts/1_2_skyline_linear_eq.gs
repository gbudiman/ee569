set terminal gif size 1024,1024
set multiplot layout 3, 1
set xrange [0:255]
set y2tics
set key off

set boxwidth 0
set ylabel "PDF (pixels)"
set y2label "CDF (pixels)"

set tics out

set title "Skyline Linear Eq - Red Channel"
plot "images/P2/Skyline_eqlz_a_hist_red_pdf.txt" smooth freq with boxes lt rgb "#FF0000" axes x1y1, "images/P2/Skyline_eqlz_a_hist_red_cdf.txt" with line axes x1y2

set title "Skyline Linear Eq - Green Channel"
plot "images/P2/Skyline_eqlz_a_hist_green_pdf.txt" smooth freq with boxes lt rgb "#00FF00" axes x1y1, "images/P2/Skyline_eqlz_a_hist_green_cdf.txt" with line axes x1y2

set title "Skyline Linear Eq - Blue Channel"
plot "images/P2/Skyline_eqlz_a_hist_blue_pdf.txt" smooth freq with boxes lt rgb "#0000FF" axes x1y1, "images/P2/Skyline_eqlz_a_hist_blue_cdf.txt" with line axes x1y2