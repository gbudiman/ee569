set terminal gif size 1512, 1024
set multiplot layout 3, 3
set xrange [0:255]
set y2range [0:255]
set y2tics
set key off

set boxwidth 0

#set xlabel "Brightness"
#set ylabel "PDF (pixels)"
#set y2label "CDF (pixels)"

set tics out

set title "Park - Red"
plot "images/P2/Park_hist_red_pdf.txt" smooth freq with boxes lt rgb "#FF0000" axes x1y1, "images/P2/Park_tf_red.txt" with line axes x1y2

set title "Park SFX - Red"
plot "images/P2/Park_sfx_hist_red_pdf.txt" smooth freq with boxes lt rgb "#FF0000" axes x1y1

set title "Park Matching - Red"
plot "images/P2/Park_match_hist_red_pdf.txt" smooth freq with boxes lt rgb "#FF0000" axes x1y1

set title "Park - Green"
plot "images/P2/Park_hist_green_pdf.txt" smooth freq with boxes lt rgb "#00FF00" axes x1y1, "images/P2/Park_tf_green.txt" with line axes x1y2

set title "Park - Green"
plot "images/P2/Park_sfx_hist_green_pdf.txt" smooth freq with boxes lt rgb "#00FF00" axes x1y1

set title "Park Matching - Green"
plot "images/P2/Park_match_hist_green_pdf.txt" smooth freq with boxes lt rgb "#00FF00" axes x1y1

set title "Park - Blue"
plot "images/P2/Park_hist_blue_pdf.txt" smooth freq with boxes lt rgb "#0000FF" axes x1y1, "images/P2/Park_tf_blue.txt" with line axes x1y2

set title "Park SFX - Blue"
plot "images/P2/Park_sfx_hist_blue_pdf.txt" smooth freq with boxes lt rgb "#0000FF" axes x1y1

set title "Park Matching - Blue"
plot "images/P2/Park_match_hist_blue_pdf.txt" smooth freq with boxes lt rgb "#0000FF" axes x1y1
