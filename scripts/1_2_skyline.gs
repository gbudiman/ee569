set terminal gif size 1520,1024
set multiplot layout 4, 3
set xrange [0:255]
set y2tics
set key off

set boxwidth 0
#set ylabel "PDF (pixels)"
#set y2label "CDF (pixels)"

set tics out

set title "Skyline - Red Channel"
plot "images/P2/Skyline_hist_red_pdf.txt" smooth freq with boxes lt rgb "#FF0000" axes x1y1, "images/P2/Skyline_hist_red_cdf.txt" with line axes x1y2

set title "Skyline - Green Channel"
plot "images/P2/Skyline_hist_green_pdf.txt" smooth freq with boxes lt rgb "#00FF00" axes x1y1, "images/P2/Skyline_hist_green_cdf.txt" with line axes x1y2

set title "Skyline - Blue Channel"
plot "images/P2/Skyline_hist_blue_pdf.txt" smooth freq with boxes lt rgb "#0000FF" axes x1y1, "images/P2/Skyline_hist_blue_cdf.txt" with line axes x1y2

set title "Skyline - Linear TF Red Channel"
plot "images/P2/Skyline_hist_red_pdf.txt" smooth freq with boxes lt rgb "#FF0000" axes x1y1, "images/P2/Skyline_tf_red.txt" with line axes x1y2

set title "Skyline - Linear TF Green Channel"
plot "images/P2/Skyline_hist_green_pdf.txt" smooth freq with boxes lt rgb "#00FF00" axes x1y1, "images/P2/Skyline_tf_green.txt" with line axes x1y2

set title "Skyline - Linear TF Blue Channel"
plot "images/P2/Skyline_hist_blue_pdf.txt" smooth freq with boxes lt rgb "#0000FF" axes x1y1, "images/P2/Skyline_tf_blue.txt" with line axes x1y2

set title "Skyline - Linear Eq Red Channel"
plot "images/P2/Skyline_eqlz_a_hist_red_pdf.txt" smooth freq with boxes lt rgb "#FF0000" axes x1y1, "images/P2/Skyline_eqlz_a_hist_red_cdf.txt" with line axes x1y2

set title "Skyline - Linear Eq Green Channel"
plot "images/P2/Skyline_eqlz_a_hist_green_pdf.txt" smooth freq with boxes lt rgb "#00FF00" axes x1y1, "images/P2/Skyline_eqlz_a_hist_green_cdf.txt" with line axes x1y2

set title "Skyline - Linear Eq Blue Channel"
plot "images/P2/Skyline_eqlz_a_hist_blue_pdf.txt" smooth freq with boxes lt rgb "#0000FF" axes x1y1, "images/P2/Skyline_eqlz_a_hist_blue_cdf.txt" with line axes x1y2

set title "Skyline - CDF Eq Red Channel"
plot "images/P2/Skyline_eqlz_b_hist_red_pdf.txt" smooth freq with boxes lt rgb "#FF0000" axes x1y1, "images/P2/Skyline_eqlz_b_hist_red_cdf.txt" with line axes x1y2

set title "Skyline - CDF Eq Green Channel"
plot "images/P2/Skyline_eqlz_b_hist_green_pdf.txt" smooth freq with boxes lt rgb "#00FF00" axes x1y1, "images/P2/Skyline_eqlz_b_hist_green_cdf.txt" with line axes x1y2

set title "Skyline - CDF Eq Blue Channel"
plot "images/P2/Skyline_eqlz_b_hist_blue_pdf.txt" smooth freq with boxes lt rgb "#0000FF" axes x1y1, "images/P2/Skyline_eqlz_b_hist_blue_cdf.txt" with line axes x1y2