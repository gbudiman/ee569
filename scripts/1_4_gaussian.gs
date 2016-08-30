set terminal gif size 1024,1024
set multiplot layout 4, 2
set xrange [0:255]
set y2tics
set key off

set boxwidth 0
set ylabel "PDF (pixels)"
set y2label "CDF (pixels)"

set tics out

set title "Target Histogram 1"
plot "images/P2/gaussian1_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/gaussian1_hist_gray_cdf.txt" with line axes x1y2

set title "Target Histogram 2"
plot "images/P2/gaussian2_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/gaussian2_hist_gray_cdf.txt" with line axes x1y2

set title "Source Histogram 1"
plot "images/P2/Student_1_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Student_1_hist_gray_cdf.txt" with line axes x1y2

set title "Source Histogram 2"
plot "images/P2/Student_2_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Student_2_hist_gray_cdf.txt" with line axes x1y2

set title "Matched Histogram 1"
plot "images/P2/Student_1_matched_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Student_1_matched_hist_gray_cdf.txt" with line axes x1y2