set terminal gif size 512, 1024
set multiplot layout 3, 1
set xrange [0:255]
set y2range [0:255]
set y2tics
set key off

set boxwidth 0

#set xlabel "Brightness"
#set ylabel "PDF (pixels)"
#set y2label "CDF (pixels)"

set tics out

set title "Skyline Ref - Red"
plot "images/P2/Skyline_hist_red_pdf.txt" smooth freq with boxes lt rgb "#FF0000" axes x1y1

set title "Skyline Ref - Green"
plot "images/P2/Skyline_hist_green_pdf.txt" smooth freq with boxes lt rgb "#00FF00" axes x1y1

set title "Trojan Ref - Blue"
plot "images/P2/Skyline_hist_blue_pdf.txt" smooth freq with boxes lt rgb "#0000FF" axes x1y1
