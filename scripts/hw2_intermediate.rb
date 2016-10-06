Dir.foreach('../ee569/hw2_out') do |item|
  size = nil

  next unless item =~ /.raw$/

  size = case item
  when /^Butterfly/ then '335x320'
  when /^Fly/ then '222x223'
  when /^Probe/ then '496x502'
  when /^Rice/ then '690x500'
  else
    next
  end

  expanded_item_path = '../ee569/hw2_out/' + item
  output = expanded_item_path.gsub(/raw$/, 'png')

  puts "#{expanded_item_path} => #{output}"
  `ruby pic.rb --size #{size} #{expanded_item_path} --out #{output} --gray`
end

Dir.foreach('../hw2_images/tests/') do |item|
  size = nil

  next unless item =~ /.raw$/

  size = case item
  when /^House/ then '512x512'
  when /^Kitten/ then '300x300'
  when /^Hillary/ then '512x512'
  when /^Trump/ then '512x512'
  when /field/ then '972x648'
  else
    next
  end

  gray = case item
  when /^House/ then '--gray'
  else ''
  end

  expanded_item_path = '../hw2_images/tests/' + item
  output = expanded_item_path.gsub(/raw$/, 'png')

  puts "#{expanded_item_path} => #{output}"
  `ruby pic.rb --size #{size} #{expanded_item_path} --out #{output} #{gray}`
end