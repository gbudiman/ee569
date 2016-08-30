set terminal gif size 1520, 1024
set multiplot layout 3, 3
set xrange [0:255]
set y2tics
set key off

set boxwidth 0

#set xlabel "Brightness"
#set ylabel "PDF (pixels)"
#set y2label "CDF (pixels)"

set tics out

set title "Beach bright"
plot "images/P2/Beach_bright_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Beach_bright_hist_gray_cdf.txt" with line axes x1y2

set title "Beach bright - Linear TF"
plot "images/P2/Beach_bright_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Beach_bright_tf_gray.txt" with line axes x1y2

set title "Beach bright - Linear Eq"
plot "images/P2/Beach_bright_eqlz_a_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Beach_bright_eqlz_a_hist_gray_cdf.txt" with line axes x1y2

set title "Beach dark"
plot "images/P2/Beach_dark_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Beach_dark_hist_gray_cdf.txt" with line axes x1y2

set title "Beach dark - Linear TF"
plot "images/P2/Beach_dark_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Beach_dark_tf_gray.txt" with line axes x1y2

set title "Beach dark - Linear Eq"
plot "images/P2/Beach_dark_eqlz_a_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Beach_dark_eqlz_a_hist_gray_cdf.txt" with line axes x1y2

set title "Beach bright - CDF Eq"
plot "images/P2/Beach_bright_eqlz_b_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Beach_bright_eqlz_b_hist_gray_cdf.txt" with line axes x1y2

set title "Beach dark CDF Eq"
plot "images/P2/Beach_dark_eqlz_b_hist_gray_pdf.txt" smooth freq with boxes lt rgb "#101010" axes x1y1, "images/P2/Beach_dark_eqlz_b_hist_gray_cdf.txt" with line axes x1y2