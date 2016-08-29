set terminal gif size 1024,1024
set multiplot layout 2, 1
set xrange [0:255]
set y2tics
set key off

set boxwidth 0
set title "Beach bright -> linear equalized"
set xlabel "Brightness"
set ylabel "PDF (pixels)"
set y2label "CDF (pixels)"

set tics out
plot "images/P2/Beach_bright_eqlz_a_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Beach_bright_eqlz_a_hist_gray_cdf.txt" with line axes x1y2

set title "Beach dark -> linear equalized"
plot "images/P2/Beach_dark_eqlz_a_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Beach_dark_eqlz_a_hist_gray_cdf.txt" with line axes x1y2